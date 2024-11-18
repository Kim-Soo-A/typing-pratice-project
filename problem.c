#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

void CursorView(char show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void menu(int selected) {
    system("cls");  // 컴코에 화면 지우기
    CursorView(0);  // 케서 숨기기

    // 메뉴 출력
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

char generate_random_letter() {
    if (rand() % 2 == 0) {
        return 'A' + (rand() % 26);  // Generates a letter from A to Z
    }
    else {
        return 'a' + (rand() % 26); // Generates a letter from a to z
    }
}

void generate_random_word(char* word, size_t len) {
    const char* sentences[1] = { "apple" };
    int random_index = rand() % 1;
    strcpy_s(word, len, sentences[random_index]); // Use safe string copy
}

void shortcode() {
    system("cls");
    srand((unsigned int)time(NULL)); // Activate random seed
    char random_letter;
    int score = 0, count = 0, total_chars = 0, incorrect_chars = 0;
    time_t start_time, end_time;
    double elapsed_time, wpm;
    printf("Starting alphabet typing practice! There are a total of %d rounds.\n", 10);
    printf("If you enter '1' at any point, the program will end.\n");

    start_time = clock();

    for (int i = 0; i < 10; i++) {
        random_letter = generate_random_letter();
        printf("\nType %c: ", random_letter);
        int user_input = getchar(); // Get input as a character
        getchar(); // Consume the newline character
        if (user_input == '1') {
            printf("\nProgram terminated at user request.\n");
            return;
        }
        // Compare both as upper case to ensure case-insensitivity
        if (toupper(user_input) == toupper(random_letter)) {
            printf(" Correct!\n");
            score++;
        }
        else {
            printf(" Incorrect. The correct answer was %c.\n", random_letter);
            incorrect_chars++;
        }
        total_chars++;
        count++;
    }

    end_time = clock(); // End timer
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    wpm = (score / 5.0) * (600.0 / elapsed_time);
    // Display score and typing speed
    printf("\nGame over! Your score is %d/%d.\n", score, count);
    printf("Typing Speed (WPM): %.2f\n", wpm);
    printf("Accuracy: %.2f%%\n", (double)score / (score + incorrect_chars) * 100.0); // Fixed accuracy calculation
    system("pause");
}

void wholecode() {
    system("cls");
    srand((unsigned int)time(NULL)); // Activate random seed
    char random_sentence[100], input_sentence[100];
    int score = 0, total_chars = 0, incorrect_chars = 0;
    time_t start_time, end_time;
    double elapsed_time, wpm;

    start_time = clock();

    for (int i = 0; i < 5; i++) {
        generate_random_word(random_sentence, sizeof(random_sentence));
        printf("\nType \"%s\": ", random_sentence);
        fgets(input_sentence, sizeof(input_sentence), stdin);
        input_sentence[strcspn(input_sentence, "\n")] = '\0'; // Ensure newline character is removed

        /*if (strcmp(input_sentence, "1") == 0) {
            printf("\nProgram terminated at user request.\n");
            return;
        }*/
        if (strcmp(input_sentence, random_sentence) == 0) {
            //printf(" Correct!\n");
        }
        else {
            //printf(" Incorrect. The correct answer was \"%s\".\n", random_sentence);
            incorrect_chars += strlen(random_sentence);
        }
        total_chars += strlen(random_sentence);
    }

    end_time = clock(); // End timer
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    wpm = (score / 5.0) * (600.0 / elapsed_time);
    // Display score and typing speed
    printf("\nGame over! Your score is %d/%d.\n", (total_chars-incorrect_chars), total_chars);
    printf("Typing Speed (WPM): %.2f\n", wpm);
    printf("Accuracy: %.2f%%\n", (double)(total_chars-incorrect_chars) / (total_chars) * 100.0); // Fixed accuracy calculation
    system("pause");
}

//고민해볼 것. accuracy 계산시 총 길이-틀린 개수/길이로 할 것인가?-> 제시한 길이가 되면 자동으로 넘어가게?

int main() {
    int selected = 1;
    int key;

    // 콘솔 창 크기 설정
    system("mode con cols=80 lines=30");

    while (1) {
        menu(selected);

        key = _getch();

        if (key == 224) {
            key = _getch();
            if (key == 72 && selected > 1) {  // 위에서 하위로
                selected--;
            }
            else if (key == 80 && selected < 3) {  // 하위에서 위로
                selected++;
            }
        }
        else if (key == 13) {  // Enter 키인 경우
            switch (selected) {
            case 1:
                shortcode();
                break;
            case 2:
                wholecode();
                break;
            case 3:
                printf("\nQuit the program. Press Enter to confirm.\n");
                getchar(); // Wait for confirmation
                return 0;
            }
        }
    }

    return 0;
}
