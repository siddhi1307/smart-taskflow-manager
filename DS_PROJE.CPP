#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
// TASK NODE - LINKED LIST
struct Task
{
    int id;
    char title[50];
    char priority[20];
    char status[20];
    Task *next;
};
// QUEUE NODE
struct QueueNode
{
    int taskId;
    char title[50];
    QueueNode *next;
};
// STACK NODE
struct StackNode
{
    int taskId;
    char title[50];
    StackNode *next;
};
// GLOBAL POINTERS
Task *head = NULL;

QueueNode *front = NULL;
QueueNode *rear = NULL;

StackNode *top = NULL;

int taskCounter = 1;
// 1. ADD TASK
// LINKED LIST
void addTask()
{
    Task *newTask;

    newTask = new Task;

    newTask->id = taskCounter++;

    cout << "\nEnter Task Title: ";
    cin.ignore();
    cin.getline(newTask->title, 50);

    cout << "Enter Priority (High/Medium/Low): ";
    cin >> newTask->priority;

    strcpy(newTask->status, "Pending");

    newTask->next = NULL;

    // If linked list is empty
    if (head == NULL)
    {
	head = newTask;
    }
    else
    {
	Task *temp;
	temp = head;

	// Go to last node
	while (temp->next != NULL)
	{
	    temp = temp->next;
	}

	temp->next = newTask;
    }

    cout << "\nTask added successfully!";
    cout << "\nTask ID: " << newTask->id;
}
// 2. DISPLAY ALL TASKS
void displayTasks()
{
    Task *temp;

    if (head == NULL)
    {
	cout << "\nNo tasks available.";
	return;
    }

    temp = head;

    cout << "\n\n====================================";
    cout << "\n          ALL TASKS";
    cout << "\n====================================";

    while (temp != NULL)
    {
	cout << "\n\nTask ID  : " << temp->id;
	cout << "\nTitle    : " << temp->title;
	cout << "\nPriority : " << temp->priority;
	cout << "\nStatus   : " << temp->status;

	cout << "\n------------------------------------";

	temp = temp->next;
    }
}

// 3. SEARCH TASK
// LINEAR SEARCH
void searchTask()
{
    int id;
    Task *temp;

    if (head == NULL)
    {
	cout << "\nNo tasks available.";
	return;
    }

    cout << "\nEnter Task ID to search: ";
    cin >> id;

    temp = head;

    while (temp != NULL)
    {
	if (temp->id == id)
	{
	    cout << "\n\nTask Found!";
	    cout << "\nTask ID  : " << temp->id;
	    cout << "\nTitle    : " << temp->title;
	    cout << "\nPriority : " << temp->priority;
	    cout << "\nStatus   : " << temp->status;

	    return;
	}

	temp = temp->next;
    }

    cout << "\nTask not found.";
}
// 4. DELETE TASK
// LINKED LIST
void deleteTask()
{
    int id;

    Task *temp;
    Task *previous;

    if (head == NULL)
    {
	cout << "\nNo tasks available.";
	return;
    }

    cout << "\nEnter Task ID to delete: ";
    cin >> id;

    temp = head;
    previous = NULL;

    while (temp != NULL)
    {
	if (temp->id == id)
	{
	    // Delete first node
	    if (previous == NULL)
	    {
		head = temp->next;
	    }
	    else
	    {
		previous->next = temp->next;
	    }

	    delete temp;

	    cout << "\nTask deleted successfully!";
	    return;
	}

	previous = temp;
	temp = temp->next;
    }

    cout << "\nTask not found.";
}
// 5. ADD TASK TO QUEUE
void addToQueue()
{
    int id;

    Task *temp;

    QueueNode *newNode;

    if (head == NULL)
    {
	cout << "\nNo tasks available.";
	return;
    }

    cout << "\nEnter Task ID to add to queue: ";
    cin >> id;

    temp = head;

    while (temp != NULL)
    {
	if (temp->id == id)
	{
	    newNode = new QueueNode;

	    newNode->taskId = temp->id;

	    strcpy(newNode->title, temp->title);

	    newNode->next = NULL;

	    // Queue is empty
	    if (rear == NULL)
	    {
		front = newNode;
		rear = newNode;
	    }
	    else
	    {
		rear->next = newNode;
		rear = newNode;
	    }

	    cout << "\nTask added to processing queue!";

	    return;
	}

	temp = temp->next;
    }

    cout << "\nTask not found.";
}
// 6. DISPLAY QUEUE
void displayQueue()
{
    QueueNode *temp;

    if (front == NULL)
    {
	cout << "\nProcessing queue is empty.";
	return;
    }

    temp = front;

    cout << "\n\n====================================";
    cout << "\n       PROCESSING QUEUE";
    cout << "\n====================================";

    while (temp != NULL)
    {
	cout << "\n\nTask ID : " << temp->taskId;
	cout << "\nTitle   : " << temp->title;

	cout << "\n------------------------------------";

	temp = temp->next;
    }
}
// 7. PROCESS NEXT TASK
// QUEUE - FIFO
void processNextTask()
{
    QueueNode *temp;

    if (front == NULL)
    {
	cout << "\nProcessing queue is empty.";
	return;
    }

    temp = front;

    cout << "\n\nProcessing Task...";
    cout << "\nTask ID : " << temp->taskId;
    cout << "\nTitle   : " << temp->title;

    front = front->next;

    // If queue becomes empty
    if (front == NULL)
    {
	rear = NULL;
    }

    delete temp;

    cout << "\n\nTask processed successfully!";
}
// 8. PUSH COMPLETED TASK
// STACK
void pushCompletedTask(int id, char title[])
{
    StackNode *newNode;

    newNode = new StackNode;

    newNode->taskId = id;

    strcpy(newNode->title, title);

    // New node becomes TOP
    newNode->next = top;

    top = newNode;
}
// 9. MARK TASK AS COMPLETED

void completeTask()
{
    int id;

    Task *temp;

    if (head == NULL)
    {
	cout << "\nNo tasks available.";
	return;
    }

    cout << "\nEnter Task ID to mark as completed: ";
    cin >> id;

    temp = head;

    while (temp != NULL)
    {
	if (temp->id == id)
	{
	    strcpy(temp->status, "Completed");

	    // Push task into stack
	    pushCompletedTask(temp->id, temp->title);

	    cout << "\nTask marked as completed!";

	    return;
	}

	temp = temp->next;
    }

    cout << "\nTask not found.";
}
// 10. DISPLAY COMPLETED TASKS
// STACK - LIFO
void displayCompletedTasks()
{
    StackNode *temp;

    if (top == NULL)
    {
	cout << "\nNo completed tasks.";
	return;
    }

    temp = top;

    cout << "\n\n====================================";
    cout << "\n    RECENTLY COMPLETED TASKS";
    cout << "\n====================================";

    while (temp != NULL)
    {
	cout << "\n\nTask ID : " << temp->taskId;
	cout << "\nTitle   : " << temp->title;

	cout << "\n------------------------------------";

	temp = temp->next;
    }
}
void main()
{
    int choice;

    clrscr();

    do
    {
	cout << "\n\n";
	cout << "============================================";
	cout << "\n       SMART TASKFLOW MANAGER";
	cout << "\n============================================";

	cout << "\n\n1. Add Task";
	cout << "\n2. Display All Tasks";
	cout << "\n3. Search Task";
	cout << "\n4. Delete Task";
	cout << "\n5. Add Task to Processing Queue";
	cout << "\n6. Display Processing Queue";
	cout << "\n7. Process Next Task";
	cout << "\n8. Mark Task as Completed";
	cout << "\n9. Display Completed Tasks";
	cout << "\n10. Exit";

	cout << "\n\nEnter your choice: ";
	cin >> choice;

	switch(choice)
	{
	    case 1:
		addTask();
		break;

	    case 2:
		displayTasks();
		break;

	    case 3:
		searchTask();
		break;

	    case 4:
		deleteTask();
		break;

	    case 5:
		addToQueue();
		break;

	    case 6:
		displayQueue();
		break;

	    case 7:
		processNextTask();
		break;

	    case 8:
		completeTask();
		break;

	    case 9:
		displayCompletedTasks();
		break;

	    case 10:
		cout << "\n\nThank you for using";
		cout << "\nSmart TaskFlow Manager!";
		break;

	    default:
		cout << "\nInvalid choice!";
	}

	if(choice != 10)
	{
	    cout << "\n\nPress any key to continue...";
	    getch();
	    clrscr();
	}

    } while(choice != 10);
}