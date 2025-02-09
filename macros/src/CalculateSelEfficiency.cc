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

void CalculateSelEfficiency(){

  //vector<TString> samples = {"DY", "Diboson","QCD","ST","TTbar","WJets","ZprimeToTTJet_M750_2018","ZprimeToTTJet_M1000_2018","ZprimeToTTJet_M2000_2018"};
  vector<TString> samples = {"QCD","TTbar","WJets", "DY","TTZToLLNuNu_2018", "ST","Diboson","Delphes_2018_0" };

  TString filename_base = "/nfs/dust/cms/user/fischery/Analysis/CMSSW_10_2_17/src/UHH2/ZprimeSemiLeptonic/Preselection";
  //filename_base += "/NOMINAL_myselections/uhh2.AnalysisModuleRunner.MC.";
  filename_base += "/uhh2.AnalysisModuleRunner.MC.";

  //vector<float> DY,Diboson,QCD,ST,TTbar,WJets,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018;
  //vector<vector<float>> vec_samples = {DY,Diboson,QCD,ST,TTbar,WJets,ZprimeToTTJet_M750_2018,ZprimeToTTJet_M1000_2018,ZprimeToTTJet_M2000_2018};
  vector<float> QCD,TT,WJets,DY,TTZToLLNuNu_2018,ST,Diboson,Delphes_2018_0;
  vector<vector<float>> vec_samples = {QCD,TT,WJets,DY,TTZToLLNuNu_2018,ST,Diboson,Delphes_2018_0};
  vector<vector<float>> vec_samples_signal = {QCD,TT,WJets,DY,TTZToLLNuNu_2018,ST,Diboson,Delphes_2018_0};

//Get signal in every Cut
  TString filename = filename_base + samples.at(7) + ".root";

  TFile* f_in = new TFile(filename, "READ");
cout<<"Point1"<<endl;
  float n_Triggern     = ((TH1F*)(f_in->Get("CommonModules_General/sum_event_weights")))->Integral();
  float n_Lep1n        = ((TH1F*)(f_in->Get("Lepton1_General/sum_event_weights")))->Integral();
  float n_Lep2n         = ((TH1F*)(f_in->Get("Lepton2_General/sum_event_weights")))->Integral();
  float n_BTag1n       = ((TH1F*)(f_in->Get("Btag1_General/sum_event_weights")))->Integral();
  float n_BTag2n       = ((TH1F*)(f_in->Get("Btag2_General/sum_event_weights")))->Integral();
  float n_6Jetsn     = ((TH1F*)(f_in->Get("Njets6_General/sum_event_weights")))->Integral();
    float n_Zwindown     = ((TH1F*)(f_in->Get("Zwindow_General/sum_event_weights")))->Integral();
for(unsigned int j=0; j<samples.size(); j++){
cout<<"Point"<<j<<endl;
    TString filename = filename_base + samples.at(j) + ".root";

    TFile* f_in = new TFile(filename, "READ");

    // Get number of events, matchable, and correctly matched before and after the chi2
    float n_Trigger     = ((TH1F*)(f_in->Get("CommonModules_General/sum_event_weights")))->Integral();
    float n_Lep1        = ((TH1F*)(f_in->Get("Lepton1_General/sum_event_weights")))->Integral();
    float n_Lep2         = ((TH1F*)(f_in->Get("Lepton2_General/sum_event_weights")))->Integral();
    float n_BTag1       = ((TH1F*)(f_in->Get("Btag1_General/sum_event_weights")))->Integral();
    float n_BTag2       = ((TH1F*)(f_in->Get("Btag2_General/sum_event_weights")))->Integral();
    float n_6Jets     = ((TH1F*)(f_in->Get("Njets6_General/sum_event_weights")))->Integral();
    float n_Zwindow     = ((TH1F*)(f_in->Get("Zwindow_General/sum_event_weights")))->Integral();
    //float n_TwoDCut     = ((TH1F*)(f_in->Get("TwoDCut_General/sum_event_weights")))->Integral();



    // Calculate fractions
    float frac_Trigger = n_Trigger / n_Trigger;
    vec_samples[j].emplace_back(frac_Trigger);

    float frac_Lep1 = n_Lep1 / n_Trigger;
    vec_samples[j].emplace_back(frac_Lep1);

    float frac_Lep2 = n_Lep2 / n_Trigger;
    vec_samples[j].emplace_back(frac_Lep2);

    float frac_Zwindow = n_Zwindow/ n_Trigger;
    vec_samples[j].emplace_back(frac_Zwindow);

    float frac_BTag1 = n_BTag1 / n_Trigger;
    vec_samples[j].emplace_back(frac_BTag1);

    float frac_BTag2 = n_BTag2 / n_Trigger;
    vec_samples[j].emplace_back(frac_BTag2);

    float frac_6Jets = n_6Jets / n_Trigger;
    vec_samples[j].emplace_back(frac_6Jets);

    //Signal to background

    float frac_Triggern = n_Triggern / n_Triggern;
    vec_samples_signal[j].emplace_back(frac_Triggern);

    float frac_Lep1n = n_Lep1 / n_Lep1n;
    vec_samples_signal[j].emplace_back(frac_Lep1n);

    float frac_Lep2n = n_Lep2 / n_Lep2n;
    vec_samples_signal[j].emplace_back(frac_Lep2n);

    float frac_Zwindown= n_Zwindow/ n_Zwindown;
    vec_samples_signal[j].emplace_back(frac_Zwindown);

    float frac_BTag1n = n_BTag1 / n_BTag1n;
    vec_samples_signal[j].emplace_back(frac_BTag1n);

    float frac_BTag2n = n_BTag2 / n_BTag2n;
    vec_samples_signal[j].emplace_back(frac_BTag2n);

    float frac_6Jetsn = n_6Jets / n_6Jetsn;
    vec_samples_signal[j].emplace_back(frac_6Jetsn);



    //float frac_TwoDCut = n_TwoDCut / n_Trigger;
    //float frac_TwoDCut = n_TwoDCut / n_HTlep;
    //vec_samples[j].emplace_back(frac_TwoDCut);


    //cout << "Sample = " << samples.at(2) << endl;
    //for (unsigned int i=0; i<vec_samples[2].size(); i++){
    //   cout << " all eff= " << vec_samples[2][i] << endl;
    //}

    cout << "Sample = " << samples.at(j) << endl;
    cout << "Trigger number events = " << n_Trigger << endl;
    cout << "Lepton1 number events = "    << n_Lep1 << endl;
    cout << "Lepton2 number events = "     << n_Lep2 << endl;
    cout << "BTag2 number events = "   << n_BTag2<< endl;

    cout << "Signal to background for Sample = " << samples.at(j) << endl;
    cout << "Trigger number events = " << n_Triggern << endl;
    cout << "Lepton1 number events = "    << n_Lep1n << endl;
    cout << "Lepton2 number events = "     << n_Lep2n << endl;
        cout << "Zwindow number events = "   << frac_Zwindown<< endl;
    cout << "BTag2 number events = "   << n_BTag2n<< endl;
    cout<<"Ratio to TTZ for this sample is" << frac_Lep1n<<endl;
  //  cout << "TwoDCut number events = " << frac_TwoDCut << endl;

    delete f_in;
  }

  // Plot cutflow

   //vector<int> colors = {400,880,867,860,810,416,1,920,922};
   vector<int> colors = {867,810,400,410,600,6,432,1};

   //TGraphErrors* cutflow_DY = new TGraphErrors();
   //TGraphErrors* cutflow_Diboson = new TGraphErrors();
   TGraphErrors* cutflow_QCD = new TGraphErrors();
   //TGraphErrors* cutflow_ST = new TGraphErrors();
   TGraphErrors* cutflow_TT = new TGraphErrors();
   TGraphErrors* cutflow_WJets = new TGraphErrors();
   TGraphErrors* cutflow_DY = new TGraphErrors();
   TGraphErrors* cutflow_TTZToLLNuNu_2018 = new TGraphErrors();
   TGraphErrors* cutflow_ST = new TGraphErrors();
   TGraphErrors* cutflow_Diboson = new TGraphErrors();
   TGraphErrors* cutflow_Delphes_2018_0 = new TGraphErrors();
;

   //vector<TGraphErrors*> graphs = {cutflow_DY, cutflow_Diboson, cutflow_QCD, cutflow_ST, cutflow_TTbar, cutflow_WJets, cutflow_ZprimeToTTJet_M750_2018, cutflow_ZprimeToTTJet_M1000_2018, cutflow_ZprimeToTTJet_M2000_2018};
   vector<TGraphErrors*> graphs = {cutflow_QCD, cutflow_TT, cutflow_WJets, cutflow_DY, cutflow_TTZToLLNuNu_2018, cutflow_ST,cutflow_Diboson, cutflow_Delphes_2018_0 };

  TCanvas* c = new TCanvas("c", "c", 600, 600);
  c->SetLogy();
  c->SetRightMargin(0.02);
  c->SetTopMargin(0.02);

  //vector<TString> labels = {"Trigger", "Jet1", "MET", "HTlep", "TwoDCut"};
  vector<TString> labels = {"Input ","Lepton1", "Lepton2","Zwindow","Btag1", "Btag2", "6 Jets"};

  for (unsigned int j=0; j<graphs.size(); j++){
    //cout<<"jmax:"<<graphs.size()<<endl;
    //cout<<"vec_samples: "<<vec_samples[j].size()<<endl;
     for (unsigned int i=0; i<vec_samples[j].size(); i++){
//cout<<"j: "<<j<<" i: "<<i<<endl;

       graphs[j]->SetPoint(i,i+0.5,vec_samples[j][i]);
       graphs[j]->SetPointError(i,0.5,0);
       graphs[j]->SetLineWidth(2);
       graphs[j]->SetLineColor(colors[j]);
       cout<<colors[j]<<endl;
     }
  }


  for (unsigned int k=0; k<labels.size(); k++){
    TAxis *ax = cutflow_QCD->GetHistogram()->GetXaxis();
    double x1 = ax->GetBinLowEdge(1);
    double x2 = ax->GetBinUpEdge(ax->GetNbins());
    //cutflow_DY->GetHistogram()->GetXaxis()->Set(5,x1,x2);
    cutflow_QCD->GetHistogram()->GetXaxis()->Set(7,x1,x2);
    cutflow_QCD->GetXaxis()->SetLabelSize(0.06);
    cutflow_QCD->GetXaxis()->SetBinLabel(k+1,labels[k]);
  }

  cutflow_QCD->GetXaxis()->SetNdivisions(505);
  cutflow_QCD->GetYaxis()->SetRangeUser(0.00001,1.3);
  cutflow_QCD->GetYaxis()->SetTitle("Fraction of events passing selection");
  cutflow_QCD->GetYaxis()->SetTitleSize(0.042);
  cutflow_QCD->GetYaxis()->SetTitleOffset(1.2);
  cutflow_QCD->Draw("AP");
  //cutflow_Diboson->Draw("Psame");
  //cutflow_DY->Draw("Psame");
  //cutflow_ST->Draw("Psame");
  cutflow_TT->Draw("Psame");
  cutflow_WJets->Draw("Psame");
  cutflow_DY->Draw("Psame");
  cutflow_TTZToLLNuNu_2018->Draw("Psame");
  cutflow_ST->Draw("Psame");
  cutflow_Diboson->Draw("Psame");
  cutflow_Delphes_2018_0->Draw("Psame");


  TLegend* leg1 = new TLegend(0.2, 0.2, 0.5, 0.5);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.042);
  //leg1->AddEntry(cutflow_DY, "DY", "L");
  //leg1->AddEntry(cutflow_Diboson, "Diboson", "L");
  leg1->AddEntry(cutflow_QCD, "QCD", "L");
  //leg1->AddEntry(cutflow_ST, "ST", "L");
  leg1->AddEntry(cutflow_TT, "TT", "L");
  leg1->AddEntry(cutflow_WJets, "WJets", "L");
  leg1->AddEntry(cutflow_DY, "DY", "L");
  leg1->AddEntry(cutflow_TTZToLLNuNu_2018, "TTZ", "L");
  leg1->AddEntry(cutflow_ST, "ST", "L");
    leg1->AddEntry(cutflow_Diboson, "Diboson", "L");
        leg1->AddEntry(cutflow_Delphes_2018_0, "Delphes Signal", "L");
  leg1->Draw("SAME");

  c->SaveAs("cutflow_finalsel.pdf");
  delete c;


  //Draw Signal to background ratio

  TCanvas* d = new TCanvas("d", "d", 600, 600);
  d->SetLogy();
  d->SetRightMargin(0.02);
  d->SetTopMargin(0.02);


  for (unsigned int j=0; j<graphs.size(); j++){
     for (unsigned int i=0; i<vec_samples[j].size(); i++){
       graphs[j]->SetPoint(i,i+0.5,vec_samples_signal[j][i]);
       graphs[j]->SetPointError(i,0.5,0);
       graphs[j]->SetLineWidth(2);
       graphs[j]->SetLineColor(colors[j]);
       cout<<colors[j]<<endl;
     }
  }


  for (unsigned int k=0; k<labels.size(); k++){
    TAxis *ax = cutflow_QCD->GetHistogram()->GetXaxis();
    double x1 = ax->GetBinLowEdge(1);
    double x2 = ax->GetBinUpEdge(ax->GetNbins());
    //cutflow_DY->GetHistogram()->GetXaxis()->Set(5,x1,x2);
    cutflow_QCD->GetHistogram()->GetXaxis()->Set(7,x1,x2);
    cutflow_QCD->GetXaxis()->SetLabelSize(0.06);
    cutflow_QCD->GetXaxis()->SetBinLabel(k+1,labels[k]);
  }

  cutflow_QCD->GetXaxis()->SetNdivisions(505);
  cutflow_QCD->GetYaxis()->SetRangeUser(0.0001,10);
  cutflow_QCD->GetYaxis()->SetTitle("Fraction of events passing selection");
  cutflow_QCD->GetYaxis()->SetTitleSize(0.042);
  cutflow_QCD->GetYaxis()->SetTitleOffset(1.2);
  cutflow_QCD->Draw("AP");
  //cutflow_Diboson->Draw("Psame");
  //cutflow_DY->Draw("Psame");
  //cutflow_ST->Draw("Psame");
  cutflow_TT->Draw("Psame");
  cutflow_WJets->Draw("Psame");
  cutflow_DY->Draw("Psame");
  cutflow_TTZToLLNuNu_2018->Draw("Psame");
  cutflow_ST->Draw("Psame");
  cutflow_Diboson->Draw("Psame");
    cutflow_Delphes_2018_0->Draw("Psame");



  TLegend* leg2 = new TLegend(0.2, 0.2, 0.5, 0.5);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.042);
  //leg1->AddEntry(cutflow_DY, "DY", "L");
  //leg1->AddEntry(cutflow_Diboson, "Diboson", "L");
  leg2->AddEntry(cutflow_QCD, "QCD", "L");
  //leg1->AddEntry(cutflow_ST, "ST", "L");
  leg2->AddEntry(cutflow_TT, "TT", "L");
  leg2->AddEntry(cutflow_WJets, "WJets", "L");
  leg2->AddEntry(cutflow_DY, "DY", "L");
  leg2->AddEntry(cutflow_TTZToLLNuNu_2018, "TTZ", "L");
  leg2->AddEntry(cutflow_ST, "ST", "L");
    leg2->AddEntry(cutflow_Diboson, "Diboson", "L");
        leg2->AddEntry(cutflow_Delphes_2018_0, "Delphes Signal", "L");
  leg2->Draw("SAME");


  d->SaveAs("cutflow_stb.pdf");
  delete d;

  delete cutflow_DY;
  delete cutflow_TTZToLLNuNu_2018;
  delete cutflow_QCD;
  //delete cutflow_ST;
  delete cutflow_TT;
  delete cutflow_WJets;
    delete cutflow_ST;
      delete cutflow_Diboson;


}
