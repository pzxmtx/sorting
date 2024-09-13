#
# Sorting algorithm using Shell method
#
.globl _shell			# make shell() function visible to client code

.data
index: .long 0			# Index of currently chosen step size
	
.section .rodata		
step:				# Step sizes used in sort. The sizes 
				# can be different, but the last one 
				# should always be 1.
	.long 7, 3, 2, 1

.text
#
# Sorting algorithm.
#
# SYNOPSIS:
# 	void shell_asm(long* v, long n)
#
# Options are:
#	RDI - the head of array to sort
#	RSI - the number of elements to be sorted
#	
#
_shell:
	lea step(%rip), %rax	# RAX = &step
	movq %rax, -16(%rsp)	# push the step sizes into stack


step_loop:			# outer loop: iterate over step sizes
	movl -16(%rsp), %eax	# RAX = address of the next step size 
	movl (%eax), %eax	# RAX = step size
	cmpq %rax, %rsi		# step size bigger than array size?..
	jb is_last_step		# ...yes, go to the next size
	movl %eax, %ecx		# ECX = starting position within array
	
	# Iterate over array from position RCX to  position in RSI 
array_loop:
	cmpq %rcx, %rsi		# aren't we reach the end of array?..
	je is_last_step		# ... we're, so chose the next step size

	# Comparision and exchange loop.
	#
	# From the position stored in RCX, take the value of a 
	# starting element and compare it with a previous one.
	# Previous element is at position RCX - step size.
	# If previous element is greater than starting, do exchange
	# and proceed further, to the beginning of array.
	# Otherwise, this loop is finished and we go the next 
	# element (RCX + 1)

	movq (%rdi, %rcx, 8), %rbx	# RBX = current value
	movq %rcx, %rdx			# RDX = RCX (current position)
	movq %rdx, %r9			# R9  = RDX (previous position to be held there)
compare_loop:
	subq %rax, %r9			# R9 = R9 - RAX (R9 - step size) 
	cmpq %r9, %rdx				
	jb continue_array_loop		# backward loop finished, 
					# go to the next value		
	# RBX - element to compare
	# RDX - current index
	# R9  - previous index
	# 
	# Compare RBX and R9.
	# If R9 > RBX, do exchange
	# Otherwise, go to the next value 
	movq (%rdi, %r9, 8), %r10
	cmpq %r10, %rbx
	ja continue_array_loop

	# Do exchange and update the indexes towards the head of array
	movq %r10, (%rdi, %rdx, 8)
	movq %rbx, (%rdi, %r9, 8)
	subq %rax, %rdx
	jmp compare_loop

continue_array_loop:
	incq %rcx		# proceed with the next element
	jmp array_loop		


is_last_step:
	movq $1, %r8
	cmpq %rax, %r8		# is this the last step size (1)?..
	je alldone		# ... yes, it is. We are done.

	movq -16(%rsp), %rax	# RDI = &step
	addq $4, %rax		# choose the next step size
	movq %rax, -16(%rsp)	# push updated pointer back to the stack
	jmp step_loop		# continue sorting with the next step size

alldone:	
	ret

.end
