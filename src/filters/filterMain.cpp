// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <stdlib.h>
#include "./filter.h"

using cimg_library::CImg;
using cimg_library::CImgDisplay;

int main(int argc, char** argv) {
  // Print USAGE message
  if (argc != 3) {
    printf("Usage: ./filterMain [smallSize] [largeSize]");
  }
  int smallSize = atoi(argv[1]);
  int largeSize = atoi(argv[2]);
  const CImg<unsigned char> image("../../image/original/lena1.png");
  CImg<unsigned char> small(smallSize, smallSize, 1, 3, 0),
    large(largeSize, largeSize, 1, 3, 0);

  Filter::downsample(image, &small);
  Filter::upsampleSimple(small, &large);

  small.save("small.png");
  large.save("large.png");

  CImgDisplay smallDisp(small, "Small"),
    largeDisp(large, "Large");

  while (!smallDisp.is_closed() || !largeDisp.is_closed()) {
    smallDisp.wait();
    largeDisp.wait();
  }

  return EXIT_SUCCESS;
}
