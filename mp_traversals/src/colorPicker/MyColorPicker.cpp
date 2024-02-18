#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(HSLAPixel first, HSLAPixel second) {
  first_ = first;
  second_ = second;
}


/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  if (x%2 == 0) {
    return first_;
  } else {
    return second_;
  }

  return first_;
}
