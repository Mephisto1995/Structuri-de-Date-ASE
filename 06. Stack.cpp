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

void display(Stack* stack)
{
	while (stack)
	{
		cout << "\nID: " << stack->s.id;
		cout << "\nName: " << stack->s.name;
		cout << "\nAverage: " << stack->s.average;
		cout << "\nNumber of marks: " << stack->s.sizeMarks;
		cout << "\nMarks: ";
		for (int i = 0; i < stack->s.sizeMarks; i++)
		{
			cout << stack->s.marks[i] << " ";
		}
		cout << "\n======================" << endl;
		stack = stack->next;
	}
}

void destroyStack(Stack* &stack)
{
	while (stack)
	{
		Stack* temp = stack->next;
		delete[] stack->s.marks;
		delete[] stack->s.name;
		delete stack;
		stack = temp;
	}

	if (stack == 0)
	{
		cout << "\ndestroyStack: stack successfully destroyed!" << endl;
	}
	else
	{
		cout << "\ndestroyStack: Error on destroy. Please check!" << endl;
	}
}

void main()
{
	Student s;
	Stack* stack = 0;

	while (!file.eof())
	{
		readFromFile(s);
		insert(stack, s);
	}

	display(stack);
	destroyStack(stack);
	getch();
}
