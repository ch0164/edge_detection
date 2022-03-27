/*
	File: histogram_equalization.cpp
*/
#include "histogram_equalization.h"

int main(void) {
	/* Allocate memory to hold input/output images. */
	int **input_image = new int*[IMAGE_HEIGHT];
	int **output_image = new int*[IMAGE_HEIGHT];
	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		input_image[i] = new int[IMAGE_WIDTH];
		output_image[i] = new int[IMAGE_WIDTH];
	}

	/* Iterate through each image. */
	for (Image image_pair : IMAGES) {
		std::string label = image_pair.first;
		const unsigned char *image = image_pair.second;

		/* Read flat 1D image array to 2D array. 
		Also, find min/max intensities in the image for later.*/
		int i_min = 255, i_max = 0;
		for (int i = 0; i < IMAGE_HEIGHT; i++) {
			for (int j = 0; j < IMAGE_WIDTH; j++) {
				input_image[i][j] = static_cast<int>(
					image[i * IMAGE_HEIGHT + j]);
				i_min = input_image[i][j] < i_min ?
					input_image[i][j] : i_min;
				i_max = input_image[i][j] > i_max ?
					input_image[i][j] : i_max;
			}
		}

		/* Michelson contrast (or visibility) coefficient:
		https://en.wikipedia.org/wiki/Contrast_(vision) */
		double michelson_coefficient = static_cast<double>(
				(i_max - i_min) / (i_max + i_min));

		/* Run experiments with thresholds from 50-250, incremented by 50. */
		for (int threshold = 50; threshold <= 250; threshold += 50) {
			/* Binarize image. */
			for (int i = 0; i < IMAGE_HEIGHT; i++) {
				for (int j = 0; j < IMAGE_WIDTH; j++) {
					if (input_image[i][j] < threshold) {
						output_image[i][j] = 0;
					}
					else {
						output_image[i][j] = 255;
					}
				}
			}
			write_pgm(label,
				"binarization_" + std::to_string(threshold), output_image);

			/* Reject pixels under threshold,
			but keep pixels which meet threshold. */
			for (int i = 0; i < IMAGE_HEIGHT; i++) {
				for (int j = 0; j < IMAGE_WIDTH; j++) {
					if (input_image[i][j] < threshold) {
						output_image[i][j] = 0;
					}
					else {
						output_image[i][j] = input_image[i][j];
					}
				}
			}
			write_pgm(label,
				"reject_" + std::to_string(threshold), output_image);
			
			/* Take pixels above the threshold in previous thresholding,
			and rescale them to range from 1 to 255, keeping those below
			the threshold at minimum intensity. */
			for (int i = 0; i < IMAGE_HEIGHT; i++) {
				for (int j = 0; j < IMAGE_WIDTH; j++) {
					if (output_image[i][j] < 0 || input_image[i][j] < 0)
						std::cout << "Error, negative number found";
					if (output_image[i][j] != 0) {
						/* Scale down image according to threshold. */
						double s = (output_image[i][j] - threshold) /
							(255.0 - threshold) * (255.0 - 1.0);
						int rescaled_pixel = static_cast<int>(round(s));
						output_image[i][j] = std::min(255, std::max(rescaled_pixel, 1));
					}
				}
			}
			write_pgm(label,
				"reject_rescale_" + std::to_string(threshold), output_image);


			/* "Accept" pixels under or at threshold and keep them the same,
			but change those above the threshold to maximum intensity. */
			for (int i = 0; i < IMAGE_HEIGHT; i++) {
				for (int j = 0; j < IMAGE_WIDTH; j++) {
					if (input_image[i][j] <= threshold) {
						output_image[i][j] = input_image[i][j];
					}
					else {
						output_image[i][j] = 255;
					}
				}
			}
			write_pgm(label, "accept_" + std::to_string(threshold), output_image);

			/* Take pixels below the threshold in previous thresholding,
			and rescale them to range from 0 to 254, but keep those above
			the threshold at maximum intensity. */
			for (int i = 0; i < IMAGE_HEIGHT; i++) {
				for (int j = 0; j < IMAGE_WIDTH; j++) {
					if (output_image[i][j] != 255) {
						double s = (254.0 / threshold) * output_image[i][j];
						int rescaled_pixel = static_cast<int>(round(s));
						output_image[i][j] = std::min(254, std::max(rescaled_pixel, 0));
					}
				}
			}
			write_pgm(label, "accept_rescale_" + std::to_string(threshold), output_image);
		}

		/* Build physical image histogram. */
		std::map<int, int> hist = create_histogram(image);

		/* Then, build cumulative image histogram. */
		std::map<int, double> cumulative_hist = 
			create_cumulative_histogram(hist);

		/* Perform histogram equalization on the image. */
		for (int i = 0; i < IMAGE_HEIGHT; i++) {
			for (int j = 0; j < IMAGE_WIDTH; j++) {
				int pixel_intensity = static_cast<int>(
					image[i * IMAGE_HEIGHT + j]);
				double pixel_cumulative_frequency = 
					cumulative_hist.at(pixel_intensity);
				output_image[i][j] = static_cast<int>(
					round(pixel_cumulative_frequency * 255.0));
			}
		}
		write_pgm(label, "equalized_histogram", output_image);

		/* Create histograms of equalized image for output.*/
	// 	std::map<int, int> equalized_hist = create_histogram(output_image);
	// 	std::map<int, double> equalized_cumulative_hist =
	// 		create_cumulative_histogram(equalized_hist);

	// 	/* Output all histograms as CSV files for visualization. */
	// 	write_histograms(label, "original", hist, cumulative_hist);
	// 	write_histograms(label, "equalized", 
	// 		equalized_hist, equalized_cumulative_hist);
	}


	/* Clean up allocated memory. */
	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		delete[] input_image[i];
		delete[] output_image[i];
	}
	delete[] input_image;
	delete[] output_image;

	return 0;
}

void write_pgm(const std::string& label, const std::string& description, int **W) {
	std::ofstream pgm(OUTPUT_DIR + label + "/histogram/" + label + 
		"_" + description + ".pgm");

	if (!pgm) {
		std::cerr << "Error occurred opening " << label << std::endl;
		return;
	}

	/* Write header, dimensions, and maximum value to file. */
	pgm << "P2" << std::endl;
	pgm << IMAGE_WIDTH << " " << IMAGE_HEIGHT << std::endl;
	pgm << "255" << std::endl;

	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		for (int j = 0; j < IMAGE_WIDTH; j++) {
			pgm << W[i][j] << " ";
		}
		pgm << std::endl;
	}

	pgm.close();
}

std::map<int, int> create_histogram(const unsigned char *I) {
	std::map<int, int> hist;
	for (int i = 0; i < 256; i++) {
		int pixel_count = 0;
		for (int j = 0; j < PIXEL_COUNT; j++) {
			if (i == static_cast<int>(I[j])) {
				pixel_count++;
			}
		}
		hist.insert(std::pair<int, int>(i, pixel_count));
	}

	return hist;
}

std::map<int, int> create_histogram(int **I) {
	std::map<int, int> hist;
	for (int i = 0; i < 256; i++) {
		int pixel_count = 0;
		for (int j = 0; j < IMAGE_HEIGHT; j++) {
			for (int k = 0; k < IMAGE_WIDTH; k++) {
				if (i == I[j][k]) {
					pixel_count++;
				}
			}
		}
		hist.insert(std::pair<int, int>(i, pixel_count));
	}

	return hist;
}

std::map<int, double> create_cumulative_histogram(std::map<int, int> hist) {
	std::map<int, double> cumulative_hist;
	double cumulative_frequency = 0.0;
	for (int i = 0; i < 256; i++) {
		double pixel_count = static_cast<double>(hist.at(i));
		double pixel_frequency = pixel_count / static_cast<double>(PIXEL_COUNT);
		cumulative_frequency += pixel_frequency;
		cumulative_hist.insert(std::pair<int, double>(i, cumulative_frequency));
	}

	return cumulative_hist;
}

void write_histograms(const std::string& label, const std::string& description,
	std::map<int, int> hist, std::map<int, double> cumulative_hist) {
	std::ofstream csv;

	/* Write image histogram to CSV. */
	csv.open(OUTPUT_DIR + label + "/histogram/" + label + 
		"_" + description + ".csv");
	if (!csv) {
		std::cerr << "Error occurred opening histogram " << label << std::endl;
		return;
	}
	for (std::pair<int, int> pixel : hist) {
		int pixel_intensity = pixel.first;
		int pixel_count = pixel.second;
		csv << pixel_intensity << "," << pixel_count << std::endl;
	}
	csv.close();

	/* Write cumulative image histogram to CSV. */
	csv.open(OUTPUT_DIR + label + "/histogram/" + label + 
		"_cumulative_" + description + ".csv");
	for (std::pair<int, double> pixel : cumulative_hist) {
		int pixel_intensity = pixel.first;
		double cumulative_frequency = pixel.second;
		csv << pixel_intensity << "," << cumulative_frequency << std::endl;
	}
	csv.close();
}