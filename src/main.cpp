#include <algorithm>
#include <button.hpp>
#include <chess.hpp>
#include <cstdarg>
#include <fstream>
#include <menu.hpp>
#include <textureButton.hpp>
#include <theme.hpp>

namespace raylib {
#include <raylib.h>
}

int main() {

  constexpr float WINDOW_WIDTH = 1000;
  constexpr float WINDOW_HEIGHT = 800;
  constexpr float BUTTON_WIDTH = 300;
  constexpr float BUTTON_HEIGHT = 100;
  constexpr float SMALL_BUTTON_WIDTH = 150;
  constexpr float SMALL_BUTTON_HEIGHT = 50;
  constexpr char WINDOW_NAME[] = "Chess";

  MENU state = MENU::MAIN;
  bool shouldQuit = false, audio = true;
  chess game;
  themes::theme theme = themes::wood;
  std::string themeName;

  std::ifstream audioFile("data/audio");
  if (!audioFile) {
    std::ofstream audioData("data/audio");
    audioData << 1;
    audioData.close();
    audioFile.open("data/audio");
  }
  audioFile >> audio;

  std::ifstream themeFile("data/theme");
  if (!themeFile) {
    std::ofstream themeData("data/theme");
    themeData << "wood";
    themeData.close();
    themeFile.open("data/theme");
  }
  themeFile >> themeName;

  if (themeName == "wood") {
    theme = themes::wood;
  } else if (themeName == "classic") {
    theme = themes::classic;
  } else if (themeName == "blue") {
    theme = themes::blue;
  } else if (themeName == "green") {
    theme = themes::green;
  }

  raylib::InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
  raylib::InitAudioDevice();
  raylib::SetTargetFPS(60);
  raylib::SetExitKey(0);

  raylib::Font font =
      raylib::LoadFontEx("assets/FreeSansBold.otf", 70, nullptr, 0);
  raylib::Font btnFont =
      raylib::LoadFontEx("assets/FreeSansBold.otf", 45, nullptr, 0);
  raylib::Font sideFont =
      raylib::LoadFontEx("assets/FreeSansBold.otf", 20, nullptr, 0);

  raylib::Sound moveSound = raylib::LoadSound("assets/move.mp3");
  raylib::Sound captureSound = raylib::LoadSound("assets/capture.mp3");

  button quitBtn({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                  WINDOW_HEIGHT - BUTTON_HEIGHT * 1.5f, BUTTON_WIDTH,
                  BUTTON_HEIGHT},
                 0.3f, 45, btnFont, "Quit", theme.lightColor, theme.darkColor,
                 theme.sideColor, theme.lightColor);

  button settingsBtn({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                      WINDOW_HEIGHT - BUTTON_HEIGHT * 2.6f, BUTTON_WIDTH,
                      BUTTON_HEIGHT},
                     0.3f, 45, btnFont, "Settings", theme.lightColor,
                     theme.darkColor, theme.sideColor, theme.lightColor);

  button playBtn({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                  WINDOW_HEIGHT - BUTTON_HEIGHT * 3.7f, BUTTON_WIDTH,
                  BUTTON_HEIGHT},
                 0.3f, 45, btnFont, "Play", theme.lightColor, theme.darkColor,
                 theme.sideColor, theme.lightColor);

  button backBtn({20, 20, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT}, 0.3f, 20,
                 sideFont, "Back", theme.lightColor, theme.darkColor,
                 theme.sideColor, theme.lightColor);

  button backBtn2({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                   WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH,
                   BUTTON_HEIGHT},
                  0.3f, 45, btnFont, "Back", theme.lightColor, theme.darkColor,
                  theme.sideColor, theme.lightColor);

  button yesBtn({WINDOW_WIDTH / 2 - SMALL_BUTTON_WIDTH / 2, WINDOW_HEIGHT / 2,
                 SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT},
                0.3f, 20, sideFont, "On", theme.lightColor, theme.darkColor,
                theme.sideColor, theme.lightColor);

  button noBtn({WINDOW_WIDTH / 2 + SMALL_BUTTON_WIDTH, WINDOW_HEIGHT / 2,
                SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT},
               0.3f, 20, sideFont, "Off", theme.lightColor, theme.darkColor,
               theme.sideColor, theme.lightColor);

  button continueBtn({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                      WINDOW_HEIGHT / 2 - BUTTON_HEIGHT, BUTTON_WIDTH,
                      BUTTON_HEIGHT},
                     0.3f, 45, btnFont, "Continue", theme.lightColor,
                     theme.darkColor, theme.sideColor, theme.lightColor);

  button gotoMenuBtn({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                      WINDOW_HEIGHT / 2 + BUTTON_HEIGHT, BUTTON_WIDTH,
                      BUTTON_HEIGHT},
                     0.3f, 45, btnFont, "Go to menu", theme.lightColor,
                     theme.darkColor, theme.sideColor, theme.lightColor);

  textureButton woodButton("assets/Wood.png", themes::wood.sideColor, 100,
                           WINDOW_HEIGHT - 300);
  textureButton classicButton("assets/Classic.png", themes::classic.sideColor,
                              300, WINDOW_HEIGHT - 300);
  textureButton blueButton("assets/Blue.png", themes::blue.sideColor, 500,
                           WINDOW_HEIGHT - 300);
  textureButton greenButton("assets/Green.png", themes::green.sideColor, 700,
                            WINDOW_HEIGHT - 300);

  textureButton lightQueenButton("assets/light_queen.png", theme.selectColor,
                                 170, 400);
  textureButton lightRookButton("assets/light_rook.png", theme.selectColor, 290,
                                400);
  textureButton lightBishopButton("assets/light_bishop.png", theme.selectColor,
                                  410, 400);
  textureButton lightKnightButton("assets/light_knight.png", theme.selectColor,
                                  530, 400);
  textureButton darkQueenButton("assets/dark_queen.png", theme.selectColor, 170,
                                400);
  textureButton darkRookButton("assets/dark_rook.png", theme.selectColor, 290,
                               400);
  textureButton darkBishopButton("assets/dark_bishop.png", theme.selectColor,
                                 410, 400);
  textureButton darkKnightButton("assets/dark_knight.png", theme.selectColor,
                                 530, 400);

  raylib::Texture darkRook = raylib::LoadTexture("assets/dark_rook.png");
  raylib::Texture darkKnight = raylib::LoadTexture("assets/dark_knight.png");
  raylib::Texture darkBishop = raylib::LoadTexture("assets/dark_bishop.png");
  raylib::Texture darkQueen = raylib::LoadTexture("assets/dark_queen.png");
  raylib::Texture darkKing = raylib::LoadTexture("assets/dark_king.png");
  raylib::Texture darkPawn = raylib::LoadTexture("assets/dark_pawn.png");

  raylib::Texture lightRook = raylib::LoadTexture("assets/light_rook.png");
  raylib::Texture lightKnight = raylib::LoadTexture("assets/light_knight.png");
  raylib::Texture lightBishop = raylib::LoadTexture("assets/light_bishop.png");
  raylib::Texture lightQueen = raylib::LoadTexture("assets/light_queen.png");
  raylib::Texture lightKing = raylib::LoadTexture("assets/light_king.png");
  raylib::Texture lightPawn = raylib::LoadTexture("assets/light_pawn.png");

  while (!raylib::WindowShouldClose() and !shouldQuit) {
    raylib::ClearBackground(theme.backColor);
    raylib::BeginDrawing();

    switch (state) {
    case MENU::MAIN:
      raylib::DrawTextEx(
          font, "Chess",
          {500 - raylib::MeasureTextEx(font, "Chess", 70, 0).x / 2, 100}, 70, 0,
          theme.foreColor);

      quitBtn.draw();
      settingsBtn.draw();
      playBtn.draw();

      if (quitBtn.isClicked()) {
        if (audio) {
          raylib::PlaySound(moveSound);
        }
        shouldQuit = true;
      } else if (settingsBtn.isClicked()) {
        if (audio) {
          raylib::PlaySound(moveSound);
        }
        state = MENU::SETTINGS;
      } else if (playBtn.isClicked()) {
        if (audio) {
          raylib::PlaySound(moveSound);
        }
        state = MENU::GAME;
        game = chess();
      }

      break;
    case MENU::SETTINGS:
      backBtn.draw();
      woodButton.draw();
      classicButton.draw();
      blueButton.draw();
      greenButton.draw();
      yesBtn.draw();
      noBtn.draw();

      raylib::DrawTextEx(
          btnFont, "Audio",
          {WINDOW_WIDTH / 2 - SMALL_BUTTON_WIDTH * 2, WINDOW_HEIGHT / 2}, 45, 1,
          theme.foreColor);

      if (yesBtn.isClicked()) {
        if (audio) {
          raylib::PlaySound(captureSound);
        }
        audio = true;

        std::ofstream audioData("data/audio");
        audioData << 1;
        audioData.close();
      } else if (noBtn.isClicked()) {
        if (audio) {
          raylib::PlaySound(captureSound);
        }
        audio = false;

        std::ofstream audioData("data/audio");
        audioData << 0;
        audioData.close();
      } else if (backBtn.isClicked() or
                 raylib::IsKeyPressed(raylib::KEY_ESCAPE)) {
        if (audio) {
          raylib::PlaySound(captureSound);
        }
        state = MENU::MAIN;
      } else if (woodButton.isClicked()) {
        if (audio) {
          raylib::PlaySound(captureSound);
        }
        theme = themes::wood;

        std::ofstream themeData("data/theme");
        themeData << "wood";
        themeData.close();
      } else if (classicButton.isClicked()) {
        if (audio) {
          raylib::PlaySound(captureSound);
        }
        theme = themes::classic;

        std::ofstream themeData("data/theme");
        themeData << "classic";
        themeData.close();
      } else if (blueButton.isClicked()) {
        if (audio) {
          raylib::PlaySound(captureSound);
        }
        theme = themes::blue;

        std::ofstream themeData("data/theme");
        themeData << "blue";
        themeData.close();
      } else if (greenButton.isClicked()) {
        if (audio) {
          raylib::PlaySound(captureSound);
        }
        theme = themes::green;

        std::ofstream themeData("data/theme");
        themeData << "green";
        themeData.close();
      }

      if (woodButton.isClicked() or classicButton.isClicked() or
          blueButton.isClicked() or greenButton.isClicked()) {
        quitBtn = button({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                          WINDOW_HEIGHT - BUTTON_HEIGHT * 1.5f, BUTTON_WIDTH,
                          BUTTON_HEIGHT},
                         0.3f, 45, btnFont, "Quit", theme.lightColor,
                         theme.darkColor, theme.sideColor, theme.lightColor);
        settingsBtn = button(
            {WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
             WINDOW_HEIGHT - BUTTON_HEIGHT * 2.6f, BUTTON_WIDTH, BUTTON_HEIGHT},
            0.3f, 45, btnFont, "Settings", theme.lightColor, theme.darkColor,
            theme.sideColor, theme.lightColor);
        playBtn = button({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                          WINDOW_HEIGHT - BUTTON_HEIGHT * 3.7f, BUTTON_WIDTH,
                          BUTTON_HEIGHT},
                         0.3f, 45, btnFont, "Play", theme.lightColor,
                         theme.darkColor, theme.sideColor, theme.lightColor);
        backBtn = button({20, 20, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT},
                         0.3f, 25, btnFont, "Back", theme.lightColor,
                         theme.darkColor, theme.sideColor, theme.lightColor);
        backBtn2 = button({WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
                           WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH,
                           BUTTON_HEIGHT},
                          0.3f, 45, btnFont, "Back", theme.lightColor,
                          theme.darkColor, theme.sideColor, theme.lightColor);

        yesBtn =
            button({WINDOW_WIDTH / 2 - SMALL_BUTTON_WIDTH / 2,
                    WINDOW_HEIGHT / 2, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT},
                   0.3f, 20, sideFont, "On", theme.lightColor, theme.darkColor,
                   theme.sideColor, theme.lightColor);

        noBtn =
            button({WINDOW_WIDTH / 2 + SMALL_BUTTON_WIDTH, WINDOW_HEIGHT / 2,
                    SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT},
                   0.3f, 20, sideFont, "Off", theme.lightColor, theme.darkColor,
                   theme.sideColor, theme.lightColor);

        continueBtn = button(
            {WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
             WINDOW_HEIGHT / 2 - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT},
            0.3f, 45, btnFont, "Continue", theme.lightColor, theme.darkColor,
            theme.sideColor, theme.lightColor);

        gotoMenuBtn = button(
            {WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
             WINDOW_HEIGHT / 2 + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT},
            0.3f, 45, btnFont, "Go to menu", theme.lightColor, theme.darkColor,
            theme.sideColor, theme.lightColor);
      }

      break;
    case MENU::PAUSE:
      raylib::DrawTextEx(
          font, "Paused",
          {WINDOW_WIDTH / 2 -
               raylib::MeasureTextEx(font, "Paused", 70, 1).x / 2,
           50},
          70, 1, theme.foreColor);

      continueBtn.draw();
      gotoMenuBtn.draw();

      if (continueBtn.isClicked()) {
        state = MENU::GAME;

        if (audio) {
          raylib::PlaySound(moveSound);
        }
      } else if (gotoMenuBtn.isClicked()) {
        state = MENU::MAIN;

        if (audio) {
          raylib::PlaySound(moveSound);
        }
      }
      break;
    case MENU::GAME: {

      if (raylib::IsKeyPressed(raylib::KEY_ESCAPE)) {
        state = MENU::PAUSE;
      }

      raylib::DrawRectangle(0, 0, 800, 40, theme.sideColor);
      raylib::DrawRectangle(0, 0, 40, 800, theme.sideColor);
      raylib::DrawRectangle(0, 760, 800, 40, theme.sideColor);
      raylib::DrawRectangle(760, 0, 40, 800, theme.sideColor);

      for (int i = 1; i <= 8; i++) {
        raylib::DrawTextEx(
            sideFont, std::to_string(i).c_str(),
            {20 - raylib::MeasureTextEx(sideFont, std::to_string(i).c_str(), 20,
                                        1)
                          .x /
                      2,
             WINDOW_HEIGHT - (40 + i * 90 - 22.5f -
                              raylib::MeasureTextEx(
                                  sideFont, std::to_string(i).c_str(), 20, 1)
                                      .y /
                                  2)},
            20, 1, theme.foreColor);

        raylib::DrawTextEx(
            sideFont, std::to_string(i).c_str(),
            {780 - raylib::MeasureTextEx(sideFont, std::to_string(i).c_str(),
                                         20, 1)
                           .x /
                       2,
             WINDOW_HEIGHT - (40 + i * 90 - 22.5f -
                              raylib::MeasureTextEx(
                                  sideFont, std::to_string(i).c_str(), 20, 1)
                                      .y /
                                  2)},
            20, 1, theme.foreColor);

        raylib::DrawTextEx(
            sideFont, std::string(1, 'a' + i - 1).c_str(),
            {40 + i * 90 - 45 -
                 raylib::MeasureTextEx(
                     sideFont, std::string(1, 'a' + i - 1).c_str(), 20, 1)
                         .x /
                     2,
             780 - raylib::MeasureTextEx(
                       sideFont, std::string(1, 'a' + i - 1).c_str(), 20, 1)
                           .y /
                       2},
            20, 1, theme.foreColor);

        raylib::DrawTextEx(
            sideFont, std::string(1, 'a' + i - 1).c_str(),
            {40 + i * 90 - 45 -
                 raylib::MeasureTextEx(
                     sideFont, std::string(1, 'a' + i - 1).c_str(), 20, 1)
                         .x /
                     2,
             20 - raylib::MeasureTextEx(
                      sideFont, std::string(1, 'a' + i - 1).c_str(), 20, 1)
                          .y /
                      2},
            20, 1, theme.foreColor);
      }

      std::vector<std::pair<int, int>> moves;
      bool ended = false;

      if (game.isSelected) {
        moves = game.getMoves(game.selected.first, game.selected.second);
      }

      if (game.isCheckMate(chess::color::light) or
          game.isCheckMate(chess::color::dark) or
          game.isStaleMate(chess::color::light) or
          game.isStaleMate(chess::color::dark)) {
        ended = true;
        game.isSelected = false;
        game.selected = {-1, -1};
      }

      for (size_t i = 0; i < game.board.size(); i++) {
        for (size_t j = 0; j < game.board[i].size(); j++) {
          if (!ended and !game.switching and
              raylib::CheckCollisionPointRec(
                  raylib::GetMousePosition(),
                  {(float)(90 * j + 40), (float)(90 * i + 40), 90, 90}) and
              raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT)) {
            if (game.board[i][j].col == game.turn) {
              game.isSelected = true;
              game.selected = {i, j};
            } else if (game.isSelected) {
              if (std::find(moves.begin(), moves.end(),
                            std::pair<int, int>{i, j}) != moves.end()) {

                bool castled = false;

                if (game.canDarkCastle1 and game.selected.first == 0 and
                    game.selected.second == 4 and i == 0 and j == 1 and
                    game.board[game.selected.first][game.selected.second]
                            .type == chess::piece::king and
                    game.board[game.selected.first][game.selected.second].col ==
                        chess::color::dark) {
                  game.move(0, 0, 0, 2);
                  game.canDarkCastle1 = false;
                  castled = true;
                  game.moves.push_back("0-0-0");
                }

                if (game.canDarkCastle2 and game.selected.first == 0 and
                    game.selected.second == 4 and i == 0 and j == 6 and
                    game.board[game.selected.first][game.selected.second]
                            .type == chess::piece::king and
                    game.board[game.selected.first][game.selected.second].col ==
                        chess::color::dark) {
                  game.move(0, 7, 0, 5);
                  game.canDarkCastle2 = false;
                  castled = true;
                  game.moves.push_back("0-0");
                }

                if (game.canLightCastle1 and game.selected.first == 7 and
                    game.selected.second == 4 and i == 7 and j == 1 and
                    game.board[game.selected.first][game.selected.second]
                            .type == chess::piece::king and
                    game.board[game.selected.first][game.selected.second].col ==
                        chess::color::light) {
                  game.move(7, 0, 7, 2);
                  game.canLightCastle1 = false;
                  castled = true;
                  game.moves.push_back("0-0-0");
                }

                if (game.canLightCastle2 and game.selected.first == 7 and
                    game.selected.second == 4 and i == 7 and j == 6 and
                    game.board[game.selected.first][game.selected.second]
                            .type == chess::piece::king and
                    game.board[game.selected.first][game.selected.second].col ==
                        chess::color::light) {
                  game.move(7, 7, 7, 5);
                  game.canLightCastle2 = false;
                  castled = true;
                  game.moves.push_back("0-0");
                }

                if (audio) {
                  if (game.board[i][j].type == chess::piece::null) {
                    raylib::PlaySound(moveSound);
                  } else {
                    raylib::PlaySound(captureSound);
                  }
                }

                std::string moveNotation =
                    game.move(game.selected.first, game.selected.second, i, j);

                if (!castled) {
                  game.moves.push_back(moveNotation);
                }

                int height = 0;

                for (const std::string &move : game.moves) {
                  height +=
                      raylib::MeasureTextEx(sideFont, move.c_str(), 20, 1).y +
                      10;
                }

                if (height > WINDOW_HEIGHT) {
                  game.moves.pop_front();
                }

                if (game.canLightCastle1 and game.selected.first == 7 and
                    game.selected.second == 0 and
                    game.board[i][j].type == chess::piece::rook and
                    game.board[i][j].col == chess::color::light) {
                  game.canLightCastle1 = false;
                }

                if (game.canLightCastle2 and game.selected.first == 7 and
                    game.selected.second == 7 and
                    game.board[i][j].type == chess::piece::rook and
                    game.board[i][j].col == chess::color::light) {
                  game.canLightCastle2 = false;
                }

                if ((game.canLightCastle1 or game.canLightCastle2) and
                    game.selected.first == 7 and game.selected.second == 4 and
                    game.board[i][j].type == chess::piece::king and
                    game.board[i][j].col == chess::color::light) {
                  game.canLightCastle1 = game.canLightCastle2 = false;
                }

                if (game.canDarkCastle1 and game.selected.first == 0 and
                    game.selected.second == 0 and
                    game.board[i][j].type == chess::piece::rook and
                    game.board[i][j].col == chess::color::dark) {
                  game.canDarkCastle1 = false;
                }

                if (game.canDarkCastle2 and game.selected.first == 0 and
                    game.selected.second == 0 and
                    game.board[i][j].type == chess::piece::rook and
                    game.board[i][j].col == chess::color::dark) {
                  game.canDarkCastle2 = false;
                }

                if ((game.canDarkCastle1 or game.canDarkCastle1) and
                    game.selected.first == 0 and game.selected.second == 4 and
                    game.board[i][j].type == chess::piece::king and
                    game.board[i][j].col == chess::color::dark) {
                  game.canDarkCastle1 = game.canDarkCastle2 = false;
                }

                if (game.board[i][j].type == chess::piece::pawn) {
                  if ((game.board[i][j].col == chess::color::light and
                       i == 0) or
                      (game.board[i][j].col == chess::color::dark and i == 7)) {
                    game.switching = true;
                    game.switcher = {i, j};
                  }
                }
                game.isSelected = false;
                game.selected = {-1, -1};
                game.turn =
                    (game.turn == chess::color::light ? chess::color::dark
                                                      : chess::color::light);
              } else {
                game.isSelected = false;
                game.selected = {-1, -1};
              }
            }
          }

          if (game.board[i][j].type == chess::piece::king and
              game.turn == game.board[i][j].col and
              game.isInCheck(game.board[i][j].col)) {
            raylib::DrawRectangle(90 * j + 40, 90 * i + 40, 90, 90,
                                  {232, 16, 16, 255});
          } else if (game.isSelected and game.selected.first == (int)i and
                     game.selected.second == (int)j) {

            raylib::DrawRectangle(90 * j + 40, 90 * i + 40, 90, 90,
                                  theme.selectColor);
          } else {
            raylib::DrawRectangle(
                90 * j + 40, 90 * i + 40, 90, 90,
                (i % 2 == 0
                     ? (j % 2 == 0 ? theme.lightColor : theme.darkColor)
                     : (j % 2 == 0 ? theme.darkColor : theme.lightColor)));
          }

          switch (game.board[i][j].type) {
          case chess::piece::knight:
            raylib::DrawTexture((game.board[i][j].col == chess::color::dark
                                     ? darkKnight
                                     : lightKnight),
                                90 * j + 35, 90 * i + 35, raylib::WHITE);
            break;
          case chess::piece::king:
            raylib::DrawTexture((game.board[i][j].col == chess::color::dark
                                     ? darkKing
                                     : lightKing),
                                90 * j + 35, 90 * i + 35, raylib::WHITE);
            break;
          case chess::piece::pawn:
            raylib::DrawTexture((game.board[i][j].col == chess::color::dark
                                     ? darkPawn
                                     : lightPawn),
                                90 * j + 35, 90 * i + 35, raylib::WHITE);
            break;
          case chess::piece::rook:
            raylib::DrawTexture((game.board[i][j].col == chess::color::dark
                                     ? darkRook
                                     : lightRook),
                                90 * j + 35, 90 * i + 35, raylib::WHITE);
            break;
          case chess::piece::queen:
            raylib::DrawTexture((game.board[i][j].col == chess::color::dark
                                     ? darkQueen
                                     : lightQueen),
                                90 * j + 35, 90 * i + 35, raylib::WHITE);
            break;
          case chess::piece::bishop:
            raylib::DrawTexture((game.board[i][j].col == chess::color::dark
                                     ? darkBishop
                                     : lightBishop),
                                90 * j + 35, 90 * i + 35, raylib::WHITE);
            break;
          case chess::piece::null:
            break;
          }
        }
      }

      for (const auto &[x, y] : moves) {
        raylib::DrawCircle(90 * y + 85, 90 * x + 85, 20,
                           (game.board[x][y].col != chess::color::null
                                ? raylib::Color{232, 16, 16, 180}
                                : raylib::Color{130, 130, 130, 180}));
      }

      if (ended) {
        backBtn2.draw();

        if (game.isCheckMate(chess::color::light)) {
          raylib::DrawTextEx(
              font, "Dark won!",
              {WINDOW_WIDTH / 2 -
                   raylib::MeasureTextEx(font, "Dark won!", 70, 1).x / 2,
               WINDOW_HEIGHT / 2 -
                   raylib::MeasureTextEx(font, "Dark won!", 70, 1).y / 2 -
                   BUTTON_HEIGHT - 50},
              70, 1, theme.foreColor);
        } else if (game.isCheckMate(chess::color::dark)) {
          raylib::DrawTextEx(
              font, "Light won!",
              {WINDOW_WIDTH / 2 -
                   raylib::MeasureTextEx(font, "Light won!", 70, 1).x / 2,
               WINDOW_HEIGHT / 2 -
                   raylib::MeasureTextEx(font, "Light won!", 70, 1).y / 2 -
                   BUTTON_HEIGHT - 50},
              70, 1, theme.foreColor);
        } else if (game.isStaleMate(chess::color::light)) {
          raylib::DrawTextEx(
              font, "Draw.",
              {WINDOW_WIDTH / 2 -
                   raylib::MeasureTextEx(font, "Draw.", 70, 1).x / 2,
               WINDOW_HEIGHT / 2 -
                   raylib::MeasureTextEx(font, "Draw.", 70, 1).y / 2 -
                   BUTTON_HEIGHT - 50},
              70, 1, theme.foreColor);
        } else if (game.isStaleMate(chess::color::dark)) {
          raylib::DrawTextEx(
              font, "Draw.",
              {WINDOW_WIDTH / 2 -
                   raylib::MeasureTextEx(font, "Draw.", 70, 1).x / 2,
               WINDOW_HEIGHT / 2 -
                   raylib::MeasureTextEx(font, "Draw.", 70, 1).y / 2 -
                   BUTTON_HEIGHT - 50},
              70, 1, theme.foreColor);
        }

        if (backBtn2.isClicked() or raylib::IsKeyPressed(raylib::KEY_ESCAPE)) {
          if (audio) {
            raylib::PlaySound(moveSound);
          }
          state = MENU::MAIN;
        }
      }

      if (game.switching) {
        raylib::DrawRectangle(150, 300, 500, 220, theme.backColor);
        raylib::DrawTextEx(
            sideFont, "Choose a piece to promote",
            {400 - raylib::MeasureTextEx(sideFont, "Choose a piece to promote",
                                         20, 1)
                           .x /
                       2,
             320},
            20, 1, theme.foreColor);

        if (game.board[game.switcher.first][game.switcher.second].col ==
            chess::color::light) {
          lightQueenButton.draw();
          lightRookButton.draw();
          lightBishopButton.draw();
          lightKnightButton.draw();

          if (lightQueenButton.isClicked()) {
            if (audio) {
              raylib::PlaySound(moveSound);
            }
            game.board[game.switcher.first][game.switcher.second] = {
                chess::piece::queen, chess::color::light};
            game.switcher = {-1, -1};
            game.selected = {-1, -1};
            game.switching = false;
            game.isSelected = false;
          } else if (lightRookButton.isClicked()) {
            if (audio) {
              raylib::PlaySound(moveSound);
            }
            game.board[game.switcher.first][game.switcher.second] = {
                chess::piece::rook, chess::color::light};
            game.switcher = {-1, -1};
            game.selected = {-1, -1};
            game.switching = false;
            game.isSelected = false;
          } else if (lightBishopButton.isClicked()) {
            if (audio) {
              raylib::PlaySound(moveSound);
            }
            game.board[game.switcher.first][game.switcher.second] = {
                chess::piece::bishop, chess::color::light};
            game.switcher = {-1, -1};
            game.selected = {-1, -1};
            game.switching = false;
            game.isSelected = false;
          } else if (lightKnightButton.isClicked()) {
            if (audio) {
              raylib::PlaySound(moveSound);
            }
            game.board[game.switcher.first][game.switcher.second] = {
                chess::piece::knight, chess::color::light};
            game.switcher = {-1, -1};
            game.selected = {-1, -1};
            game.switching = false;
            game.isSelected = false;
          }
        } else {
          darkQueenButton.draw();
          darkRookButton.draw();
          darkBishopButton.draw();
          darkKnightButton.draw();

          if (darkQueenButton.isClicked()) {
            if (audio) {
              raylib::PlaySound(moveSound);
            }
            game.board[game.switcher.first][game.switcher.second] = {
                chess::piece::queen, chess::color::dark};
            game.switcher = {-1, -1};
            game.selected = {-1, -1};
            game.switching = false;
            game.isSelected = false;
          } else if (darkRookButton.isClicked()) {
            if (audio) {
              raylib::PlaySound(moveSound);
            }
            game.board[game.switcher.first][game.switcher.second] = {
                chess::piece::rook, chess::color::dark};
            game.switcher = {-1, -1};
            game.selected = {-1, -1};
            game.switching = false;
            game.isSelected = false;
          } else if (darkBishopButton.isClicked()) {
            if (audio) {
              raylib::PlaySound(moveSound);
            }
            game.board[game.switcher.first][game.switcher.second] = {
                chess::piece::bishop, chess::color::dark};
            game.switcher = {-1, -1};
            game.selected = {-1, -1};
            game.switching = false;
            game.isSelected = false;
          } else if (darkKnightButton.isClicked()) {
            if (audio) {
              raylib::PlaySound(moveSound);
            }
            game.board[game.switcher.first][game.switcher.second] = {
                chess::piece::knight, chess::color::dark};
            game.switcher = {-1, -1};
            game.selected = {-1, -1};
            game.switching = false;
            game.isSelected = false;
          }
        }
      }

      float yPos = 0;
      for (const std::string &move : game.moves) {
        raylib::DrawTextEx(sideFont, move.c_str(), {820, yPos}, 20, 1,
                           theme.foreColor);
        yPos += raylib::MeasureTextEx(sideFont, move.c_str(), 20, 1).y + 10;
      }

      break;
    }
    default:
      break;
    }

    raylib::EndDrawing();
  }

  raylib::UnloadFont(font);
  raylib::UnloadFont(btnFont);
  raylib::CloseAudioDevice();
  raylib::CloseWindow();
  return 0;
}
