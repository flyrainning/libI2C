# libI2C
PHP扩展程序，为PHP提供对I2C（Inter－Integrated Circuit）总线基本操作的支持，可以使用php直接操作I2C总线进行通讯。
编译此扩展需要安装libi2c-dev库。debian系列可以使用命令`apt-get install libi2c-dev`安装

> **注意：**本扩展基于Linux内核i2c驱动，目前能支持的系统尚未全面测试，已在 `cubieboard 2` 开发板中进行测试，理论上常见的全志系列cpu的开发板和迷你电脑都能够支持，比如树莓派。

请根据您使用的系统和硬件自行调整启用I2C总线，如cubieboard需调整script.fex启用i2c。系统总线工作正常后即可在php中调用本扩展访问总线。简单的检查方法是查看 `/sys/class/i2c-dev/` 下是否有内容，或者是否能够使用 `i2cdetect` 等工具，当然，要使用这些工具首先要安装 `i2c-tools`

#代码实例

```php
//实例化
$i2c=new i2c();

//打开设备
$i2c->open($adapter,$addr);


//向一个地址写入数据
$subaddr=0x2;
$i2c->write($subaddr, 0x00);


//读取数据
$data=$i2c->read($subaddr);

```

项目整理准备中，代码稍等几天
