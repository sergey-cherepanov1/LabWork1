#include "bmp.h"

int main()
{
    std::vector<uint8_t> imageData;
    int width, height;

    if (!loadBMP("input.bmp", imageData, width, height))
    {
        std::cout << "Error loading image!" << std::endl;
        return -1;
    }


    int kernelSize = 15;
    double sigma = 3.0;
    gaussianFilter(imageData, width, height, kernelSize, sigma);


    if (!saveBMP("output.bmp", imageData, width, height))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }

    return 0;
}
