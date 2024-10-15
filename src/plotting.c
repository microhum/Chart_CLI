#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Import plot
#include "plot.c"

// Define
#define SCREEN_H 24
#define SCREEN_W 42

void clear_screen() {
    printf("\033[H\033[J");
}

int main()
{
    char on_plotting = 1;
    int plot_type = 0;
    int i = 0;

    printf("Type of your plot:\n");
    printf("Table (0), Scatter (1), Line (2) (default 0) :");
    scanf("%d", &plot_type);
    while ((getchar()) != '\n')
        ;

    char buffer[100], lower_buffer[100];
    double x_values[100];
    double y_values[100];

    if (plot_type == 1)
    {
        // Force Insert Point (0,0)
        x_values[i] = 0;
        y_values[i] = 0;
        i++;
    }

    printf("Getting Input (Press ENTER if done)\n");
    while (on_plotting)
    {   
        if(plot_type && i > 1){
            plot_scatter(x_values, y_values, i, SCREEN_H, SCREEN_W);
        }
        
        printf("\nPlot %d [x] [y] ", i);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)

        strcpy(lower_buffer, buffer);
        strlwr(lower_buffer);

        if (strcmp(lower_buffer, "done\n") == 0 || strcmp(lower_buffer, "exit\n") == 0 || strcmp(lower_buffer, "esc\n") == 0 || strcmp(lower_buffer, "\n") == 0)
        {
            on_plotting = 0;
        }
        else if (sscanf(buffer, "%lf %lf", &x_values[i], &y_values[i]) == 2)
        {
            // printf("%.2lf %.2lf\n", x_values[i], y_values[i]);
            system("cls");
            i++;
        }
        else
        {
            printf("Invalid input. Please enter two valid numbers.\n");
        }
    }

    switch (plot_type)
    {
    case 0:
        plot_table(x_values, y_values, i, SCREEN_H, SCREEN_W);
        break;
    case 1:
        plot_scatter(x_values, y_values, i, SCREEN_H, SCREEN_W);
        break;
    case 2:
        // plot_scatter(axis, i);
        break;
    default:
        break;
    }
}
