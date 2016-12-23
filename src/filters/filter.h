// Copyright 2016
// Author: Lukas Halbritter <halrbitl@informatik.uni-freiburg.de>

#ifndef SRC_FILTERS_FILTER_H_
#define SRC_FILTERS_FILTER_H_

#include <CImg/CImg.h>

using cimg_library::CImg;

class Filter {
 public:
  // Constructor
  Filter();

  // Generate an image with false color artifacts as caused by an bayer filter
  // This is obtained by adding a bayer filter to the image and then
  // interpolating the pixel values with the colors of this filtered image
  // params: input - An RGB input image
  //         output - Reference to the image with artifacts
  static void bayerArtifacts(const CImg<unsigned char>& input,
    CImg<unsigned char>* output);

  // Generate a grayscale image as an bayer filter would generate it on an
  // image sensor.
  // params: input - An RGB input image
  //         output - Reference to the filtered grayscale image
  static void bayerGrayscale(const CImg<unsigned char>& input,
    CImg<unsigned char>* output);

  // Generate a rgb image as you would gain it from coloring an bayer filtered
  // grayscale image.
  // params: input - An RGB input image
  //         output - Reference to the colored bayer filtered image
  static void bayerColor(const CImg<unsigned char>& input,
    CImg<unsigned char>* output);

  enum Color {RED, GREEN, BLUE};

 private:
  // Get the filter color of a bayer filter for an given image at a given
  // position
  // params: input - An input image
  //         x - The x-value of the pixel you want to know the color of
  //         y - The y-value of the pixel you want to know the color of
  static Filter::Color getBayerPixelColor(const CImg<unsigned char>& input,
    int x, int y);
};

#endif  // SRC_FILTERS_FILTER_H_
