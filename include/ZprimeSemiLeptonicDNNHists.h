#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

class ZprimeSemiLeptonicDNNHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicDNNHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();

TH1F *QCD_out0;
uhh2::Event::Handle<double> h_NNoutput0;

  virtual ~ZprimeSemiLeptonicDNNHists();
};
                                          
