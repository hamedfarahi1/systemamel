/*
 * C++ Program to Implement Queue using Linked List
 */
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>

using namespace std;
struct node
{
	int data;
	node *next;
} *front = NULL, *rear = NULL, *p = NULL, *np = NULL;
void push(int x)
{
	np = new node;
	np->data = x;
	np->next = NULL;
	if (front == NULL)
	{
		front = rear = np;
		rear->next = NULL;
	}
	else
	{
		rear->next = np;
		rear = np;
		rear->next = NULL;
	}
}
int remove()
{
	int x;
	if (front == NULL)
	{
		cout << "empty queue\n";
		return 0;
	}
	else
	{
		p = front;
		x = p->data;
		front = front->next;
		delete (p);
		return (x);
	}
}
void sharedMem()
{

	key_t readKey = ftok("shmfile", 65);
	int readShmId  = shmget(readKey, 15 * sizeof(int), IPC_CREAT | 0666);
	if (readShmId < 0)
	{
		printf("shmget error\n");
		return;
	}
	int *arr = (int*) shmat(readShmId,(void*)0,0);
	

	int i = 0;
	while (true)
	{
		if (front != NULL)
			arr[i] = remove();
		else
			break;
		i++;
	}
	cout << endl << "array is saved to memory" << endl;
}
void readFile()
{
	int sum = 0;
	int x;
	ifstream inFile;

	inFile.open("test.txt");
	if (!inFile)
	{
		cout << "Unable to open file";
	}

	while (inFile >> x)
	{
		push(x);
		cout << "read " << x << " and push it to queue" << endl;
	}

	inFile.close();
}

int main()
{
	readFile();
	sharedMem();
}