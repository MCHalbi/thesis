// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <CImg.h>
#include "./filter.h"

using cimg_library::CImg;

// _____________________________________________________________________________
Filter::Filter() {}

// _____________________________________________________________________________
void Filter::bayerArtifacts(const CImg<unsigned char> input,
  CImg<unsigned char>* output) {}

// _____________________________________________________________________________
void Filter::bayerGrayscale(const CImg<unsigned char> input,
  CImg<unsigned char>* output) {
  int width = input.width();
  int height = input.height();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      unsigned char red   = input(x, y, 0, 0);
      unsigned char green = input(x, y, 0, 1);
      unsigned char blue  = input(x, y, 0, 2);
      if (x % 2 == 0 && y % 2 == 0) {
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
      } else if (x % 2 == 1 && y % 2 == 1) {
        (*output)(x, y, 0, 0) = green;
        (*output)(x, y, 0, 1) = green;
        (*output)(x, y, 0, 2) = green;
      }
    }
  }
}

// _____________________________________________________________________________
void Filter::bayerColor(const CImg<unsigned char> input,
  CImg<unsigned char>* output) {}
