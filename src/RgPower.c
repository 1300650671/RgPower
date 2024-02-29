#include "RgPower.h"

#define DBG_TAG "RgPower"
#ifdef RGPOWER_USEING_LOG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_ERROR
#endif
#include <rtdbg.h>

static int RgPower_delay = 0;
static int RgPower_status = 0;
static int RgPower_voltage = 0;
static int RgPower_voltage_back = 0xFFFF;
static int RgPower_value = 0;

static rt_adc_device_t RgPower_adc_dev;

static float get_power(void)
{
    int value = 0;
    int vol = 0;
    /* 读取采样值  算数平均滤波 */
    for (int var = 0; var < 50; var++)
    {
        value = rt_adc_read(RgPower_adc_dev, RGPOWER_ADC_DEV_CHANNEL);
        /* 转换为对应电压值 */
        int now_v = value * RGPOWER_REFER_VOLTAGE * RGPOWER_SCALE_FACTOR / RGPOWER_CONVERT_BITS_MAX;
        vol += now_v;
        rt_thread_delay(20);
    }
    vol = vol / 50;

    return vol;
}

static void display_power_send(void *par)
{

    /* 查找设备 */
    RgPower_adc_dev = (rt_adc_device_t) rt_device_find(RGPOWER_ADC_DEV_NAME);
    if (RgPower_adc_dev == RT_NULL)
    {
        LOG_E("adc sample run failed! can't find %s device!\n", RGPOWER_ADC_DEV_NAME);
        return;
    }
    rt_adc_enable(RgPower_adc_dev, RGPOWER_ADC_DEV_CHANNEL);

    while (1)
    {
        RgPower_status = rt_pin_read(RGPOWER_CHARGE_PIN_NUM);
        if (RgPower_status != RGPOWER_CHARGE_GPIO_STATUS)
        {
            if (RgPower_delay == 0 || RgPower_delay > 10)
            {
                RgPower_voltage = get_power();
                if (RgPower_voltage >= RgPower_voltage_back)
                {
                    RgPower_voltage = RgPower_voltage_back;
                }

                RgPower_voltage_back = RgPower_voltage;

                LOG_D("Voltage : %d mv", RgPower_voltage);

                if (RgPower_voltage <= RGPOWER_0_VOLTAGE)
                {
                    LOG_E("low power off !!!\r\n");
                    rt_pin_write(RGPOWER_POWER_OFF_PIN_NUM, PIN_LOW);
                }

                RgPower_value = (RgPower_voltage - RGPOWER_0_VOLTAGE) * 100 / (RGPOWER_100_VOLTAGE - RGPOWER_0_VOLTAGE);
                if (RgPower_value < 0)
                    RgPower_value = 0;
                if (RgPower_value > 100)
                    RgPower_value = 100;
                LOG_D("POWER %d %%", RgPower_value);

            }
            else
            {
                RgPower_delay = RgPower_delay + 1;
                rt_thread_mdelay(1000);
            }
        }
        else
        {
            RgPower_voltage_back = 0xFFFF;
            RgPower_delay = 0;
            rt_thread_mdelay(1000);
        }
    }
}

int RgPower_get_power(void)
{
    if (RgPower_status != RGPOWER_CHARGE_GPIO_STATUS)
    {
        return RgPower_value;
    }
    else
    {
        return -1;
    }
}

int RgPower_init(void)
{
    /* 关机脚默认高电平 */
    rt_pin_mode(RGPOWER_POWER_OFF_PIN_NUM, PIN_MODE_OUTPUT_OD);
    rt_pin_write(RGPOWER_POWER_OFF_PIN_NUM, PIN_HIGH);
    /* 充电检测引脚 输入 */
    rt_pin_mode(RGPOWER_CHARGE_PIN_NUM, PIN_MODE_INPUT);

    rt_thread_t check_tid;
    check_tid = rt_thread_create("power_send", display_power_send, RT_NULL, 2048, 11, 10);
    if (check_tid != RT_NULL)
        rt_thread_startup(check_tid);
    return 0;
}
INIT_COMPONENT_EXPORT(RgPower_init);
