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

struct CircularList
{
	CircularList* lastNode;
	Student s;
	CircularList* node;

	CircularList() :
		node(nullptr),
		lastNode(nullptr)
	{}

	void Insert(const Student& s)
	{
		CircularList* temp = new CircularList;
		temp->s = s;
		
		if (node == nullptr)
		{
			node = temp;
			lastNode = temp;
		}
		else
		{
			temp->node = node;
			lastNode->node = temp;
			lastNode = temp;
		}
	}

	void Display()
	{
		CircularList* temp = node;
		while (temp->node != node)
		{
			std::cout << temp->s << std::endl;
			temp = temp->node;
		}
		
		// Also displaying the last element
		std::cout << temp->s << std::endl;
	}

	void ReleaseMemory()
	{
		CircularList* temp = nullptr;
		while (node != lastNode)
		{
			temp = node->node;
			node->s.ReleaseMemory();
			delete node;
			node = temp;
		}
		// Releasing memory for last node
		node->s.ReleaseMemory();
		delete node;
		node = nullptr;
		lastNode = nullptr;
	}

	// We can basically remove by any criteria, but ID is by far the easiest to implement
	void RemoveByID(const int& id)
	{
		CircularList* backupNode = node;
		bool isFirstElement = true;

		// We only treat 2 cases here, because the case which we remove the last node object
		// gets treated outside the while loop
		while (node != lastNode)
		{
			if (node->s.mID == id)
			{
				if (isFirstElement == true)
				{
					CircularList* temp = node->node;
					lastNode->node = node->node;
					node->s.ReleaseMemory();
					delete node;
					node = temp;
					backupNode = temp;
					return; // We can even end the function call here
				}
				else
				{
					CircularList* temp = backupNode;
					while (temp->node != node)
					{
						temp = temp->node;
					}
					temp->node = node->node;
					node->s.ReleaseMemory();
					delete node;
					node = backupNode; // reset
					return;
				}
			}
			
			isFirstElement = false;
			node = node->node;
		}

		if (lastNode->s.mID == id)
		{
			CircularList* temp = backupNode;
			while (temp->node != lastNode)
			{
				temp = temp->node;
			}
			temp->node = lastNode->node; // same as if we've putted backupNode
			lastNode->s.ReleaseMemory();
			delete lastNode;
			lastNode = temp;
			node = backupNode;
		}
	}
};

void main()
{
	CircularList list;
	Student s;
	while (!file.eof())
	{
		s.PopulateStudent();
		list.Insert(s);
		s.ReleaseMemory();
	}
	list.Display();
	list.RemoveByID(500);
	list.Display();
	list.ReleaseMemory();
	std::cin.get();
}