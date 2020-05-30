#include "ui.h"

UiPage &UiPage::AddElement(UiBase &element)
{
  this->uiElements.push_back(element);
  return *this;
}

void UiPage::DrawAllElements(U8G2 &u)
{
  for (UiBase &uiElement : uiElements)
  {
    uiElement.Draw(u);
  }
}