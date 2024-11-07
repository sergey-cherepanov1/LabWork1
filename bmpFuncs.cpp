#include "bmp.h"
#include <iomanip> 

bool loadBMP(const std::string& filename, std::vector<uint8_t>& imageData, int& width, int& height)
{
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    BMPFileHeader fileHeader;
    file.read((char*)&fileHeader, sizeof(fileHeader));

    if (fileHeader.file_type != 0x4D42)
    {
        std::cout << "Not a BMP file!" << std::endl;
        return false;
    }

    BMPInfoHeader infoHeader;
    file.read((char*)&infoHeader, sizeof(infoHeader));

    width = infoHeader.width;
    height = infoHeader.height;

    // Size of image data
    int imageSize = infoHeader.image_size;

    // Allocating memory for image data
    imageData.resize(imageSize);

    // Move the read pointer to where the image data begins
    file.seekg(fileHeader.offset_data, std::ios::beg);

    // Reading image data
    file.read((char*)imageData.data(), imageSize);
    std::cout << imageSize << ' ' << fileHeader.file_size << std::endl;
    std::cout << width << ' ' << height << std::endl;
    for (size_t i = 0; i < imageData.size(); ++i) {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)imageData[i] << " ";
        if (i % 390 == 0) {std::cout << '\n';}
    }
    file.close();
    return true;
}

bool saveBMP(const std::string& filename, const std::vector<uint8_t>& imageData, int width, int height)
{
    std::ofstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open())
    {
        std::cout << "Error opening file for saving!" << std::endl;
        return false;
    }

    BMPFileHeader fileHeader = {0x4D42, (uint32_t)(54 + imageData.size()), 0, 0, 54};
    BMPInfoHeader infoHeader = {40, width, height, 1, 24, 0, (uint32_t)imageData.size(), 0, 0, 0, 0};

    file.write((char*)&fileHeader, sizeof(fileHeader));
    file.write((char*)&infoHeader, sizeof(infoHeader));
    file.write((const char*)imageData.data(), imageData.size());

    file.close();
    return true;
}

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
