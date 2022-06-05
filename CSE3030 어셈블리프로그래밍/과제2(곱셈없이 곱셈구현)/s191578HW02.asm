TITLE s191578HW02.asm

; Program Description: calculate 38*x1 + 47*x2 + 19*x3
; Author: Kim Jae Yeon
; Creation Date: 2020.05.01
; input: x1, x2, x3
; output: 38*x1 + 47*x2 + 19*x3

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW02.inc

.code
main PROC

	;38 * x1, 38 = 2^5 + 2^2 + 2^1
	;1. calculate (2^5)*x1
	mov eax, x1
	add eax, eax
	add eax, eax
	add eax, eax
	add eax, eax
	add eax, eax	; in eax, there is (2^5)*x1

	;2. calculate (2^2)*x1
	mov ebx, x1
	add ebx, ebx
	add ebx, ebx	; in ebx, there is (2^2)*x1

	add eax, ebx	; in eax, there is (2^5)*x1 + (2^2)*x1
	
	;3. calculate (2^1)*x1
	mov ebx, x1
	add ebx, ebx	; in ebx, there is (2^1)*x1

	add eax, ebx	; in eax, there is (2^5)*x1 + (2^2)*x1 + (2^1)*x1.
	;As a result, there is 38*x1 in eax.


	;47 * x2, 47 = 2^5 + 2^3 + 2^2 + 2^1 + 2^0
	;1. calculate (2^5)*x2
	mov ebx, x2
	add ebx, ebx
	add ebx, ebx
	add ebx, ebx
	add ebx, ebx
	add ebx, ebx	; in ebx, there is (2^5)*x2

	add eax, ebx	; in eax, there is 38*x1 + (2^5)*x2

	;2. calculate (2^3)*x2
	mov ebx, x2
	add ebx, ebx
	add ebx, ebx
	add ebx, ebx	; in ebx, there is (2^3)*x2

	add eax, ebx	; in eax, there is 38*x1 + (2^5)*x2 + (2^3)*x2

	;3. calculate (2^2)*x2
	mov ebx, x2
	add ebx, ebx
	add ebx, ebx	; in ebx, there is (2^2)*x2

	add eax, ebx	; in eax, there is 38*x1 + (2^5)*x2 + (2^3)*x2 + (2^2)*x2

	;4. calculate (2^1)*x2
	mov ebx, x2
	add ebx, ebx	; in ebx, there is (2^1)*x2

	add eax, ebx	; in eax, there is 38*x1 + (2^5)*x2 + (2^3)*x2 + (2^2)*x2 + (2^1)*x2

	;5. calculate (2^0)*x2
	mov ebx, x2		; in ebx, there is (2^0)*x2

	add eax, ebx	; in eax, there is 38*x1 + (2^5)*x2 + (2^3)*x2 + (2^2)*x2 + (2^1)*x2 + (2^0)*x2
	;As a result, there is 38*x1 + 47*x2 in eax.


	;19 * x3, 19 = 2^4 + 2^1 + 2^0
	;1. calculate (2^4)*x3
	mov ebx, x3
	add ebx, ebx
	add ebx, ebx
	add ebx, ebx
	add ebx, ebx	; in ebx, there is (2^4)*x3

	add eax, ebx	; in eax, there is 38*x1 + 47*x2 + (2^4)*x3

	;2. calculate (2^1)*x3
	mov ebx, x3
	add ebx, ebx	; in ebx, there is (2^1)*x3

	add eax, ebx	; in eax, there is 38*x1 + 47*x2 + (2^4)*x3 + (2^1)*x3

	;3. calculate (2^0)*x3
	mov ebx, x3		; in ebx, there is (2^0)*x3

	add eax, ebx	; in eax, there is 38*x1 + 47*x2 + (2^4)*x3 + (2^1)*x3 + (2^0)*x3
	;As a result, there is 38*x1 + 47*x2 + 19*x3 in eax.

	call WriteInt	; print value of eax

	exit
main ENDP
END main