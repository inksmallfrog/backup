	# PURPOSE: Learning to call function with as
	#
	# FUNCTIONS: _start power
	#
	# PROCESS: 5^2 + 2^2 - 3^2
	#
	# PLATFORM: Linux x86-64
	#
	.section .data

	.section .text

	# FUNCTION_NAME: _start
	#
	# PARAMETERS: none
	#
	# RETURN: %rbx - return code
	#
	# VARIABLES: %rax - tempory operator
	#		    system call code
	#	     %rbx - tempory operator
	#		    return code(result)
	#
	.globl _start
_start:
	pushq $5
	pushq $2
	call power
	addq $16, %rsp
	movq %rax, %rbx
	pushq %rax
	pushq $2
	pushq $2
	call power
	addq $16, %rsp
	pushq %rax
	pushq $3
	pushq $2
	call power
	addq $16, %rsp
	popq %rbx
	addq (%rsp), %rbx
	subq %rax, %rbx
	movq $1, %rax
	int $0x80

	# FUNCTION_NAME: power
	#
	# PARAMETERS: 1 - base number
	#	      2 - power number
	#
	# RETURN: %rax - result of the power
	#
	# VARIABLES: %rax - result
	#	     %rbx - base number
	#	     %rdi - count
	#
	.type power, @function
power:
	pushq %rbp
	movq %rsp, %rbp
	movq $1, %rax
	movq 16(%rbp), %rdi
	movq 24(%rbp), %rbx
	
power_loop_start:
	cmpq $0, %rdi
	je power_loop_end
	imulq %rbx, %rax
	decq %rdi
	jmp power_loop_start

power_loop_end:
	movq %rbp, %rsp
	popq %rbp
	ret
