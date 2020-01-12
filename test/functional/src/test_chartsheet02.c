/*****************************************************************************
 * Test cases for libxlsxwriter.
 *
 * Test to compare output against Excel files.
 *
 * Copyright 2014-2020, John McNamara, jmcnamara@cpan.org
 *
 */

#include "xlsxwriter.h"

int main() {

    lxw_workbook   *workbook   = workbook_new("test_chartsheet02.xlsx");
    lxw_worksheet  *worksheet1 = workbook_add_worksheet(workbook, NULL);
    lxw_chartsheet *chartsheet = workbook_add_chartsheet(workbook, NULL);
    lxw_worksheet  *worksheet2 = workbook_add_worksheet(workbook, NULL);
    lxw_chart      *chart      = workbook_add_chart(workbook, LXW_CHART_BAR);

    /* For testing, copy the randomly generated axis ids in the target file. */
    chart->axis_id_1 = 79858304;
    chart->axis_id_2 = 79860096;

    uint8_t data[5][3] = {
        {1, 2,  3},
        {2, 4,  6},
        {3, 6,  9},
        {4, 8,  12},
        {5, 10, 15}
    };

    int row, col;
    for (row = 0; row < 5; row++)
        for (col = 0; col < 3; col++)
            worksheet_write_number(worksheet1, row, col, data[row][col], NULL);

    chart_add_series(chart, NULL, "=Sheet1!$A$1:$A$5");
    chart_add_series(chart, NULL, "=Sheet1!$B$1:$B$5");
    chart_add_series(chart, NULL, "=Sheet1!$C$1:$C$5");

    chartsheet_set_chart(chartsheet, chart);
    chartsheet_activate(chartsheet);
    worksheet_select(worksheet2);

    return workbook_close(workbook);
}
