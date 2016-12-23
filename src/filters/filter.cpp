// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <CImg/CImg.h>
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

  //            x / b
  //       o------------->
  //       |
  //       |
  //       |
  // y / a |
  //       |
  //       |
  //       |
  //       v
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
              getBayerPixelColor(input, currentX, currentY);
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
      Color filterColor = getBayerPixelColor(input, x, y);
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
      if ((x % 2 == 0 && y % 2 == 0) ||
          (x % 2 == 1 && y % 2 == 1)) {
        (*output)(x, y, 0, 0) = green;
        (*output)(x, y, 0, 1) = green;
        (*output)(x, y, 0, 2) = green;
      } else if (x % 2 == 0 && y % 2 == 1) {
        (*output)(x, y, 0, 0) = blue;
        (*output)(x, y, 0, 1) = blue;
        (*output)(x, y, 0, 2) = blue;
      } else if (x % 2 == 1 && y % 2 == 0) {
        (*output)(x, y, 0, 0) = red;
        (*output)(x, y, 0, 1) = red;
        (*output)(x, y, 0, 2) = red;
      }
    }
  }
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
      Color filterColor = getBayerPixelColor(input, x, y);
      switch (filterColor) {
        case Filter::GREEN:
          (*output)(x, y, 0, 0) = 0;
          (*output)(x, y, 0, 1) = green;
          (*output)(x, y, 0, 2) = 0;
          break;
        case Filter::BLUE:
          (*output)(x, y, 0, 0) = 0;
          (*output)(x, y, 0, 1) = 0;
          (*output)(x, y, 0, 2) = blue;
          break;
        case Filter::RED:
          (*output)(x, y, 0, 0) = red;
          (*output)(x, y, 0, 1) = 0;
          (*output)(x, y, 0, 2) = 0;
          break;
      }
    }
  }
}

// ____________________________________________________________________________
Filter::Color Filter::getBayerPixelColor(const CImg<unsigned char>& input,
  int x, int y) {
  if (x % 2 == 0 && y % 2 == 1) {
    return BLUE;
  } else if (x % 2 == 1 && y % 2 == 0) {
    return RED;
  } else {
    return GREEN;
  }
}
