	.text
	.file	"simple-lock.c"
	.globl	lock
	.align	16, 0x90
	.type	lock,@function
lock:                                   # @lock
	.cfi_startproc
# BB#0:
	movl	lockvar(%rip), %ecx
	#APP
	movl	$0, %eax
.Ltmp0:
	lock
	cmpxchgl	%edi, lockvar(%rip)
	je	.Ltmp0
	#NO_APP
	retq
.Lfunc_end0:
	.size	lock, .Lfunc_end0-lock
	.cfi_endproc

	.globl	unlock
	.align	16, 0x90
	.type	unlock,@function
unlock:                                 # @unlock
	.cfi_startproc
# BB#0:
	pushq	%rax
.Ltmp1:
	.cfi_def_cfa_offset 16
	movl	%edi, %ecx
	movl	lockvar(%rip), %edx
	cmpl	%ecx, %edx
	je	.LBB1_2
# BB#1:
	movl	$.L.str, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	printf
.LBB1_2:
	movl	$0, lockvar(%rip)
	popq	%rax
	retq
.Lfunc_end1:
	.size	unlock, .Lfunc_end1-unlock
	.cfi_endproc

	.globl	incrementor
	.align	16, 0x90
	.type	incrementor,@function
incrementor:                            # @incrementor
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp2:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp3:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp4:
	.cfi_def_cfa_offset 32
.Ltmp5:
	.cfi_offset %rbx, -24
.Ltmp6:
	.cfi_offset %rbp, -16
	movl	(%rdi), %ebx
	movl	$1000000, %ebp          # imm = 0xF4240
	movl	lockvar(%rip), %ecx
	.align	16, 0x90
.LBB2_1:                                # =>This Inner Loop Header: Depth=1
	#APP
	movl	$0, %eax
.Ltmp7:
	lock
	cmpxchgl	%ebx, lockvar(%rip)
	je	.Ltmp7
	#NO_APP
	incl	counter(%rip)
	movl	lockvar(%rip), %edx
	cmpl	%ebx, %edx
	je	.LBB2_3
# BB#2:                                 #   in Loop: Header=BB2_1 Depth=1
	movl	$.L.str, %edi
	xorl	%eax, %eax
	movl	%ebx, %esi
	callq	printf
.LBB2_3:                                # %unlock.exit
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$0, lockvar(%rip)
	xorl	%ecx, %ecx
	decl	%ebp
	jne	.LBB2_1
# BB#4:
	xorl	%eax, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end2:
	.size	incrementor, .Lfunc_end2-incrementor
	.cfi_endproc

	.globl	create_thread
	.align	16, 0x90
	.type	create_thread,@function
create_thread:                          # @create_thread
	.cfi_startproc
# BB#0:
	pushq	%rax
.Ltmp8:
	.cfi_def_cfa_offset 16
	movq	%rsi, %rax
	incl	threads(%rip)
	xorl	%esi, %esi
	movl	$threads, %ecx
	movq	%rax, %rdx
	callq	pthread_create
	testl	%eax, %eax
	jne	.LBB3_2
# BB#1:
	popq	%rax
	retq
.LBB3_2:
	movl	$1, %edi
	callq	exit
.Lfunc_end3:
	.size	create_thread, .Lfunc_end3-create_thread
	.cfi_endproc

	.globl	join_thread
	.align	16, 0x90
	.type	join_thread,@function
join_thread:                            # @join_thread
	.cfi_startproc
# BB#0:
	pushq	%rax
.Ltmp9:
	.cfi_def_cfa_offset 16
	movq	(%rdi), %rdi
	xorl	%esi, %esi
	callq	pthread_join
	testl	%eax, %eax
	jne	.LBB4_2
# BB#1:
	popq	%rax
	retq
.LBB4_2:
	movl	$2, %edi
	callq	exit
.Lfunc_end4:
	.size	join_thread, .Lfunc_end4-join_thread
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	subq	$24, %rsp
.Ltmp10:
	.cfi_def_cfa_offset 32
	incl	threads(%rip)
	leaq	16(%rsp), %rdi
	xorl	%esi, %esi
	movl	$incrementor, %edx
	movl	$threads, %ecx
	callq	pthread_create
	testl	%eax, %eax
	jne	.LBB5_5
# BB#1:                                 # %create_thread.exit
	incl	threads(%rip)
	leaq	8(%rsp), %rdi
	xorl	%esi, %esi
	movl	$incrementor, %edx
	movl	$threads, %ecx
	callq	pthread_create
	testl	%eax, %eax
	jne	.LBB5_5
# BB#2:                                 # %create_thread.exit1
	movq	16(%rsp), %rdi
	xorl	%esi, %esi
	callq	pthread_join
	testl	%eax, %eax
	jne	.LBB5_6
# BB#3:                                 # %join_thread.exit
	movq	8(%rsp), %rdi
	xorl	%esi, %esi
	callq	pthread_join
	testl	%eax, %eax
	jne	.LBB5_6
# BB#4:                                 # %join_thread.exit2
	movl	counter(%rip), %esi
	movl	$.L.str.1, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	addq	$24, %rsp
	retq
.LBB5_5:
	movl	$1, %edi
	callq	exit
.LBB5_6:
	movl	$2, %edi
	callq	exit
.Lfunc_end5:
	.size	main, .Lfunc_end5-main
	.cfi_endproc

	.type	threads,@object         # @threads
	.bss
	.globl	threads
	.align	4
threads:
	.long	0                       # 0x0
	.size	threads, 4

	.type	counter,@object         # @counter
	.globl	counter
	.align	4
counter:
	.long	0                       # 0x0
	.size	counter, 4

	.type	lockvar,@object         # @lockvar
	.globl	lockvar
	.align	4
lockvar:
	.long	0                       # 0x0
	.size	lockvar, 4

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"WTF! Am %i but found %i!\n"
	.size	.L.str, 26

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"Counter: %i\n"
	.size	.L.str.1, 13


	.ident	"clang version 3.7.1 (tags/RELEASE_371/final)"
	.section	".note.GNU-stack","",@progbits
