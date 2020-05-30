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
    this->x1 = this->anchor_x;
    this->y1 = this->anchor_y;
    this->x2 = this->anchor_x + this->width;
    this->y2 = this->anchor_y + this->height;
    break;
  case center:
    this->x1 = this->anchor_x - this->width * 0.5;
    this->y1 = this->anchor_y;
    this->x2 = this->anchor_x + this->width * 0.5;
    this->y2 = this->anchor_y + this->height;
    break;
  case right:
    this->x1 = this->anchor_x - this->width;
    this->y1 = this->anchor_y;
    this->x2 = this->anchor_x;
    this->y2 = this->anchor_y + this->height;
    break;
  }
}

BoundingBox &BoundingBox::SetAnchorPoint(int anchor_x, int anchor_y)
{
  this->anchor_x = anchor_x;
  this->anchor_y = anchor_y;
  this->UpdateCorners();
  return *this;
}
BoundingBox &BoundingBox::SetSize(int width, int height)
{
  this->width = width;
  this->height = height;
  this->UpdateCorners();
  return *this;
}