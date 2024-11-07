#include "loadBMP.h"

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

    // Calculating the image row size with alignment to a 4 bytes.
    // Row size in bytes
    int rowSize = (width * infoHeader.bits_per_pixel + 31) / 32 * 4;

    // Size of all image data
    int imageSize = rowSize * height;

    // Allocating memory for image data
    imageData.resize(imageSize);

    // Move the read pointer to where the image data begins
    file.seekg(fileHeader.offset_data, std::ios::beg);

    // Reading image data
    file.read((char*)imageData.data(), imageSize);
    std::cout << imageSize << ' ' << infoHeader.image_size << std::endl;
    file.close();
    return true;
}
