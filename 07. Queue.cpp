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

class Queue
{
public:
	Queue * prev;
	Student s;
	Queue* next;

	Queue()
	{
		// Do this, so in Add function to not make temp->next = 0 / temp->prev=0;
		prev = 0;
		next = 0;
	}
};

void insert(Queue* &queue, Queue* &endQueue, Student s)
{
	Queue* temp = new Queue();
	temp->s = s;

	if (queue == 0)
	{
		queue = temp;
		endQueue = temp;
	}
	else
	{
		endQueue->next = temp;
		temp->prev = endQueue;
		endQueue = temp;
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

void display(Queue* queue)
{
	while (queue)
	{
		cout << "\nID: " << queue->s.id;
		cout << "\nName: " << queue->s.name;
		cout << "\nAverage: " << queue->s.average;
		cout << "\nNumber of marks: " << queue->s.sizeMarks;
		cout << "\nMarks: ";
		for (int i = 0; i < queue->s.sizeMarks; i++)
		{
			cout << queue->s.marks[i] << " ";
		}
		cout << "\n======================" << endl;
		queue = queue->next;
	}
}

void destroyList(Queue* &queue)
{
	while (queue)
	{
		Queue* temp = queue->next;
		delete[] queue->s.marks;
		delete[] queue->s.name;
		delete queue;
		queue = temp;
	}

	if (queue == 0)
	{
		cout << "\ndestroyList: List successfully destroyed!" << endl;
	}
	else
	{
		cout << "\ndestroyList: Error on destroy. Please check!" << endl;
	}
}

void pop(Node* &start)
{
	Node* temp = start->next;
	delete[] start->s.name;
	delete[] start->s.marks;
	start->s.name = nullptr;
	start->s.marks = nullptr;
	delete start;
	start = temp;
}

void main()
{
	Student s;
	Queue* queue = 0, *endQueue = 0;

	while (!file.eof())
	{
		readFromFile(s);
		insert(queue, endQueue, s);
	}

	display(queue);
	destroyList(queue);
	getch();
}
