#include <iostream>
#include <fstream>
#pragma warning(disable:4996)
using namespace std;
fstream file("HeapData.txt", ios::in);

// VERY IMPORTANT:
/*
	When you remove the root element or you want to purify your whole array, you Heapify Down!!!
	When you add to last element, you Heapify Up!!! That is because the last element you've added 
	is the last one in the array, so you need to look upwards to when heaping.
*/

// This is a min Heap implementation
class Heap
{
private: // Members
	int* items;
	int capacity;
	int size;

private: // Methods
	int GetLeftChildIndex(const int& parentIndex) { return 2 * parentIndex + 1; }
	int GetRightChildIndex(const int& parentIndex) { return 2 * parentIndex + 2; }
	int GetParentIndex(const int& childIndex) { return (childIndex - 1) / 2; }

	bool HasLeftChild(const int& index) { return GetLeftChildIndex(index) < size; }
	bool HasRightChild(const int& index) { return GetRightChildIndex(index) < size; }
	bool HasParent(const int& index) { return GetParentIndex(index) < size; }

	int GetLeftChild(const int& index) { return items[GetLeftChildIndex(index)]; }
	int GetRightChild(const int& index) { return items[GetRightChildIndex(index)]; }
	int GetParent(const int& index) { return items[GetParentIndex(index)]; }

	void Swap(const int& indexOne, const int& indexTwo)
	{
		items[indexOne] ^= items[indexTwo] ^= items[indexOne] ^= items[indexTwo];
	}

	int* GetNewSize(int* &items, const int& capacity)
	{
		int* retVal = new int[capacity];
		for (int index = 0; index < size; index++)
		{
			retVal[index] = items[index];
		}
		delete[] items;
		items = nullptr; // in case we don't return this function to this->items or if the function is called without a pointer to catch it generating memory Leak
		return retVal;
	}

	void EnsureExtraCapacity()
	{
		if (size == capacity)
		{
			items = GetNewSize(items, capacity * 2);
			capacity *= 2;
		}
	}

	void HeapifyUp()
	{
		// You start from the last element and make your way up untill the first element
		// Start with the last element added
		int index = size - 1;

		// It's going up as long as there is a parent item and as long as my array is out of order
		while (HasParent(index) && GetParent(index) > items[index])
		{
			Swap(GetParentIndex(index), index);
			// Walk upwards;
			index = GetParentIndex(index);
		}
	}

	void HeapifyDown()
	{
		// Will start with root element
		int index = 0;

		// As long as I have children, keep going down and fix the heap
		// The check can only be done only on left child, because if there is no left child, then guaranteed there is no right child
		while (HasLeftChild(index))
		{
			// Set the smallerChildIndex to be equal to the smaller of the left or the right child
			int smallerChildIndex = 0;
			if (HasRightChild(index) && GetRightChild(index) < GetLeftChild(index))
			{
				smallerChildIndex = GetRightChildIndex(index);
			}
			else
			{
				smallerChildIndex = GetLeftChildIndex(index);
			}

			// Now check the parent to see if it's smaller than the two of it's children
			if (items[index] < items[smallerChildIndex])
			{
				break;
			}
			else
			{
				// If that's not the case, swap the value with the smaller child and mode down to my smaller child
				Swap(index, smallerChildIndex);
				index = smallerChildIndex;
			}
		}
	}

	void PopulateFromFile()
	{
		int item = 0;
		while(!file.eof())
		{
			file >> item;
			Add(item);
		}
	}

public:
	Heap() :
		size(0),
		capacity(10)
	{
		items = new int[capacity];
		PopulateFromFile();
		HeapifyDown();
	}

	~Heap()
	{
		cout << "Destructor called!" << endl;
		delete[] items;
		items = nullptr;
	}

	int Peek()
	{
		if (size == 0) return -1;
		return items[0];
	}

	// Extracts the first element and removes it from the array
	int Pop(const int& index = 0)
	{
		if (size == 0) return -1;
		int item = items[0];
		if (index == 0)
		{
			items[0] = items[size - 1];
		}
		else
		{
			items[0] = items[index];
		}
		size--;
		HeapifyDown();
		return item;
	}

	void Add(const int& item)
	{
		EnsureExtraCapacity();
		// Adding the element into the last spot of the array;
		items[size++] = item;
		HeapifyUp();
	}

	void Display()
	{
		cout << "========================DISPLAY HEAP========================" << endl;
		for (int index = 0; index < size; index++)
		{
			cout << items[index] << endl;
		}
	}

	// Work in progress
	void Remove(const int& information)
	{
		if (items != nullptr)
		{
			for (int index = 0; index < size; index++)
			{
				if (items[index] == information)
				{
					// Heap data structure is extremely retarded, so best bet is to remove by 
					// calling Pop method and sending it the index of the position we want to remove
					Pop(index);
					break;
				}
			}
		}
	}
};

void Initialize()
{
	Heap heap;
	heap.Add(-1995);
	heap.Display();
	heap.Remove(2);
	heap.Display();
}

void main()
{
	Initialize();
}