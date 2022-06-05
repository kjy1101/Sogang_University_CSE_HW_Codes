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

	mov edi, OFFSET intArray	; edi�� �ٽ� intArray�� OFFSET�� �ִ´�.
	mov intArrayN, ecx			; intArrayN�� �����迭�� �ִ� �������� ������ �ִ´�.
	call ArraySum				; ArraySum �Լ��� ȣ���� �����迭�� �ִ� ������ ��� ���Ѵ�.
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

ArraySum PROC
; function: ���� �迭�� �ִ� ������ ��� ���ϴ� �Լ�
; Receives: OFFSET of integerArray(edi), number of integers in array(ecx)
; Returns: sum of all integer values
; Calls: WriteInt(if result is neg), WriteDec(if result is pos)
; ------------------------------------
	cmp ecx, 0					; �����迭�� ����� ���ڰ� 0���� �۰ų� ���ٸ� quit���� �����Ѵ�.
	jle quit
	mov esi, 0
	mov eax, [edi+esi]			; eax�� �����迭�� ù ���� �ִ´�.
	dec ecx
	L1:
		cmp ecx, 0				; �����迭�� ����� ���ڰ� 1�����ٸ� L2�� �����Ѵ�.
		jle L2
		add esi, TYPE SDWORD	; �����迭�� �������� ����Ų��.
		add eax, [edi+esi]		; eax�� �� ���� ���Ѵ�.
	loop L1

L2:	
	cmp eax, 0
	jge unsigned_print			; eax(��)�� ������ unsigned_print�� �����Ѵ�.

	call WriteInt				; eax(��)�� ������� WriteInt�� ���� ����Ѵ�.
	call Crlf
	jmp quit

	unsigned_print:
		call WriteDec			; eax(��)�� ������ WriteDec�� ���� ����Ѵ�.
		call Crlf

	quit:

	ret
ArraySum ENDP

; ===================================


END main