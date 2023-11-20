#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
//[AuNV] (2023/10//06) add new code -----> 
class Game;
//[AuNV] (2023/10//06) <----- 
class Controller {
 public:
  //[AuNV] (2023/10//06) mod code -----> 
  //void HandleInput(bool &running, Snake &snake) const;
     void HandleInput(bool &running, Snake &snake, Game &l_game) const;
  //[AuNV] (2023/10//06) <----- 

 private:
  //[AuNV] (2023/10//06) mod code -----> 
  //void ChangeDirection(Snake &snake, Snake::Direction input,
  //                     Snake::Direction opposite) const;
   void ChangeDirection(Snake& snake, Snake::Direction input,
         Snake::Direction opposite, bool &result) const;
  //[AuNV] (2023/10//06) <----- 
};

#endif