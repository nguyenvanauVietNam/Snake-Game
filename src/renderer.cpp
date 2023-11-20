#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height){

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //load backgroup
  //LoadBackground("./resources/BGSnake.jpg");
  backgroundTexture = IMG_LoadTexture(sdl_renderer, "./resources/BGSnake.gif");
  if (!backgroundTexture) {
    std::cerr << "Failed to load background image.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  else{
    std::cout << "Load back ground success!" <<std::endl;
  }


}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}


//[AuNV] (2023/10//06) mod code -----> 
//void Renderer::Render(Snake const snake, SDL_Point const &food) {
void Renderer::Render(Snake const snake, SDL_Point const& food, bool* wall, bool *position) {
//[AuNV] (2023/10//06) <----- 
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  // Render the background
  SDL_RenderCopy(sdl_renderer, backgroundTexture, NULL, NULL);
  //[AuNV] (2023/10//06) add new code -----> 
  //Draw wall
  if (*wall)
  {
      SDL_SetRenderDrawColor(sdl_renderer, 0x7E, 0x41, 0x1F, 0xFF);
      SDL_Rect box = { 0 ,0 , 640 , 640 }; // limit wall around the window
      SDL_RenderDrawRect(sdl_renderer, &box);
   }
  //[AuNV] (2023/10//06) <----- 
  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  foodRender = IMG_LoadTexture(sdl_renderer, "./resources/Organe.gif");
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  SDL_RenderCopy(sdl_renderer, foodRender,NULL, &block);
  // Render snake's body
  //[AuNV] (2023/10//06) add new code -----> 
  if (*position)
  {
      SDL_SetRenderDrawColor(sdl_renderer, 0xBE, 0xD3, 0x3D, 0xFF);
  }
  else
  {
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  }
  //[AuNV] (2023/10//06) <----- 
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

//[AuNV] (2023/10//06) add new code -----> 
void Renderer::SetPauseTitle() {
    std::string title{ "GAME PAUSED press ESC to resume" };
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

SDL_Window* Renderer::GetMainWindow()
{
    return sdl_window;
}
//[AuNV] (2023/10//06) <----- 