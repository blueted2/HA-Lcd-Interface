#include "ui.h"

BoundingBox::BoundingBox(int _anchor_x, int _anchor_y, int _width, int _height, UiAlign _align)
    : anchor_x(_anchor_x), anchor_y(_anchor_y), width(_width), height(_height), align(_align)
{
  UpdateCorners();
};

void BoundingBox::UpdateCorners()
{
  switch (align)
  {
  case left:
    break;
  case center:
    break;
  case right:
    break;
  }
}