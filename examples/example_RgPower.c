/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-27     liuxx       the first version
 */

#include "RgPower.h"

#define DBG_TAG "RgPowere_ex"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

int RgPower_example(void)
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
}
MSH_CMD_EXPORT(RgPower_example, say hello to RT-Thread);
