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

class Vector
{
public:
	Student* arrayOfStudents;
	size_t size;

	Vector()
	{
		arrayOfStudents = 0;
		size = 0;
	}
};

void add(Vector &vector, Student s)
{
	if (vector.arrayOfStudents != 0)
	{
		if (vector.size == 0)
		{
			vector.arrayOfStudents = new Student();
			vector.arrayOfStudents[0] = s;
			++vector.size; // Although it's the same result as for vector.size++,
						   // it helps the compiler because it can prelucrates it faster;
		}
		else
		{
			Student* copyVector = new Student[vector.size + 1];
			for (int i = 0; i < vector.size; i++)
			{
				// Necessary deep copy in this situation: we are copying objects, not simple variables (int, float, etc.);
				copyVector[i].average = vector.arrayOfStudents[i].average;
				copyVector[i].id = vector.arrayOfStudents[i].id;
				copyVector[i].sizeMarks = vector.arrayOfStudents[i].sizeMarks;
				copyVector[i].name = new char[strlen(vector.arrayOfStudents[i].name) + 1];
				strcpy(copyVector[i].name, vector.arrayOfStudents[i].name);
				copyVector[i].marks = new int[vector.arrayOfStudents[i].sizeMarks];
				for (int j = 0; j < vector.arrayOfStudents[i].sizeMarks; j++)
				{
					copyVector[i].marks[j] = vector.arrayOfStudents[i].marks[j];
				}
				delete[] vector.arrayOfStudents[i].name;
				delete[] vector.arrayOfStudents[i].marks;
				vector.arrayOfStudents[i].name = nullptr;
				vector.arrayOfStudents[i].marks = nullptr;
			}
			copyVector[vector.size] = s;
			delete[] vector.arrayOfStudents;
			vector.arrayOfStudents = copyVector;
			++vector.size;
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

void display(Vector vector)
{
	if (vector.arrayOfStudents != 0)
	{
		for (size_t i = 0; i < vector.size; i++)
		{
			cout << "\nID: " << vector.arrayOfStudents[i].id;
			cout << "\nName: " << vector.arrayOfStudents[i].name;
			cout << "\nAverage: " << vector.arrayOfStudents[i].average;
			cout << "\nNumber of marks: " << vector.arrayOfStudents[i].sizeMarks;
			cout << "\nMarks: ";
			for (int j = 0; j < vector.arrayOfStudents[i].sizeMarks; j++)
			{
				cout << vector.arrayOfStudents[i].marks[j] << " ";
			}
			cout << "\n=====================";
		}
	}
}

void destroy(Vector& vector)
{
	if (vector.arrayOfStudents != 0)
	{
		for (size_t i = 0; i < vector.size; i++)
		{
			delete[] vector.arrayOfStudents[i].name;
			delete[] vector.arrayOfStudents[i].marks;

			// Avoiding creating dangling pointers
			vector.arrayOfStudents[i].name = 0;
			vector.arrayOfStudents[i].marks = 0;
		}
		delete[] vector.arrayOfStudents;
		vector.arrayOfStudents = 0;
		vector.size = 0;

		if (vector.arrayOfStudents == 0)
		{
			cout << "\ndestroy: Deletion successfull!" << endl;
		}
	}
}

void main()
{
	Vector vector;
	fstream getFileLength("Student.txt", ios::in);
	getFileLength.seekg(0, ios::end);
	size_t length = getFileLength.tellg();
	vector.arrayOfStudents = new Student[length];
	Student s;
	
	while (!file.eof())
	{
		readFromFile(s);
		add(vector, s);
	}

	display(vector);
	destroy(vector);

	getch();
}
