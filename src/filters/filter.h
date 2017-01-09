// Copyright 2016
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#ifndef SRC_FILTERS_FILTER_H_
#define SRC_FILTERS_FILTER_H_

#include <CImg/CImg.h>

using cimg_library::CImg;

class Filter {
 public:
  enum Color {RED, GREEN, BLUE};

  // Constructor
  Filter();

  // Generate an image with color artifacts as caused by an bayer filter
  // This is obtained by adding a bayer filter to the image and then
  // interpolating the pixel values with the colors of this filtered image
  // params: input - An RGB input image
  //         output - Reference to the image with artifacts
  //         radius - Interpolation radius
  static void bayerArtifacts(const CImg<unsigned char>& input,
    CImg<unsigned char>* output, const int radius);

  // Generate an image with color artifacts as caused by an bayer filter with
  // given grid size. This is obtained by adding a bayer filter to the image and
  // then interpolating the pixel values with the colors of this filtered image.
  // params: input - An RGB input image
  //         output - Reference to the image with artifacts
  //         gridSize - Grid size of the bayer filter. The grid size refers to
  //           the size of one color field, i. e. a green, red or blue filter
  //           tile measures gridSize * gridSize pixels
  static void bayerArtifacts(const CImg<unsigned char>& input,
    CImg<unsigned char>* output, const int radius, const int gridSize);

  // Generate a grayscale image as an bayer filter would generate it on an
  // image sensor.
  // params: input - An RGB input image
  //         output - Reference to the filtered grayscale image
  static void bayerGrayscale(const CImg<unsigned char>& input,
    CImg<unsigned char>* output);

  // Generate a grayscale image as an bayer filter would generate it on an
  // image sensor. The size of the bayer pattern can be choosen.
  // params: input - An RGB input image
  //         output - The filtered grayscale image
  //         gridSize - The grid size of the bayer filter. This parameter
  //           specifies the size of one field in the pattern, not of one GRBG
  //           field group
  static void bayerGrayscale(const CImg<unsigned char>& input,
    CImg<unsigned char>* output, const int gridSize);

  // Generate a rgb image as you would gain it from coloring an bayer filtered
  // grayscale image.
  // params: input - An RGB input image
  //         output - The colored bayer filtered image
  static void bayerColor(const CImg<unsigned char>& input,
    CImg<unsigned char>* output);

  // Generate a rgb image as you would gain it from coloring an bayer filtered
  // grayscale image with a given filter grid size.
  // params: input - A reference to the input image
  //         output - Pointer to the output image
  //         gridSize - Grid size of the bayer filter. The grid size refers to
  //           the size of one color field, i. e. a green, red or blue filter
  //           tile measures gridSize * gridSize pixels
  static void bayerColor(const CImg<unsigned char>& input,
    CImg<unsigned char>* output, const int filterSize);

  // Apply an fisheye effect on the image.
  // params: input -
  //         output -
  static void rectilinearToFisheye(const CImg<unsigned char>& input,
    CImg<unsigned char>* output, int radius);

  // Correct image distortion caused by fisheye effect
  static void fisheyeToRectilinear(const CImg<unsigned char>& input,
    CImg<unsigned char>* output, int radius);

 private:
  // Get the filter color of a bayer filter at a given position
  // params: x - The x-value of the filter field of which you want to know the
  //           color
  //         y - The y-value of the filter field of which you want to know the
  //           color
  static Filter::Color getBayerPixelColor(const int x, const int y);

  // Get the distance from the center of a square width sidelength 2 * radius
  // to the edge of the square in direction (x, y). The origin of the
  // coordinate system lies in the center of the square.
  // param: x - x coordinate of the direction
  //        y - y coordinate oif the direction
  //        radius - Half sidelength of the square / radius of the inscribed
  //          circle of the square
  static float getMaxLength(int x, int y, int radius);
};

#endif  // SRC_FILTERS_FILTER_H_
