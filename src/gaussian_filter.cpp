/* Sergey Cherepanov st129987@student.spbu.ru
   LabWork1
*/

#include "bmp.h"

/**
 * @brief Calculates the 2D Gaussian function value
 * @param x X-coordinate offset from center
 * @param y Y-coordinate offset from center
 * @param sigma Standard deviation of the Gaussian distribution
 * @return double The computed Gaussian weight value
 */
double BmpFile::gaussian_func(int x, int y, double sigma)
{
    return (1.0 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
}

/**
 * @brief Generates a Gaussian kernel matrix
 * @param size The size of the kernel (must be odd)
 * @param sigma Standard deviation for the Gaussian distribution
 * @return std::vector<std::vector<double>> The generated kernel matrix
 */
std::vector<std::vector<double>> BmpFile::kernel_matrix(int size, double sigma)
{
    std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
    double sum = 0.0;

    int center = size / 2;

    // Loop through each position in the kernel and apply the Gaussian function
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            kernel[x][y] = gaussian_func(x - center, center - y, sigma);
            sum += kernel[x][y];
        }
    }

    // Normalize the kernel so that the sum of all weights equals 1
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            kernel[i][j] /= sum;
        }
    }

    return kernel;
}

/**
 * @brief Applies a kernel to a single pixel
 * @param x X-coordinate of the target pixel
 * @param y Y-coordinate of the target pixel
 * @param kernel The convolution kernel to apply
 * @param center The center index of the kernel
 * @param new_red [out] Accumulator for the new red component
 * @param new_green [out] Accumulator for the new green component
 * @param new_blue [out] Accumulator for the new blue component
 */
void BmpFile::apply_kernel_to_pixel(int x, int y, const std::vector<std::vector<double>>& kernel, int center, double& new_red, double& new_green, double& new_blue)
{
    // Loop over the surrounding pixels in the kernel
    for (int ky = -center; ky <= center; ky++)
    {
        for (int kx = -center; kx <= center; kx++)
        {
            // Check boundaries for pixel coordinates
            int pixel_x = x + kx;
            int pixel_y = y + ky;

            if (pixel_x < 0) pixel_x = 0;
            if (pixel_y < 0) pixel_y = 0;
            if (pixel_x >= width) pixel_x = width - 1;
            if (pixel_y >= height) pixel_y = height - 1;

            // Calculate the pixel index in the image data
            int pixel_index = (pixel_y * (width * 3 + (4 - (width * 3) % 4) % 4) + pixel_x * 3);

            // Get the weight of the current kernel element
            double weight = kernel[ky + center][kx + center];

            // Apply the kernel to the pixel's RGB values
            new_blue += image_data[pixel_index] * weight;
            new_green += image_data[pixel_index + 1] * weight;
            new_red += image_data[pixel_index + 2] * weight;
        }
    }
}

/**
 * @brief Applies Gaussian blur to the entire image
 * @param kernel_size The size of the convolution kernel (must be odd)
 * @param sigma The standard deviation for the Gaussian blur
 */
void BmpFile::gaussian_filter(int kernel_size, double sigma)
{
    std::vector<std::vector<double>> kernel = kernel_matrix(kernel_size, sigma);
    int padding = (4 - (width * 3) % 4) % 4;
    std::vector<uint8_t> filtered_data(image_data);
    
    int center = kernel_size / 2;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double new_red = 0.0, new_green = 0.0, new_blue = 0.0;

            // Apply the kernel to the current pixel
            apply_kernel_to_pixel(x, y, kernel, center, new_red, new_green, new_blue);

            // Calculate the new pixel index in the filtered image data
            int new_pixel_index = (y * (width * 3 + padding) + x * 3);

            // Store the new RGB values in the filtered image data
            filtered_data[new_pixel_index] = (uint8_t)(new_blue);
            filtered_data[new_pixel_index + 1] = (uint8_t)(new_green);
            filtered_data[new_pixel_index + 2] = (uint8_t)(new_red);
        }
    }

    image_data = std::move(filtered_data);
}
