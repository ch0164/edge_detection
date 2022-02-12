/* 
    File: edge_detection.cpp
*/
#include "edge_detection.h"

int sobel(const bool vertical, const int i, const int j, int **I) {
	if (vertical) {
		return I[i - 1][j - 1] * SOBEL_V[0][0]
			 + I[i - 1][j] * SOBEL_V[0][1]
			 + I[i - 1][j + 1] * SOBEL_V[0][2]
			 + I[i][j - 1] * SOBEL_V[1][0]
			 + I[i][j] * SOBEL_V[1][1]
			 + I[i][j + 1] * SOBEL_V[1][2]
			 + I[i + 1][j - 1] * SOBEL_V[2][0]
			 + I[i + 1][j] * SOBEL_V[2][1]
			 + I[i + 1][j + 1] * SOBEL_V[2][2];
	}
	else {
		return I[i - 1][j - 1] * SOBEL_H[0][0]
			 + I[i - 1][j] * SOBEL_H[0][1]
			 + I[i - 1][j + 1] * SOBEL_H[0][2]
			 + I[i][j - 1] * SOBEL_H[1][0]
			 + I[i][j] * SOBEL_H[1][1]
			 + I[i][j + 1] * SOBEL_H[1][2]
			 + I[i + 1][j - 1] * SOBEL_H[2][0]
			 + I[i + 1][j] * SOBEL_H[2][1]
			 + I[i + 1][j + 1] * SOBEL_H[2][2];
	}
}

int roberts(const bool vertical, const int i, const int j, int **I) {
	if (vertical) {
		return I[i][j] * ROBERTS_V[0][0]
			 + I[i][j + 1] * ROBERTS_V[0][1]
			 + I[i + 1][j] * ROBERTS_V[1][0]
			 + I[i + 1][j + 1] * ROBERTS_V[1][1];
	}
	else {
		return I[i][j] * ROBERTS_H[0][0]
			 + I[i][j + 1] * ROBERTS_H[0][1]
			 + I[i + 1][j] * ROBERTS_H[1][0]
			 + I[i + 1][j + 1] * ROBERTS_H[1][1];
	}
}

void write_pgm(const std::string& label, int **W) {
	std::ofstream pgm(OUTPUT_DIR + label + ".pgm");
	
    if (!pgm) {
		std::cerr << "Error occurred opening " << label << std::endl;
		return;
	}

	pgm << "P2" << std::endl;  // Header
	pgm << IMAGE_WIDTH - 2 << " " << IMAGE_HEIGHT - 2 << std::endl;  // Dimensions
	pgm << "255" << std::endl;  // Maximum Value

	for (int i = 0; i < IMAGE_HEIGHT - 2; i++) {
		for (int j = 0; j < IMAGE_WIDTH - 2; j++) {
			pgm << W[i][j] << " ";
		}
		pgm << std::endl;
	}
}
