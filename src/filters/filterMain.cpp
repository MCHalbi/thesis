// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include "./filter.h"

using cimg_library::CImg;
using cimg_library::CImgDisplay;

int main() {
  const CImg<unsigned char> image("../../image/original/lena1.png");
  CImg<unsigned char> result1(256, 256, 1, 3, 0), result2(500, 500, 1, 3, 0);

  Filter::downsample(image, &result1);
  Filter::downsample(image, &result2);

  CImgDisplay result1Disp(result1, "result1 (256 x 256)"),
    result2Disp(result2, "result2 (500 x 500)");

  while (!result1Disp.is_closed() || !result2Disp.is_closed()) {
    result1Disp.wait();
    result2Disp.wait();
  }

  return EXIT_SUCCESS;
}
