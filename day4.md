## xv6_kernel_study Day4
  
Date: 2021-07-15

## Traps, Interrupts, and drivers 
	
Trap 은 current process 에 의해 발생, Interrupts 는 디바이스에 의해 발생    
	
Interrupts 0 - 31 : software exceptions   
- divide errors or attempts to access invalid memory addresses.   
   
Interrupts 32 - 63 : hardware interrupt  
     
Interrupt 64 : system call interrupt   

	
Trap 발생 시, 두 가지 경우   

1. User mode 경우  
프로세서는 테스크 세그먼트 디스크립터(task segment descriptor) %esp, %ss register를 로드한 후,   
%ss 및 %esp 이전 사용자를 새 스택으로 푸시  
    
2. Kernel mode 경우   
프로세서는 %eflags, %cs, %eip 레지스터를 푸시    
   
Alltraps 는 프로세서 레지스터를 저장   
(%ds, %es, %fs, %gs / general-purpose registers)    
		
[ trap frame ]   
kernel stack은 프로세서 레지스터들을 포함한 struct trapframe 을 포함    
kernel 이 현재 프로세스로 리턴할 때, trap frame은 user mode processor registers 를 restore 하기 위해 모든 정보를 포함    
     
## Creating the first process 
    
메인에서 몇 개의 디바이스들과 서브 시스템들이 초기화 된 이후, userinit 프로세스를 생성한다. userinit 프로세스는 allocproc 프로세스를 호출하고, 이 프로세스는 프로세스 테이블에 슬롯(struct proc)를 할당하고, 프로세스의 상태를 초기화 시키는 역할을 한다.     
    
프로세스 테이블에 사용되지 않은 슬롯이 있으면, allocproc 는 UNUSED 상태인 init 프로세스를 EMBRYO 상태로 만든다. 이후, 프로세스의 커널 스레드를 위해 커널 스택을 할당한다. 메모리 할당 실패 시, UNUSED 상태로 되돌림.    
	
		
## 느낀 점 
	커널 스택이 어떻게 형성되고, 커널이 하는 역할들에 대해 더욱 깊이 배울 수 있는 것 같다. 
	또한 System call 이 어떻게 작동되는지 코드를 통해 이해할 필요가 있는 것 같다. 
