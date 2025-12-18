# STM32G431RBT6 蓝桥杯嵌入式开发板项目

## 项目简介

基于 STM32G431RBT6 微控制器的嵌入式开发项目，适用于蓝桥杯嵌入式设计与开发竞赛。

### 硬件规格

| 参数 | 规格 |
|------|------|
| MCU | STM32G431RBT6 (Cortex-M4, 170MHz Max) |
| Flash | 128 KB |
| SRAM | 32 KB |
| 外部晶振 | 24 MHz HSE |
| 系统时钟 | 80 MHz (通过PLL) |
| 封装 | LQFP64 |

### 外设配置

- **USART1**: PA9(TX) / PA10(RX), 9600 bps, DMA接收
- **GPIO**: LED控制 (PC8-PC15), 按键输入 (PB0-PB2, PA0)
- **LCD**: 自定义LCD驱动接口
- **SWD**: PA13/PA14 调试接口

## 目录结构

```
test_demo/
├── APP/                    # 用户应用代码
│   ├── key_app.c/h        # 按键驱动
│   ├── lcd_app.c/h        # LCD应用层
│   ├── lcd.c/h            # LCD底层驱动
│   ├── led_app.c/h        # LED控制
│   ├── scheduler.c/h      # 任务调度器
│   ├── uart_app.c/h       # 串口应用
│   ├── system.c/h         # 系统初始化
│   ├── mydefine.h         # 全局宏定义
│   └── fonts.h            # LCD字体库
├── Core/
│   ├── Inc/               # HAL配置头文件
│   └── Src/               # HAL配置源文件
├── Drivers/
│   ├── CMSIS/             # ARM CMSIS库
│   └── STM32G4xx_HAL_Driver/  # ST HAL库
├── MDK-ARM/               # Keil工程文件
│   ├── test_demo.uvprojx  # Keil工程
│   └── startup_stm32g431xx.s  # 启动文件
└── test_demo.ioc          # STM32CubeMX配置文件
```

## 开发环境

### 使用的工具

| 工具 | 用途 |
|------|------|
| **VSCode + EIDE** | 代码编辑、编译、烧录 |
| **STM32CubeMX** | 外设配置和代码生成 |
| **ARM GCC / AC5/AC6** | 编译工具链 |
| **ST-Link** | 调试器/烧录器 |

### 开发流程

1. 使用 STM32CubeMX 打开 `test_demo.ioc` 进行外设配置
2. 在 VSCode 中安装 EIDE 扩展
3. 打开项目文件夹，EIDE 自动识别工程
4. 在 EIDE 中编译和烧录

---

## 调试

### 串口调试

- 波特率: 9600
- 数据位: 8
- 停止位: 1
- 校验: 无

连接 PA9(TX) 和 PA10(RX) 到 USB-TTL 转换器。

### LED 指示

| LED | GPIO | 说明 |
|-----|------|------|
| LED1-LED8 | PC8-PC15 | 低电平点亮 |

---

## 许可证

本项目仅供学习和竞赛使用。

## 更新日志

- 2024-12: 初始版本，基于 STM32CubeMX 6.14.1 生成