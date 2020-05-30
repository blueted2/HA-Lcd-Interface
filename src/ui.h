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
  int anchor_x, anchor_y; // The anchor points from which the corner points are calculated
  int width, height;
  UiAlign align;

  void UpdateCorners(); // Callled whenever any of the defining variables change

public:
  int x1, y1, x2, y2; // The two corner points of the bounding box

  BoundingBox(int anchor_x, int anchor_y, int width, int height, UiAlign align);

  BoundingBox &SetAnchorPoint(int anchor_x, int anchor_y);
  BoundingBox &SetSize(int width, int height);
};

/* Base class, from which all ui elements will inherit */
class UiBase
{
public:
  void virtual Draw(U8G2 &);
};

class UiPage
{
private:
  // Using std::reference_wrapper because a vector can't directly store references
  std::vector<std::reference_wrapper<UiBase>> uiElements; // Using vector so that the size is dynamic

public:
  void DrawAllElements(U8G2 &);
  UiPage &AddElement(UiBase &);
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
  /* Returning references to the current object to allow chaining */
  UiLabel &SetAnchorPosition(int anchor_x, int anchor_y);
  UiLabel &SetSize(int width, int height);
  UiLabel &SetText(const char *text);
  UiLabel &SetFont(uint8_t *font);

  UiLabel &SetDrawBorder(bool draw_border);
  UiLabel &SetBorderRadius(int border_radius);

  BoundingBox &GetBoundingBox();
};

#endif