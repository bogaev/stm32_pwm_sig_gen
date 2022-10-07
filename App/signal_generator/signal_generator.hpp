#ifndef _SIGNAL_GENERATOR_H_
#define _SIGNAL_GENERATOR_H_

#include "main.h"

#include "App\c_interface\sig_gen_interface.h"
#include "App\signals\signals.hpp"

#include <cmath>
#include <utility>
#include <memory>

class SignalGenerator {  
public:
  SignalGenerator(uint32_t sample_rate);
  
  explicit SignalGenerator(uint32_t sample_rate,
                           enSignalTypes carrier,
                           enSignalTypes amod = SIG_GEN_TYPE_NONE,
                           enSignalTypes fmod = SIG_GEN_TYPE_NONE);
  
  explicit SignalGenerator(uint32_t sample_rate,
                           std::shared_ptr<Signal> carrier, 
                           std::shared_ptr<Signal> amod = nullptr,
                           std::shared_ptr<Signal> fmod = nullptr);
  
  double GetValue();
  double GetAmp() const;
  double GetFreq() const;
  uint32_t GetSampleRate() const;
  
  void SetSignal(uint8_t signal, uint8_t param, double value);
  
private:
  void Reset();
  SignalGenerator& GenerateCarrier();
  SignalGenerator& AddAM();
  SignalGenerator& GenerateFM();
  
  const uint32_t sample_rate_;
    
  std::shared_ptr<Signal> carrier_;
  std::shared_ptr<Signal> amod_;   
  std::shared_ptr<Signal> fmod_;   
  
  uint8_t amod_depth_percent_ = 100;
  double value_ = 0;
  uint32_t sample_ = 0;
};

#endif // #ifndef _SIGNAL_GENERATOR_H_