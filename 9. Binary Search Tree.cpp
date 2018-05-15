#include <iostream> // basic input output operations
#include <fstream> // for reading from files
#include <conio.h> // for getch()
using namespace std;

#pragma warning(disable:4996)

fstream file("StudentBST.txt", ios::in);

class Student
{
public:
	int id;
	char* name;
	float average;
	int sizeMarks;
	int* marks;

	Student()
	{
		id = 0;
		name = 0;
		average = 0;
		sizeMarks = 0;
		marks = 0;
	}
};

class Node
{
public:
	Node * left;
	Student s;
	Node* right;

	Node()
	{
		left = 0;
		right = 0;
	}
};

Node* createNode(Student s, Node* left, Node* right)
{
	Node* temp = new Node();
	temp->s = s;
	temp->left = left;
	temp->right = right;
	return temp;
}

Node* add(Node* root, Student s)
{
	Node* temp = root;
	if (temp == 0)
	{
		temp = createNode(s, 0, 0);
		return temp;
	}
	else
	{
		while (true)
		{
			if (s.id > temp->s.id)
			{
				if (temp->right != 0)
				{
					temp = temp->right;
				}
				else
				{
					temp->right = createNode(s, 0, 0);
					return root;
				}
			}
			else if (s.id < temp->s.id)
			{
				if (temp->left != 0)
				{
					temp = temp->left;
				}
				else
				{
					temp->left = createNode(s, 0, 0);
					return root;
				}
			}
			else return 0;
		}
	}
}

void readFromFile(Student& s)
{

	char buffer[256];
	file >> s.id;
	file >> buffer;
	s.name = new char[strlen(buffer) + 1];
	strcpy(s.name, buffer);
	file >> s.average;
	file >> s.sizeMarks;
	if (s.sizeMarks > 0)
	{
		s.marks = new int[s.sizeMarks];
		for (int i = 0; i < s.sizeMarks; i++)
		{
			file >> s.marks[i];
		}
	}
	else
	{
		// Do nothing
	}
}

// In Order display: It'll show the nodes in ascending order regarding the 
// id of the student it was inserted in bst.
void inOrder(Node* root)
{
	if (root)
	{
		inOrder(root->left);
		cout << "\nID: " << root->s.id
			<< "\nName: " << root->s.name
			<< "\nAverage: " << root->s.average
			<< "\nNumber of marks: " << root->s.sizeMarks
			<< "\nMarks: ";
		for (int i = 0; i < root->s.sizeMarks; ++i)
		{
			cout << " " << root->s.marks[i];
		}
		cout << "\n=====================";
		inOrder(root->right);
	}
}

void postOrder(Node* root)
{
	if (root)
	{
		inOrder(root->left);
		inOrder(root->right);
		cout << "\nID: " << root->s.id
			<< "\nName: " << root->s.name
			<< "\nAverage: " << root->s.average
			<< "\nNumber of marks: " << root->s.sizeMarks
			<< "\nMarks: ";
		for (int i = 0; i < root->s.sizeMarks; ++i)
		{
			cout << " " << root->s.marks[i];
		}
		cout << "\n=====================";
	}
}

void preOrder(Node* root)
{
	if (root)
	{

		cout << "\nID: " << root->s.id
			<< "\nName: " << root->s.name
			<< "\nAverage: " << root->s.average
			<< "\nNumber of marks: " << root->s.sizeMarks
			<< "\nMarks: ";
		for (int i = 0; i < root->s.sizeMarks; ++i)
		{
			cout << " " << root->s.marks[i];
		}
		cout << "\n=====================";
		inOrder(root->left);
		inOrder(root->right);
	}
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int treeLevel(Node* root)
{
	if (root)
	{
		return 1 + max(treeLevel(root->left), treeLevel(root->right));
	}
	else
	{
		return 0;
	}
}

Node* searchByID(Node* root, int id)
{
	if (root)
	{
		if (root->s.id == id)
		{
			return root;
		}
		else if (root->s.id > id)
		{
			return searchByID(root->left, id);
		}
		else
		{
			return searchByID(root->right, id);
		}
	}
	else
	{
		return 0;
	}
}

void main()
{
	Node* root = 0;
	Student s;
	while (!file.eof())
	{
		readFromFile(s);
		root = add(root, s);
	}
	/*inOrder(root);
	cout << endl << endl;
	postOrder(root);
	cout << endl << endl;
	preOrder(root);
	cout << endl << endl;*/

	Node* findMyStudent = 0;
	findMyStudent = searchByID(root, 2300);
	if (findMyStudent != 0)
	{
		cout << "\nStudent has been found with the following credentials: " << endl;
		cout << "\nID: " << findMyStudent->s.id
			<< "\nName: " << findMyStudent->s.name
			<< "\nAverage: " << findMyStudent->s.average
			<< "\nNumber of marks: " << findMyStudent->s.sizeMarks
			<< "\nMarks: ";
		for (int i = 0; i < findMyStudent->s.sizeMarks; ++i)
		{
			cout << " " << findMyStudent->s.marks[i];
		}
		cout << "\n=====================";
	}
	else
	{
		cout << "\nStudent does not exist in data structure!" << endl;
	}

	int sizeOfTree = 0;
	sizeOfTree = treeLevel(root);
	if (sizeOfTree != 0)
	{
		cout << "\n\nSize of tree: " << sizeOfTree;
	}
	else
	{
		cout << "\n\nTree doesn't exist!" << endl;
	}

	getch();
}