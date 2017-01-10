// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include "./filter.h"

using cimg_library::CImg;
using cimg_library::CImgDisplay;
using std::string;
using std::to_string;
using std::ctime;
using std::clock;

int main(int argc, char** argv) {
  // Print USAGE message
  if (argc != 1) {
    printf("Usage: ./filterMain\n");
    exit(EXIT_FAILURE);
  }

  const CImg<unsigned char> image("../../image/original/lena1.png");
  int width = image.width();
  int height = image.height();
  CImg<unsigned char> output(width, height, 1, 3);

  for (float radius = 0.1; radius <= 2; radius += 0.1) {
    Filter::rectilinearToFisheye(image, &output, radius);

    string radiusStr = to_string(radius);
    output.save(("fisheye_radius_" + radiusStr + ".png").c_str());
  }

  return EXIT_SUCCESS;
}
