#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "myHelper.h"
#include "tr_Tree.h"
#include "ScaleFactor.h"
#include "ZmmSF.h"
#include "LumiReweightingStandAlone.h"
#include "btagSF.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"

using namespace std;

int main(int argc, char** argv){
    
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);
    
    cout << "************* input: " << input.c_str() << " *************" << endl;
    
    TFile * skimmed = new TFile(input.c_str());
    TTree * tree = (TTree*) skimmed->Get("emu_tree");
    TH1F * nevents = (TH1F*) skimmed->Get("nevents");
    float N = nevents->GetBinContent(1); //total generated events (before skimming)
    
    //sample weights
    float xs, weight, luminosity = 59740.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "DY"){weight = 1.0;}
    else if(sample == "DY1"){weight = 1.0;}
    else if(sample == "DY2"){weight = 1.0;}
    else if(sample == "DY3"){weight = 1.0;}
    else if(sample == "DY4"){weight = 1.0;}
    else if(sample == "GGHTT"){xs = 48.58*0.0627; weight = luminosity*xs/N;}
    else if(sample == "GGZHLLTT"){xs = 0.1227*0.0627*3*0.033658; weight = luminosity*xs/N;}
    else if(sample == "GGZHNNTT"){xs = 0.1227*0.0627*0.2000; weight = luminosity*xs/N;}
    else if(sample == "GGZHQQTT"){xs = 0.1227*0.0627*0.6991; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_antitop"){xs = 35.6; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_top"){xs = 35.6; weight = luminosity*xs/N;}
    else if(sample == "ST_t_antitop"){xs = 26.23; weight = luminosity*xs/N;}
    else if(sample == "ST_t_top"){xs = 44.07; weight = luminosity*xs/N;}
    else if(sample == "TTTo2L2Nu"){xs = 88.29; weight = luminosity*xs/N;}
    else if(sample == "TTToHadronic"){xs = 377.96; weight = luminosity*xs/N;}
    else if(sample == "TTToSemiLeptonic"){xs = 365.35; weight = luminosity*xs/N;}
    else if(sample == "VBFHTT"){xs = 3.782*0.0627; weight = luminosity*xs/N;}
    else if(sample == "VV2L2Nu"){xs = 11.95; weight = luminosity*xs/N;}
    else if(sample == "W"){weight = 1.0;}
    else if(sample == "W1"){weight = 1.0;}
    else if(sample == "W2"){weight = 1.0;}
    else if(sample == "W3"){weight = 1.0;}
    else if(sample == "W4"){weight = 1.0;}
    else if(sample == "WZ2L2Q"){xs = 5.595; weight = luminosity*xs/N;}
    else if(sample == "WZ3LNu"){xs = 4.43; weight = luminosity*xs/N;}
    else if(sample == "WminusHTT"){xs = 0.5328*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WplusHTT"){xs = 0.840*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZHTT"){xs = 0.7612*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZZ2L2Q"){xs = 3.22; weight = luminosity*xs/N;}
    else if(sample == "ZZ4L"){xs = 1.212; weight = luminosity*xs/N;}
    else {cout << "Missing sample cross section!!!" << endl; return 0;}
    
  
    tree->SetBranchAddress("pt_1", &pt_1);
    tree->SetBranchAddress("phi_1", &phi_1);
    tree->SetBranchAddress("eta_1", &eta_1);
    tree->SetBranchAddress("m_1", &m_1);
    tree->SetBranchAddress("e_1", &e_1);
    tree->SetBranchAddress("q_1", &q_1);
    tree->SetBranchAddress("iso_1", &iso_1);
    tree->SetBranchAddress("pt_2", &pt_2);
    tree->SetBranchAddress("phi_2", &phi_2);
    tree->SetBranchAddress("eta_2", &eta_2);
    tree->SetBranchAddress("m_2", &m_2);
    tree->SetBranchAddress("e_2", &e_2);
    tree->SetBranchAddress("q_2", &q_2);
    tree->SetBranchAddress("iso_2", &iso_2);
    tree->SetBranchAddress("passMu23E12", &passMu23E12);
    tree->SetBranchAddress("passMu8E23", &passMu8E23);
    tree->SetBranchAddress("matchMu23E12_1", &matchMu23E12_1);
    tree->SetBranchAddress("matchMu8E23_1", &matchMu8E23_1);
    tree->SetBranchAddress("filterMu23E12_1", &filterMu23E12_1);
    tree->SetBranchAddress("filterMu8E23_1", &filterMu8E23_1);
    tree->SetBranchAddress("matchMu23E12_2", &matchMu23E12_2);
    tree->SetBranchAddress("matchMu8E23_2", &matchMu8E23_2);
    tree->SetBranchAddress("filterMu23E12_2", &filterMu23E12_2);
    tree->SetBranchAddress("filterMu8E23_2", &filterMu8E23_2);
    tree->SetBranchAddress("bpt_deepcsv_1", &bpt_deepcsv_1);
    tree->SetBranchAddress("beta_deepcsv_1", &beta_deepcsv_1);
    tree->SetBranchAddress("bphi_deepcsv_1", &bphi_deepcsv_1);
    tree->SetBranchAddress("bm_deepcsv_1", &bm_deepcsv_1);
    tree->SetBranchAddress("bpt_deepcsv_2", &bpt_deepcsv_2);
    tree->SetBranchAddress("beta_deepcsv_2", &beta_deepcsv_2);
    tree->SetBranchAddress("bphi_deepcsv_2", &bphi_deepcsv_2);
    tree->SetBranchAddress("bm_deepcsv_2", &bm_deepcsv_2);
    tree->SetBranchAddress("numGenJets", &numGenJets);
    
    TH1F * hist_em = new TH1F("", "", 30, 0., 100.);
    TH1F * hist_emb = new TH1F("", "", 30, 0., 300.);
    TH1F * hist_embb = new TH1F("", "", 30, 0., 600.);

    //loop over events
    int n = tree->GetEntries(); //no. of events after skimming
    for(int i = 0; i < n; i++){
        if(i % 10000 == 0) printf("event %d of %d...\n", i, n);
        tree->GetEntry(i);
        
        //emu selection
        bool isEMuTrigger_1 = passMu8E23 && matchMu8E23_1 && filterMu8E23_1 && matchMu8E23_2 && filterMu8E23_2;
        bool isEMuTrigger_2 = passMu23E12 && matchMu23E12_1 && filterMu23E12_1 && matchMu23E12_2 && filterMu23E12_2;
        
        if (!isEMuTrigger_1 && !isEMuTrigger_2) continue;
        if (!((isEMuTrigger_1 && pt_1>24 && pt_2>9) or (isEMuTrigger_2 && pt_1>13 && pt_2>24))) continue;
        if (!(fabs(eta_1)<2.5 && fabs(eta_2)<2.4)) continue;
        if (!(iso_1<0.15 && iso_2<0.15)) continue;
        if (q_1*q_2>0) continue;
        if (!(bpt_deepcsv_1>20)) continue;
        
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepcsv_1,beta_deepcsv_1,bphi_deepcsv_1,bm_deepcsv_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepcsv_2,beta_deepcsv_2,bphi_deepcsv_2,bm_deepcsv_2);
        
        if (!(myele.DeltaR(mymu)>0.3)) continue;
        
        //DY and W per-event weights
        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
            if (numGenJets==0) continue;
            else if (numGenJets==1) weight = 0.6298;
            else if (numGenJets==2) weight = 0.5521;
            else if (numGenJets==3) weight = 0.5995;
            else if (numGenJets==4) weight = 0.8211;
        }
        
        if (sample=="W" or sample=="W1" or sample=="W2" or sample=="W3" or sample=="W4"){
            if (numGenJets==0) continue;
            else if (numGenJets==1) weight = 9.082;
            else if (numGenJets==2) weight = 4.511;
            else if (numGenJets==3) weight = 3.077;
            else if (numGenJets==4) weight = 3.233;
        }
        
        //filling histograms
        float m_em = (myele + mymu).M();
        float m_emb = (myele + mymu + myb1).M();
        hist_em->Fill(m_em, weight);
        hist_emb->Fill(m_emb, weight);
        if (bpt_deepcsv_2 > 20){
            float m_embb = (myele + mymu + myb1 + myb2).M();
            hist_embb->Fill(m_embb, weight);
        }
    }

    TFile * fout = TFile::Open(output.c_str(), "RECREATE");
    TDirectory * td1 = fout->mkdir("m_em");
    TDirectory * td2 = fout->mkdir("m_emb");
    TDirectory * td3 = fout->mkdir("m_embb");

    
    td1->cd();
    hist_em->SetName(name.c_str());
    hist_em->Write();
    td2->cd();
    hist_emb->SetName(name.c_str());
    hist_emb->Write();
    td3->cd();
    hist_embb->SetName(name.c_str());
    hist_embb->Write();
    
    fout->Close();
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}

