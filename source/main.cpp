/* 
    File: main.cpp
*/
#include "edge_detection.h"

int main(void) {
	/* Allocate memory to hold input/output images. */
	int **input_image = new int*[IMAGE_HEIGHT];
	int **output_image = new int*[IMAGE_HEIGHT - 2];
	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		input_image[i] = new int[IMAGE_WIDTH];
	}
	for (int i = 0; i < IMAGE_HEIGHT - 2; i++) {
		output_image[i] = new int[IMAGE_WIDTH - 2];
	}
	
	/* Iterate through each image. */
	for (Image image_pair : IMAGES) {
		/* Unpack image parameters. */
		std::string image_label = image_pair.first;
		const unsigned char *image = image_pair.second;
		
		/* Read flat 1D image array to 2D array. */
		for (int i = 0; i < IMAGE_HEIGHT; i++) {
			for (int j = 0; j < IMAGE_WIDTH; j++) {
				input_image[i][j] = static_cast<int>(image[i * IMAGE_HEIGHT + j]);
			}
		}
		
		/* Detect image's edges using the Sobel operator. */
		for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
			for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
				int V = sobel(true, i, j, input_image);
				int H = sobel(false, i, j, input_image);
				output_image[i - 1][j - 1] = static_cast<int>(round(sqrt(pow(V, 2) + pow(H, 2))));
			}
		}

		/* Generate PGM file for Sobel output. */
		write_pgm(image_label + "_sobel", output_image);

		/* Detect image's edges using the Roberts cross. */
		for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
			for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
				int V = roberts(true, i, j, input_image);
				int H = roberts(false, i, j, input_image);
				output_image[i - 1][j - 1] = static_cast<int>(round(sqrt(pow(V, 2) + pow(H, 2))));
			}
		}

		/* Generate PGM file for Roberts output. */
		write_pgm(image_label + "_roberts", output_image);
	}

    /* Clean up allocated memory. */
    for (int i = 0; i < IMAGE_HEIGHT; i++) {
		delete[] input_image[i];
	}
	for (int i = 0; i < IMAGE_HEIGHT - 2; i++) {
		delete[] output_image[i];
	}
	delete[] input_image;
	delete[] output_image;

    return 0;
}

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
