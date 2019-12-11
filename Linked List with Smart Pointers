namespace DataStructures
{
	namespace Enums
	{
		enum EDATA
		{
			E_INVALID = -1,
			E_OK = 0
		};
	}

	class Node
	{
	public:
		Node() :
			mData(Enums::EDATA::E_INVALID),
			mNext(nullptr)
		{}

		int GetData() const { return mData; }
		std::shared_ptr<Node> GetNext() const { return mNext; }

		void SetData(const int data) { this->mData = data; }
		void SetNext(const std::shared_ptr<Node> next) { this->mNext = next; }

	private:
		int mData;
		std::shared_ptr<Node> mNext;
	};

	namespace LinkedList
	{
		class LinkedList
		{
		public:
			LinkedList() :
				mFirst(nullptr),
				mLast(nullptr)
			{}

			void Add(const int data)
			{
				std::shared_ptr<DataStructures::Node> node = std::make_shared<Node>();
				node->SetData(data);

				if (mFirst == nullptr)
				{
					mFirst = node;
					mLast = node;
				}
				else
				{
					mLast->SetNext(node);
					mLast = node;
				}
			}

			void Display()
			{
				std::shared_ptr<DataStructures::Node> traverseNode = mFirst;
				if (traverseNode != nullptr)
				{
					while (traverseNode != nullptr)
					{
						std::cout << traverseNode->GetData() << " ";
						traverseNode = traverseNode->GetNext();
					}
					std::cout << std::endl;
				}
			}

			void Remove(const int data)
			{
				std::shared_ptr<DataStructures::Node> backupFirst = mFirst;
				std::shared_ptr<DataStructures::Node> backupLast  = mLast;
				bool isFirstElement = true;

				while (mFirst != nullptr)
				{
					if (mFirst->GetData() == data)
					{
						if (isFirstElement)
						{
							// Remove first element;
							backupFirst = mFirst->GetNext();
							mFirst.reset(); // bad practice, always use check with std::unique before, but we need to reset it now because it's safe, given the context
							mFirst = backupFirst;
							return;
						}
						else if (mFirst == mLast)
						{
							// Remove last element;
							std::shared_ptr<DataStructures::Node> temp = backupFirst;
							while (temp->GetNext() != mLast) // same with == mFirst, but keeping this writing for readibility purposes
							{
								temp = temp->GetNext();
							}
							mLast = temp;
							mLast->SetNext(nullptr);
							mFirst.reset();
							mFirst = backupFirst;
							return;
						}
						else
						{
							// Remove inbetween;
							std::shared_ptr<Node> temp = backupFirst;
							while (temp->GetNext() != mFirst)
							{
								temp = temp->GetNext();
							}
							temp->SetNext(mFirst->GetNext());
							mFirst.reset();
							mFirst = backupFirst;
							return;
						}
					}

					mFirst = mFirst->GetNext();
					isFirstElement = false;
				}
			}

		private:
			std::shared_ptr<DataStructures::Node> mFirst;
			std::shared_ptr<DataStructures::Node> mLast;
		};
	}
}

void main()
{
	DataStructures::LinkedList::LinkedList linkedList;
	linkedList.Add(10);
	linkedList.Add(20);
	linkedList.Add(30);
	linkedList.Display();
	linkedList.Remove(20);
	linkedList.Display();
}
