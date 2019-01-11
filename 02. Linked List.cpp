#include <iostream>
#include <fstream>
#pragma warning(disable:4996) // For disabling that annoying "use strcpy_s instead" error message
#define BUFFER_SIZE 256
#define FILENAME "Student.txt"
std::fstream file(FILENAME, std::ios::in);

struct Student
{
	int mID;
	char* mName;
	float mAverage;
	int mNumberOfMarks;
	int* mMarks;

	Student() :
		mID(0),
		mName(nullptr),
		mAverage(0.0f),
		mNumberOfMarks(0),
		mMarks(nullptr)
	{}

	// Copy constructor
	Student(const Student& other) :
		mID(other.mID),
		mAverage(other.mAverage),
		mNumberOfMarks(other.mNumberOfMarks)
	{
		mName = new char[strlen(other.mName) + 1];
		strcpy(mName, other.mName);

		mMarks = new int[mNumberOfMarks];
		for (int i = 0; i < mNumberOfMarks; i++)
		{
			mMarks[i] = other.mMarks[i];
		}
	}

	// Operator =
	Student& operator=(const Student& other)
	{
		mID = other.mID;
		mAverage = other.mAverage;
		mNumberOfMarks = other.mNumberOfMarks;

		if (mName == nullptr)
		{
			mName = new char[strlen(other.mName) + 1];
			strcpy(mName, other.mName);
		}
		else
		{
			delete[] mName;
			mName = new char[strlen(other.mName) + 1];
			strcpy(mName, other.mName);
		}

		if (mMarks == nullptr)
		{
			mMarks = new int[mNumberOfMarks];
			for (int i = 0; i < mNumberOfMarks; i++)
			{
				mMarks[i] = other.mMarks[i];
			}
		}
		else
		{
			delete[] mMarks;
			mMarks = new int[mNumberOfMarks];
			for (int i = 0; i < mNumberOfMarks; i++)
			{
				mMarks[i] = other.mMarks[i];
			}
		}

		return *this;
	}

	void ReleaseMemory()
	{
		delete[] mName;
		mName = nullptr;

		delete[] mMarks;
		mMarks = nullptr;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Student& s);
};

std::ostream& operator<<(std::ostream& stream, const Student& s)
{
	stream << "ID: " << s.mID << std::endl;
	stream << "Name: " << s.mName << std::endl;
	stream << "Average: " << s.mAverage << std::endl;
	stream << "Number of marks: " << s.mNumberOfMarks << std::endl;
	stream << "Marks: ";

	for (int i = 0; i < s.mNumberOfMarks; i++)
	{
		if (s.mMarks[i] != s.mNumberOfMarks - 1)
		{
			stream << s.mMarks[i] << ", ";
		}
		else
		{
			stream << s.mMarks[i];
		}
	}

	stream << std::endl << "=============================" << std::endl;

	return stream;
}

void PopulateStudent(Student& s)
{
	char buffer[BUFFER_SIZE];
	file >> s.mID;
	file >> buffer;
	s.mName = new char[strlen(buffer) + 1];
	strcpy(s.mName, buffer);
	file >> s.mAverage;
	file >> s.mNumberOfMarks;
	s.mMarks = new int[s.mNumberOfMarks];

	for (int index = 0; index < s.mNumberOfMarks; index++)
	{
		file >> s.mMarks[index];
	}
}

struct LinkedList
{
	Student s;
	LinkedList* node;

	LinkedList() :
		node(nullptr)
	{}

	LinkedList(const LinkedList& other) = delete;
	LinkedList& operator=(const LinkedList& other) = delete;

	void Insert(const Student& s)
	{
		LinkedList* temp = new LinkedList;
		temp->s = s;
		if (this->node == nullptr)
		{
			// If list is empty case
			node = temp;
		}
		else
		{
			LinkedList* temp2 = node;
			while (temp2->node != nullptr)
			{
				temp2 = temp2->node;
			}
			temp2->node = temp;
		}
	}

	void Display()
	{
		LinkedList* temp = node;
		while (temp != nullptr)
		{
			std::cout << temp->s << std::endl;
			temp = temp->node;
		}
	}

	void ReleaseMemory()
	{
		while (node != nullptr)
		{
			LinkedList* nextNode = node->node; // setting nextNode to be the next element in our list
			node->s.ReleaseMemory();
			delete node;
			node = nextNode;
		}
	}

	void RemoveByID(const int& id)
	{
		LinkedList* backupFirstNode = node;
		bool isFirstElement = true;
		while (node != nullptr)
		{
			if (node->s.mID == id)
			{
				// Do we remove the first element from our list?
				if (isFirstElement == true)
				{
					// Make a backup temp node to access the next element in our list
					LinkedList* temp = node->node;

					// Delete the first node
					node->s.ReleaseMemory();
					delete node;

					// Make the first node point to our next node in our list
					node = temp;

					// Also update our backup node, good practice
					backupFirstNode = temp;

					break;
				}

				// Do we remove the last element from our list?
				else if(node->node == nullptr)
				{
					// We need a temp node to point to our second to last node, so that node can become last node;
					LinkedList* temp = backupFirstNode;

					// We traverse the list until we position our temp node on the second to last node in our list
					while (temp->node != node)
					{
						temp = temp->node;
					}

					// We delete the last node
					node->s.ReleaseMemory();
					delete node;

					// We destroy the connection between the second to last node and last node, 
					//by making the first mentioned to point to nullptr, thus making it the last node in our list
					temp->node = nullptr;

					break;
				}

				else
				{
					// We remove an element in between our first and last elements from our list

					// We need a temp to point to the node before the one we want to delete
					LinkedList* temp = backupFirstNode;

					while (temp->node != node)
					{
						temp = temp->node;
					}

					// We destroy the connection between our temp node and the node we want to remove, 
					// by making our temp node to point to the next node of the removal one
					temp->node = node->node;

					// Remove the node we want
					node->s.ReleaseMemory();
					delete node;

					break;
				}
			}

			isFirstElement = false;
			node = node->node; // Accessing next node
		}

		// Reset the node to point to the first node in our list
		node = backupFirstNode;
	}
};

void main()
{
	LinkedList list;
	Student student;
	while (!file.eof())
	{
		PopulateStudent(student);
		list.Insert(student);
		student.ReleaseMemory();
	}
	list.Display();
	list.RemoveByID(300);
	list.Display();
	list.ReleaseMemory();
}
