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
    clear_screen();

    int plot_type = 0, data_mode = 0; // Use to manage plotting function
    char data_path[50];               // Use to keep csv path
    FILE *fpt;                        // Use to keep csv content from path
    int plot_count = 0;               // Use to indicate currect ploting point of data

    while (1)
    {
        // Initialize Plotting, Get plot_type and data_mode
        printf("Type of your plot:\n");
        printf("Table (0), Scatter (1), Line (2), Exit(-1) : ");
        scanf("%d", &plot_type);
        if (plot_type == -1)
            break;
        printf("write (0) read (1), Exit(-1) : ");
        scanf("%d", &data_mode);
        if (data_mode == -1)
            break;

        // Get csv path
        if (data_mode == 1)
        {
            printf("Choose your data path (ex: your_path/file.csv): ");
            scanf("%s", data_path);
        }

        // Start Plotting function
        char buffer[100], lower_buffer[100];
        double x_values[200];
        double y_values[200];

        if (plot_type == 1)
        {
            // Force Insert Point (0,0)
            x_values[plot_count] = 0;
            y_values[plot_count] = 0;

            if (data_mode == 1)
            {
                // Open csv path
                fpt = fopen(data_path, "r");
                if (fpt == NULL)
                {
                    printf("Error opening file '%s'.\n\n", data_path);
                    continue;
                }

                // Get x,y from csv with maximum 100 character of data per line
                char line[100];
                while (fgets(line, sizeof(line), fpt))
                {
                    if (sscanf(line, "%lf,%lf", &x_values[plot_count], &y_values[plot_count]) == 2)
                        plot_count++;
                }
                fclose(fpt);
            }
        }

        // Clear input buffer
        while (getchar() != '\n')
            ;

        printf("Getting Input (Press ENTER if done)\n");
        while (1)
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

            // Show plotting history table
            printf("\n\n");
            printf("------+--------+---------\n");
            printf("index | X      | Y\n");
            printf("------+--------+---------\n");
            for (int j = 0; j < plot_count; j++)
            {
                printf("%3d   | %-6.2lf | %.2lf\n", j, x_values[j], y_values[j]);
            }
            printf("------+--------+---------\n");

            // Get new plotting point
            printf("\nPlot %d [x] [y], Exit(exit): ", plot_count);
            if (fgets(buffer, sizeof(buffer), stdin))
            {
                strcpy(lower_buffer, buffer);
                strlwr(lower_buffer);

                // Check exit condition
                if (!strcmp(lower_buffer, "done\n") ||
                    !strcmp(lower_buffer, "exit\n") ||
                    !strcmp(lower_buffer, "esc\n") ||
                    !strcmp(lower_buffer, "\n"))
                {
                    printf("Do you really want to exit the program? (%sy%s, n) ", "\033[4m", "\033[0m");
                    fgets(buffer, sizeof(buffer), stdin);
                    if (buffer[0] == '\n' || tolower(buffer[0]) == 'y')
                        clear_screen();
                    break;
                }

                else if (sscanf(buffer, "%lf %lf", &x_values[plot_count], &y_values[plot_count]) == 2)
                {
                    // printf("%.2lf %.2lf\n", x_values[i], y_values[i]);
                    clear_screen();
                    plot_count++;
                }
                else
                {
                    printf("Invalid input. Please enter two valid numbers.\n");
                }
            }
        }
    }
    printf("End of Program, Thank you.\n");
}