#include <stdio.h>
#include <windows.h> // Include for SetConsoleOutputCP
#include <locale.h>  // Include for locale settings
#include "constant.h"
#include "plot.c"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "");

    DataSet dataSet = {
        .label = {"Score", "Sec A", "Sec B", "Sec C"},
        .db = {
            {5, 2, 3, 1, 4},
            {3, 2, 1, 4, 6},
            {3, 22, 33, 44, 55},
            {111, 222, 333, 444, 555}},
        .db_sort = {},
        .db_cols_size = 4,
        .db_rows_size = 5,
        .chosen_Y_param = 0,
        .chosen_X_param = {1, 2, 3},
        .chosen_X_param_size = 3,
        .show_size = 5};

    sort_db_by_Y_param(&dataSet);
    print_db(&dataSet, dataSet.db_sort);

    return 0;
}