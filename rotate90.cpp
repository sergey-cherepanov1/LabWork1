#include "rotate90.h"

void rotate90(std::vector<uint8_t>& imageData, int& width, int& height) {
    std::vector<uint8_t> rotatedImageData(width * height);

    int rowSize = (width * 8 + 31) / 32 * 4;
    int rotatedRowSize = (height * 8 + 31) / 32 * 4;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            rotatedImageData[(j * height) + (height - i - 1)] = imageData[(i * width) + j];
        }
    }
    

    std::swap(width, height);
    imageData.swap(rotatedImageData);
}
