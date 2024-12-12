#include <stdio.h>
#include <string.h>

#include "state.h"

int main(void) {
    char file_path[100];
    char correct_file_path[100] = "../";
    char mode[10];
    scanf("%s", file_path);
    strcat(correct_file_path, file_path);
    scanf("%s", mode);
    if (strcmp(mode, "0") == 0) {
        if (print_file(correct_file_path) == 0) {
            printf("n/a\n");
        }
    } else if (strcmp(mode, "1") == 0) {
        if (sort_file(correct_file_path) == 0) {
            printf("n/a\n");
        } else
            print_file(correct_file_path);
    } else if (strcmp(mode, "2") == 0) {
        if (insert_and_sort_file(correct_file_path) == 0) {
            printf("n/a\n");
        } else
            print_file(correct_file_path);
    } else
        printf("n/a\n");
    return 0;
}

int print_file(const char *file_path) {
    int flag = 1;
    printf("%s", file_path);
    FILE *pfile = fopen(file_path, "rb");
    if (pfile == NULL) {
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
                printf("%d %d %d %d %d %d %d %d\n", record.year, record.month, record.day, record.hour,
                       record.minute, record.second, record.status, record.code);
            }
            fclose(pfile);
        }
    }
    return flag;
}

int sort_file(const char *file_path) {
    int flag = 1;
    FILE *pfile = fopen(file_path, "rb+");
    if (pfile == NULL) {
        flag = 0;
    }
    if (flag == 1) {
        int record_count = get_records_count_in_file(pfile);
        if (record_count <= 1) {
            flag = 0;
            fclose(pfile);
        }
        if (flag == 1) {
            for (int i = 0; i < record_count - 1; i++) {
                for (int j = 0; j < record_count - i - 1; j++) {
                    struct my_struct record_1 = read_record_from_file(pfile, j);
                    struct my_struct record_2 = read_record_from_file(pfile, j + 1);

                    if (record_1.year > record_2.year ||
                        (record_1.year == record_2.year && record_1.month > record_2.month) ||
                        (record_1.year == record_2.year && record_1.month == record_2.month &&
                         record_1.day > record_2.day) ||
                        (record_1.year == record_2.year && record_1.month == record_2.month &&
                         record_1.day == record_2.day && record_1.hour > record_2.hour) ||
                        (record_1.year == record_2.year && record_1.month == record_2.month &&
                         record_1.day == record_2.day && record_1.hour == record_2.hour &&
                         record_1.minute > record_2.minute) ||
                        (record_1.year == record_2.year && record_1.month == record_2.month &&
                         record_1.day == record_2.day && record_1.hour == record_2.hour &&
                         record_1.minute == record_2.minute && record_1.second > record_2.second)) {
                        swap_records_in_file(pfile, j, j + 1);
                    }
                }
            }
        }
        fclose(pfile);
    }
    return flag;
}

int insert_and_sort_file(const char *file_path) {
    int flag = 1;
    FILE *pfile = fopen(file_path, "ab+");
    if (pfile == NULL) {
        flag = 0;
    }
    if (flag == 1) {
        struct my_struct new_record;
        scanf("%d %d %d %d %d %d %d %d", &new_record.year, &new_record.month, &new_record.day,
              &new_record.hour, &new_record.minute, &new_record.second, &new_record.status, &new_record.code);
        fwrite(&new_record, sizeof(struct my_struct), 1, pfile);
        fclose(pfile);
        if (sort_file(file_path) == 0) flag = 0;
    }
    return flag;
}