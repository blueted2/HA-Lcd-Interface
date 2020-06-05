#include "ui.h"

UiProgressBar::UiProgressBar(U8G2 *u, int anchor_x, int anchor_y, int width, int height, UiAlign align = left)
{
  this->bounding_box.SetAnchorPoint(anchor_x, anchor_y).SetAlignment(align).SetSize(width, height);
  this->u = u;
}

UiProgressBar &UiProgressBar::SetValue(float value)
{
  this->value = value;
  return *this;
}

UiProgressBar &UiProgressBar::SetMaxValue(float value)
{
  this->max_value = value;
  return *this;
}

void UiProgressBar::Draw()
{
  int x1 = this->bounding_box.x1;
  int x2 = this->bounding_box.x2;
  int y1 = this->bounding_box.y1;
  int width = this->bounding_box.GetWidth();
  int height = this->bounding_box.GetHeight();
  u->drawFrame(x1, y1, width, height);
  u->setDrawColor(2);
  u->drawBox(x1 + 1, y1 + 1, (x2 - x1 - 2) * this->value / this->max_value, height - 2);
}