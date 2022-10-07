#include "tim.h"

#include "App\pwm_controller\pwm_controller.hpp"

PwmController::PwmController(TIM_HandleTypeDef* timer,
                             tdPwmChannels channels,
                             pwm_gen::PwmGenerator* generator)
  : timer_(timer),
    generator_(generator)
{
  channels_.pos_halfwave_channel = channels.pos_halfwave_channel;
  channels_.neg_halfwave_channel = channels.neg_halfwave_channel;
}

void PwmController::SetSignalParams(uint8_t signal, uint8_t param, double value) {
  generator_->SetSignal(signal, param, value);
}

//class IT_PwmController ----------------------------------------------------

IT_PwmController::IT_PwmController(TIM_HandleTypeDef* timer,
                 tdPwmChannels channels,
                 pwm_gen::PwmGenerator* generator)
  : PwmController(timer, channels, generator)
{}

IT_PwmController::~IT_PwmController() {
  Stop();
}
  
void IT_PwmController::Start() {
  HAL_TIM_PWM_Start_IT(timer_, channels_.pos_halfwave_channel);
  HAL_TIM_PWM_Start_IT(timer_, channels_.neg_halfwave_channel);
}

void IT_PwmController::Stop() {
  HAL_TIM_PWM_Stop_IT(timer_, channels_.pos_halfwave_channel);
  HAL_TIM_PWM_Stop_IT(timer_, channels_.neg_halfwave_channel);
}

void IT_PwmController::Run() {
    uint16_t dc = generator_->GetValue();
    if(generator_->IsNegHalfwave()) {
      __HAL_TIM_SET_COMPARE(timer_,
                            channels_.pos_halfwave_channel, 0);
      __HAL_TIM_SET_COMPARE(timer_,
                            channels_.neg_halfwave_channel,
                            dc);
    }
    else {
      __HAL_TIM_SET_COMPARE(timer_,
                            channels_.neg_halfwave_channel, 0);
      __HAL_TIM_SET_COMPARE(timer_,
                            channels_.pos_halfwave_channel,
                            dc);
    }
}
