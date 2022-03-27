/* 
    File: histogram_equalization.h
*/

/* C++ Includes */
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

/* Project Includes */
#include "convert/cameraman.h"
#include "convert/house.h"
#include "convert/lena.h"
#include "convert/mandril.h"
#include "convert/peppers.h"
#include "convert/pirate.h"

/* Output Directory */
static const std::string ROOT_DIR = "C:\\Users\\Christian\\Desktop\\School\\Research\\edge_detection\\";
//static const std::string ROOT_DIR = "C:\\Users\\youar\\CLionProjects\\edge_detection";
static const std::string OUTPUT_DIR = ROOT_DIR + "output\\";

/* Input Image Info */
typedef std::pair<std::string, const unsigned char *> Image;
static const std::vector<Image> IMAGES = {
    Image("cameraman", cameraman_image),
    Image("house", house_image),
    Image("lena", lena_image),
    Image("mandril", mandril_image),
    Image("peppers", peppers_image),
    Image("pirate", pirate_image)
};

/* Input Image Dimensions */
static const int IMAGE_WIDTH = 512;
static const int IMAGE_HEIGHT = 512;
static const int PIXEL_COUNT = IMAGE_WIDTH * IMAGE_HEIGHT;

/* Helper Functions */
void write_pgm(const std::string&, const std::string&, int **W);
std::map<int, int> create_histogram(const unsigned char *);
std::map<int, int> create_histogram(int **);
std::map<int, double> create_cumulative_histogram(std::map<int, int>);
void write_histograms(const std::string&, const std::string&,
	std::map<int, int> hist, std::map<int, double> cumulative_hist);
