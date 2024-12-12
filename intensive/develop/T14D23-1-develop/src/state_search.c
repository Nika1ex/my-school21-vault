#include <stdio.h>
#include <string.h>

#include "state.h"

int main(void) {
    int day, month, year;
    char file_path[100];
    char correct_file_path[100] = "../";
    scanf("%s", file_path);
    strcat(correct_file_path, file_path);
    scanf("%d.%d.%d", &day, &month, &year);
    if (search_file_by_date(correct_file_path, day, month, year) == 0) {
        printf("n/a\n");
    }
    return 0;
}

int search_file_by_date(const char *file_path, int day, int month, int year) {
    int flag = 1;
    FILE *pfile = fopen(file_path, "rb");
    if (file_path == NULL) {
        flag = 0;
    }
    if (flag == 1) {
        int records_count = get_records_count_in_file(pfile);
        if (records_count == 0) {
            flag = 0;
            fclose(pfile);
        }
        if (flag == 1) {
            for (int i = 0; i < records_count; i++) {
                struct my_struct record = read_record_from_file(pfile, i);
                if (record.day == day && record.month == month && record.year == year) {
                    printf("%d", record.code);
                    fclose(pfile);
                    return flag;
                }
            }
        }
    }
    return flag;
}