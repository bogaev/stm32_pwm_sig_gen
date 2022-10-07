#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include "App\c_interface\sig_gen_interface.h"

#include <cmath>
#include <memory>

const double pi = std::acos(-1);

class Signal {
public:
  Signal(uint32_t sample_timer_period);
  virtual ~Signal() {};
  void SetParam(uint8_t param, double value);
  
  Signal& SetAmp(double amp);
  Signal& SetFreq(double freq);
  Signal& SetPeriod(double period);
  Signal& SetFmodDepth(double mod_depth_percent);
  
  double GetAmp();
  double GetFreq();
  double GetPeriod();
  double GetModDepth();
  
  std::unique_ptr<Signal> Create(enSignalTypes sig_type);
  
  virtual double GetValue(uint32_t point) { return 0; };
  virtual double FM(uint32_t point, Signal& sig) { return 0; };
  virtual double GetIntegral(uint32_t point) { return 0; };

protected:
  const uint32_t sample_rate_;
  uint8_t fmod_depth_percent_ = 100;
  double freq_ = 1.;
  double period_ = 1.;
  double amp_ = 1.;
};

class Sinus : public Signal {
public:
  Sinus(uint32_t sample_timer_period);
  double GetValue(uint32_t point) override;
  double FM(uint32_t point, Signal& fmod) override;
  double GetIntegral(uint32_t point) override;
};

class Square : public Signal {
public:
  Square(uint32_t sample_timer_period);
  double GetValue(uint32_t point) override;
  double FM(uint32_t point, Signal& fmod) override;
  double GetIntegral(uint32_t point) override;
  
private:
  double square(double t);
};

class Triangle : public Signal {
public:
  Triangle(uint32_t sample_timer_period);
  double GetValue(uint32_t point) override;
  double FM(uint32_t point, Signal& fmod) override;
  double GetIntegral(uint32_t point) override;
  
private:
  double triangle(double t);
};

class Saw : public Signal {
public:
  Saw(uint32_t sample_timer_period);
  double GetValue(uint32_t point) override;
  double FM(uint32_t point, Signal& fmod) override;
  double GetIntegral(uint32_t point) override;
  
private:
  double sawtooth(double t);
};

#endif // #ifndef _SIGNALS_H_