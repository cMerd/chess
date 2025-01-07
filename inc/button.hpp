#include <string>

namespace raylib {
#include <raylib.h>
}

class button {
public:
  button(const raylib::Rectangle &hitbox, float radius, float fontSize,
         const raylib::Font &textFont, const std::string &label,
         const raylib::Color &foregroundColor,
         const raylib::Color &backgroundColor,
         const raylib::Color &hoveringColor,
         const raylib::Color &clickingColor);
  void draw();
  bool isHovered();
  bool isClicked();

private:
  raylib::Rectangle hitbox;
  raylib::Color foreColor;
  raylib::Color backColor;
  raylib::Color hoverColor;
  raylib::Color clickColor;
  raylib::Font font;
  std::string text;
  float rad;
  float fSize;
};
