#include "types.h"
#include "stat.h" 
#include "user.h"


int main(void) { 
    int pid = fork() ; 
    int p = 0; 
    if(pid == 0) { 
         p = setpriority(pid, 5); 
    }else{
         p = setpriority(pid, 10); 
    } 
    while(1){ 
        sleep(10); 
        if ( p == 5 ) { 
            printf(1, "CHLID\n"); 
        }else if( p == 10 ) { 
            printf(2, "PARENT\n");
        }
    }
    return 0;
}
