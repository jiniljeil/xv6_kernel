## xv6_kernel_study Lab2
  
Date: 2021-07-22  

[xv6 memory structure] 
  
```
code
stack (fixed-sized, one page)
heap (grows towards the high-end of the address space)
``` 

XV6 메모리 구조 위와 같이 구성되어있다. 이를 아래와 같이 바꾸는 것이 LAB3 작업이다.   

[xv6 rearranged memory structure]
   
```
code
heap (grows towards the high-end of the address space)
... (gap)
stack (at end of address space; grows backwards)
```

(XV6 Criteria)

## Virtual Address
    
[ Dir | Table | Offset ]
   
## Physical Address 
  
Range (0 ~ 1023) [ 20 bits | 12 bits ]
   
[ PPN | Offset ] 

- Detail  
 
  [ Physical Page Number (20) | AVL(3) | (2) | D(1) | A(1) | CD(1) | WT(1) | U(1) | W(1) | P(1) ] 
    
  - AVL : Available for system use 
  - D : Dirty (0 in page directory) 
  - A : Accessed 
  - CD : Cache Disabled 
  - WT : 1 = Write-through, 0 = Write-back 
  - U : User ( Page 사용 가능 여부, 0 = kernel 만 사용 가능, 1 = user 사용 가능) 
  - W : Writable (0 = read, instruction fetch)
  - P : Present (whether PTE exists or not) 
    
   
## Page Directory 
    
Range (0 ~ 1023) [ 20 bits | 12 bits ] 
  
[ PPN | Flags ] 
      
## Page Table 
     
Range (0 ~ 1023) [ 20 bits | 12 bits ] 
   
[ PPN | Flags ]
      
각각의 프로세스는 페이지 테이블 갖는다. 프로세스 간에 Context Switching 발생 시 Page Table 을 바꿔줌  
커널은 자기 자신의 Kernel Page table 을 갖고 있지 않기에 프로세스의 page table 을 빌려받음 


Exec()  
   
1. Reads the ELF header  
   (ELF Binary consists of an ELF header, struct elfhdr, section headers, struct proghdr)
2. Checks the magic number 
  
3. Allocates a new page table with no user mapping with setupkvm()
   
4. Allocates memory for each ELF segment with allocuvm() 
   (allocuvm checks that the virtual addresses requested is below KERNBASE(0x80000000)   
    
5. Loads each segment into memory with loaduvm() 
   (loaduvm uses wlakpgdir to find the physical address of the allocated memory at which to write each page of the ELF segment, and readi to read from the file)    

## 느낀 점  
   메모리가 어떻게 할당되며, 메모리에 데이터가 어떤 과정으로 로드되는지 알아볼 수 있었다. 또한 스택 영역을 높은 주소 영역에 놓는 작업을 시도하였다. 



