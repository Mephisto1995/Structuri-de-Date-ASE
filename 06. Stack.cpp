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

struct Stack
{
	Stack* lastElement;
	Student s;
	Stack* element;

	Stack() :
		lastElement(nullptr),
		element(nullptr)
	{}

	void Push(const Student& s)
	{
		Stack* temp = new Stack;
		temp->s = s;

		if (element == nullptr)
		{
			element = temp;
			lastElement = temp;
		}
		else
		{
			// Insertion at the beginning of the List / Stack
			temp->element = element;
			element = temp;
		}
	}

	void Pop()
	{
		Stack* temp = element->element;
		element->s.ReleaseMemory();
		delete element;
		element = temp;
	}

	void Show()
	{
		Stack* temp = element;
		while (temp != nullptr)
		{
			std::cout << temp->s << std::endl;
			temp = temp->element;
		}
	}

	void ReleaseMemory()
	{
		while (element != lastElement)
		{
			Pop();
		}
		element->s.ReleaseMemory();
		delete element;
		element = nullptr;
		lastElement = nullptr;
	}

	void RemoveByID(const int& id)
	{
		Stack* backupNode = element;
		bool isFirstElement = true;

		while (element != lastElement)
		{
			if (element->s.mID == id)
			{
				if (isFirstElement == true)
				{
					Pop();
					return;
				}
				else
				{
					Stack* temp = backupNode;
					while (temp->element != element)
					{
						temp = temp->element;
					}
					temp->element = element->element;
					element->s.ReleaseMemory();
					delete element;
					element = backupNode;
					return;
				}
			}

			isFirstElement = false;
			element = element->element;
		}

		if (lastElement->s.mID == id)
		{
			Stack* temp = backupNode;
			while (temp->element != lastElement)
			{
				temp = temp->element;
			}
			temp->element = nullptr;
			lastElement->s.ReleaseMemory();
			delete lastElement;
			lastElement = temp;
			element = backupNode;
		}

		element = backupNode;
	}
};

void main()
{
	Stack stack;
	Student s;
	while (!file.eof())
	{
		s.PopulateStudent();
		stack.Push(s);
		s.ReleaseMemory();
	}
	stack.Show();
	stack.RemoveByID(500);
	stack.Show();
	stack.ReleaseMemory();
}