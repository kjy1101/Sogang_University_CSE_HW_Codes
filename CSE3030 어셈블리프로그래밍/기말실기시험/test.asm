INCLUDE Irvine32.inc
.data

.code
main PROC
	mov rax, 0FFFF0000FFFF0000h
	mov rbx, 2
	mul rbx

	exit
main ENDP


END main