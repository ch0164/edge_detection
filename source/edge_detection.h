/* 
    File: edge_detection.h
*/

/* C Includes */

/* C++ Includes */
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

/* Project Includes */
#include "convert/cameraman.h"
#include "convert/lena.h"
#include "convert/mandril.h"
#include "convert/pirate.h"

/* Output Directory */
static const std::string OUTPUT_DIR = "../output/";

/* Input Image Info */
typedef std::pair<std::string, const unsigned char *> Image;
static const std::vector<Image> IMAGES = {
	Image("cameraman", cameraman_image),
	Image("lena", lena_image),
	Image("mandril", mandril_image),
	Image("pirate", pirate_image)
};

/* Input Image Dimensions */
static const int IMAGE_WIDTH = 512;
static const int IMAGE_HEIGHT = 512;
static const int PIXEL_COUNT = IMAGE_WIDTH * IMAGE_HEIGHT;

/* Sobel Operator */
static const int SOBEL_V[3][3] = {{-1, 0, 1},
								  {-2, 0, 2},
								  {-1, 0, 1 }};
static const int SOBEL_H[3][3] = {{-1, -2, -1},
								  {0, 0, 0},
								  {1, 2, 1}};

/* Roberts Cross Operators */
static const int ROBERTS_V[2][2] = {{1, 0},
									{0, -1}};
static const int ROBERTS_H[2][2] = {{0, 1},
									{-1, 0}};

/* Helper Functions */
int sobel(const bool, const int, const int, int **);
int roberts(const bool, const int, const int, int **);
void write_pgm(const std::string&, int **);
