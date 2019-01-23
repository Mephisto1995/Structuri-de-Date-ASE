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

struct Node
{
	Student mStudent;
	Node* mNext;

	Node()
	{
		mNext = nullptr;
	}
};

struct LinkedList
{
	Node* mNode;

	LinkedList() :
		mNode(nullptr)
	{}

	void Insert(const Student& student)
	{
		Node* temp = new Node;
		temp->mStudent = student;
		if (mNode == nullptr)
		{
			mNode = temp;
		}
		else
		{
			Node* traverseNode = mNode;
			while (traverseNode->mNext != nullptr)
			{
				traverseNode = traverseNode->mNext;
			}
			traverseNode->mNext = temp;
		}
	}

	void Display()
	{
		Node* traverseNode = mNode;
		while (traverseNode != nullptr)
		{
			cout << traverseNode->mStudent << endl;
			traverseNode = traverseNode->mNext;
		}
	}

	void ReleaseMemory()
	{
		while (mNode != nullptr)
		{
			Node* nextNode = mNode->mNext;
			mNode->mStudent.ReleaseMemory();
			delete mNode;
			mNode = nextNode;
		}
	}

	void RemoveByID(const int& id)
	{
		Node* backupMemberNode = mNode;
		bool isFirstElement = true;
		while (mNode != nullptr)
		{
			if (mNode->mStudent.mID == id)
			{
				// Do we remove the first element from our list?
				if (isFirstElement)
				{
					// Make the backup member node to point to the next element in our list
					backupMemberNode = mNode->mNext;

					// Delete the first node
					mNode->mStudent.ReleaseMemory();
					delete mNode;

					// Make the member node of our list to point to our backup member node which is our next node in our list
					mNode = backupMemberNode;
					return;
				}

				// Do we remove the last element from our list?
				else if (mNode->mNext == nullptr)
				{
					// We need a temp node to point to our second to last node, so that node can become last node;
					Node* traverseNode = backupMemberNode;

					// We traverse the list until we position our temp node on the second to last node in our list
					while (traverseNode->mNext != mNode)
					{
						traverseNode = traverseNode->mNext;
					}

					// We destroy the connection between the second to last node and last node, 
					//by making the first mentioned to point to nullptr, thus making it the last node in our list
					traverseNode->mNext = nullptr;

					// We delete the last node
					mNode->mStudent.ReleaseMemory();
					delete mNode;

					// Reset
					mNode = backupMemberNode;
					return;
				}
				else
				{
					Node* traverseNode = backupMemberNode;
					while (traverseNode->mNext != mNode)
					{
						traverseNode = traverseNode->mNext;
					}
					traverseNode->mNext = mNode->mNext;
					mNode->mStudent.ReleaseMemory();
					delete mNode;
					mNode = backupMemberNode;
					return;
				}
			}
			isFirstElement = false;
			mNode = mNode->mNext;
		}

		// This is needed in case we run into an use case where the student with the given
		// id is not in our linked list.
		mNode = backupMemberNode;
	}
};

void main()
{
	LinkedList list;
	Student s;
	while (!file.eof())
	{
		s.PopulateStudent();
		list.Insert(s);
		s.ReleaseMemory();
	}
	list.Display();
	list.RemoveByID(600);
	list.Display();
	list.ReleaseMemory();
}
