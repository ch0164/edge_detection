/* 
    File: histogram_equalization.h
*/
#pragma once

/* Project Includes */
#include "edge_detection.h"

/* Helper Functions */
std::map<int, int> create_histogram(const unsigned char *);
std::map<int, int> create_histogram(int **);
std::map<int, double> create_cumulative_histogram(std::map<int, int>);
void write_histograms(const std::string&, const std::string&,
	std::map<int, int> hist, std::map<int, double> cumulative_hist);