#!/usr/bin/env python
# coding=utf-8

from pwn import *
#context.log_level = "debug"
p = process("./crypto")
p.sendlineafter("请输入要进行的操作：","2")
p.recvuntil("第一步，请做100次基本的数学运算吧：")
for i in range(100):
    p.recvuntil(' : ')
    e = p.recvuntil(" = ")[:-3]
    r = eval(e)
    if '/' in e and r<0:
        r+=1
    log.info("%d : %s = %d"%(i,e,r))
    p.sendline(str(r))
log.success(p.recvuntil("#"))
#p.interactive()
