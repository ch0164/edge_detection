/*
	File: main.cpp
*/
#include "edge_detection.h"

int main(void) {  // Start Total Timer
	Timer total_time("Total");

	/* Allocate memory to hold input/output images. */
	int **input_image = new int*[IMAGE_HEIGHT];
	int **blurred_image = new int*[IMAGE_HEIGHT];
	int **output_image = new int*[IMAGE_HEIGHT - 2];
	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		input_image[i] = new int[IMAGE_WIDTH];
		blurred_image[i] = new int[IMAGE_WIDTH];
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
				input_image[i][j] = static_cast<int>(
					image[i * IMAGE_HEIGHT + j]);
			}
		}

		{Timer sobel_time(image_label + "_sobel");

		/* Detect image's edges using the Sobel operator. */
		for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
			for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
				int V = convolve_order_3(SOBEL_V, i, j, input_image);
				int H = convolve_order_3(SOBEL_H, i, j, input_image);
				output_image[i - 1][j - 1] = static_cast<int>(
					round(sqrt(pow(V, 2) + pow(H, 2))));
			}
		}
		write_pgm(image_label, image_label + "_sobel", output_image);
		}  // End Sobel Timer

		{Timer roberts_time(image_label + "_roberts");

		/* Detect image's edges using the Roberts cross. */
		for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
			for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
				int V = convolve_order_2(ROBERTS_V, i, j, input_image);
				int H = convolve_order_2(ROBERTS_H, i, j, input_image);
				output_image[i - 1][j - 1] = static_cast<int>(
					round(sqrt(pow(V, 2) + pow(H, 2))));
			}
		}
		write_pgm(image_label, image_label + "_roberts", output_image);
		}  // End Roberts Timer

		{Timer mean_sobel_time(image_label + "_mean_sobel");
		/* Blur image with mean blur, then apply Sobel. */
		for (int i = 0; i < IMAGE_HEIGHT - 0; i++) {
			for (int j = 0; j < IMAGE_WIDTH - 0; j++) {
				if (i == 0 || i == IMAGE_HEIGHT - 1 ||  j == 0 || j == IMAGE_WIDTH - 1) {
					blurred_image[i][j] = 0;
				} else {
					blurred_image[i][j] = static_cast<int>(
						round(convolve_order_3(MEAN_BLUR, i, j, input_image) / 9));
				}
			}
		}
		for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
			for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
				int V = convolve_order_3(SOBEL_V, i, j, blurred_image);
				int H = convolve_order_3(SOBEL_H, i, j, blurred_image);
				output_image[i - 1][j - 1] = static_cast<int>(
					round(sqrt(pow(V, 2) + pow(H, 2))));
			}
		}
		write_pgm(image_label, image_label + "_mean_sobel", output_image);
		}  // End Mean Sobel Timer

		{Timer mean_roberts_time(image_label + "_mean_roberts");
		/* Blur image with mean blur, then apply Roberts. */
		for (int i = 0; i < IMAGE_HEIGHT - 0; i++) {
			for (int j = 0; j < IMAGE_WIDTH - 0; j++) {
				if (i == 0 || i == IMAGE_HEIGHT - 1 || j == 0 || j == IMAGE_WIDTH - 1) {
					blurred_image[i][j] = 0;
				} else {
					blurred_image[i][j] = static_cast<int>(
						round(convolve_order_3(MEAN_BLUR, i, j, input_image) / 9));
				}
			}
		}
		write_pgm(image_label, image_label + "_mean_blur", blurred_image);
		for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
			for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
				int V = convolve_order_2(ROBERTS_V, i, j, blurred_image);
				int H = convolve_order_2(ROBERTS_H, i, j, blurred_image);
				output_image[i - 1][j - 1] = static_cast<int>(
					round(sqrt(pow(V, 2) + pow(H, 2))));
			}
		}
		write_pgm(image_label, image_label + "_mean_roberts", output_image);
	}  // End Mean Roberts Timer

		{Timer gaussian_sobel_time(image_label + "_gaussian_sobel");
		/* Blur image with Gaussian blur, then apply Sobel. */
		for (int i = 0; i < IMAGE_HEIGHT - 0; i++) {
			for (int j = 0; j < IMAGE_WIDTH - 0; j++) {
				if (i == 0 || i == IMAGE_HEIGHT - 1 || j == 0 || j == IMAGE_WIDTH - 1) {
					blurred_image[i][j] = 0;
				} else {
					blurred_image[i][j] = static_cast<int>(
						round(convolve_order_3(GAUSSIAN_BLUR, i, j, input_image) / 16));
				}
			}
		}
		for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
			for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
				int V = convolve_order_3(SOBEL_V, i, j, blurred_image);
				int H = convolve_order_3(SOBEL_H, i, j, blurred_image);
				output_image[i - 1][j - 1] = static_cast<int>(
					round(sqrt(pow(V, 2) + pow(H, 2))));
			}
		}
		write_pgm(image_label, image_label + "_gaussian_sobel", output_image);
		}  // End Gaussian Sobel Timer

		{Timer mean_roberts_time(image_label + "_gaussian_roberts");
		/* Blur image with Gaussian blur, then apply Roberts cross. */
		for (int i = 0; i < IMAGE_HEIGHT - 0; i++) {
			for (int j = 0; j < IMAGE_WIDTH - 0; j++) {
				if (i == 0 || i == IMAGE_HEIGHT - 1 || j == 0 || j == IMAGE_WIDTH - 1) {
					blurred_image[i][j] = 0;
				} else {
					blurred_image[i][j] = static_cast<int>(
						round(convolve_order_3(GAUSSIAN_BLUR, i, j, input_image) / 16));
				}
			}
		}
		write_pgm(image_label, image_label + "_gaussian_blur", output_image);
		for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
			for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
				int V = convolve_order_2(ROBERTS_V, i, j, blurred_image);
				int H = convolve_order_2(ROBERTS_H, i, j, blurred_image);
				output_image[i - 1][j - 1] = static_cast<int>(
					round(sqrt(pow(V, 2) + pow(H, 2))));
			}
		}
		write_pgm(image_label, image_label + "_gaussian_roberts", blurred_image);
		}  // End Gaussian Roberts Timer
	}

	/* Clean up allocated memory. */
	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		delete[] input_image[i];
		delete[] blurred_image[i];
	}
	for (int i = 0; i < IMAGE_HEIGHT - 2; i++) {
		delete[] output_image[i];
	}
	delete[] input_image;
	delete[] blurred_image;
	delete[] output_image;

	return 0;
}  // End Total Timer

int convolve_order_2(const int mask[2][2], const int i, const int j, int **I) {
	return I[i][j] * mask[0][0]
		+ I[i][j + 1] * mask[0][1]
		+ I[i + 1][j] * mask[1][0]
		+ I[i + 1][j + 1] * mask[1][1];
}

int convolve_order_3(const int mask[3][3], const int i, const int j, int **I) {
	return I[i - 1][j - 1] * mask[0][0]
		+ I[i - 1][j] * mask[0][1]
		+ I[i - 1][j + 1] * mask[0][2]
		+ I[i][j - 1] * mask[1][0]
		+ I[i][j] * mask[1][1]
		+ I[i][j + 1] * mask[1][2]
		+ I[i + 1][j - 1] * mask[2][0]
		+ I[i + 1][j] * mask[2][1]
		+ I[i + 1][j + 1] * mask[2][2];
}

void write_pgm(const std::string& label, const std::string& mask, int **W) {
	std::ofstream pgm(OUTPUT_DIR + label + "/" + mask + ".pgm");

	if (!pgm) {
		std::cerr << "Error occurred opening " << label << std::endl;
		return;
	}

	/* Write header, dimensions, and maximum value to file. */
	pgm << "P2" << std::endl;
	pgm << IMAGE_WIDTH - 2 << " " << IMAGE_HEIGHT - 2 << std::endl;
	pgm << "255" << std::endl;

	for (int i = 0; i < IMAGE_HEIGHT - 2; i++) {
		for (int j = 0; j < IMAGE_WIDTH - 2; j++) {
			pgm << W[i][j] << " ";
		}
		pgm << std::endl;
	}
}
