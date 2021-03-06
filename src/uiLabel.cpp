#include "ui.h"

UiLabel::UiLabel(U8G2 *u, int anchor_x, int anchor_y, int width = -1, int height = -1, UiAlign align = left)
{
  this->u = u;
  if (width == -1)
  {
    this->SetAutomaticBorderWidth(true);
    width = 10;
  }

  if (height == -1)
  {
    this->SetAutomaticBorderHeight(true);
    height = 10;
  }

  this->UpdateBoundingBox();
  this->label_box.SetAnchorPoint(anchor_x, anchor_y).SetSize(width, height).SetAlignment(align);
}

UiLabel &UiLabel::SetAnchorPosition(int anchor_x, int anchor_y)
{
  this->label_box.SetAnchorPoint(anchor_x, anchor_y);
  return *this;
}

UiLabel &UiLabel::SetSize(int width, int height)
{
  this->label_box.SetSize(width, height);
  this->UpdateBoundingBox();
  return *this;
}
UiLabel &UiLabel::SetAlignement(UiAlign align)
{
  this->label_box.SetAlignment(align);
  this->UpdateBoundingBox();
  return *this;
}

UiLabel &UiLabel::SetText(String text)
{
  this->text = text;
  this->UpdateBoundingBox();
  return *this;
}

UiLabel &UiLabel::SetFont(const uint8_t *font)
{
  this->font = font;
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
  u->setFont(this->font);
  int width = this->label_box.GetWidth();
  int height = this->label_box.GetHeight();

  if (this->automatic_border_width)
  {
    width = this->u->getStrWidth(this->text.c_str()) + 4;
  }

  if (this->automatic_border_height)
  {
    height = u->getMaxCharHeight() + 4;
  }
  this->label_box.SetSize(width, height);
}

void UiLabel::Draw()
{
  u->setDrawColor(2);
  u->setBitmapMode(true /* transparent*/);
  u->setFont(this->font);
  int str_width = u->getStrWidth(this->text.c_str());
  int str_height = u->getMaxCharHeight();

  int x1 = this->label_box.x1;
  int y1 = this->label_box.y1;
  int width = this->label_box.GetWidth();
  int height = this->label_box.GetHeight();
  if (this->draw_border)
    u->drawFrame(x1, y1, width, height);

  int draw_y = y1 + str_height * 0.5 + height * 0.5 - 1;
  int draw_x = 0;

  switch (text_align)
  {
  case left:
    draw_x = x1 + 2;
    break;
  case center:
    draw_x = x1 + width * 0.5 - str_width * 0.5;
    break;
  case right:
    draw_x = x1 + width - str_width - 2;
    break;
  }

  u->drawUTF8(draw_x, draw_y, this->text.c_str());
}