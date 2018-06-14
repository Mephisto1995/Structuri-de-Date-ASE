#include <iostream>
#include <fstream>
using namespace std;
#define HEAP_NAME "Heap.txt"
#pragma warning (disable:4996)

class Heap
{
private:
	// This vector represents the ID of a student, or the ID's of your base structure
	// Too lazy to bother creating another structure in this case.
	int* vector;
	int size;

	void populateHeap()
	{
		fstream file;
		file.open(HEAP_NAME, ios::in);
		if (file.is_open())
		{
			int intBuffer;
			int i = 0;
			file >> size;
			if (size != -1 && size > 0 && vector == nullptr)
			{
				vector = new int[size];
				while (!file.eof())
				{
					file >> intBuffer;
					vector[i++] = intBuffer;
				}

				for (int i = (size - 1) / 2; i >= 0; i--)
				{
					filtration(i);
				}
			}
			file.close();
		}
	}

	void filtration(const int& index)
	{
		int maxIndex = index;
		int leftIndex = 2 * index + 1;
		int rightIndex = 2 * index + 2;
		if (leftIndex < this->size && vector[leftIndex] < vector[maxIndex])
		{
			maxIndex = leftIndex;
		}
		if (rightIndex < this->size && vector[rightIndex] < vector[maxIndex])
		{
			maxIndex = rightIndex;
		}
		if (maxIndex != index)
		{
			// Changing variables using XOR
			vector[maxIndex] ^= vector[index] ^= vector[maxIndex] ^= vector[index];
			filtration(index);
		}
	}

public:
	Heap() { size = -1; vector = nullptr; populateHeap(); }
	~Heap()
	{
		if (vector != nullptr)
		{
			delete[] vector;
			vector = nullptr;
		}
	}
	int* getVector() { return vector; }
	int getSize() { return size; }

	void add(const int& element)
	{
		if (vector != nullptr)
		{
			int* tempVector = new int[size + 1];
			for (int i = 0; i < size; i++)
			{
				tempVector[i] = vector[i];
			}
			tempVector[size] = element;
			delete[] vector;
			vector = tempVector;
			++size;
			for (int i = (size - 1) / 2; i >= 0; i--)
			{
				filtration(i);
			}
		}
	}

	// Extraction will be from first element of vector
	// You can also make it to extract last element as well
	int extract()
	{
		if (vector != nullptr)
		{
			int retVal = vector[0];
			int* tempVector = new int[size - 1];
			for (int i = 0; i < size; i++)
			{
				tempVector[i] = vector[i + 1];
			}
			delete[] vector;
			vector = tempVector;
			--size;
			for (int i = (size - 1) / 2; i >= 0; i--)
			{
				filtration(i);
			}
			return retVal;
		}
	}

	void display()
	{
		for (int i = 0; i < size; i++)
		{
			cout << vector[i] << " ";
		}
		cout << endl;
	}
};

void main()
{
	Heap h;
	h.display();
	h.add(14);
	cout << "First element of heap is: " << h.extract() << endl;
	h.display();
	system("Pause");
}