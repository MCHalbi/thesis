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
  CImg<unsigned char> output2(width, height, 1, 3);

  Filter::rectilinearToFisheye(image, &output, width / 2);
  output.save("fisheyeToRectilinear.jpg");
  printf("ping");
  fflush(stdout);
  Filter::fisheyeToRectilinear(output, &output2, width / 2);
  printf("pong");
  fflush(stdout);
  output2.save("rectilinearToFisheye.jpg");

  return EXIT_SUCCESS;
}
