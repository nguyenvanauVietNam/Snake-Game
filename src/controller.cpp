#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include "game.h" //[AuNV] (2023/10//06) add new code /

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite, bool &postion) const {
    //[AuNV] (2023/10//06) mod code -----> 
  /*if (snake.direction != opposite || snake.size == 1) snake.direction = input;*/
    if (postion)
    {
        if (snake.direction != input || snake.size == 1)
        {
            snake.direction = opposite;
        }
    }
    else
    {
        if (snake.direction != opposite || snake.size == 1)
        {
            snake.direction = input;
        }
    }
  //[AuNV] (2023/10//06) <----- 
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, Game& l_game) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown, l_game.m_position);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp, l_game.m_position);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight, l_game.m_position);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft, l_game.m_position);
          break;
        //[AuNV] (2023/10//06) add new code -----> 
        // Pause game
        case SDLK_ESCAPE:
            l_game.TriggerPause();
            break;
        //die if hit wall
        case SDLK_w:
            l_game.m_wall ? l_game.m_wall = false : l_game.m_wall = true;
            break;
        //[AuNV] (2023/10//06) <----- 
      }
    }
  }
}