#include <iostream>
#include <fstream>
#pragma warning(disable:4996) // For disabling that annoying "use strcpy_s instead" error message
#define BUFFER_SIZE 256
#define FILENAME "Student.txt"
std::fstream file(FILENAME, std::ios::in);

// Short Description
/* Stack and Queue will be implemented as a doubly linked list.

	Stack and Queues are basically linked lists (simple or double,
	depends on how you prefer to implement them) with special
	properties, such as pop (for Stack), which removes top element
	from Stack or get (for Queue) which removes last element
	from Queue.
*/

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

struct Queue
{
	Queue* prevNode;
	Student s;
	Queue* node;

	Queue() :
		prevNode(nullptr),
		node(nullptr)
	{}

	void Push(const Student& s)
	{
		Queue* temp = new Queue;
		temp->s = s;

		if (node == nullptr)
		{
			node = temp;
			prevNode = temp;
		}
		else
		{
			prevNode->node = temp;
			prevNode = temp;
		}
	}

	void Pop()
	{
		// Case when popping the only element in our Queue
		if (node == prevNode)
		{
			node->s.ReleaseMemory();
			delete node;
			node = nullptr;
			prevNode = nullptr;
		}
		else
		{
			Queue* temp = node;
			while (temp->node != prevNode)
			{
				temp = temp->node;
			}
			temp->node = nullptr;
			prevNode->s.ReleaseMemory();
			delete prevNode;
			prevNode = temp;
		}
	}

	void Show()
	{
		Queue* temp = node;
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
			Pop();
		}
	}

	void RemoveByID(const int& id)
	{
		Queue* backupFirstNode = node;
		Queue* backupLastNode  = prevNode;
		bool isFirstElement = true;

		while (node != nullptr)
		{
			if (node->s.mID == id)
			{
				if (isFirstElement)
				{
					Queue* temp = node->node;
					node->s.ReleaseMemory();
					delete node;
					node = temp;
					backupFirstNode = temp;
					return;
				}
				else if (node == prevNode)
				{
					node = backupFirstNode;
					Pop();
					return;
				}
				else
				{
					Queue* temp = backupFirstNode;
					while (temp->node != node)
					{
						temp = temp->node;
					}
					temp->node = node->node;
					node->s.ReleaseMemory();
					delete node;

					node = backupFirstNode;
					return;
				}
			}

			isFirstElement = false;
			node = node->node;
		}

		node = backupFirstNode;
		prevNode = backupLastNode;
	}
};

void main()
{
	Queue queue;
	Student s;
	while (!file.eof())
	{
		s.PopulateStudent();
		queue.Push(s);
		s.ReleaseMemory();
	}
	queue.Show();
	queue.RemoveByID(500);
	queue.Show();
	queue.ReleaseMemory();
	std::cin.get();
}