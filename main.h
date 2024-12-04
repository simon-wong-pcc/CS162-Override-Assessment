#ifndef main_h_
#define main_h_

#include "task.h"

const int MAX_LIST_SIZE = 30;

void printMenu();
bool openUserMenu(Task* taskList, int& size);

void addTask(Task* taskList, int& size);
void removeTask(Task* taskList, int& size);
void listTasks(Task* taskList, int& size);
void listTasksByType(Task* taskList, int& size);
void listTasksByName(Task* taskList, int& size);

Task constructTaskFromUser();
int getRangedIntFromUser(const char* prompt, int lower, int upper);
void getStringFromUser(const char* prompt, char* outStr);

#endif
