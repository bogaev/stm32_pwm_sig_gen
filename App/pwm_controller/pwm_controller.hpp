#ifndef _PWM_CONTROLLER_H_
#define _PWM_CONTROLLER_H_

#include "App\signals\signals.hpp"
#include "App\pwm_generator\pwm_generator.hpp"

#include <memory>

struct tdPwmChannels {
  uint32_t pos_halfwave_channel;
  uint32_t neg_halfwave_channel;
};

class PwmController {
public:
    PwmController(TIM_HandleTypeDef* timer,
                  tdPwmChannels channels,
                  pwm_gen::PwmGenerator* generator);
    virtual ~PwmController() {};
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Run() = 0;
    void SetSignalParams(uint8_t signal, uint8_t param, double value);
    
protected:  
    TIM_HandleTypeDef* timer_ = nullptr;
    tdPwmChannels channels_;
    std::unique_ptr<pwm_gen::PwmGenerator> generator_;
};

class IT_PwmController : public PwmController {    
public:
    IT_PwmController(TIM_HandleTypeDef* timer,
                     tdPwmChannels channels,
                     pwm_gen::PwmGenerator* generator);
    virtual ~IT_PwmController();
    void Start() override;
    void Stop() override;
    void Run() override;
};

#endif // #ifndef _SIN_H_