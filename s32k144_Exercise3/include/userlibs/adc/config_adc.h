/*
 * config_adc.h
 *
 *  Created on: Oct 26, 2025
 *      Author: Admin
 */

#ifndef USERLIBS_ADC_CONFIG_ADC_H_
#define USERLIBS_ADC_CONFIG_ADC_H_

/**
 * @brief init adc
 *
 */

#include "S32K144.h"
#include <stdint.h>
#include <stdbool.h>

/* ADC Clock Divider */
typedef enum
{
    ADC_CLK_DIV_1 = 0u,    /* Divide by 1 */
    ADC_CLK_DIV_2 = 1u,    /* Divide by 2 */
    ADC_CLK_DIV_4 = 2u,    /* Divide by 4 */
    ADC_CLK_DIV_8 = 3u     /* Divide by 8 */
} ADC_ClockDivide_t;

/* ADC Resolution */
typedef enum
{
    ADC_RESOLUTION_8BIT  = 0u,    /* 8-bit resolution */
    ADC_RESOLUTION_10BIT = 1u,    /* 10-bit resolution */
    ADC_RESOLUTION_12BIT = 2u     /* 12-bit resolution */
} ADC_Resolution_t;

/* ADC Input Clock Source */
typedef enum
{
    ADC_CLK_ALT1 = 0u,    /* Alternative clock 1 */
    ADC_CLK_ALT2 = 1u,    /* Alternative clock 2 */
    ADC_CLK_ALT3 = 2u,    /* Alternative clock 3 */
    ADC_CLK_ALT4 = 3u     /* Alternative clock 4 */
} ADC_ClockSource_t;

/* ADC Sample Time */
typedef enum
{
    ADC_SAMPLE_TIME_2   = 0u,     /* 2 ADC clocks */
    ADC_SAMPLE_TIME_4   = 1u,     /* 4 ADC clocks */
    ADC_SAMPLE_TIME_8   = 2u,     /* 8 ADC clocks */
    ADC_SAMPLE_TIME_16  = 3u,     /* 16 ADC clocks */
    ADC_SAMPLE_TIME_32  = 4u,     /* 32 ADC clocks */
    ADC_SAMPLE_TIME_64  = 5u,     /* 64 ADC clocks */
    ADC_SAMPLE_TIME_128 = 6u,     /* 128 ADC clocks */
    ADC_SAMPLE_TIME_256 = 7u      /* 256 ADC clocks */
} ADC_SampleTime_t;

/* ADC Trigger Type */
typedef enum
{
    ADC_TRIGGER_SOFTWARE = 0u,    /* Software trigger */
    ADC_TRIGGER_HARDWARE = 1u     /* Hardware trigger */
} ADC_TriggerType_t;

/* ADC Configuration Structure */
typedef struct
{
    ADC_ClockDivide_t clkDivide;       /* Clock divider */
    ADC_Resolution_t resolution;        /* Conversion resolution */
    ADC_ClockSource_t clkSource;        /* Clock source */
    ADC_SampleTime_t sampleTime;        /* Sample time */
    ADC_TriggerType_t triggerType;      /* Trigger type */
    bool continuousMode;                 /* Continuous conversion mode */
    bool lowPowerMode;                   /* Low power mode */
} ADC_Config_t;

/* ADC Channel Configuration */
typedef struct
{
    uint8_t channelNumber;               /* ADC channel (0-31) */
    bool interruptEnable;                /* Interrupt enable */
} ADC_ChannelConfig_t;

/* ADC Result Structure */
typedef struct
{
    uint16_t rawValue;                   /* Raw ADC value */
    uint16_t voltage_mV;                 /* Converted voltage in mV */
    bool valid;                          /* Conversion valid flag */
} ADC_Result_t;


#define ADC_R_MASK              0x00000FFFu

/* Reference Voltage (mV) */
#define ADC_VREF_MV             5000u

/**
 * @brief Initialize ADC module
 * @param base: Pointer to ADC base address (ADC0 ỏ ADC1)
 * @param config: Pointer tới cấu hình ADC
 */
void ADC_Init(ADC_Type *base, const ADC_Config_t *config);

/**
 * @brief Config ADC channel
 * @param base: Pointer tới ADC base address
 * @param channelConfig: Pointer to channel config
 */
void ADC_ConfigureChannel(ADC_Type *base, const ADC_ChannelConfig_t *channelConfig);

/**
 * @brief Start conversion (software trigger)
 * @param base: Pointer tới ADC base address
 * @param channel: ADC channel number (0-31)
 */
void ADC_StartConversion(ADC_Type *base, uint8_t channel);

/**
 * @brief Examine conversion
 * @param base: Pointer tới ADC base address
 * @return true if conversion complete
 */
bool ADC_IsConversionComplete(ADC_Type *base);

/**
 * @brief Read conversion result
 * @param base: Pointer to ADC base address
 * @return Raw ADC value (0-4095 for 12-bit)
 */
uint16_t ADC_GetConversionResult(ADC_Type *base);

/**
 * @brief Read result and convert to voltage
 * @param base: Pointer to ADC base address
 * @param result: Pointer to structure for storage results
 */
void ADC_GetResult(ADC_Type *base, ADC_Result_t *result);

/**
 * @brief Implement calibration for ADC
 * @param base: Pointer to ADC base address
 * @return true if calibration success
 */
bool ADC_Calibrate(ADC_Type *base);

/**
 * @brief default config
 * @param config: Pointer to structure to save results
 */
void ADC_GetDefaultConfig(ADC_Config_t *config);

/**
 * @brief convert raw value to voltage(mV)
 * @param rawValue: Raw ADC value
 * @param resolution: ADC resolution
 * @return Voltage in mV
 */
uint16_t ADC_ConvertToVoltage(uint16_t rawValue, ADC_Resolution_t resolution);

#endif /* USERLIBS_ADC_CONFIG_ADC_H_ */
