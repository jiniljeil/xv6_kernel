## xv6_kernel_study Day3
  
Date: 2021-07-14

## console.c  
    	
Input: Keyboard & Serial Port 로 부터 입력 
Output: Screen & Serial Port 에 출력    

[inline assembly]   
__asm__ __volatile__ (asms : output : input : clobber);	   
	
1. outb(port, data) - "out %0 %1::"d"(data) "a" (port)":   
	
AL, AX 또는 EAX 레지스터의 내용이 가리키는 메모리 주소에서 byte, word, long 값을 DX register 에 지정된 포트로 전송하거나, 포트 주소로 전송    
	
2. inb(port, data) - "in %1,%0" : "=a" (data) : "d" (port);   
 
byte, word, long을 Port 혹은 DX register에 지정된 포트에서   
AL, AX, 또는 EAX 레지스터가 각각 가리키기는 byte, word, long 주소로 전송    
    
## 느낀 점
오늘은 kernel의 entry가 실행이 되고난 후, kernel stack의 시작 주소가 어디에 있으며,   
ebp, esp 값이 어떻게 변화하는지 GDB를 통해 알아봄으로써, entry -> main 으로 이동하기 전에   
어떤 작업들을 하는지 알 수 있었다. 또한 console.c 코드를 보며, 어떻게 I/O device 와 데이터를 주고 받는지 배울 수 있었다.    
	
