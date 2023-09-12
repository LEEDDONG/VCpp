// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <stdio.h>
#include <conio.h>

#define ESC 27



int main()
{
	
	
	printf("♥이은석 교수님의 vc++♥");
	printf("\n");
	
	while (1)
	{
		char s;
		printf("command>");
	

		
		s = _getche();
		if (s == 27) {
			break;
		}
		while (1) {
			char enter = _getch();
			if (enter == '\r')break;
		}
		printf("\n");
		
			if (s == 'q') {
				printf("q:qwer화이팅\n");

			}
			else if (s == 'w') {
				printf("w:과제 너무 좋다\n");
			}
			else if (s == 'e') {
				printf("e:담주부턴 과제량 3배다\n");
			}
			else if (s == 'r') {
				printf("r:행복합니다\n");
			}

			else {
				printf("!에러에러!\n");
			}
		}
	}

