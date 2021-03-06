/* 
    File: edge_detection.h
*/
#pragma once

/* C++ Includes */
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

/* Project Includes */
#include "convert/cameraman.h"
#include "convert/lena.h"
#include "convert/mandril.h"
#include "convert/pirate.h"

/* Output Directory */
static const std::string ROOT_DIR = "C:\\Users\\Christian\\Desktop\\School\\Research\\edge_detection\\";
static const std::string OUTPUT_DIR = ROOT_DIR + "output\\";

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
static const int SOBEL_V[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1 }};
static const int SOBEL_H[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

/* Roberts Cross Operators */
static const int ROBERTS_V[2][2] = {{1, 0}, {0, -1}};
static const int ROBERTS_H[2][2] = {{0, 1}, {-1, 0}};

/* Blur Operators */
static const int MEAN_BLUR[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
static const int GAUSSIAN_BLUR[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

/* Helper Functions */
int convolve_order_2(const int[2][2], const int, const int, int **);
int convolve_order_3(const int[3][3], const int, const int, int **);
void write_pgm(const std::string&, const std::string&, int **);

/* Execution Timer Class */
class Timer {
private:
    std::chrono::time_point<std::chrono::system_clock> start;
	std::string label;
public:
    Timer(const std::string& l) : 
		start(std::chrono::system_clock::now()), label(l) {}
    ~Timer() {
        std::chrono::duration<double> elapsed_seconds = 
			std::chrono::system_clock::now() - start;
        std::cout << label << " execution time: ";
		std::cout << elapsed_seconds.count() << " s" << std::endl;
    }
};
