#include <stdio.h>
#include <string.h>
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

void print_ascii_art()
{
    printf(" ________  ___  ___  ___  ________  ___  __    ________  ___       ________  _________               ________  ___       ___     \n");
    printf("|\\   __  \\|\\  \\|\\  \\|\\  \\|\\   ____\\|\\  \\|\\  \\ |\\   __  \\|\\  \\     |\\   __  \\|\\___   ___\\            |\\   ____\\|\\  \\     |\\  \\    \n");
    printf("\\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\___|\\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\    \\ \\  \\|\\  \\|___ \\  \\_|____________\\ \\  \\___|\\ \\  \\    \\ \\  \\   \n");
    printf(" \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\    \\ \\   ___  \\ \\   ____\\ \\  \\    \\ \\  \\\\\\  \\   \\ \\  \\|\\____________\\ \\  \\    \\ \\  \\    \\ \\  \\  \n");
    printf("  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\____\\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\____\\ \\  \\\\\\  \\   \\ \\  \\|____________|\\ \\  \\____\\ \\  \\____\\ \\  \\ \n");
    printf("   \\ \\_____  \\ \\_______\\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\__\\    \\ \\_______\\ \\_______\\   \\ \\__\\              \\ \\_______\\ \\_______\\ \\__\\\n");
    printf("    \\|___| \\__\\|_______|\\|__|\\|_______|\\|__| \\|__|\\|__|     \\|_______|\\|_______|    \\|__|               \\|_______|\\|_______|\\|__|\n");
    printf("          \\|__|                                                                                                                   \n");
    printf("                                                                                                                                  \n");
    printf("                                                                                                                                  \n");
}

bool CheckQuitCondition(char input[])
{
    if (!strcmp(input, "done\n") ||
        !strcmp(input, "exit\n") ||
        !strcmp(input, "esc\n") ||
        !strcmp(input, "q\n") ||
        !strcmp(input, "\n"))
        return true;
    else
        return false;
}

int main()
{
    setup();

    // Initialize default CSV read parameters
    FILE *fpt;
    char file_path[50];

    // Initialize temporary address to keep input
    char input[100];

    // Initialize default DataSet initial parameters
    DataSet *dataSet;
    char name[10][20] = {};
    int default_max_cols_size = 5, default_max_name_legth = 20, default_max_rows_size = 100;

    // Initailize plotting parameters
    int plot_type = 0, data_mode = 0;
    bool force_break = false;

    while (1)
    {
        // ----------------------------- Setup State -----------------------------
        // Draw Logo acii art
        print_ascii_art();

        // Get Plotting parameters
        printf("Select Plot Types:\n");
        printf("  q : Exit.\n");
        printf("  0 : Table.\n");
        printf("  1 : Scatter.\n");
        printf("  2 : Line.\n");
        printf(": ");

        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &plot_type);
        if (CheckQuitCondition(input)) // Exit
            break;
        printf("\n");

        printf("Select Mode:\n");
        printf("  q : Exit.\n");
        printf("  0 : Write.\n");
        printf("  1 : Read.\n");
        printf(": ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &data_mode);
        if (data_mode == -1) // Exit
            break;
        printf("\n");

        // Get more specific parameters
        if (data_mode == 0) // Write manually
        {
            printf("Amount of you input column: ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &default_max_cols_size);

            printf("\nInput Name Of Column:\n");
            for (int i = 0; i < default_max_cols_size; i++)
            {
                printf("  Column[%d]: ", i);
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                strcpy(name[i], input);
            }

            // Initialize DataSet
            dataSet = ctp_initialize_dataset(default_max_cols_size, default_max_name_legth, default_max_rows_size);
            ctp_add_label(dataSet, *name, 20, default_max_cols_size);
            dataSet->db_rows_size = 0;
            dataSet->db_cols_size = default_max_cols_size;
        }
        else if (data_mode == 1)
        {
            // Get csv path
            printf("Choose your data path (ex: your_path/file.csv)\n: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            strcpy(file_path, input);

            // Open file
            fpt = fopen(file_path, "r");
            if (fpt == NULL)
            {
                perror("Error opening file");
                return 1;
            }

            // Initialize tempo input
            char _input[300]; // Buffer to hold the first line (adjust size as needed)
            char *_idx;

            // Read the first line which are the label and count data column
            if (fgets(_input, sizeof(_input), fpt) != NULL)
            {
                // Remove newline if present
                char *newline = strchr(_input, '\n');
                if (newline)
                    *newline = '\0';

                // Split
                _idx = strtok(_input, ",");

                int _cols_size = 0;
                while (_idx != NULL)
                {
                    strcpy(name[_cols_size], _idx);
                    _idx = strtok(NULL, ",");
                    _cols_size++;
                }
                default_max_cols_size = _cols_size;
            }

            // Initialize DataSet
            dataSet = ctp_initialize_dataset(default_max_cols_size, default_max_name_legth, default_max_rows_size);
            ctp_add_label(dataSet, *name, 20, default_max_cols_size);
            dataSet->db_rows_size = 0;
            dataSet->db_cols_size = default_max_cols_size;

            // Read the other line which are the data
            while (fgets(_input, sizeof(_input), fpt) != NULL)
            {
                // Remove newline if present
                char *newline = strchr(_input, '\n');
                if (newline)
                    *newline = '\0';

                // Split
                _idx = strtok(_input, ",");

                int _col = 0;
                while (_idx != NULL)
                {
                    sscanf(_idx, "%lf", &dataSet->db[_col][dataSet->db_rows_size]);
                    _idx = strtok(NULL, ",");
                    _col++;
                }
                dataSet->db_rows_size++;
            }
        }

        // ----------------------------- Input State -----------------------------
        // Start Plotting
        printf("\nGetting Plotting:\n");

        int plot_option = -1;
        // -1 menu, 0 writing, 1 searching, 2 more

        while (1)
        {
            // Display the plot
            if (dataSet->db_rows_size >= 2)
            {
                switch (plot_type)
                {
                case 0:
                    if (plot_option == 0 || plot_option == -1)
                        ctp_plot_table(dataSet);
                    else if (plot_option == 1)
                        ctp_plot_table_search(dataSet);
                    break;
                case 1:
                    if (plot_option == 0 || plot_option == -1)
                        ctp_plot_scatter(dataSet);
                    else if (plot_option == 1)
                        ctp_plot_search(dataSet);
                    break;
                default:
                    break;
                }
                printf("\n");
            }

            if (plot_option == -1) // Menu
            {
                printf("Plot Menu:\n");
                printf("  q: Exit. \n");
                printf("  0: Writing new data. \n");
                printf("  1: Searching data. \n");
                printf(": ");
                fgets(input, sizeof(input), stdin);
                printf("\n");
                if (CheckQuitCondition(input))
                    break;
                sscanf(input, "%d", &plot_option);
            }

            if (plot_option == 0) // Writing
            {
                // Get new plotting point
                printf("Wrinting Mode:\n");
                printf("Plot %d, Done(q):\n", dataSet->db_rows_size);

                // Recieve New data
                CTP_PARAM data[dataSet->db_rows_size];
                for (int i = 0; i < dataSet->db_cols_size; i++)
                {
                    printf("  Column[%d] (%s): ", i, dataSet->label[i]);
                    fgets(input, sizeof(input), stdin);

                    if (CheckQuitCondition(input))
                    {
                        plot_option = -1;
                        break;
                    }
                    else
                        sscanf(input, "%lf", &data[i]);
                }
                printf("\n");
                if (force_break)
                    break;

                ctp_add_row(dataSet, data);
            }
            else if (plot_option == 1) // Search
            {
                int col;
                char op[20];
                double target;

                printf("Searching Mode:\n");

                printf("  Select search column, Done(q):\n");
                for (int i = 0; i < dataSet->db_cols_size; i++)
                {
                    printf("    %d: %s\n", i, dataSet->label[i]);
                }
                printf("  : ");
                fgets(input, sizeof(input), stdin);
                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                    ;
                }
                else
                    sscanf(input, "%d", &col);
                printf("\n");

                printf("  Select operator, Quit(q):\n");
                printf("    e: Equal (==)\n");
                printf("    ne: Not equal (!=)\n");
                printf("    lt: Less than (<)\n");
                printf("    lte: Less than or Equal (<=)\n");
                printf("    gt: Grater than (>)\n");
                printf("    gte: Grater than or Equal (>=)\n");
                printf("  : ");
                fgets(input, sizeof(input), stdin);

                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                    ;
                }
                else
                {
                    // Remove newline if present
                    char *newline = strchr(input, '\n');
                    if (newline)
                        *newline = '\0';
                    strcpy(op, input);
                }
                printf("\n");

                printf("  Set search value, Quit(q): ");
                fgets(input, sizeof(input), stdin);
                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                    ;
                }
                else
                    sscanf(input, "%lf", &target);

                ctp_findMany(dataSet, col, op, target);
            }
            printf("End of Program, Thank you.\n");
        }
    }

    return 0;
}