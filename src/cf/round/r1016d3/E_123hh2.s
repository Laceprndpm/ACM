	.file	"E_123hh2.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
	.p2align 4
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB4999:
	.cfi_startproc
	endbr64
	movl	%esi, %eax
	ret
	.cfi_endproc
.LFE4999:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.text
	.align 2
	.p2align 4
	.type	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE24_M_get_insert_unique_posERS1_.isra.0, @function
_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE24_M_get_insert_unique_posERS1_.isra.0:
.LFB11798:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	16(%rdi), %rbx
	testq	%rbx, %rbx
	jne	.L4
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L10:
	movq	%rax, %rbx
.L4:
	movq	32(%rbx), %rdx
	movq	24(%rbx), %rax
	cmpq	%rbp, %rdx
	cmovg	16(%rbx), %rax
	setg	%cl
	testq	%rax, %rax
	jne	.L10
	movq	%rbx, %rsi
	testb	%cl, %cl
	jne	.L5
.L7:
	xorl	%eax, %eax
	cmpq	%rdx, %rbp
	cmovle	%rax, %rsi
	cmovg	%rax, %rbx
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbx, %rax
	movq	%rsi, %rdx
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	.cfi_restore_state
	leaq	8(%rdi), %rbx
.L5:
	cmpq	%rbx, 24(%rdi)
	je	.L12
	movq	%rbx, %rdi
	call	_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base@PLT
	movq	%rbx, %rsi
	movq	32(%rax), %rdx
	movq	%rax, %rbx
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L12:
	movq	%rbx, %rsi
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	xorl	%ebx, %ebx
	movq	%rbx, %rax
	movq	%rsi, %rdx
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11798:
	.size	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE24_M_get_insert_unique_posERS1_.isra.0, .-_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE24_M_get_insert_unique_posERS1_.isra.0
	.align 2
	.p2align 4
	.type	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0, @function
_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0:
.LFB11799:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%rdi, 16(%rsp)
	testq	%rdi, %rdi
	je	.L18
.L36:
	movq	16(%rsp), %rax
	movq	24(%rax), %rax
	movq	%rax, 8(%rsp)
	testq	%rax, %rax
	je	.L20
.L35:
	movq	8(%rsp), %rax
	movq	24(%rax), %r14
	testq	%r14, %r14
	je	.L21
.L34:
	movq	24(%r14), %r15
	testq	%r15, %r15
	je	.L22
.L33:
	movq	24(%r15), %rbx
	testq	%rbx, %rbx
	je	.L23
.L32:
	movq	24(%rbx), %r12
	testq	%r12, %r12
	je	.L24
.L31:
	movq	24(%r12), %rbp
	testq	%rbp, %rbp
	je	.L25
.L30:
	movq	24(%rbp), %rdx
	testq	%rdx, %rdx
	je	.L26
.L29:
	movq	24(%rdx), %r13
	testq	%r13, %r13
	je	.L27
.L28:
	movq	24(%r13), %rdi
	movq	%rdx, 24(%rsp)
	call	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	movq	%r13, %rdi
	movq	16(%r13), %r13
	movl	$48, %esi
	call	_ZdlPvm@PLT
	movq	24(%rsp), %rdx
	testq	%r13, %r13
	jne	.L28
.L27:
	movq	16(%rdx), %r13
	movl	$48, %esi
	movq	%rdx, %rdi
	call	_ZdlPvm@PLT
	testq	%r13, %r13
	je	.L26
	movq	%r13, %rdx
	jmp	.L29
.L24:
	movq	16(%rbx), %rbp
	movl	$48, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	testq	%rbp, %rbp
	je	.L23
	movq	%rbp, %rbx
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L25:
	movq	16(%r12), %rbp
	movl	$48, %esi
	movq	%r12, %rdi
	call	_ZdlPvm@PLT
	testq	%rbp, %rbp
	je	.L24
	movq	%rbp, %r12
	jmp	.L31
.L23:
	movq	16(%r15), %rbx
	movl	$48, %esi
	movq	%r15, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L22
	movq	%rbx, %r15
	jmp	.L33
	.p2align 4,,10
	.p2align 3
.L26:
	movq	16(%rbp), %rdx
	movl	$48, %esi
	movq	%rbp, %rdi
	movq	%rdx, 24(%rsp)
	call	_ZdlPvm@PLT
	movq	24(%rsp), %rdx
	testq	%rdx, %rdx
	je	.L25
	movq	%rdx, %rbp
	jmp	.L30
.L22:
	movq	16(%r14), %rbx
	movl	$48, %esi
	movq	%r14, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L21
	movq	%rbx, %r14
	jmp	.L34
.L21:
	movq	8(%rsp), %rdi
	movl	$48, %esi
	movq	16(%rdi), %rbx
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L20
	movq	%rbx, 8(%rsp)
	jmp	.L35
.L20:
	movq	16(%rsp), %rdi
	movl	$48, %esi
	movq	16(%rdi), %rbx
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L18
	movq	%rbx, 16(%rsp)
	jmp	.L36
.L18:
	addq	$40, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11799:
	.size	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0, .-_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4
	.globl	_Z5judgex
	.type	_Z5judgex, @function
_Z5judgex:
.LFB9883:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA9883
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$104, %rsp
	.cfi_def_cfa_offset 160
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
	leaq	40(%rsp), %r13
	cmpq	$0, n(%rip)
	movl	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movq	%r13, 56(%rsp)
	movq	%r13, 64(%rsp)
	movq	$0, 72(%rsp)
	jle	.L75
	leaq	32(%rsp), %rax
	movq	%rdi, %r12
	xorl	%r15d, %r15d
	movl	$1, %ebx
	movq	$0, 8(%rsp)
	leaq	awa(%rip), %r14
	movq	%rax, 16(%rsp)
	jmp	.L96
	.p2align 4,,10
	.p2align 3
.L125:
	movq	72(%rsp), %rax
.L77:
	cmpq	%rax, %r12
	je	.L123
.L82:
	addq	$1, %rbx
	cmpq	%rbx, n(%rip)
	jl	.L124
.L96:
	movq	(%r14,%rbx,8), %rcx
	cmpq	%r12, %rcx
	jge	.L125
	testq	%r15, %r15
	je	.L103
	movq	%r15, %rax
	movq	%r13, %rbp
	jmp	.L80
	.p2align 4,,10
	.p2align 3
.L127:
	movq	%rdi, %rax
	testq	%rax, %rax
	je	.L126
.L80:
	movq	16(%rax), %rsi
	movq	24(%rax), %rdi
	cmpq	32(%rax), %rcx
	jg	.L127
	movq	%rax, %rbp
	movq	%rsi, %rax
	testq	%rax, %rax
	jne	.L80
.L126:
	cmpq	%r13, %rbp
	je	.L78
	cmpq	32(%rbp), %rcx
	jl	.L78
	movq	72(%rsp), %rax
	movb	$1, 40(%rbp)
	cmpq	%rax, %r12
	jne	.L82
	.p2align 4,,10
	.p2align 3
.L94:
	movq	24(%r15), %rdi
	call	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	movq	%r15, %rdi
	movl	$48, %esi
	movq	16(%r15), %r15
	call	_ZdlPvm@PLT
.L123:
	testq	%r15, %r15
	jne	.L94
	addq	$1, 8(%rsp)
	xorl	%r15d, %r15d
	addq	$1, %rbx
	cmpq	%rbx, n(%rip)
	movq	$0, 48(%rsp)
	movq	%r13, 56(%rsp)
	movq	%r13, 64(%rsp)
	movq	$0, 72(%rsp)
	jge	.L96
.L124:
	movq	8(%rsp), %rax
	cmpq	%rax, k(%rip)
	setle	%bl
	testq	%r15, %r15
	je	.L74
.L98:
	movq	24(%r15), %rdi
	call	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	movq	%r15, %rdi
	movq	16(%r15), %r15
	movl	$48, %esi
	call	_ZdlPvm@PLT
	testq	%r15, %r15
	jne	.L98
.L74:
	movq	88(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L128
	addq	$104, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L103:
	.cfi_restore_state
	movq	%r13, %rbp
	.p2align 4,,10
	.p2align 3
.L78:
	movl	$48, %edi
.LEHB0:
	call	_Znwm@PLT
.LEHE0:
	movq	(%r14,%rbx,8), %rcx
	movb	$0, 40(%rax)
	movq	%rax, %r15
	movq	%rcx, 32(%rax)
	cmpq	%r13, %rbp
	je	.L129
	cmpq	32(%rbp), %rcx
	jge	.L87
	movq	%rcx, 24(%rsp)
	cmpq	%rbp, 56(%rsp)
	je	.L109
	movq	%rbp, %rdi
	call	_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base@PLT
	movq	24(%rsp), %rcx
	cmpq	32(%rax), %rcx
	jg	.L130
.L92:
	movq	16(%rsp), %rdi
	movq	%rcx, %rsi
	movq	%rcx, 24(%rsp)
	call	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE24_M_get_insert_unique_posERS1_.isra.0
	movq	24(%rsp), %rcx
	movq	%rax, %rbp
	testq	%rdx, %rdx
	jne	.L131
.L90:
	movl	$48, %esi
	movq	%r15, %rdi
	call	_ZdlPvm@PLT
	movq	72(%rsp), %rax
.L93:
	movb	$1, 40(%rbp)
	movq	48(%rsp), %r15
	jmp	.L77
	.p2align 4,,10
	.p2align 3
.L87:
	jle	.L90
	cmpq	%rbp, 64(%rsp)
	je	.L91
	movq	%rbp, %rdi
	movq	%rcx, 24(%rsp)
	call	_ZSt18_Rb_tree_incrementPSt18_Rb_tree_node_base@PLT
	movq	24(%rsp), %rcx
	cmpq	32(%rax), %rcx
	jge	.L92
	cmpq	$0, 24(%rbp)
	je	.L91
	movq	%rax, %rbp
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L85:
	cmpq	%r13, %rbp
	je	.L109
	testb	%al, %al
	jne	.L109
.L91:
	xorl	%edi, %edi
	cmpq	32(%rbp), %rcx
	setl	%dil
	jmp	.L88
.L130:
	cmpq	$0, 24(%rax)
	je	.L108
.L109:
	movl	$1, %edi
.L88:
	movq	%rbp, %rdx
	movq	%r13, %rcx
	movq	%r15, %rsi
	movq	%r15, %rbp
	call	_ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_@PLT
	movq	72(%rsp), %rax
	addq	$1, %rax
	movq	%rax, 72(%rsp)
	jmp	.L93
	.p2align 4,,10
	.p2align 3
.L129:
	cmpq	$0, 72(%rsp)
	je	.L92
	movq	64(%rsp), %rbp
	cmpq	32(%rbp), %rcx
	jle	.L92
	xorl	%eax, %eax
	jmp	.L85
.L131:
	testq	%rax, %rax
	movq	%rdx, %rbp
	setne	%al
	jmp	.L85
.L75:
	cmpq	$0, k(%rip)
	setle	%bl
	jmp	.L74
.L108:
	movq	%rax, %rbp
	xorl	%eax, %eax
	jmp	.L85
.L128:
	call	__stack_chk_fail@PLT
.L110:
	endbr64
	movq	%rax, %rbx
	jmp	.L99
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA9883:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9883-.LLSDACSB9883
.LLSDACSB9883:
	.uleb128 .LEHB0-.LFB9883
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L110-.LFB9883
	.uleb128 0
.LLSDACSE9883:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC9883
	.type	_Z5judgex.cold, @function
_Z5judgex.cold:
.LFSB9883:
.L99:
	.cfi_def_cfa_offset 160
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	48(%rsp), %rdi
	call	_ZNSt8_Rb_treeIxSt4pairIKxbESt10_Select1stIS2_ESt4lessIxESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	movq	88(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L132
	movq	%rbx, %rdi
.LEHB1:
	call	_Unwind_Resume@PLT
.LEHE1:
.L132:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE9883:
	.section	.gcc_except_table
.LLSDAC9883:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC9883-.LLSDACSBC9883
.LLSDACSBC9883:
	.uleb128 .LEHB1-.LCOLDB0
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSEC9883:
	.section	.text.unlikely
	.text
	.size	_Z5judgex, .-_Z5judgex
	.section	.text.unlikely
	.size	_Z5judgex.cold, .-_Z5judgex.cold
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB9899:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movl	$1, %ebx
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	stdin(%rip), %rdi
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	jbe	.L134
	movq	$-1, %rbp
	.p2align 4,,10
	.p2align 3
.L136:
	movq	stdin(%rip), %rdi
	cmpb	$45, %dl
	cmove	%rbp, %rbx
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	ja	.L136
.L134:
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L137:
	xorl	$48, %edx
	movq	stdin(%rip), %rdi
	leaq	0(%rbp,%rbp,4), %rcx
	movsbq	%dl, %rax
	leaq	(%rax,%rcx,2), %rbp
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	jbe	.L137
	imulq	%rbp, %rbx
	leaq	awa(%rip), %r13
	movq	$-1, %rbp
	leaq	-1(%rbx), %rax
	movq	%rax, 8(%rsp)
	testq	%rbx, %rbx
	jle	.L184
	.p2align 4,,10
	.p2align 3
.L138:
	movq	stdin(%rip), %rdi
	movl	$1, %ebx
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	jbe	.L139
	.p2align 4,,10
	.p2align 3
.L141:
	movq	stdin(%rip), %rdi
	cmpb	$45, %dl
	cmove	%rbp, %rbx
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	ja	.L141
.L139:
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L142:
	movq	stdin(%rip), %rdi
	xorl	$48, %edx
	leaq	(%r12,%r12,4), %rax
	movsbq	%dl, %rdx
	leaq	(%rdx,%rax,2), %r12
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	jbe	.L142
	imulq	%r12, %rbx
	movq	stdin(%rip), %rdi
	movq	%rbx, n(%rip)
	movl	$1, %ebx
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	jbe	.L143
	.p2align 4,,10
	.p2align 3
.L145:
	movq	stdin(%rip), %rdi
	cmpb	$45, %dl
	cmove	%rbp, %rbx
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	ja	.L145
.L143:
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L146:
	movq	stdin(%rip), %rdi
	xorl	$48, %edx
	leaq	(%r12,%r12,4), %rax
	movsbq	%dl, %rdx
	leaq	(%rdx,%rax,2), %r12
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	jbe	.L146
	imulq	%r12, %rbx
	movq	n(%rip), %rdx
	movq	%rbx, k(%rip)
	testq	%rdx, %rdx
	jle	.L147
	movl	$1, %r12d
	.p2align 4,,10
	.p2align 3
.L152:
	movq	stdin(%rip), %rdi
	movl	$1, %ebx
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	jbe	.L148
	.p2align 4,,10
	.p2align 3
.L150:
	movq	stdin(%rip), %rdi
	cmpb	$45, %dl
	cmove	%rbp, %rbx
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	ja	.L150
.L148:
	xorl	%r14d, %r14d
	.p2align 4,,10
	.p2align 3
.L151:
	movq	stdin(%rip), %rdi
	xorl	$48, %edx
	leaq	(%r14,%r14,4), %rax
	movsbq	%dl, %rdx
	leaq	(%rdx,%rax,2), %r14
	call	getc@PLT
	movl	%eax, %edx
	subl	$48, %eax
	cmpb	$9, %al
	jbe	.L151
	movq	%r14, %rcx
	movq	n(%rip), %rdx
	imulq	%rbx, %rcx
	movq	%rcx, 0(%r13,%r12,8)
	addq	$1, %r12
	cmpq	%r12, %rdx
	jge	.L152
.L147:
	xorl	%r12d, %r12d
	addq	$1, %rdx
	movq	%rdx, %r14
	js	.L153
	xorl	%r15d, %r15d
	jmp	.L156
	.p2align 4,,10
	.p2align 3
.L186:
	leaq	1(%rbx), %r15
	movq	%rbx, %r12
	cmpq	%r14, %r15
	jg	.L153
.L156:
	leaq	(%r15,%r14), %rax
	movq	%rax, %rbx
	shrq	$63, %rbx
	addq	%rax, %rbx
	sarq	%rbx
	movq	%rbx, %rdi
	call	_Z5judgex
	testb	%al, %al
	jne	.L186
	leaq	-1(%rbx), %r14
	cmpq	%r14, %r15
	jle	.L156
.L153:
	movq	%r12, %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo9_M_insertIxEERSoT_@PLT
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r12
	testq	%r12, %r12
	je	.L187
	cmpb	$0, 56(%r12)
	je	.L158
	movsbl	67(%r12), %esi
.L159:
	movq	%rbx, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	subq	$1, 8(%rsp)
	movq	8(%rsp), %rax
	cmpq	$-1, %rax
	jne	.L138
.L184:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L158:
	.cfi_restore_state
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r12), %rax
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L159
	movq	%r12, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L159
.L187:
	call	_ZSt16__throw_bad_castv@PLT
	.cfi_endproc
.LFE9899:
	.size	main, .-main
	.globl	k
	.bss
	.align 8
	.type	k, @object
	.size	k, 8
k:
	.zero	8
	.globl	n
	.align 8
	.type	n, @object
	.size	n, 8
n:
	.zero	8
	.globl	awa
	.align 32
	.type	awa, @object
	.size	awa, 1600040
awa:
	.zero	1600040
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
