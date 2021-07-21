## xv6_kernel_study Day6
  
Date: 2021-07-19

## System call flow 
   
[과정]
1. call wait() in the user program (%eax register stores the syscall number, invoke system call by int %eax instruction)    
       
2. Trap is taken place. After that, build the trapframe, invoke the stack switch, and call trap() in the trapasm.S  
       
3. If trap is same with T_SYSCALL(=64), call syscall() in trap.c  
        
4. After that, find the sys_wait() in the system call table as index and call sys_wait(). 
       
5. bring the argument by using argptr() and inserting the arguments in the wait function, call wait(); 

## Context Switching 

   과정
1. call main() in kernel -> mpmain() -> scheduler()  
   
2. If time interrupt is invoked, call yield() 
      
3. After the ptable is locked and the process changes the state of process to RUNNABLE, call sched(). 
      (Then, the reason of the ptable is locked is that <strong>the process running the scheduler()</strong>
       and <strong>the process conducting the work in the kernel</strong> are existed.)   
       
4. After that, the process put into disable interrupt state and call the swtch().  
       
5. the registers of the current process push on the kernel stack, change the %esp register, and load the registers of the scheduler.  
       
6. Switch to the kernel page table, choose the process to switch in the process table, and switch to process's address space (page table of the process)   
       
7. the process is changed to the state is RUNNING. 
        
8. After that, the registers of the scheduler push on the kernel stack, change the %esp register and load the registers of the new process by calling swtch().    
       
   In the xv6 kernel, the policy of context switching is used on the method named Round Robin. 
   Per process has the own page table
   ```
   struct context{  
       ebp, 
       ebx, 
       esi, 
       ebi, 
       eip   
   }
   ``` 

## 느낀점   
   
   정말 하루 하루 공부할 때마다 부족했던 부분을 채울 수 있게되고, 시스템 내부의 동작 원리나 구조 등을 코드를 통해 직접 흐름을 읽음으로써 더욱 더 공부가 되는 것 같다. 궁금했던 부분들이 있을 때마다 서로 질문하고 코드를 보며 이해하는 그런 시간들이 정말 의미 깊었던 것 같다. 또한 우리가 바라보지 못했던 부분들을 교수님께서 집어주셔서 그러한 부분들까지도 생각해보고 이해하고 넘어갈 수 있는 시간들이 정말 감사하다.   



