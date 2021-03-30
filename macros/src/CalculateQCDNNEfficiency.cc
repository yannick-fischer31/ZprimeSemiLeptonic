#include "../include/cosmetics.h"
#include "../include/Tools.h"
#include <TString.h>
#include <iostream>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TText.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>

using namespace std;

void CalculateQCDNNEfficiency(){

  //vector<TString> samples = {"DY", "Diboson","QCD","ST","TTbar","WJets","ZprimeToTTJet_M750_2018","ZprimeToTTJet_M1000_2018","ZprimeToTTJet_M2000_2018"};
  vector<TString> samples = {"QCD","TTbar","WJets","ZprimeToTTJet_M750_2018","ZprimeToTTJet_M1000_2018","ZprimeToTTJet_M2000_2018","ZprimeToTTJet_M3000_2018"};

  TString filename_base = "/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_Original/ZPrime_2018/Analysis_applyQCD_score/muon";
  filename_base += "/NOMINAL/uhh2.AnalysisModuleRunner.MC.";

  //vector<float> DY,Diboson,QCD,ST,TTbar,WJets,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018;
  //vector<vector<float>> vec_samples = {DY,Diboson,QCD,ST,TTbar,WJets,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018};
  vector<float> QCD,TTbar,WJets,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018,ZprimeToTTJet_M3000_2018;
  vector<vector<float>> vec_samples = {QCD,TTbar,WJets,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018,ZprimeToTTJet_M3000_2018};

for(unsigned int j=0; j<samples.size(); j++){

    TString filename = filename_base + samples.at(j) + ".root";

    TFile* f_in = new TFile(filename, "READ");

    // Get number of events, matchable, and correctly matched before and after the chi2
    float n_Muon2     = ((TH1F*)(f_in->Get("Muon2_General/sum_event_weights")))->Integral();
    float n_QCD_output1 = ((TH1F*)(f_in->Get("QCD_output1_General/sum_event_weights")))->Integral();

    // Calculate fractions
    float frac_Muon2 = n_Muon2 / n_Muon2;
    vec_samples[j].emplace_back(frac_Muon2);

    float frac_QCD_output1 = n_QCD_output1 / n_Muon2;
    vec_samples[j].emplace_back(frac_QCD_output1);

    //cout << "Sample = " << samples.at(2) << endl;
    //for (unsigned int i=0; i<vec_samples[2].size(); i++){
    //   cout << " all eff= " << vec_samples[2][i] << endl;
    //}

    cout << "Sample = " << samples.at(j) << endl;
    cout << "Initial number events = " << n_Muon2 << endl;
    cout << "Final frac events = " << frac_QCD_output1 << endl;

    delete f_in;
  }

  // Plot cutflow
/*
   //vector<int> colors = {400,880,867,860,810,416,1,920,922};
   vector<int> colors = {867,810,416,1,920,922};

   //TGraphErrors* cutflow_DY = new TGraphErrors();
   //TGraphErrors* cutflow_Diboson = new TGraphErrors();
   TGraphErrors* cutflow_QCD = new TGraphErrors();
   //TGraphErrors* cutflow_ST = new TGraphErrors();
   TGraphErrors* cutflow_TTbar = new TGraphErrors();
   TGraphErrors* cutflow_WJets = new TGraphErrors();
   TGraphErrors* cutflow_ZprimeToTTJet_M750_2018 = new TGraphErrors();
   TGraphErrors* cutflow_ZprimeToTTJet_M1000_2018 = new TGraphErrors();
   TGraphErrors* cutflow_ZprimeToTTJet_M2000_2018 = new TGraphErrors();

   //vector<TGraphErrors*> graphs = {cutflow_DY, cutflow_Diboson, cutflow_QCD, cutflow_ST, cutflow_TTbar, cutflow_WJets, cutflow_ZprimeToTTJet_M750_2018, cutflow_ZprimeToTTJet_M1000_2018, cutflow_ZprimeToTTJet_M2000_2018};
   vector<TGraphErrors*> graphs = {cutflow_QCD, cutflow_TTbar, cutflow_WJets, cutflow_ZprimeToTTJet_M750_2018, cutflow_ZprimeToTTJet_M1000_2018, cutflow_ZprimeToTTJet_M2000_2018};

  TCanvas* c = new TCanvas("c", "c", 600, 600);
  c->SetLogy();
  c->SetRightMargin(0.02);
  c->SetTopMargin(0.02);
 
  vector<TString> labels = {"Nominal", "QCD_output1"}; 

  for (unsigned int j=0; j<graphs.size(); j++){
     for (unsigned int i=0; i<vec_samples[j].size(); i++){
       graphs[j]->SetPoint(i,i+0.5,vec_samples[j][i]);
       graphs[j]->SetPointError(i,0.5,0);
       graphs[j]->SetLineWidth(2);
       graphs[j]->SetLineColor(colors[j]);
     }
  }


  for (unsigned int k=0; k<labels.size(); k++){
    TAxis *ax = cutflow_QCD->GetHistogram()->GetXaxis();
    double x1 = ax->GetBinLowEdge(1);
    double x2 = ax->GetBinUpEdge(ax->GetNbins());
    cutflow_QCD->GetHistogram()->GetXaxis()->Set(2,x1,x2);
    cutflow_QCD->GetXaxis()->SetLabelSize(0.06);
    cutflow_QCD->GetXaxis()->SetBinLabel(k+1,labels[k]);
  }

  cutflow_QCD->GetXaxis()->SetNdivisions(505);
  cutflow_QCD->GetYaxis()->SetRangeUser(0.001,1.3);
  cutflow_QCD->GetYaxis()->SetTitle("Efficiency");
  cutflow_QCD->GetYaxis()->SetTitleSize(0.042);
  cutflow_QCD->GetYaxis()->SetTitleOffset(1.2);  
  cutflow_QCD->Draw("AP"); 
  //cutflow_Diboson->Draw("Psame"); 
  //cutflow_DY->Draw("Psame"); 
  //cutflow_ST->Draw("Psame"); 
  cutflow_TTbar->Draw("Psame"); 
  cutflow_WJets->Draw("Psame"); 
  cutflow_ZprimeToTTJet_M750_2018->Draw("Psame"); 
  cutflow_ZprimeToTTJet_M1000_2018->Draw("Psame"); 
  cutflow_ZprimeToTTJet_M2000_2018->Draw("Psame"); 


  TLegend* leg1 = new TLegend(0.2, 0.2, 0.5, 0.5);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.042);
  //leg1->AddEntry(cutflow_DY, "DY", "L");
  //leg1->AddEntry(cutflow_Diboson, "Diboson", "L");
  leg1->AddEntry(cutflow_QCD, "QCD", "L");
  //leg1->AddEntry(cutflow_ST, "ST", "L");
  leg1->AddEntry(cutflow_TTbar, "TTbar", "L");
  leg1->AddEntry(cutflow_WJets, "WJets", "L");
  leg1->AddEntry(cutflow_ZprimeToTTJet_M750_2018, "Z' TTJet M750", "L");
  leg1->AddEntry(cutflow_ZprimeToTTJet_M1000_2018, "Z' TTJet M1000", "L");
  leg1->AddEntry(cutflow_ZprimeToTTJet_M2000_2018, "Z' TTJet M2000", "L");
  leg1->Draw("SAME");


  c->SaveAs("cutflow_QCD.pdf");
  delete c;

  //delete cutflow_DY;
  //delete cutflow_Diboson;
  delete cutflow_QCD;
  //delete cutflow_ST;
  delete cutflow_TTbar;
  delete cutflow_WJets;
  delete cutflow_ZprimeToTTJet_M750_2018;
  delete cutflow_ZprimeToTTJet_M1000_2018;
  delete cutflow_ZprimeToTTJet_M2000_2018;
*/
}
