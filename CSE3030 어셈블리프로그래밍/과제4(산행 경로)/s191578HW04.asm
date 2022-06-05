TITLE s191578HW04

; Program Description: update highest and lowest in downhill, and calculated greatest difference in uphill or flat section
; Author: Kim Jae Yeon
; Creation Date: 2020. 5. 24
; function: find the height of the downhill which has the greatest altitude difference
; input: number of test, (list size, heights measured) * number of test
; output: greatest difference among downhills

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW04.inc

.data
highest DWORD 0		;내리막의 최고점
lowest DWORD 0		;내리막의 최저점

.code
main PROC
	
	mov ecx, TN
TEST_CASE:
	push ecx
	cmp ecx, 0		;오류 처리를 위해 ecx가 0이면 종료한다.
	je quit

	cmp ecx, TN
	je put_Case
	jne put_Height

	put_Case:					;첫번째 test case일 때는 ecx에 CASE를 넣는다.
		mov ecx, CASE
		mov esi, 0
		sub ecx, 1				;마지막값은 보지 않을 것이므로 1을 뺀다.
		mov edx, 0				;edx에는 최고높이차이를 넣을 것이고, 이후 연산에서의 비교를 위해 0으로 초기화한다.
		jmp L1

	put_Height:					;두번째 이상의 test case일 때는 HEIGHT에 있는 값을 넣어야 한다.
		mov ecx, HEIGHT[esi+4]
		add esi, 8				;등산로는 현재 esi값으로부터 두 칸(8) 뒤에서 시작한다.
		sub ecx, 1
		mov edx, 0

	L1:							;main loop
		cmp ecx, 0				;오류 처리를 위해 ecx가 0이면 quit_print로 점프한다.
		je quit_print
		mov eax, HEIGHT[esi]	;HEIGHT[esi]는 현재 고려중인 지점으로, '현재값'이라고 부른다.
		cmp eax, HEIGHT[esi+4]
		jg downhill				;현재값>다음값(내리막)
		jle uphill				;현재값<=다음값(오르막 or 평지)
	loop L1
	jmp quit_print				;등산로 하나의 연산이 모두 끝나면 결과값을 출력한다.

loop TEST_CASE
	jmp quit					;모든 등산로를 고려했으면 프로그램을 종료한다.


	downhill:					;내리막
		cmp eax, highest
		jg update_highest		;현재값이 기존까지의 최고점보다 크면 최고점을 현재값으로 갱신한다.
		mov ebx, HEIGHT[esi+4]
		mov lowest, ebx			;최저점에는 다음값이 들어간다.
		add esi, 4				;다시 L1으로 돌아가기 전에 esi, ecx값을 조정한다.
		dec ecx
		cmp ecx, 0
		je uphill2				;ecx가 0이라면 uphill2로 점프한다.(L1으로 돌아가지 않음)
		jmp L1


	update_highest:
			mov highest, eax	;최고점에 현재값을 넣고 다시 downhill로 돌아간다.
			jmp downhill
	

	uphill:						;오르막 or 평지
		mov ebx, highest		;현재 고려중인 내리막의 높이차이(highest-lowest)를 구한다.
		sub ebx, lowest
		cmp ebx, edx
		jg update_height		;현재의 높이차이가 기존의 최대높이차이보다 크면 최대높이를 현재 높이차이로 갱신한다.
		mov highest, 0			;다음 내리막 연산을 위해 highest와 lowest를 0으로 초기화한다.
		mov lowest, 0
		add esi, 4				;L1으로 돌아가기 전에 esi와 ecx값을 조정한다.
		dec ecx
		jmp L1


	update_height:
			mov edx, ebx		;최대높이차이(edx)에 현재 높이차이를 넣고 다시 uphill로 돌아간다.
			jmp uphill


	uphill2:
		mov ebx, highest		;현재 고려중인 내리막의 높이차이(highest-lowest)를 구한다.
		sub ebx, lowest
		cmp ebx, edx
		jg update_height2		;현재의 높이차이가 기존의 최대높이차이보다 크면 최대높이를 현재 높이차이로 갱신한다.
		mov highest, 0			;highest와 lowest를 0으로 초기화하고 L1으로 돌아간다.
		mov lowest, 0
		jmp L1

	update_height2:
		mov edx, ebx			;최대높이차이(edx)에 현재 높이차이를 넣고 다시 uphill2로 돌아간다.
		jmp uphill2
		

	quit_print:					;등산로 하나의 연산이 모두 끝난 후 결과값을 출력한다.
		pop ecx					;TEST_CASE에 대한 ecx값을 불러온다.
		dec ecx
		mov eax, edx
		call WriteDec			;edx에 있던 값을 eax에 옮겨서 출력한다.
		call Crlf
		call Crlf
		jmp TEST_CASE

	quit:						;최종 종료

	exit
main ENDP
END main