# STM32 GDB 命令行调试指南

本指南介绍如何使用 OpenOCD 和 GDB 在命令行下调试 STM32 项目。

## 1. 准备工作

确保已安装：
- **OpenOCD**: 用于连接调试器 (ST-Link/CMSIS-DAP)
- **arm-none-eabi-gdb**: ARM GDB 调试客户端

## 2. 调试代码准备

为了演示调试，我们在 `key_app.c` 中添加了调试变量：

```c
// 调试用变量
volatile uint32_t debug_counter = 0;       // 按键处理函数调用次数
volatile uint8_t debug_key_pressed = 0;    // 最后一次按下的按键值
volatile uint8_t debug_led_state = 0;      // LED状态位图
volatile uint32_t debug_key1_count = 0;    // KEY1按下次数
```

这些 `volatile` 变量可以防止被编译器优化，确保在 GDB 中能实时读取。

## 3. 启动调试服务 (OpenOCD)

在终端 1 中运行：

```cmd
openocd -f interface/cmsis-dap.cfg -f target/stm32g4x.cfg
```

*注意：如果连接不稳定，可尝试降低时钟频率（在 cfg 文件中添加 `adapter speed 500`）。*

成功启动后会看到：
`Info : Listening on port 3333 for gdb connections`

## 4. 启动调试客户端 (GDB)

在终端 2 中运行：

```cmd
arm-none-eabi-gdb build\test_demo\test_demo.elf
```

## 5. GDB 常用调试命令

进入 GDB 后，依次执行以下命令（或将它们保存为 `debug.gdb` 脚本）：

### 连接与复位
```gdb
target remote localhost:3333    # 连接 OpenOCD
monitor reset halt              # 复位并暂停
load                            # 下载程序（如果已烧录可跳过）
```

### 查看变量
```gdb
print debug_counter             # 查看计数器值
print debug_key_pressed         # 查看按键值
display debug_counter           # 每次暂停自动显示计数器
```

### 控制运行
```gdb
continue (或 c)                 # 继续运行
next (或 n)                     # 单步执行（不进入函数）
step (或 s)                     # 单步执行（进入函数）
```

### 设置断点
```gdb
break key_proc                  # 在函数入口设置断点
break key_app.c:45              # 在指定行设置断点
info breakpoints                # 查看断点
delete 1                        # 删除编号为 1 的断点
```

## 6. 自动化调试脚本

您可以创建一个 `.gdb` 脚本（例如 `debug_script.gdb`）来自动执行初始化：

```gdb
target remote localhost:3333
monitor reset halt
break key_proc
continue
```

运行方式：
```cmd
arm-none-eabi-gdb build\test_demo\test_demo.elf -x debug_script.gdb