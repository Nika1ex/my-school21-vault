#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define MODE_SIZE 10
#define FILE_NAME_SIZE 100
#define FILE_SIZE 10000
#define TEXT_SIZE 1000
#define DIRECTORY_NAME_SIZE 100

void quest_1(char *file_name);
void print_file(FILE *file_path);

void quest_2(const char *file_name);

void quest_3();
void encryption(FILE *file_path, int shift);

int main(void) {
    char mode[MODE_SIZE];
    char file_name[FILE_NAME_SIZE];
    int flag = 1;
    while (flag != -1) {
        scanf("%s", mode);
        if (strcmp(mode, "-1") == 0) {
            flag = -1;
        } else if (strcmp(mode, "1") == 0) {
            quest_1(file_name);

        } else if (strcmp(mode, "2") == 0) {
            quest_2(file_name);

        } else if (strcmp(mode, "3") == 0) {
            quest_3();
        } else
            printf("n/a\n");
    }
    return 0;
}

void quest_1(char *file_name) {
    scanf(" %[^\n]", file_name);
    FILE *file_path = fopen(file_name, "r");
    if (file_path != NULL) {
        fseek(file_path, 0, SEEK_END);
        size_t file_size = ftell(file_path);
        if (file_size > 0) {
            print_file(file_path);
        } else {
            printf("n/a\n");
        }
        fclose(file_path);
    } else {
        printf("n/a\n");
    }
}

void print_file(FILE *file_path) {
    rewind(file_path);
    char ch;
    char file_contents[FILE_SIZE];
    int i = 0;
    while ((ch = fgetc(file_path)) != EOF) {
        file_contents[i++] = ch;
    }
    file_contents[i] = '\0';
    puts(file_contents);
}

void quest_2(const char *file_name) {
    FILE *file_path = fopen(file_name, "r");
    char text[TEXT_SIZE];
    if (file_path != NULL) {
        fclose(file_path);
        file_path = fopen(file_name, "a+");
        scanf(" %[^\n]", text);
        fprintf(file_path, "%s", text);
        print_file(file_path);
        fclose(file_path);
    } else {
        scanf(" %[^\n]", text);
        printf("n/a\n");
    }
}

void quest_3() {
    char directory[DIRECTORY_NAME_SIZE];
    scanf("%s", directory);
    DIR *directory_path = opendir(directory);
    if (!directory_path) {
        printf("n/a\n");
        return;
    }
    int shift;
    scanf("%d", &shift);
    struct dirent *entry;
    while ((entry = readdir(directory_path)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char full_file_name[DIRECTORY_NAME_SIZE * 20];
        snprintf(full_file_name, sizeof(full_file_name), "%s/%s", directory, entry->d_name);
        if (strstr(entry->d_name, ".c")) {
            FILE *file_path = fopen(full_file_name, "r+");
            if (!file_path) continue;
            encryption(file_path, shift);
            fclose(file_path);
        } else if (strstr(entry->d_name, ".h")) {
            FILE *file_path = fopen(full_file_name, "w");
            if (file_path) fclose(file_path);
        }
    }
    closedir(directory_path);
}

void encryption(FILE *file_path, int shift) {
    rewind(file_path);
    char ch;
    char file_contents[FILE_SIZE];
    int i = 0;
    while ((ch = fgetc(file_path)) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            file_contents[i++] = ((ch - 'a' + shift) % 26) + 'a';
        } else if (ch >= 'A' && ch <= 'Z') {
            file_contents[i++] = ((ch - 'A' + shift) % 26) + 'A';
        } else
            file_contents[i++] = ch;
    }
    rewind(file_path);
    fwrite(file_contents, sizeof(char), i, file_path);
}