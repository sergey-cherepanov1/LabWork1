/* Sergey Cherepanov st129987@student.spbu.ru
   LabWork1
*/

#include "bmp.h"
#include "gaussian_blur.h"

int main()
{
    std::vector<uint8_t> image_data;
    int width, height;

    if (!load_bmp("input.bmp", image_data, width, height))
    {
        std::cout << "Error loading image!" << std::endl;
        return -1;
    }

    std::vector<uint8_t> image_data1 = image_data;
    int width1 = width, height1 = height;

    rotate90(image_data, width, height);
    if (!save_bmp("90.bmp", image_data, width, height))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "90-degree rotated image saved as '90.bmp'!" << std::endl;

    int kernel_size;
    double sigma;

    std::cout << "Enter kernel size for Gaussian blur (odd number: 3, 5, 7...): ";
    std::cin >> kernel_size;
    std::cout << "Enter sigma for Gaussian blur (e.g., 3.0): ";
    std::cin >> sigma;

    gaussian_filter(image_data, width, height, kernel_size, sigma);
    if (!save_bmp("90blurred.bmp", image_data, width, height))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "Blurred image saved as 'blurred90.bmp'!" << std::endl;

    rotate270(image_data1, width1, height1);
    if (!save_bmp("270.bmp", image_data1, width1, height1))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "270-degree rotated image saved as '270.bmp'!" << std::endl;

    gaussian_filter(image_data1, width1, height1, kernel_size, sigma);
    if (!save_bmp("270blurred.bmp", image_data1, width1, height1))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "Blurred 270-degree rotated image saved as '270blurred.bmp'!" << std::endl;

    return 0;
}
