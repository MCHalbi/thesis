// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <CImg/CImg.h>
#include <math.h>
#include <stdio.h>
#include "./filter.h"

using cimg_library::CImg;

// _____________________________________________________________________________
Filter::Filter() {}

// _____________________________________________________________________________
void Filter::bayerArtifacts(const CImg<unsigned char>& input,
  CImg<unsigned char>* output) {
  Filter::bayerColor(input, output);

  int width = input.width();
  int height = input.height();

  //          x
  //   o------------->
  //   |  +--+--+--+
  //   |  |  |  |  |
  //   |  +--+--+--+
  // y | a|  |  |  |
  //   |  +--+--+--+
  //   |  |  |  |  |
  //   |  +--+--+--+
  //   v      b
  for (int y = 0; y < width; y++) {
    for (int x = 0; x < height; x++) {
      int rMedian = 0;
      int gMedian = 0;
      int bMedian = 0;
      int rCount = 0;
      int gCount = 0;
      int bCount = 0;
      for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
          int currentX = x + b;
          int currentY = y + a;
          if (currentX >= 0 && currentY >= 0 &&
              currentX < width && currentY < height) {
            Color currentFilterColor =
              getBayerPixelColor(currentX, currentY);
            switch (currentFilterColor) {
              case RED:
                rMedian += input(currentX, currentY, 0, 0);
                rCount++;
                break;
              case GREEN:
                gMedian += input(currentX, currentY, 0, 1);
                gCount++;
                break;
              case BLUE:
                bMedian += input(currentX, currentY, 0, 2);
                bCount++;
                break;
            }
          }
        }
      }
      rMedian = rMedian / rCount;
      gMedian = gMedian / gCount;
      bMedian = bMedian / bCount;
      Color filterColor = getBayerPixelColor(x, y);
      switch (filterColor) {
        case RED:
          (*output)(x, y, 0, 0) = input(x, y, 0, 0);
          (*output)(x, y, 0, 1) = (unsigned char) gMedian;
          (*output)(x, y, 0, 2) = (unsigned char) bMedian;
          break;
        case GREEN:
          (*output)(x, y, 0, 0) = (unsigned char) rMedian;
          (*output)(x, y, 0, 1) = input(x, y, 0, 1);
          (*output)(x, y, 0, 2) = (unsigned char) bMedian;
          break;
        case BLUE:
          (*output)(x, y, 0, 0) = (unsigned char) rMedian;
          (*output)(x, y, 0, 1) = (unsigned char) gMedian;
          (*output)(x, y, 0, 2) = input(x, y, 0, 2);
          break;
      }
    }
  }
}

// _____________________________________________________________________________
void Filter::bayerGrayscale(const CImg<unsigned char>& input,
  CImg<unsigned char>* output) {
  int width = input.width();
  int height = input.height();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      unsigned char red   = input(x, y, 0, 0);
      unsigned char green = input(x, y, 0, 1);
      unsigned char blue  = input(x, y, 0, 2);
      Color filterColor = getBayerPixelColor(x, y);
      switch (filterColor) {
        case GREEN:
          (*output)(x, y, 0, 0) = green;
          (*output)(x, y, 0, 1) = green;
          (*output)(x, y, 0, 2) = green;
          break;
        case BLUE:
          (*output)(x, y, 0, 0) = blue;
          (*output)(x, y, 0, 1) = blue;
          (*output)(x, y, 0, 2) = blue;
          break;
        case RED:
          (*output)(x, y, 0, 0) = red;
          (*output)(x, y, 0, 1) = red;
          (*output)(x, y, 0, 2) = red;
          break;
      }
    }
  }
}

// _____________________________________________________________________________
void Filter::bayerGrayscale(const CImg<unsigned char>& input,
  CImg<unsigned char>* output, const int patternSize) {
  int imageWidth = input.width();
  int imageHeight = input.height();

  int patternWidth = imageWidth / patternSize;
  int patternHeight = imageHeight/ patternSize;

  CImg<unsigned char> temp(patternWidth, patternHeight, 1, 1, 0);
}

// _____________________________________________________________________________
void Filter::bayerColor(const CImg<unsigned char>& input,
  CImg<unsigned char>* output) {
  int width = input.width();
  int height = input.height();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      unsigned char red   = input(x, y, 0, 0);
      unsigned char green = input(x, y, 0, 1);
      unsigned char blue  = input(x, y, 0, 2);
      Color filterColor = getBayerPixelColor(x, y);
      switch (filterColor) {
        case GREEN:
          (*output)(x, y, 0, 0) = 0;
          (*output)(x, y, 0, 1) = green;
          (*output)(x, y, 0, 2) = 0;
          break;
        case BLUE:
          (*output)(x, y, 0, 0) = 0;
          (*output)(x, y, 0, 1) = 0;
          (*output)(x, y, 0, 2) = blue;
          break;
        case RED:
          (*output)(x, y, 0, 0) = red;
          (*output)(x, y, 0, 1) = 0;
          (*output)(x, y, 0, 2) = 0;
          break;
      }
    }
  }
}

// ____________________________________________________________________________
void Filter::downsample(const CImg<unsigned char>& input,
  CImg<unsigned char>* output) {
  int oldWidth = input.width();
  int oldHeight = input.height();
  int newWidth = output->width();
  int newHeight = output->height();
  // Size of the area of the input image which will be merged into one pixel in
  // the ouptut image
  int gridSizeX = round(oldWidth / newWidth);
  int gridSizeY = round(oldHeight/ newHeight);

  for (int y = 0; y < newHeight; y++) {
    for (int x = 0; x < newWidth; x++) {
      int newRed = 0, newGreen = 0, newBlue = 0, counter = 0;
      for (int a = 0; a < gridSizeY; a++) {
        for (int b = 0; b < gridSizeX; b++) {
          int xPos = x * gridSizeX + b;
          int yPos = y * gridSizeY + a;
          if (xPos >= 0 && xPos < oldWidth && yPos >= 0 && yPos < oldHeight) {
            newRed += input(x * gridSizeX + b, y * gridSizeY + a, 0, 0);
            newGreen += input(x * gridSizeX + b, y * gridSizeY + a, 0, 1);
            newBlue += input(x * gridSizeX + b, y * gridSizeY + a, 0, 2);
            counter++;
          }
        }
      }
      (*output)(x, y, 0, 0) = (unsigned char) (newRed / counter);
      (*output)(x, y, 0, 1) = (unsigned char) (newGreen / counter);
      (*output)(x, y, 0, 2) = (unsigned char) (newBlue / counter);
    }
  }
}

// ____________________________________________________________________________
void Filter::upsampleSimple(const CImg<unsigned char>& input,
  CImg<unsigned char>* output) {
  int oldWidth = input.width();
  int oldHeight = input.height();
  int newWidth = output->width();
  int newHeight = output->height();

  int gridSizeX = round(newWidth / oldWidth);
  int gridSizeY = round(newHeight / oldHeight);

  printf("grid size: %d x %d", gridSizeX, gridSizeY);
  fflush(stdout);

  for (int y = 0; y < newHeight; y++) {
    for (int x = 0; x < newWidth; x++) {
      int originX = floor(x / gridSizeX);
      int originY = floor(y / gridSizeY);
      (*output)(x, y, 0, 0) = input(originX, originY, 0, 0);
      (*output)(x, y, 0, 1) = input(originX, originY, 0, 1);
      (*output)(x, y, 0, 2) = input(originX, originY, 0, 2);
    }
  }
}

// ____________________________________________________________________________
Filter::Color Filter::getBayerPixelColor(int x, int y) {
  if (x % 2 == 0 && y % 2 == 1) {
    return BLUE;
  } else if (x % 2 == 1 && y % 2 == 0) {
    return RED;
  } else {
    return GREEN;
  }
}
