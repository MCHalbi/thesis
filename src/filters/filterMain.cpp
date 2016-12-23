// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include "./filter.h"

using cimg_library::CImg;
using cimg_library::CImgDisplay;

int main() {
  const CImg<unsigned char> image("../../image/lena1.png");
  CImg<unsigned char> resultGrayscale(512, 512, 1, 3, 0),
    resultColor(512, 512, 1, 3, 0), resultPattern(512, 512, 1, 3, 0);

  Filter::bayerGrayscale(image, &resultGrayscale);
  Filter::bayerColor(image, &resultColor);
  Filter::bayerArtifacts(image, &resultPattern);

  CImgDisplay originalDisp(image, "Original"),
    resultGrayscaleDisp(resultGrayscale, "Filtered Image"),
    resultColorDisp(resultColor, "Filtered Color Image"),
    resultPatternDisp(resultPattern, "Image with artifacts");

  resultGrayscale.save("./filtered.png");
  resultColor.save("./filteredColor.png");
  resultPattern.save("./withArtifacts.png");

  while (!originalDisp.is_closed() || !resultGrayscaleDisp.is_closed() ||
    !resultColorDisp.is_closed() || !resultPatternDisp.is_closed()) {
    originalDisp.wait();
    resultGrayscaleDisp.wait();
    resultColorDisp.wait();
    resultPatternDisp.wait();
  }

  return EXIT_SUCCESS;
}
