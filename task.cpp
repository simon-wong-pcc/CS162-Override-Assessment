#include <fstream>
#include <iostream>
#include <cstring>

#include "main.h"
#include "task.h"
using namespace std;

// Insert a task into taskList, sorted by personName and update size
// Source(s): Zybooks
void insertTask(Task task, Task* taskList, int& size) {

    // Calculate index by comparing each personName to the personName in the new task
    int index = 0;
    while (index < MAX_LIST_SIZE && strcmp(taskList[index].personName, task.personName) < 0) {
        index++;
    }

    // Shift Elements
    for (int i = MAX_LIST_SIZE - 1; i > index; i--) {
        taskList[i] = taskList[i - 1];
    }

    // Insert Element
    taskList[index] = task;
    size++; // Increase size
}

// Remove a task from taskList by Index and update size
// Source(s): Zybooks
void removeTask(int index, Task* taskList, int& size) {
    // Shift elements left
    for (int i = index; i < MAX_LIST_SIZE - 1; i++) {
        taskList[i] = taskList[i + 1];
    }

    // Set last element to empty struct
    taskList[MAX_LIST_SIZE - 1] = {};
    size--; // Decrement size
}

// Print a task
void printTask(Task task) {
    cout << task.day << ";";
    cout << task.name << ";";
    cout << task.duration << ";";
    cout << task.personName << ";";
    cout << taskTypeToString(task.category) << endl;
}

// Print all tasks
void printTasks(Task* taskList, int& size) {
    for (int i = 1; i <= size; i++) {
        cout << i << ". ";
        printTask(taskList[i - 1]);
    }
}

// Print all tasks of certain type
void printTasksByType(Task* taskList, int& size, TaskType filter) {
    bool exists = false;
    for (int i = 0; i < size; i++) {
        if (taskList[i].category == filter) {
            printTask(taskList[i]);
            exists = true;
        }
    }

    if (!exists) {
        cout << "No Results Found" << endl;
    }
}

// Print all tasks that contain substring
// Source(s): Zybooks
void printTasksByName(Task* taskList, int& size, char* filter) {
    bool exists = false;
    for (int i = 0; i < size; i++) {
        // Strstr will return a ptr to the first instance of substr
        // or nullptr if it doesn't exist
        if (strstr(taskList[i].name, filter) != nullptr) {
            printTask(taskList[i]);
            exists = true;
        }
    }

    if (!exists) {
        cout << "No Results Found" << endl;
    }
}

// Print a string corresponding to a taskType 
void printTaskType(TaskType type) { // Alternete version with single return path
    switch (type) {
    case Operations:
        cout << "Operations" << endl;
        break;
    case Maintenance:
        cout << "Maintenance" << endl;
        break;
    case Inventory:
        cout << "Inventory" << endl;
        break;
    case Communications:
        cout << "Communications" << endl;
        break;
    case Other:
        cout << "Other" << endl;
        break;
    }
}

// Convert TaskType enum to string
const char* taskTypeToString(TaskType type) {
    // Version with multiple control path
    // Acceptable use IMO, but technically against style guidelines :(
    switch (type) {
    case Operations:        return "Operations"; // Lifetime of string literal is 
    case Maintenance:       return "Maintenance";// the same as program lifetime
    case Inventory:         return "Inventory";  // making this ok
    case Communications:    return "Communications";
    case Other:             return "Other";
    }
}

// Load a task from a file
// Returns -1 if error, otherwise 0
// Source(s): Zybooks
int loadTasksFromFile(const char* filename, Task* taskList, int& size) {
    // Format: Day; Task Name; Duration; Person Name; Category //

    // Open and check file
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Error: File could not open";
        return -1;
    }

    Task newTask;

    // Input outside loop to check for EOF
    file >> newTask.day;
    file.ignore(5, ';');

    while (!file.eof() && size < MAX_LIST_SIZE) {

        file.getline(newTask.name, MAX_CHAR, ';');

        file >> newTask.duration;
        file.ignore(5, ';');

        file.getline(newTask.personName, MAX_CHAR, ';');

        // To input directly into category without the use of
        // a temperary variable, cast category to an int reference
        file >> (int&)(newTask.category);
        file.ignore(5, '\n');

        insertTask(newTask, taskList, size); // insertTask will increment count for us

        // Prepare for next item
        file >> newTask.day;
        file.ignore(5, ';');

    }

    file.close();

    return 0;
}

// Save taskList to a file
void saveTasksToFile(const char* filename, Task* taskList, int& size) {
    // Format: Day; Task Name; Duration; Person Name; Category //

    // Open and check file
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Error: File could not open";
        return;
    }

    for (int i = 0; i < size; i++) {
        file << taskList[i].day << ';';
        file << taskList[i].name << ';';
        file << taskList[i].duration << ';';
        file << taskList[i].personName << ';';
        file << taskList[i].category << '\n';
    }

    file.close();
}
