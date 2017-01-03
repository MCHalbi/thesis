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
using std::ctime;
using std::clock;

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

  clock_t start;
  clock_t end;
  double duration[10][11] = {0};
  for (int rad = 0; rad <= 10; rad++) {
    for (int size = 1; size <= 10; size++) {
      start = clock();
      Filter::bayerArtifacts(image, &output, rad, size);
      end = clock();
      duration[size - 1][rad] =
        (end - start) / static_cast<double>(CLOCKS_PER_SEC) * 1000;
    }
  }

  double sum = 0;
  printf("                                             grid\n");
  printf("   ");
  for (int size = 1; size <= 10; size++) {
    if (size < 10) {
      printf("        %d", size);
    } else {
      printf("       %d", size);
    }
  }
  printf("\n");
  for (int rad = 0; rad <= 10; rad++) {
    if (rad < 10) {
      printf("  %d", rad);
    } else {
      printf(" %d", rad);
    }
    for (int size = 1; size <= 10; size++) {
      double curr = duration[size - 1][rad];
      if (curr < 10) {
        printf("    %.3f", curr);
      } else if (curr < 100) {
        printf("   %.3f", curr);
      } else if (curr < 1000) {
        printf("  %.3f", curr);
      } else {
        printf(" %.3f", curr);
      }
      sum += curr;
    }
    printf("\n");
  }
  printf("TOTAL TIME ELAPSED = %f\n", sum);
  return EXIT_SUCCESS;
}
