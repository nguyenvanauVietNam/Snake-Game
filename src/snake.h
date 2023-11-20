#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  //Update score after snake eated
  Snake(int grid_width, int grid_height, int *score)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) ,
       m_score(score){}
 //[AuNV] (2023/10//06) add new code -----> 
 // void Update();
  void Update(bool* wall, SDL_Window* main_windows);
 //[AuNV] (2023/10//06) <----- 

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  //[AuNV] (2023/10//06) add new code -----> 
//   void UpdateHead();
  void UpdateHead(bool *wal,SDL_Window* main_windows);
//[AuNV] (2023/10//06) <----- 
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell, SDL_Window* main_windows);

  bool growing{false};
  int grid_width;
  int grid_height;
  int* m_score; //[AuNV] (2023/10//06) add new code /
};

#endif