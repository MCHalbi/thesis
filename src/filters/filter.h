// Copyright 2016
// Author: Lukas Halbritter <halrbitl@informatik.uni-freiburg.de>

#ifndef SRC_FILTERS_FILTER_H_
#define SRC_FILTERS_FILTER_H_

#include <CImg/CImg.h>

using cimg_library::CImg;

class Filter {
 public:
  enum Color {RED, GREEN, BLUE};

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

  // Generate a grayscale image as an bayer filter would generate it on an
  // image sensor. The size of the bayer pattern can be choosen.
  // params: input - An RGB input image
  //         output - Reference to the filtered grayscale image
  //         patternSize - The grid size of the bayer filter. This parameter
  //           specifies the size of one field in the pattern, not of one GRBG
  //           field group
  static void bayerGrayscale(const CImg<unsigned char>& input,
    CImg<unsigned char>* output, const int patternSize);

  // Generate a rgb image as you would gain it from coloring an bayer filtered
  // grayscale image.
  // params: input - An RGB input image
  //         output - Reference to the colored bayer filtered image
  static void bayerColor(const CImg<unsigned char>& input,
    CImg<unsigned char>* output);

  // Downsample an rgb image.
  // params: input - Reference to the image you want to rescale
  //         ouput - Pointer to the object where your new image will be saved.
  //           The input will be downsampled to the size of this CImg object
  static void downsample(const CImg<unsigned char>& input,
    CImg<unsigned char>* output);

  // Upsample an rgb image. Therefore use no interpolation, i.e. each pixel
  // is rescaled without respect to it's neighbour pixels. The result is a
  // pixelated image.
  // params: input - Reference to the image you want to rescale
  //         ouput - Pointer to the object where your new image will be saved.
  //           The input will be upsampled to the size of this CImg object
  static void upsampleSimple(const CImg<unsigned char>& input,
    CImg<unsigned char>* output);

 private:
  // Get the filter color of a bayer filter at a given position
  // params: x - The x-value of the filter field of which you want to know the
  //           color
  //         y - The y-value of the filter field of which you want to know the
  //           color
  static Filter::Color getBayerPixelColor(int x, int y);
};

#endif  // SRC_FILTERS_FILTER_H_
