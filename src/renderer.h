#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  //[AuNV] (2023/10//06) add new code -----> 
  //void Render(Snake const snake, SDL_Point const &food);
  void Render(Snake const snake, SDL_Point const& food, bool* wall, bool* poisoned);
  void SetPauseTitle();
  //[AuNV] (2023/10//06) <----- 
  void UpdateWindowTitle(int score, int fps);
  SDL_Window* GetMainWindow();
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *backgroundTexture;
  SDL_Texture *foodRender;
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif