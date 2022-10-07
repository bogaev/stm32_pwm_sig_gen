#include "sig_gen_interface.h"
#include "App\signals\signals.hpp"
#include "App\signal_generator\signal_generator.hpp"
#include "App\pwm_generator\pwm_generator.hpp"
#include "App\pwm_controller\pwm_controller.hpp"

#include <unordered_map>

static std::unordered_map<SIG_GEN_HandleTypeDef*, PwmController*> pwms;

static SIG_GEN_StatusTypeDef CheckCorrStruct(SIG_GEN_RangeCoeff* array,
                                             uint32_t size) {
  if(array[0].from != 0) {
    return SIG_GEN_ERROR_INCORRECT_BOUNDS;
  }
  
  for(uint32_t i = 0; i < size-1; ++i) {
    double cur_end = array[i].to;
    double next_start = array[i+1].from;
    if(cur_end != next_start) {
      return SIG_GEN_ERROR_INCORRECT_BOUNDS;
    }
  }
  
  return SIG_GEN_OK;
}

SIG_GEN_StatusTypeDef SIG_GEN_Init(SIG_GEN_HandleTypeDef* sg_handle) {   
  if(pwms.count(sg_handle)) {
    SIG_GEN_Deinit(sg_handle);
  }

  if(sg_handle->pwm_timer == 0) {
    return SIG_GEN_ERROR_PWM_TIMER_NOT_SET;
  }
  
  double sample_rate = 
    sg_handle->coeffs ? 
      sg_handle->coeffs->freq_array[sg_handle->coeffs->freq_array_size-1].to * 2.
        : 1000.;
  
  auto sig_gen = new SignalGenerator((uint32_t)sample_rate);
  
  pwm_gen::PwmGenerator::Settings duty_cycle_settings;
  duty_cycle_settings.min_percent = (double)sg_handle->min_duty_cycle_percent;
  duty_cycle_settings.max_percent = (double)sg_handle->max_duty_cycle_percent;
  duty_cycle_settings.timer_period = (double)sg_handle->pwm_timer->Init.Period;
  
  pwm_gen::SignalStabilizer::Settings stabilizer_settings = {0};
  if(sg_handle->coeffs != 0) {
    {
      auto err = CheckCorrStruct(sg_handle->coeffs->amp_array,
                                 sg_handle->coeffs->amp_array_size);
      if (err) {
        return err;
      }
    }
    {
      auto err = CheckCorrStruct(sg_handle->coeffs->freq_array,
                                 sg_handle->coeffs->freq_array_size);
      if (err) {
        return err;
      }
    }
    stabilizer_settings.coeffs = sg_handle->coeffs;
  }
    
  auto pwm_gen_ = new pwm_gen::PwmGenerator(sig_gen,
                                            duty_cycle_settings,
                                            stabilizer_settings);
  
  pwms[sg_handle] = new IT_PwmController(sg_handle->pwm_timer,
                                        {sg_handle->channels[0],
                                         sg_handle->channels[1]},
                                         pwm_gen_);
  pwms[sg_handle]->Start();
  
  return SIG_GEN_OK;
}

SIG_GEN_StatusTypeDef SIG_GEN_Deinit(SIG_GEN_HandleTypeDef* sg_handle) {   
  pwms.at(sg_handle)->~PwmController();
  pwms.erase(sg_handle);
  return SIG_GEN_OK;
}

SIG_GEN_StatusTypeDef SIG_GEN_SetSignalType(SIG_GEN_HandleTypeDef* sg_handle, enSignals signal, enSignalTypes type) {
  if(!pwms.count(sg_handle)) {
    return SIG_GEN_ERROR_PWM_NOT_INITED;
  }
  pwms.at(sg_handle)->SetSignalParams(signal, SIG_GEN_PARAM_SIGNAL_TYPE, type);
  return SIG_GEN_OK;
}

SIG_GEN_StatusTypeDef SIG_GEN_SetCarrierAmp(SIG_GEN_HandleTypeDef* sg_handle, double value) {
  if(!pwms.count(sg_handle)) {
    return SIG_GEN_ERROR_PWM_NOT_INITED;
  }
  if(value > sg_handle->coeffs->amp_array[sg_handle->coeffs->amp_array_size-1].to) {
    return SIG_GEN_ERROR_AMPLITUDE_VALUE_ABOVE_MAX;
  }
  pwms.at(sg_handle)->SetSignalParams(SIG_GEN_CARRIER, SIG_GEN_PARAM_AMP, value);
  return SIG_GEN_OK;
}

SIG_GEN_StatusTypeDef SIG_GEN_SetFreq(SIG_GEN_HandleTypeDef* sg_handle, enSignals signal, double value) {
  double sample_rate = 
    sg_handle->coeffs ? 
      sg_handle->coeffs->freq_array[sg_handle->coeffs->freq_array_size-1].to * 2.
        : 1000.;
  if(value >= sample_rate / 2.) {
    return SIG_GEN_ERROR_SAMPLE_RATE_LESS_THAN_FREQ;
  }
  if(!pwms.count(sg_handle)) {
    return SIG_GEN_ERROR_PWM_NOT_INITED;
  }
  pwms.at(sg_handle)->SetSignalParams(signal, SIG_GEN_PARAM_FREQ, value);
  return SIG_GEN_OK;
}

SIG_GEN_StatusTypeDef SIG_GEN_SetAmpModDepth(SIG_GEN_HandleTypeDef* sg_handle, uint8_t percent) {
  if(!pwms.count(sg_handle)) {
    return SIG_GEN_ERROR_PWM_NOT_INITED;
  }
  pwms.at(sg_handle)->SetSignalParams(SIG_GEN_AMP_MOD, SIG_GEN_PARAM_AMP_DEPTH, percent);
  return SIG_GEN_OK;
}

SIG_GEN_StatusTypeDef SIG_GEN_SetFreqModSens(SIG_GEN_HandleTypeDef* sg_handle, uint8_t percent) {
  if(!pwms.count(sg_handle)) {
    return SIG_GEN_ERROR_PWM_NOT_INITED;
  }
  pwms.at(sg_handle)->SetSignalParams(SIG_GEN_FREQ_MOD, SIG_GEN_PARAM_FREQ_DEPTH, percent);
  return SIG_GEN_OK;
}

SIG_GEN_StatusTypeDef SIG_GEN_Run(SIG_GEN_HandleTypeDef* sg_handle) {
  if(!pwms.count(sg_handle)) {
    return SIG_GEN_ERROR_PWM_NOT_INITED;
  }
  pwms.at(sg_handle)->Run();
  return SIG_GEN_OK;
}
