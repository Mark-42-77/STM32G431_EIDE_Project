# GDB 调试演示脚本
# 连接到 OpenOCD GDB 服务器
target remote localhost:3333

# 复位并暂停
monitor reset halt

# 设置断点在 key_proc 函数
break key_proc

# 显示断点列表
info breakpoints

# 打印调试变量的地址和值
print &debug_counter
print debug_counter
print &debug_key_pressed
print debug_key_pressed

# 显示寄存器
info registers r0 r1 r2 r3 pc sp lr

# 显示调用栈
backtrace

# 继续运行到断点
continue