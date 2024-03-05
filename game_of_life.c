#include "game_of_life.h"

int main() {
  char arr[WIDTH][LENGTH];
  if (init_field(arr)) {
    screen_preparation();
    int finish = 1, sleep = 50000;

    FILE *f = freopen("/dev/tty", "r", stdin);
    while (finish) {
      clear();
      usleep(sleep);
      show_field(arr);

      if (click(getch(), &sleep)) break;
      finish = nextArr(arr);
    }
    fclose(f);
    endwin();
    printf("Game over!");
  } else {
    printf("n/a");
  }
  return 0;
}

int init_field(char arr[WIDTH][LENGTH]) {
  int flag = 1, data;
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < LENGTH; j++) {
      if (i == 0 || i == WIDTH - 1)
        arr[i][j] = '-';
      else if (j == 0 || j == LENGTH - 1)
        arr[i][j] = '|';
      else {
        if (scanf("%d", &data) == 1 && (data == 0 || data == 1)) {
          arr[i][j] = data == 0 ? NONE : ALIVE;
        } else {
          flag = 0;
          break;
        }
      }
    }
    if (flag == 0) break;
  }
  return flag;
}

void show_field(char arr[WIDTH][LENGTH]) {
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < LENGTH; j++) {
      printw("%c", arr[i][j]);
    }
    printw("\n");
  }
}

int nextArr(char arr[WIDTH][LENGTH]) {
  char arr_2[WIDTH][LENGTH];
  int finish = 0;
  equateArr(arr, arr_2);
  for (int i = 1; i < WIDTH - 1; i++) {
    for (int j = 1; j < LENGTH - 1; j++) {
      int n = getAlive(arr, i, j);
      if (arr[i][j] == NONE && n == 3) {
        arr_2[i][j] = ALIVE;
        finish = 1;
      } else if (arr[i][j] == ALIVE && (n < 2 || n > 3)) {
        arr_2[i][j] = NONE;
        finish = 1;
      }
    }
  }
  equateArr(arr_2, arr);
  return finish;
}

void equateArr(char lastArr[WIDTH][LENGTH], char newArr[WIDTH][LENGTH]) {
  for (int i = 1; i < WIDTH; i++) {
    for (int j = 1; j < LENGTH; j++) {
      newArr[i][j] = lastArr[i][j];
    }
  }
}

int getAlive(char arr[WIDTH][LENGTH], int i, int j) {
  int n = 0;
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      if (k == 0 && l == 0) continue;

      int x = i + k;
      int y = j + l;

      if (x < 1)
        x = WIDTH - 2;
      else if (x > WIDTH - 2)
        x = 1;

      if (y < 1)
        y = LENGTH - 2;
      else if (y > LENGTH - 2)
        y = 1;

      if (arr[x][y] == ALIVE) n++;
    }
  }
  return n;
}

int click(char ch, int *sleep) {
  int flag = 0;
  int change = 5000;
  if (ch == 'q' || ch == 'Q') {
    flag = 1;
  } else if (ch == '-') {
    *sleep += change;
  } else if (ch == '+' && *sleep - change > 0) {
    *sleep -= change;
  }
  return flag;
}

void screen_preparation() {
  initscr();
  noecho();
  refresh();
  nodelay(stdscr, 1);
}