#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer /*&renderer*/*renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  //[AuNV] (2023/10//06) add new code -----> 

  void TriggerPause();
  friend class Controller; // Controler can access this variable
protected:
    //wall around in screen
    bool m_wall;
  //[AuNV] (2023/10//06) <----- 

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  //[AuNV] (2023/10//06) mod code -----> 
  //void Update();
  void Update(Renderer* renderer);
  void Pause();
  void Resume();
  bool m_paused;
  bool m_position;
  //[AuNV] (2023/10//06) <----- 
};

#endif