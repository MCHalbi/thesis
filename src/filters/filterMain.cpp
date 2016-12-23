// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include "./filter.h"

using cimg_library::CImg;
using cimg_library::CImgDisplay;

int main() {
  const CImg<unsigned char> image("../../image/lena1.png");
  CImg<unsigned char> result(512, 512, 1, 3, 0);

  Filter::bayerGrayscale(image, &result);

  CImgDisplay originalDisp(image, "Original"),
    resultDisp(result, "Filtered Image");

  result.save("./filtered.png");

  while (!originalDisp.is_closed() || !resultDisp.is_closed()) {
    originalDisp.wait();
    resultDisp.wait();
  }

  return EXIT_SUCCESS;
}
