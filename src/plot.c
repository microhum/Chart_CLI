#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <wchar.h> //wprintf for printing unicode
#include "utilities.c"
#include "constant.c"

const char SCATTER_FLAG = 'X';
const char *Y_AXIS_FLAG = "┼";
const char *X_AXIS_FLAG = "-";

void plot_table(const DataSet *dataSet)
{
    // Print header
    printf("%d Plots Total\n", dataSet->show_size);

    // Top Line
    printf("%s", CORNER_TL);
    for (int i = 0; i < dataSet->chosen_X_param_size + 1; i++)
    {
        for (int j = 0; j < TABLE_WIDTH; j++)
        {
            printf("%s", CORNER_HZ);
        }
        if (i != dataSet->chosen_X_param_size)
            printf("%s", CORNER_BHZ);
    }
    printf("%s", CORNER_TR);
    printf("\n");

    // Print Lable name
    printf("%s", CORNER_VC);
    printf("%*s", TABLE_WIDTH - BACK_SPACE, dataSet->label[dataSet->chosen_Y_param]);
    for (int k = 0; k < BACK_SPACE; k++)
        printf(" ");
    for (int i = 0; i < dataSet->chosen_X_param_size; i++)
    {
        printf("%s", CORNER_VC);
        printf("%*s", TABLE_WIDTH - BACK_SPACE, dataSet->label[dataSet->chosen_X_param[i]]);
        for (int k = 0; k < BACK_SPACE; k++)
            printf(" ");
    }
    printf("%s", CORNER_VC);
    printf("\n");

    // Print the data
    for (int i = 0; i < dataSet->show_size; i++)
    {
        // Pararel Line
        printf("%s", CORNER_LVC);
        for (int i = 0; i < dataSet->chosen_X_param_size + 1; i++)
        {
            for (int j = 0; j < TABLE_WIDTH; j++)
            {
                printf("%s", CORNER_HZ);
            }
            if (i != dataSet->chosen_X_param_size)
                printf("%s", CORNER_ALL);
        }
        printf("%s", CORNER_RVC);
        printf("\n");

        // Data
        printf("%s", CORNER_VC);
        printf("%*.2f", TABLE_WIDTH - BACK_SPACE, dataSet->db[dataSet->chosen_Y_param][i]); // Print Y values
        for (int k = 0; k < BACK_SPACE; k++)
            printf(" ");
        for (int j = 0; j < dataSet->chosen_X_param_size; j++)
        {
            printf("%s", CORNER_VC);
            printf("%*.2f", TABLE_WIDTH - BACK_SPACE, dataSet->db[dataSet->chosen_X_param[j]][i]); // Print X values
            for (int k = 0; k < BACK_SPACE; k++)
                printf(" ");
        }
        printf("%s", CORNER_VC);
        printf("\n");
    }

    // Buttom Line
    printf("%s", CORNER_BL);
    for (int i = 0; i < dataSet->chosen_X_param_size + 1; i++)
    {
        for (int j = 0; j < TABLE_WIDTH; j++)
        {
            printf("%s", CORNER_HZ);
        }
        if (i != dataSet->chosen_X_param_size)
            printf("%s", CORNER_THZ);
    }
    printf("%s", CORNER_BR);
    printf("\n");
}

// void plot_scatter(const DataSet *dataSet)
// {
//     double db_sort[MAX_PARAM_SIZE][MAX_PARAM_SIZE];
// }

void plot_scatter_old(double x[], double y[], const int size_arr)
{
    double x_sort[size_arr], y_sort[size_arr];
    memcpy(x_sort, x, sizeof(double) * size_arr);
    memcpy(y_sort, y, sizeof(double) * size_arr);

    // # Sort array
    bubble_sort(x_sort, size_arr);
    bubble_sort(y_sort, size_arr);

    printf("\nInitialize Scatter Plot\n");

    printf("%d Plots Total\n", size_arr);

    double graph_size_H = SCREEN_H;
    double graph_size_W = SCREEN_W;

    printf("Chart Size :%lf %lf\n\n", graph_size_H, graph_size_W);

    double _y_sort[size_arr];
    memcpy(_y_sort, y_sort, sizeof(double) * size_arr);
    double _x_sort[size_arr];
    memcpy(_x_sort, x_sort, sizeof(double) * size_arr);
    int size__y = removeDuplicates(_y_sort, size_arr);
    int size__x = removeDuplicates(_x_sort, size_arr);

    printf("%d, %d\n", size__x, size__y);

    // Normalize (scaling) plotting value
    double x_normalize[size_arr]; // Scaling X with X axis
    double y_normalize[size_arr]; // Scaling Y with Y axis
    double _y_normalize[size__y]; // Scaling and removed duplicates of Y for Y axis
    double _x_normalize[size__x]; // Scaling and removed duplicates of X for X axis

    for (int i = 0; i < size_arr; i++)
    {
        x_normalize[i] = normalize(graph_size_W, x[i], x_sort[0], x_sort[size_arr - 1]);
        y_normalize[i] = normalize(graph_size_H, y[i], y_sort[0], y_sort[size_arr - 1]); // From back to front
    }
    for (int i = 0; i < size__x; i++)
    {
        _x_normalize[i] = normalize(graph_size_W, _x_sort[i], _x_sort[0], _x_sort[size__x - 1]);
        _y_normalize[i] = normalize(graph_size_H, _y_sort[i], _y_sort[0], _y_sort[size__y - 1]); // From back to front
    }
    // ### for array debug
    // print_double_array(_x_sort, size__x);
    // print_double_array(_y_sort, size__y);
    // print_double_array(_x_normalize, size__x);
    // print_double_array(_y_normalize, size__y);

    // ### Debug Normalized Value
    // printf("Normalized Values:\n");
    // for (int i = 0; i < size_arr; i++)
    // {
    //     printf("x: %-5.2lf ->%-8.2lf", x[i], x_normalize[i]);
    //     printf("| y: %-5.2lf ->%-8.2lf\n", y[size_arr - i - 1], y_normalize[size_arr - i - 1]);
    // }
    // printf("\n");

    // Draw Y Axis
    int indent_y = nDigits(y_sort[size_arr - 1]);
    int partition = 0;
    for (int i = 0; i < graph_size_H + 1; i++)
    {

        int curr_number = -1;
        double match_pair_x[10][4]; // x values with same y
        int match_idx = 0;
        // printf("%d %d",graph_size_H - i,  _y_normalize[partition]);

        if (partition < size__y && graph_size_H - i <= _y_normalize[size__y - partition - 1])
        {

            printf("%.2lf", _y_sort[size__y - partition - 1]);
            curr_number = (double)_y_sort[size__y - partition - 1];

            // Get all x values that is same y
            for (int match_n = 0; match_n < size_arr; match_n++)
            {

                if (y[size_arr - match_n - 1] == curr_number)
                {
                    // Get x value
                    match_pair_x[match_idx][0] = x[size_arr - match_n - 1];

                    // Get y value
                    match_pair_x[match_idx][1] = y[size_arr - match_n - 1];

                    // Get x distance
                    match_pair_x[match_idx][2] = (double)round(x_normalize[size_arr - match_n - 1]);
                    match_pair_x[match_idx][3] = (double)round(y_normalize[size_arr - match_n - 1]);
                    match_idx += 1;
                }
            }

            partition++;
        }

        // Make an indent from most digit number
        if (curr_number != -1)
        {
            for (int i = nDigits(curr_number); i < indent_y; i++)
            {
                // printf(" %d %d %d", indent_y, nDigits(curr_number), curr_number);
                printf(" ");
            }
        }
        else
        {
            // .2lf = 3 space ( . + decimal)
            printf("   ");
            for (int i = 0; i < indent_y; i++)
            {
                printf(" ");
            }
        }

        printf("%s", Y_AXIS_FLAG);

        int show_point_axis = 0;
        // Plot scatter point
        if (match_idx > 0)
        {
            // Sort Array by X Value
            for (int k = 0; k < match_idx - 1; k++)
            {
                for (int l = 0; l < match_idx - k - 1; l++)
                {
                    if (match_pair_x[l][0] > match_pair_x[l + 1][0])
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            double temp = match_pair_x[l][m];
                            match_pair_x[l][m] = match_pair_x[l + 1][m];
                            match_pair_x[l + 1][m] = temp;
                        }
                    }
                }
            }

            int last_pos = 0;
            int extra_length = 0;
            for (int num_pair = 0; num_pair < match_idx; num_pair++)
            {
                int pos = match_pair_x[num_pair][2] * 3;
                // printf("x: %d y: %d",match_pair_x[num_pair][2], match_pair_x[num_pair][3]);
                for (int j = last_pos; j < pos - extra_length; j++)
                {
                    printf(" ");
                }
                // Plot scatter with color
                printf("\033[1;31m");
                printf("%c", SCATTER_FLAG);

                if (show_point_axis)
                {
                    printf("\033[1;32m");
                    printf(" (%.0lf, %.0lf)", match_pair_x[num_pair][0], match_pair_x[num_pair][1]);
                    extra_length += snprintf(NULL, 0, " (%.0lf, %.0lf)", match_pair_x[num_pair][0], match_pair_x[num_pair][1]);
                }
                printf("\033[0m");
                last_pos = pos + 1;
            }
        }
        printf("\n");
    }

    // Draw X Axis

    // indent space for x
    indent_y += 3;
    for (int i = 0; i < indent_y; i++)
    {
        printf(" ");
    }
    printf("+");
    for (int i = 0; i < graph_size_W + 1; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%s", X_AXIS_FLAG);
        }
    }
    printf("\n");

    // indent to match with ---
    int indent_x = 3;
    // . + 2 decimal
    int x_decimal = 3;

    // starter indent space for x
    for (int i = 0; i < indent_y - x_decimal; i++)
    {
        printf(" ");
    }

    partition = 0;
    for (int i = 0; i <= graph_size_W + 1; i++)
    {
        int curr_number = -1;

        if (partition < size__x && i >= _x_normalize[partition])
        {
            // printf("%d ", i);
            printf("%.2lf", _x_sort[partition]);
            curr_number = (int)_x_sort[partition];
            partition++;
        }

        int remove_indent = 0;
        if (curr_number != -1)
        {
            remove_indent = nDigits(curr_number);
            remove_indent += x_decimal;
        }
        for (int i = 0; i < indent_x - remove_indent; i++)
        {
            printf(" ");
        }
    }
}