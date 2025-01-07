namespace raylib {
#include <raylib.h>
}

namespace themes {
struct theme {
  raylib::Color lightColor;
  raylib::Color darkColor;
  raylib::Color sideColor;
  raylib::Color foreColor;
  raylib::Color backColor;
  raylib::Color selectColor;
  raylib::Color moveColor;
};

extern theme wood;
extern theme classic;
extern theme blue;
extern theme green;
}; // namespace themes
