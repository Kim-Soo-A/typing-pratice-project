#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

// 커서 숨기기 함수
void CursorView(char show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// 텍스트 색상 설정 함수
void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// shortcode.txt 파일 생성 함수
void create_shortcode_file() {
    FILE* file = fopen("shortcode.txt", "w");
    if (!file) {
        printf("Error creating shortcode.txt file.\n");
        exit(1);
    }
    fprintf(file, "printf(\"Hello, World!\\n\");\n");
    fprintf(file, "int a = 5;\n");
    fprintf(file, "for (int i = 0; i < 10; i++) {\n    printf(\"%d\\n\", i);\n}\n");
    fprintf(file, "char name[50];\nscanf(\"%s\", name);\n");
    fprintf(file, "double result = a * 2.5;\n");
    fclose(file);
}

// wholecode.txt 파일 생성 함수
void create_wholecode_file() {
    FILE* file = fopen("wholecode.txt", "w");
    if (!file) {
        printf("Error creating wholecode.txt file.\n");
        exit(1);
    }
    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "#include <stdlib.h>\n");
    fprintf(file, "int main() {\n");
    fprintf(file, "    int n, i;\n");
    fprintf(file, "    printf(\"Enter a number: \");\n");
    fprintf(file, "    scanf(\"%d\", &n);\n");
    fprintf(file, "    for (i = 0; i < n; i++) {\n");
    fprintf(file, "        printf(\"Number: %d\\n\", i);\n");
    fprintf(file, "    }\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");
    fclose(file);
}

// 메뉴 출력 함수
void menu(int selected) {
    system("cls");  // 콘솔 화면 지우기
    CursorView(0);  // 커서 숨기기

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

// 파일에서 짧은 코드 읽기
void generate_short_code_from_file(char* code, size_t len) {
    FILE* file = fopen("shortcode.txt", "r");
    if (!file) {
        printf("Error opening shortcode.txt for reading.\n");
        exit(1);
    }
    char line[256];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        line_count++;
    }
    fseek(file, 0, SEEK_SET);
    int random_index = rand() % line_count;
    for (int i = 0; i <= random_index; i++) {
        fgets(line, sizeof(line), file);
    }
    line[strcspn(line, "\n")] = 0;
    strcpy_s(code, len, line);
    fclose(file);
}

// 파일에서 긴 코드 읽기
void generate_whole_code_from_file(char* code, size_t len) {
    FILE* file = fopen("wholecode.txt", "r");
    if (!file) {
        printf("Error opening wholecode.txt for reading.\n");
        exit(1);
    }
    char line[256];
    char temp_code[500] = "";
    while (fgets(line, sizeof(line), file)) {
        strcat(temp_code, line);
    }
    strcpy_s(code, len, temp_code);
    fclose(file);
}

// 짧은 코드 연습 함수
void shortcode() {
    system("cls");
    char random_code[100], user_input[100];
    int score = 0, count = 0;
    time_t start_time, end_time;
    double elapsed_time, wpm;
    FILE* file = fopen("shortcode_results.txt", "a");

    if (!file) {
        printf("Error opening file for writing.");
        return;
    }

    printf("Starting short code typing practice! There are a total of %d rounds.\n", 5);
    printf("If you enter '1' at any point, the program will end.\n");

    srand((unsigned int)time(NULL));
    start_time = time(NULL);

    for (int i = 0; i < 5; i++) {
        generate_short_code_from_file(random_code, sizeof(random_code));
        printf("\nType the following code:\n%s\n", random_code);
        printf("Your input: ");
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = '\0';

        if (strcmp(user_input, "1") == 0) {
            fprintf(file, "Program terminated at user request.\n");
            printf("\nProgram terminated at user request.\n");
            fclose(file);
            return;
        }
        int correct = 1;
        for (int j = 0; j < strlen(random_code); j++) {
            if (user_input[j] == random_code[j]) {
                setTextColor(1);  // 파란색 텍스트
                printf("%c", user_input[j]);
            }
            else {
                setTextColor(4);  // 빨간색 텍스트
                printf("%c", user_input[j]);
                correct = 0;
            }
            setTextColor(7);  // 기본 색상으로 복원
        }
        printf("\n");

        if (correct) {
            score++;
        }
        count++;
    }

    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);
    wpm = (score / elapsed_time) * 60.0;
    printf("\nYour score is %d/%d.\n", score, count);
    printf("Typing Speed (WPM): %.2f\n", wpm);
    fprintf(file, "Your score is %d/%d. Typing Speed (WPM): %.2f\n", score, count, wpm);
    fclose(file);
    system("pause");
}

// 긴 코드 연습 함수
void wholecode() {
    system("cls");
    char random_code[500], user_input[500];
    int score = 0, count = 0;
    time_t start_time, end_time;
    double elapsed_time, wpm;
    FILE* file = fopen("wholecode_results.txt", "a");

    if (!file) {
        printf("Error opening file for writing.");
        return;
    }

    printf("Starting whole code typing practice! There are a total of %d rounds.\n", 3);
    printf("If you enter '1' at any point, the program will end.\n");

    srand((unsigned int)time(NULL));
    start_time = time(NULL);

    for (int i = 0; i < 3; i++) {
        generate_whole_code_from_file(random_code, sizeof(random_code));
        printf("\nType the following code:\n%s\n", random_code);
        printf("Your input: ");
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = '\0';

        if (strcmp(user_input, "1") == 0) {
            fprintf(file, "Program terminated at user request.\n");
            printf("\nProgram terminated at user request.\n");
            fclose(file);
            return;
        }
        int correct = 1;
        for (int j = 0; j < strlen(random_code); j++) {
            if (user_input[j] == random_code[j]) {
                setTextColor(1);  // 파란색 텍스트
                printf("%c", user_input[j]);
            }
            else {
                setTextColor(4);  // 빨간색 텍스트
                printf("%c", user_input[j]);
                correct = 0;
            }
            setTextColor(7);  // 기본 색상으로 복원
        }
        printf("\n");

        if (correct) {
            score++;
        }
        count++;
    }

    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);
    wpm = (score / elapsed_time) * 60.0;
    printf("\nYour score is %d/%d.\n", score, count);
    printf("Typing Speed (WPM): %.2f\n", wpm);
    fprintf(file, "Your score is %d/%d. Typing Speed (WPM): %.2f\n", score, count, wpm);
    fclose(file);
    system("pause");
}

// 메인 함수
int main() {
    create_shortcode_file();
    create_wholecode_file();

    int selected = 1;
    int key;

    system("mode con cols=80 lines=30");

    while (1) {
        menu(selected);

        key = _getch();

        if (key == 224) {
            key = _getch();
            if (key == 72 && selected > 1) {
                selected--;
            }
            else if (key == 80 && selected < 3) {
                selected++;
            }
        }
        else if (key == 13) {
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
