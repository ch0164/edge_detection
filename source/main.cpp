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

    return 0;
}
