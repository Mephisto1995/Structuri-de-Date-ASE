#include <iostream> // basic input output operations
#include <fstream> // for reading from files
using namespace std;
#pragma warning(disable:4996)
#define FILE_NAME "NewStudent.txt"

class Student
{
private:
	int id;
	char* name;
	float average;

public:
	Student() :
		id(-1),
		name(nullptr),
		average(0.0)
	{}

	~Student()
	{
		cout << "Destructor of Student called!" << endl;
		if (name != nullptr)
		{
			delete[] name;
			name = nullptr;
		}
	}

	// Copy constructor
	Student(const Student& s) :
		id(s.id),
		average(s.average)
	{
		name = new char[strlen(s.name) + 1];
		strcpy(name, s.name);
	}

	int getId() { return id; }
	char* getName() { return name; }
	float getAverage() { return average; }

	void setId(const int& id) { this->id = id; }
	void setName(const char* name)
	{
		if (name != nullptr)
		{
			this->name = new char[strlen(name) + 1];
			strcpy(this->name, name);
		}
	}
	void setAverage(const float& average) { this->average = average; }
};

class List
{
private:
	Student student;
	List* node;

public:
	List() :
		node(nullptr)
	{

	}

	~List()
	{
		cout << "Destructor of List called!" << endl;

		if (node != nullptr)
		{
			while (node != nullptr)
			{
				List* temp = node->node;
				node->student.~Student();
				node = temp;
			}
		}
		student.~Student();
	}

	void populateList()
	{
		fstream file;
		file.open(FILE_NAME, ios::in);
		if (file.is_open())
		{
			int id;
			char name[256];
			float average;
			while (!file.eof())
			{
				file >> id;
				file >> name;
				file >> average;
				student.setId(id);
				student.setName(name);
				student.setAverage(average);
				add(student);
			}
		}
	}

	void add(Student s)
	{
		List* temp = new List();
		temp->student.setName(s.getName());
		temp->student.setId(s.getId());
		temp->student.setAverage(s.getAverage());
		if (node == nullptr)
		{
			node = temp;
		}
		else
		{
			List* temp2 = node;
			while (temp2->node != nullptr)
			{
				temp2 = temp2->node;
			}
			temp2->node = temp;
		}
	}

	void remove(Student s)
	{
		List* backup = node;
		bool isFirst = true;
		while (node != nullptr)
		{
			if (s.getId() == node->student.getId())
			{
				if (isFirst)
				{
					List* temp = node->node; // node->next
					node->student.~Student();
					//delete[] node; <- nu facem delete de node pt ca delete cheama explicit destructoru lui List =>
					// => ar crapa, intrucat double deletion pe node, ca noi am sters studentul cu node->student.~Student();
					node = temp;
					backup = node;
					break;
				}
				else if (node->node == nullptr) // last element in our list
				{
					List* temp = backup; // temp = start
					while (temp->node != node) // while (temp->next != start)
					{
						temp = temp->node; // temp = temp->next
					}
					temp->node = nullptr;
					node->student.~Student();
					node = backup;
					break;
				}
				else
				{
					List* temp = backup;
					while (temp->node != node)
					{
						temp = temp->node;
					}
					temp->node = node->node;
					node->student.~Student();
					node = backup;
					break;
				}
			}
			isFirst = false;
			node = node->node; // node = node->next or start = start->next;
		}
	}

	void display()
	{
		if (node != nullptr)
		{
			List* backup = node;
			while (node != nullptr)
			{
				cout << "Student ID: " << node->student.getId() << endl;
				cout << "Student name: " << node->student.getName() << endl;
				cout << "Student average: " << node->student.getAverage() << endl;
				cout << "==============================" << endl;
				node = node->node;
			}
			node = backup;
		}
	}

	bool isEmpty()
	{
		return node == nullptr ? true : false;
	}
};

void main()
{
	List list;
	if (list.isEmpty())
	{
		list.populateList();
	}
	cout << endl << endl;
	Student s;
	s.setId(72000); s.setName("Dummy test"); s.setAverage(10);
	list.add(s);
	list.display();
	list.remove(s);
	cout << endl << endl;
	list.display();
	system("pause");
}