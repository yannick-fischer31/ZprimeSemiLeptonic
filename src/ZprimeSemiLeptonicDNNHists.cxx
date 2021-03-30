#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicDNNHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;

ZprimeSemiLeptonicDNNHists::ZprimeSemiLeptonicDNNHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {

  h_NNoutput0 = ctx.get_handle<double>("NNoutput0");
  init();
}

void ZprimeSemiLeptonicDNNHists::init(){

QCD_out0 = book<TH1F>("QCD_out0", "QCD NN output 0", 100, 0, 1);
}

void ZprimeSemiLeptonicDNNHists::fill(const Event & event){

double weight = event.weight;
double NNoutput0= event.get(h_NNoutput0);

QCD_out0->Fill(NNoutput0, weight);

}

ZprimeSemiLeptonicDNNHists::~ZprimeSemiLeptonicDNNHists(){}
