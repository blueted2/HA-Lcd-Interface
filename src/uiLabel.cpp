#include "ui.h"

UiLabel::UiLabel(int anchor_x, int anchor_y, int width, int height)
{
  this->label_box.SetAnchorPoint(anchor_x, anchor_y).SetSize(width, height).SetAlignment(center);
}

void UiLabel::Draw(U8G2 &u)
{
  int x1 = this->label_box.x1;
  int y1 = this->label_box.y1;
  int width = this->label_box.GetWidth();
  int height = this->label_box.GetHeight();
  u.drawFrame(x1, y1, width, height);
}