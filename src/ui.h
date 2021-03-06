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
  UiAlign align; // Where box is located relative to its anchor points

  void UpdateCorners(); // Callled whenever any of the defining variables change

public:
  int x1, y1, x2, y2; // The two corner points of the bounding box

  BoundingBox(int anchor_x, int anchor_y, int width, int height, UiAlign align);

  BoundingBox &SetAnchorPoint(int anchor_x, int anchor_y);
  BoundingBox &SetSize(int width, int height);
  BoundingBox &SetAlignment(UiAlign align);

  int GetWidth();
  int GetHeight();
};

/* Base class, from which all ui elements will inherit */
class UiBase
{
public:
  virtual void Draw();
};

class UiPage
{
private:
  // Using std::reference_wrapper because a vector can't directly store references
  std::vector<std::reference_wrapper<UiBase>> ui_elements; // Using vector so that the size is dynamic
  
public:
  void DrawAllElements();
  UiPage &AddElement(UiBase &);
};

class UiLabel : public UiBase
{
private:
  String text = "Default asgdasdgsad";
  bool automatic_border_height = false;
  bool automatic_border_width = false;
  U8G2 *u; // Pointer instead of reference because you can't have a reference without initilising the object
  UiAlign text_align = center;

public:
  BoundingBox label_box = BoundingBox(0, 0, 0, 0, left);
  const uint8_t *font = u8g2_font_6x10_tf;
  bool draw_border = false;
  int border_radius = 2;
  UiLabel(U8G2 *u, int anchor_x, int anchor_y, int width, int height, UiAlign center);

  /* Returning references to the current object to allow chaining */
  UiLabel &SetAnchorPosition(int anchor_x, int anchor_y);
  UiLabel &SetSize(int width, int height);
  UiLabel &SetAlignement(UiAlign align);
  UiLabel &SetText(String text);
  UiLabel &SetFont(const uint8_t *);

  UiLabel &SetAutomaticBorderWidth(bool);
  UiLabel &SetAutomaticBorderHeight(bool);

  void UpdateBoundingBox();

  virtual void Draw();
};

class UiProgressBar : public UiBase
{
private:
  U8G2 *u;
  float max_value = 1;
  float value = 0;

public:
  UiProgressBar(U8G2 *u, int anchor_x, int anchor_y, int width, int height, UiAlign align);
  BoundingBox bounding_box = BoundingBox(0, 0, 0, 0, left);

  UiProgressBar &SetText(String text);
  UiProgressBar &SetValue(float value);
  UiProgressBar &SetMaxValue(float max_value);

  void UpdateBoundingBox();

  virtual void Draw();
};



#endif