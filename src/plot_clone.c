#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

#include "../libs/CTerminalPlotLib/include/CTerminalPlotLib.h"
#include "../libs/CTerminalPlotLib/src/CTerminalPlotLib.c"

void setup()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "");
}

int main()
{
    setup();
    FILE *fpt;                        // Use to keep csv content from path
    char data_path[50];               // Use to keep csv path
    int plot_type = 0, data_mode = 0; // Use to manage plotting function
    char name[10][20] = {};

    int default_max_cols_size = 5, default_max_name_legth = 20, default_max_rows_size = 100;

    while (1)
    {
        // ----------------------------- Setup State -----------------------------
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
        else if (data_mode == 0)
        {
            // Get input column
            printf("Amount of you input column : ");
            scanf("%d", &default_max_cols_size);

            printf("\nInput Name Of Column:\n");
            for (int i = 0; i < default_max_cols_size; i++)
            {
                printf("Column[%d]: ", i);
                scanf("%s", name[i]);
            }
        }
        else if (data_mode == 1)
        {
            // Get csv path
            printf("Choose your data path (ex: your_path/file.csv): ");
            scanf("%s", data_path);
        }

        // ----------------------------- Input State -----------------------------
        // Initial data set
        DataSet *dataSet = ctp_initialize_dataset(default_max_cols_size, default_max_name_legth, default_max_rows_size);
        ctp_add_label(dataSet, name, 20, default_max_cols_size);
        dataSet->db_rows_size = 0;
        dataSet->db_cols_size = default_max_cols_size;

        // Clear input buffer
        while (getchar() != '\n')
            ;

        printf("Getting Input (Press ENTER if done)\n");
        while (1)
        {
            // Display the plot
            if (dataSet->db_rows_size >= 2)
            {
                switch (plot_type)
                {
                case 0:
                    ctp_plot_table(dataSet);
                    break;
                case 1:
                    ctp_plot(dataSet);
                    break;
                default:
                    break;
                }
            }

            // Get new plotting point
            printf("\nPlot %d:\n", dataSet->db_rows_size);

            CTP_PARAM data[dataSet->db_rows_size];
            for (int i = 0; i < dataSet->db_cols_size; i++)
            {
                printf("Column[%d] (%s): ", i, dataSet->label[i]);
                scanf("%lf", &data[i]);
            }
            ctp_add_row(dataSet, data);
        }
    }

    return 0;
}