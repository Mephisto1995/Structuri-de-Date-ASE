#include <iostream> // basic input output operations
#include <fstream> // for reading from files
#include <conio.h> // for getch()
using namespace std;

#pragma warning(disable:4996)

fstream file("Student.txt", ios::in);

class Student
{
public:
	size_t id;
	char* name;
	float average;
	size_t sizeMarks;
	int* marks;

	Student()
	{
		id = 0;
		name = 0;
		average = 0;
		sizeMarks = 0;
		marks = 0;
	}
};

class DoublyCircularyList
{
public:
	DoublyCircularyList * prev;
	Student s;
	DoublyCircularyList* next;

	DoublyCircularyList()
	{
		// Do this, so in Add function to not make temp->next=0 / temp->prev=0;
		next = 0;
		prev = 0;
	}
};

void insert(DoublyCircularyList* &list, DoublyCircularyList* &endList, Student s)
{
	DoublyCircularyList* temp = new DoublyCircularyList();
	temp->s = s;

	if (list == 0)
	{
		list = temp;
		endList = temp;
	}
	else
	{
		temp->next = list;
		list->prev = temp;
		endList->next = temp;
		temp->prev = endList;
		endList = temp;
	}
}

void readFromFile(Student &s)
{
	char buffer[256];
	file >> s.id;
	file >> buffer;
	s.name = new char[strlen(buffer) + 1];
	strcpy(s.name, buffer);
	file >> s.average;
	file >> s.sizeMarks;
	if (s.sizeMarks > 0)
	{
		s.marks = new int[s.sizeMarks];
		for (size_t i = 0; i < s.sizeMarks; i++)
		{
			file >> s.marks[i];
		}
	}
	else
	{
		// Do nothing
	}
}

void display(DoublyCircularyList* list, DoublyCircularyList* endList)
{
	while (list != endList)
	{
		cout << "\nID: " << list->s.id;
		cout << "\nName: " << list->s.name;
		cout << "\nAverage: " << list->s.average;
		cout << "\nNumber of marks: " << list->s.sizeMarks;
		cout << "\nMarks: ";
		for (int i = 0; i < list->s.sizeMarks; i++)
		{
			cout << list->s.marks[i] << " ";
		}
		cout << "\n======================" << endl;
		list = list->next;
	}

	// Do this because when you exit while loop, 
	// you'll be positioned on last node, on endList
	// but that node won't be shown during the while loop.
	cout << "\nID: " << list->s.id;
	cout << "\nName: " << list->s.name;
	cout << "\nAverage: " << list->s.average;
	cout << "\nNumber of marks: " << list->s.sizeMarks;
	cout << "\nMarks: ";
	for (size_t i = 0; i < list->s.sizeMarks; i++)
	{
		cout << list->s.marks[i] << " ";
	}
	cout << "\n======================" << endl;
}

void destroyList(DoublyCircularyList* &list, DoublyCircularyList* &endList)
{
	while (list != endList)
	{
		DoublyCircularyList* temp = list->next;
		delete[] list->s.marks;
		delete[] list->s.name;
		delete list;
		list = temp;
	}

	// Do this because when you exit while loop, 
	// you'll be positioned on last node, on endList
	// but that node won't be shown during the while loop.
	delete[] list->s.marks;
	delete[] list->s.name;
	delete list;
	list = 0;
	endList = 0; // Or list, since list is NULL.

	if (list == 0 && endList == 0)
	{
		cout << "\ndestroyList: List successfully destroyed!" << endl;
	}
	else
	{
		cout << "\ndestroyList: Error on destroy. Please check!" << endl;
	}
}

void main()
{
	Student s;
	DoublyCircularyList* list = 0, *endList = 0;

	while (!file.eof())
	{
		readFromFile(s);
		insert(list, endList, s);
	}

	display(list, endList);
	destroyList(list, endList);
	getch();
}
