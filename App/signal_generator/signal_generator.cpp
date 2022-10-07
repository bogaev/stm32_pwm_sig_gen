#include "App\signal_generator\signal_generator.hpp"

SignalGenerator::SignalGenerator(uint32_t sample_rate) 
  : sample_rate_(sample_rate),
    carrier_(Signal{sample_rate_}.Create(SIG_GEN_TYPE_NONE)),
    amod_(Signal{sample_rate_}.Create(SIG_GEN_TYPE_NONE)),
    fmod_(Signal{sample_rate_}.Create(SIG_GEN_TYPE_NONE))
{}

SignalGenerator::SignalGenerator(uint32_t sample_rate,
                                 enSignalTypes carrier,
                                 enSignalTypes amod,
                                 enSignalTypes fmod)
  : sample_rate_(sample_rate),
    carrier_(Signal{sample_rate_}.Create(carrier)),
    amod_(Signal{sample_rate_}.Create(amod)),
    fmod_(Signal{sample_rate_}.Create(fmod))
{}

SignalGenerator::SignalGenerator(uint32_t sample_rate,
                                 std::shared_ptr<Signal> carrier,
                                 std::shared_ptr<Signal> amod,
                                 std::shared_ptr<Signal> fmod)
  : sample_rate_(sample_rate),
    carrier_(carrier),
    amod_(amod),
    fmod_(fmod)
{}

double SignalGenerator::GetValue() {
  if (carrier_ && amod_ && fmod_) {
    GenerateFM().AddAM();
  }
  else if (carrier_ && amod_) {
    GenerateCarrier().AddAM();
  }
  else if (carrier_ && fmod_) {
    GenerateFM();
  }
  else if (carrier_) {
    GenerateCarrier();
  }
  else {
    value_ = 0;
  }
  ++sample_;
  return value_;
}

SignalGenerator& SignalGenerator::GenerateCarrier() {
  value_ = carrier_->GetValue(sample_);
  return *this;
}

SignalGenerator& SignalGenerator::AddAM() {
  value_ =  std::abs(value_)
              * ((1.-(double)amod_depth_percent_ / 100.)
                + ((double)amod_depth_percent_ / 100.)
                  * amod_->GetValue(sample_));
  return *this;
}

SignalGenerator& SignalGenerator::GenerateFM() {
  value_ = carrier_->FM(sample_, *fmod_);
  return *this;
}

double SignalGenerator::GetAmp() const {
  return carrier_->GetAmp();
}

double SignalGenerator::GetFreq() const {
  return carrier_->GetFreq();
}

uint32_t SignalGenerator::GetSampleRate() const {
  return sample_rate_;
}

void SignalGenerator::SetSignal(uint8_t signal, uint8_t param, double value) {
  Reset();
  if (signal == SIG_GEN_CARRIER) {
    if (param == SIG_GEN_PARAM_SIGNAL_TYPE) {
      carrier_ = Signal(sample_rate_).Create(static_cast<enSignalTypes>(value));
      return;
    }
    carrier_->SetParam(param, value);
  }
  else if (signal == SIG_GEN_AMP_MOD) {
    if (param == SIG_GEN_PARAM_AMP_DEPTH) {
      amod_depth_percent_ = (uint8_t) value;
      return;
    }
    if (param == SIG_GEN_PARAM_SIGNAL_TYPE) {
      amod_ = Signal(sample_rate_).Create(static_cast<enSignalTypes>(value));
      return;
    }
    amod_->SetParam(param, value);
  }
  else if (signal == SIG_GEN_FREQ_MOD) {
    if (param == SIG_GEN_PARAM_FREQ_DEPTH) {
      carrier_->SetFmodDepth(value);
      return;
    }
    if (param == SIG_GEN_PARAM_SIGNAL_TYPE) {
      fmod_ = Signal(sample_rate_).Create(static_cast<enSignalTypes>(value));
      return;
    }
    fmod_->SetParam(param, value);
  }
}

void SignalGenerator::Reset() {
  sample_ = 0;
  value_ = 0;
}
