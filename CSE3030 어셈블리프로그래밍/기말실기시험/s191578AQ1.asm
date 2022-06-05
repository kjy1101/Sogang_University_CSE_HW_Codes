TITLE s191578AQ

INCLUDE Irvine32.inc
.data
BUF_SIZE EQU 24
inBuffer BYTE BUF_SIZE DUP(?)
inBufferN DWORD ?
end_idx DWORD ?
start_message BYTE "Enter a string : ", 0
goodbye_message BYTE "Bye!", 0

.code
main PROC
	L0:
	mov edx, OFFSET start_message
	call WriteString
	mov edx, OFFSET inBuffer	; inBuffer�� ���ڿ��� �Է¹ް� inBuffer�� OFFSET�� edx�� �ִ´�.(parameter passing)
	mov ecx, BUF_SIZE
	call ReadString

	call strlen					; inBuffer, �� �Է¹��� ���ڿ��� ���̸� strlen �Լ��� ���� ���Ѵ�.
	mov inBufferN, esi			; inBuffer�� ���̴� inBufferN�� �����Ѵ�.
	mov ecx, inBufferN			; inBuffer�� ���̸� ecx�� �����Ѵ�.(parameter passing)
	cmp ecx, 0
	je quit						; �Է��� ���ڿ��� ���̰� 0, �� ���͸� �������� quit���� �����Ѵ�.

	;�ϴ� ¦���� ��
	cmp inBufferN, 2
	jle H8
	mov ebx, 0
	H0:
		mov end_idx, ecx
		sub end_idx, ebx
		dec end_idx

;		mov eax, ebx
;		call WriteInt
;		mov eax, end_idx
;		call WriteInt
;		call Crlf
		
		mov esi, 0
	H3:
		cmp esi, ebx
		jl H1
		cmp esi, end_idx
		jg H1

		;�������
		mov eax, [edx+esi]
		call WriteChar
		jmp H2

		H1: ;��ĭ���
			mov eax, 0
			call WriteChar
		H2:

		
		inc esi
		cmp esi, end_idx
		jle H3
		call Crlf


		mov eax, end_idx
		sub eax, ebx
		cmp eax, 1
		jle increasing_step_

		inc ebx
		jmp H0
;//////////////////////////////////////////////////////////////////////////
		increasing_step_:
			dec ebx
		increasing_step:
			mov end_idx, ecx
			sub end_idx, ebx
			dec end_idx

;			mov eax, ebx
;			call WriteInt
;			mov eax, end_idx
;			call WriteInt
;			call Crlf
		
			mov esi, 0
		H4:
			cmp esi, ebx
			jl H5
			cmp esi, end_idx
			jg H5

			;�������
			mov eax, [edx+esi]
			call WriteChar
			jmp H6

			H5: ;��ĭ���
				mov eax, 0
				call WriteChar
			H6:

		
			inc esi
			cmp esi, end_idx
			jle H4
			call Crlf

			cmp ebx, 0
		;	jle L0
			jg H7
			call Crlf
			jmp L0
			H7:
			dec ebx
			jmp increasing_step
;//////////////////////////////////////////////////////////////////////////
	H8:
		call WriteString
		call Crlf
		call Crlf
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
END main