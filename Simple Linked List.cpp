#include <iostream> // basic input output operations
#include <fstream> // for reading from files
#include <conio.h> // for getch()
using namespace std;

#pragma warning(disable:4996)

fstream file("Student.txt", ios::in);

class Student
{
public:
	int id;
	char* name;
	float average;
	int sizeMarks;
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

class SimpleLinkedList
{
public:
	Student s;
	SimpleLinkedList* next;

	SimpleLinkedList()
	{
		next = 0; // Do this, so in Add function to not make temp->next=0;
	}
};

void insert(SimpleLinkedList* &list, Student s)
{
	SimpleLinkedList* temp = new SimpleLinkedList();
	temp->s = s;

	if (list == 0)
	{
		list = temp;
	}
	else
	{
		SimpleLinkedList *temp2 = list;
		while (temp2->next != 0)
		{
			temp2 = temp2->next;
		}

		temp2->next = temp;
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
		for (int i = 0; i < s.sizeMarks; i++)
		{
			file >> s.marks[i];
		}
	}
	else
	{
		// Do nothing
	}
}

void display(SimpleLinkedList* list)
{
	while (list)
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
}

void destroyList(SimpleLinkedList* &list)
{
	while (list)
	{
		SimpleLinkedList* temp = list->next;
		delete[] list->s.marks;
		delete[] list->s.name;
		delete list;
		list = temp;
	}

	if (list == 0)
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
	SimpleLinkedList* list = 0;

	while (!file.eof())
	{
		readFromFile(s);
		insert(list, s);
	}

	display(list);
	destroyList(list);
	getch();
}
