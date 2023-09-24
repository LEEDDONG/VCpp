#include<stdio.h>
#include <conio.h>
#include <Windows.h>
#define UP 72 // -32 + 2
#define DOWN 80 // -32 + 4
#define LEFT 75 // -32 + 1
#define RIGHT 77 // -32 + 3

// 문자 배열을 비움
void reset(int array[], int x)
{
    for (int i = 0; i < x; i++) {
        array[i] = 0;
    }
}

int main()
{
    char input = ' '; // 사용자에게 입력 받음
    int array[100] = {}; // 입력받은 문자를 저장할 배열
    int index = 0; // 배열의 입력된 문자 수


    while (input != 27) {
        // 문자 배열이 꽉 찬 경우 프로그램 종료        
        if (index > 92) {
            break;
        }
        else if (index >= 5) {
            for (int i = 0; i < index; i++) {
                // DOWN DOWN UP UP
                if ((array[i] == -32 && array[i + 1] == 4) && (array[i + 2] == -32 && array[i + 3] == 4) && (array[i + 4] == -32 && array[i + 5] == 2) && (array[i + 6] == -32 && array[i + 7] == 2)) {
                    printf("\n★★★★★★★★");
                    printf("\n★치도리★\n");
                    printf("★★★★★★★★\n");
                    reset(array, index);
                    index = 0;
                }
                // LEFT UP LEFT DOWN
                if ((array[i] == -32 && array[i + 1] == 1) && (array[i + 2] == -32 && array[i + 3] == 2) && (array[i + 4] == -32 && array[i + 5] == 3) && (array[i + 6] == -32) && array[i + 7] == 4) {
                    printf("\n＠＠＠＠＠");
                    printf("\n＠나선환＠\n");
                    printf("＠＠＠＠＠\n");
                    reset(array, index);
                    index = 0;
                }

                // r UP UP 
                if ((char)(array[i] == 'r') && (array[i + 1] == -32 && array[i + 2] == 2) && (array[i + 3] == -32 && array[i + 4] == 2)) {
                    printf("\n♨♨♨♨♨♨♨♨♨♨♨♨");
                    printf("\n♨아마테라스♨\n");
                    printf("♨♨♨♨♨♨♨♨♨♨♨♨\n");
                    reset(array, index);
                    index = 0;
                }

            }
        }

        input = _getch();

        switch (input)
        {
        case LEFT:
            if (array[index - 1] == -32) {
                printf("← ");
                array[index] = 1;
            }
            else {
                printf("%c ", input);
                array[index] = input;
            }
            index++;
            break;
        case UP:
            if (array[index - 1] == -32) {
                printf("↑ ");
                array[index] = 2;
            }
            else {
                printf("%c ", input);
                array[index] = input;
            }
            index++;
            break;
        case RIGHT:
            if (array[index - 1] == -32) {
                printf("→ ");
                array[index] = 3;
            }
            else {
                printf("%c ", input);
                array[index] = input;
            }
            index++;
            break;
        case DOWN:
            if (array[index - 1] == -32) {
                printf("↓ ");
                array[index] = 4;
            }
            else {
                printf("%c ", input);
                array[index] = input;
            }
            index++;
            break;
        default:
            if (input != -32) {
                printf("%c ", input);
                array[index] = input;
            }
            else {
                array[index] = input;
            }
            index++;
            break;
        }

        Sleep(300);
    }
}