/* Sergey Cherepanov st129987@student.spbu.ru
   LabWork1
*/

#ifndef BMP_h
#define BMP_h

#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

class BmpFile
{
public:
    BmpFile(const std::string& filename) { load(filename); }

    bool load(const std::string& filename);
    bool save(const std::string& filename) const;
    void rotate90();
    void rotate270();
    void gaussian_filter(int kernel_size, double sigma);
    
private:
    #pragma pack(push, 1)
    struct BMPFileHeader
    {
        uint16_t file_type = 0x4D42; // File type BM is 0x4D42
        uint32_t file_size = 0;      // Total file size
        uint16_t reserved1 = 0;      // Reserved field
        uint16_t reserved2 = 0;      // Reserved field
        uint32_t offset_data = 54;   // The offset in the file where image data begins
    };

    struct BMPInfoHeader
    {
        uint32_t header_size = 40;  // Header size, 40 bytes
        int32_t width = 0;          // Image width in pixels
        int32_t height = 0;         // Image height in pixels
        uint16_t colour_planes = 1; // Number of color planes, always 1
        uint16_t bits_per_pixel = 24; // Bits per pixel (usually 24-bit)
        uint32_t compression = 0;   // Compression method (0 means no compression)
        uint32_t image_size = 0;    // Image size in bytes
        int32_t x_resolution = 0;   // Horizontal resolution (not used)
        int32_t y_resolution = 0;   // Vertical resolution (not used)
        uint32_t colours = 0;       // Number of colors in the palette (0 if bpp > 8)
        uint32_t important_colours = 0; // Number of important colors (0 usually)
    };
    #pragma pack(pop)
    
    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    std::vector<uint8_t> image_data;
    int width, height;
    
    double gaussian_func(int x, int y, double sigma);
    std::vector<std::vector<double>> kernel_matrix(int size, double sigma);
    void apply_kernel_to_pixel(int x, int y, const std::vector<std::vector<double>>& kernel, int center, double& new_red, double& new_green, double& new_blue);
};

#endif
