#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }
    fprintf(file, "File created successfully: %s\n", filename);
    fclose(file);
    printf("Created: %s\n", filename);
}

void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("Deleted: %s\n", filename);
    } else {
        perror("Error deleting file");
    }
}

void copyFile(const char *source, const char *destination) {
    FILE *src = fopen(source, "r");
    FILE *dest = fopen(destination, "w");
    char ch;

    if (src == NULL || dest == NULL) {
        perror("Error copying file");
        return;
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
    printf("Copied: %s ➡️ %s\n", source, destination);
}

void moveFile(const char *oldName, const char *newName) {
    if (rename(oldName, newName) == 0) {
        printf("Moved: %s ➡️ %s\n", oldName, newName);
    } else {
        perror("Error moving file");
    }
}

void writeFile(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    char content[1024];
    getchar(); 
    printf("✍️Enter content to write (end with # on a new line):\n");
    while (fgets(content, sizeof(content), stdin)) {
        if (strcmp(content, "#\n") == 0) break;
        fputs(content, file);
    }
    fclose(file);
    printf("Content written to %s\n", filename);
}

void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }
    char ch;
    printf("📖Contents of %s:\n", filename);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

int main() {
    char filename[100], newname[100];

    printf("\n📁File Management Menu:\n");
    printf("1. Create File\n");
    printf("2. Delete File\n");
    printf("3. Copy File\n");
    printf("4. Move File\n");
    printf("5. Write to File\n");
    printf("6. Read from File\n");
    printf("Choose an option: ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter filename to create: ");
            scanf("%s", filename);
            createFile(filename);
            break;

        case 2:
            printf("Enter filename to delete: ");
            scanf("%s", filename);
            deleteFile(filename);
            break;

        case 3:
            printf("Enter source filename to copy: ");
            scanf("%s", filename);
            printf("Enter destination filename: ");
            scanf("%s", newname);
            copyFile(filename, newname);
            break;

        case 4:
            printf("Enter filename to move: ");
            scanf("%s", filename);
            printf("Enter new filename/location: ");
            scanf("%s", newname);
            moveFile(filename, newname);
            break;

        case 5:
            printf("Enter filename to write to: ");
            scanf("%s", filename);
            writeFile(filename);
            break;

        case 6:
            printf("Enter filename to read from: ");
            scanf("%s", filename);
            readFile(filename);
            break;

        default:
            printf("Opps!!Invalid choice!\n");
    }

    return 0;
}

