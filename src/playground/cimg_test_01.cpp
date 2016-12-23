// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <CImg.h>

using cimg_library::CImg;
using cimg_library::CImgDisplay;

int main() {
  CImg<unsigned char> image("../../image/lena1.png"), result(512, 512, 1, 3, 0);
  CImgDisplay main_display(image, "Image"),
              result_display(result, "Beyer filter");
  while (!main_display.is_closed()) {
    main_display.wait();
  }
  return 0;
}
