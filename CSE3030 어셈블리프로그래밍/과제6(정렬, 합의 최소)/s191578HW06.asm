TITLE s191578HW06

; Program Description: find a minimum of distance sum between the shop and each house
;	1. HW05에서 작성한 strlen과 StringToInteger 함수를 이용하여 문자열로 집들의 위치를 입력받고, 이를 정수배열로 추출한다.
;	2. 정수배열에 있는 값들을 Sorting 함수를 이용해 오름차순으로 정렬한다.
;	3-1. 가게와 집은 둘다 제일 작은값부터 순차적으로 선택한다.
;	3-2. 선택한 가게 하나 당 정수배열을 처음부터 끝까지 돌면서 거리의 합을 구한다.
;	3-3. 제일 큰 값에 있는 가게, 즉 마지막 가게에 대한 계산까지 마치면 거리합의 최소값이 들어있는 eax를 출력한다.
;	4. 새로운 입력값에 대해 1~3과정을 반복한다.(단, 엔터만 치면 종료)
; Author: Kim Jae Yeon
; Procedures: strlen, StringToInteger, Sorting
; 함수의 기능: strlen - 문자열의 길이를 계산하는 함수
;			  StringToInteger - 문자열에서 숫자를 추출하는 함수
;			  Sorting - 정수배열에 있는 값들을 오름차순으로 정렬하는 함수

INCLUDE Irvine32.inc

.data
BUF_SIZE EQU 256
inBuffer BYTE BUF_SIZE DUP(?)
inBufferN DWORD ?
intArray SDWORD BUF_SIZE/2 DUP(?)
intArrayN DWORD ?
start_message BYTE "Enter numbers(<ent> to exit) : ", 0
goodbye_message BYTE "Bye!", 0

.code
main PROC

L0:
	mov edx, OFFSET start_message
	call WriteString
	call Crlf
	mov edx, OFFSET inBuffer	; inBuffer에 문자열을 입력받고 inBuffer의 OFFSET을 edx에 넣는다.(parameter passing)
	mov edi, OFFSET intArray	; intArray의 OFFSET을 edi에 넣는다.(parameter passing)
	mov ecx, BUF_SIZE
	call ReadString

	call strlen					; inBuffer, 즉 입력받은 문자열의 길이를 strlen 함수를 통해 구한다.
	mov inBufferN, esi			; inBuffer의 길이는 inBufferN에 저장한다.
	mov ecx, inBufferN			; inBuffer의 길이를 ecx에 저장한다.(parameter passing)
	cmp ecx, 0
	je quit						; 입력한 문자열의 길이가 0, 즉 엔터만 눌렀으면 quit으로 점프한다.
	call StringToInteger		; 하나라도 엔터가 아닌 문자를 입력했다면 StringToInteger 함수를 호출한다.

	mov edi, OFFSET intArray	; edi에 다시 intArray의 OFFSET을 넣는다.(없어도 됨)
	mov intArrayN, ecx			; intArrayN에 정수배열에 있는 정수값의 개수를 넣는다.

	cmp intArrayN, 0
	jle L3				; 정수배열에 숫자가 0개라면 L3으로 건너뛴다.
	cmp intArrayN, 1
	je H0				; 정수배열에 숫자가 1개라면 정렬하지 않고 바로 거리의 합을 구한다.
	call Sorting		; 정수배열에 숫자가 2개 이상일때만 배열을 오름차순으로 정렬한다.

;=====intArray 내용 확인용=====
;	mov esi, 0
;	mov ecx, intArrayN
;	test_loop:
;		mov eax, [edi+esi]
;		call WriteInt
;		add esi, TYPE SDWORD
;	loop test_loop
;	call Crlf
;=============================
H0:	
	mov ecx, intArrayN		; ecx에 정수배열의 원소 개수를 넣는다.
	mov edi, 0				; edi는 선택할 가게의 위치를 나타내므로 초기값은 0으로 설정한다.
	mov eax, 7fffffffh		; eax에 거리의 합의 최소(결론)를 넣을 것이므로 SDWORD로 선언될 수 있는 가장 큰 값을 넣는다.
	H1:
		mov esi, 0			; esi는 가게와의 거리를 구할 집을 나타내고, 초기값은 0으로 설정한다.
		mov edx, 0			; edx는 가게와 집의 거리를 계산할 때 그 결과값들을 중간 저장한다.
		H2:
			mov ebx, [intArray+edi]		; ebx에 가게의 위치를 넣는다.
			sub ebx, [intArray+esi]		; 그리고 집의 위치를 뺀다.
			cmp ebx, 0
			jge H3						; 거리가 양수라면 H3으로 건너뛴다.
			neg ebx						; 거리가 음수라면 부호를 반전한다.
			H3:
				add edx, ebx			; edx에 방금 구한 거리를 더한다.
				add esi, TYPE SDWORD	; esi는 다음 집을 가리킨다.
				mov ecx, intArrayN
				shl ecx, 2
				cmp esi, ecx
				jl H2					; 이제 거리를 계산할 집이 마지막 집 이하(마지막 집 포함)라면 H2로 돌아간다.
				cmp eax, edx			; 이제 거리를 계산할 집이 마지막 집을 초과한 집이라면(존재하지 않는 집)
				jle H4					; 기존까지의 거리의 합의 최솟값(eax)과 이번에 계산한 값(edx)을 비교해
				mov eax, edx			; eax를 유지하거나 edx로 갱신한다.
				H4:
					add edi, TYPE SDWORD	; 현재 가게에서 다음 집을 가게로 선택한다.
					mov ecx, intArrayN
					shl ecx, 2
					cmp edi, ecx
					jl H1					; 이 가게가 마지막 집 이하(마지막 집 포함)라면 H1으로 돌아간다.
					call WriteDec			; 그렇지 않다면 eax(최종 결과값)를 출력한다.
					call Crlf


	L3:
	jmp L0

	quit:
		mov edx, OFFSET goodbye_message	; 종료 메세지를 출력하고 프로그램을 종료한다.
		call WriteString

	exit
main ENDP

; ===================================

strlen PROC
; function: 문자열의 길이를 계산하는 함수
; Recieves: OFFSET of string(edx)
; Returns: length of string(esi)
; ------------------------------------
	mov esi, -1
	L1:
		inc esi
		mov bl, [edx+esi]
		cmp bl, 0			; 문자열의 esi번째에 있는 값이 0(end of string)이 아니면 1씩 늘려가며 개수를 센다.
		jne L1				; 문자열의 esi번째에 있는 값이 0(end of string)이면 개수 세기를 종료한다.

	ret
strlen ENDP
; ===================================

StringToInteger PROC
; function: 문자열로부터 정수값들을 추출하는 함수
; Receives: OFFSET of string(edx), length of string(ecx), OFFSET of integerArray(edi)
; Returns: number of integer values(ecx), OFFSET of integerArray(edi)
; Calls: ParseInteger32
; ------------------------------------
	mov esi, 0	; esi: 문자열 전체를 차례대로 방문할 인덱스
	mov ebx, 0	; ebx: 시작점으로부터 몇개의 문자를 바꿀건지를 저장한다.
				; eax: 정수로 바꿀 문자열의 시작 주소
				; edx: 문자열 전체의 시작주소
	push edi	; edi: 정수배열 전체의 시작주소를 저장해놓는다.

	;===[edx+esi]는 edx로부터 esi만큼 떨어진 지점의 값으로, '현재값'이라고 부른다.===
	
	T1:
		push ecx
		mov ecx, 0
		mov cl, [edx+esi]
		cmp cl, 20h			; 현재값이 공백인가?
		pop ecx
		je Blank			; 현재값이 공백이라면 Blank로 점프한다.
							; 현재값이 공백이 아니라면 계속 진행한다.
		mov eax, edx
		add eax, esi		; eax <- edx+esi, eax에 현재값의 주소를 넣는다.

	T2:
		inc ebx				; 정수로 바꿔야할 문자의 개수를 1 늘린다.
		inc esi				; 다음값을 보기 위해 esi를 1 늘린다. 이제부터 현재값은 다음값이다.
		cmp esi, ecx		; esi가 ecx보다 크거나 같은가? 즉, 현재값이 문자열의 마지막값인가?
		jge print			; 현재값이 문자열의 마지막값이라면 print로 점프한다.
							; 현재값이 문자열의 마지막값이 아니라면 계속 진행한다.
		push ecx
		mov ecx, 0
		mov cl, [edx+esi]
		cmp cl, 20h			; 현재값이 공백인가?
		pop ecx
		je print			; 현재값이 공백이라면 print로 점프한다.
		jmp T2				; 현재값이 공백이 아니라면 T2로 되돌아간다.

	Blank:
		inc esi				; 다음값을 보기 위해 esi를 1 늘린다. 이제부터 현재값은 다음값이다.
		cmp esi, ecx
		jge quit			; 현재값이 문자열의 마지막값이라면 quit으로 점프한다.
		jmp T1				; 현재값이 문자열의 마지막값이 아니라면 T1으로 되돌아간다.

	print:
		push edx
		push ecx
		mov edx, eax			; edx에 숫자로 바꿀 문자열의 시작 주소를 넣는다.
		mov ecx, ebx			; ebx에 숫자로 바꿀 문자열의 길이를 넣는다.
		call ParseInteger32		; 함수를 이용해서 문자열을 정수로 바꾼다.

		mov [edi], eax			;정수배열에 문자열로부터 추출한 정수를 넣는다.
		add edi, TYPE SDWORD	;다음값을 가리키기 위해 edi에 TYPE SDWORD를 더한다.

		mov ebx, 0				; ebx를 0으로 초기화한다.
		pop ecx
		pop edx
		cmp esi, ecx			; esi>=ecx, 즉 문자열의 끝이면 quit으로 점프한다.
		jge quit
		jmp T1					; 문자열의 끝이 아니라면 T1으로 되돌아간다.

	quit:						; 문자열로부터 모든 정수를 추출해냈으므로 추출한 정수의 개수를 센다.
		mov edx, 0
		mov eax, edi			; eax에는 뒤로 밀린 edi를 넣는다.
		pop edi					; pop을 통해 원래 정수배열 전체의 시작주소를 가리키던 edi를 불러온다.
		sub eax, edi			; 두 값의 차이를 구한다.
		mov ecx, TYPE SDWORD
		div ecx					; 개수를 구하기 위해 TYPE SDWORD로 나눈다.
		mov ecx, eax			; ecx에 숫자의 개수를 저장한다.


	ret
StringToInteger ENDP

; ===================================

Sorting PROC
; function: 정수배열에 있는 정수값들을 오름차순으로 정렬하는 함수
; Receives: OFFSET of integerArray(edi), number of integer values(ecx)
; Returns: OFFSET of sorted integerArray(edi)
; 버블정렬 알고리즘을 사용하여 정수배열에 있는 정수값들을 오름차순으로 정렬한다.
; ------------------------------------
	dec ecx
	L1:
		mov ebx, ecx						; 2중 반복문에서 L2의 ecx(반복하는 횟수)는 L1의 ecx의 영향을 받으므로 ecx를 ebx에 저장하고,
		push ecx							; push를 이용해 또 저장한다.
		L2:
			push ebx						; L2에서 ebx는 L1의 ecx를 의미하고, 이 값은 L2를 도는 동안 바뀌지 않아야 하므로 저장한다.
			sub ebx, ecx					; ebx(L1의 ecx)에서 L2의 ecx를 뺀다.
			shl ebx, 2						; 정수배열이 SDWORD로 선언되어 있으므로 4를 곱한다.
			mov eax, [edi+ebx]
			cmp eax, [edi+ebx+TYPE SDWORD]	; 정수배열의 ebx번째 숫자와 그 다음(오른쪽)에 있는 숫자를 비교한다.
			JG exchange						; ebx번째 숫자가 ebx+4번째 숫자보다 크다면 둘의 위치를 바꾼다.
			pop ebx
		loop L2
		pop ecx
	loop L1
	jmp quit								; 정렬이 끝나면 quit으로 점프한다.

	exchange:
		mov eax, [edi+ebx]
		xchg eax, [edi+ebx+TYPE SDWORD]		; 정수배열의 ebx+4번째 숫자 자리에 ebx번째 숫자를 넣는다.
		mov [edi+ebx], eax					; 정수배열의 ebx번째 숫자 자리에는 ebx+4번째 숫자를 넣는다.
		dec ecx
		pop ebx
		cmp ecx, 0
		jg L2								; 마지막 숫자의 교환이 아니었다면 다시 L2로 돌아간다.
		pop ecx
		jmp L1								; 마지막 숫자의 교환이었다면 다음 숫자 비교를 위해 L1으로 돌아간다.

	quit:

	ret
Sorting ENDP

; ===================================

END main