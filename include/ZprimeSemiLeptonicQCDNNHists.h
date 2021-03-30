#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

class ZprimeSemiLeptonicQCDNNHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicQCDNNHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();

TH1F *QCD_out0;
uhh2::Event::Handle<double> h_NNoutputQCD;

  virtual ~ZprimeSemiLeptonicQCDNNHists();
};
                                          
