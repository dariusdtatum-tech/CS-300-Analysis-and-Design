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


---

## CS 300 Data Structures and Algorithms Reflection

1. What was the problem you were solving in the projects for this course?
The problem was designing an academic course advisor program that could read a file containing a list of computer science courses, store that data along with any prerequisites, and let a user interact with it. The program needed to be fast and efficient, allowing an advisor to search for a specific course instantly or print a complete list of all courses in alphanumeric order.

2. How did you approach the problem? Consider why data structures are important to understand.
I approached the problem by looking at how different data structures handle search times and memory usage. Understanding data structures is incredibly important because choosing the wrong one can slow a program down as more data is added. For example, using a Vector is easy to set up, but searching it requires looking through every single item one by one, which is an O(N) linear time complexity. To make the program faster, I focused on implementing a Binary Search Tree (BST). Because a BST organizes data hierarchically, it cuts down the average search and insertion time to O(log N), and it allows for an easy in-order traversal to print the courses alphabetically.

3. How did you overcome any roadblocks you encountered while going through the activities or project?
My biggest roadblocks were managing pointers correctly and dealing with complex conditional logic, especially when handling node deletions in the Binary Search Tree or parsing file data that had varying numbers of prerequisites. When working with recursion, it was easy to lose track of where pointers were pointing, which could cause memory leaks or segementation faults. I overcame these challenges by breaking down the logic, using manual print statements to trace the flow of data through the loops, and carefully checking that my pointers were properly updated when deleting or moving nodes.

4. How was your work on this project expanded your approach to designing software and developing programs?
This project taught me not to just jump straight into writing code the moment I get an assignment. Instead, it has shown me the value of planning the software design first. I now spend time analyzing data requirements and thinking about scalability from the start. Using Big-O notation to evaluate my code has changed how I think, and I now always look for ways to optimize my algorithms so they can handle large datasets without lagging.

5. How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
It has made me focus a lot more on writing clean, modular code. Instead of grouping all my logic into one massive function, I separate things--like putting the file-parsing logic, the core data structure algorithms, and the user interface menus into distinct functions. I also focus on using descriptive variable names and adding meaningful comments. This makes the program much easier to maintain, meaning if I ever need to swap out the Binary Search Tree for a Hash Table in the future, I can do it without having to rewrite the entire user interface.

