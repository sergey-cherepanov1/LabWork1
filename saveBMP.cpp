#include "saveBMP.h"

bool saveBMP(const std::string& filename, const std::vector<uint8_t>& imageData, int width, int height)
{
    std::ofstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open())
    {
        std::cerr << "Error opening file for saving!" << std::endl;
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
