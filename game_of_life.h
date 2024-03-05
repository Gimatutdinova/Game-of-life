#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 25 + 2
#define LENGTH 80 + 2
#define NONE ' '
#define ALIVE '*'

int init_field(char arr[WIDTH][LENGTH]);
void show_field(char arr[WIDTH][LENGTH]);
int getAlive(char arr[WIDTH][LENGTH], int i, int j);
int nextArr(char arr[WIDTH][LENGTH]);
void equateArr(char lastArr[WIDTH][LENGTH], char newArr[WIDTH][LENGTH]);
void screen_preparation();
int click(char ch, int *sleep);

#endif