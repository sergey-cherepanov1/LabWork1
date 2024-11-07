#include "bmp.h"

int main() {
    std::vector<uint8_t> imageData;
    int width, height;

    if (!loadBMP("input.bmp", imageData, width, height)) {
        std::cout << "Error loading BMP file!" << std::endl;
        return -1;
    }

    rotate90(imageData, width, height);

    if (!saveBMP("output90.bmp", imageData, width, height)) {
        std::cout << "Error saving BMP file!" << std::endl;
        return -1;
    }
    
    rotate270(imageData, width, height);

    if (!saveBMP("output270.bmp", imageData, width, height)) {
        std::cout << "Error saving BMP file!" << std::endl;
        return -1;
    }

    return 0;
}
