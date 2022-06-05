TITLE s191578HW05 List Sum

; Program Decription: Extract integer values from string and add them all
; Author: Kim Jae Yeon
; Procedures: main, strlen, StringToInteger, ArraySum

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

	mov edi, OFFSET intArray	; edi에 다시 intArray의 OFFSET을 넣는다.
	mov intArrayN, ecx			; intArrayN에 정수배열에 있는 정수값의 개수를 넣는다.
	call ArraySum				; ArraySum 함수를 호출해 정수배열에 있는 값들을 모두 더한다.
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

ArraySum PROC
; function: 정수 배열에 있는 값들을 모두 더하는 함수
; Receives: OFFSET of integerArray(edi), number of integers in array(ecx)
; Returns: sum of all integer values
; Calls: WriteInt(if result is neg), WriteDec(if result is pos)
; ------------------------------------
	cmp ecx, 0					; 정수배열에 저장된 숫자가 0보다 작거나 같다면 quit으로 점프한다.
	jle quit
	mov esi, 0
	mov eax, [edi+esi]			; eax에 정수배열의 첫 값을 넣는다.
	dec ecx
	L1:
		cmp ecx, 0				; 정수배열에 저장된 숫자가 1개였다면 L2로 점프한다.
		jle L2
		add esi, TYPE SDWORD	; 정수배열의 다음값을 가리킨다.
		add eax, [edi+esi]		; eax에 그 값을 더한다.
	loop L1

L2:	
	cmp eax, 0
	jge unsigned_print			; eax(합)가 양수라면 unsigned_print로 점프한다.

	call WriteInt				; eax(합)가 음수라면 WriteInt를 통해 출력한다.
	call Crlf
	jmp quit

	unsigned_print:
		call WriteDec			; eax(합)가 양수라면 WriteDec를 통해 출력한다.
		call Crlf

	quit:

	ret
ArraySum ENDP

; ===================================


END main