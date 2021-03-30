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
#include <TMath.h>
#include <fstream>

using namespace std;

void CalculateQCDNNCut(){

  //vector<TString> samples = {"DY", "Diboson","QCD","ST","TTbar","WJets","ZprimeToTTJet_M750_2018","ZprimeToTTJet_M1000_2018","ZprimeToTTJet_M2000_2018"};
  vector<TString> samples = {"QCD","AllBkg","OtherBkg","ZprimeToTTJet_M750_2018","ZprimeToTTJet_M1000_2018","ZprimeToTTJet_M2000_2018","ZprimeToTTJet_M3000_2018"};

  TString filename_base = "/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_Original/ZPrime_2018/Analysis_applyQCD_score/muon";
  filename_base += "/NOMINAL/uhh2.AnalysisModuleRunner.MC.";

  //vector<float> DY,Diboson,QCD,ST,TTbar,WJets,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018;
  //vector<vector<float>> vec_samples = {DY,Diboson,QCD,ST,TTbar,WJets,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018};
  vector<float> QCD,AllBkg,OtherBkg,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018,ZprimeToTTJet_M3000_2018;
  vector<vector<float>> vec_samples = {QCD,AllBkg,OtherBkg,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018,ZprimeToTTJet_M3000_2018};
  vector<vector<float>> num_samples = {QCD,AllBkg,OtherBkg,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018,ZprimeToTTJet_M3000_2018};

for(unsigned int j=0; j<samples.size(); j++){

    TString filename = filename_base + samples.at(j) + ".root";

    TFile* f_in = new TFile(filename, "READ");

    float n_cut_i[101];
    float frac_cut_i[101];

    TH1F* h_score = (TH1F*)f_in->Get("QCDNN/QCD_out0");
    float n_tot = h_score->Integral(0,100);
    float n_cut95 = h_score->Integral(0,95);

    for(unsigned int k=0; k<101; k++){
       n_cut_i[k] = h_score->Integral(0,k);
       frac_cut_i[k] = n_cut_i[k]/n_tot;
       vec_samples[j].emplace_back(frac_cut_i[k]);
       num_samples[j].emplace_back(n_cut_i[k]);
    }


    delete f_in;
  }


  //cout << "Sample = " << samples.at(1) << endl;
  ////for(unsigned int j=3; j<6; j++){
  //  cout << "Sig = " << samples.at(3) << endl;
  //  for(unsigned int i=0; i<vec_samples[1].size(); i++){
  //    //cout << " cut " << i << " frac = " << vec_samples[2][i]  << " num events " << num_samples[2][i] << endl;
  //    cout << " frac bkg events " << vec_samples[1][i] << endl;
  //    cout << " frac sig events " << vec_samples[3][i] << endl;
  //    //cout << " S/sqrt(S+B) " << (num_samples[3][i])/sqrt(num_samples[3][i]+num_samples[1][i]) << endl;
  //  }


  // PLOT ROC

  TGraph* roc_s1 = new TGraph();
  TGraph* roc_s2 = new TGraph();
  TGraph* roc_s3 = new TGraph();
  TGraph* roc_s4 = new TGraph();
 
  vector<int> colors = {867,810,416,880};

  vector<TGraph*> rocs  = {roc_s1, roc_s2, roc_s3,roc_s4};
  TGraph* twod_s1 = new TGraph();
  TGraph* twod_s2 = new TGraph();
  TGraph* twod_s3 = new TGraph();
  TGraph* twod_s4 = new TGraph();


  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);
  c2->SetLogy();
  //c2->SetLogx();
  c2->SetRightMargin(0.05);
  c2->SetLeftMargin(0.1);
  c2->SetTopMargin(0.02);

for (unsigned int j=0; j<rocs.size(); j++){
  for (unsigned int i=0; i<vec_samples[1].size(); i++){
    rocs[j]->SetPoint(i,vec_samples[j+3][i],vec_samples[0][i]);
    rocs[j]->SetLineWidth(2);
    rocs[j]->SetLineColor(colors[j]);
    rocs[j]->GetXaxis()->SetLimits(0.0,1.0);
  }
}


  twod_s1->SetPoint(0, 0.8247, 0.0187015);
  twod_s1->SetMarkerColor(colors[0]);
  twod_s2->SetPoint(0, 0.759444, 0.0187015);
  twod_s2->SetMarkerColor(colors[1]);
  twod_s3->SetPoint(0, 0.668526, 0.0187015);
  twod_s3->SetMarkerColor(colors[2]);
  twod_s4->SetPoint(0, 0.6284, 0.0187015);
  twod_s4->SetMarkerColor(colors[3]);

  twod_s1->SetMarkerStyle(47);
  twod_s1->SetMarkerSize(2);
  twod_s2->SetMarkerStyle(47);
  twod_s2->SetMarkerSize(2);
  twod_s3->SetMarkerStyle(47);
  twod_s3->SetMarkerSize(2);
  twod_s4->SetMarkerStyle(47);
  twod_s4->SetMarkerSize(2);

  roc_s1->GetYaxis()->SetRangeUser(0.001,1.3);
  roc_s1->GetYaxis()->SetTitle("#varepsilon_{B}");
  roc_s1->GetXaxis()->SetTitle("#varepsilon_{S}");
  roc_s1->GetYaxis()->SetTitleSize(0.05);
  roc_s1->GetXaxis()->SetTitleSize(0.05);
  roc_s1->GetYaxis()->SetTitleOffset(0.9);  
  roc_s1->GetXaxis()->SetTitleOffset(0.9);  
  roc_s1->Draw();
  roc_s2->Draw("same");
  roc_s3->Draw("same");
  roc_s4->Draw("same");

  twod_s1->Draw("Psame");
  twod_s2->Draw("Psame");
  twod_s3->Draw("Psame");
  twod_s4->Draw("Psame");

  TLegend* leg2 = new TLegend(0.2, 0.75, 0.4, 0.9);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.04);
  leg2->AddEntry(roc_s1, "QCD NN,", "L");
  leg2->AddEntry(roc_s2, "QCD NN,", "L");
  leg2->AddEntry(roc_s3, "QCD NN,", "L");
  leg2->AddEntry(roc_s4, "QCD NN,", "L");
  leg2->Draw("SAME");

  TLegend* leg3 = new TLegend(0.4, 0.75, 0.7, 0.9);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.04);
  leg3->AddEntry(twod_s1, "2D cut - Z' M750", "P");
  leg3->AddEntry(twod_s2, "2D cut - Z' M1000", "P");
  leg3->AddEntry(twod_s3, "2D cut - Z' M2000", "P");
  leg3->AddEntry(twod_s4, "2D cut - Z' M3000", "P");
  leg3->Draw("SAME");


  c2->SaveAs("roc.pdf");
  delete c2;








  // Plot cutflow
/*
   vector<int> colors = {867,810,416,1,920,922};

   TGraphErrors* cutflow_QCD = new TGraphErrors();
   TGraphErrors* cutflow_AllBkg = new TGraphErrors();
   TGraphErrors* cutflow_OtherBkg = new TGraphErrors();
   TGraphErrors* cutflow_ZprimeToTTJet_M750_2018 = new TGraphErrors();
   TGraphErrors* cutflow_ZprimeToTTJet_M1000_2018 = new TGraphErrors();
   TGraphErrors* cutflow_ZprimeToTTJet_M2000_2018 = new TGraphErrors();

   vector<TGraphErrors*> graphs = {cutflow_QCD, cutflow_AllBkg, cutflow_OtherBkg, cutflow_ZprimeToTTJet_M750_2018, cutflow_ZprimeToTTJet_M1000_2018, cutflow_ZprimeToTTJet_M2000_2018};

  TCanvas* c = new TCanvas("c", "c", 600, 600);
  c->SetLogy();
  c->SetRightMargin(0.05);
  c->SetLeftMargin(0.1);
  c->SetTopMargin(0.02);
 
  vector<TString> labels = {"cut1", "cut2","cut3","cut4","cut5","cut6","cut7","cut8","cut9","cut95", "no cut", ""}; 

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
    cutflow_QCD->GetHistogram()->GetXaxis()->Set(12,x1,x2);
    cutflow_QCD->GetXaxis()->SetLabelSize(0.06);
    cutflow_QCD->GetXaxis()->SetBinLabel(k+1,labels[k]);
  }

  cutflow_QCD->GetXaxis()->SetNdivisions(505);
  cutflow_QCD->GetYaxis()->SetRangeUser(0.001,1.3);
  cutflow_QCD->GetYaxis()->SetTitle("Efficiency");
  cutflow_QCD->GetYaxis()->SetTitleSize(0.042);
  cutflow_QCD->GetYaxis()->SetTitleOffset(1.2);  
  cutflow_QCD->Draw("AP"); 
  cutflow_AllBkg->Draw("Psame"); 
  cutflow_OtherBkg->Draw("Psame"); 
  cutflow_ZprimeToTTJet_M750_2018->Draw("Psame"); 
  cutflow_ZprimeToTTJet_M1000_2018->Draw("Psame"); 
  cutflow_ZprimeToTTJet_M2000_2018->Draw("Psame"); 


  TLegend* leg1 = new TLegend(0.2, 0.4, 0.5, 0.65);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(cutflow_QCD, "QCD", "L");
  leg1->AddEntry(cutflow_AllBkg, "AllBkg", "L");
  leg1->AddEntry(cutflow_OtherBkg, "OtherBkg", "L");
  leg1->AddEntry(cutflow_ZprimeToTTJet_M750_2018, "Z' TTJet M750", "L");
  leg1->AddEntry(cutflow_ZprimeToTTJet_M1000_2018, "Z' TTJet M1000", "L");
  leg1->AddEntry(cutflow_ZprimeToTTJet_M2000_2018, "Z' TTJet M2000", "L");
  leg1->Draw("SAME");


  c->SaveAs("cutflow_cuts.pdf");
  delete c;

  delete cutflow_QCD;
  delete cutflow_AllBkg;
  delete cutflow_OtherBkg;
  delete cutflow_ZprimeToTTJet_M750_2018;
  delete cutflow_ZprimeToTTJet_M1000_2018;
  delete cutflow_ZprimeToTTJet_M2000_2018;
*/
}
