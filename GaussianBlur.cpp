#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

double gaussianFunc(int x, int y, double sigma)
{
    return (1.0 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
}


std::vector<std::vector<double>> kernelMatrix(int size, double sigma)
{
    std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
    double sum = 0.0;

    int center = size / 2;

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            kernel[x][y] = gaussianFunc(x - center, center - y, sigma);
            sum += kernel[x][y];
        }
    }


    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            kernel[i][j] /= sum;
        }
    }
    for (auto row : kernel)
    {
        for (double value : row)
        {
            std::cout << std::fixed << std::setprecision(3) << value << " ";
        }
        std::cout << std::endl;
    }

    return kernel;
}
