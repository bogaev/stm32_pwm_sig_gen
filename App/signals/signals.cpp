#include "App\signals\signals.hpp"

/*
https://math.stackexchange.com/questions/178079/
integration-of-sawtooth-square-and-triangle-wave-functions
*/

double t_debug = 0;
double amp_debug = 0;

// class Signal --------------------------------------------------------------

Signal::Signal(uint32_t sample_timer_period)
  : sample_rate_(sample_timer_period)
{}

void Signal::SetParam(uint8_t param, double value) {
  if(param == (uint8_t)SIG_GEN_PARAM_AMP) {
    SetAmp(value);
  }
  if(param == (uint8_t)SIG_GEN_PARAM_FREQ) {
    SetFreq(value);
  }
}

Signal& Signal::SetAmp(double amp) {
  amp_ = amp;
  return *this;
}

Signal& Signal::SetFreq(double freq) {
  freq_ = freq;
  period_ = 1. / freq_;
  return *this;
}

Signal& Signal::SetPeriod(double period) {
  period_ = period;
  freq_ = 1. / period_;
  return *this;
}

Signal& Signal::SetFmodDepth(double mod_depth_percent) {
  fmod_depth_percent_ = (uint8_t) mod_depth_percent;
  return *this;
}

double Signal::GetAmp() {
  return amp_;
}

double Signal::GetFreq() {
  return freq_;
}
  
double Signal::GetPeriod() {
  return period_;
}

double Signal::GetModDepth() {
  return fmod_depth_percent_;
}

std::unique_ptr<Signal> Signal::Create(enSignalTypes sig_type) {
  if(sig_type == SIG_GEN_TYPE_NONE) {
    return nullptr;
  }
  else if(sig_type == SIG_GEN_TYPE_SINUS) {
    return std::make_unique<Sinus>(sample_rate_);
  }
  else if(sig_type == SIG_GEN_TYPE_SQUARE) {
    return std::make_unique<Square>(sample_rate_);
  }
  else if(sig_type == SIG_GEN_TYPE_TRIANGLE) {
    return std::make_unique<Triangle>(sample_rate_);
  }
  else if(sig_type == SIG_GEN_TYPE_SAW) {
    return std::make_unique<Saw>(sample_rate_);
  }
  return nullptr;
}

// class Sinus ---------------------------------------------------------------

Sinus::Sinus(uint32_t sample_timer_period)
  : Signal(sample_timer_period)
{}

double Sinus::GetValue(uint32_t point) {
  double t = (double)point / (double)sample_rate_;
  return amp_ * std::cos(2.*pi * freq_ * t);
}

double Sinus::FM(uint32_t point, Signal& fmod) {
  double t = (double)point / (double)sample_rate_;
  return amp_ * std::cos(2.*pi * freq_ * t
                         + (freq_ - fmod.GetFreq()) / fmod.GetFreq()
                         * (5.0 * fmod_depth_percent_ / 100.)
                         * fmod.GetIntegral(point));
}

double Sinus::GetIntegral(uint32_t point) {
  double t = (double)point / (double)sample_rate_;
  return std::sin(2.*pi * freq_ * t);
}

// class Square ---------------------------------------------------------------

Square::Square(uint32_t sample_timer_period)
  : Signal(sample_timer_period)
{}

double Square::GetValue(uint32_t point) {
  int sample = (int)point % (int)(period_ * (double)sample_rate_);
  double t = (double)sample / (double)sample_rate_;
  t_debug = t;
  return square(t);
}

double Square::FM(uint32_t point, Signal& /*fmod*/) {
  return this->GetValue(point);
}

double Square::GetIntegral(uint32_t point) {
  int sample = (int)point % (int)(period_ * (double)sample_rate_);
  double t = (double)sample / (double)sample_rate_;
  if (t < period_ / 2.) {
    return t;
  }
  return -t;
}

double Square::square(double t) {
  if (t < period_ / 2.) {
    amp_debug = amp_;
    return amp_;
  }
  amp_debug = -amp_;
  return -amp_;
}

// class Triangle -------------------------------------------------------------

Triangle::Triangle(uint32_t sample_timer_period)
  : Signal(sample_timer_period)
{}

double Triangle::GetValue(uint32_t point) {
  int sample = (int)point % (int)(period_ * (double)sample_rate_);
  double t = (double)sample / (double)sample_rate_;
  return amp_ * triangle(t);
}

double Triangle::FM(uint32_t point, Signal& /*fmod*/) {
  return this->GetValue(point);
}

double Triangle::GetIntegral(uint32_t point) {
  int sample = (int)point % (int)(period_ * (double)sample_rate_);
  double t = (double)sample / (double)sample_rate_;
  if (t < period_ / 2.) {
    return t * (2.*t / period_ - 1.);
  }
  return t * (3. - 2.*t / period_);
}

double Triangle::triangle(double t) {
  if (t < period_ / 2.) {
    return 4.*t / period_ - 1.;
  }
  return 3. - 4.*t / period_;
}

// class Saw ---------------------------------------------------------------

Saw::Saw(uint32_t sample_timer_period)
  : Signal(sample_timer_period)
{}

double Saw::GetValue(uint32_t point) {
  int sample = (int)point % (int)(period_ * (double)sample_rate_);
//  double t = period_ - (double)sample / (double)sample_rate_;
  double t = (double)sample / (double)sample_rate_;
  return amp_ * sawtooth(t);
}

double Saw::FM(uint32_t point, Signal& /*fmod*/) {
  return this->GetValue(point);
}

double Saw::GetIntegral(uint32_t point) {
  int sample = (int)point % (int)(period_ * (double)sample_rate_);
  double t = (double)sample / (double)sample_rate_;
  return t * (t - period_) / period_;
}

double Saw::sawtooth(double t) {
  return 2.*t / period_ - 1.;
}