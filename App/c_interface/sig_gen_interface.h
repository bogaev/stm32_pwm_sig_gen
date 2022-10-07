#ifndef _SIG_GEN_INTERFACE_H_
#define _SIG_GEN_INTERFACE_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PWM_MAX_NUM 8
#define SIG_GEN_DEFAULT_SENS_AMP 100
#define SIG_GEN_DEFAULT_SENS_FREQ 15

typedef enum {
  SIG_GEN_OK = 0,
  SIG_GEN_ERROR_PWM_TIMER_NOT_SET,        
  SIG_GEN_ERROR_SAMPLE_RATE_NOT_SET,       
  SIG_GEN_ERROR_SAMPLE_RATE_LESS_THAN_FREQ,
  SIG_GEN_ERROR_AMPLITUDE_VALUE_ABOVE_MAX, 
  SIG_GEN_ERROR_PWM_NOT_INITED,            
  SIG_GEN_ERROR_INCORRECT_BOUNDS,          
  SIG_GEN_ERROR_NUM                       
}
SIG_GEN_StatusTypeDef;

typedef enum {
  SIG_GEN_CARRIER = 0,
  SIG_GEN_AMP_MOD,
  SIG_GEN_FREQ_MOD,
  SIG_GEN_NUM
}
enSignals;

typedef enum {
  SIG_GEN_TYPE_NONE = 0,
  SIG_GEN_TYPE_SINUS,
  SIG_GEN_TYPE_SQUARE,
  SIG_GEN_TYPE_TRIANGLE,
  SIG_GEN_TYPE_SAW,
  SIG_GEN_TYPE_NUM
}
enSignalTypes;

typedef enum {
  SIG_GEN_PARAM_SIGNAL_TYPE = 0,
  SIG_GEN_PARAM_AMP,
  SIG_GEN_PARAM_FREQ,
  SIG_GEN_PARAM_AMP_DEPTH,
  SIG_GEN_PARAM_FREQ_DEPTH,
  SIG_GEN_PARAM_NUM
}
enSignalParams;

typedef struct {
  double from;
  double to;
  double coeff;
}
SIG_GEN_RangeCoeff;

typedef struct {
  SIG_GEN_RangeCoeff* amp_array;
  uint32_t amp_array_size;
  SIG_GEN_RangeCoeff* freq_array;
  uint32_t freq_array_size;
}
SIG_GEN_CoeffsInitStruct;

// Cтруктура инициализации генератора сигналов
typedef struct {
  TIM_HandleTypeDef* pwm_timer; // указатель на структуру ШИМ-генератора HAL
  uint32_t channels[2]; // номера каналов для генерации сигнала (положительная и отрицательная полуволна)
  uint8_t min_duty_cycle_percent; // минимальная величина коэффициента заполнения в процентах
  uint8_t max_duty_cycle_percent; // максимальная величина коэффициента заполнения в процентах
  SIG_GEN_CoeffsInitStruct* coeffs;
}
SIG_GEN_HandleTypeDef;

SIG_GEN_StatusTypeDef SIG_GEN_Init(SIG_GEN_HandleTypeDef* sg_handle);
SIG_GEN_StatusTypeDef SIG_GEN_Deinit(SIG_GEN_HandleTypeDef* sg_handle);
SIG_GEN_StatusTypeDef SIG_GEN_SetSignalType(SIG_GEN_HandleTypeDef* sg_handle, enSignals signal, enSignalTypes type);
SIG_GEN_StatusTypeDef SIG_GEN_SetCarrierAmp(SIG_GEN_HandleTypeDef* sg_handle, double value);
SIG_GEN_StatusTypeDef SIG_GEN_SetFreq(SIG_GEN_HandleTypeDef* sg_handle, enSignals signal, double value);
SIG_GEN_StatusTypeDef SIG_GEN_SetAmpModDepth(SIG_GEN_HandleTypeDef* sg_handle, uint8_t percent);
SIG_GEN_StatusTypeDef SIG_GEN_SetFreqModSens(SIG_GEN_HandleTypeDef* sg_handle, uint8_t percent);
SIG_GEN_StatusTypeDef SIG_GEN_Run(SIG_GEN_HandleTypeDef* sg_handle);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _SIG_GEN_INTERFACE_H_