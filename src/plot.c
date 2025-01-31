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

bool get_input(char *input, int sizeof_input)
{
    fgets(input, sizeof_input, stdin);
    if (CheckQuitCondition(input))
        return true;
    return false;
}

void remove_enter(char *input)
{
    char *newline = strchr(input, '\n');
    if (newline)
        *newline = '\0';
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

        if (get_input(input, sizeof(input)))
            break;
        sscanf(input, "%d", &plot_type);
        printf("\n");

        if (plot_type == 0) // Only table
        {
            plot_show[0] = true;
        }
        else if (plot_type == 1) // Only scatter
        {
            plot_show[1] = true;
        }
        else if (plot_type == 2) // Both table and scatter
        {
            plot_show[0] = true;
            plot_show[1] = true;
        }

        printf("Select Mode:\n");
        printf("  q : Exit.\n");
        printf("  0 : Write new Data.\n");
        printf("  1 : Read from file.\n");
        printf(": ");

        if (get_input(input, sizeof(input)))
            break;
        sscanf(input, "%d", &data_mode);
        printf("\n");

        // Get more specific parameters
        if (data_mode == 0) // Write manually
        {
            plot_option = 1; // Send to write new data first

            printf("Amount of you input column: ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &default_max_cols_size);
            printf("\n");

            printf("Input Name Of Column:\n");
            for (int i = 0; i < default_max_cols_size; i++)
            {
                printf("  Column[%d]: ", i);
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                strcpy(name[i], input);
            }
            printf("\n");

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

                if (get_input(input, sizeof(input)))
                {
                    semi_force_break = true;
                    break;
                }
                remove_enter(input);
                strcpy(file_path, input);
                printf("\n");

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
                remove_enter(_input);
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
                remove_enter(_input);
                _idx = strtok(_input, ",");

                int _col = 0;
                while (_idx != NULL)
                {
                    double temp;
                    sscanf(_idx, "%lf", &temp);
                    dataSet->db[_col][dataSet->db_rows_size] = (CTP_PARAM)temp;
                    _idx = strtok(NULL, ",");
                    _col++;
                }
                dataSet->db_rows_size++;
            }
            fclose(fpt);
        }
        ctp_printf_memory_usage(dataSet);

        // ----------------------------- Input State -----------------------------
        // Start Plotting
        while (1)
        {
            printf("\nGetting Plotting:\n");
            // Display the plot
            if (plot_show[0])
            {

                printf("Default Table:\n");
                ctp_plot_table(dataSet);

                printf("\n");
            }
            if (plot_show[1])
            {
                if (dataSet->db_rows_size >= 2)
                {
                    printf("Default Scatter:\n");
                    ctp_plot_scatter(dataSet);
                }
                else
                    printf("Default Plot has %d point, It has less point to plot scatter.\n", dataSet->db_rows_size);
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
                printf("  p: Check DataSet Properties\n");
                printf("  s: Setting Plot Show\n");
                printf("  ----------------------------\n");
                printf("  0: Setting All Plot Properties\n");
                printf("  1: Write New Data\n");
                printf("  2: Search Data\n");
                printf("  3: Analyze Data.\n");
                printf("  4: Sort Data\n");
                printf("  5: Save Data\n");
                printf(": ");

                if (get_input(input, sizeof(input)))
                {
                    force_break = true;
                    break;
                }
                if (!strcmp(input, "r\n"))
                {
                    ctp_free_dataset(dataSet);
                    ctp_reset_find();
                    break;
                }
                if (!strcmp(input, "p\n"))
                {
                    ctp_printf_properties(dataSet);
                    continue;
                    ;
                }
                if (!strcmp(input, "s\n"))
                {
                    while (1)
                    {
                        printf("Edit Plot Show. \n");
                        printf("  q: Return To Menu. \n");
                        printf("  0: Default Table Plot. (%s) \n", plot_show[0] ? "true " : "false");
                        printf("  1: Default Scatter Plot. (%s) \n", plot_show[1] ? "true " : "false");
                        printf("  2: Search Table Plot. (%s) \n", plot_show[2] ? "true " : "false");
                        printf("  3: Search Scatter Plot. (%s) \n", plot_show[3] ? "true " : "false");
                        printf(": ");

                        if (get_input(input, sizeof(input)))
                            break;
                        printf("\n");

                        int index;
                        sscanf(input, "%d", &index);

                        plot_show[index] = !plot_show[index];
                    }
                }
                printf("\n");

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

                if (get_input(input, sizeof(input)))
                {
                    plot_option = -1;
                    continue;
                }
                printf("\n");

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

                        if (get_input(input, sizeof(input)))
                            break;
                        printf("\n");

                        int index;
                        sscanf(input, "%d", &index);

                        plot_show[index] = !plot_show[index];
                    }
                }
                else if (setting_mode == 1)
                {
                    while (1)
                    {
                        printf("  Edit Table Plot Proproties. \n");
                        printf("    q: Return To Menu. \n");
                        printf("    0: Table Width Per Column (%d)\n", TABLE_WIDTH);
                        printf("    1: Table Back Space Of Column (%d)\n", BACK_SPACE);
                        printf("    2: Reset To Default\n");
                        printf(": ");

                        if (get_input(input, sizeof(input)))
                            break;
                        printf("\n");

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
                        printf("    q: Return To Menu. \n");
                        printf("    0: Graph Size (%d x %d)\n", SCREEN_W, SCREEN_H);
                        printf("    1: Graph Border (%d)\n", BORDER_EDGE);
                        printf("    2: Reset To Default\n");
                        printf(": ");

                        if (get_input(input, sizeof(input)))
                            break;
                        printf("\n");

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

                bool correct_input = true;
                CTP_PARAM data[dataSet->db_rows_size];
                for (int i = 0; i < dataSet->db_cols_size; i++)
                {
                    printf("  Column[%d] (%s): ", i, dataSet->label[i]);

                    if (get_input(input, sizeof(input)))
                    {
                        plot_option = -1;
                        correct_input = false;
                        break;
                    }
                    double temp;
                    sscanf(input, "%lf", &temp);
                    data[i] = (CTP_PARAM)temp;
                }
                printf("\n");

                if (correct_input)
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
                printf("  q: Return To Menu \n");
                printf("  r: Reset Filter\n");
                printf("  0: Add New Filter \n");
                printf("  1: Analyzing This Data\n");
                printf("  2: Sort This Data \n");
                printf("  3: Save This Data\n");
                printf(": ");

                if (get_input(input, sizeof(input)))
                {
                    plot_option = -1;
                    continue;
                }

                if (strcmp(input, "r\n") == 0)
                {
                    ctp_reset_find();

                    if (plot_show[2])
                    {
                        plot_show[0] = true;
                        plot_show[2] = false;
                    }

                    if (plot_show[3])
                    {
                        plot_show[1] = true;
                        plot_show[3] = false;
                    }

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
                else if (index == 3)
                {
                    plot_option = 5;
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

                    if (get_input(input, sizeof(input)))
                    {
                        plot_option = -1;
                        continue;
                    }
                    printf("\n");
                    sscanf(input, "%d", &col);

                    printf("  Select operator, Quit(q):\n");
                    printf("    e: Equal (==)\n");
                    printf("    ne: Not equal (!=)\n");
                    printf("    lt: Less than (<)\n");
                    printf("    lte: Less than or Equal (<=)\n");
                    printf("    gt: Grater than (>)\n");
                    printf("    gte: Grater than or Equal (>=)\n");
                    printf("  : ");

                    if (get_input(input, sizeof(input)))
                    {
                        plot_option = -1;
                        continue;
                    }
                    printf("\n");

                    remove_enter(input);
                    strcpy(op, input);

                    printf("  Set search value, Quit(q): ");
                    if (get_input(input, sizeof(input)))
                    {
                        plot_option = -1;
                        continue;
                    }
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
                    printf("  0: Analyze Default Data\n");
                    printf("  1: Analyze Filter Data\n");
                    printf(": ");
                    if (get_input(input, sizeof(input)))
                    {
                        plot_option = -1;
                        break;
                    }
                    printf("\n");

                    int index;
                    sscanf(input, "%d", &index);

                    while (1)
                    {
                        printf("Analyze %s:\n", (index == 0) ? "Default Data" : "Filter Data");
                        printf("  q: Return To Menu. \n");
                        printf("  0: Find Mean. \n");
                        printf("  1: Find MD (Mean Deviation). \n");
                        printf("  2: Find SD (Standard Deviation). \n");
                        printf(": ");

                        if (get_input(input, sizeof(input)))
                        {
                            printf("\n");
                            break;
                        }

                        int analyze_mode;
                        sscanf(input, "%d", &analyze_mode);

                        CTP_PARAM *db_analyze;
                        if (analyze_mode == 0)
                        {
                            printf("Getting Mean (%s):\n", (index == 0) ? "Default Data" : "Filter Data");
                            if (index == 0)
                                db_analyze = ctp_analyze_mean(dataSet);
                            else
                                db_analyze = ctp_analyze_mean_search(dataSet);
                        }
                        else if (analyze_mode == 1)
                        {
                            printf("Getting MD (%s):\n", (index == 0) ? "Default Data" : "Filter Data");
                            if (index == 0)
                                db_analyze = ctp_analyze_md(dataSet);
                            else
                                db_analyze = ctp_analyze_md_search(dataSet);
                        }

                        else if (analyze_mode == 2)
                        {
                            printf("Getting SD (%s):\n", (index == 0) ? "Default Data" : "Filter Data");
                            if (index == 0)
                                db_analyze = ctp_analyze_sd(dataSet);
                            else
                                db_analyze = ctp_analyze_sd_search(dataSet);
                        }
                        ctp_plot_analyze(dataSet, db_analyze);
                        printf("\n");
                    }
                }
            }
            else if (plot_option == 4) // Sort
            {
                printf("Sort Mode:\n");
                printf("  q: Return To Menu \n");
                printf("  0: Sort Default Data\n");
                printf("  1: Sort Filter Data\n");
                printf("  2: Save Data\n");
                printf(": ");

                if (get_input(input, sizeof(input)))
                {
                    plot_option = -1;
                    continue;
                }
                printf("\n");

                int index;
                sscanf(input, "%d", &index);

                printf("  Select Base Sort Column \n");
                for (int i = 0; i < dataSet->db_cols_size; i++)
                {
                    printf("    %d: %s \n", i, dataSet->label[i]);
                }
                printf("  : ");

                if (get_input(input, sizeof(input)))
                {
                    plot_option = -1;
                    continue;
                }
                printf("\n");

                int scol;
                sscanf(input, "%d", &scol);

                int temp_Y = dataSet->chosen_Y_param;
                int temp_show = dataSet->show_begin;
                bool temp_p = dataSet->plotProperties->customize_display;
                dataSet->chosen_Y_param = scol;
                dataSet->plotProperties->customize_display = true;
                dataSet->show_end = ((index == 0) ? dataSet->db_rows_size : dataSet->db_search_size);

                if (index == 0)
                {
                    ctp_sort(dataSet);
                }
                else if (index == 1)
                {
                    ctp_sort_search(dataSet);
                }
                else if (index == 2)
                {
                    plot_option = 5;
                    continue;
                }

                dataSet->chosen_Y_param = temp_Y;
                dataSet->show_begin = temp_show;
                dataSet->plotProperties->customize_display = temp_p;
            }
            else if (plot_option == 5) // Save
            {
                printf("Save Mode:\n");
                printf("  q: Return To Menu \n");
                printf("  0: Save this default data.\n");
                printf("  1: Save this filter data.\n");
                printf(": ");

                if (get_input(input, sizeof(input)))
                {
                    plot_option = -1;
                    continue;
                }
                printf("\n");

                int index;
                sscanf(input, "%d", &index);

                printf("Choose your data path (ex: your_path/file.csv), Return to Menu(q):\n");
                printf(": ");

                if (get_input(input, sizeof(input)))
                {
                    plot_option = -1;
                    continue;
                }
                printf("\n");

                remove_enter(input);
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

                for (int i = 0; i < ((index == 0) ? dataSet->db_rows_size : dataSet->db_search_size); i++)
                {
                    for (int j = 0; j < dataSet->db_cols_size; j++)
                    {
                        if (index == 0)
                        {
                            fprintf(fpt, "%lf", (double)dataSet->db[j][i]);
                        }
                        else
                        {
                            fprintf(fpt, "%lf", (double)dataSet->db_search[j][i]);
                        }

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