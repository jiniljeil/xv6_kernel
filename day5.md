## xv6_kernel_study Day5
  
Date: 2021-07-16

## System call 이란? 
	커널이 제공하는 서비스에 대해, 응용 프로그램의 요청에 따라 커널에 접근하기 위한 인터페이스이다. 

## System call 호출 과정 
	
	[User space] 
	1. User space program 이 커널에게 서비스를 요청  
	2. eax register 에 system call number를 저장한 후, system call 요청   
	
	[Kernel space]
	3. trap 에 의해 syscall 발생, syscall 은 %eax와 인덱스를 포함하는 trap frame 으로부터 system call number 로드  
	4. syscall 은 system call table 에 해당되는 entry 를 발생시킴  
        5. User space program 의 인자 값을 읽어옴 (xv6 kernel: argint, argptr, argstr 등) 
	6. 커널에서 서비스 처리 
   
## 느낀점
	오늘은 Lab1을 진행하면서 코드짜는 것에 중심을 두어 진행하였다.   
        xv6 kernel 스터디를 진행한지 5일 동안 정말 많은 것들은 배울 수 있었다.   
  	예전 글로만 봤었던 시스템 내부 동작들이, 운영체제와 컴퓨터 구조를 배운 후   
	코드들을 통해 직접 동작하는 것을 보니 확실히 더 와닿은 것 같다.  
        특히, system call 에 의해 작동하는 waitpid() 를 구현해보면서 정말 재밌게 공부할 수 있었던 것 같다.    	
