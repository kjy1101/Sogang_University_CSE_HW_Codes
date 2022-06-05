INCLUDE Irvine32.inc

.data
start_message BYTE "Enter Capacity : ", 0

.code
main PROC
	mov edx, OFFSET start_message
	call WriteString

	exit
main ENDP
END main