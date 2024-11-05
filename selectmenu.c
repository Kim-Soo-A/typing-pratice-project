#include <stdio.h>
#include <conio.h>
#include <windows.h>
void menu(int);
void shortcode();
void wholecode();

void CursorView(char show) { //Ŀ���� �������� �ʵ��� ��
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void menu(int selected) {
    system("cls");  // �ܼ� ȭ�� �����
    CursorView(0);  // Ŀ�� �����

    // �޴� ���
    printf("\n\n\n\n");
    printf("            ============================\n");
    printf("            |         �޴� ����        |\n");
    printf("            ============================\n");
    if (selected == 1) {
        printf("            |��     Short code          |\n");
    }
    else {
        printf("            |      Short code          |\n");
    }
    if (selected == 2) {
        printf("            |��     Whole code          |\n");
    }
    else {
        printf("            |      Whole code          |\n");
    }
    if (selected == 3) {
        printf("            |��     Exit                |\n");
    }
    else {
        printf("            |      Exit                |\n");
    }
    printf("            ============================\n");
}

void shortcode() {
    printf("\n'ª�� �ڵ� ����'�� �����մϴ�.\n");
    system("pause");
}

void wholecode() {
    printf("\n'��ü �ڵ� ����'�� �����մϴ�.\n");
    system("pause");
}

int main() {
    int selected = 1; //default���� short code�� ����
    int key;

    // �ܼ� â ũ�� ����
    system("mode con cols=80 lines=30");

    while (1) {
        menu(selected);  // �޴� ��� �Լ� ȣ��

        key = _getch();  // Ű �Է� ���

        if (key == 224) {  // ����Ű�� ���
            key = _getch();  // ���� ����Ű �ڵ� �б�
            if (key == 72) {  // ���� ȭ��ǥ
                if (selected > 1) selected--;
            }
            else if (key == 80) {  // �Ʒ��� ȭ��ǥ
                if (selected < 3) selected++;
            }
        }
        else if (key == 13) {  // Enter Ű�� ���
            switch (selected) {
            case 1:
                shortcode();
                break;
            case 2:
                wholecode();
                break;
            case 3:
                printf("\n���α׷��� �����մϴ�.\n");
                return 0;
            }
        }
    }

    return 0;
}
