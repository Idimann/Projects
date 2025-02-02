
release:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 c1 2f 00 00 	mov    0x2fc1(%rip),%rax        # 3fd0 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .text:

0000000000001020 <_start>:
    1020:	f3 0f 1e fa          	endbr64
    1024:	31 ed                	xor    %ebp,%ebp
    1026:	49 89 d1             	mov    %rdx,%r9
    1029:	5e                   	pop    %rsi
    102a:	48 89 e2             	mov    %rsp,%rdx
    102d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1031:	50                   	push   %rax
    1032:	54                   	push   %rsp
    1033:	45 31 c0             	xor    %r8d,%r8d
    1036:	31 c9                	xor    %ecx,%ecx
    1038:	48 8d 3d fd 00 00 00 	lea    0xfd(%rip),%rdi        # 113c <main>
    103f:	ff 15 7b 2f 00 00    	call   *0x2f7b(%rip)        # 3fc0 <__libc_start_main@GLIBC_2.34>
    1045:	f4                   	hlt
    1046:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    104d:	00 00 00 
    1050:	48 8d 3d b9 2f 00 00 	lea    0x2fb9(%rip),%rdi        # 4010 <__TMC_END__>
    1057:	48 8d 05 b2 2f 00 00 	lea    0x2fb2(%rip),%rax        # 4010 <__TMC_END__>
    105e:	48 39 f8             	cmp    %rdi,%rax
    1061:	74 15                	je     1078 <_start+0x58>
    1063:	48 8b 05 5e 2f 00 00 	mov    0x2f5e(%rip),%rax        # 3fc8 <_ITM_deregisterTMCloneTable@Base>
    106a:	48 85 c0             	test   %rax,%rax
    106d:	74 09                	je     1078 <_start+0x58>
    106f:	ff e0                	jmp    *%rax
    1071:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1078:	c3                   	ret
    1079:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1080:	48 8d 3d 89 2f 00 00 	lea    0x2f89(%rip),%rdi        # 4010 <__TMC_END__>
    1087:	48 8d 35 82 2f 00 00 	lea    0x2f82(%rip),%rsi        # 4010 <__TMC_END__>
    108e:	48 29 fe             	sub    %rdi,%rsi
    1091:	48 89 f0             	mov    %rsi,%rax
    1094:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1098:	48 c1 f8 03          	sar    $0x3,%rax
    109c:	48 01 c6             	add    %rax,%rsi
    109f:	48 d1 fe             	sar    $1,%rsi
    10a2:	74 14                	je     10b8 <_start+0x98>
    10a4:	48 8b 05 2d 2f 00 00 	mov    0x2f2d(%rip),%rax        # 3fd8 <_ITM_registerTMCloneTable@Base>
    10ab:	48 85 c0             	test   %rax,%rax
    10ae:	74 08                	je     10b8 <_start+0x98>
    10b0:	ff e0                	jmp    *%rax
    10b2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10b8:	c3                   	ret
    10b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10c0:	f3 0f 1e fa          	endbr64
    10c4:	80 3d 45 2f 00 00 00 	cmpb   $0x0,0x2f45(%rip)        # 4010 <__TMC_END__>
    10cb:	75 33                	jne    1100 <_start+0xe0>
    10cd:	55                   	push   %rbp
    10ce:	48 83 3d 0a 2f 00 00 	cmpq   $0x0,0x2f0a(%rip)        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    10d5:	00 
    10d6:	48 89 e5             	mov    %rsp,%rbp
    10d9:	74 0d                	je     10e8 <_start+0xc8>
    10db:	48 8b 3d 26 2f 00 00 	mov    0x2f26(%rip),%rdi        # 4008 <__dso_handle>
    10e2:	ff 15 f8 2e 00 00    	call   *0x2ef8(%rip)        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    10e8:	e8 63 ff ff ff       	call   1050 <_start+0x30>
    10ed:	c6 05 1c 2f 00 00 01 	movb   $0x1,0x2f1c(%rip)        # 4010 <__TMC_END__>
    10f4:	5d                   	pop    %rbp
    10f5:	c3                   	ret
    10f6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    10fd:	00 00 00 
    1100:	c3                   	ret
    1101:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
    1108:	00 00 00 00 
    110c:	0f 1f 40 00          	nopl   0x0(%rax)
    1110:	f3 0f 1e fa          	endbr64
    1114:	e9 67 ff ff ff       	jmp    1080 <_start+0x60>

0000000000001119 <foo>:
    1119:	55                   	push   %rbp
    111a:	48 89 e5             	mov    %rsp,%rbp
    111d:	48 c7 45 e0 00 01 00 	movq   $0x100,-0x20(%rbp)
    1124:	00 
    1125:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
    112c:	00 
    112d:	48 c7 45 f0 05 00 00 	movq   $0x5,-0x10(%rbp)
    1134:	00 
    1135:	b8 08 00 00 00       	mov    $0x8,%eax
    113a:	5d                   	pop    %rbp
    113b:	c3                   	ret

000000000000113c <main>:
    113c:	55                   	push   %rbp
    113d:	48 89 e5             	mov    %rsp,%rbp
    1140:	b8 00 00 00 00       	mov    $0x0,%eax
    1145:	e8 cf ff ff ff       	call   1119 <foo>
    114a:	5d                   	pop    %rbp
    114b:	c3                   	ret

Disassembly of section .fini:

000000000000114c <_fini>:
    114c:	f3 0f 1e fa          	endbr64
    1150:	48 83 ec 08          	sub    $0x8,%rsp
    1154:	48 83 c4 08          	add    $0x8,%rsp
    1158:	c3                   	ret
