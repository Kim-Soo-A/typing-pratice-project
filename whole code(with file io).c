#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

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

void shortcode();
void wholecode();

int main() {
    int selected = 1;
    int key;

    while (1) {
        menu(selected);

        key = _getch();

        if (key == 224) {  // 화살표 키 감지
            key = _getch();
            if (key == 72 && selected > 1) {  // 위쪽 화살표
                selected--;
            }
            else if (key == 80 && selected < 3) {  // 아래쪽 화살표
                selected++;
            }
        }
        else if (key == 13) {  // 엔터 키 감지
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
    system("cls");
    CursorView(0);
    char code[100];
    FILE* file = fopen("shortcodes.txt", "r");
    int totalCorrectCount = 0, totalInputCount = 0;
    int lines = 0;
    time_t start_time, end_time;

    if (!file) {
        printf("Error: Could not open file.\n");
        return;
    }

    time(&start_time); // 전체 입력 시작 시간
    while (fgets(code, sizeof(code), file)) {
        code[strcspn(code, "\n")] = 0; // 개행 문자 제거
        printf("Type this code: %s\n", code);
        int len = strlen(code);
        char input[100] = { 0 }; // 입력 배열 초기화
        int inputIndex = 0; // 입력 배열 인덱스
        int correctCount = 0;

        printf("Your input: ");
        while (1) {
            char ch = _getch(); // 글자 입력 받기

            if (ch == '\r') { // Enter key to finish input
                break;
            }
            else if (ch == '\b' && inputIndex > 0) { // Backspace 처리
                printf("\b \b"); // 화면에서 글자 지우기
                inputIndex--; // 인덱스 감소
            }
            else if (isprint(ch) && inputIndex < len) { // 인쇄 가능한 문자만 처리
                input[inputIndex] = ch;
                if (ch == code[inputIndex]) {
                    setTextColor(2); // 정답일 경우 녹색
                    correctCount++;
                }
                else {
                    setTextColor(4); // 오답일 경우 빨간색
                }
                printf("%c", ch);
                setTextColor(7); // 기본 색상으로 복원
                inputIndex++;
            }
        }
        totalCorrectCount += correctCount;
        totalInputCount += len;
        lines++;
        printf("\n");
    }
    fclose(file);

    time(&end_time); // 전체 입력 종료 시간
    double elapsed_time = difftime(end_time, start_time);
    double accuracy = ((double)totalCorrectCount / totalInputCount) * 100;
    double wpm = ((double)totalInputCount / elapsed_time) * 60;

    printf("Time taken: %.2f seconds.\n", elapsed_time);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Typing Speed: %.2f WPM\n", wpm);
    system("pause");
}


void wholecode() {
    system("cls");
    CursorView(0);
    char code[500];
    FILE* file = fopen("wholecodes.txt", "r");
    int totalCorrectCount = 0, totalInputCount = 0;
    int lines = 0;
    time_t start_time, end_time;

    if (!file) {
        printf("Error: Could not open file.\n");
        return;
    }

    time(&start_time); // 전체 입력 시작 시간
    while (fgets(code, sizeof(code), file)) {
        code[strcspn(code, "\n")] = 0; // 개행 문자 제거
        printf("Type this code: %s\n", code);
        int len = strlen(code);
        char input[500] = { 0 };
        int inputIndex = 0;
        int correctCount = 0;

        printf("Your input: ");
        while (1) {
            char ch = _getch();

            if (ch == '\r') { // Enter key to finish input
                break;
            }
            else if (ch == '\b' && inputIndex > 0) { // Backspace 처리
                printf("\b \b");
                inputIndex--;
            }
            else if (isprint(ch) && inputIndex < len) {
                input[inputIndex] = ch;
                if (ch == code[inputIndex]) {
                    setTextColor(2);
                    correctCount++;
                }
                else {
                    setTextColor(4);
                }
                printf("%c", ch);
                setTextColor(7);
                inputIndex++;
            }
        }
        totalCorrectCount += correctCount;
        totalInputCount += len;
        lines++;
        printf("\n");
    }
    fclose(file);

    time(&end_time); // 전체 입력 종료 시간
    double elapsed_time = difftime(end_time, start_time);
    double accuracy = ((double)totalCorrectCount / totalInputCount) * 100;
    double wpm = ((double)totalInputCount / elapsed_time) * 60;

    printf("Time taken: %.2f seconds.\n", elapsed_time);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Typing Speed: %.2f WPM\n", wpm);
    system("pause");
}
