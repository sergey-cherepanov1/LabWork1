#ifndef SAVEBMP_h
#define SAVEBMP_h

#include "bmp.h"

bool saveBMP(const std::string& filename, const std::vector<uint8_t>& imageData, int width, int height);

#endif
