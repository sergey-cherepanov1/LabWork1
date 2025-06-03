/* Sergey Cherepanov st129987@student.spbu.ru
   LabWork1
*/

#ifndef EXPERIMENT_h
#define EXPERIMENT_h

#include "bmp.h"
#include <thread>

/**
 * @brief Rotates image 90° clockwise and applies Gaussian blur
 * @param bmp The image to process (passed by value)
 */
void rotate90AndBlur(BmpFile bmp)
{
    bmp.rotate90();
    bmp.gaussian_filter(5, 5);
};

/**
 * @brief Rotates image 270° clockwise and applies Gaussian blur 
 * @param bmp The image to process (passed by value)
 */
void rotate270AndBlur(BmpFile bmp)
{
    bmp.rotate270();
    bmp.gaussian_filter(5, 5);
};

/**
 * @brief Executes image processing in parallel using two threads
 * @param bmp The source image to process
 * @return Execution time duration in seconds
 */
std::chrono::duration<double> runParallel(BmpFile bmp)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    std::thread t90(rotate90AndBlur, bmp);
    std::thread t270(rotate270AndBlur, bmp);
    
    t90.join();
    t270.join();
    
    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Parallel execution time: " << duration.count() << " seconds" << std::endl;
    return duration;
};

/**
 * @brief Executes image processing sequentially in single thread
 * @param bmp The source image to process 
 * @return Execution time duration in seconds
 */
std::chrono::duration<double> runBasic(BmpFile bmp)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    
    BmpFile bmp1 = bmp;

    bmp.rotate90();
    bmp.gaussian_filter(5, 5);

    bmp1.rotate270();
    bmp.gaussian_filter(5, 5);
    
    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;
    std::cout << "Basic execution time: " << duration.count() << " seconds" << std::endl;
    return duration;
};

/**
 * @brief Runs the performance comparison experiment
 * @param bmp The test image to use for benchmarking
 */
void runExperiment(BmpFile bmp)
{
    std::chrono::duration<double> d1 = runBasic(bmp);
    std::chrono::duration<double> d2 = runParallel(bmp);
    std::chrono::duration<double> d3 = d1 - d2;
    
    std::cout << "Difference: " << d3.count() << " (~" << (int)((d3 / d1) * 100) << "%)\n";
    return;
};

#endif
