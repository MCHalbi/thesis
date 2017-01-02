// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <stdlib.h>
#include "./filter.h"

using cimg_library::CImg;
using cimg_library::CImgDisplay;

int main(int argc, char** argv) {
  // Print USAGE message
  if (argc != 2) {
    printf("Usage: ./filterMain [filterSize]");
  }

  int filterSize = atoi(argv[1]);
  const CImg<unsigned char> image("../../image/original/lena1.png");
  int width = image.width();
  int height = image.height();
  CImg<unsigned char> filtered(width, height, 1, 3, 0);

  Filter::bayerColor(image, &filtered, filterSize);

  filtered.save("filtered.png");

  CImgDisplay filteredDisp(filtered, "Filtered");

  while (!filteredDisp.is_closed()) {
    filteredDisp.wait();
  }

  return EXIT_SUCCESS;
}
