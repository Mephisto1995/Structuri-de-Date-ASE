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

	void PopulateStudent()
	{
		char buffer[BUFFER_SIZE];
		file >> mID;
		file >> buffer;
		mName = new char[strlen(buffer) + 1];
		strcpy(mName, buffer);
		file >> mAverage;
		file >> mNumberOfMarks;
		mMarks = new int[mNumberOfMarks];

		for (int index = 0; index < mNumberOfMarks; index++)
		{
			file >> mMarks[index];
		}
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

struct DoublyLinkedList
{
	DoublyLinkedList* prevNode; // Also our last node
	Student s;
	DoublyLinkedList* node; // Also our first node

	DoublyLinkedList() :
		prevNode(nullptr),
		node(nullptr)
	{}

	void Insert(const Student& s)
	{
		DoublyLinkedList* temp = new DoublyLinkedList;
		temp->s = s;
		if (node == nullptr)
		{
			node = temp;
			prevNode = temp;
		}
		else
		{
			// prevNode also acts as it's the last node in our list
			prevNode->node = temp;
			temp->prevNode = prevNode;
			prevNode = temp;
		}
	}

	void Display()
	{
		DoublyLinkedList* temp = node;
		while (temp != nullptr)
		{
			std::cout << temp->s << std::endl;
			temp = temp->node;
		}
	}

	void ReverseDisplay()
	{
		DoublyLinkedList* temp = prevNode;
		while (temp != nullptr)
		{
			std::cout << temp->s << std::endl;
			temp = temp->prevNode;
		}
	}

	void ReleaseMemory()
	{
		while (node != nullptr)
		{
			DoublyLinkedList* nextNode = node->node;
			node->s.ReleaseMemory();
			delete node;
			node = nextNode;
		}

		// Ultimately, this will destroy prevNode as well, so we just put him to point to nullptr,
		// to avoid having dangling pointer here
		prevNode = nullptr;
	}

	// Just for fun
	void ReverseReleaseMemory()
	{
		while (prevNode != nullptr)
		{
			DoublyLinkedList* previousNode = prevNode->prevNode;
			prevNode->s.ReleaseMemory();
			delete prevNode;
			prevNode = previousNode;
		}
		node = nullptr;
	}

	void RemoveByID(const int& id)
	{
		// For explanations on how to remove, please see my LinkedList.cpp file
		DoublyLinkedList* backupFirstNode = node;
		DoublyLinkedList* backupLastNode  = prevNode;
		bool isFirstElement = true;

		while (node != nullptr)
		{
			if (node->s.mID == id)
			{
				if (isFirstElement == true)
				{
					DoublyLinkedList* temp = node->node;
					node->s.ReleaseMemory();
					delete node;
					node = temp;
					node->prevNode = nullptr;
					backupFirstNode = temp;
					break;
				}
				else if (node == prevNode) // If we are on our last node
				{
					DoublyLinkedList* temp = node->prevNode;
					prevNode = prevNode->prevNode;
					backupLastNode = prevNode;

					// We don't need to worry for linking the previous nodes to the
					// second to last node because they are already connected
					temp->node = nullptr;

					node->s.ReleaseMemory();
					delete node;
					break;
				}
				else
				{
					DoublyLinkedList* temp = node->prevNode;
					temp->node = node->node;
					node->node->prevNode = temp;
					node->s.ReleaseMemory();
					delete node;
					break;
				}
			}

			isFirstElement = false;
			node = node->node;
		}

		// Restoring to default
		node = backupFirstNode;
	}
};

void main()
{
	DoublyLinkedList list;
	Student s;
	while (!file.eof())
	{
		s.PopulateStudent();
		list.Insert(s);
		s.ReleaseMemory();
	}
	list.Display();
	std::cout << std::endl << std::endl;
	list.RemoveByID(300);
	list.Display();
	list.ReleaseMemory();
}
