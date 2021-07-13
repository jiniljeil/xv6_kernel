## xv6_kernel_study Day2
  
Date: 2021-07-13

## ELF (Executable and Linking Format) 
	1. ELF Header 
		모든 ELF 파일의 시작부분에 위치, Program Header 와 Section Header에 관련된 정보 포함 
		Magic number를 통해 ELF 파일인지 확인

	2. Program Header Table 
		ELF 내에 Segment 들에 대한 정보와 프로그램 실행을 위해 시스템이 필요한 기타 정보들을 포함 
		
		(Object file 들은 section만 가지고 있으며, linking 과정에서 section 정보들이 ELF 파일 내 segment들에 위치하게 되어 program header 정보 없음) 
			
		- Segment
		동일한 메모리 속성을 가진 section의 집합 

	3. Section 
		ELF 에서 처리 될 수 있는 가장 작은 단위, ELF header, Program header table, Section header table 을 제외한 오브젝트 파일에 모든 정보를 포함
		- .bss section 
		- .data section 
		- .dynamic section 
		- .dynsym section 
		- .fini section 
		- .init section 
		- etc... 

	4. Section Header Table	
		ELF를 구성하는 각각 다른 Section을 정의하는 Section Header 구조체가 연속된 메모리에 나열

	
	Reference: https://refspecs.linuxfoundation.org/elf/elf.pdf

## Entry
	부트 로더에서 entry()를 통해 커널로 넘어가게 되면, entry.S 코드가 실행된다. 
	이 때, 페이지 테이블이 형성되고, 페이징이 활성화되며, control register에 플래그를 통해 모드 변경 (protected mode -> address mode) (추가 설명: protected mode 이전 모드=real mode)
	이후, high address로 변환 후, main 호출 (main이 호출되면, init 프로세스가 작동) 
	
어셈블리어 코드 레지스터 설명:
 
	The WP and PG flags in control register CR0 (bit 16 and bit 31, respectively).
	The PSE, PAE, and PGE flags in control register CR4 (bit 4, bit 5, and bit 7, respectively).
		
	CR0_PG가 CR0 register에 mov 하게 되면, 페이징을 활성화한다. 
	CR3 register에는 프로세서가 선형 주소 변환에 사용할 첫 번째 페이징 구조의 물리적 주소가 포함되어 있으며, 해당 구조가 원하는 대로 초기화 
 	CR4 set Page Size Extension allows for pages larger than the traditional 4 KiB size 
		
	CASE1: CR0.PG = 1, CR4.PAE = 0  (32 bit paging) 
	CASE2: CR0.PG = 1, CR4.PAE = 1, and IA32_EFER.LME = 0 (PAE paging)
	CASE3: CR0.PG = 1, CR4.PAE = 1, and IA32_EFER.LME = 1, (IA-32e paging)
	
	Reference: https://en.wikipedia.org/wiki/Control_register
## 느낀 점 
	공부를 할 때, 공식적인 문서를 토대로 공부하는 습관이 중요하다는 것을 깨닫게 되었고, 
	하나를 익히더라도 제대로 익히는 것이 중요하다는 생각이 들게 되었다.  

