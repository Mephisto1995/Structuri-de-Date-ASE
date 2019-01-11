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

struct DoubleCircularList
{
	DoubleCircularList* prevNode;
	Student s;
	DoubleCircularList* node;

	DoubleCircularList() :
		prevNode(nullptr),
		node(nullptr)
	{}

	void Insert(const Student& s)
	{
		DoubleCircularList* temp = new DoubleCircularList;
		temp->s = s;

		if (node == nullptr)
		{
			node = temp;
			prevNode = temp;
		}
		else
		{
			prevNode->node = temp;
			temp->prevNode = prevNode;
			temp->node = node;
			node->prevNode = temp;
			prevNode = temp;
		}
	}

	void Display()
	{
		DoubleCircularList* temp = node;
		while (temp != prevNode)
		{
			std::cout << temp->s << std::endl;
			temp = temp->node;
		}
		std::cout << temp->s << std::endl;
	}

	void ReverseDisplay()
	{
		DoubleCircularList* temp = prevNode;
		while (temp != node)
		{
			std::cout << temp->s << std::endl;
			temp = temp->prevNode;
		}
		std::cout << temp->s << std::endl;
	}

	void ReleaseMemory()
	{
		DoubleCircularList* temp = nullptr;
		while (node != prevNode)
		{
			temp = node->node;
			node->s.ReleaseMemory();
			delete node;
			node = temp;
		}
		node->s.ReleaseMemory();
		delete node;
		node = nullptr;
		prevNode = nullptr;
	}

	void RemoveByID(const int& id)
	{
		DoubleCircularList* backupFirstNode = node;
		DoubleCircularList* backupLastNode  = prevNode;
		bool isFirstElement = true;

		while (node != prevNode)
		{
			if (node->s.mID == id)
			{
				if (isFirstElement)
				{
					DoubleCircularList* temp = node->node;
					node->s.ReleaseMemory();
					delete node;
					node = temp;
					node->prevNode = prevNode;
					prevNode->node = node;
					backupFirstNode = temp;
					break;
				}
				else
				{
					DoubleCircularList* temp = node->prevNode;
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

		if (prevNode->s.mID == id)
		{
			DoubleCircularList* temp = prevNode->prevNode;
			temp->node = prevNode->node;
			backupFirstNode->prevNode = temp; // same thing with prevNode->node->prevNode = temp, but used backupFirstNode for readibility
			prevNode->s.ReleaseMemory();
			delete prevNode;
			prevNode = temp;
			backupLastNode = prevNode;
		}

		node = backupFirstNode;
		prevNode = backupLastNode;
	}
};

void main()
{
	DoubleCircularList list;
	Student s;
	while (!file.eof())
	{
		s.PopulateStudent();
		list.Insert(s);
		s.ReleaseMemory();
	}
	list.Display();
	std::cout << std::endl << std::endl;
	list.RemoveByID(500);
	list.Display();
	list.ReleaseMemory();
}