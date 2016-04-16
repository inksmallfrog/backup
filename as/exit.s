	# 目的： 退出并向Linux内核返回一个值
	#
	
	# 输入： 无
	#

	# 输出： 返回一个状态码。
	#

	# 变量：
	#	%eax保存系统调用
	#	%ebx保存返回状态
	#
	.section .data
	.section .text
	.globl _start
_start:
	movl $1, %eax # 用于退出程序的Linux内核命令号（系统调用）
	movl $2, %ebx # 返回的状态码

