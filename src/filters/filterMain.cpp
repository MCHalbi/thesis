// Copyright 2016 - 2017
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

  const CImg<unsigned char> image("../../image/original/flyingThings.ppm");
  int width = image.width();
  int height = image.height();
  CImg<unsigned char> output(width, height, 1, 3), tmp(width, height, 1, 3);
  tmp = image;

  for (float radius = 0.1; radius <= 2; radius += 0.1) {
    Filter::rectilinearToFisheye(image, &tmp, radius);

    string radiusStr = to_string(radius);
    tmp.save(("fisheye_radius_" + radiusStr + ".png").c_str());

    Filter::fisheyeToRectilinear(tmp, &output, radius);

    output.save(("blur_radius_" + radiusStr + ".png").c_str());
  }

  return EXIT_SUCCESS;
}
