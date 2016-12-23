// Copyright 2016
// Author: Lukas Halbritter <halrbitl@informatik.uni-freiburg.de>

#ifndef SRC_FILTERS_FILTER_H_
#define SRC_FILTERS_FILTER_H_

#include <CImg.h>

using cimg_library::CImg;

class Filter {
 public:
  // Constructor
  Filter();

  // Generate an image with false color artifacts as caused by an bayer filter
  // params: input - An RGB input image
  //         output - Reference to the image with artifacts
  static void bayerArtifacts(const CImg<unsigned char> input,
    CImg<unsigned char>* output);

  // Generate a grayscale image as an bayer filter would generate it on an
  // image sensor.
  // params: input - An RGB input image
  //         output - Reference to the filtered grayscale image
  static void bayerGrayscale(const CImg<unsigned char> input,
    CImg<unsigned char>* output);

  // Generate a rgb image as you would gain it from coloring an bayer filtered
  // grayscale image.
  // params: input - An RGB input image
  //         output - Reference to the colored bayer filtered image
  static void bayerColor(const CImg<unsigned char> input,
    CImg<unsigned char>* output);

 private:
};

#endif  // SRC_FILTERS_FILTER_H_
