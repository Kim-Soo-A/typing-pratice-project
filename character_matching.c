#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> // Header file for random functions
#include <time.h>   // Header file for time calculations
#include <ctype.h>  // Header file for toupper function // 필요없음 
#include <string.h> // Header file for strcmp function
#include <conio.h>  // Header file for getch function

char generate_random_letter() //알파벳 랜덤으로 뽑기 
{
    if ( rand()%2 == 0)
    {
        return 'A' + (rand() % 26);  // Generates a letter from A to Z
    }
    else 
    {
        return 'a' + (rand()%26); // a~z
    }
}

void generate_random_word(char* word) //단어 랜덤으로 뽑기 
{
    const char* sentences[5] = { "apple", "mom", "dad", "banana", "cook" }; // Example words
    int random_index = rand() % 6;   // Randomly selects one of the 5 words
    strcpy(word, sentences[random_index]); 
}

int main()
{
    char random_letter, user_input;
    int score = 0;
    clock_t start_time, end_time;
    double elapsed_time; // Measured time
    double wpm; // Words per minute
    int count = 0;
    char random_sentence[100];
    char mode; // Mode selection: alphabet or word practice

    printf("Enter 'a' for alphabet typing practice, 's' for sentence typing practice: ");
    scanf("%c", &mode); // 알파벳 할지 단어 할지 정하기 

    srand(time(NULL)); // Initialize random number generator for a new pattern

    if (mode == 'a')
    {
        printf("Starting alphabet typing practice! There are a total of %d rounds.\n", 1000);
        printf("If you enter '1' at any point, the program will end.\n");

        // Start timer
        start_time = clock();

        // Begin alphabet typing practice
        for (int i = 0; i < 1000; i++)
        {
            random_letter = generate_random_letter(); // Line 11
            printf("\nRound %d: Type %c: ", i + 1, random_letter);

            user_input = _getch(); // 엔터 
            if (user_input == '1')
            {
                printf("\nProgram terminated at user request.\n");
                break;
            }
            if (user_input == random_letter) // 소문자로 입력해도 대문자로 처리 
            {
                printf("Correct!\n");
                score++;
            }
            else
            {
                printf("Incorrect. The correct answer was %c.\n", random_letter);
            }
            count++;
        }

    }
    else if (mode == 's')
    {
        printf("Starting sentence typing practice! There are a total of %d rounds.\n", 1000);
        printf("If you enter '1' at any point, the program will terminate.\n");  // Entering '1' will terminate the program

        start_time = clock();  // Start timer     

        // Begin word typing practice
        for (int i = 0; i < 1000; i++)
        {
            generate_random_word(random_sentence); // Line 17
            char input_sentence[100];

            printf("\nRound %d: Type \"%s\": ", i + 1, random_sentence);
            scanf("%s", input_sentence);

            if (input_sentence[0] == '1' && input_sentence[1] == '\0')
            {
                printf("\nProgram terminated at user request.\n");
                break;
            }

            if (strcmp(input_sentence, random_sentence) == 0)
            {
                printf("Correct!\n");
                score++; // Increase score when correct word is entered
            }
            else
            {
                printf("Incorrect. The correct answer was \"%s\".\n", random_sentence); // Display correct answer when incorrect
            }
            count++; // Keep count of the number of attempts
        }
    }
    else
    {
        printf("Invalid mode selected. Please restart the program.\n");
        return 1;
    }

    end_time = clock(); // End timer

    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Calculate typing speed in WPM
    wpm = (score / elapsed_time) * 60.0;

    // Display score and typing speed
    printf("\nGame over! Your score is %d/%d.\n", score, count);
    printf("Typing Speed (WPM): %.2f\n", wpm);
    printf("Total elapsed time: %.2f seconds\n", elapsed_time);

    return 0;
}
