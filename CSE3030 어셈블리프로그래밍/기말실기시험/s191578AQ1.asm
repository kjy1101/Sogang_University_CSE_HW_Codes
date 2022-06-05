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
	mov edx, OFFSET inBuffer	; inBuffer에 문자열을 입력받고 inBuffer의 OFFSET을 edx에 넣는다.(parameter passing)
	mov ecx, BUF_SIZE
	call ReadString

	call strlen					; inBuffer, 즉 입력받은 문자열의 길이를 strlen 함수를 통해 구한다.
	mov inBufferN, esi			; inBuffer의 길이는 inBufferN에 저장한다.
	mov ecx, inBufferN			; inBuffer의 길이를 ecx에 저장한다.(parameter passing)
	cmp ecx, 0
	je quit						; 입력한 문자열의 길이가 0, 즉 엔터만 눌렀으면 quit으로 점프한다.

	;일단 짝수일 때
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

		;문자출력
		mov eax, [edx+esi]
		call WriteChar
		jmp H2

		H1: ;빈칸출력
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

			;문자출력
			mov eax, [edx+esi]
			call WriteChar
			jmp H6

			H5: ;빈칸출력
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
END main