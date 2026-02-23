#include "snake.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>

void changePosition(struct snakeT *snake){
  switch(snake->direction){
      case LEFT:
        snake->x -= snake->speed;
        break;
      case RIGHT:
        snake->x += snake->speed;
        break;
      case UP:
        snake->y -= snake->speed;
        break;
      case DOWN:
        snake->y += snake->speed;
        break;
    }
}

void getDir(int ch, struct snakeT *snake){
  switch(ch){
      case KEY_LEFT:
        if (snake->direction != RIGHT) snake->direction = LEFT;
        break;
      case KEY_RIGHT:
        if (snake->direction != LEFT) snake->direction = RIGHT;
        break;
      case KEY_UP:
        if (snake->direction != DOWN) snake->direction = UP;
        break;
      case KEY_DOWN:
        if (snake->direction != UP) snake->direction = DOWN;
        break;
    }
}

void addNode(struct snakeT *snake) {
    struct nodeT *new_node = malloc(sizeof(struct nodeT));
    new_node->x = snake->x; 
    new_node->y = snake->y;
    new_node->next_node = snake->next_node;
    snake->next_node = new_node;
    
    snake->size += 1;
}

void eraseNode(struct snakeT *snake){
  if(snake->next_node != NULL){
      struct nodeT *current_node = snake->next_node;
        while(current_node->next_node != NULL){
          current_node = current_node->next_node;
        }
      mvprintw(current_node->y, current_node->x, " ");
    }
    else mvprintw(snake->y, snake->x, " ");
}

void moveSnake(struct snakeT *snake, char *snakespr, char *bodyspr, int prevx, int prevy){
  if(snake->next_node != NULL){
      struct nodeT *current_node = snake->next_node;
      while(current_node != NULL){
        int tempx = current_node->x;
        int tempy = current_node->y;
        current_node->x = prevx;
        current_node->y = prevy;
        prevx = tempx;
        prevy = tempy;
        mvprintw(current_node->y, current_node->x, bodyspr);
        current_node = current_node->next_node;
        }
    }
    mvprintw(snake->y, snake->x,"%s",snakespr);
}

void respawnFruit(struct fruitT *fruit, int row, int col){
  fruit->x = rand() % col;
  fruit->y = rand() % row;
}

bool isEaten(struct snakeT *snake, struct fruitT *fruit){
  if ((snake->x == fruit->x) && (snake->y == fruit->y)){
    return TRUE;
  }
  return FALSE;
}

bool isAlive(struct snakeT *snake){
  if(snake->next_node != NULL){
      struct nodeT *current_node = snake->next_node;
      while(current_node != NULL){
        if(snake->x == current_node->x && snake->y == current_node->y) return FALSE;
        current_node = current_node->next_node;
      }
    }
  return TRUE;
}



int gameEngine(struct snakeT *snake, struct fruitT *fruit){
  int ch, row, col;
  initscr();
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
  timeout(150);
  char snakespr[] = "Q";
  char bodyspr[] = "o";
  char fruitspr[] = "*";
  getmaxyx(stdscr, row, col);
  respawnFruit(fruit, row, col);
  snake->y = row/2;
  snake->x = (col-strlen(snakespr))/2;
  
  mvprintw(snake->y, snake->x,"%s",snakespr);
  while((ch = getch()) != 'q'){
    eraseNode(snake);
    if(isEaten(snake, fruit)){
      addNode(snake);
      respawnFruit(fruit, row, col);
    }
    getDir(ch, snake);
    int prevx = snake->x;
    int prevy = snake->y;
    changePosition(snake);
    moveSnake(snake, snakespr, bodyspr, prevx, prevy);
    if(isAlive(snake) == FALSE) break;
    mvprintw(fruit->y, fruit->x,"%s",fruitspr);
    mvprintw(0, 0, "%d", snake->size);
  }
  endwin();
  return 0;
}
