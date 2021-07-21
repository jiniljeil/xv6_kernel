#include "types.h"
#include "stat.h" 
#include "user.h" 
#define MAX 2

void
loop(int num)
{
        sleep(100);
        while(1){
                printf(1," %d ",num);
        }

        exit(0);
}

int main(void) { 

     int i ;
     int pid[MAX]; 

     for(i = 0 ; i < MAX; i++) { 
	  pid[i] = fork(); 
	  
          if(pid[i] < 0) printf(2, "fork failed\n"); 
	  if(pid[i] == 0) loop(i); 
     } 
     
     sleep(1000); 
}
