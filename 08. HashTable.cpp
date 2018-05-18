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

class Node
{
public:
	Student s;
	Node* next;

	Node()
	{
		next = 0;
	}
};

class HashTable
{
public:
	Node** arrayOfNodes;
	size_t sizeNodes;
	int* keys;
	size_t sizeKeys;

	HashTable(size_t size)
	{
		this->sizeNodes = size;
		this->sizeKeys = 0;
		this->keys = 0;
		this->arrayOfNodes = 0;
	}
};

size_t getKey()
{
	// You can basically make this function to return anything you want,
	// it's completely up to you.
	return rand() % 100 + 1;
}

void addKey(HashTable& table, size_t key)
{
	if (table.keys == 0)
	{
		table.keys = new int();
		table.keys[0] = key;
		++table.sizeKeys;
	}
	else
	{
		int* copyVector = new int[table.sizeKeys + 1];
		for (int i = 0; i < table.sizeKeys; i++)
		{
			copyVector[i] = table.keys[i];
		}
		copyVector[table.sizeKeys] = key;
		delete[] table.keys;
		table.keys = copyVector;
		++table.sizeKeys;
	}
}

void insert(HashTable& table, Student s)
{
	if (table.arrayOfNodes != 0)
	{
		size_t key = getKey();
		Node* temp = new Node();
		temp->s = s;
		addKey(table, key);
		
		if (table.arrayOfNodes[key] == 0)
		{
			table.arrayOfNodes[key] = temp;
		}
		else
		{
			Node* temp2 = table.arrayOfNodes[key];
			while (temp2->next)
			{
				temp2 = temp2->next;
			}
			temp2->next = temp;
			--table.sizeKeys;
		}
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

void display(HashTable table)
{
	if (table.arrayOfNodes != 0 && table.keys != 0)
	{
		for (size_t i = 0; i < table.sizeKeys; i++)
		{
			Node* temp = table.arrayOfNodes[table.keys[i]];

			while (temp)
			{
				cout << "\nID: " << temp->s.id;
				cout << "\nName: " << temp->s.name;
				cout << "\nAverage: " << temp->s.average;
				cout << "\nNumber of marks: " << temp->s.sizeMarks;
				cout << "\nMarks: ";
				for (int i = 0; i < temp->s.sizeMarks; i++)
				{
					cout << temp->s.marks[i] << " ";
				}
				cout << "\n======================" << endl;
				temp = temp->next;
			}
		}
	}
}

void destroy(HashTable& table)
{
	if (table.arrayOfNodes != 0 && table.keys != 0)
	{
		for (size_t i = 0; i < table.sizeKeys; i++)
		{
			Node* temp = table.arrayOfNodes[table.keys[i]];

			while (temp)
			{
				Node* tempNext = temp->next;
				delete[] temp->s.marks;
				delete[] temp->s.name;
				delete temp;
				temp = tempNext;
			}
		}
	}

	delete[] table.arrayOfNodes;
	delete[] table.keys;

	table.arrayOfNodes = 0;
	table.keys = 0;
	table.sizeKeys = 0;
	table.sizeNodes = 0;

	if (table.arrayOfNodes == 0 && table.keys == 0)
	{
		cout << "\ndestroy: HashTable successfully destroyed!";
	}
	else
	{
		cout << "\ndestroy: Error on destroy. Please check!";
	}
}

void main()
{
	fstream getFileLength("Student.txt", ios::in);
	getFileLength.seekg(0, ios::end);
	int length = getFileLength.tellg();

	HashTable table(length);
	table.arrayOfNodes = new Node*[table.sizeNodes]; // or length
	for (size_t i = 0; i < table.sizeNodes; i++) //or i < length
	{
		table.arrayOfNodes[i] = 0;
	}

	Student s;
	while (!file.eof())
	{
		readFromFile(s);
		insert(table, s);
	}

	display(table);
	destroy(table);
	getch();
}
