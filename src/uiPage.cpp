#include "ui.h"

UiPage &UiPage::AddElement(UiBase &element)
{
  this->ui_elements.push_back(element);
  return *this;
}

void UiPage::DrawAllElements()
{
  for (UiBase &uiElement : ui_elements)
  {
    uiElement.Draw();
  }
}