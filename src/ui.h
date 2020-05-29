#ifndef UI_H
#define UI_H

#include <U8g2lib.h>
#include <vector>

enum UiAlign
{
  left,
  center,
  right
};

/* Simple class to turn an anchor point, a width and height, and an alignement into 2 corner point of a rectangle */
class BoundingBox
{
private:
  int x1, y1, x2, y2;     // The two corner points of the bounding box
  int anchor_x, anchor_y; // The anchor points from which the corner points are calculated
  int width, height;
  UiAlign align;

public:
  BoundingBox(int anchor_x, int anchor_y, int width, int height, UiAlign align);
  //: anchor_x(anchor_x), anchor_y(anchor_y), width(width), height(height), align(align);

  int GetX1();
  int GetX2();
  int GetY1();
  int GetY2();
};

/* Base class, from which all ui elements will inherit */
class UiBase
{
public:
  void virtual Draw(U8G2 *);
};

class UiPage
{
private:
  std::vector<UiBase> uiElements; // Using vector so that the size is dynamic

public:
  void DrawAllElements();
};

class UiLabel : public UiBase
{
private:
  BoundingBox label_box;
  const char *text;
  uint8_t *font;
  bool draw_border;
  int border_radius;

public:
  void Draw();

  UiLabel &SetAnchorPosition(int, int);
  UiLabel &SetSize(int, int);
  UiLabel &SetText(const char *);
  UiLabel &SetFont(uint8_t *);

  UiLabel &SetDrawBorder(bool);
  UiLabel &SetBorderRadius(int);

  BoundingBox &GetBoundingBox();
};

#endif