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

/**
 * @class BmpFile
 * @brief Provides BMP image loading, manipulation and saving capabilities
 */
class BmpFile
{
public:
    /**
     * @brief Constructs BmpFile and loads specified image
     * @param filename Path to BMP file to load
     */
    BmpFile(const std::string& filename) { load(filename); }

    /**
     * @brief Loads BMP image from file
     * @param filename Path to BMP file
     * @return true if loading succeeded
     * @return false if loading failed
     */
    bool load(const std::string& filename);

    /**
     * @brief Saves image to BMP file
     * @param filename Destination file path
     * @return true if saving succeeded
     * @return false if saving failed
     */
    bool save(const std::string& filename) const;

    /**
     * @brief Rotates image 90 degrees clockwise
     */
    void rotate90();

    /**
     * @brief Rotates image 270 degrees clockwise (90° counter-clockwise)
     */
    void rotate270();

    /**
     * @brief Applies Gaussian blur filter to image
     * @param kernel_size Size of convolution kernel (must be odd)
     * @param sigma Standard deviation for Gaussian function
     */
    void gaussian_filter(int kernel_size, double sigma);
    
private:
    #pragma pack(push, 1)
    /**
     * @struct BMPFileHeader
     * @brief Represents BMP file header structure
     */
    struct BMPFileHeader
    {
        uint16_t file_type = 0x4D42; ///< "BM" signature (19778 in decimal)
        uint32_t file_size = 0;      ///< Complete file size in bytes
        uint16_t reserved1 = 0;      ///< Reserved space
        uint16_t reserved2 = 0;      ///< Reserved space
        uint32_t offset_data = 54;   ///< Pixel data offset from file start
    };

    /**
     * @struct BMPInfoHeader
     * @brief Represents DIB header (BITMAPINFOHEADER)
     */
    struct BMPInfoHeader
    {
        uint32_t header_size = 40;  ///< This header's size (40 bytes)
        int32_t width = 0;          ///< Image width in pixels
        int32_t height = 0;         ///< Image height in pixels
        uint16_t colour_planes = 1; ///< Must be 1
        uint16_t bits_per_pixel = 24; ///< Color depth (24-bit for RGB)
        uint32_t compression = 0;   ///< Compression method (0 = none)
        uint32_t image_size = 0;    ///< Raw bitmap data size
        int32_t x_resolution = 0;   ///< Horizontal resolution (pixels/meter)
        int32_t y_resolution = 0;   ///< Vertical resolution (pixels/meter)
        uint32_t colours = 0;       ///< Color palette size (0 for 24bpp)
        uint32_t important_colours = 0; ///< Important colors (0 = all)
    };
    #pragma pack(pop)
    
    BMPFileHeader file_header; ///< BMP file header instance
    BMPInfoHeader info_header; ///< DIB header instance
    std::vector<uint8_t> image_data; ///< Stores raw pixel data
    int width, height; ///< Cached image dimensions
    
    /**
     * @brief Calculates Gaussian function value
     * @param x X coordinate offset from center
     * @param y Y coordinate offset from center
     * @param sigma Standard deviation
     * @return double Computed Gaussian value
     */
    double gaussian_func(int x, int y, double sigma);

    /**
     * @brief Generates Gaussian kernel matrix
     * @param size Kernel dimensions (size x size)
     * @param sigma Standard deviation
     * @return std::vector<std::vector<double>> Generated kernel
     */
    std::vector<std::vector<double>> kernel_matrix(int size, double sigma);

    /**
     * @brief Applies kernel to single pixel
     * @param x Pixel x-coordinate
     * @param y Pixel y-coordinate
     * @param kernel Convolution kernel
     * @param center Kernel center index
     * @param new_red Output for red component
     * @param new_green Output for green component
     * @param new_blue Output for blue component
     */
    void apply_kernel_to_pixel(int x, int y, const std::vector<std::vector<double>>& kernel, int center, double& new_red, double& new_green, double& new_blue);
};

#endif
