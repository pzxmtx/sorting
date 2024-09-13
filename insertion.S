#
# Sorting algorithm using insertion method
#
.globl _insertion

.data
step:				# start counting from the next one, so 1
	.quad 1			# 

i:				# backward counter
	.quad step


.text

#
# SYNOPSIS:
# void _insertion(long* v, long n)
# 
# RDI = v
# RSI = n
#
_insertion:
	movq %rsi, -8(%rsp)	# push the number of elements on to stack
	
	lea step(%rip), %rcx	# RCX = &step
	movq %rcx, -16(%rsp)	

	lea i(%rip), %rdx	# RDX = &i
	movq %rdx, -24(%rsp)	


next:				# outer loop
	movq -16(%rsp), %rdx	# find out step's address
	movq (%rdx), %rdx	# and put the step value to RDX

	cmpq %rdx, %rsi		# check if we've already reached the end of array
	je alldone

	movq %rdx, %rsi		# begin with step
	
compare:			# inner loop, compare 

	# Use index register RSI to iterate over array backwards
	# RDX holds a current position within the array, and we start
	# from there. 
	# 
	# On each iteration, compare (%RAX, %RSI) and (%RAX, %RSI-1)
	#
	# Inner loop terminates (jumps to outer loop) if:
	# - (%RAX, %RSI) > (%RAX, %RSI-1), or ...
	# - RSI = 0, i.e., start of array has been reached.

	movq (%rdi, %rsi, 8), %rbx 	# RBX - value to compare
	decq %rsi			# shift RSI to a previous element
	movq (%rdi, %rsi, 8), %rcx 	# RCX - previous value
	cmpq %rcx, %rbx			# do comparision ... 
	jg loop				#    previous < current -> go to outer loop
	movq %rbx, (%rdi, %rsi, 8) 	# RSI-1 = RBX
	incq %rsi
	movq %rcx, (%rdi, %rsi, 8)	# RSI = RCX
	decq %rsi			# RSI = RSI - 1
	xor %rcx, %rcx			# RCX = 0		
	cmpq %rsi, %rcx			# if RSI == 0 ...
	je loop				#    ... head of array reached -> go to outer loop
	jmp compare			#    ... inner loop continues, otherwise

loop:
	movq -16(%rsp), %rdx	# RDX = &step
	incq (%rdx)		# RDX = &(step + 1)
	movq -8(%rsp), %rcx	# RCX = count
	movq (%rdx), %rdx	# RDX = step
	cmpq %rdx, %rcx
	je alldone		# end of array reached

	movq -24(%rsp), %rcx	# RDX = &i
	movq %rdx, (%rcx)	# i = step ; -24(%%rsp) = &i

	jmp next		# back to main loop

alldone:	
	ret
.end
