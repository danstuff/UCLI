#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include <vector>
#include <assert.h>
#include <string>
#include <Windows.h>

using namespace std;

typedef unsigned int uint;

void displayTitle(){
	system("cls");

	for(uint i = 0; i < 21; i++)
		cout << char(219);
	cout << " USELESS CODING LANGUAGE INTERPERETER ";
	for(uint i = 0; i < 21; i++)
		cout << char(219);

	cout << endl;
}

void clearInputBuffer(){
	string buffer;
	getline(cin, buffer);
}

#endif