#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //library for printing random codes
#include <string.h>
#include <conio.h> //library for reading input values ​​from the keyboard
#include <windows.h> //library for change colors
#include <time.h> //library for measuring time

// Function for hiding cursor
void CursorView(char show) { // Prevent cursor from blinking
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// Function for changing color of text
void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function for selecting menu
void menu(int selected) {
    system("cls"); // Cleaning console
    CursorView(0);

    printf("\n\n\n\n");
    printf("            ============================\n");
    printf("            |         Select menu      |\n");
    printf("            ============================\n");
    if (selected == 1) {
        printf("            |\u25b6     Short code          |\n");
    }
    else {
        printf("            |      Short code          |\n");
    }
    if (selected == 2) {
        printf("            |\u25b6     Whole code          |\n");
    }
    else {
        printf("            |      Whole code          |\n");
    }
    if (selected == 3) {
        printf("            |\u25b6     Exit                |\n");
    }
    else {
        printf("            |      Exit                |\n");
    }
    printf("            ============================\n");
}

void shortcode();
void wholecode();

int main() {
    srand((unsigned int)time(NULL)); //Initialize random generation
    int selected = 1;
    int key;

    while (1) {
        menu(selected);

        key = _getch();

        if (key == 224) { // Directional key detection
            key = _getch();
            if (key == 72 && selected > 1) { //Up arrow
                selected--;
            }
            else if (key == 80 && selected < 3) { //Down arrow
                selected++;
            }
        }
        else if (key == 13) { //Enter key detection
            switch (selected) {
            case 1:
                shortcode();
                break;
            case 2:
                wholecode();
                break;
            case 3:
                printf("\nQuit the program.\n");
                return 0;
            }
        }
    }

    return 0;
}

void shortcode() {
    system("cls"); //Clear console
    CursorView(1);

    char code[1000][1000]; //Save multiple lines of code
    int lineCount = 0;   //Number of lines read from file
    int totalCorrectCount = 0, totalInputCount = 0;
    int rounds;          //User input: number of rounds
    time_t start_time, end_time;
    int usedIndices[1000] = { 0 }; // Tracking used index to avoid print duplicate values

    FILE* file = fopen("shortcodes.txt", "r");
    if (!file) {
        printf("Error: Could not open file.\n");
        return;
    }

    while (fgets(code[lineCount], sizeof(code[lineCount]), file)) {
        code[lineCount][strcspn(code[lineCount], "\n")] = 0;
        lineCount++;
    }
    fclose(file);

    if (lineCount == 0) {
        printf("Error: shortcodes.txt file is empty.\n");
        return;
    }
    printf("This is short code practice. Press Enter key to move to the next code\n");
    printf("Press ESC key to return to the menu\n\n");
    printf("Enter the number of rounds to practice: ");
    scanf_s("%d", &rounds);
    getchar(); // Clear buffer (remove enter key)

    if (rounds > lineCount) {
        printf("Error: Number of rounds must be less than or equal to %d.\n\n", lineCount);
        printf("Press any key to return to the menu...\n");
        _getch(); // Wait for user input
        return;
    }

    time(&start_time); // Start measuring time

    int totalCodeLength = 0; //Variables to store the full code length

//Processing each code output and user input from the iteration
for (int round = 0; round < rounds; round++) {
    //Random code selection
    int randomIndex;
    do {
        randomIndex = rand() % lineCount;
    } while (usedIndices[randomIndex] == 1); //Randomization continues until an unused code is found.

    usedIndices[randomIndex] = 1; //To display code that has already been used

    printf("Type this code: %s\n", code[randomIndex]);
    char input[100] = { 0 };
    int inputIndex = 0;
    int correctCount = 0;

    //Cummation of the full length of the output code
    totalCodeLength += strlen(code[randomIndex]);

    printf("Your input: ");
    while (1) {
        char ch = _getch();

        if (ch == 27) { //ESC key detection
            return;     //Return to menu
        }
        else if (ch == '\r') { //Enter key
            break;
        }
        else if (ch == '\b' && inputIndex > 0) { //Backspace
            inputIndex--;
            printf("\b \b");
            if (code[randomIndex][inputIndex] == input[inputIndex]) {
                correctCount--; //Decrease correct count if the character was correct
            }
            totalInputCount--; //Decrease total input count
        }
        else if (isprint(ch) && inputIndex < strlen(code[randomIndex])) { //Printable character
            input[inputIndex] = ch;
            if (ch == code[randomIndex][inputIndex]) {
                setTextColor(2); // Correct: green
                correctCount++;
            }
            else {
                setTextColor(4); //Incorrect: red
            }
            printf("%c", ch);
            setTextColor(7); //Reset to default color(gray) for next line
            inputIndex++;
            totalInputCount++; //Increase total input count
        }
    }

    totalCorrectCount += correctCount;
    printf("\n");
}

    time(&end_time); // End measuring time
    double elapsed_time = difftime(end_time, start_time);
    double accuracy = ((double)totalCorrectCount / (double)totalCodeLength) * 100;
    double wpm = ((double)totalInputCount / elapsed_time) * 60;

    printf("Practice Completed!\n");
    printf("Time taken: %.2f seconds\n", elapsed_time);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Typing Speed: %.2f WPM\n", wpm);
    system("pause"); // Keep Results Screen
}

void practiceCode(const char* filename) {
    system("cls");
    CursorView(1);
    char code[500];
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'.\n", filename);
        return;
    }

    printf("This is code practice from %s. Press Enter to move to the next line.\n", filename);
    printf("Press ESC to move to menu.\n");
    setTextColor(3); //dark skyblue
    printf("Please press the space bar once instead of the Tab key.\n\n");
    setTextColor(7);

    char input[500] = { 0 };
    int totalCorrectCount = 0, totalCodeLength = 0;
    time_t start_time, end_time;
    time(&start_time); // Start measuring time

    while (fgets(code, sizeof(code), file)) {
        code[strcspn(code, "\n")] = 0; // Remove newline character
        printf("Type this code: %s\n", code);
        int len = strlen(code); //length of current code
        totalCodeLength += len; //Accumulated length of the entire code
        int inputIndex = 0;
        int correctCount = 0;

        printf("Your input: ");
        while (1) {
            char ch = _getch(); // Key Input Detection

            if (ch == 27) { // ESC key
                fclose(file);
                return; // Return to the menu
            }
            else if (ch == '\r') { // Enter key
                printf("\n");
                totalCorrectCount += correctCount; //Accumulate the number of characters matched in the current line
                break;
            }
            else if (ch == '\b' && inputIndex > 0) { // Backspace
                inputIndex--;
                printf("\b \b");
                if (code[inputIndex] == input[inputIndex]) {
                    correctCount--;
                }
            }
            else if (isprint(ch) && inputIndex < len) { //Typeable characters
                input[inputIndex] = ch;
                if (ch == code[inputIndex]) {
                    setTextColor(2); //Correct: green
                    correctCount++;
                }
                else {
                    setTextColor(4); //Incorrect: red
                }
                printf("%c", ch);
                setTextColor(7); //Reset to default color(gray)
                inputIndex++;
            }
        }
    }
    fclose(file);

    time(&end_time); // End measuring time
    double elapsed_time = difftime(end_time, start_time);
    double accuracy = ((double)totalCorrectCount / (double)totalCodeLength) * 100;
    double wpm = ((double)totalCorrectCount / elapsed_time) * 60;

    printf("Practice Completed!\n");
    printf("Time taken: %.2f seconds\n", elapsed_time);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Typing Speed: %.2f WPM\n", wpm);
    system("pause");
}

void wholecode() {
    int selected = 1; // Default selection
    int key;

    while (1) {
        system("cls");  // Clear the screen
        printf("\n\n\n\n");
        printf("            ============================\n");
        printf("            |      Select category     |\n");
        printf("            ============================\n");
       if (selected == 1) {
            printf("            |\u25b6     scanf               |\n");
        }
        else {
            printf("            |      scanf               |\n");
        }
        if (selected == 2) {
            printf("            |\u25b6     if                  |\n");
        }
        else {
            printf("            |      if                  |\n");
        }
        if (selected == 3) {
            printf("            |\u25b6     pointer             |\n");
        }
        else {
            printf("            |      pointer             |\n");
        }
        printf("            ============================\n");
        key = _getch();

        if (key == 224) { // Arrow key detection
            key = _getch();
            if (key == 72 && selected > 1) { // Up arrow
                selected--;
            }
            else if (key == 80 && selected < 3) { // Down arrow
                selected++;
            }
        }
        else if (key == 13) { // Enter key detection
            switch (selected) {
            case 1:
                practiceCode("scanf.txt");
                return;
            case 2:
                practiceCode("if.txt");
                return;
            case 3:
                practiceCode("pointer.txt");
                return;
            }
        }
        else if (key == 27) { // ESC to exit
            return;
        }
    }
}
