#include <stdio.h>
#include <conio.h>
#include <windows.h>
void menu(int);
void shortcode();
void wholecode();

void CursorView(char show) { //커서가 깜빡이지 않도록 함
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void menu(int selected) {
    system("cls");  // 콘솔 화면 지우기
    CursorView(0);  // 커서 숨기기

    // 메뉴 출력
    printf("\n\n\n\n");
    printf("            ============================\n");
    printf("            |         메뉴 선택        |\n");
    printf("            ============================\n");
    if (selected == 1) {
        printf("            |▶     Short code          |\n");
    }
    else {
        printf("            |      Short code          |\n");
    }
    if (selected == 2) {
        printf("            |▶     Whole code          |\n");
    }
    else {
        printf("            |      Whole code          |\n");
    }
    if (selected == 3) {
        printf("            |▶     Exit                |\n");
    }
    else {
        printf("            |      Exit                |\n");
    }
    printf("            ============================\n");
}

void shortcode() {
    printf("\n'짧은 코드 연습'을 시작합니다.\n");
    system("pause");
}

void wholecode() {
    printf("\n'전체 코드 연습'을 시작합니다.\n");
    system("pause");
}

int main() {
    int selected = 1; //default값을 short code로 설정
    int key;

    // 콘솔 창 크기 설정
    system("mode con cols=80 lines=30");

    while (1) {
        menu(selected);  // 메뉴 출력 함수 호출

        key = _getch();  // 키 입력 대기

        if (key == 224) {  // 방향키인 경우
            key = _getch();  // 실제 방향키 코드 읽기
            if (key == 72) {  // 위쪽 화살표
                if (selected > 1) selected--;
            }
            else if (key == 80) {  // 아래쪽 화살표
                if (selected < 3) selected++;
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
                printf("\n프로그램을 종료합니다.\n");
                return 0;
            }
        }
    }

    return 0;
}
