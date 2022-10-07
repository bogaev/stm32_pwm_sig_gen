#include "tim.h"

#include "App/pwm_os_tasks/pwm_os_tasks.hpp"
#include "App/pwm_controller/pwm_controller.hpp"

#include <memory>

extern TIM_HandleTypeDef htim14;

static PwmController* pwms[PWM_NUM];

void Run_PWM() {
  for(auto& pwm : pwms) {
    if(pwm) {
      pwm->Run();
    }
  }
}

void InitPwmControllers() {
//  const int DUTY_CYCLE_MIN = 50;
//  const int DUTY_CYCLE_MAX = 65;

  const int DUTY_CYCLE_MIN_PERCENT = 60;
  const int DUTY_CYCLE_MAX_PERCENT = 75;
  const float TIMER_PERIOD = 656.f;

//  static uint16_t dma_positive[DATA_BUFFER_SIZE] = {0};
//  static uint16_t dma_negative[DATA_BUFFER_SIZE] = {0};
//  static tdDataBuffers dma_buffers = { {dma_positive, dma_negative} };
    
  std::shared_ptr<Signal> carrier = Signal{}.Create(SIG_GEN_TYPE_SINUS);
//  std::shared_ptr<Signal> carrier = Signal{}.Create(SIG_GEN_TYPE_SQUARE);
//  std::shared_ptr<Signal> carrier = Signal{}.Create(SIG_GEN_TYPE_TRIANGLE);
//  std::shared_ptr<Signal> carrier = Signal{}.Create(SIG_GEN_TYPE_SAW);
  
//  std::shared_ptr<Signal> amp_mod = Signal{}.Create(SIG_GEN_TYPE_SINUS);
//  std::shared_ptr<Signal> amp_mod = Signal{}.Create(SIG_GEN_TYPE_SQUARE);
//  std::shared_ptr<Signal> amp_mod = Signal{}.Create(SIG_GEN_TYPE_TRIANGLE);
//  std::shared_ptr<Signal> amp_mod = Signal{}.Create(SIG_GEN_TYPE_SAW);
  
//  std::shared_ptr<Signal> freq_mod = Signal{}.Create(SIG_GEN_TYPE_SINUS);
//  std::shared_ptr<Signal> freq_mod = Signal{}.Create(SIG_GEN_TYPE_SQUARE);
//  std::shared_ptr<Signal> freq_mod = Signal{}.Create(SIG_GEN_TYPE_TRIANGLE);
//  std::shared_ptr<Signal> freq_mod = Signal{}.Create(SIG_GEN_TYPE_SAW);
  
  carrier->SetFreq(20);
//  amp_mod->SetFreq(1);
//  freq_mod->SetFreq(20);
  
  static SignalGenerator signal_generator(carrier);
//  static SignalGenerator signal_generator(carrier, amp_mod);
//  static SignalGenerator signal_generator(carrier, nullptr, freq_mod);
//  static SignalGenerator signal_generator(carrier, amp_mod, freq_mod);
  
  static PwmGenerator pwm_generator(signal_generator, 
                              {DUTY_CYCLE_MIN_PERCENT, DUTY_CYCLE_MAX_PERCENT, TIMER_PERIOD});

//  pwms[TIM1_CH_1_2_DMA] = new DMA_PwmController(&htim1, {TIM_CHANNEL_1, TIM_CHANNEL_2});
  pwms[TIM1_CH_1_2_DMA] = new IT_PwmController(&htim1, {TIM_CHANNEL_1, TIM_CHANNEL_2});
//  pwms[TIM2_CH_1_2_DMA] = new DMA_PwmController(&htim2, {TIM_CHANNEL_1, TIM_CHANNEL_2});
  pwms[TIM2_CH_1_2_DMA] = new IT_PwmController(&htim2, {TIM_CHANNEL_1, TIM_CHANNEL_2});
  pwms[TIM2_CH_3_4_IT] = new IT_PwmController(&htim2, {TIM_CHANNEL_3, TIM_CHANNEL_4});
  pwms[TIM3_CH_1_2_IT] = new IT_PwmController(&htim3, {TIM_CHANNEL_1, TIM_CHANNEL_2}, &pwm_generator);
//  pwms[TIM3_CH_3_4_DMA] = new DMA_PwmController(&htim3, {TIM_CHANNEL_3, TIM_CHANNEL_4});
  pwms[TIM3_CH_3_4_DMA] = new IT_PwmController(&htim3, {TIM_CHANNEL_3, TIM_CHANNEL_4});
//  pwms[TIM4_CH_1_2_DMA] = new DMA_PwmController(&htim4, {TIM_CHANNEL_1, TIM_CHANNEL_2});
  pwms[TIM4_CH_1_2_DMA] = new IT_PwmController(&htim4, {TIM_CHANNEL_1, TIM_CHANNEL_2});
  pwms[TIM8_CH_1_2_IT] = new IT_PwmController(&htim8, {TIM_CHANNEL_1, TIM_CHANNEL_2});
  pwms[TIM12_CH_1_2_IT] = new IT_PwmController(&htim12, {TIM_CHANNEL_1, TIM_CHANNEL_2});
//  , &pwm_generator
  for(auto& pwm : pwms) {
    if(pwm) {
      pwm->Start();
    }
  }
  HAL_TIM_Base_Start_IT(&DISCR_HTIM);
}
