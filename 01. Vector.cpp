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

struct Vector
{
	Student* mVector;
	int mSize;

	Vector() :
		mVector(nullptr),
		mSize(0)
	{}

	Vector(const Vector& other) = delete;
	Vector& operator=(const Vector& other) = delete;

	void Add(const Student& student)
	{
		if (mSize == 0)
		{
			mVector = new Student;
			mVector[0] = student;
			mSize++;
		}
		else
		{
			Student* copyVector = new Student[mSize + 1];
			for (int index = 0; index < mSize; index++)
			{
				copyVector[index] = mVector[index];
			}
			copyVector[mSize] = student;
			delete mVector;
			mVector = copyVector;
			mSize++;
		}
	}

	void RemoveByID(const int& id)
	{
		if (mVector != nullptr)
		{
			for (int mVectorIndex = 0; mVectorIndex < mSize; mVectorIndex++)
			{
				if (mVector[mVectorIndex].mID == id)
				{
					std::cout << "Vector::RemoveByID(): Student Removed: " << mVector[mVectorIndex];
					delete[] mVector[mVectorIndex].mName;
					mVector[mVectorIndex].mName = nullptr;

					delete[] mVector[mVectorIndex].mMarks;
					mVector[mVectorIndex].mMarks = nullptr;

					// Found element case
					Student* copyVector = new Student[mSize - 1];
					for (int copyVectorIndex = 0; copyVectorIndex < mSize; copyVectorIndex++)
					{
						// Copying all students that we want to keep
						if (mVector[mVectorIndex].mID != id)
						{
							copyVector[copyVectorIndex] = mVector[copyVectorIndex];
						}
						else
						{
							copyVector[copyVectorIndex] = mVector[copyVectorIndex + 1];
						}
					}
					delete[] mVector;
					mVector = copyVector;
					mSize--;
					return; // Ending function call
				}

				if (mVectorIndex == mSize)
				{
					std::cout << "Vector::RemoveByID: ID not found! ID: " << id << std::endl;
				}
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);
};

std::ostream& operator<<(std::ostream& stream, const Vector& vector)
{
	if (vector.mVector != nullptr)
	{
		for (int i = 0; i < vector.mSize; i++)
		{
			stream << vector.mVector[i];
		}
	}
	return stream;
}

void ReleaseMemory(Vector& v)
{
	if (v.mVector != nullptr)
	{
		for (int index = 0; index < v.mSize; index++)
		{
			delete[] v.mVector[index].mName;
			v.mVector[index].mName = nullptr;

			delete[] v.mVector[index].mMarks;
			v.mVector[index].mMarks = nullptr;
		}
	}
}

void ReleaseMemory(Student& s)
{
	delete[] s.mName;
	s.mName = nullptr;

	delete[] s.mMarks;
	s.mMarks = nullptr;
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

void main()
{
	Student s;
	Vector v;
	while (!file.eof())
	{
		PopulateStudent(s);
		v.Add(s);
		ReleaseMemory(s);
	}
	std::cout << v;
	ReleaseMemory(v);
	std::cin.get();
}