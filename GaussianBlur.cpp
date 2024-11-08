#include <vector>
#include <cmath>
#include <iostream>

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

    return kernel;
}

void gaussianFilter(std::vector<uint8_t>& imageData, int width, int height, int kernelSize, double sigma)
{
    std::vector<std::vector<double>> kernel = kernelMatrix(kernelSize, sigma);
    int padding = (4 - (width * 3) % 4) % 4;

    std::vector<uint8_t> filteredData(imageData);

    int center = kernelSize / 2;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            double newRed = 0.0, newGreen = 0.0, newBlue = 0.0;

            for (int ky = -center; ky <= center; ky++)
            {
                for (int kx = -center; kx <= center; kx++)
                {

                    int pixelX = x + kx;
                    int pixelY = y + ky;

                    if (pixelX < 0) pixelX = 0;
                    if (pixelY < 0) pixelY = 0;
                    if (pixelX >= width) pixelX = width - 1;
                    if (pixelY >= height) pixelY = height - 1;

                    int pixelIndex = (pixelY * (width * 3 + padding) + pixelX * 3);
                    double weight = kernel[ky + center][kx + center];

                    newBlue += imageData[pixelIndex] * weight;
                    newGreen += imageData[pixelIndex + 1] * weight;
                    newRed += imageData[pixelIndex + 2] * weight;
                }
            }


            int newPixelIndex = (y * (width * 3 + padding) + x * 3);
            filteredData[newPixelIndex] = (uint8_t)(newBlue);
            filteredData[newPixelIndex + 1] = (uint8_t)(newGreen);
            filteredData[newPixelIndex + 2] = (uint8_t)(newRed);
        }
    }

    imageData = std::move(filteredData);
}
