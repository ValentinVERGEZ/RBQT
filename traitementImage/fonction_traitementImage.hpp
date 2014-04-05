#ifndef _FONCTION_TRAITEMENTIMAGE_HEADER_
#define _FONCTION_TRAITEMENTIMAGE_HEADER_

/* Includes */
    //StdLib
    #include <iostream>
    #include <stdio.h> 
    #include <sstream>
    #include <string>
    #include <math.h>
    #include <vector>

    // Perso
    #ifdef USE_ROBOTINO
        #include "robotino.hpp"
	#endif // USE_ROBOTINO

	// OpenCV
	/* Les deux bibliothèques nécessaires d'opencv :
		- cv.h contient les structures et fonctions de manipulation d'images
		- highgui.h contient les fonctions d'affichage des images
	*/
	#include <cv.h>
	#include <highgui.hpp>

    #include <opencv2/core/core.hpp>
    #include <opencv2/imgproc/imgproc.hpp>

/* Prototypes */
// ------------------------------- UTILS ---------------------------- 
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param t [description]
	 * @param d [description]
	 */
    void on_trackbar( int, void* );

    /**
     * @brief [brief description]
     * @details [long description]
     */
    void createTrackbars();

    /**
     * @brief Convert int to string
     * 
     * @param number Number to be converted
     * @return Number converted into string format
     */
    std::string intToString(int number);


// ------------------------------- FILTRAGE ---------------------------- 
   
    //sort the window using insertion sort
    //insertion sort is best for this sorting
    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param window [description]
     */
    void insertionSort(int window[]);

    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param imgToFilter [description]
     */
    void medianfilter(cv::Mat imgToFilter);


// ---------------------------- opération de traitement d'image -------------------------------

    /* effectue le traitement de l'image binaire pour obtenir un objet plus fidèle à l'objet réel */
    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param mask [description]
     */
    void morphOps(cv::Mat &mask);

    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param x [description]
     * @param y [description]
     * @param frame [description]
     */
    void drawObject(int x, int y,cv::Mat &frame);

    // ---------------------------- COLOR TREATEMENT -------------------------------
    /*
     * Transform the image into a two colored image, one color for the color we want to track, another color for the others colors
     * From this image, we get two datas : the number of pixel detected, and the center of gravity of these pixel
     */
    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param image [description]
     * @param nbPixels [description]
     * 
     * @return [description]
     */
    CvPoint binarisation(cv::Mat & image, int *nbPixels);

    /*
     * Recupération de la couleur d'un pixel par clique de la souris 
     */
    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param  [description]
     * @return [description]
     */
    void getObjectColor(int event, int x, int y, int flags, void *param = NULL);
    
    /*
     * Traque l'objet voulu en fonction de sa teinte HSV et de la taille choisie (OBJECT_AREA) 
     * et marquage de celui-ci
     */
    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param x [description]
     * @param y [description]
     * @param threshold [description]
     * @param cameraFeed [description]
     */
    void trackFilteredObject(int &x, int &y, cv::Mat threshold, cv::Mat &cameraFeed);




#endif // _FONCTION_TRAITEMENTIMAGE_HEADER_