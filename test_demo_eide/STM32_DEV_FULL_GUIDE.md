# STM32 EIDE 命令行开发全流程指南

本指南旨在指导开发者（或自动化脚本）如何在不依赖图形界面的情况下，完成 STM32 项目的**编译**、**烧录**与**调试**全流程。本方案基于 VS Code EIDE 插件环境，但操作完全通过 CLI（命令行）执行。

---

## 1. 核心工具链准备

在开始之前，请确保已定位到以下工具的路径（路径可能因环境而异，以下为当前环境路径）：

| 工具 | 用途 | 关键文件/路径 |
| :--- | :--- | :--- |
| **Builder** | 项目构建 | `unify_builder.exe` (EIDE 插件内置) |
| **Config** | 构建参数 | `build/test_demo/builder.params` (EIDE 自动生成) |
| **OpenOCD** | 烧录/调试服务 | `openocd.exe` (系统已安装) |
| **GDB** | 调试客户端 | `arm-none-eabi-gdb.exe` (GCC 工具链) |

---

## 2. 脚本文件准备 (Script Preparation)

在执行后续操作前，请在项目根目录下创建以下脚本文件。

### 2.1 烧录脚本 (`flash.cfg`)
用于自动化烧录流程。

```tcl
# flash.cfg
init
adapter speed 100          ;# 设置通信频率为 100kHz (推荐值，确保稳定性)
reset halt                 ;# 复位并暂停芯片
flash write_image erase build/test_demo/test_demo.hex ;# 擦除并写入 HEX 文件
reset run                  ;# 复位并运行
shutdown                   ;# 烧录完成后关闭 OpenOCD
```

### 2.2 调试配置脚本 (`debug.cfg`)
用于启动调试服务，可根据硬件情况调整参数。

```tcl
# debug.cfg
source [find interface/cmsis-dap.cfg] ;# 指定调试器类型
adapter speed 500                     ;# 设置通信频率
source [find target/stm32g4x.cfg]     ;# 指定目标芯片
```

### 2.3 一键运行脚本 (`run_all.bat`)
用于 Windows 环境下的一键编译和烧录。

```bat
@echo off
echo [1/2] Compiling...
cd /d "%~dp0"
"c:\Users\peng\.vscode\extensions\cl.eide-3.26.1\res\tools\win32\unify_builder\unify_builder.exe" -p "build\test_demo\builder.params" -r
if %errorlevel% neq 0 exit /b %errorlevel%

echo [2/2] Flashing...
openocd -f interface/cmsis-dap.cfg -f target/stm32g4x.cfg -f flash.cfg
echo Done.
```

---

## 3. 第一阶段：命令行编译 (Build)

### 3.1 原理
EIDE 插件在编译时会生成一个 `builder.params` 文件，其中包含了所有的编译参数、包含路径和宏定义。我们可以直接调用 EIDE 的构建器 `unify_builder.exe` 加载此配置进行编译。

### 3.2 操作步骤

1. **定位构建器路径**：
   通常位于用户目录的 `.vscode` 扩展目录下。
   
2. **执行编译命令**：
   **重要：必须在项目根目录下执行此命令**，否则构建器无法正确解析相对路径。
   
   ```cmd
   cd /d d:\Users\peng\Desktop\keil51\STM32\CODE\lanqiao\1210\test_demo_eide
   "c:\Users\peng\.vscode\extensions\cl.eide-3.26.1\res\tools\win32\unify_builder\unify_builder.exe" -p "build\test_demo\builder.params" -r
   ```
   *注：建议加上 `-r` 参数强制重新编译，确保改动生效。*

3. **验证结果**：
   - 成功标志：输出 `exit code: 0`
   - 产物检查：检查 `build/test_demo/` 目录下是否生成了 `test_demo.hex` 和 `test_demo.elf`。

---

## 4. 第二阶段：命令行烧录 (Flash)

### 4.1 执行烧录
确保调试器（如 CMSIS-DAP）已连接，运行：

```cmd
openocd -f interface/cmsis-dap.cfg -f target/stm32g4x.cfg -f flash.cfg
```

或者直接运行我们创建的批处理文件：
```cmd
run_all.bat
```

---

## 5. 第三阶段：命令行调试 (Debug)

调试分为 **"代码插桩"**、**"启动服务"** 和 **"GDB 交互"** 三步。

### 5.1 代码插桩 (可选但推荐)
在纯命令行调试中，直接观察变量比设置断点更直观。建议在代码中（如 `main.c` 或 `key_app.c`）添加 `volatile` 全局变量：

```c
// 添加 volatile 关键字防止编译器优化，确保调试器能实时读取
volatile uint32_t debug_counter = 0;       
volatile uint8_t debug_key_value = 0;
```

### 5.2 步骤 A：启动 GDB Server
在一个单独的终端窗口（终端 1）中运行 OpenOCD 作为服务器。使用我们创建的 `debug.cfg`：

```cmd
openocd -f debug.cfg
```
*成功标志：看到 `Listening on port 3333 for gdb connections`。请保持此终端开启。*

### 5.3 步骤 B：启动 GDB Client
在另一个终端窗口（终端 2）中运行 GDB 连接目标：

```cmd
arm-none-eabi-gdb build\test_demo\test_demo.elf
```

进入 GDB 交互界面 `(gdb)` 后，依次输入以下指令进行调试：

1. **连接目标**：
   ```gdb
   target remote localhost:3333
   ```

2. **复位并暂停**：
   ```gdb
   monitor reset halt
   ```

3. **查看变量**（验证之前的插桩）：
   ```gdb
   print debug_counter      # 查看当前值
   display debug_counter    # 设置自动显示（每次停顿都会显示）
   ```

4. **控制运行**：
   - `c` (continue): 继续运行程序
   - `Ctrl+C`: 暂停程序（以查看变量变化）
   - `n` (next): 单步执行

5. **修改变量**（动态注入）：
   ```gdb
   set var debug_counter = 100
   ```

---

## 6. 常见问题排查 (Troubleshooting)

1. **Error: CMSIS-DAP command mismatch**
   - **原因**：USB 线缆质量差、供电不足或时钟频率过高。
   - **解决**：在 `flash.cfg` 或 `debug.cfg` 中将 `adapter speed` 调低（例如从 500 降至 100 或 50）。

2. **GDB 提示 "No symbol table"**
   - **原因**：加载的文件没有符号表。
   - **解决**：确保 GDB 加载的是 `.elf` 文件（包含调试信息）而不是 `.hex` 或 `.bin` 文件。

3. **变量值一直不变**
   - **原因**：编译器将变量优化了。
   - **解决**：确保调试变量定义时加上 `volatile` 关键字。