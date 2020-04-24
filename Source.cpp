#include <iostream>
#include <vector>
#include <memory>
#pragma optimize("", off)
using std::cout;
using std::cin;
using std::endl;

class List
{
private:
	struct Node
	{
		int mData;
		std::shared_ptr<Node> mNext;

		Node() :
			mData(),
			mNext()
		{}

		Node(const Node& other) :
			mData(other.mData),
			mNext(other.mNext)
		{}

		Node& operator=(const Node& other)
		{
			mData = other.mData;
			mNext = other.mNext;

			return *this;
		}
	};
	typedef std::shared_ptr<Node> pNode;

public:
	List() :
		mHead(nullptr),
		mEnd(nullptr)
	{}

	~List()
	{
		Clear();
	}

	List(const List& other) = delete;
	List(const List&& other) = delete;
	List& operator=(const List& other) = delete;
	
	void Add(const int data)
	{
		pNode node = std::make_shared<Node>();
		node->mData = data;

		if (mHead == nullptr)
		{
			mHead = node;
			mEnd = node;
		}
		else
		{
			mEnd->mNext = node;
			mEnd = node;
		}
	}

	void Display()
	{
		pNode node = mHead;
		while (node != nullptr)
		{
			cout << "Data: " << node->mData << endl;
			node = node->mNext;
		}
	}

	void Delete(const int data)
	{
		bool isFirst = true;
		pNode backupFirst = mHead;
		
		while (backupFirst != nullptr)
		{
			if (backupFirst->mData == data)
			{
				if (isFirst)
				{
					mHead = backupFirst->mNext;
					return;
				}
				else if (backupFirst->mNext == nullptr)
				{
					pNode traverseNode = mHead;
					while (traverseNode->mNext != mEnd) // at this stage, both backupFirst and mEnd are on the same node, so using mEnd variable for reading advantages
					{
						traverseNode = traverseNode->mNext;
					}
					traverseNode->mNext = nullptr;
					mEnd = traverseNode;
					return;
				}
				else
				{
					pNode traverseNode = mHead;
					while (traverseNode->mNext != backupFirst)
					{
						traverseNode = traverseNode->mNext;
					}
					traverseNode->mNext = backupFirst->mNext;
					return;
				}
			}

			isFirst = false;
			backupFirst = backupFirst->mNext;
		}
	}

	void Erase(const int data)
	{
		bool isFirst = true;
		pNode backupFirst = mHead;

		while (backupFirst != nullptr)
		{
			if (backupFirst->mData == data)
			{
				if (isFirst)
				{
					mHead = backupFirst->mNext;
				}
				else if (backupFirst->mNext == nullptr)
				{
					pNode traverseNode = mHead;
					while (traverseNode->mNext != mEnd) // at this stage, both backupFirst and mEnd are on the same node, so using mEnd variable for reading advantages
					{
						traverseNode = traverseNode->mNext;
					}
					mEnd = traverseNode;
				}
				else
				{
					pNode traverseNode = mHead;
					while (traverseNode->mNext != backupFirst)
					{
						traverseNode = traverseNode->mNext;
					}
					traverseNode->mNext = backupFirst->mNext;
				}
			}

			isFirst = false;
			backupFirst = backupFirst->mNext;
		}
	}

	void Clear()
	{
		mHead = nullptr;
		mEnd = nullptr;
	}

private:
	pNode mHead;
	pNode mEnd;
};

/*void main()
{
	List list;
	
	for (int i = 10; i < 100; i+=10)
	{
		list.Add(i);
	}

	list.Display();

	list.Delete(10);
	list.Delete(90);
	list.Delete(50);

	cout << "============ GOGU ============" << endl;

	list.Display();

	list.Clear();
}*/

class Singleton
{
public:
	static Singleton& GetInstance()
	{
		static Singleton instance;
		return instance;
	}

	void Foo()
	{

	}

	void Bar()
	{

	}

private:
	Singleton();
};

class A : public Singleton
{

};

void main()
{
	Singleton::GetInstance().Foo();
	Singleton::GetInstance().Bar();
}