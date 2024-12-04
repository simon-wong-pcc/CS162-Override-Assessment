#ifndef task_h_
#define task_h_

const int MAX_CHAR = 51;

enum TaskType {
    Operations, Maintenance, Inventory, Communications, Other
};

struct Task {
    char name[MAX_CHAR];       // The name of the task
    int day;                   // What day of the month, 1 - 30
    char personName[MAX_CHAR]; // The person assigned to the task
    int duration;              // The duration of the task, 1 - 10
    TaskType category;         // The type of task
};

void insertTask(Task task, Task* taskList, int& size);
void removeTask(int index, Task* taskList, int& size);

const char* taskTypeToString(TaskType type);

void printTasks(Task* taskList, int& size);
void printTasksByType(Task* taskList, int& size, TaskType filter);
void printTasksByName(Task* taskList, int& size, char* filter);
void printTaskType(TaskType type);

int loadTasksFromFile(const char* filename, Task* taskList, int& size);
void saveTasksToFile(const char* filename, Task* taskList, int& size);

#endif
