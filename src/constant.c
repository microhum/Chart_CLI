#include "constant.h"

// Copy db to db_sort for sort next
void copy_db_to_sort(DataSet *data)
{
    for (int i = 0; i < data->db_rows_size; i++)
    {
        for (int j = 0; j < data->db_cols_size; j++)
        {
            data->db_sort[j][i] = data->db[j][i];
        }
    }
}

// Function to swap two row of db (db[columns][rows])
void DataSet_swap(double db[][MAX_PARAM_SIZE], int size, int a, int b)
{
    for (int i = 0; i < size; i++)
    {
        double temp = db[i][a];
        db[i][a] = db[i][b];
        db[i][b] = temp;
    }
}

// Partition function that selects a pivot and partitions the array
int partition(double db[][MAX_PARAM_SIZE], int chosen_Y_param, int size, int low, int high)
{
    double pivot = db[chosen_Y_param][high]; // Choose the last element as pivot
    int i = (low - 1);                       // Index of smaller element

    for (int j = low; j < high; j++)
    {
        // If current element is smaller than or equal to pivot
        if (db[chosen_Y_param][j] < pivot)
        {
            i++; // Increment index of smaller element
            DataSet_swap(db, size, i, j);
        }
    }
    DataSet_swap(db, size, i + 1, high);
    return (i + 1); // Return the partitioning index
}

// Quick sort function for specically DataSet structure
void quickSort(double db[][MAX_PARAM_SIZE], int chosen_Y_param, int size, int low, int high)
{
    if (low < high)
    {
        // Partition the array
        int pi = partition(db, chosen_Y_param, size, low, high);

        // Recursively sort elements before and after partition
        quickSort(db, chosen_Y_param, size, low, pi - 1);
        quickSort(db, chosen_Y_param, size, pi + 1, high);
    }
}

// Sort db_sort by using chosen_Y_param to be index
void sort_db_by_Y_param(DataSet *data)
{
    copy_db_to_sort(data);
    quickSort(data->db_sort, data->chosen_Y_param, data->db_cols_size, 0, data->db_rows_size - 1);
}

// Print all data set (using for testing)
void print_db(const DataSet *dataSet, double db[][MAX_PARAM_SIZE])
{
    for (int i = 0; i < dataSet->db_rows_size; i++)
    {
        for (int j = 0; j < dataSet->db_cols_size; j++)
        {
            printf("%.2lf\t", db[j][i]);
        }
        printf("\n");
    }
}