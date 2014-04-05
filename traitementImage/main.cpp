/** 
 * Auteur MARTIN Nathan pour Open German Robocup en 2014 (martin.nathan@polytech-lille.net) 
 *  but de l'algo: Traiter le flux caméra du robotino et faire du traitement d'image:
 *  Reconnaissance d'objets et récupération du barycentre 
 *  
 */ 

/* INCLUDES */
#include "main.hpp"

/* VARIABLES GLOBALES */
   #ifdef USE_ROBOTINO
        // Image camera partagée entre plusieurs fichiers
        IplImage *img;
        //protection de la ressource image. Exclusion mutuelle afin d'éviter que
        //l'image soit monopolisée par le même utilisateur
        bool imgUsed; 
        bool imgRequested;
    #endif // USE_ROBOTINO

/* ------------------------- FONCTION MAIN ---------------------------*/
int main( int argc, char **argv ) //argv l'adresse IP du robotino sur lequel va tourner le programme
{
/* Environment */
    // Lecture touche clavier pour interrompre le programme
    char c;
    // Utiles à al recherche d'objet
    int nbPixels;
    int x,y;
    // Images
    cv::Mat frame,imgResult;

    // Création de l'image à traiter dans les deux cas :
    //  - Cas de l'image en provenance du robotino
    //  - Cas de l'image de tracking artificielle
    #ifdef USE_ROBOTINO
        // Allocation mémoire de img
        img = cvCreateImage(cvSize(320,240),IPL_DEPTH_8U, 3);

        // Sans arguments, le programme se connecte sur 127.0.0.1, soit sur lui même
        // ( Utile pour lancer le programme depuis le robotino)
        std::string hostname = "127.0.0.1";
        // Avec argument, le programme se connecte à l'IP fournie en argument
        if( argc > 1 ){ hostname = argv[1]; }

        // Initialement la ressource image est libre
        imgRequested = false;
        imgUsed = false;
        
        // Initialisation de la connexion au robotino et demande du flux camera
        rbqt::lleague::init(hostname);

        // On convertit le type IplImage en Mat pour pouvoir travailler en C++. De plus, IplImage est osbolete
        cv::Mat imgMat = cv::Mat(img,true); // true : fait une copie de img plutôt que de passer par des pointeurs
    #else
        // Création d'une image vierge
        cv::Mat imgMat= cv::imread("./imgOrangeObject.jpg");
    #endif // USE_ROBOTINO

/* Algo */
    // Créer des sliders pour le seuillage HSV
    createTrackbars();

    // Création de la fenêtre principale sur sur laquelle cliquer pour récupérer la couleur à tracker
    cvNamedWindow("Flux Video + Tracking", CV_WINDOW_AUTOSIZE);

    // Association d'une fonction de callBack aux events de la souris sur la fenetre principale
    // cv::setMouseCallback("Flux Video + Tracking", getObjectColor, &imgMat);

    // Boucle (touche 'q' pour quitter)
    do{
        // Mise à jour de l'image à traiter dans les deux cas :
        //  - Cas de l'image en provenance du robotino
        //  - Cas de l'image de tracking artificielle
        #ifdef USE_ROBOTINO
            // Protection de la ressource img (partagée entre plusieurs procesus)
            #ifdef DEBUG 
                // Affiche si l'image est déjà demandée ailleurs
                std::cout << "MAIN : Wait for imgMat not requested : " << ((imgUsed)?" Requested":" Not Requested") << std::endl;
            #endif // DEBUG
            // Attendre que l'image ne soit plus demandée par un autre processus
            while(imgRequested);
            #ifdef DEBUG 
                // Signale la fin de l'attente
                std::cout << "MAIN : END WAIT " << std::endl;
            #endif // DEBUG
            // Reclamation de la ressource
            imgRequested = true;

            #ifdef DEBUG 
                // Affiche si l'image est déjà utilisée ailleurs
                std::cout << "MAIN : Wait for img not used : " << ((imgUsed)?" Used":" Not Used") << std::endl;
            #endif // DEBUG
            // Attendre que l'image ne soit plus utilisée par un autre processus
            while(imgUsed);
            #ifdef DEBUG 
                // Signale la fin de l'attente
                std::cout << "MAIN : END WAIT " << std::endl;
            #endif // DEBUG
            // Signale l'utilisation de l'image et la fin de la requête d'utilisation
            imgUsed = true;
            imgRequested = false;

            // On convertit le type IplImage en Mat pour pouvoir travailler en C++. De plus, IplImage est osbolete
            imgMat=cv::Mat(img,true); // true : fait une copie de img plutôt que de passer par des pointeurs 
        #else
            // Mise à jours de notre image de tracking artificielle 
            // imgMat=cv::Mat();
        #endif // USE_ROBOTINO
   
        // Debug sur l'image de base
        #ifdef DEBUG       
            // Informations sur l'image
            printf("L'image fait %dx%d pixels et possède %d canaux (couleurs)\n",imgMat.size().width,imgMat.size().height,imgMat.channels()); 
            
            // Affichage de l'image venant de la caméra
            imshow("Flux caméra (img Mat)", imgMat);
            #ifdef USE_ROBOTINO
                cvShowImage("Flux caméra (img Ipl)", img);
            #endif // USE_ROBOTINO
        #endif  // DEBUG


        // Convertion de l'image en RGB en BGR
        cvtColor(imgMat, imgMat, CV_RGB2BGR);

        // Copie de l'image récupérée permettant d'en faire ce que l'on veut
        frame = imgMat.clone();

        // Application d'un filtre median
        medianfilter(frame); //pour atténuer le bruit
        // Debug sur l'image filtrée
        #ifdef DEBUG       
            // Affichage de l'image filtrée
            imshow("Flux après filtrage", frame);
        #endif  // DEBUG

        // Seuillage HSV de l'image (binarisation)
        binarisation(frame,&nbPixels);
        // Debug sur l'image seuillée (binarisée)
        #ifdef DEBUG       
            // Affichage de l'image seuillée
            imshow("Flux après seuillage", frame);
        #endif  // DEBUG

        #ifdef USE_ROBOTINO
            // Libération de la ressource image
            imgUsed = false;
        #endif // USE_ROBOTINO

        #ifdef DEBUG
            std::cout << "DEBUG : Sortie binarisation " << std::endl;
        #endif

        // Operation morphologique sur l'image binaire (ouvertures/fermetures)
        morphOps(frame);
        // Debug sur l'image traitée
        #ifdef DEBUG       
            // Affichage de l'image traitée
            imshow("Flux après opérations morphologiques", frame);
        #endif  // DEBUG
        
        // Tracking d'un objet à partir d'une image seuillée (binarisée)
            // ImgResult est une copie du flux video à laquelle on ajoute le résultat du tracking
            imgResult = imgMat.clone();
        trackFilteredObject(x,y,frame,imgResult);
        
        // Affichage du flux video et du résultat du tracking
        imshow("Flux Video + Tracking", imgResult);       

        // Mise à jour des trackBars
        cv::setTrackbarPos("H_MIN", trackbarWindowName, H_MIN);
        cv::setTrackbarPos("H_MAX", trackbarWindowName, H_MAX);
        cv::setTrackbarPos("S_MIN", trackbarWindowName, S_MIN);
        cv::setTrackbarPos("S_MAX", trackbarWindowName, S_MAX);
        cv::setTrackbarPos("V_MIN", trackbarWindowName, V_MIN);
        cv::setTrackbarPos("V_MAX", trackbarWindowName, V_MAX);

        // Attends 150ms l'appui sur une touche
        c = cvWaitKey(150);

    }while(c != 'q');   // Touche 'q' pour quitter

    // Libération de la mémoire alouées aux images Ipl
    #ifdef USE_ROBOTINO
        cvReleaseImage(img);
    #endif // USE_ROBOTINO

    return 0;
}