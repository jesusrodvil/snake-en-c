#include "snake.h"
#include <stdlib.h>
#include <time.h>

int main(){
  struct snakeT snake;
  struct fruitT fruit;

  snake.alive = TRUE;
  snake.direction = 3;
  snake.speed = 1;
  snake.next_node = NULL;
  snake.size = 1;

  srand(time(NULL));
  gameEngine(&snake, &fruit);
  return 0;
}