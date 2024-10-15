#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Utilities
int nDigits(int x)
{
    if (x == 0)
    {
        return 1;
    }
    return floor(log10(abs(x))) + 1;
}

// Finding Max
int find_max(double arr[], int size)
{
    int max = arr[0];
    for (int i = 0; i < size; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void swap(double *num1, double *num2)
{
    double temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void bubble_sort(double arr[], int n)
{
    int swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0)
        {
            break;
        }
    }
}

void copy_array(double *original, double *copy, int n)
{
    for (int i = 0; i < n; i++)
    {
        copy[i] = original[i];
    }
}
int removeDuplicates(double arr[], int N)
{
    if (N == 0)
    {
        return 0;
    }
    int i = 0;
    for (int j = 1; j < N; j++)
    {
        if (arr[i] != arr[j])
        {
            i++;
            arr[i] = arr[j];
        }
    }
    return i + 1;
}

void print_double_array(double *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%.2lf ", array[i]);
    }
    printf("\n");
}

// new_size = graph_size_H * (( y[partition] - y[0] ) / ( y[size_arr -1] - y[0]));
double normalize(double max_new_size, double old_size, double min_old_size, double max_old_size)
{
    double new_size = max_new_size * ((old_size - min_old_size) / (max_old_size - min_old_size));
    return new_size;
}