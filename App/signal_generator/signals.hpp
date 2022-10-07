#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include "App/sig_gen_interface.h"

#include <cmath>
#include <memory>
#include "../common.h"

const float pi = std::acos(-1);

class Signal {
public:
  Signal(uint32_t sample_timer_period);
  virtual ~Signal() {};
  void SetParam(uint8_t param, uint16_t value);
  
  Signal& SetAmp(float amp);
  Signal& SetFreq(float freq);
  Signal& SetPeriod(float period);
  Signal& SetModIndex(float mod_index);
  
  float GetAmp();
  float GetFreq();
  float GetPeriod();
  float GetModIndex();
  
  std::unique_ptr<Signal> Create(enSignalTypes sig_type);
  
  virtual float operator()(uint32_t point) { return 0; };
  virtual float FM(uint32_t point, Signal& sig) { return 0; };
  virtual float GetIntegral(uint32_t point) { return 0; };

protected:
  float freq_ = 1.;
  float period_ = 1.;
  float amp_ = 1.;
  float mod_index_ = 1.;
};

class Sinus : public Signal {
public:
  Sinus(uint32_t sample_timer_period);
  float operator()(uint32_t point) override;
  float FM(uint32_t point, Signal& fmod) override;
  float GetIntegral(uint32_t point) override;
};

class Square : public Signal {
public:
  Square(uint32_t sample_timer_period);
  float operator()(uint32_t point) override;
  float FM(uint32_t point, Signal& fmod) override;
  float GetIntegral(uint32_t point) override;
  
private:
  float square(float t);
};

class Triangle : public Signal {
public:
  Triangle(uint32_t sample_timer_period);
  float operator()(uint32_t point) override;
  float FM(uint32_t point, Signal& fmod) override;
  float GetIntegral(uint32_t point) override;
  
private:
  float triangle(float t);
};

class Saw : public Signal {
public:
  Saw(uint32_t sample_timer_period);
  float operator()(uint32_t point) override;
  float FM(uint32_t point, Signal& fmod) override;
  float GetIntegral(uint32_t point) override;
  
private:
  float sawtooth(float t);
};

#endif // #ifndef _SIGNALS_H_