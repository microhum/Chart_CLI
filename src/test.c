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
            {2, 3, 4, 5, 6},
            {1, 2, 3, 4, 5},
            {11, 22, 33, 44, 55},
            {111, 222, 333, 444, 555}},
        .chosen_Y_param = 0,
        .chosen_X_param = {1, 2, 3},
        .chosen_X_param_amount = 3,
        .show_amount = 5};

    plot_table(&dataSet);

    return 0;
}