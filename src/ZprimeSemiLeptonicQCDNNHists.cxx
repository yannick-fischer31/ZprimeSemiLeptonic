#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicQCDNNHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;

ZprimeSemiLeptonicQCDNNHists::ZprimeSemiLeptonicQCDNNHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {

  h_NNoutputQCD = ctx.get_handle<double>("NNoutputQCD");
  init();
}

void ZprimeSemiLeptonicQCDNNHists::init(){

QCD_out0 = book<TH1F>("QCD_out0", "QCD NN output 0", 100, 0, 1);
}

void ZprimeSemiLeptonicQCDNNHists::fill(const Event & event){

double weight = event.weight;
double NNoutputQCD = event.get(h_NNoutputQCD);

QCD_out0->Fill(NNoutputQCD, weight);

}

ZprimeSemiLeptonicQCDNNHists::~ZprimeSemiLeptonicQCDNNHists(){}
