#include <iostream>
#include <fstream>
#include <queue> // for BF traversal
#include <stack> // for DF traversal
#define GRAPH_NAME "Graph.txt"
#define STUDENT_NAME "StudentGraph.txt"
#define IN ios::in
#pragma warning (disable:4996)
using namespace std;

class Student
{
private:
	int id;
	char* name;
	float average;

public:
	Student()
	{
		id = 0; name = nullptr; average = 0.0;
	}

	~Student()
	{
		/*Don't need destructor here. Will take care of this dealocation in Graph class, when we
		deallocate the vector of students. Otherwise when we insert the last name for our student, 
		the destructor for this class will be called from populateVector() function and deletes the
		name content for our last name, hence we cannot display the last name AND it will crash because
		we call delete[] name twice on a pointer which was already deallocated.
		*/
		/*if (name != nullptr)
		{
			delete[] name;
			name = nullptr;
		}*/
	}

	int getId() { return id; }
	char* getName() { return name; }
	float getAverage() { return average; }

	void setId(const int& id) { this->id = id; }
	void setName(char* name) // Basic oop stuff, more detailed
	{
		if (name != nullptr)
		{
			this->name = new char[strlen(name) + 1];
			strcpy(this->name, name);
		}
		else // for setName(nullptr)
		{
			delete[] this->name;
			this->name = nullptr; // or this->name = name;
		}
	}
	void setAverage(const float& average) { this->average = average; }
};

class Graph
{
private:
	int** adjacentMatrix;
	int size;
	Student* vector;

	void initializeSize()
	{
		fstream file;
		file.open(GRAPH_NAME, IN);
		if (file.is_open())
		{
			file >> size;
		}
		file.close();
	}

	void initializeAdjacentMatrix()
	{
		if (size > -1 && size != 0 && adjacentMatrix == nullptr)
		{
			adjacentMatrix = new int*[size];
			for (size_t i = 0; i < size; i++)
			{
				adjacentMatrix[i] = new int[size];
			}
		}
	}

	void initializeVector()
	{
		if (size > -1 && size != 0 && vector == nullptr)
		{
			vector = new Student[size];
		}
	}

	void zeros()
	{
		if (adjacentMatrix != nullptr)
		{
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = 0; j < size; j++)
				{
					adjacentMatrix[i][j] = 0;
				}
			}
		}
	}

	void populateAdjacentMatrix()
	{
		if (adjacentMatrix != nullptr)
		{
			fstream file;
			file.open(GRAPH_NAME, IN);
			if (file.is_open())
			{
				int u, v;
				file.seekg(ios::beg + 1);
				while (!file.eof())
				{
					file >> u >> v;
					adjacentMatrix[u][v] = 1;
				}
			}
			file.close();
		}
	}

	void populateVector()
	{
		if (vector != nullptr)
		{
			fstream file;
			file.open(STUDENT_NAME, IN);
			if (file.is_open())
			{
				int i = 0;
				Student s;
				char charBuffer[256];
				int intBuffer;
				float floatBuffer;
				while (!file.eof() && i < size)
				{
					file >> intBuffer;
					file >> charBuffer;
					file >> floatBuffer;
					s.setId(intBuffer);
					s.setName(charBuffer);
					s.setAverage(floatBuffer);
					vector[i++] = s;
				}
			}
			file.close();
		}
	}

public:
	Graph()
	{
		size = -1; 
		adjacentMatrix = nullptr; 
		vector = nullptr; 

		initializeSize();
		initializeAdjacentMatrix();
		initializeVector();
		zeros();
		populateAdjacentMatrix();
		populateVector();
	}
	~Graph()
	{
		if (adjacentMatrix != nullptr)
		{
			for (size_t i = 0; i < size; i++)
			{
				delete[] adjacentMatrix[i];
				adjacentMatrix[i] = nullptr;
			}
			delete[] adjacentMatrix;
			adjacentMatrix = nullptr;
		}

		if (vector != nullptr)
		{
			for (size_t i = 0; i < size; i++)
			{
				vector[i].setName(nullptr);
			}
			delete[] vector;
			vector = nullptr;
		}
	}

	void traverseAdjacentMatrix()
	{
		if (adjacentMatrix != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					cout << adjacentMatrix[i][j] << " ";
				}
				cout << endl;
			}
		}
	}

	void checkNeighbours()
	{
		if (adjacentMatrix != nullptr)
		{
			int counter = 0;
			int nrOfArcs = 0;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (adjacentMatrix[i][j] == 1)
					{
						++counter;
					}
				}
				cout << "Line " << i << " has a total number of neighbours of: " << counter << endl;
				nrOfArcs += counter;
				counter = 0;
			}
			cout << "Number of arcs in this graph is: " << nrOfArcs << endl;
			cout << endl;
		}
	}

	// Check my ATP repo for detailed code explanation on DF traversal
	void DFTraversal()
	{
		cout << "--------------------------DEPTH FIRST TRAVERSAL--------------------------" << endl;
		if (adjacentMatrix != nullptr)
		{
			stack<int> stack; // Could've used vector to always extract last element from it,
							  // but is much more easy this way
			int node = -1;
			bool* visited = new bool[size];
			for (int i = 0; i < size; i++)
			{
				visited[i] = false;
			}
			stack.push(adjacentMatrix[0][0]);
			node = stack.top();
			cout << "Node removed from stack: " << node << endl;
			visited[0] = true;
			stack.pop();
			while (true)
			{
				for (int i = 0; i < size; i++)
				{
					if (adjacentMatrix[node][i] == 1 && visited[i] == false)
					{
						visited[i] = true;
						stack.push(i);
					}
				}
				if (stack.size() == 0)
				{
					break;
				}
				else
				{
					node = stack.top();
					cout << "Node removed from stack: " << node << endl;
					stack.pop();
				}
			}
			delete[] visited;
			visited = nullptr;
			cout << endl;
		}
	}

	// Check my ATP repo for detailed code explanation on BF traversal
	void BFTraversal()
	{
		cout << "--------------------------BREADTH FIRST TRAVERSAL--------------------------" << endl;
		if (adjacentMatrix != nullptr)
		{
			queue<int> queue;
			int node = -1;
			bool* visited = new bool[size];
			for (int i = 0; i < size; i++)
			{
				visited[i] = false;
			}
			queue.push(adjacentMatrix[0][0]);
			node = queue.front();
			cout << "Node removed from queue: " << node << endl;
			visited[0] = true;
			queue.pop();
			while (true)
			{
				for (int i = 0; i < size; i++)
				{
					if (adjacentMatrix[node][i] == 1 && visited[i] == false)
					{
						visited[i] = true;
						queue.push(i);
					}
				}
				if (queue.size() == 0)
				{
					break;
				}
				else
				{
					node = queue.front();
					cout << "Node removed from queue: " << node << endl;
					queue.pop();
				}
			}
			delete[] visited;
			visited = nullptr;
			cout << endl;
		}
	}
};

void main()
{
	Graph g;
	g.traverseAdjacentMatrix();
	g.checkNeighbours();
	g.DFTraversal();
	g.BFTraversal();
	system("pause");
}