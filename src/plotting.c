#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

// Import plot
#include "plot.c"
#define UNDERLINE "\033[4m"

// Define
#define SCREEN_H 24
#define SCREEN_W 42

// in format command: {syntax, help_detail}
char functions[][3][100] = {
    {"lr", "Linear Regression Plotting"},
    {"mean", "find mean"},
    {"remove", "remove"}};

void setup()
{
    // Set output to utf-8
    SetConsoleOutputCP(CP_UTF8);
}

void clear_screen()
{
    printf("\033[H\033[J");
}

int main()
{
    setup();
    FILE *fpt;
    char data_path[50];

    char on_plotting = 1;
    int data_mode = 0;
    int plot_type = 0;
    int plot_count = 0;

    printf("Type of your plot:\n");
    printf("Table (0), Scatter (1), Line (2) (default 0) :");
    scanf("%d", &plot_type);
    printf("write (0) read (1)", "\033[4m", "\033[0m");
    scanf("%d", &data_mode);
    if (data_mode == 1)
    {
        printf("Choose your data path (ex: your_path/file.csv):");
        scanf("%s", data_path);
    }
    while ((getchar()) != '\n')
        ;

    char buffer[100], lower_buffer[100];
    double x_values[200];
    double y_values[200];

    if (plot_type == 1)
    {
        // Force Insert Point (0,0)
        x_values[plot_count] = 0;
        y_values[plot_count] = 0;
        plot_count++;

        if (data_mode == 1)
        {
            fpt = fopen(data_path, "r");
            if (fpt == NULL)
            {
                printf("Error opening file.\n");
                return 1;
            }
            char line[100];
            while (fgets(line, sizeof(line), fpt))
            {
                // printf("%s\n", line);
                if (sscanf(line, "%lf,%lf", &x_values[plot_count], &y_values[plot_count]) == 2)
                {
                    plot_count++;
                }
            }
            fclose(fpt);
        }
    }

    printf("Getting Input (Press ENTER if done)\n");
    while (on_plotting)
    {
        // Display the plot
        if (plot_count > 1)
        {
            switch (plot_type)
            {
            case 0:
                plot_table(x_values, y_values, plot_count, SCREEN_H, SCREEN_W);
                break;
            case 1:
                plot_scatter(x_values, y_values, plot_count, SCREEN_H, SCREEN_W);
                break;
            case 2:
                // plot_scatter(axis, i);
                break;
            default:
                break;
            }
        }
        // plotting history
        printf("\n\n");
        printf("------+--------+---------\n");
        printf("index | X      | Y\n");
        printf("------+--------+---------\n");
        for (int j = 0; j < plot_count; j++)
        {
            printf("%3d   | %-6.2lf | %.2lf\n", j, x_values[j], y_values[j]);
        }
        printf("------+--------+---------\n");

        printf("\nPlot %d [x] [y] ", plot_count);
        // Recieve Plotting
        if (fgets(buffer, sizeof(buffer), stdin))
        {
            strcpy(lower_buffer, buffer);
            strlwr(lower_buffer);

            if (strcmp(lower_buffer, "done\n") == 0 || strcmp(lower_buffer, "exit\n") == 0 || strcmp(lower_buffer, "esc\n") == 0 || strcmp(lower_buffer, "\n") == 0)
            {
                char buffer_[10], exit = 'y';
                printf("Do you really want to exit the program? (%sY%s, n) ", "\033[4m", "\033[0m");
                fgets(buffer_, sizeof(buffer_), stdin);
                if (buffer_[0] == '\n' || tolower(buffer_[0]) == 'y')
                {
                    on_plotting = 0;
                    return 0;
                }
            }

            else if (sscanf(buffer, "%lf %lf", &x_values[plot_count], &y_values[plot_count]) == 2)
            {
                // printf("%.2lf %.2lf\n", x_values[i], y_values[i]);
                system("cls");
                plot_count++;
            }
            else
            {
                printf("Invalid input. Please enter two valid numbers.\n");
            }
        }
    }
}
