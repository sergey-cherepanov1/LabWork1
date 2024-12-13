/* Sergey Cherepanov st129987@student.spbu.ru
   LabWork1
*/

#include "bmp.h"

int main()
{
    // Create an object of BmpFile class to load the BMP image
    BmpFile bmp("input.bmp");
    BmpFile bmp1 = bmp;

    // Rotate the image 90 degrees clockwise
    bmp.rotate90();
    if (!bmp.save("90.bmp"))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "90-degree rotated image saved as '90.bmp'!" << std::endl;

    // Get kernel size and sigma for Gaussian blur
    int kernel_size;
    double sigma;

    std::cout << "Enter kernel size for Gaussian blur (odd number: 3, 5, 7...): ";
    std::cin >> kernel_size;
    std::cout << "Enter sigma for Gaussian blur (e.g., 3.0): ";
    std::cin >> sigma;

    // Apply the Gaussian blur filter to the rotated image
    bmp.gaussian_filter(kernel_size, sigma);
    if (!bmp.save("90blurred.bmp"))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "Blurred image saved as 'blurred90.bmp'!" << std::endl;

    // Rotate the image 270 degrees counter-clockwise
    bmp1.rotate270();
    if (!bmp1.save("270.bmp"))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "270-degree rotated image saved as '270.bmp'!" << std::endl;

    // Apply Gaussian blur to the 270-degree rotated image
    bmp1.gaussian_filter(kernel_size, sigma);
    if (!bmp1.save("270blurred.bmp"))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "Blurred 270-degree rotated image saved as '270blurred.bmp'!" << std::endl;

    return 0;
}
