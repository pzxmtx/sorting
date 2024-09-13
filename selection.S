#
# Sorting algorithm using selection method
#
.globl _selection

.text
#
# SYNOPSIS:
# void _selection(long* v, long n)
# 
# RDI = v
# RSI = n
#
_selection:
	# Initial set up

	xorq %rcx, %rcx			# RCX = 0
	movq $1, %rdx			# RDX = 1
	
next:				# outer loop; iterate over array
	cmpq %rdx, %rsi		# check if we've already reached the end of array
	je alldone
	movq (%rdi, %rdx, 8), %r8	# R8 = v[rdx]
	
lookup:				# inner loop; search for a smallest value in
				# the range RCX+1 .. RSI-1
				# At the end, R8 will contain a smallest value
	cmpq %rdx, %rsi
	je compare
	movq (%rdi, %rdx, 8), %rax
	cmpq %rax, %r8
	jb another
	xchgq %r8, %rax		# R8  - updated smallest value
	movq %rdx, %rbx		# RBX - updated position of smallest value
another:
	incq %rdx
	jmp lookup
	
compare:		
	movq (%rdi, %rcx, 8), %rax
	cmpq %rax, %r8
	ja continue			# R8 > RAX, so no change and continue
	movq %rax, (%rdi, %rbx, 8)	# R8 < RAX, so exchange them
	movq %r8, (%rdi, %rcx, 8)	
	
continue:			# continue outer loop
	incq %rcx
	movq %rcx, %rdx
	incq %rdx
	jmp next
	

alldone:	
	ret
.end
