#include "ui.h"

UiLabel::UiLabel(U8G2 *u, int anchor_x, int anchor_y, int width, int height)
{
  this->u = u;
  this->label_box.SetAnchorPoint(anchor_x, anchor_y).SetSize(width, height).SetAlignment(left);
}

void UiLabel::Draw()
{

  int x1 = this->label_box.x1;
  int y1 = this->label_box.y1;
  int width = this->label_box.GetWidth();
  int height = this->label_box.GetHeight();
  u->drawFrame(x1, y1, width, height);
}

UiLabel &UiLabel::SetAnchorPosition(int anchor_x, int anchor_y)
{
  this->label_box.SetAnchorPoint(anchor_x, anchor_y);
}

UiLabel &UiLabel::SetSize(int width, int height)
{
  this->label_box.SetSize(width, height);
  return *this;
}

UiLabel &UiLabel::SetText(String text)
{
  this->text = text;
  this->UpdateBoundingBox();
  return *this;
}

UiLabel &UiLabel::SetAutomaticBorderWidth(bool b)
{
  this->automatic_border_width = b;
  this->UpdateBoundingBox();
  return *this;
}
UiLabel &UiLabel::SetAutomaticBorderHeight(bool b)
{
  this->automatic_border_height = b;
  this->UpdateBoundingBox();
  return *this;
}

void UiLabel::UpdateBoundingBox()
{

  int width = this->label_box.GetWidth();
  int height = this->label_box.GetHeight();

  if (this->automatic_border_width)
  {
    width = this->text.length();
  }
}