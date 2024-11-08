#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 
#include <time.h>   
#include <string.h>

double calculate_typing_speed(int typing_count, double elapsed_time) {
    return (typing_count / 5.0) * (60000.0 / elapsed_time);
} 

void menu(int);
void shortcode();
void wholecode();

void CursorView(char show) { 
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void menu(int selected) {
    system("cls"); 
    CursorView(0); 

    printf("\n\n\n\n");
    printf("            ============================\n");
    printf("            |         메뉴 선택        |\n");
    printf("            ============================\n");
    if (selected == 1) {
        printf("            |\u25b6     짧은 코드 연습       |\n");
    }
    else {
        printf("            |      짧은 코드 연습       |\n");
    }
    if (selected == 2) {
        printf("            |\u25b6     긴 코드 연습         |\n");
    }
    else {
        printf("            |      긴 코드 연습         |\n");
    }
    if (selected == 3) {
        printf("            |\u25b6     종료                |\n");
    }
    else {
        printf("            |      종료                |\n");
    }
    printf("            ============================\n");
}

void shortcode() {
    const char* short_examples[10] = { "int a = 5;", "char b = 'c';", "float c = 3.14;", "a++;", "printf(\"Hello\");", "int sum = a + b;", "for(int i=0; i<10; i++){}", "if(a > b){ printf(\"a is greater\"); }", "while(a < 10){ a++; }", "do { printf(\"Loop\"); } while(a < 5);" };
    int example_index;

    char user_input[100];
    int score = 0;
    clock_t start_time, end_time;
    double elapsed_time;
    double wpm;
    int typing_count = 0;
    int count = 0;

    printf("짧은 코드 타자 연습을 시작합니다! 총 5라운드가 진행됩니다.\n");
    printf("도중에 '1'을 입력하면 프로그램이 종료됩니다.\n");

    srand((unsigned int)time(NULL));

    start_time = clock();

    for (int i = 0; i < 5; i++) {
        example_index = rand() % 10;
        printf("\nRound %d: Type the following code: %s\n", i + 1, short_examples[example_index]);
        printf("\nYour Input: ");

        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = 0;

        if (strcmp(user_input, "1") == 0) {
            printf("\n사용자 요청에 의해 프로그램이 종료됩니다.\n");
            break;
        }
        if (_stricmp(user_input, short_examples[example_index]) == 0) {

            printf("Correct!\n");
            score++;
        }
        else {
            printf("Incorrect. The correct answer was: %s\n", short_examples[example_index]);
        }
        count++;
    }

    end_time = clock();

    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    wpm = calculate_typing_speed(typing_count, elapsed_time);

    printf("\nGame over! Your score is %d/%d.\n", score, count);
    printf("Typing Speed (WPM): %.2f\n", wpm);
    printf("Total elapsed time: %.2f seconds\n", elapsed_time);
}

void wholecode() {
    const char* long_examples[5] = {
        "#include <stdio.h>\nint main() {\n    printf(\"Hello, World!\");\n    return 0;\n}",
        "int factorial(int n) {\n    if (n == 0) return 1;\n    else return n * factorial(n - 1);\n}",
        "for (int i = 0; i < 10; i++) {\n    printf(\"%d\", i);\n}",
        "char str[20];\nscanf(\"%s\", str);\nprintf(\"%s\", str);",
        "int arr[5] = {1, 2, 3, 4, 5};\nfor (int i = 0; i < 5; i++) {\n    printf(\"%d\", arr[i]);\n}"
    };
    int example_index;

    char input_sentence[500];
    int score = 0;
    clock_t start_time, end_time;
    double elapsed_time;
    double wpm;
    int count = 0;
    int typing_count = 0;

    printf("긴 코드 타자 연습을 시작합니다! 총 5라운드가 진행됩니다.\n");
    printf("도중에 '1'을 입력하면 프로그램이 종료됩니다.\n");

    srand((unsigned int)time(NULL));

    start_time = clock();

    for (int i = 0; i < 5; i++) {
        example_index = rand() % 5;
        printf("\nRound %d: Type the following code:\n%s\n", i + 1, long_examples[example_index]);
        printf("\nYour Input: ");

        fgets(input_sentence, sizeof(input_sentence), stdin);
        input_sentence[strcspn(input_sentence, "\n")] = 0;

        if (strcmp(input_sentence, "1") == 0) {
            printf("\n사용자 요청에 의해 프로그램이 종료됩니다.\n");
            break;
        }

        if (_stricmp(input_sentence, long_examples[example_index]) == 0) {

            printf("Correct!\n");
            score++;
        }
        else {
            printf("Incorrect. The correct answer was:\n%s\n", long_examples[example_index]);
        }
        count++;
    }

    end_time = clock();

    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    wpm = calculate_typing_speed(typing_count, elapsed_time);

    printf("\nGame over! Your score is %d/%d.\n", score, count);
    printf("Typing Speed (WPM): %.2f\n", wpm);
    printf("Total elapsed time: %.2f seconds\n", elapsed_time);
}

int main() {
    int selected = 1;
    int key;

    system("mode con cols=80 lines=30");

    while (1) {
        menu(selected);  

        key = _getch(); 

        if (key == 224) { 
            key = _getch(); 
            if (key == 72) { 
                if (selected > 1) selected--;
            }
            else if (key == 80) { 
                if (selected < 3) selected++;
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
                printf("\n프로그램을 종료합니다.\n");
                return 0;
            }
        }
    }

    return 0;
}
