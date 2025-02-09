#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>


class ZprimeSemiLeptonicPreselectionHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicPreselectionHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();
  bool is_mc;

TH1F *N_jets,*N_genjets, *pt_jet, *pt_jet1, *pt_jet2, *pt_jet3, *eta_jet, *eta_jet1, *eta_jet2, *eta_jet3, *phi_jet, *phi_jet1, *phi_jet2, *phi_jet3, *m_jet, *m_jet1, *m_jet2, *m_jet3, *csv_jet, *csv_jet1, *csv_jet2, *csv_jet3, *N_bJets_loose, *N_bJets_med, *N_bJets_tight;

TH1F *N_mu, *pt_mu, *pt_mu1, *pt_mu2, *eta_mu, *eta_mu1, *eta_mu2, *phi_mu, *phi_mu1, *phi_mu2, *reliso_mu, *reliso_mu1, *reliso_mu2, *reliso_mu_rebin, *reliso_mu1_rebin, *reliso_mu2_rebin;

TH1F *N_ele, *pt_ele, *pt_ele1, *pt_ele2, *eta_ele, *eta_ele1, *eta_ele2, *phi_ele, *phi_ele1, *phi_ele2, *reliso_ele, *reliso_ele1, *reliso_ele2, *reliso_ele_rebin, *reliso_ele1_rebin, *reliso_ele2_rebin;

TH1F *M_mumu, *pt_Z, *N_Zcor, *M_ee, *dRmin_mu_jet, *dRmin_mu_jet_scaled, *dRmin_ele_jet, *dRmin_ele_jet_scaled, *ptrel_mu_jet, *ptrel_ele_jet, *dRmin_mu1_jet, *dRmin_mu1_jet_scaled, *dRmin_ele1_jet, *dRmin_ele1_jet_scaled, *ptrel_mu1_jet, *ptrel_ele1_jet;

TH1F *N_AK8CHSjets, *pt_AK8CHSjet, *pt_AK8CHSjet1, *pt_AK8CHSjet2, *pt_AK8CHSjet3, *eta_AK8CHSjet, *eta_AK8CHSjet1, *eta_AK8CHSjet2, *eta_AK8CHSjet3, *phi_AK8CHSjet, *phi_AK8CHSjet1, *phi_AK8CHSjet2, *phi_AK8CHSjet3, *mSD_AK8CHSjet, *mSD_AK8CHSjet1, *mSD_AK8CHSjet2, *mSD_AK8CHSjet3, *N_subjets_AK8CHSjet, *N_subjets_AK8CHSjet1, *N_subjets_AK8CHSjet2, *N_subjets_AK8CHSjet3, *N_daughters_AK8CHSjet, *N_daughters_AK8CHSjet1, *N_daughters_AK8CHSjet2, *N_daughters_AK8CHSjet3, *dRmin_AK8Puppi_AK8CHSjet, *dRmin_AK8Puppi_AK8CHSjet1, *dRmin_AK8Puppi_AK8CHSjet2, *dRmin_AK8Puppi_AK8CHSjet3, *dRmin_mu_AK8CHSjet, *dRmin_mu_AK8CHSjet1, *dRmin_mu_AK8CHSjet2, *dRmin_mu_AK8CHSjet3, *tau1_AK8CHSjet, *tau1_AK8CHSjet1, *tau1_AK8CHSjet2, *tau1_AK8CHSjet3, *tau2_AK8CHSjet, *tau2_AK8CHSjet1, *tau2_AK8CHSjet2, *tau2_AK8CHSjet3, *tau3_AK8CHSjet, *tau3_AK8CHSjet1, *tau3_AK8CHSjet2, *tau3_AK8CHSjet3, *tau21_AK8CHSjet, *tau21_AK8CHSjet1, *tau21_AK8CHSjet2, *tau21_AK8CHSjet3, *tau32_AK8CHSjet, *tau32_AK8CHSjet1, *tau32_AK8CHSjet2, *tau32_AK8CHSjet3;

TH1F *N_AK8Puppijets, *pt_AK8Puppijet, *pt_AK8Puppijet1, *pt_AK8Puppijet2, *pt_AK8Puppijet3, *eta_AK8Puppijet, *eta_AK8Puppijet1, *eta_AK8Puppijet2, *eta_AK8Puppijet3, *phi_AK8Puppijet, *phi_AK8Puppijet1, *phi_AK8Puppijet2, *phi_AK8Puppijet3, *mSD_AK8Puppijet, *mSD_AK8Puppijet1, *mSD_AK8Puppijet2, *mSD_AK8Puppijet3, *N_subjets_AK8Puppijet, *N_subjets_AK8Puppijet1, *N_subjets_AK8Puppijet2, *N_subjets_AK8Puppijet3, *N_daughters_AK8Puppijet, *N_daughters_AK8Puppijet1, *N_daughters_AK8Puppijet2, *N_daughters_AK8Puppijet3, *dRmin_AK8CHS_AK8Puppijet, *dRmin_AK8CHS_AK8Puppijet1, *dRmin_AK8CHS_AK8Puppijet2, *dRmin_AK8CHS_AK8Puppijet3, *dRmin_mu_AK8Puppijet, *dRmin_mu_AK8Puppijet1, *dRmin_mu_AK8Puppijet2, *dRmin_mu_AK8Puppijet3, *tau1_AK8Puppijet, *tau1_AK8Puppijet1, *tau1_AK8Puppijet2, *tau1_AK8Puppijet3, *tau2_AK8Puppijet, *tau2_AK8Puppijet1, *tau2_AK8Puppijet2, *tau2_AK8Puppijet3, *tau3_AK8Puppijet, *tau3_AK8Puppijet1, *tau3_AK8Puppijet2, *tau3_AK8Puppijet3, *tau21_AK8Puppijet, *tau21_AK8Puppijet1, *tau21_AK8Puppijet2, *tau21_AK8Puppijet3, *tau32_AK8Puppijet, *tau32_AK8Puppijet1, *tau32_AK8Puppijet2, *tau32_AK8Puppijet3;

TH1F *NPV, *MET, *MET_rebin, *MET_rebin2, *MET_rebin3, *ST, *ST_rebin, *ST_rebin2, *ST_rebin3, *STjets, *STjets_rebin, *STjets_rebin2, *STjets_rebin3, *STlep, *STlep_rebin, *STlep_rebin2, *STlep_rebin3, *S11, *S12, *S13, *S22, *S23, *S33, *sum_event_weights;

TH2F *dRmin_ptrel_mu, *dRmin_ptrel_mu1, *dRmin_ptrel_ele, *dRmin_ptrel_ele1;

  virtual ~ZprimeSemiLeptonicPreselectionHists();
};
