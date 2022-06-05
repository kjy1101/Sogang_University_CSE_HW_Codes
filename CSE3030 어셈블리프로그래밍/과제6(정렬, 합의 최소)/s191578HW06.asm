TITLE s191578HW06

; Program Description: find a minimum of distance sum between the shop and each house
;	1. HW05���� �ۼ��� strlen�� StringToInteger �Լ��� �̿��Ͽ� ���ڿ��� ������ ��ġ�� �Է¹ް�, �̸� �����迭�� �����Ѵ�.
;	2. �����迭�� �ִ� ������ Sorting �Լ��� �̿��� ������������ �����Ѵ�.
;	3-1. ���Կ� ���� �Ѵ� ���� ���������� ���������� �����Ѵ�.
;	3-2. ������ ���� �ϳ� �� �����迭�� ó������ ������ ���鼭 �Ÿ��� ���� ���Ѵ�.
;	3-3. ���� ū ���� �ִ� ����, �� ������ ���Կ� ���� ������ ��ġ�� �Ÿ����� �ּҰ��� ����ִ� eax�� ����Ѵ�.
;	4. ���ο� �Է°��� ���� 1~3������ �ݺ��Ѵ�.(��, ���͸� ġ�� ����)
; Author: Kim Jae Yeon
; Procedures: strlen, StringToInteger, Sorting
; �Լ��� ���: strlen - ���ڿ��� ���̸� ����ϴ� �Լ�
;			  StringToInteger - ���ڿ����� ���ڸ� �����ϴ� �Լ�
;			  Sorting - �����迭�� �ִ� ������ ������������ �����ϴ� �Լ�

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
	mov edx, OFFSET inBuffer	; inBuffer�� ���ڿ��� �Է¹ް� inBuffer�� OFFSET�� edx�� �ִ´�.(parameter passing)
	mov edi, OFFSET intArray	; intArray�� OFFSET�� edi�� �ִ´�.(parameter passing)
	mov ecx, BUF_SIZE
	call ReadString

	call strlen					; inBuffer, �� �Է¹��� ���ڿ��� ���̸� strlen �Լ��� ���� ���Ѵ�.
	mov inBufferN, esi			; inBuffer�� ���̴� inBufferN�� �����Ѵ�.
	mov ecx, inBufferN			; inBuffer�� ���̸� ecx�� �����Ѵ�.(parameter passing)
	cmp ecx, 0
	je quit						; �Է��� ���ڿ��� ���̰� 0, �� ���͸� �������� quit���� �����Ѵ�.
	call StringToInteger		; �ϳ��� ���Ͱ� �ƴ� ���ڸ� �Է��ߴٸ� StringToInteger �Լ��� ȣ���Ѵ�.

	mov edi, OFFSET intArray	; edi�� �ٽ� intArray�� OFFSET�� �ִ´�.(��� ��)
	mov intArrayN, ecx			; intArrayN�� �����迭�� �ִ� �������� ������ �ִ´�.

	cmp intArrayN, 0
	jle L3				; �����迭�� ���ڰ� 0����� L3���� �ǳʶڴ�.
	cmp intArrayN, 1
	je H0				; �����迭�� ���ڰ� 1����� �������� �ʰ� �ٷ� �Ÿ��� ���� ���Ѵ�.
	call Sorting		; �����迭�� ���ڰ� 2�� �̻��϶��� �迭�� ������������ �����Ѵ�.

;=====intArray ���� Ȯ�ο�=====
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
	mov ecx, intArrayN		; ecx�� �����迭�� ���� ������ �ִ´�.
	mov edi, 0				; edi�� ������ ������ ��ġ�� ��Ÿ���Ƿ� �ʱⰪ�� 0���� �����Ѵ�.
	mov eax, 7fffffffh		; eax�� �Ÿ��� ���� �ּ�(���)�� ���� ���̹Ƿ� SDWORD�� ����� �� �ִ� ���� ū ���� �ִ´�.
	H1:
		mov esi, 0			; esi�� ���Կ��� �Ÿ��� ���� ���� ��Ÿ����, �ʱⰪ�� 0���� �����Ѵ�.
		mov edx, 0			; edx�� ���Կ� ���� �Ÿ��� ����� �� �� ��������� �߰� �����Ѵ�.
		H2:
			mov ebx, [intArray+edi]		; ebx�� ������ ��ġ�� �ִ´�.
			sub ebx, [intArray+esi]		; �׸��� ���� ��ġ�� ����.
			cmp ebx, 0
			jge H3						; �Ÿ��� ������ H3���� �ǳʶڴ�.
			neg ebx						; �Ÿ��� ������� ��ȣ�� �����Ѵ�.
			H3:
				add edx, ebx			; edx�� ��� ���� �Ÿ��� ���Ѵ�.
				add esi, TYPE SDWORD	; esi�� ���� ���� ����Ų��.
				mov ecx, intArrayN
				shl ecx, 2
				cmp esi, ecx
				jl H2					; ���� �Ÿ��� ����� ���� ������ �� ����(������ �� ����)��� H2�� ���ư���.
				cmp eax, edx			; ���� �Ÿ��� ����� ���� ������ ���� �ʰ��� ���̶��(�������� �ʴ� ��)
				jle H4					; ���������� �Ÿ��� ���� �ּڰ�(eax)�� �̹��� ����� ��(edx)�� ����
				mov eax, edx			; eax�� �����ϰų� edx�� �����Ѵ�.
				H4:
					add edi, TYPE SDWORD	; ���� ���Կ��� ���� ���� ���Է� �����Ѵ�.
					mov ecx, intArrayN
					shl ecx, 2
					cmp edi, ecx
					jl H1					; �� ���԰� ������ �� ����(������ �� ����)��� H1���� ���ư���.
					call WriteDec			; �׷��� �ʴٸ� eax(���� �����)�� ����Ѵ�.
					call Crlf


	L3:
	jmp L0

	quit:
		mov edx, OFFSET goodbye_message	; ���� �޼����� ����ϰ� ���α׷��� �����Ѵ�.
		call WriteString

	exit
main ENDP

; ===================================

strlen PROC
; function: ���ڿ��� ���̸� ����ϴ� �Լ�
; Recieves: OFFSET of string(edx)
; Returns: length of string(esi)
; ------------------------------------
	mov esi, -1
	L1:
		inc esi
		mov bl, [edx+esi]
		cmp bl, 0			; ���ڿ��� esi��°�� �ִ� ���� 0(end of string)�� �ƴϸ� 1�� �÷����� ������ ����.
		jne L1				; ���ڿ��� esi��°�� �ִ� ���� 0(end of string)�̸� ���� ���⸦ �����Ѵ�.

	ret
strlen ENDP
; ===================================

StringToInteger PROC
; function: ���ڿ��κ��� ���������� �����ϴ� �Լ�
; Receives: OFFSET of string(edx), length of string(ecx), OFFSET of integerArray(edi)
; Returns: number of integer values(ecx), OFFSET of integerArray(edi)
; Calls: ParseInteger32
; ------------------------------------
	mov esi, 0	; esi: ���ڿ� ��ü�� ���ʴ�� �湮�� �ε���
	mov ebx, 0	; ebx: ���������κ��� ��� ���ڸ� �ٲܰ����� �����Ѵ�.
				; eax: ������ �ٲ� ���ڿ��� ���� �ּ�
				; edx: ���ڿ� ��ü�� �����ּ�
	push edi	; edi: �����迭 ��ü�� �����ּҸ� �����س��´�.

	;===[edx+esi]�� edx�κ��� esi��ŭ ������ ������ ������, '���簪'�̶�� �θ���.===
	
	T1:
		push ecx
		mov ecx, 0
		mov cl, [edx+esi]
		cmp cl, 20h			; ���簪�� �����ΰ�?
		pop ecx
		je Blank			; ���簪�� �����̶�� Blank�� �����Ѵ�.
							; ���簪�� ������ �ƴ϶�� ��� �����Ѵ�.
		mov eax, edx
		add eax, esi		; eax <- edx+esi, eax�� ���簪�� �ּҸ� �ִ´�.

	T2:
		inc ebx				; ������ �ٲ���� ������ ������ 1 �ø���.
		inc esi				; �������� ���� ���� esi�� 1 �ø���. �������� ���簪�� �������̴�.
		cmp esi, ecx		; esi�� ecx���� ũ�ų� ������? ��, ���簪�� ���ڿ��� ���������ΰ�?
		jge print			; ���簪�� ���ڿ��� ���������̶�� print�� �����Ѵ�.
							; ���簪�� ���ڿ��� ���������� �ƴ϶�� ��� �����Ѵ�.
		push ecx
		mov ecx, 0
		mov cl, [edx+esi]
		cmp cl, 20h			; ���簪�� �����ΰ�?
		pop ecx
		je print			; ���簪�� �����̶�� print�� �����Ѵ�.
		jmp T2				; ���簪�� ������ �ƴ϶�� T2�� �ǵ��ư���.

	Blank:
		inc esi				; �������� ���� ���� esi�� 1 �ø���. �������� ���簪�� �������̴�.
		cmp esi, ecx
		jge quit			; ���簪�� ���ڿ��� ���������̶�� quit���� �����Ѵ�.
		jmp T1				; ���簪�� ���ڿ��� ���������� �ƴ϶�� T1���� �ǵ��ư���.

	print:
		push edx
		push ecx
		mov edx, eax			; edx�� ���ڷ� �ٲ� ���ڿ��� ���� �ּҸ� �ִ´�.
		mov ecx, ebx			; ebx�� ���ڷ� �ٲ� ���ڿ��� ���̸� �ִ´�.
		call ParseInteger32		; �Լ��� �̿��ؼ� ���ڿ��� ������ �ٲ۴�.

		mov [edi], eax			;�����迭�� ���ڿ��κ��� ������ ������ �ִ´�.
		add edi, TYPE SDWORD	;�������� ����Ű�� ���� edi�� TYPE SDWORD�� ���Ѵ�.

		mov ebx, 0				; ebx�� 0���� �ʱ�ȭ�Ѵ�.
		pop ecx
		pop edx
		cmp esi, ecx			; esi>=ecx, �� ���ڿ��� ���̸� quit���� �����Ѵ�.
		jge quit
		jmp T1					; ���ڿ��� ���� �ƴ϶�� T1���� �ǵ��ư���.

	quit:						; ���ڿ��κ��� ��� ������ �����س����Ƿ� ������ ������ ������ ����.
		mov edx, 0
		mov eax, edi			; eax���� �ڷ� �и� edi�� �ִ´�.
		pop edi					; pop�� ���� ���� �����迭 ��ü�� �����ּҸ� ����Ű�� edi�� �ҷ��´�.
		sub eax, edi			; �� ���� ���̸� ���Ѵ�.
		mov ecx, TYPE SDWORD
		div ecx					; ������ ���ϱ� ���� TYPE SDWORD�� ������.
		mov ecx, eax			; ecx�� ������ ������ �����Ѵ�.


	ret
StringToInteger ENDP

; ===================================

Sorting PROC
; function: �����迭�� �ִ� ���������� ������������ �����ϴ� �Լ�
; Receives: OFFSET of integerArray(edi), number of integer values(ecx)
; Returns: OFFSET of sorted integerArray(edi)
; �������� �˰����� ����Ͽ� �����迭�� �ִ� ���������� ������������ �����Ѵ�.
; ------------------------------------
	dec ecx
	L1:
		mov ebx, ecx						; 2�� �ݺ������� L2�� ecx(�ݺ��ϴ� Ƚ��)�� L1�� ecx�� ������ �����Ƿ� ecx�� ebx�� �����ϰ�,
		push ecx							; push�� �̿��� �� �����Ѵ�.
		L2:
			push ebx						; L2���� ebx�� L1�� ecx�� �ǹ��ϰ�, �� ���� L2�� ���� ���� �ٲ��� �ʾƾ� �ϹǷ� �����Ѵ�.
			sub ebx, ecx					; ebx(L1�� ecx)���� L2�� ecx�� ����.
			shl ebx, 2						; �����迭�� SDWORD�� ����Ǿ� �����Ƿ� 4�� ���Ѵ�.
			mov eax, [edi+ebx]
			cmp eax, [edi+ebx+TYPE SDWORD]	; �����迭�� ebx��° ���ڿ� �� ����(������)�� �ִ� ���ڸ� ���Ѵ�.
			JG exchange						; ebx��° ���ڰ� ebx+4��° ���ں��� ũ�ٸ� ���� ��ġ�� �ٲ۴�.
			pop ebx
		loop L2
		pop ecx
	loop L1
	jmp quit								; ������ ������ quit���� �����Ѵ�.

	exchange:
		mov eax, [edi+ebx]
		xchg eax, [edi+ebx+TYPE SDWORD]		; �����迭�� ebx+4��° ���� �ڸ��� ebx��° ���ڸ� �ִ´�.
		mov [edi+ebx], eax					; �����迭�� ebx��° ���� �ڸ����� ebx+4��° ���ڸ� �ִ´�.
		dec ecx
		pop ebx
		cmp ecx, 0
		jg L2								; ������ ������ ��ȯ�� �ƴϾ��ٸ� �ٽ� L2�� ���ư���.
		pop ecx
		jmp L1								; ������ ������ ��ȯ�̾��ٸ� ���� ���� �񱳸� ���� L1���� ���ư���.

	quit:

	ret
Sorting ENDP

; ===================================

END main