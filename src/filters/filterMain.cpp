// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <stdlib.h>
#include <stdio.h>
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
  CImg<unsigned char> pattern(width, height, 1, 3),
    patternrgb(width, height, 1, 3);

  Filter::bayerArtifacts(image, &pattern);
  Filter::bayerArtifacts(image, &patternrgb, filterSize);

  pattern.save("artifacts.png");
  patternrgb.save("artifactsscale.png");

  CImgDisplay patternDisp(pattern, "Artifacts");
  CImgDisplay patternrgbDisp(patternrgb, "Artifacts scaled");

  while (!patternDisp.is_closed()) {
    patternDisp.wait();
  }

  return EXIT_SUCCESS;
}
