#include <button.hpp>
#include <stdexcept>
#include <string>

namespace raylib {
#include <raylib.h>
}

button::button(const raylib::Rectangle &btnHitbox, float radius, float fontSize,
               const raylib::Font &textFont, const std::string &label,
               const raylib::Color &foregroundColor,
               const raylib::Color &backgroundColor,
               const raylib::Color &hoveringColor,
               const raylib::Color &clickingColor)
    : hitbox(btnHitbox), foreColor(foregroundColor), backColor(backgroundColor),
      hoverColor(hoveringColor), clickColor(clickingColor), font(textFont),
      text(label), rad(radius), fSize(fontSize) {
  raylib::Vector2 len = raylib::MeasureTextEx(font, text.c_str(), fSize, 1);
  if (len.x > hitbox.width or len.y > hitbox.height) {
    throw std::range_error("(button): Label does not fit into the hitbox.");
  }
}

bool button::isHovered() {
  return raylib::CheckCollisionPointRec(raylib::GetMousePosition(), hitbox);
}

bool button::isClicked() {
  return isHovered() and
         raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT);
}

void button::draw() {

  raylib::Vector2 len = raylib::MeasureTextEx(font, text.c_str(), fSize, 1);

  raylib::DrawRectangleRounded(
      hitbox, rad, 1,
      (isClicked() ? clickColor : (isHovered() ? hoverColor : backColor)));

  raylib::DrawTextEx(font, text.c_str(),
                     {hitbox.x + hitbox.width / 2 - len.x / 2,
                      hitbox.y + hitbox.height / 2 - len.y / 2},
                     fSize, 1, foreColor);
}
