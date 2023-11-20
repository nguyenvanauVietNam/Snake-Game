#include <iostream>
#include <memory> //  smart pointer
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "logfile.h"

int main() {
   // using std::shared_ptr create smart pointer to l_logfile
   std::shared_ptr<CLogFile> l_logfile = std::make_shared<CLogFile>();
   
   // Main render
   SDL_Window* l_main_sdl_window;

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  
  // [AuNV] (2023/10/06) add new code /
  l_logfile->LogToFile("-----------Start game-----------");
  std::string l_Layer{"AuNV"};
  
  // Input user name
  std::cout << "Enter your name:" << std::endl;
  std::cin >> l_Layer;
  std::cout << "Welcome: " << l_Layer << std::endl;
  std::cout << "Game has started!\n";
  std::cout << "Press W: create wall/delete wall!\n";
  std::cout << "Press ESC: pause/resume!\n";
  
  // Run game
  game.Run(controller, &renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  l_logfile->LogToFile("Game has terminated successfully!");
  ///
  
  std::string nameString = "Your name:" + l_Layer;
  // Log user information and score
  l_logfile->LogToFile(nameString);
  std::string scoreString = "Score: " + std::to_string(game.GetScore());
  l_logfile->LogToFile(scoreString.c_str());
  std::string sizeString = "Size: " + std::to_string(game.GetSize());
  l_logfile->LogToFile(sizeString.c_str());
  l_logfile->LogToFile("-----------End game-----------");
  
  return 0;
}