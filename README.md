# CS 300: Data Structures and Analysis - ABCU Advising Program

## Project Overview

This repository contains a command-line course planning application that I built for academic advisors at ABCU. The program reads a list of courses from a CSV file, parses the data, and stores it inside a custom **Binary Search Tree (BST)**. This structure allows advisors to look up course titles and verify prerequisites efficiently.


Per my professor's instructions, the entire application is written within a single source file('ProjectTwo.cpp') without using external code parsers or split headers.


---


## Technical Design & Reflections

### 1. Choosing the Data Structure

During the design phase of this project, I looked at using Vectors, Hash Tables, and Binary Search Trees to see which fits the advisors' requirements best. While a Vector loads quickly and a Hash Table offers fast individual searches, I chose a **Binary Search Tree**.


The BST naturally keeps all the course numbers sorted in alphanumeric order based on how they are inserted. This allows my program to print a perfectly sorted curriculum list (Option 2) using an **In-Order Traversal** without needing to run any extra sorting functions at runtime.


### 2. Time and Space Efficiency

* **Search Runtime:** The average search time scales at **O(log n)**. By comparing the course ID at each node, the program cuts the remaining search space in half with every step, making lookups quick even if the data file grows.

* **Memory Management:** To make sure there are no heap memory leaks when the program exits, I built a destructor using a **Post-Order Traversal** algorithm. This makes sure that child nodes are safely deleted from memory before the parent node itself is deleted.


---


## Program Features & Menu Options

I built a terminal-based menu system with built-in input validation so that the loop doesn't crash or get stuck if a user types a letter by mistake into the number prompt.


1. **Load Data Structure:** Opens 'CS 300 ABCU_Advising_Program_Input.csv', cleans up hidden characters, and populates the tree. It blocks data duplication if run multiple times.

2. **Print Course List:** Uses a recursive left-root-right tree traversal to output the full course catalog sorted alphanumerically.

3. **Print Course:** Prompts for a specific course ID (case-insensitive), runs a BST search, and prints the title and prerequisites. If no prerequisites exist, it prints "None".

9. **Exit:** Cleans up the tree from heap memory and terminates the program safely.
