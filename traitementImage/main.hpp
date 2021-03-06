#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_

/* Includes */
    //StdLib
    #include <iostream>

    // Perso
    #ifdef USE_ROBOTINO
        #include "robotino.hpp"
	#endif // USE_ROBOTINO
    #include "fonction_traitementImage.hpp"    


/* Variables globales */
    #ifdef USE_ROBOTINO
        // Image camera partagée entre plusieurs fichiers
        extern IplImage *img;
        extern bool imgUsed;
        extern bool imgRequested;
    #endif // USE_ROBOTINO
    extern cv::Mat imgBGR;
#endif // _MAIN_HEADER_