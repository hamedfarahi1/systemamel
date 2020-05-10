#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
using namespace std; 

float avarege(int *arr, int n) {
    float sum = 0.0, avg;
    int i = 0;
    cout << "avarege of:  ";
    while(i < n) {
        if ( i == n - 1)
            cout << arr[i];
        else
            cout << arr[i] << ", ";
        sum += arr[i];
        i++;
    }
    cout << " is: " << sum / n << endl;
    return sum / n;
}
int main() 
{ 
	key_t readKey = ftok("shmfile", 65);
  
	int readShmId  = shmget(readKey, 15 * sizeof(int), IPC_CREAT | 0666);
  
	int *arr = (int*) shmat(readShmId,(void*)0,0);
  
    for (int i = 0; i < sizeof(arr); i++)
        cout << avarege(arr, i+1) << endl;
    cout << endl << "complate";
    shmdt(arr); 
    
    shmctl(readShmId,IPC_RMID,NULL); 
     
    return 0; 
} 
