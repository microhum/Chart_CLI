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

    // Initialize plot show propoties
    // Default Table || Default Scatter Plot || Search Table || Search Scatter Plot
    bool plot_show[4];
    for (int i = 0; i < 4; i++)
        plot_show[i] = false;

    int plot_option = -1;
    // -1 menu, 0 writing, 1 searching, 2 more

    while (!force_break)
    {
        // ----------------------------- Setup State -----------------------------
        // Draw Logo acii art
        print_ascii_art();

        // Get Plotting parameters
        printf("Select Plot Types:\n");
        printf("  q : Exit.\n");
        printf("  0 : Table Plot.\n");
        printf("  1 : Scatter Plot.\n");
        printf("  2 : Both Table and Scatter Plot.\n");
        printf(": ");

        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &plot_type);
        if (CheckQuitCondition(input)) // Exit
            break;
        printf("\n");

        if (plot_type == 0)
        {
            plot_show[0] = true;
        }
        else if (plot_type == 1)
        {
            plot_show[1] = true;
        }
        else if (plot_type == 2)
        {
            plot_show[0] = true;
            plot_show[1] = true;
        }

        printf("Select Mode:\n");
        printf("  q : Exit.\n");
        printf("  0 : Write new Data.\n");
        printf("  1 : Read from file.\n");
        printf(": ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &data_mode);
        if (data_mode == -1) // Exit
            break;
        printf("\n");

        // Get more specific parameters
        if (data_mode == 0) // Write manually
        {
            plot_option = 1;
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
            bool semi_force_break = false;
            while (1)
            {
                // Get csv path
                printf("Choose your data path (ex: your_path/file.csv), Return to Menu(q)\n: ");
                fgets(input, sizeof(input), stdin);

                if (CheckQuitCondition(input))
                {
                    semi_force_break = true;
                    break;
                }

                // Remove newline if present
                char *newline = strchr(input, '\n');
                if (newline)
                    *newline = '\0';
                strcpy(file_path, input);

                // Open file
                fpt = fopen(file_path, "r");
                if (fpt == NULL)
                {
                    printf("Error opening file.\n\n");
                    continue;
                }
                else
                    break;
            }
            if (semi_force_break)
                continue;

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
            fclose(fpt);
        }

        // ----------------------------- Input State -----------------------------
        // Start Plotting
        printf("\nGetting Plotting:\n");

        while (1)
        {
            // Display the plot

            if (plot_show[0])
            {
                if (dataSet->db_rows_size >= 2)
                {
                    printf("Default Table:\n");
                    ctp_plot_table(dataSet);
                }
                else
                    printf("Default Plot has %d point, It has less point to plot scatter.\n", dataSet->db_search_size);
                printf("\n");
            }
            if (plot_show[1])
            {
                printf("Default Scatter:\n");
                ctp_plot_scatter(dataSet);
                printf("\n");
            }

            if (plot_show[2])
            {
                printf("Search Table:\n");
                ctp_plot_table_search(dataSet);
                printf("\n");
            }
            if (plot_show[3])
            {
                if (dataSet->db_search_size >= 2)
                {
                    printf("Search Scatter:\n");
                    ctp_plot_scatter_search(dataSet);
                }
                else
                    printf("Search Plot has %d point, It has less point to plot scatter.\n", dataSet->db_search_size);
                printf("\n");
            }

            if (plot_option == -1) // Menu
            {
                printf("Plot Menu:\n");
                printf("  q: End The Program.\n");
                printf("  r: Create New Plot.\n");
                printf("  0: Setting.\n");
                printf("  1: Write New Data.\n");
                printf("  2: Search Data.\n");
                printf("  3: Analyze Data.\n");
                printf("  4: Sort Data.\n");
                printf("  5: Save Data.\n");
                printf(": ");
                fgets(input, sizeof(input), stdin);
                printf("\n");
                if (CheckQuitCondition(input))
                {
                    force_break = true;
                    break;
                }
                if (!strcmp(input, "r\n"))
                    break;

                sscanf(input, "%d", &plot_option);
            }

            if (plot_option == 0) // Setting
            {
                printf("Setting Mode:\n");
                printf("  q: Return To Menu \n");
                printf("\n");
                printf("  0: Edit Plot Show \n");
                printf("    - Default Table Plot (%s) \n", plot_show[0] ? "true" : "false");
                printf("    - Default Scatter Plot (%s) \n", plot_show[1] ? "true" : "false");
                printf("    - Search Table Plot (%s) \n", plot_show[2] ? "true" : "false");
                printf("    - Search Scatter Plot (%s) \n", plot_show[3] ? "true" : "false");
                printf("\n");
                printf("  1: Edit Table Plot Proproties \n");
                printf("    - Table Width Per Column (%d) \n", TABLE_WIDTH);
                printf("    - Table Back Space Of Column  (%d) \n", BACK_SPACE);
                printf("    - Reset To Default\n");
                printf("\n");
                printf("  2: Edit Scatter Plot Proproties. \n");
                printf("    - Graph Size (%d x %d) \n", SCREEN_W, SCREEN_H);
                printf("    - Graph Border (%d) \n", BORDER_EDGE);
                printf("    - Reset To Default\n");
                printf("\n");
                printf(": ");
                fgets(input, sizeof(input), stdin);

                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                }

                int setting_mode;
                sscanf(input, "%d", &setting_mode);

                if (setting_mode == 0)
                {
                    while (1)
                    {
                        printf("  Edit Plot Show. \n");
                        printf("    q: Return To Menu. \n");
                        printf("    0: Default Table Plot. (%s) \n", plot_show[0] ? "true " : "false");
                        printf("    1: Default Scatter Plot. (%s) \n", plot_show[1] ? "true " : "false");
                        printf("    2: Search Table Plot. (%s) \n", plot_show[2] ? "true " : "false");
                        printf("    3: Search Scatter Plot. (%s) \n", plot_show[3] ? "true " : "false");
                        printf(": ");

                        fgets(input, sizeof(input), stdin);

                        if (CheckQuitCondition(input))
                            break;

                        int index;
                        sscanf(input, "%d", &index);

                        plot_show[index] = !plot_show[index];
                        printf("\n");
                    }
                }
                else if (setting_mode == 1)
                {
                    while (1)
                    {
                        printf("  Edit Table Plot Proproties. \n");
                        printf("    0: %d: Table Width Per Column\n", TABLE_WIDTH);
                        printf("    1: %d: Table Back Space Of Column\n", BACK_SPACE);
                        printf("    2: Reset To Default\n");
                        printf(": ");
                        fgets(input, sizeof(input), stdin);

                        if (CheckQuitCondition(input))
                            break;

                        int index;
                        sscanf(input, "%d", &index);

                        if (index == 0)
                        {
                            int new;
                            printf("Set New Table Width To: ");
                            fgets(input, sizeof(input), stdin);
                            sscanf(input, "%d", &new);

                            ctp_set_table_width(new);
                        }
                        else if (index == 1)
                        {
                            int new;
                            printf("Set New Table Back Space To: ");
                            fgets(input, sizeof(input), stdin);
                            sscanf(input, "%d", &new);

                            ctp_set_table_backspace(new);
                        }
                        else if (index == 2)
                        {
                            ctp_set_table_reset_default();
                        }

                        printf("\n");
                    }
                }
                else if (setting_mode == 2)
                {
                    while (1)
                    {
                        printf("  Edit Scatter Plot Proproties. \n");
                        printf("    0: %d x %d: Graph Size\n", SCREEN_W, SCREEN_H);
                        printf("    1: %d: Graph Border\n", BORDER_EDGE);
                        printf("    2: Reset To Default\n");
                        printf(": ");
                        fgets(input, sizeof(input), stdin);

                        if (CheckQuitCondition(input))
                            break;

                        int index;
                        sscanf(input, "%d", &index);

                        if (index == 0)
                        {
                            int new_width, new_height;
                            printf("Set New Graph Width To: ");
                            fgets(input, sizeof(input), stdin);
                            sscanf(input, "%d", &new_width);

                            printf("Set New Graph Height To: ");
                            fgets(input, sizeof(input), stdin);
                            sscanf(input, "%d", &new_height);

                            ctp_set_graph_resolution(new_width, new_height);
                        }
                        else if (index == 1)
                        {
                            int new;
                            printf("Set New Graph Border To: ");
                            fgets(input, sizeof(input), stdin);
                            sscanf(input, "%d", &new);

                            ctp_set_graph_border(new);
                        }
                        else if (index == 2)
                        {
                            ctp_set_graph_reset_default();
                        }

                        printf("\n");
                    }
                }
            }
            else if (plot_option == 1) // Write
            {
                printf("Wrinting Mode:\n");
                printf("Plot %d, Return To Menu(q):\n", dataSet->db_rows_size);

                // Recieve New data by repeating each collumn
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

                ctp_add_row(dataSet, data);
            }
            else if (plot_option == 2) // Search
            {
                if (plot_show[0])
                {
                    plot_show[0] = false;
                    plot_show[2] = true;
                }

                if (plot_show[1])
                {
                    plot_show[1] = false;
                    plot_show[3] = true;
                }

                int col;
                char op[20];
                double target;

                printf("Searching Mode:\n");
                printf("  q: Return To Menu. \n");
                printf("  0: Add New Filter. \n");
                printf("  1: Analyzing This data\n");
                printf("  2: Save This Data. \n");
                printf(": ");
                fgets(input, sizeof(input), stdin);

                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                }

                int index;
                sscanf(input, "%d", &index);

                if (index == 1)
                {
                    plot_option = 3;
                    continue;
                }
                else if (index == 2)
                {
                    plot_option = 4;
                    continue;
                }
                else if (index == 0)
                {
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
            }
            else if (plot_option == 3) // Analyze
            {
                while (1)
                {
                    printf("Analyze Mode:\n");
                    printf("  q: Return To Menu. \n");
                    printf("  0: Find Mean. \n");
                    printf("  1: Find MD (Mean Deviation). \n");
                    printf("  2: Find SD (Standard Deviation). \n");
                    printf(": ");
                    fgets(input, sizeof(input), stdin);
                    printf("\n");

                    if (CheckQuitCondition(input))
                    {
                        plot_option = -1;
                        break;
                    }

                    int analyze_mode;
                    sscanf(input, "%d", &analyze_mode);

                    CTP_PARAM *db_analyze;
                    if (analyze_mode == 0)
                    {
                        printf("Getting Mean:\n");
                        db_analyze = ctp_analyze_mean(dataSet);
                    }
                    else if (analyze_mode == 1)
                    {
                        printf("Getting MD:\n");
                        db_analyze = ctp_analyze_md(dataSet);
                    }

                    else if (analyze_mode == 2)
                    {
                        printf("Getting SD:\n");
                        db_analyze = ctp_analyze_sd(dataSet);
                    }
                    ctp_plot_analyze(dataSet, db_analyze);
                    printf("\n");
                }
            }
            else if (plot_option == 4) // Sort
            {
                printf("Sort Mode:\n");
                printf("  q: Return To Menu \n");
                printf("  0: Sort Default Data\n");
                printf("  2: Sort Filter Data\n");
                printf(": ");
                fgets(input, sizeof(input), stdin);
                printf("\n");

                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                }
                int index;
                sscanf(input, "%d", &index);

                printf("  Select Base Sort Column \n");
                for (int i = 0; i < dataSet->db_cols_size; i++)
                {
                    printf("    %d: %s \n", i, dataSet->label[i]);
                }
                printf("  : ");

                fgets(input, sizeof(input), stdin);
                printf("\n");

                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                }
                int scol;
                sscanf(input, "%d", &scol);

                int temp_Y = dataSet->chosen_Y_param;
                int temp_show = dataSet->show_begin;
                bool temp_p = dataSet->plotProperties->customize_display;
                dataSet->chosen_Y_param = scol;
                dataSet->plotProperties->customize_display = true;
                dataSet->show_end = dataSet->db_rows_size;

                if (index == 0)
                {
                    ctp_printf_properties(dataSet);
                    ctp_sort(dataSet);
                }
                else if (index == 1)
                {
                    ctp_sort_search(dataSet);
                }

                dataSet->chosen_Y_param = temp_Y;
                dataSet->show_begin = temp_show;
                dataSet->plotProperties->customize_display = temp_p;
            }
            else if (plot_option == 5) // Save
            {
                printf("Save Mode:\n");
                printf("  0: Save this default data.\n");
                printf("  1: Save this filter data.\n");
                printf(": ");
                fgets(input, sizeof(input), stdin);
                printf("\n");
                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                }
                int index;
                sscanf(input, "%d", &index);

                printf("Choose your data path (ex: your_path/file.csv), Return to Menu(q):\n");
                printf(": ");
                fgets(input, sizeof(input), stdin);
                printf("\n");
                if (CheckQuitCondition(input))
                {
                    plot_option = -1;
                    continue;
                }
                // Remove newline if present
                char *newline = strchr(input, '\n');
                if (newline)
                    *newline = '\0';

                fpt = fopen(input, "w");

                if (fpt == NULL)
                {
                    printf("Error opening file\n");
                    continue;
                }

                for (int i = 0; i < dataSet->db_cols_size; i++)
                {
                    fprintf(fpt, "%s", dataSet->label[i]);
                    if (i != dataSet->db_cols_size - 1)
                        fprintf(fpt, ",");
                }
                fprintf(fpt, "\n");

                for (int i = 0; i < dataSet->db_rows_size; i++)
                {
                    for (int j = 0; j < dataSet->db_cols_size; j++)
                    {
                        if (index == 0)
                            fprintf(fpt, "%lf", dataSet->db[j][i]);
                        else
                            fprintf(fpt, "%lf", dataSet->db_search[j][i]);
                        if (j != dataSet->db_cols_size - 1)
                            fprintf(fpt, ",");
                    }
                    fprintf(fpt, "\n");
                }

                fclose(fpt);
            }
        }
    }

    ctp_free_dataset(dataSet);

    print_ascii_art();
    printf("End of Program, Thank you.\n\n");

    return 0;
}