// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "./filter.h"

using cimg_library::CImg;
using cimg_library::CImgDisplay;
using std::string;
using std::to_string;

int main(int argc, char** argv) {
  // Print USAGE message
  if (argc != 3) {
    printf("Usage: ./filterMain [filterSize] [interpolation radius]\n");
    exit(EXIT_FAILURE);
  }

  int filterSize = atoi(argv[1]);
  int r= atoi(argv[2]);
  const CImg<unsigned char> image("../../image/original/lena1.png");
  int width = image.width();
  int height = image.height();
  CImg<unsigned char> pattern(width, height, 1, 3),
    patternrgb(width, height, 1, 3);

  Filter::bayerArtifacts(image, &pattern, r);
  for (int rad = 0; rad <= 10; rad++) {
    for (int size = 1; size <= 10; size++) {
      Filter::bayerArtifacts(image, &patternrgb, rad, size);
      string filename("lena_bayer_artifacts_rad_" + to_string(rad));
      filename += "_grid_" + to_string(size) + ".png";
      patternrgb.save(filename.c_str());
    }
  }

  // pattern.save("artifacts.png");
  // patternrgb.save("artifactsscale.png");

  CImgDisplay patternDisp(pattern, "Artifacts");
  CImgDisplay patternrgbDisp(patternrgb, "Artifacts scaled");

  while (!patternDisp.is_closed()) {
    patternDisp.wait();
  }

  return EXIT_SUCCESS;
}
