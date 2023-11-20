#include "game.h"
#include <iostream>
#include "SDL.h"
//[AuNV] (2023/10//06) add new code -----> 
#include <thread>
#include <chrono>
#include <future>
//[AuNV] (2023/10//06) <----- 
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height, &score),
    engine(dev()),
    random_w(0, static_cast<int>(grid_width)),
    random_h(0, static_cast<int>(grid_height)) {
    PlaceFood();
}



void Game::Run(Controller const &controller, Renderer /*&renderer*/*renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //[AuNV] (2023/10//06) mod code ----->
    controller.HandleInput(running, snake, *this);
    Update(renderer);
    renderer->Render(snake, food, &m_wall, &m_position);
    //[AuNV] (2023/10//06) <----- 

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
     //renderer.UpdateWindowTitle(score, frame_count); change * from &
      renderer->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update(Renderer* l_renderer) {
    if (this->m_paused == true) {
        l_renderer->SetPauseTitle();
        return;
    };
    if (!snake.alive)
    {
        return;
    }
    //get main windows
    SDL_Window* windowPtr = l_renderer->GetMainWindow();
    snake.Update(&m_wall,windowPtr);

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    std::random_device l_randome_device;  //Will be used to obtain a seed for the random number engine
    std::mt19937 l_generated(l_randome_device()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> l_distribution(1, 10);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        snake.GrowBody();
        if (l_distribution(l_generated) <= 2) {
            m_position = true;
            // resolves 5 seconds later
            std::thread l_poisonTimer([&]() {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                m_position = false;
                });
            l_poisonTimer.detach();
        }

    }
}
//[AuNV] (2023/10//06) add new code -----> 
void Game::TriggerPause() {
    this->m_paused ? Resume() : Pause();
}

// pause the game
void Game::Pause() {
    this->m_paused = true;
}

// resume the game
void Game::Resume() {
    this->m_paused = false;
}
//[AuNV] (2023/10//06) <----- 
int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }