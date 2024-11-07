#include "bmp.h"

int main() {
    std::vector<uint8_t> imageData;
    int width, height;

    // Загрузка изображения
    if (!loadBMP("input.bmp", imageData, width, height)) {
        std::cout << "Error loading BMP file!" << std::endl;
        return -1;
    }

    // Поворот изображения на 90 градусов
    rotate90(imageData, width, height);

    // Сохранение изображения
    if (!saveBMP("output.bmp", imageData, width, height)) {
        std::cout << "Error saving BMP file!" << std::endl;
        return -1;
    }

    return 0;
}
