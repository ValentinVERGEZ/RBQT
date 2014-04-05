/* Auteur MARTIN Nathan pour Open German Robocup en 2014 (martin.nathan@polytech-lille.net) 
   but de l'algo: Traiter le flux caméra du robotino et faire du traitement d'image:
   Reconnaissance d'objets et récupération du barycentre */


/* INCLUDES */
#include "main.hpp"

/* VARIABLES GLOBALES */

    // Image camera partagée entre plusieurs fichiers
    IplImage *img;
    //protection de la ressource image. Exclusion mutuelle afin d'éviter que
    //l'image soit monopolisée par le même utilisateur
    bool imgUsed; 
    bool imgRequested;

    //initial min et max valeurs du filtre HSV
    //Seront changées par l'utilisation de trackbars ou du clique souris
    int H_MIN = 0;
    int H_MAX = 256;
    int S_MIN = 0;
    int S_MAX = 256;
    int V_MIN = 0;
    int V_MAX = 256;

    // init varialbes of Color tracked and our tolerance towards it
      int h = 0, s = 0, v = 0, TOLERANCE = 50, TOLERANCE_V = 100; //TOLERANCE_V la tolérance niveau luminosité


    //default capture width and height
    const int FRAME_WIDTH = 640;
    const int FRAME_HEIGHT = 480;
    //max number of objects to be detected in frame
    const int MAX_NUM_OBJECTS=50;
    //minimum and maximum object area
    const int MIN_OBJECT_AREA = 30*30;
    const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;

    const std::string trackbarWindowName ("Trackbars");


/* FONCTIONS */
    void on_trackbar( int, void* ){
        //This function gets called whenever a
        // trackbar position is changed
    }

    void createTrackbars(){
        //create window for trackbars
        cvNamedWindow("Trackbars",0);
        //create memory to store trackbar name on window
        char TrackbarName[50];
        //create trackbars and insert them into window
        //3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
        //the max value the trackbar can move (eg. H_HIGH), 
        //and the function that is called whenever the trackbar is moved(eg. on_trackbar)                                ---->    ---->     ---->      
        cv::createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
        cv::createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
        cv::createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
        cv::createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
        cv::createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
        cv::createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);
    }

    std::string intToString(int number){
        std::stringstream ss;
        ss << number;
        return ss.str();
    }


// ------------------------------- FILTRAGE ---------------------------- 
   
    //sort the window using insertion sort
    //insertion sort is best for this sorting
    void insertionSort(int window[]){
        int temp, i , j;
        for(i = 0; i < 9; i++){
            temp = window[i];
            for(j = i-1; j >= 0 && temp < window[j]; j--){
                window[j+1] = window[j];
            }
            window[j+1] = temp;
        }   
    }   

    void medianfilter(cv::Mat imgToFilter){
        //create a sliding window of size 9
        int window[9];
 
        cv::Mat afterMedian = imgToFilter.clone();
        for(int y = 0; y < imgToFilter.rows; y++)
            for(int x = 0; x < imgToFilter.cols; x++)
                afterMedian.at<uchar>(y,x) = 0.0;
 
        for(int y = 1; y < imgToFilter.rows - 1; y++){
            for(int x = 1; x < imgToFilter.cols - 1; x++){
 
                // Pick up window element
 
                window[0] = imgToFilter.at<uchar>(y - 1 ,x - 1);
                window[1] = imgToFilter.at<uchar>(y, x - 1);
                window[2] = imgToFilter.at<uchar>(y + 1, x - 1);

                window[3] = imgToFilter.at<uchar>(y - 1, x);
                window[4] = imgToFilter.at<uchar>(y, x);
                window[5] = imgToFilter.at<uchar>(y + 1, x);

                window[6] = imgToFilter.at<uchar>(y - 1, x + 1);
                window[7] = imgToFilter.at<uchar>(y, x + 1);
                window[8] = imgToFilter.at<uchar>(y + 1, x + 1);

 
                // sort the window to find median
                insertionSort(window);
 
                // assign the median to centered element of the matrix
                afterMedian.at<uchar>(y,x) = window[4];
            }
        }
    }


// ---------------------------- opération de traitement d'image -------------------------------

    /* effectue le traitement de l'image binaire pour obtenir un objet plus fidèle à l'objet réel */
    void morphOps(cv::Mat &mask){ //en paramètre le flux à traiter

        //create structuring element that will be used to "dilate" and "erode" image.
        //the element chosen here is a 3px by 3px ellipse
        cv::Mat erodeElement = getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
        //dilate with larger element so make sure object is nicely visible
        cv::Mat dilateElement = getStructuringElement(cv::MORPH_RECT,cv::Size(8,8)); //ancien 3.3

        for(int k=0;k<3;k++){
            dilate(mask,mask,dilateElement);
            erode(mask,mask,erodeElement);
        }
    }

    void drawObject(int x, int y,cv::Mat &frame){
        #define B 0
        #define G 0
        #define R 255
        #define COLOR_TARGET cv::Scalar(B,G,R) 
        //use some of the openCV drawing functions to draw crosshairs
        //on your tracked image!
        //added 'if' and 'else' statements to prevent
        //memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

        circle(frame,cv::Point(x,y),20,COLOR_TARGET,2);
        if(y-25>0)
        line(frame,cv::Point(x,y),cv::Point(x,y-25),COLOR_TARGET,2);
        else line(frame,cv::Point(x,y),cv::Point(x,0),COLOR_TARGET,2);
        if(y+25<FRAME_HEIGHT)
        line(frame,cv::Point(x,y),cv::Point(x,y+25),COLOR_TARGET,2);
        else line(frame,cv::Point(x,y),cv::Point(x,FRAME_HEIGHT),COLOR_TARGET,2);
        if(x-25>0)
        line(frame,cv::Point(x,y),cv::Point(x-25,y),COLOR_TARGET,2);
        else line(frame,cv::Point(x,y),cv::Point(0,y),COLOR_TARGET,2);
        if(x+25<FRAME_WIDTH)
        line(frame,cv::Point(x,y),cv::Point(x+25,y),COLOR_TARGET,2);
        else line(frame,cv::Point(x,y),cv::Point(FRAME_WIDTH,y),COLOR_TARGET,2);

        putText(frame,intToString(x)+","+intToString(y),cv::Point(x,y+30),1,1,cv::Scalar(255,0,0),2);

    }

    // ---------------------------- COLOR TREATEMENT -------------------------------
    /*
     * Transform the image into a two colored image, one color for the color we want to track, another color for the others colors
     * From this image, we get two datas : the number of pixel detected, and the center of gravity of these pixel
     */
    CvPoint binarisation(cv::Mat & image, int *nbPixels){
        int x, y;
        //CvScalar pixel;
        cv::Mat hsv, binary;
        int sommeX = 0, sommeY = 0;
        *nbPixels = 0;

        // Create the mask &initialize it to white (no color detected)
        binary = cvCreateImage(image.size(), IPL_DEPTH_8U, 1);
        // Create the hsv image
        hsv = image.clone();
        //Conversion from BGR to HSV
        cvtColor(image,hsv,CV_BGR2HSV);
        // We create the mask
        inRange(hsv,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),binary);
   
        #ifdef DEBUG
        std::cout << "binary width " << binary.rows << std::endl;
        std::cout << "binary height " << binary.cols << std::endl;
        #endif

 //SEGFAULT juste après??
        // Show the result of the mask image
        imshow("Flux binarisée", binary);   
        
        #ifdef DEBUG
        std::cout << "DEBUG5.3 " << std::endl;
        imshow("hsv", hsv);
        #endif
    
        //pour récupérer en sortie le résultat des opérations car image est un parametre resultat
        image = binary.clone();

        // If there is no pixel, we return a center outside the image, else we return the center of gravity
        if(*nbPixels > 0)
            return cvPoint((int)(sommeX / (*nbPixels)), (int)(sommeY / (*nbPixels)));
        else
            return cvPoint(-1, -1);
    }

    /*
     * Recupération de la couleur d'un pixel par clique de la souris 
     */
    void getObjectColor( int event, int x, int y, int flags, void *param = NULL) {
        // Vars
        CvScalar pixel;
        IplImage *hsv;

        if(event == CV_EVENT_LBUTTONUP) {

/*tests*/
/*
// Get the hsv image
 {  
            hsv = cvCloneImage(img);
            cvCvtColor(img, hsv, CV_BGR2HSV);
            nbTotPix = 0; //nombre total de pixel de la région choisie

    Recup x et y du pixel: XPixelMin et YPixelMin au clique

    au relachement XPixelMax et YPixelMax
    //sommes des valeurs HSV des pixels pour faire une moyenne
    int hSum = 0, sSum = 0, vSum = 0;

    for (int i = XPixelMin; i < XPixelMax; ++i)
    {
        for (int i = YPixelMin; i < YPixelMax; ++i)
        {
            // Get the selected pixel
            pixel = cvGet2D(hsv, y, x);
            // Change the value of the tracked color with the color of the selected pixel
            hSum = hSum+(int)pixel.val[0];
            sSum = sSum+(int)pixel.val[1];
            vSum = vSum+(int)pixel.val[2];
        }
    }
    nbTotPix=(YPixelMax-YPixelMin*XPixelMax-XPixelMin)
            // Change the value of the tracked color with the color of the selected pixel area
            h = hSum/nbTotPix;
            s = sSum/nbTotPix;
            v = vSum/nbTotPix;
}

// Reglage des niveaux
            H_MIN = h - TOLERANCE;
            S_MIN = s - TOLERANCE;
            V_MIN = v - TOLERANCE_V;
            H_MAX = h + TOLERANCE;
            S_MAX = s + TOLERANCE;
            V_MAX = v + TOLERANCE_V;

            // Protection pour ne pas sortir des valeurs limites
            H_MIN = ((H_MIN < 0)?0:H_MIN);
            S_MIN = ((S_MIN < 0)?0:S_MIN);
            V_MIN = ((V_MIN < 0)?0:V_MIN);
            H_MAX = ((H_MAX > 255)?0:H_MAX);
            S_MAX = ((S_MAX > 255)?0:S_MAX);
            V_MAX = ((V_MAX > 255)?0:V_MAX);
        
            // Release the memory of the hsv image
                cvReleaseImage(&hsv);
*/

//fonction fonctionnelle

            // Get the hsv image
            hsv = cvCloneImage(img);
            cvCvtColor(img, hsv, CV_BGR2HSV);
     
            // Get the selected pixel
            pixel = cvGet2D(hsv, y, x);
   
            // Change the value of the tracked color with the color of the selected pixel
            h = (int)pixel.val[0];
            s = (int)pixel.val[1];
            v = (int)pixel.val[2];

            // Reglage des niveaux
            H_MIN = h - TOLERANCE;
            S_MIN = s - TOLERANCE;
            V_MIN = v - TOLERANCE_V;
            H_MAX = h + TOLERANCE;
            S_MAX = s + TOLERANCE;
            V_MAX = v + TOLERANCE_V;

            // Protection pour ne pas sortir des valeurs limites
            H_MIN = ((H_MIN < 0)?0:H_MIN);
            S_MIN = ((S_MIN < 0)?0:S_MIN);
            V_MIN = ((V_MIN < 0)?0:V_MIN);
            H_MAX = ((H_MAX > 255)?0:H_MAX);
            S_MAX = ((S_MAX > 255)?0:S_MAX);
            V_MAX = ((V_MAX > 255)?0:V_MAX);
        
            // Release the memory of the hsv image
                cvReleaseImage(&hsv);
        }
    }
    
    /*
     * Traque l'objet voulu en fonction de sa teinte HSV et de la taille choisie (OBJECT_AREA) 
     * et marquage de celui-ci
     */
    void trackFilteredObject(int &x, int &y, cv::Mat threshold, cv::Mat &cameraFeed){

        cv::Mat temp;
        threshold.copyTo(temp);
        //these two vectors needed for output of findContours
        std::vector<std::vector <cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        std::vector<int> myints;
        //find contours of filtered image using openCV findContours function
        findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
        //use moments method to find our filtered object
        double refArea = 0;
        bool objectFound = false;
        if (hierarchy.size() > 0) {
            int numObjects = hierarchy.size();
            //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
            if(numObjects<MAX_NUM_OBJECTS){
                for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                    cv::Moments moment = moments((cv::Mat)contours[index]);
                    double area = moment.m00;

                    //if the area is less than MIN_OBJECT_AREA then it is probably just noise
                    //if the area is the same as the 3/2 of the image size, probably just a bad filter
                    //we only want the object with the largest area so we safe a reference area each
                    //iteration and compare it to the area in the next iteration.
                    if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                        x = moment.m10/area;
                        y = moment.m01/area;
                        objectFound = true;
                        refArea = area;
                    }else objectFound = false;

                }
                //let user know you found an object
                if(objectFound ==true){
                    putText(cameraFeed,"Tracking Object",cv::Point(0,50),2,1,cv::Scalar(255,0,0),2);
                    //draw object location on screen
                    drawObject(x,y,cameraFeed);}

            }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",cv::Point(0,50),1,2,cv::Scalar(0,0,255),2);
        }
    }




/* ------------------------- FONCTION MAIN ---------------------------*/

int main( int argc, char **argv ) //argv l'adresse IP du robotino sur lequel va tourner le programme
{
    char c; //lecture d'une touche clavier pour interrompre le programme
    imgRequested = false;
    imgUsed = false;
    int nbPixels;
    cv::Mat frame,mask,binary;
    int x,y;

    // si pas d'argument, le programme s'exécute à l'adresse 127.0.0.1 donc sur lui même
    // utile pour lancer le programme depuis le robotino
    std::string hostname = "127.0.0.1";
    if( argc > 1 ){ hostname = argv[1]; }

    img = cvCreateImage(cvSize(320,240),IPL_DEPTH_8U, 3);
    rbqt::lleague::init(hostname);

    // On converti le type IplImage en Mat pour pouvoir travailler en c++. De plus, IplImage est osbolete
    cv::Mat imgMat=cv::Mat(img,true); //true if you wish an independent copy else it will change myIplImage data 

    //create slider bars for HSV filtering
    createTrackbars();

    //On affiche le flux sur lequel cliquer pour récupérer la couleur
    cvNamedWindow("Flux caméra type Mat + Tracking", CV_WINDOW_AUTOSIZE);
    //A chaque clique la focntion getObjectColor est appelée
    cv::setMouseCallback("Flux caméra type Mat + Tracking", getObjectColor, NULL);

    do{
        //Gestion de l'utilisation du flux caméra
        //std::cout << "MAIN : Wait for imgMat not requested : " << ((imgUsed)?" Requested":" Not Requested") << std::endl;
        while(imgRequested);
        //std::cout << "MAIN : END WAIT " << std::endl;
        imgRequested = true;

        //std::cout << "MAIN : Wait for img not used : " << ((imgUsed)?" Used":" Not Used") << std::endl;
        while(imgUsed);
        //std::cout << "MAIN : END WAIT " << std::endl;
        imgUsed = true;
        imgRequested = false;

        // On converti IplImage en Matà chaque passage dans la boucle pour avoir un flux continu
        imgMat=cv::Mat(img,true); //true if you wish an independent copy else it will change myIplImage data 
   
        #ifdef DEBUG       
        printf("L'image fait %dx%d pixels et possède %d canaux (couleurs)\n",img->width,img->height,img->nChannels); 
        // Affichage de l'image venant de la caméra
        imshow("Flux caméra type Mat", imgMat);
        cvShowImage("Flux caméra ipl", img);
        #endif

        //copie de l'image récupérée permettant d'en faire ce que l'on veut
        frame = imgMat.clone();
        //Convertion de l'image en RGB en BGR
        cvtColor(frame, frame, CV_RGB2BGR);
        imgMat = frame.clone(); //pour avoir l'image RGB la caméra
        medianfilter(frame); //pour atténuer le bruit
        binarisation(frame,&nbPixels);
        imgUsed = false;

        #ifdef DEBUG
        std::cout << "DEBUG : Sortie binarisation " << std::endl;
        #endif

        //on a mtn frame qui est un flux binarisé
        binary = frame.clone();
        // operation morphologique sur l'image binaire
        morphOps(binary);
        
        trackFilteredObject(x,y,binary,imgMat);
        imshow("Flux caméra type Mat + Tracking", imgMat);
       
        // libération de l'image
        cvReleaseImage(&img);
        // Pour mettre à jour le trackbar ?
        cv::createTrackbar("H_MIN", trackbarWindowName, &H_MIN, 256, on_trackbar);
        cv::createTrackbar("H_MAX", trackbarWindowName, &H_MAX, 256, on_trackbar);
        cv::createTrackbar("S_MIN", trackbarWindowName, &S_MIN, 256, on_trackbar);
        cv::createTrackbar("S_MAX", trackbarWindowName, &S_MAX, 256, on_trackbar);
        cv::createTrackbar("V_MIN", trackbarWindowName, &V_MIN, 256, on_trackbar);
        cv::createTrackbar("V_MAX", trackbarWindowName, &V_MAX, 256, on_trackbar);
        // Appuyez sur une touche pour sortir
        c = cvWaitKey(150);
    }while(c != 'q');
//ATTENTION LIBERATION ICI ??
    cvReleaseImage(&img);

    return 0;
}