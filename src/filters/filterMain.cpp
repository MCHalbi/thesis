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
  CImg<unsigned char> grayscale(width, height, 1, 3, 0),
    color(width, height, 1, 3, 0);

  Filter::bayerGrayscale(image, &grayscale, filterSize);
  Filter::bayerColor(image, &color, filterSize);

  grayscale.save("grayscale.png");
  color.save("color.png");

  CImgDisplay grayscaleDisp(grayscale, "Grayscale");
  CImgDisplay colorDisp(color, "Color");

  while (!grayscaleDisp.is_closed()) {
    grayscaleDisp.wait();
  }

  return EXIT_SUCCESS;
}
