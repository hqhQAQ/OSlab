# System help

## Makefile Option

### run

使用qemu运行编译好的系统

### debug

使用qemu运行系统并等待gdb连接

### gdb

使用gdb调试vmlinux,进入后需要使用target remote localhost:1234命令连接

### SCHEDULE

该选项默认为PREEMPTIVE, 即使用抢占式调度算法, 可以设置为其他以使用linux0.11的非抢占式调度

例如: 

```bash

make SCHEDULE=NO

```

### clean

删除编译出的所有文件

