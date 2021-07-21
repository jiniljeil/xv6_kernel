#include "types.h"
#include "stat.h" 
#include "user.h"

int main(void) {
    int pid = fork() ;
    if(pid == 0) {
         setpriority(pid, 5);
         while(1) {sleep(10); printf(1, "CHLID\n"); }
    }else{
         setpriority(pid, 10);
         while(1) {sleep(10); printf(1, "PARENT\n"); }  
    }
    /*while(1){
        sleep(10);
        if ( p == 5 ) {
            printf(1, "CHLID\n");
        }else if( p == 10 ) {
            printf(1, "PARENT\n");
        }
    }*/
    return 0;
}
/*
int main(void) {
   int pid1, pid2, child_pid, status;

   // First child process
   if((pid1 = fork()) == -1) { 
        printf(1, "fork failed\n");  
        exit(-1); 
   // Parent process 
   }else if(pid1 != 0) { 
       child_pid = waitpid(pid1, &status, 0);
       printf(1, "child1[pid: %d] terminated with code %x\n", pid1, status);
       // Second child process 
       if ((pid2 = fork()) == -1) {
             printf(1, "fork failed\n");
             exit(-1); 
       }
       // Parent process 
       else if( pid2 != 0 ) { 
	     child_pid = waitpid(pid2, &status, 0); 
	     printf(1, "child2[pid: %d] terminated with code %x\n", child_pid, status);
       // Second child process  
       }else {
	     printf(1, "run child2(pid: %d)\n", pid2); 
	     exit(0); 
       } 
   }else { 
       printf(1, "run child1(pid: %d)\n", pid1); 
       exit(0);
   }
   exit(0);
}
*/
/*
int main(void) { 
    int process[10];

    for(int i = 0 ; i < 10; i++) { 
        process[i] = fork(); 
        if( process[i] < 0 ) { 
	    printf(1, "fork failed!\n"); 
	    exit(1); 
	}else if( process[i] == 0) { 
    	    sleep(10 * i + i); 
	    exit(i); 
	}else { 
	    continue; 
	}
    }

    for(int i = 0 ; i < 10; i++) { 
         int status; 
         int pid = waitpid(process[i], &status, 0); 
	 printf(1, "PID: %d exited with status %d! \n", pid, status); 
    }
	    
}
*/ 

/*
int main(void) { 
	int pid = fork(); 
	if( pid == 0) { 
		printf(1, "CHILD!\n"); 
		exit(0);  
	}
	int status; 
	wait(&status); 
	
	printf(1, "wait!: %d\n", status); 
	exit(1); 
}
*/
