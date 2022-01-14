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
Cell** field;

/**
Grid size for the playing field.
Grid size for the playing field.Can be passed as a command line argument when starting the program, else defaults to 10x10.
 */
int grid_size;

/**
Number of mines for the playing field.
Number of mines for the playing field. Can be passed as a command line argument when starting the program, else defaults to 25.
 */
int no_of_mines;

/**
 Generates new playing field.

 Generates new playing field.
 Allocates memory dynamically for a nested array of cells according to grid size.
 Initializes all flags of the cell structs with 0.
 Places mines randomly on the field with placeMine().
 Determines the number of adjacent mines for each cell.
 Randomly opens one cell that is not a mine with openFirstCell().

 \returns pointer to a nested array of cells ( i.e. the newly generated field)

 */

Cell** generateField(){
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
      field[i][j] = (Cell) {.mine = 0, .adjacentMines = 0, .isOpened = 0, .isFlagged = 0};
    }
  }

  // randomly distribute no_of_mines
  for (i = 0; i < no_of_mines; i++){
    placeMine(field);
  }

  // determine and save number of adjacent mines
  // always check before that index is not out of bounds
  for (int i = 0 ; i < grid_size; i++ ){
    for (int j = 0 ; j < grid_size; j++ ){
      if (field[i][j].mine == 1) {
        continue;
      }
      if (j-1 >= 0) {
        if (field[i][j-1].mine == 1){
        field[i][j].adjacentMines +=1;
        }
      }
      if (j+1 < grid_size) {
        if (field[i][j+1].mine == 1) {
          field[i][j].adjacentMines +=1;
        }
      }
      if (i+1 < grid_size) {
        if (field[i+1][j].mine == 1) {
          field[i][j].adjacentMines +=1;
        }
      }
      if (i-1 >= 0) {
        if (field[i-1][j].mine == 1) {
          field[i][j].adjacentMines +=1;
        }
      }
      if (i+1 < grid_size && j+1 < grid_size){
        if (field[i+1][j+1].mine == 1) {
          field[i][j].adjacentMines +=1;
        }
      }
      if (i-1 >= 0 && j-1 >= 0) {
        if (field[i-1][j-1].mine == 1) {
          field[i][j].adjacentMines +=1;
        }
      }
      if (i-1 >= 0 && j+1 < grid_size) {
        if (field[i-1][j+1].mine == 1) {
          field[i][j].adjacentMines +=1;
        }
      }
      if (i+1 < grid_size && j-1 >= 0) {
        if (field[i+1][j-1].mine == 1) {
          field[i][j].adjacentMines +=1;
        }
      }
    }
  }

  // randomly open one cell that is not a mine
  openFirstCell(field);
  return field;
};


/**
 Places a mine on the field.

 Generates random x and y coordinates.
 Checks that there is no mine on that cell yet and places a mine with placeMine(), else calls itself recursively until a free cell is targeted.
 (max. half the number of cells will contain a mine, so the recursion will eventually end)

 \param field a pointer to a nested array of cells

 */
void placeMine(Cell** field){
  int x = rand() % grid_size;
  int y = rand() % grid_size;
  if (field[x][y].mine == 0) {
    field[x][y].mine = 1;
  } else {
    placeMine(field);
  }
}

/**
 Opens the first cell.

 Generates random x and y coordinates.
 Checks that there is no mine on that cell and opens it, else calls itself recursively until a cell is targeted that does not contain a mine.
 (max. half the number of cells will contain a mine, so the recursion will eventually end)

 \param field a pointer to a nested array of cells

 */
void openFirstCell(Cell** field){
  int x = rand() % grid_size;
  int y = rand() % grid_size;
  if (field[x][y].mine != 1 && field[x][y].adjacentMines != 0) {
    field[x][y].isOpened = 1;
  } else {
    openFirstCell(field);
  }
}