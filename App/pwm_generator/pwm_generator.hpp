#ifndef _PWM_GENERATOR_H_
#define _PWM_GENERATOR_H_

#include "main.h"
#include <cmath>
#include <memory>

#include "App\signal_generator\signal_generator.hpp"
#include "App\c_interface\sig_gen_interface.h"

namespace pwm_gen {

const double amp_coeff[3][2] = {
  { 1.0f, 0.15f },
  { 0.6f, 1.7f },
  { 0.45f, 1.7f }
};

class SignalStabilizer final {
public:
  struct Settings {
    const SIG_GEN_CoeffsInitStruct* coeffs = nullptr;
  };
  
  SignalStabilizer(const SignalStabilizer::Settings& settings)
    : coeffs_(settings.coeffs),
      max_amp_(coeffs_->amp_array[coeffs_->freq_array_size-1].to),
      max_freq_(coeffs_->freq_array[coeffs_->freq_array_size-1].to)
  {}
  
  double GetAmpCoeff(double current_amp) const {
//    return (1.f - coeffs_->amp_array[0].coeff)
//              + (current_amp / max_amp_)
//                * coeffs_->amp_array[0].coeff;
    return GetCoeff(current_amp,
                    coeffs_->amp_array,
                    coeffs_->amp_array_size);
  }

  double GetFreqCoeff(double current_freq) const {
    return GetCoeff(current_freq,
                    coeffs_->freq_array,
                    coeffs_->freq_array_size);
  }
  
private:
  double GetCoeff(double value, SIG_GEN_RangeCoeff* array, uint32_t size) const {
    for (uint32_t i = 0; i < size; ++i) {
      if (value >= array[i].from && value < array[i].to) {
        return array[i].coeff;
      }
      if (i == size-1 && value >= array[i].from && value <= array[i].to) {
        return array[i].coeff;
      }
    }
    return 1.f;
  }
  
  const SIG_GEN_CoeffsInitStruct* coeffs_;
  const double max_amp_;
  const double max_freq_;
};

class PwmGenerator final {
public:
  struct Settings {
    double min_percent;
    double max_percent;
    double timer_period;
  };
  
  PwmGenerator(SignalGenerator* sig_gen,
               const PwmGenerator::Settings& duty_cycle_settings,
               const SignalStabilizer::Settings& stabilizer_settings);
  
  void SetSignal(uint8_t signal, uint8_t param, double value);
  uint32_t GetValue();
  uint8_t IsNegHalfwave() const;
  
private:
  double GetMinDutyCycle() const;
  double GetMaxDutyCycle() const;
  double GetRangeDutyCycle() const;
  void Reset();

  std::shared_ptr<SignalGenerator> sig_gen_;
  const double min_duty_cycle_;
  const double max_duty_cycle_;
  const std::shared_ptr<SignalStabilizer> stabilizer_;
  
  uint8_t is_neg_halfwave_ = 0;
};

}

#endif // #ifndef _PWM_GENERATOR_H_