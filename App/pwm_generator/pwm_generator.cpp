#include "App\pwm_generator\pwm_generator.hpp"

namespace pwm_gen {

PwmGenerator::PwmGenerator(SignalGenerator* sig_gen,
                           const PwmGenerator::Settings& duty_cycle_settings,
                           const SignalStabilizer::Settings& stabilizer_settings) 
  : sig_gen_(sig_gen),
    min_duty_cycle_(duty_cycle_settings.timer_period * duty_cycle_settings.min_percent / 100.),
    max_duty_cycle_(duty_cycle_settings.timer_period * duty_cycle_settings.max_percent / 100.),
    stabilizer_(stabilizer_settings.coeffs ?
                    std::make_unique<SignalStabilizer>(stabilizer_settings) : nullptr)
{}

void PwmGenerator::SetSignal(uint8_t signal, uint8_t param, double value) {
  Reset();
  sig_gen_->SetSignal(signal, param, value);
}

uint32_t PwmGenerator::GetValue() {
  double signal_value = sig_gen_->GetValue();
  uint32_t dc = (uint32_t)(GetMinDutyCycle()
                  + GetRangeDutyCycle()
                    * std::abs(signal_value));
  signal_value >= 0 ? is_neg_halfwave_ = 0 : is_neg_halfwave_ = 1;
  return dc;
}

uint8_t PwmGenerator::IsNegHalfwave() const {
  return is_neg_halfwave_;
}

double PwmGenerator::GetMinDutyCycle() const {
  return min_duty_cycle_ 
            * (stabilizer_ ? stabilizer_->GetFreqCoeff(sig_gen_->GetFreq()) : 1.);
}

double PwmGenerator::GetMaxDutyCycle() const {
  return max_duty_cycle_ 
            * (stabilizer_ ? stabilizer_->GetFreqCoeff(sig_gen_->GetFreq()) : 1.);
}

double PwmGenerator::GetRangeDutyCycle() const {
  return (GetMaxDutyCycle() - GetMinDutyCycle()) 
            * (stabilizer_ ? stabilizer_->GetAmpCoeff(sig_gen_->GetAmp()) : 1.);
}

void PwmGenerator::Reset() {
  is_neg_halfwave_ = 0;
}

}
