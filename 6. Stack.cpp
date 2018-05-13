#include <iostream> // basic input output operations
#include <fstream> // for reading from files
#include <conio.h> // for getch()
using namespace std;

#pragma warning(disable:4996)

fstream file("Student.txt", ios::in);

// Stack and Queue will be implemented as a doubly linked list.

// Stack and Queues are basically linked lists (simple or double,
// depends on how you prefer to implement them) with special
// properties, such as pop (for Stack), which removes top element
// from Stack or get (for Queue) which removes last element
// from Queue.

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

class Stack
{
public:
	Stack * prev;
	Student s;
	Stack* next;

	Stack()
	{
		// Do this, so in Add function to not make temp->next = 0 / temp->prev=0;
		prev = 0;
		next = 0;
	}
};

void insert(Stack* &stack, Student s)
{
	Stack* temp = new Stack();
	temp->s = s;

	if (stack == 0)
	{
		stack = temp;
	}
	else
	{
		// Insertion at the beginning of the List / Stack
		temp->next = stack;
		stack->prev = temp;
		stack = temp;
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

void display(Stack* list)
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

void destroyList(Stack* &list)
{
	while (list)
	{
		Stack* temp = list->next;
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
	Stack* list = 0;

	while (!file.eof())
	{
		readFromFile(s);
		insert(list, s);
	}

	display(list);
	destroyList(list);
	getch();
}