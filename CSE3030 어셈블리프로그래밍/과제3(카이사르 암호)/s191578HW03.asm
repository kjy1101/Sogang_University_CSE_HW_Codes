TITLE s191578HW03, Caesar cipher

; Program Description: Caesar Cipher
; List has additory elements(0123456789"012") according to key value
; i is index of Cipher_Str(range: 0~Num_Str*10)
; make Cipher_Str[i] to constant, subtract key value, plus List size(in this program, 10, and call it List_index)
; find List[List_index] and put it in Cipher_Str[i] to use less memory(no additory variable)
; if all DeCipher over, write to file

; Author: Kim Jae Yeon
; Creation Date: 2020. 5. 15
; function: make Cipher strings to Decipher strings
; input: Number of Cipher string, Cipher strings
; output: Decipher strings matched to each Cipher strings

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW03.inc

.data
List BYTE "0123456789012", 0		; List size is 10, not 13
key BYTE 7
filename BYTE "0s191578_out.txt", 0
filehandle handle ?
MY_CRLF BYTE 13, 10

.code
main PROC

	mov ecx, Num_Str			; Decipher process is repeated Num_Str
	mov esi, 0					; n th string starting index(esi) = 10*(n-1)
L2:
	push ecx
	mov ecx, 9					; Cipher_Str's length is 9(fixed)
L1:
	movzx eax, Cipher_Str[esi]	; make character Cipher_Str[esi] to constant value by subtract "0"
	sub eax, "0"
	movzx ebx, key				; subtract key value
	sub eax, ebx
	add eax, 10					; add 10(List size, fixed)
	push esi					; store Cipher_Str's index
	mov esi, eax				; now esi has List's index
	movzx eax, List[esi]		; eax has 'List_index'th value in List
	pop esi
	mov Cipher_Str[esi], al		; Cipher_Str[Cipher_Str index] is changed to List[List index]
	inc esi						; to point next character of Cipher_Str
loop L1
	pop ecx
	inc esi						; end of string is 0, so jump 1 index
loop L2

	mov edx, OFFSET filename	; file open
	call CreateOutputFile
	mov filehandle, eax

	mov ecx, Num_Str			; write process is repeated Num_Str
	mov ebx, 0
L3:
	mov eax, filehandle
	push ecx
	mov edx, OFFSET Cipher_Str
	mov ecx, LENGTHOF Cipher_Str	; ecx contains end of string(0)
	dec ecx							; so subtract 1
	add edx, ebx					; it will write from Cipher_Str[ebx]
	call WriteToFile

	mov eax, filehandle
	mov edx, OFFSET MY_CRLF			; write enter
	mov ecx, 2
	call WriteToFile

	mov eax, filehandle
	mov edx, OFFSET MY_CRLF			; write enter
	mov ecx, 2
	call WriteToFile

	add ebx, 10						; to point next string starting index
	pop ecx
loop L3

	mov eax, filehandle			; close file
	call CloseFile

main ENDP
END main