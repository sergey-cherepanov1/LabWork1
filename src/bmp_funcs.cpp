/* Sergey Cherepanov st129987@student.spbu.ru
   LabWork1
*/

#include "bmp.h"

bool BmpFile::load(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    file.read((char*)&file_header, sizeof(file_header));

    if (file_header.file_type != 0x4D42)
    {
        std::cout << "Not a BMP file!" << std::endl;
        return false;
    }

    file.read((char*)&info_header, sizeof(info_header));

    width = info_header.width;
    height = info_header.height;
    image_data.resize(info_header.image_size);

    file.seekg(file_header.offset_data, std::ios::beg);
    file.read((char*)image_data.data(), image_data.size());
    file.close();
    return true;
}

bool BmpFile::save(const std::string& filename) const
{
    std::ofstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open())
    {
        std::cout << "Error opening file for saving!" << std::endl;
        return false;
    }

    BMPFileHeader file_header = {0x4D42, (uint32_t)(54 + image_data.size()), 0, 0, 54};
    BMPInfoHeader info_header = {40, width, height, 1, 24, 0, (uint32_t)image_data.size(), 0, 0, 0, 0};

    file.write((const char*)&file_header, sizeof(file_header));
    file.write((const char*)&info_header, sizeof(info_header));
    file.write((const char*)image_data.data(), image_data.size());

    file.close();
    return true;
}

void BmpFile::rotate90()
{
    int padding = (4 - (width * 3) % 4) % 4;
    int new_padding = (4 - (height * 3) % 4) % 4;
    std::vector<uint8_t> rotated_data((height * 3 + new_padding) * width);

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int old_index = (j * (width * 3 + padding)) + i * 3;
            int new_index = ((width - 1 - i) * (height * 3 + new_padding)) + j * 3;

            rotated_data[new_index] = image_data[old_index];
            rotated_data[new_index + 1] = image_data[old_index + 1];
            rotated_data[new_index + 2] = image_data[old_index + 2];
        }
    }
    image_data = std::move(rotated_data);
    std::swap(height, width);
}

void BmpFile::rotate270()
{
    int padding = (4 - (width * 3) % 4) % 4;
    int new_padding = (4 - (height * 3) % 4) % 4;
    std::vector<uint8_t> rotated_data((height * 3 + new_padding) * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int old_index = (i * (width * 3 + padding)) + j * 3;
            int new_index = ((j * (height * 3 + new_padding)) + (height - 1 - i) * 3);

            rotated_data[new_index] = image_data[old_index];
            rotated_data[new_index + 1] = image_data[old_index + 1];
            rotated_data[new_index + 2] = image_data[old_index + 2];
        }
    }
    image_data = std::move(rotated_data);
    std::swap(height, width);
}
