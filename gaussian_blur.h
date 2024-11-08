#ifndef GAUSSIAN_BLUR_H
#define GAUSSIAN_BLUR_H

#include <vector>
#include <cmath>
#include <iostream>

double gaussian_func(int x, int y, double sigma);
std::vector<std::vector<double>> kernel_matrix(int size, double sigma);
void gaussian_filter(std::vector<uint8_t>& image_data, int width, int height, int kernel_size, double sigma);


#endif
