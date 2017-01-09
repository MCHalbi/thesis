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
  CImg<unsigned char>* output, const int r) {
  Filter::bayerColor(input, output);

  int width = input.width();
  int height = input.height();

  for (int y = 0; y < width; y++) {
    for (int x = 0; x < height; x++) {
      // Calculate mean value of the pixel enviroment
      int meanR = 0, meanG = 0, meanB = 0;
      int countR = 0, countG = 0, countB = 0;
      for (int offsetY = -r; offsetY <= r; offsetY++) {
        for (int offsetX = -r; offsetX <= r; offsetX++) {
          int currentX = x + offsetX;
          int currentY = y + offsetY;
          Color currentFilterColor = getBayerPixelColor(currentX, currentY);
          if (currentX >= 0 && currentY >= 0 &&
              currentX < width && currentY < height) {
            switch (currentFilterColor) {
              case RED:
                meanR += input(currentX, currentY, 0, 0);
                countR++;
                break;
              case GREEN:
                meanG += input(currentX, currentY, 0, 1);
                countG++;
                break;
              case BLUE:
                meanB += input(currentX, currentY, 0, 2);
                countB++;
                break;
            }
          }
        }
      }

      if (countR != 0) meanR /= countR;
      if (countG != 0) meanG /= countG;
      if (countB != 0) meanB /= countB;

      // Set pixel value of the output image
      Color filterColor = getBayerPixelColor(x, y);
      switch (filterColor) {
        case RED:
          (*output)(x, y, 0, 0) = input(x, y, 0, 0);
          (*output)(x, y, 0, 1) = (unsigned char) meanG;
          (*output)(x, y, 0, 2) = (unsigned char) meanB;
          break;
        case GREEN:
          (*output)(x, y, 0, 0) = (unsigned char) meanR;
          (*output)(x, y, 0, 1) = input(x, y, 0, 1);
          (*output)(x, y, 0, 2) = (unsigned char) meanB;
          break;
        case BLUE:
          (*output)(x, y, 0, 0) = (unsigned char) meanR;
          (*output)(x, y, 0, 1) = (unsigned char) meanG;
          (*output)(x, y, 0, 2) = input(x, y, 0, 2);
          break;
      }
    }
  }
}

// _____________________________________________________________________________
void Filter::bayerArtifacts(const CImg<unsigned char>& input,
  CImg<unsigned char>* output, const int r, const int gSize) {
  Filter::bayerColor(input, output);
  int width = input.width();
  int height = input.height();

  for (int y = 0; y < height; y += gSize) {
    for (int x = 0; x < width; x += gSize) {
      // Calculate mean values
      int meanR = 0, meanG = 0, meanB = 0;
      int countR = 0, countG = 0, countB = 0;
      for (int offsY = -r * gSize; offsY <= r * gSize; offsY += gSize) {
        for (int offsX = -r * gSize; offsX <= r * gSize; offsX += gSize) {
          int currentX = x + offsX;
          int currentY = y + offsY;
          Color currentFilterColor =
            getBayerPixelColor(currentX / gSize, currentY / gSize);
          if (currentX >= 0 && currentY >= 0 &&
            currentX < width && currentY < height) {
            switch (currentFilterColor) {
              case RED:
                meanR += input(currentX, currentY, 0, 0);
                countR++;
                break;
              case GREEN:
                meanG += input(currentX, currentY, 0, 1);
                countG++;
                break;
              case BLUE:
                meanB += input(currentX, currentY, 0, 2);
                countB++;
                break;
            }
          }
        }
      }

      if (countR != 0) meanR /= countR;
      if (countG != 0) meanG /= countG;
      if (countB != 0) meanB /= countB;

      // Set new rgb pixel values
      Color filterColor = getBayerPixelColor(x, y);
      unsigned char valR, valG, valB;
      switch (filterColor) {
        case RED:
          valR = input(x, y, 0, 0);
          valG = (unsigned char) meanG;
          valB = (unsigned char) meanB;
          break;
        case GREEN:
          valR = (unsigned char) meanR;
          valG = input(x, y, 0, 1);
          valB = (unsigned char) meanB;
          break;
        case BLUE:
          valR = (unsigned char) meanR;
          valG = (unsigned char) meanG;
          valB = input(x, y, 0, 2);
          break;
      }

      // Safe new value in the output image
      for (int offsetY = 0; offsetY < gSize; offsetY++) {
        for (int offsetX = 0; offsetX < gSize; offsetX++) {
          int currentX = x + offsetX;
          int currentY = y + offsetY;
          if (currentX < width && currentY < height) {
            (*output)(currentX, currentY, 0, 0) = valR;
            (*output)(currentX, currentY, 0, 1) = valG;
            (*output)(currentX, currentY, 0, 2) = valB;
          }
        }
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
  CImg<unsigned char>* output, const int gridSize) {
  int width = input.width();
  int height = input.height();

  for (int y = 0; y < height; y += gridSize) {
    for (int x = 0; x < width; x += gridSize) {
      // First, calculate  the means of the areas in the image which are
      // covered by a single filter tile ...
      int meanR = 0, meanG = 0, meanB = 0, count = 0;
      for (int offsetY = 0; offsetY < gridSize; offsetY++) {
        for (int offsetX = 0; offsetX < gridSize; offsetX++) {
          if (x + offsetX < width && y + offsetY < height) {
            meanR += input(x + offsetX, y + offsetY, 0, 0);
            meanG += input(x + offsetX, y + offsetY, 0, 1);
            meanB += input(x + offsetX, y + offsetY, 0, 2);
            count++;
          }
        }
      }

      meanR /= count;
      meanG /= count;
      meanB /= count;

      // ... then fill the corresponding pixels in the output image with this
      // mean value
      Color filterColor = getBayerPixelColor(x / gridSize, y / gridSize);
      for (int offsetY = 0; offsetY < gridSize; offsetY++) {
        for (int offsetX = 0; offsetX < gridSize; offsetX++) {
          if (x + offsetX < width && y + offsetY < height) {
            switch (filterColor) {
              case RED:
                (*output)(x + offsetX, y + offsetY, 0, 0) = meanR;
                (*output)(x + offsetX, y + offsetY, 0, 1) = meanR;
                (*output)(x + offsetX, y + offsetY, 0, 2) = meanR;
                break;
              case GREEN:
                (*output)(x + offsetX, y + offsetY, 0, 0) = meanG;
                (*output)(x + offsetX, y + offsetY, 0, 1) = meanG;
                (*output)(x + offsetX, y + offsetY, 0, 2) = meanG;
                break;
              case BLUE:
                (*output)(x + offsetX, y + offsetY, 0, 0) = meanB;
                (*output)(x + offsetX, y + offsetY, 0, 1) = meanB;
                (*output)(x + offsetX, y + offsetY, 0, 2) = meanB;
                break;
            }
          }
        }
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
void Filter::bayerColor(const CImg<unsigned char>& input,
  CImg<unsigned char>* output, const int gridSize) {
  int width = input.width();
  int height = input.height();

  for (int y = 0; y < height; y += gridSize) {
    for (int x = 0; x < width; x += gridSize) {
      // First, calculate  the means of the areas in the image which are
      // covered by a single filter tile ...
      int meanR = 0, meanG = 0, meanB = 0, count = 0;
      for (int offsetY = 0; offsetY < gridSize; offsetY++) {
        for (int offsetX = 0; offsetX < gridSize; offsetX++) {
          if (x + offsetX < width && y + offsetY < height) {
            meanR += input(x + offsetX, y + offsetY, 0, 0);
            meanG += input(x + offsetX, y + offsetY, 0, 1);
            meanB += input(x + offsetX, y + offsetY, 0, 2);
            count++;
          }
        }
      }
      meanR /= count;
      meanG /= count;
      meanB /= count;

      // ... then fill the corresponding pixels in the output image with this
      // mean value
      Color filterColor = getBayerPixelColor(x / gridSize, y / gridSize);
      for (int offsetY = 0; offsetY < gridSize; offsetY++) {
        for (int offsetX = 0; offsetX < gridSize; offsetX++) {
          if (x + offsetX < width && y + offsetY < height) {
            switch (filterColor) {
              case RED:
                (*output)(x + offsetX, y + offsetY, 0, 0) = meanR;
                (*output)(x + offsetX, y + offsetY, 0, 1) = 0;
                (*output)(x + offsetX, y + offsetY, 0, 2) = 0;
                break;
              case GREEN:
                (*output)(x + offsetX, y + offsetY, 0, 0) = 0;
                (*output)(x + offsetX, y + offsetY, 0, 1) = meanG;
                (*output)(x + offsetX, y + offsetY, 0, 2) = 0;
                break;
              case BLUE:
                (*output)(x + offsetX, y + offsetY, 0, 0) = 0;
                (*output)(x + offsetX, y + offsetY, 0, 1) = 0;
                (*output)(x + offsetX, y + offsetY, 0, 2) = meanB;
                break;
            }
          }
        }
      }
    }
  }
}

// ____________________________________________________________________________
void Filter::rectilinearToFisheye(const CImg<unsigned char>& input,
  CImg<unsigned char>* output, int radius) {
  int width = input.width();
  int height = input.height();

  for (int y = 0; y < height; y++) {
    int centerY = height / 2 - y;
    for (int x = 0; x < width; x++) {
      int centerX = x - width / 2;
      int maxLength = getMaxLength(centerX, centerY, radius);
      int newX = (centerX *  maxLength / radius) + (width / 2);
      int newY = (height / 2) - (centerY * maxLength / radius);
      if (!(newX < 0 || newX >= width || newY < 0 || newY >= height)) {
        (*output)(x, y, 0, 0) = input(newX, newY, 0, 0);
        (*output)(x, y, 0, 1) = input(newX, newY, 0, 1);
        (*output)(x, y, 0, 2) = input(newX, newY, 0, 2);
      } else {
        (*output)(x, y, 0, 0) = 0;
        (*output)(x, y, 0, 1) = 0;
        (*output)(x, y, 0, 2) = 0;
      }
    }
  }
}

// ____________________________________________________________________________
void Filter::fisheyeToRectilinear(const CImg<unsigned char>& input,
  CImg<unsigned char>* output, int radius) {
  int width = input.width();
  int height = input.height();

  for (int y = 0; y < height; y++) {
    int centerY = height / 2 - y;
    for (int x = 0; x < width; x++) {
      int centerX = x - width / 2;
      int maxLength = getMaxLength(centerX, centerY, radius);
      int newX = (centerX * radius / maxLength) + (width / 2);
      int newY = (height / 2) - (centerY * radius / maxLength);
      if (!(newX < 0 || newX >= width || newY < 0 || newY >= height)) {
        (*output)(x, y, 0, 0) = input(newX, newY, 0, 0);
        (*output)(x, y, 0, 1) = input(newX, newY, 0, 1);
        (*output)(x, y, 0, 2) = input(newX, newY, 0, 2);
      } else {
        (*output)(x, y, 0, 0) = 0;
        (*output)(x, y, 0, 1) = 0;
        (*output)(x, y, 0, 2) = 0;
      }
    }
  }
}

// ____________________________________________________________________________
Filter::Color Filter::getBayerPixelColor(const int x, const int y) {
  if (x % 2 == 0 && y % 2 == 1) {
    return BLUE;
  } else if (x % 2 == 1 && y % 2 == 0) {
    return RED;
  } else {
    return GREEN;
  }
}

// ____________________________________________________________________________
float Filter::getMaxLength(int x, int y, int r) {
  if (x == 0 || y == 0) {
    return r;
  } else if (abs(x) >= abs(y)) {
    return sqrt(pow(r, 2) + pow(y * r / x, 2));
  } else {
    return sqrt(pow(r, 2) + pow(x * r / y, 2));
  }
}
