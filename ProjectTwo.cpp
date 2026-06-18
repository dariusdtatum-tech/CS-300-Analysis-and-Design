#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// --- STRUCTURES ---

// Store basic course information together
struct Course {
		string courseNumber;	// e.g., CSCI300
		string courseTitle;		// e.g., Introduction to Algorithms
		vector<string> prerequisites; // Holds list of required course numbers
};

// Represents a single node inside our Binary Search Tree
struct Node {
	Course course;
	Node* left;
	Node* right;

	// Initialize pointers to null when a blank node is made
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// Overloaded constructor to set up a node directly with data
	Node(Course aCourse) : Node() {
		course = aCourse;
	}
};

// --- BST CLASS DEFINITION ---

class BinarySearchTree {
private:
	Node* root;

	// Helper functions for recursive operations
	void addNode(Node* node, Course course);
	void inOrder(Node* node);
	void destroyTree(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void Insert(Course course);
	void PrintInOrder();
	Course Search(string courseNumber);
};

// Constructor sets root pointer to null
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

// Destructor calls helper function to clear heap memory
BinarySearchTree::~BinarySearchTree() {
	destroyTree(root);
}

// --- BST METHOD IMPLEMENTATIONS ---

// Traverses the tree bottom-up to delete children before parents
void BinarySearchTree::destroyTree(Node* node) {
	if (node !=nullptr) {
		destroyTree(node->left);	// Clear left branch
		destroyTree(node->right);	// Clear right branch
		delete node;				// Delete current node
	}
}

// Public insert function handles adding first node or routing to helper
void BinarySearchTree::Insert(Course course) {
	if (root == nullptr) {
		root = new Node(course);
	} else {
		addNode(root, course);
	}
}

// Recursive helper to look left or right for insertion spot based on alphabet order
void BinarySearchTree::addNode(Node* node, Course course) {
	if (course.courseNumber < node->course.courseNumber) {
		// Look at the left child branch
		if (node->left == nullptr) {
			node->left = new Node(course);
		} else {
			addNode(node->left, course);
		}
	} else {
		// Look at the right child branch
		if (node->right == nullptr) {
			node->right = new Node(course);
		} else {
			addNode(node->right, course);
		}
	}
}

// Triggers recursive in-order printing starting from root
void BinarySearchTree::PrintInOrder() {
	inOrder(root);
}

// Left-Root-Right traversal prints everything in alphanumeric order automatically
void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr) {
		inOrder(node->left);
		cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
		inOrder(node->right);
	}
}

// Search function goes down branches by comparing string values
Course BinarySearchTree::Search(string courseNumber) {
	Node* current = root;

	while (current != nullptr) {
		// Found a perfect match
		if (current->course.courseNumber == courseNumber) {
			return current->course;
		}
		// Go left if target string is smaller, otherwise go right
		if (courseNumber < current->course.courseNumber) {
			current = current->left;
		} else {
			current = current->right;
		}
	}

	// If we exit loop without finding it, send back a blank course
	Course emptyCourse;
	return emptyCourse;
}

// --- FILE PARSING LOGIC ---

// Reads rows from the text file and pushes data into our BST object
void loadCourses(string csvPath, BinarySearchTree* bst) {
	cout << "Loading CSV file " << csvPath << endl;
	ifstream file(csvPath);

	// Make sure file actually exists and can open
	if (!file.is_open()) {
		cout << "Error: Could not open file. Check the file name and path in Eclipse." << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		// Drop hidden Windows carriage returns to avoid string comparison bugs
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}

		stringstream ss(line);
		string token;
		vector<string> tokens;

		// Separate line data out using commas
		while (getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		// Row verification: Needs at least a course ID and a course title
		if (tokens.size() < 2) {
			continue;
		}

		Course course;
		course.courseNumber = tokens[0];
		course.courseTitle = tokens[1];

		// Capture remaining strings as prerequisites
		for (size_t i = 2; i < tokens.size(); ++i) {
			string prereq = tokens[i];

			if (!prereq.empty() && prereq.back() == '\r') {
				prereq.pop_back();
			}

			// Ignore blank tokens caused by trailing commas
			if (!prereq.empty()) {
				course.prerequisites.push_back(prereq);
			}
		}

		// Add the finished course struct to our tree structure
		bst->Insert(course);
	}
	file.close();
	cout << "Data loaded successfully." << endl;
}

// --- MAIN CLI FUNCTION ---

int main() {
	BinarySearchTree* bst = new BinarySearchTree();
	string csvPath = "CS 300 ABCU_Advising_Program_Input.csv";
	int choice = 0;
	string badInput;
	bool dataLoaded = false; // Flags if data structure is already filled

	cout << "Welcome to the course planner." << endl;

	while (choice != 9) {
		cout << "\n 1. Load Data Structure." << endl;
		cout << " 2. Print Course List." << endl;
		cout << " 3. Print Course." << endl;
		cout << " 9. Exit" << endl;
		cout << "\nWhat would you like to do? ";

		cin >> choice;

		// Catch letter inputs or typos so the loop doesn't crash infinitely
		if (cin.fail()) {
			cin.clear();	 // Clear error state flag
			cin >> badInput; // Pull bad input out of stream
			cout << "Invalid input. Please enter a valid number." << endl;
			choice = 0;
			continue;
		}

		switch (choice) {
			case 1:
				// Stop system from multiplying data rows if run multiple times
				if(!dataLoaded) {
					loadCourses(csvPath, bst);
					dataLoaded = true;
				} else {
					cout << "Error: Data has already been loaded into the system." << endl;
				}
				break;

			case 2:
				cout << "Here is a sample schedule:" << endl;
				cout << endl;
				bst->PrintInOrder();
				break;

			case 3: {
				string courseKey;
				cout << "What course do you want to know about? ";
				cin >> courseKey;

				// Force user input to uppercase so it lines up with CSV IDs
				transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);

				Course course = bst->Search(courseKey);

				if (!course.courseNumber.empty()) {
					cout << course.courseNumber << ", " << course.courseTitle << endl;
					cout << "Prerequisites: ";
					if (course.prerequisites.empty()) {
						cout << "None" << endl;
					} else {
						// Print list out neatly with commas splitting items
						for (size_t i = 0; i < course.prerequisites.size(); ++i) {
							cout << course.prerequisites[i];
							if (i != course.prerequisites.size() - 1) {
								cout << ", ";
							}
						}
						cout << endl;
					}
				} else {
					cout << "Course not found." << endl;
				}
				break;
			}
			case 9:
				cout << "Thank you for using the course planner!" << endl;
				break;

			default:
				cout << choice << " is not a valid option." << endl;
				break;
		}
	}

	// Clean up our dynamically allocated tree memory right before program terminates
	delete bst;
	return 0;
}
