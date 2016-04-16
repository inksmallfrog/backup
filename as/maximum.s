	# 目的： 本程序寻找一组数据项中的最大值
	#
	# 变量： 寄存器有以下用途：
	#
	# %edi - 保存正在检测的数据项索引
	# %ebx - 当前已经找到的最大数据项
	# %eax - 当前数据项
	#
	# 使用以下内存位置：
	#
	# data_items - 包含数据项
	#		0表示数据项结束
	#

	.section .data
data_items:
	.long 10, 20, 13, 4, 9, 8, 1, 48, 23, 0

	.section .text
	.globl _start
_start:
	movl $0, %edi
	movl $65535, %ebx
loop_start:
	movl data_items(, %edi, 4), %eax
	incl %edi
	cmpl $0, %eax
	je loop_end
	cmpl %eax, %ebx
	jle loop_start
	movl %eax, %ebx
	jmp loop_start
loop_end:
	movl $1, %eax
	int $0x80
