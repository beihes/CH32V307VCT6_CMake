#   CH32V307VCT6_CMake
这是为 CH32 的 RISC-V 单片机编译的 CMake 配置
**本例程使用YD-CH32V307VCT6**
##  Windows编译方式
将MounRiver Studio下的toolchain中的GCC(这里选的是GCC12)加到CMakeLists的TOOLPATH里，环境变量我没成功，不过ARM的GCC和以直接添加在环境变量
##  Linux编译方式
我没试:(
    （等待更新中）
##  功能
### FLASH
####    W25Q32
使用驱动SPI1
####    SDCard
使用驱动SDIO(还没更新)
### I2C
等待更新
### I2S
等待更新
### Key
使用PB03接口，已实现长按计时
### LED
LED_RED     PA15
LED_GREEN   PB04
### RTC
使用TIM1调整计时，初始时间2025-01-01 3 00:00:00
### USART
等待更新
### USB
使用USBHS接口，已实现U盘读取，方法为长按Key超过3秒
##  App
### GAME
等待更新