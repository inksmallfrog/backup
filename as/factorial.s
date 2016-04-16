	# PURPOSE: This program call a function to calculate
	# 	   the factorial of the given number
	#
	# FUNCTIONS: _start factorial
	#
	# PROGRESS: 4!
	#
	.section .data

	.section .text

	# FUNCTION_NAME: _start
	#
	# PURPOSE: the entry point of the program
	#
	# RETURN: %rbx - return code(the result)
	#
	# PARAMETERS: none
	#
	# VARIABLES: %rax - store the result of function factorial
	#		    store the syscall code
	#	     %rbx - store the result as return code
	#
	.globl _start
_start:
	pushq $4
	call factorial
	addq $8, %rsp
	movq %rax, %rbx
	movq $1, %rax
	int $0x80

	# FUNCTION_NAME: factorial
	#
	# PURPOSE: calculate the factoirla of the given number
	#
	# RETURN: %rax - the result of the factorial
	#
	# PARAMETERS: 1 - the given number n
	#
	# VARIAB     %rax - temporily store number n - 1
	#		    temporily store factorial of n-1
	#		    store result
	# 	     %rbx - temporily store number n
	#
	.type factorial, @function
factorial:
	pushq %rbp
	movq %rsp, %rbp
	movq 16(%rbp), %rax
	subq $8, %rsp
	cmpq $1, %rax
	je factorial_directly_return
	decq %rax
	pushq %rax
	call factorial
	addq $8, %rsp
	movq 16(%rbp), %rbx
	imulq %rbx, %rax
	movq %rbp, %rsp
	popq %rbp
	ret

factorial_directly_return:
	movq %rbp, %rsp
	popq %rbp
	ret
