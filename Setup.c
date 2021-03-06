/** \file
* \brief This file handles setting up a new playfield for minesweeper*/

#include <stdio.h>
#include <stdlib.h>
#include "setup.h"

// global variables

/**
Playing field.
Pointer to a nested array cells representing the playing field
 */
Cell **field;

/**
Grid size for the playing field.
Grid size for the playing field. Can be passed as a command line argument when starting the program, else defaults to 10x10.
 */
int grid_size;

/**
Number of mines for the playing field.
Number of mines for the playing field. Can be passed as a command line argument when starting the program, else defaults to 25.
 */
int no_of_mines;

Cell** generate_field(){
// dynamically allocate memory for a nested array of cells according to grid size

  int g = grid_size, i, j;

  Cell** field = (Cell**)malloc(g * sizeof(Cell*));
  if (field == NULL){
    fprintf(stderr, "Could not allocate memory\n");
    exit(1);
  }
  for (i = 0; i < g; i++){
    field[i] = (Cell*)malloc(g * sizeof(Cell));
    if (field[i] == NULL){
    fprintf(stderr, "Could not allocate memory\n");
    exit(1);
  }
  }
  // initialize with default values
  for (i = 0; i < g; i++){
    for (j = 0; j < g; j++){
      field[i][j] = (Cell) {.adjacent_mines = 0, .is_flagged = 0, .is_mine = 0,  .is_opened = 0,};
    }
  }

  // randomly distribute no_of_mines
  for (i = 0; i < no_of_mines; i++){
    place_mine(field);
  }

  // determine and save number of adjacent mines
  // always check before that index is not out of bounds
  for (int i = 0 ; i < grid_size; i++ ){
    for (int j = 0 ; j < grid_size; j++ ){
      if (field[i][j].is_mine == 1) {
        continue;
      }
      if (j-1 >= 0) {
        if (field[i][j-1].is_mine == 1){
        field[i][j].adjacent_mines +=1;
        }
      }
      if (j+1 < grid_size) {
        if (field[i][j+1].is_mine == 1) {
          field[i][j].adjacent_mines +=1;
        }
      }
      if (i+1 < grid_size) {
        if (field[i+1][j].is_mine == 1) {
          field[i][j].adjacent_mines +=1;
        }
      }
      if (i-1 >= 0) {
        if (field[i-1][j].is_mine == 1) {
          field[i][j].adjacent_mines +=1;
        }
      }
      if (i+1 < grid_size && j+1 < grid_size){
        if (field[i+1][j+1].is_mine == 1) {
          field[i][j].adjacent_mines +=1;
        }
      }
      if (i-1 >= 0 && j-1 >= 0) {
        if (field[i-1][j-1].is_mine == 1) {
          field[i][j].adjacent_mines +=1;
        }
      }
      if (i-1 >= 0 && j+1 < grid_size) {
        if (field[i-1][j+1].is_mine == 1) {
          field[i][j].adjacent_mines +=1;
        }
      }
      if (i+1 < grid_size && j-1 >= 0) {
        if (field[i+1][j-1].is_mine == 1) {
          field[i][j].adjacent_mines +=1;
        }
      }
    }
  }

  // randomly open one cell that is not a mine
  open_first_cell(field);
  return field;
}

void place_mine(Cell **field){
  int x = rand() % grid_size;
  int y = rand() % grid_size;
  if (field[x][y].is_mine == 0) {
    field[x][y].is_mine = 1;
  } else {
    place_mine(field);
  }
}

void open_first_cell(Cell **field){
  int x = rand() % grid_size;
  int y = rand() % grid_size;
  if (field[x][y].is_mine != 1 && field[x][y].adjacent_mines != 0) {
    field[x][y].is_opened = 1;
  } else {
    open_first_cell(field);
  }
}
