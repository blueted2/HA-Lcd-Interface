#include "ui.h"

UiPage &UiPage::AddElement(UiBase &element)
{
  this->uiElements.push_back(element);
  return *this;
}

void UiPage::DrawAllElements()
{
  for (UiBase &uiElement : uiElements)
  {
    uiElement.Draw();
  }
}