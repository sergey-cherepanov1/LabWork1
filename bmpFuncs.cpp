#include "bmp.h"

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
    int padding = (4 - (width * 3) % 4) % 4;
    int newPadding = (4 - (height * 3) % 4) % 4;

    std::vector<uint8_t> rotatedData((width * 3 + padding) * height);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int oldIndex = (j * (width * 3 + padding)) + i * 3; 
            int newIndex = ((width - 1 - i) * (height * 3 + newPadding)) + j * 3;

            rotatedData[newIndex] = imageData[oldIndex]; 
            rotatedData[newIndex + 1] = imageData[oldIndex + 1]; 
            rotatedData[newIndex + 2] = imageData[oldIndex + 2]; 
        }
    }

    imageData = std::move(rotatedData);
    
    std::swap(height, width);
}

void rotate270(std::vector<uint8_t>& imageData, int& width, int& height)
{  
    int padding = (4 - (width * 3) % 4) % 4;
    int newPadding = (4 - (height * 3) % 4) % 4;

    std::vector<uint8_t> rotatedData((width * 3 + padding) * height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int oldIndex = (i * (width * 3 + padding)) + j * 3;
            int newIndex = ((j * (height * 3 + newPadding)) + (height - 1 - i) * 3); 

            rotatedData[newIndex] = imageData[oldIndex];  
            rotatedData[newIndex + 1] = imageData[oldIndex + 1]; 
            rotatedData[newIndex + 2] = imageData[oldIndex + 2]; 
        }
    }

    imageData = std::move(rotatedData);
    std::swap(height, width);

}
