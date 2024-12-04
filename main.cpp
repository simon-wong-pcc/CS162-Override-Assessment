#include <iostream>
#include <fstream>

#include "main.h"
#include "task.h"
using namespace std;

int main() {
    Task taskList[MAX_LIST_SIZE];
    int size = 0;

    // Check if file was succesfully loaded
    if (loadTasksFromFile("tasks.txt", taskList, size)) {
        cout << "Error opening file" << endl;
        return -1;
    }

    // Main Loop
    bool exitSig = false;
    do {
        printMenu(); // Print Menu
        exitSig = openUserMenu(taskList, size); // Handle menu choices
    } while (!exitSig); // Continue until exitSig

    saveTasksToFile("tasks.txt", taskList, size);

    cout << "Tasks written to file! Thank you for using my program!!" << endl;

    return 0;
}

// Print the menu
void printMenu() {
    cout << "Pick an option from below:\n\n";
    cout << "(a)Add a new task\n";
    cout << "(b)List tasks by name\n";
    cout << "(c)Remove tasks by index\n";
    cout << "(d)Search tasks by type\n";
    cout << "(e)Search tasks by name\n";
    cout << "(q)Quit\n" << endl;
}

// Allow user to select option from menu. 
// Returns true if the user wants to quit, otherwise false
bool openUserMenu(Task* taskList, int& size) {

    char selection;
    bool exitSig = false;

    cin >> selection;
    cin.clear(); // Reset cin to work with getline
    cin.ignore(100, '\n');

    switch (selection) {
    case 'a': // Add
        addTask(taskList, size);
        break;
    case 'b': // List
        listTasks(taskList, size);
        break;
    case 'c': // Remove
        removeTask(taskList, size);
        break;
    case 'd': // Search by type
        listTasksByType(taskList, size);
        break;
    case 'e': // Search by name
        listTasksByName(taskList, size);
        break;
    case 'q': // Quit
        exitSig = true;
        break;
    default: // Default Case
        cout << "Invalid Option!\n";
        break;
    }
    return exitSig;
}

// Prompt user for task and add to taskList
void addTask(Task* taskList, int& size) {
    if (size + 1 > MAX_LIST_SIZE) { // Validate size
        cout << "Error: List is max size\n\n";
    }
    else {
        Task newTask = constructTaskFromUser(); // Get new task
        insertTask(newTask, taskList, size); // Insert Task
        cout << "\nTask added!\n\n";
    }
}

// Prompt user for index and remove from taskList
void removeTask(Task* taskList, int& size) {
    if (size == 0) { // Validate Size
        cout << "Error: List is empty\n\n";
    }
    else {
        printTasks(taskList, size); // Print the tasks
        cout << "\n";
        int index = getRangedIntFromUser("Enter index of task to remove: ", 1, size) - 1; // Get index
        removeTask(index, taskList, size); // Remove task
        cout << "Task removed!\n\n";
    }
}

// list tasks in taskList
void listTasks(Task* taskList, int& size) {
    if (size == 0) { // Validate size
        cout << "No Results Found\n\n";
    }
    else {
        printTasks(taskList, size); // Print tasks
        cout << endl;
    }
}

// Prompt user for type and print the filtered taskList
void listTasksByType(Task* taskList, int& size) {
    // Prompt for task type
    const char* prompt = "\nEnter the task type 0-Operations, 1-Maintenance, 2-Inventory, 3-Communications, and 4-Others): ";
    TaskType type = (TaskType)getRangedIntFromUser(prompt, 0, 4);

    cout << endl << "Showing Results for: " << taskTypeToString(type) << endl;

    printTasksByType(taskList, size, type);
    cout << endl;
}

// Prompt user for a substring and print the filtered taskList
void listTasksByName(Task* taskList, int& size) {
    char filter[51];
    getStringFromUser("Enter the search string (50 characters max): ", filter);

    cout << endl << "Showing Results for: " << filter << endl;
    printTasksByName(taskList, size, filter);
    cout << endl;
}

// Prompt the user to create a new task
Task constructTaskFromUser() {
    Task newTask;

    // Day
    newTask.day = getRangedIntFromUser("Enter the day of the task (whole numbers between 1 and 30): ", 1, 30);
    // Name
    getStringFromUser("Enter the task name (50 characters or less): ", newTask.name);
    // Person Name
    getStringFromUser("Enter the person's name (50 characters or less): ", newTask.personName);
    // Duration
    newTask.duration = getRangedIntFromUser("Enter the number of hours (whole numbers between 1 and 10): ", 1, 10);
    // Category
    const char* prompt = "Enter the task type 0-Operations, 1-Maintenance, 2-Inventory, 3-Communications, and 4-Others): ";
    newTask.category = (TaskType)getRangedIntFromUser(prompt, 0, 4);

    return newTask;
}

// Get a int in a specified range from user
int getRangedIntFromUser(const char* prompt, int lower, int upper) {
    int out;
    do {
        // Prompt
        cout << prompt;
        cin >> out;
        if (cin.fail() || out < lower || out > upper) { // Validate input
            cout << "Invalid Entry! Must be between " << lower << " and " << upper << " inclusive!" << endl;
            out = lower - 1; // Set to below lower to continue loop
        }
        cin.clear(); // Reset cin
        cin.ignore(100, '\n');
    } while (out < lower || out > upper);

    return out;
}

// Get a string from the user
void getStringFromUser(const char* prompt, char* outStr) {
    do {
        if (cin.fail()) { // Check if string is less than 50 characters
            cout << "Invalid Entry! Must be less than 50 characters!" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        cout << prompt;
        cin.getline(outStr, MAX_CHAR);
    } while (cin.fail());
}
