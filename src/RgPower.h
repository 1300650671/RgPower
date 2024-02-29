#ifndef APPLICATIONS_RGPOWER_POWER_H_
#define APPLICATIONS_RGPOWER_POWER_H_

/*
 * 软件名称：RgPower
 * 当前版本：v1.0.0
 *
 * 版本说明：
 *
 * 版本号：v1.0.0
 * 作者：liuxx
 * 修订说明：
 * [init] 完成基本功能 1 电量计算 2 包索引制作 3 git 初始化
 *
 *
 * */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdint.h>

/* 无需改动 配置在RT-Thread Seetings中 */
#ifndef PKG_USING_RGPOWER
#define RGPOWER_USEING_LOG
#define RGPOWER_POWER_OFF_PIN_NUM 22
#define RGPOWER_CHARGE_PIN_NUM 5
#define RGPOWER_CHARGE_GPIO_STATUS 1
#define RGPOWER_ADC_DEV_NAME "adc3"
#define RGPOWER_ADC_DEV_CHANNEL 11
#define RGPOWER_REFER_VOLTAGE 3300
#define RGPOWER_CONVERT_BITS_MAX 4096
#define RGPOWER_SCALE_FACTOR 3
#define RGPOWER_100_VOLTAGE  4200
#define RGPOWER_0_VOLTAGE    3500
#endif

int RgPower_get_power(void);

#endif /* APPLICATIONS_RGPOWER_POWER_H_ */
