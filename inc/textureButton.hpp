#include <string>

namespace raylib {
#include <raylib.h>
}

class textureButton {
public:
  textureButton(const std::string &texturePath, const raylib::Color &tint,
                float xPos, float yPos);
  void draw();
  bool isHovered();
  bool isClicked();

private:
  raylib::Texture texture;
  raylib::Color hoverTint;
  float x, y;
};
