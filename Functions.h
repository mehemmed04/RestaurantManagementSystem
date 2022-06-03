#pragma once
#include<iostream>
#include"Start.h"
#include"Entities.h"
#include<Windows.h>
#include<conio.h>
using namespace std;


void SetCordinates(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
