// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <CImg/Cimg.h>

using namespace cimg_library;

int main() {
  CImg<unsigned char> image("../../image/lena1.png"), visu(512, 512, 3, 0);
  CImgDisplay main_display(image, "Image");
  while (!main_display.is_closed()) {
    main_display.wait();
  }
  return 0;
}
