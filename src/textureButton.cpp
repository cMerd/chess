#include <string>
#include <textureButton.hpp>

namespace raylib {
#include <raylib.h>
}

textureButton::textureButton(const std::string &texturePath,
                             const raylib::Color &tint, float xPos,
                             float yPos) {
  x = xPos;
  y = yPos;
  hoverTint = tint;
  texture = raylib::LoadTexture(texturePath.c_str());
}

bool textureButton::isHovered() {
  return raylib::CheckCollisionPointRec(
      raylib::GetMousePosition(),
      {x, y, (float)texture.width, (float)texture.height});
}

bool textureButton::isClicked() {
  return isHovered() and
         raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT);
}

void textureButton::draw() {
  raylib::DrawTexture(texture, x, y, raylib::WHITE);
  if (isHovered()) {
    raylib::DrawRectangleLinesEx(
        {x - 10, y - 10, (float)texture.width + 20, (float)texture.height + 20},
        10, hoverTint);
  }
}
