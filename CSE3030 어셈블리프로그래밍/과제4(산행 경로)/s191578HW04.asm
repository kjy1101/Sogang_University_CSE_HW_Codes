TITLE s191578HW04

; Program Description: update highest and lowest in downhill, and calculated greatest difference in uphill or flat section
; Author: Kim Jae Yeon
; Creation Date: 2020. 5. 24
; function: find the height of the downhill which has the greatest altitude difference
; input: number of test, (list size, heights measured) * number of test
; output: greatest difference among downhills

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW04.inc

.data
highest DWORD 0		;�������� �ְ���
lowest DWORD 0		;�������� ������

.code
main PROC
	
	mov ecx, TN
TEST_CASE:
	push ecx
	cmp ecx, 0		;���� ó���� ���� ecx�� 0�̸� �����Ѵ�.
	je quit

	cmp ecx, TN
	je put_Case
	jne put_Height

	put_Case:					;ù��° test case�� ���� ecx�� CASE�� �ִ´�.
		mov ecx, CASE
		mov esi, 0
		sub ecx, 1				;���������� ���� ���� ���̹Ƿ� 1�� ����.
		mov edx, 0				;edx���� �ְ�������̸� ���� ���̰�, ���� ���꿡���� �񱳸� ���� 0���� �ʱ�ȭ�Ѵ�.
		jmp L1

	put_Height:					;�ι�° �̻��� test case�� ���� HEIGHT�� �ִ� ���� �־�� �Ѵ�.
		mov ecx, HEIGHT[esi+4]
		add esi, 8				;���δ� ���� esi�����κ��� �� ĭ(8) �ڿ��� �����Ѵ�.
		sub ecx, 1
		mov edx, 0

	L1:							;main loop
		cmp ecx, 0				;���� ó���� ���� ecx�� 0�̸� quit_print�� �����Ѵ�.
		je quit_print
		mov eax, HEIGHT[esi]	;HEIGHT[esi]�� ���� ������� ��������, '���簪'�̶�� �θ���.
		cmp eax, HEIGHT[esi+4]
		jg downhill				;���簪>������(������)
		jle uphill				;���簪<=������(������ or ����)
	loop L1
	jmp quit_print				;���� �ϳ��� ������ ��� ������ ������� ����Ѵ�.

loop TEST_CASE
	jmp quit					;��� ���θ� ��������� ���α׷��� �����Ѵ�.


	downhill:					;������
		cmp eax, highest
		jg update_highest		;���簪�� ���������� �ְ������� ũ�� �ְ����� ���簪���� �����Ѵ�.
		mov ebx, HEIGHT[esi+4]
		mov lowest, ebx			;���������� �������� ����.
		add esi, 4				;�ٽ� L1���� ���ư��� ���� esi, ecx���� �����Ѵ�.
		dec ecx
		cmp ecx, 0
		je uphill2				;ecx�� 0�̶�� uphill2�� �����Ѵ�.(L1���� ���ư��� ����)
		jmp L1


	update_highest:
			mov highest, eax	;�ְ����� ���簪�� �ְ� �ٽ� downhill�� ���ư���.
			jmp downhill
	

	uphill:						;������ or ����
		mov ebx, highest		;���� ������� �������� ��������(highest-lowest)�� ���Ѵ�.
		sub ebx, lowest
		cmp ebx, edx
		jg update_height		;������ �������̰� ������ �ִ�������̺��� ũ�� �ִ���̸� ���� �������̷� �����Ѵ�.
		mov highest, 0			;���� ������ ������ ���� highest�� lowest�� 0���� �ʱ�ȭ�Ѵ�.
		mov lowest, 0
		add esi, 4				;L1���� ���ư��� ���� esi�� ecx���� �����Ѵ�.
		dec ecx
		jmp L1


	update_height:
			mov edx, ebx		;�ִ��������(edx)�� ���� �������̸� �ְ� �ٽ� uphill�� ���ư���.
			jmp uphill


	uphill2:
		mov ebx, highest		;���� ������� �������� ��������(highest-lowest)�� ���Ѵ�.
		sub ebx, lowest
		cmp ebx, edx
		jg update_height2		;������ �������̰� ������ �ִ�������̺��� ũ�� �ִ���̸� ���� �������̷� �����Ѵ�.
		mov highest, 0			;highest�� lowest�� 0���� �ʱ�ȭ�ϰ� L1���� ���ư���.
		mov lowest, 0
		jmp L1

	update_height2:
		mov edx, ebx			;�ִ��������(edx)�� ���� �������̸� �ְ� �ٽ� uphill2�� ���ư���.
		jmp uphill2
		

	quit_print:					;���� �ϳ��� ������ ��� ���� �� ������� ����Ѵ�.
		pop ecx					;TEST_CASE�� ���� ecx���� �ҷ��´�.
		dec ecx
		mov eax, edx
		call WriteDec			;edx�� �ִ� ���� eax�� �Űܼ� ����Ѵ�.
		call Crlf
		call Crlf
		jmp TEST_CASE

	quit:						;���� ����

	exit
main ENDP
END main