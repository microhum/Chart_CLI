# Data Visualization Library

This library provides functions to visualize datasets in a statistic format. It includes a function `plot_table` that formats and displays a dataset with customizable labels.

## DataSet Structure

The `DataSet` structure holds the data necessary for plotting the table. It includes parameters for the data values, labels, and configuration settings.

### Definition

```c
#define MAX_NAME_SIZE 20
#define MAX_PARAM 5
#define MAX_PARAM_SIZE 100

typedef struct {
    char label[MAX_PARAM][MAX_NAME_SIZE]; // Array of labels for parameters
    double db[MAX_PARAM_SIZE][MAX_PARAM];  // 2D array for storing data values
    int chosen_Y_param;                     // Index of the chosen Y parameter
    int chosen_X_param[MAX_PARAM];         // Array of chosen X parameters
    int chosen_X_param_amount;             // Number of chosen X parameters
    int show_amount;                       // Number of data rows to display
} DataSet;
```

### Members
- `label`: An array of strings that represent the names of each parameter.
- `db`: A 2D array containing the data values for each parameter.
- `chosen_Y_param`: The index of the parameter chosen for the Y-axis.
- `chosen_X_param`: An 2D array of indices representing the chosen parameters for the X-axis.
- `chosen_X_param_amount`: The number of parameters chosen for the X-axis.
- `show_amount`: The number of rows of data to display.

### Example Usage
```c
DataSet dataSet = {
    .label = {"Score", "Sec A", "Sec B", "Sec C"},
    .db = {
        {2, 3, 4, 5},
        {1, 2, 3, 4},
        {11, 22, 33, 44},
        {111, 222, 333, 444}
    },
    .chosen_Y_param = 0,
    .chosen_X_param = {1, 2, 3},
    .chosen_X_param_amount = 3,
    .show_amount = 4
};
```
---

## plot_table Function

The `plot_table` function prints a formatted table of the dataset to the console, using box-drawing characters for a clear visual representation.

### Definition

```c
void plot_table(const DataSet *dataSet);
```

### Parameters
- `dataSet`: A pointer to a `DataSet` structure containing the data to be plotted.

### Description
The `plot_table` function performs the following actions:
1. Prints the total number of plots.
2. Creates a top border using box-drawing characters.
3. Displays the labels for the Y and X parameters.
4. Prints the data values in rows, with proper alignment.
5. Creates a bottom border to close the table.

### Setting
```c
//const.h
#define TABLE_WIDTH 10       // Width of each table cell
#define BACK_SPACE 2         // Space to add after each cell

// For drawing table
const char *CORNER_TL = "┌"; // Top left corner
const char *CORNER_TR = "┐"; // Top right corner
const char *CORNER_BL = "└"; // Bottom left corner
const char *CORNER_BR = "┘"; // Bottom right corner
const char *CORNER_THZ = "┴"; // Bottom horizontal connector
const char *CORNER_BHZ = "┬"; // Top horizontal connector
const char *CORNER_LVC = "├"; // Left vertical connector
const char *CORNER_RVC = "┤"; // Right vertical connector
const char *CORNER_ALL = "┼"; // Cross connector
const char *CORNER_VC = "│";  // Vertical line
const char *CORNER_HZ = "─";  // Horizontal line
```
- `TABLE_WIDTH`: Width of each table cell.
- `BACK_SPACE`: Space to add after each cell.
- `Other Below`: Character to write cell.


### Example Usage
```c
DataSet dataSet = {
    .label = {"Score", "Sec A", "Sec B", "Sec C"},
    .db = {
        {2, 3, 4, 5},
        {1, 2, 3, 4},
        {11, 22, 33, 44},
        {111, 222, 333, 444}
    },
    .chosen_Y_param = 0,
    .chosen_X_param = {1, 2, 3},
    .chosen_X_param_amount = 3,
    .show_amount = 4
};

plot_table(&dataSet);
```

### Output
```
┌──────────┬──────────┬──────────┬──────────┐
│   Score  │   Sec A  │   Sec B  │   Sec C  │
├──────────┼──────────┼──────────┼──────────┤
│    2.00  │    1.00  │   11.00  │  111.00  │
├──────────┼──────────┼──────────┼──────────┤
│    3.00  │    2.00  │   22.00  │  222.00  │
├──────────┼──────────┼──────────┼──────────┤
│    4.00  │    3.00  │   33.00  │  333.00  │
├──────────┼──────────┼──────────┼──────────┤
│    5.00  │    4.00  │   44.00  │  444.00  │
├──────────┼──────────┼──────────┼──────────┤
│    6.00  │    5.00  │   55.00  │  555.00  │
└──────────┴──────────┴──────────┴──────────┘
```
The output will be a neatly formatted table displayed in the console, with the specified Y and X parameters along with their values.

---

## Conclusion

This library offers a simple way to visualize datasets in C, making it easier to analyze and present data. The `plot_table` function can be customized further to enhance its functionality and adaptability.
