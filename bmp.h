#ifndef BMP_h
#define BMP_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#pragma pack(push, 1) // used to remove struct alignment, make it equals to 1 byte
struct BMPFileHeader
{
    uint16_t file_type = 0x4D42; // File type BM is 0x4D42
    uint32_t file_size = 0;      // Total file size
    uint16_t reserved1 = 0;      // reserved service field
    uint16_t reserved2 = 0;      // reserved service field
    uint32_t offset_data = 54; // The offset in the file at which the image data begins. Usually 54 bytes for 24-bit BMP
};

struct BMPInfoHeader
{
    uint32_t header_size = 40; // Header size, 40 bytes usually
    int32_t width = 0; // Image width in pixels
    int32_t height = 0; // Image height in pixels
    uint16_t colour_planes = 1; // Amount of colour planes, always 1
    uint16_t bits_per_pixel = 24; // Color depth in bits per pixel (24 bits for color, 8 for gray)
    uint32_t compression = 0; // compression method (0 - no compression)
    uint32_t image_size = 0; // image size in bytes
    int32_t x_resolution = 0; // number of pixels per meter along the X axis (not used)
    int32_t y_resolution = 0; // number of pixels per meter along the Y axis (not used)
    uint32_t colours = 0; // Number of colors in the palette (0 if bits_per_pixel > 8)
    uint32_t important_colours = 0; // Number of important colors in the palette
};

#pragma pack(pop)
#endif
