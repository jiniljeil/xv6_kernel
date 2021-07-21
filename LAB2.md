## xv6_kernel_study Lab2
  
Date: 2021-07-21

## Scheduler  
  
[Round Robin Scheduler] 
```c
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
  
  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;

      swtch(&(c->scheduler), p->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
    }
    release(&ptable.lock);
  }
}
```   

위 코드는 xv6 kernel에 구현되어있는 기존 코드의 일부이다. 위 코드는 <strong>Time interrupt</strong> 에 의해 **Round Robin** 방식으로 작동한다.   
Lab2 에서는 이를 priority 방식으로 구현하는 것이 목적이었다. 그렇기 위해선, 각 프로세스마다 priority 값을 가져야 한다.  
그리하여, **setpriority**, **getpriority** 를 system call 을 추가해주었다. 
    
[ 공통 API 및 규칙 지정 ]  
1. Priority 범위 [ -10 ~ 10 ]   
2. 프로세스의 Priority 초기값 -11   

```c
int setpriority(int pid, int priority_level) ; 
int getpriority(int pid, int * prio); 
```  
   
동일한 코드에서 테스트가 실행될 수 있도록 하기 위해, 공통 API 를 정하여 코드를 작성하였다.   

**setpriority**: PID 값이 0인 경우 현재 프로세스에 Priority 값 지정, 그 외에는 PID 값을 프로세스 테이블에서 찾아 Priority 값 지정   
   
**getpriority**: PID 값이 0인 경우 현재 프로세스에 Priority 값을 **int * prio** 에 저장, 그 외에는 PID 값을 프로세스 테이블에서 찾아 **int * prio** 에 저장   
    
(Code should be revised for System call: **user.h defs.h sysproc.c proc.c usys.S**)   
    
[Priority Scheduler]  
```c
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
  int priority_max = -11 ;
  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
       if(p->state != RUNNABLE) continue;
       for(tmp = ptable.proc; tmp < &ptable.proc[NPROC]; tmp++) {
          if(tmp->state != RUNNABLE)
             continue;
          if(priority_max <= tmp->level) {
             priority_max = tmp->level;
          }
       }
       if(priority_max == p->level) {
          c->proc = p;
          switchuvm(p);
          p->state = RUNNING;
          priority_max = -11;
          swtch(&(c->scheduler), p->context);
          switchkvm();

          c->proc = 0 ;
       }
    }
    release(&ptable.lock);
  }
}
```  

위와 같이 scheduler 코드를 수정해주었으며, priority 에 의해 프로세스들이 잘 작동하는지 여러 테스트 과정을 거쳤다.   
**단, xv6 kernel 에서는 CPU 가 2개로 되어있어 두 개의 프로세스가 각각 scheduler 를 작동시킨다.**  
그렇기에, 매 순간 최대의 Priority 를 찾아주는 방식으로 구현되었다.  
   
이 후, Starvation problem, Inheritance 문제도 해결할 예정이다.   

#### The other Scheduling method  
**1. First in First out (FIFO)**
**2. Shortest Job First (SJF)**   
**3. Shortest Time-to-Completion First (STCF)**   
**4. Round Robin**  
**5. Multi-Level Feedback Queue (MLFQ)**  

## Conclusion    
직접 시스템 콜에 의해 작동하는 기능들도 구현해보고, Scheduler 방식을 수정해보았다.    
   
## 느낀 점  
	하루 하루 정말 많이 배우고 코드를 통해 스케줄러를 직접 구현해봄으로써 동작 원리 뿐만아니라 개념에 대한 이해를 확실히 할 수 있는 순간이었다.   
	공통 테스트 코드가 작동하기 위해 공통 API 를 지정하여 작업을 해보았는데 이러한 경험들이 필요하며 정말 중요하다는 것을 깨닫게 되었다.   
	오늘도 많은 배움을 얻을 수 있는 순간이었다. 
	
