# GDB Debug Script for STM32G4
target remote localhost:3333
monitor reset halt

# 显示寄存器
info registers

# 显示当前位置
where

# 读取一些内存
x/16x 0x08000000

# 继续运行
continue