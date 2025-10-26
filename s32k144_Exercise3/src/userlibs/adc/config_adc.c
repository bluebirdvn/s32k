/*
 * config_adc.c
 *
 *  Created on: Oct 26, 2025
 *      Author: Admin
 */
#include "config_adc.h"

void ADC_Init(ADC_Type *base, const ADC_Config_t *config)
{
    uint32_t cfg1 = 0u;
    uint32_t sc2 = 0u;
    uint32_t sc3 = 0u;

    /* Configure CFG1 register */
    cfg1 |= (uint32_t)config->clkSource & ADC_CFG1_ADICLK_MASK;
    cfg1 |= (uint32_t)ADC_CFG1_MODE(config->resolution);
    cfg1 |= (uint32_t)ADC_CFG1_ADIV(config->clkDivide);

    base->CFG1 = cfg1;

    /* Configure SC2 register */
    if (config->triggerType == ADC_TRIGGER_HARDWARE)
    {
        sc2 |= ADC_SC2_ADTRG_MASK;
    }
    base->SC2 = sc2;

    /* Configure SC3 register */
    if (config->continuousMode)
    {
        sc3 |= ADC_SC3_ADCO_MASK;
    }
    base->SC3 = sc3;

    /* Perform calibration */
    ADC_Calibrate(base);
}

void ADC_ConfigureChannel(ADC_Type *base, const ADC_ChannelConfig_t *channelConfig)
{
    uint32_t sc1 = 0u;

    sc1 |= (channelConfig->channelNumber & ADC_SC1_ADCH_MASK);

    if (channelConfig->interruptEnable)
    {
        sc1 |= ADC_SC1_AIEN_MASK;
    }

    base->SC1[0] = sc1;
}

void ADC_StartConversion(ADC_Type *base, uint8_t channel)
{
    uint32_t sc1 = base->SC1[0];

    /* Clear channel bits and set new channel */
    sc1 &= ~ADC_SC1_ADCH_MASK;
    sc1 |= (channel & ADC_SC1_ADCH_MASK);

    /* Write SC1 will start conversion */
    base->SC1[0] = sc1;
}

bool ADC_IsConversionComplete(ADC_Type *base)
{
    return ((base->SC1[0] & ADC_SC1_COCO_MASK) != 0u);
}

uint16_t ADC_GetConversionResult(ADC_Type *base)
{
    return (uint16_t)(base->R[0] & ADC_R_MASK);
}

void ADC_GetResult(ADC_Type *base, ADC_Result_t *result)
{
    if (ADC_IsConversionComplete(base))
    {
        result->rawValue = ADC_GetConversionResult(base);
        result->voltage_mV = ADC_ConvertToVoltage(result->rawValue, ADC_RESOLUTION_12BIT);
        result->valid = true;
    }
    else
    {
        result->valid = false;
    }
}

bool ADC_Calibrate(ADC_Type *base)
{

}

void ADC_GetDefaultConfig(ADC_Config_t *config)
{
    config->clkDivide = ADC_CLK_DIV_4;
    config->resolution = ADC_RESOLUTION_12BIT;
    config->clkSource = ADC_CLK_ALT1;
    config->sampleTime = ADC_SAMPLE_TIME_16;
    config->triggerType = ADC_TRIGGER_SOFTWARE;
    config->continuousMode = false;
    config->lowPowerMode = false;
}

uint16_t ADC_ConvertToVoltage(uint16_t rawValue, ADC_Resolution_t resolution)
{
    uint32_t maxValue;
    uint32_t voltage;

    /* Determine max value based on resolution */
    switch (resolution)
    {
        case ADC_RESOLUTION_8BIT:
            maxValue = 255u;
            break;
        case ADC_RESOLUTION_10BIT:
            maxValue = 1023u;
            break;
        case ADC_RESOLUTION_12BIT:
        default:
            maxValue = 4095u;
            break;
    }

    /* Convert to voltage in mV */
    voltage = ((uint32_t)rawValue * ADC_VREF_MV) / maxValue;

    return (uint16_t)voltage;
}
