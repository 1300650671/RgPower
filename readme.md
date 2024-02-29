# RgPower

## 简介

RgPower 软件包提供了使用rtthread adc驱动采集电压，使用电池电压计算当前电量百分比，并且借助滤波算法对电量数据进行滤波处理，同时支持低电量自动关机

## 支持情况

| 读取方式 | 支持情况 |
| -------- | -------- |
| 轮询     | √        |
| 中断     | ×        |

## 软件包依赖
* 1、RT-Thread Settings 中打开 使用ADC设备驱动程序
* 2、board.h 中使能任意ADC设备
* 3、cubemx setting 中选择打开ADC引脚
#### 

## 使用说明

#### 获取软件包
~~~
RT-Thread online packages
    peripheral libraries and drivers --->
        [*] Use RgPower --->
~~~

#### 示例
~~~
#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "RgPower.h"

int main(void)
{

    while (1)
    {
        int power = RgPower_get_power();

        if (power < 0)
        {
            LOG_D("充电中");
        }
        else
        {
            LOG_D("电量： %d %%", power);
        }

        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
~~~

## 注意事项
~~~
本软件包依赖RTT ADC驱动，暂时不支持其他平台
~~~
## 联系人信息

* 维护人：liuxx
* 邮箱：1300650671@qq.com
* 软件包主页：https://github.com/1300650671/RgPower.git

