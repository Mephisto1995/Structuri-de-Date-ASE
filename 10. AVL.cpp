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
	int bf;

	Node()
	{
		left = 0;
		right = 0;
		bf = 0;
	}
};

int treeLevels(Node* root)
{
	if (root)
	{
		int i = 1 + treeLevels(root->left);
		int j = 1 + treeLevels(root->right);
		if (i > j)return i;
		else return j;
	}
	else return 0;
}

Node* createNode(Student s, Node* left, Node* right)
{
	Node* temp = new Node();
	temp->s = s;
	temp->left = left;
	temp->right = right;
	return temp;
}

Node* insert(Node* root, Student s)
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

void calculBF(Node* root)
{
	if (root)
	{
		root->bf = treeLevels(root->right) - treeLevels(root->left);
		calculBF(root->left);
		calculBF(root->right);
	}
}

void displayInOrder(Node* root)
{
	if (root)
	{
		displayInOrder(root->left);
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
		displayInOrder(root->right);
	}
}

void leftRotation(Node* &root)
{
	if (root)
	{
		cout << "\nLeft rotation" << endl;
		Node* temp = root->right;
		root->right = temp->left; // saving temp->left data in root->right for later usage
		temp->left = root;
		root = temp;
	}
}

void rightRotation(Node* &root)
{
	if (root)
	{
		cout << "\nRight rotation!" << endl;
		Node* temp = root->left;
		root->left = temp->right; // saving temp->right data in root->left for later usage
		temp->right = root;
		root = temp;
	}
}

void leftRightRotation(Node* &root)
{
	if (root)
	{
		cout << "\nLeft right rotation!" << endl;
		Node* temp1 = root->left;
		Node* temp2 = temp1->right;
		temp1->right = temp2->left;
		temp2->left = temp1;
		root->left = temp2->right;
		temp2->right = root;
		root = temp2;
	}
}

void rightLeftRotation(Node* &root)
{
	if (root)
	{
		cout << "\nRight left rotation!" << endl;
		Node* temp1 = root->right;
		Node* temp2 = temp1->left;
		temp1->left = temp2->right;
		temp2->right = temp1; // At this time, we have node temp2 in place of temp1. 
							  // Visually it's wrong as fuck, but if you redraw, it's like I say.
		root->right = temp2->left;
		temp2->left = root;
		root = temp2;
	}
}

void addToAVL(Node* &root, Student s)
{
	root = insert(root, s);
	calculBF(root);

	if (root->bf >= 2 && root->right->bf >= 1)
	{
		leftRotation(root);
		calculBF(root);
	}
	else if (root->bf >= 2 && root->right->bf <= -1)
	{
		rightLeftRotation(root);
		calculBF(root);
	}
	else if (root->bf <= -2 && root->left->bf <= -1)
	{
		rightRotation(root);
		calculBF(root);
	}
	else if (root->bf <= -2 && root->left->bf >= 1)
	{
		leftRightRotation(root);
		calculBF(root);
	}
}

void displayPreOrder(Node* root)
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
		displayInOrder(root->left);
		displayInOrder(root->right);
	}
}

void readFromFile(Student& s, Node* &root)
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

	// Modification from this part occur after the rotation code has been written
	addToAVL(root, s);
}

void main()
{
	Node* root = 0;
	Student s;
	while (!file.eof())
	{
		readFromFile(s, root);
	}

	displayPreOrder(root);
	system("Pause");
}
