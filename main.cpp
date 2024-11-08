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


    int kernel_size = 15;
    double sigma = 3.0;
    gaussian_filter(image_data, width, height, kernel_size, sigma);


    if (!save_bmp("output.bmp", image_data, width, height))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }

    return 0;
}
