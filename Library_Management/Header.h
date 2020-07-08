#ifndef Header_h
#define Header_h
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include<string>
#include <direct.h>
#include <ctime>
#include<stdio.h>
using namespace std;
struct Day {
	int Date;
	int Month;
	int Year;
};
struct Reader {
	long Code;
	char Fullname[45];
	char ID[45];
	Day DOB;
	int Sex;
	char Email[101];
	char Address[101];
	Day CreatedDate;
	Day ExpirationDate;
};
struct DNode {
	Reader reader;
	DNode* Next;
	DNode* Prev;
};
struct DList {
	DNode* Head;
	DNode* Tail;
};
void AddReader();
void InputDay(Day& day);
void WriteReader(fstream& f, Reader reader);
//Tra ve ngay sau "day" ngay
Day CountDaysAfter(Day D1, int day);
bool LeapYear(int year);
Day GetCurrentDate();

//temporary
void PrintAllReader();

void PrintReader(Reader reader);
void PrintDay(Day day);

DNode* Initialize(Reader reader);
void AddTail(DList& dlist, DNode* reader);
//Doc file readers/readers.csv, tham so dau vao la DList, doc tat ca vao DList
void ReadReader(DList& dlist);
void InitSystemFolder();

//2.5
void FindReaderByID();

#endif