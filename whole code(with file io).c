#define _CRT_SECURE_NO_WARNINGS
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
    system("cls");
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
    srand((unsigned int)time(NULL)); // 난수 생성 초기화
    int selected = 1;
    int key;

    while (1) {
        menu(selected);

        key = _getch();

        if (key == 224) { // 화살표 키 감지
            key = _getch();
            if (key == 72 && selected > 1) { // 위쪽 화살표
                selected--;
            }
            else if (key == 80 && selected < 3) { // 아래쪽 화살표
                selected++;
            }
        }
        else if (key == 13) { // 엔터 키 감지
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

    char code[1000][1000]; // 여러 줄의 코드 저장
    int lineCount = 0;   // 파일에서 읽은 줄 수
    int totalCorrectCount = 0, totalInputCount = 0;
    int rounds;          // 사용자 입력: 라운드 수
    time_t start_time, end_time;
    int usedIndices[1000] = { 0 }; // 사용한 인덱스 추적

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
    getchar(); // 버퍼 클리어 (엔터키 제거)

    if (rounds > lineCount) {
        printf("Error: Number of rounds must be less than or equal to %d.\n\n", lineCount);
        printf("Press any key to return to the menu...\n");
        _getch(); // 사용자 입력 대기
        return;
    }

    time(&start_time); // 연습 시작 시간

    for (int round = 0; round < rounds; round++) {
        // 랜덤 코드 선택
        int randomIndex;
        do {
            randomIndex = rand() % lineCount;
        } while (usedIndices[randomIndex]==1); //이미 사용되지 않은 코드가 나올 때까지 계속 랜덤 추출함

        usedIndices[randomIndex] = 1; //코드 사용 표시

        printf("Type this code: %s\n", code[randomIndex]);
        char input[100] = { 0 };
        int inputIndex = 0;
        int correctCount = 0;

        printf("Your input: ");
        while (1) {
            char ch = _getch();

            if (ch == 27) { // ESC 키 감지
                return;     // 메뉴로 돌아감
            }
            else if (ch == '\r') { // Enter 키
                break;
            }
            else if (ch == '\b' && inputIndex > 0) { // Backspace
                printf("\b \b");
                inputIndex--;
            }
            else if (isprint(ch) && inputIndex < strlen(code[randomIndex])) {
                input[inputIndex] = ch;
                if (ch == code[randomIndex][inputIndex]) {
                    setTextColor(2); // 정답: 녹색
                    correctCount++;
                }
                else {
                    setTextColor(4); // 오답: 빨간색
                }
                printf("%c", ch);
                setTextColor(7); // 기본 색상 복원
                inputIndex++;
            }
        }

        totalCorrectCount += correctCount;
        totalInputCount += strlen(code[randomIndex]);
        //printf("\nCorrect: %d / %d\n", correctCount, strlen(code[randomIndex]));
        printf("\n");
    }

    time(&end_time); // 연습 종료 시간
    double elapsed_time = difftime(end_time, start_time);
    double accuracy = ((double)totalCorrectCount / totalInputCount) * 100;
    double wpm = ((double)totalInputCount / elapsed_time) * 60;

    printf("Practice Completed!\n");
    printf("Time taken: %.2f seconds\n", elapsed_time);
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
    time_t start_time, end_time;

    if (!file) {
        printf("Error: Could not open file.\n");
        return;
    }
    printf("This is whole code practice. Press Enter to move to the next line\n");
    printf("Press ESC to move to menu\n\n");

    time(&start_time);
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

            if (ch == 27) { // ESC 키 감지
                fclose(file);
                return;
            }
            else if (ch == '\r') { // Enter 키
                break;
            }
            else if (ch == '\b' && inputIndex > 0) { // Backspace
                printf("\b \b");
                inputIndex--;
            }
            else if (isprint(ch) && inputIndex < len) {
                input[inputIndex] = ch;
                if (ch == code[inputIndex]) {
                    setTextColor(2); // 정답: 녹색
                    correctCount++;
                }
                else {
                    setTextColor(4); // 오답: 빨간색
                }
                printf("%c", ch);
                setTextColor(7);
                inputIndex++;
            }
        }
        totalCorrectCount += correctCount;
        totalInputCount += len;
        printf("\n");
    }
    fclose(file);

    time(&end_time); // 연습 종료 시간
    double elapsed_time = difftime(end_time, start_time);
    double accuracy = ((double)totalCorrectCount / totalInputCount) * 100;
    double wpm = ((double)totalInputCount / elapsed_time) * 60;

    printf("\nPractice Completed!\n");
    printf("Time taken: %.2f seconds\n", elapsed_time);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Typing Speed: %.2f WPM\n", wpm);
    system("pause");
}
