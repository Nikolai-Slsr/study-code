/* 
 * Lab 6 - Section I: File I/O Function Demonstrations
 * Demonstrates various file reading and writing functions in C
 */

#include <stdio.h>
#include <stdlib.h>

void demo_fgetc() {
    printf("\n=== Demo: fgetc() ===\n");
    printf("Reading file character by character...\n");
    
    FILE *file = fopen("sensor1.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return;
    }
    
    // Read first 50 characters
    printf("First 50 characters: ");
    for (int i = 0; i < 50; i++) {
        int c = fgetc(file);
        if (c == EOF) break;
        putchar(c);
    }
    printf("\n");
    
    fclose(file);
}

void demo_fgets() {
    printf("\n=== Demo: fgets() ===\n");
    printf("Reading file line by line...\n");
    
    FILE *file = fopen("sensor1.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return;
    }
    
    char line[100];
    int lineCount = 0;
    
    // Read first 5 lines
    while (fgets(line, sizeof(line), file) != NULL && lineCount < 5) {
        printf("Line %d: %s", lineCount + 1, line);
        lineCount++;
    }
    
    fclose(file);
}

void demo_fscanf() {
    printf("\n=== Demo: fscanf() ===\n");
    printf("Reading formatted data from file...\n");
    
    FILE *file = fopen("sensor1.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return;
    }
    
    double time, probability;
    int count = 0;
    
    // Read first 5 data points
    while (fscanf(file, "%lf %lf", &time, &probability) == 2 && count < 5) {
        printf("Data point %d: time=%.2f, probability=%.3f\n", 
               count + 1, time, probability);
        count++;
    }
    
    fclose(file);
}

void demo_fputc() {
    printf("\n=== Demo: fputc() ===\n");
    printf("Writing characters to file...\n");
    
    FILE *file = fopen("output_fputc.txt", "w");
    if (file == NULL) {
        printf("Error: Could not create file\n");
        return;
    }
    
    // Write a simple message character by character
    const char *message = "Hello from fputc!\n";
    for (int i = 0; message[i] != '\0'; i++) {
        fputc(message[i], file);
    }
    
    fclose(file);
    printf("Successfully wrote to output_fputc.txt\n");
}

void demo_fputs() {
    printf("\n=== Demo: fputs() ===\n");
    printf("Writing strings to file...\n");
    
    FILE *file = fopen("output_fputs.txt", "w");
    if (file == NULL) {
        printf("Error: Could not create file\n");
        return;
    }
    
    fputs("Line 1: This is written with fputs\n", file);
    fputs("Line 2: Another line of text\n", file);
    fputs("Line 3: File I/O is important!\n", file);
    
    fclose(file);
    printf("Successfully wrote to output_fputs.txt\n");
}

void demo_fprintf() {
    printf("\n=== Demo: fprintf() ===\n");
    printf("Writing formatted data to file...\n");
    
    FILE *file = fopen("output_fprintf.txt", "w");
    if (file == NULL) {
        printf("Error: Could not create file\n");
        return;
    }
    
    // Write formatted sensor-like data
    fprintf(file, "# Simulated Sensor Data\n");
    fprintf(file, "# Time    Probability\n");
    
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%.2f    %.3f\n", i * 0.02, 0.5 + i * 0.05);
    }
    
    fclose(file);
    printf("Successfully wrote formatted data to output_fprintf.txt\n");
}

void answer_file_location_question() {
    printf("\n=== Answer to File Location Question ===\n");
    printf("Q: What happens when you move the file to another folder?\n");
    printf("A: The program will fail to open the file because the path is no longer valid.\n\n");
    
    printf("Q: What do you need to adjust to solve the issue?\n");
    printf("A: You need to either:\n");
    printf("   1. Provide the full absolute path to the file\n");
    printf("      Example: fopen(\"/path/to/folder/sensor1.txt\", \"r\")\n");
    printf("   2. Provide the relative path from where the program is executed\n");
    printf("      Example: fopen(\"../data/sensor1.txt\", \"r\")\n");
    printf("   3. Change the current working directory before opening the file\n");
    printf("   4. Copy/move the file to the program's working directory\n");
}

int main() {
    printf("========================================\n");
    printf("Lab 6 - Section I: File I/O Demonstrations\n");
    printf("========================================\n");
    
    // Demonstrate reading functions
    demo_fgetc();
    demo_fgets();
    demo_fscanf();
    
    // Demonstrate writing functions
    demo_fputc();
    demo_fputs();
    demo_fprintf();
    
    // Answer the file location question
    answer_file_location_question();
    
    printf("\n========================================\n");
    printf("All demonstrations completed!\n");
    printf("========================================\n");
    
    return 0;
}
