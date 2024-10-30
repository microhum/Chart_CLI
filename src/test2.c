#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 5

// Comparison function for qsort
int compare(const void *a, const void *b)
{
    const int *rowA = *(const int **)a; // Pointer to the first row
    const int *rowB = *(const int **)b; // Pointer to the second row
    return rowA[0] - rowB[0];           // Sort by the first element
}

void print2DArray(int arr[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int arr[ROWS][COLS] = {
        {3, 1, 4, 4, 2},
        {5, 2, 2, 3, 5},
        {1, 22, 33, 44, 55},
        {111, 222, 333, 444, 555}};

    printf("Original array:\n");
    print2DArray(arr);

    // Create an array of pointers to the rows
    int *rows[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        rows[i] = arr[i]; // Point to each row of arr
    }

    // Use qsort to sort the array of pointers based on the first column
    qsort(rows, ROWS, sizeof(int *), compare);

    // Rearrange the original array based on the sorted order of the rows
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            arr[i][j] = rows[i][j];
        }
    }

    printf("\nSorted array based on first row:\n");
    print2DArray(arr);

    return 0;
}
