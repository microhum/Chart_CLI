#ifndef CONSTANTS_H // Include guard to prevent multiple inclusions
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// About dataSet poproties
#define MAX_NAME_SIZE 40
#define MAX_PARAM_SIZE 99
#define MAX_PARAM 99

// About table drawing
const char *CORNER_TL = "┌";
const char *CORNER_TR = "┐";
const char *CORNER_BL = "└";
const char *CORNER_BR = "┘";
const char *CORNER_THZ = "┴";
const char *CORNER_BHZ = "┬";
const char *CORNER_LVC = "├";
const char *CORNER_RVC = "┤";
const char *CORNER_ALL = "┼";
const char *CORNER_VC = "│";
const char *CORNER_HZ = "─";

// About plot_table fucntion poproties
#define TABLE_WIDTH 10
#define BACK_SPACE 2

// About plot_scatter fucntion poproties
#define SCREEN_H 42
#define SCREEN_W 42

// Main Dataframe
typedef struct
{
    char label[MAX_PARAM][MAX_NAME_SIZE];      // Labels for each parameter
    double db[MAX_PARAM][MAX_PARAM_SIZE];      // Data table
    double db_sort[MAX_PARAM][MAX_PARAM_SIZE]; // Data table but sort by Y param
    int db_cols_size;                          // Amout of table column
    int db_rows_size;                          // Amout of table row
    int chosen_Y_param;                        // Index for the Y parameter
    int chosen_X_param[MAX_PARAM];             // Array of indices for X parameters
    int chosen_X_param_size;                   // Number of chosen X parameters
    int show_size;                             // Number of values to display
} DataSet;

// Function declarations
void DataSet_swap(double db[][MAX_PARAM_SIZE], int size, int a, int b);
int partition(double db[][MAX_PARAM_SIZE], int chosen_Y_param, int size, int low, int high);
void quickSort(double db[][MAX_PARAM_SIZE], int chosen_Y_param, int size, int low, int high);
void sort_db_by_Y_param(DataSet *data);
void print_db(const DataSet *dataSet, double db[][MAX_PARAM_SIZE]);

#endif // CONSTANTS_H