#ifndef CONSTANTS_H // Include guard to prevent multiple inclusions
#define CONSTANTS_H

#define MAX_NAME_SIZE 40
#define MAX_PARAM_SIZE 99
#define MAX_PARAM 99

#define TABLE_WIDTH 10
#define BACK_SPACE 2

// For drawing table
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

// Dataframe for keep csv file
typedef struct
{
    char label[MAX_PARAM_SIZE][MAX_NAME_SIZE]; // Labels for each parameter
    double db[MAX_PARAM_SIZE][MAX_PARAM_SIZE]; // Data table
    int chosen_Y_param;                        // Index for the Y parameter
    int chosen_X_param[MAX_PARAM_SIZE];        // Array of indices for X parameters
    int chosen_X_param_amount;                 // Number of chosen X parameters
    int show_amount;                           // Number of values to display
} DataSet;

#endif // CONSTANTS_H
