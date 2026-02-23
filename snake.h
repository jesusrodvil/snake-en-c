#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

enum {UP, DOWN, LEFT, RIGHT};

struct nodeT{
  int x, y;
  struct nodeT *next_node;
};

struct snakeT{
  int speed, size, x, y, direction;
  struct nodeT *next_node;
  bool alive;
};

struct fruitT{
  int x,y;
};

void changePosition(struct snakeT *snake);
void getDir(int ch, struct snakeT *snake);
void addNode(struct snakeT *snake);
void eraseNode(struct snakeT *snake);
void moveSnake(struct snakeT *snake, char *snakespr, char *bodyspr, int prevx, int prevy);
void respawnFruit(struct fruitT *fruit, int row, int col);
bool isEaten(struct snakeT *snake, struct fruitT *fruit);
bool isAlive(struct snakeT *snake);
int gameEngine(struct snakeT *snake, struct fruitT *fruit);

#endif