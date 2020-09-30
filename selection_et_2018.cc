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
#include "btagSF_2018.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "GetTauFR.h"

using namespace std;

int main(int argc, char** argv){
    
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);
    
    cout << "************* input: " << input.c_str() << " *************" << endl;
    
    TFile * skimmed = new TFile(input.c_str());
    TTree * tree = (TTree*) skimmed->Get("etau_tree");
    TH1F * nevents = (TH1F*) skimmed->Get("nevents");
    float N = nevents->GetBinContent(2); //no. of generated events (before skimming) with genweight
    
    //sample weights
    float xs, weight, luminosity = 59740.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "gghbbtt15"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt20"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt25"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt30"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt35"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt40"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt45"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt50"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt55"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt60"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt20"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt40"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt60"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "embedded"){weight = 1.0;}
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
    else if(sample == "WZ3LNu"){xs = 4.708; weight = luminosity*xs/N;}
    else if(sample == "WminusHTT"){xs = 0.5328*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WplusHTT"){xs = 0.840*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZHTT"){xs = 0.7612*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZZ2L2Q"){xs = 3.22; weight = luminosity*xs/N;}
    else if(sample == "ZZ4L"){xs = 1.212; weight = luminosity*xs/N;}
    else {cout << "Missing sample cross section!!!" << endl; return 0;}
    
    
    tree->SetBranchAddress("run", &run);
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
    tree->SetBranchAddress("l2_decayMode", &l2_decayMode);
    tree->SetBranchAddress("passEle35", &passEle35);
    tree->SetBranchAddress("matchEle35_1", &matchEle35_1);
    tree->SetBranchAddress("filterEle35_1", &filterEle35_1);
    tree->SetBranchAddress("passEle32", &passEle32);
    tree->SetBranchAddress("matchEle32_1", &matchEle32_1);
    tree->SetBranchAddress("filterEle32_1", &filterEle32_1);
    tree->SetBranchAddress("passEle24Tau30", &passEle24Tau30);
    tree->SetBranchAddress("matchEle24Tau30_1", &matchEle24Tau30_1);
    tree->SetBranchAddress("filterEle24Tau30_1", &filterEle24Tau30_1);
    tree->SetBranchAddress("matchEle24Tau30_2", &matchEle24Tau30_2);
    tree->SetBranchAddress("filterEle24Tau30_2", &filterEle24Tau30_2);
    tree->SetBranchAddress("passEle24HPSTau30", &passEle24HPSTau30);
    tree->SetBranchAddress("matchEle24HPSTau30_1", &matchEle24HPSTau30_1);
    tree->SetBranchAddress("filterEle24HPSTau30_1", &filterEle24HPSTau30_1);
    tree->SetBranchAddress("matchEle24HPSTau30_2", &matchEle24HPSTau30_2);
    tree->SetBranchAddress("filterEle24HPSTau30_2", &filterEle24HPSTau30_2);
    tree->SetBranchAddress("matchEmbFilter_Ele24Tau30_1", &matchEmbFilter_Ele24Tau30_1);
    tree->SetBranchAddress("matchEmbFilter_Ele24Tau30_2", &matchEmbFilter_Ele24Tau30_2);
    tree->SetBranchAddress("bpt_deepcsv_1", &bpt_deepcsv_1);
    tree->SetBranchAddress("beta_deepcsv_1", &beta_deepcsv_1);
    tree->SetBranchAddress("bphi_deepcsv_1", &bphi_deepcsv_1);
    tree->SetBranchAddress("bm_deepcsv_1", &bm_deepcsv_1);
    tree->SetBranchAddress("bflavour_deepcsv_1", &bflavour_deepcsv_1);
    tree->SetBranchAddress("bscore_deepcsv_1", &bscore_deepcsv_1);
    tree->SetBranchAddress("bpt_deepcsv_2", &bpt_deepcsv_2);
    tree->SetBranchAddress("beta_deepcsv_2", &beta_deepcsv_2);
    tree->SetBranchAddress("bphi_deepcsv_2", &bphi_deepcsv_2);
    tree->SetBranchAddress("bm_deepcsv_2", &bm_deepcsv_2);
    tree->SetBranchAddress("bflavour_deepcsv_2", &bflavour_deepcsv_2);
    tree->SetBranchAddress("bscore_deepcsv_2", &bscore_deepcsv_2);
    tree->SetBranchAddress("numGenJets", &numGenJets);
    tree->SetBranchAddress("pt_top1", &pt_top1);
    tree->SetBranchAddress("pt_top2", &pt_top2);
    tree->SetBranchAddress("npu", &npu);
    tree->SetBranchAddress("genM", &genM);
    tree->SetBranchAddress("genpT", &genpT);
    tree->SetBranchAddress("genweight", &genweight);
    tree->SetBranchAddress("genpt_1", &genpt_1);
    tree->SetBranchAddress("genpt_2", &genpt_2);
    tree->SetBranchAddress("geneta_1", &geneta_1);
    tree->SetBranchAddress("geneta_2", &geneta_2);
    tree->SetBranchAddress("mjj", &mjj);
    tree->SetBranchAddress("njets", &njets);
    tree->SetBranchAddress("gen_match_1",&gen_match_1);
    tree->SetBranchAddress("gen_match_2",&gen_match_2);
    tree->SetBranchAddress("met", &met);
    tree->SetBranchAddress("metphi", &metphi);
    tree->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices);
    tree->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter);
    tree->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter);
    tree->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter);
    tree->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter);
    tree->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter);
    tree->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter);
    tree->SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter", &Flag_ecalBadCalibReducedMINIAODFilter);
    tree->SetBranchAddress("byTightDeepVSe_2", &byTightDeepVSe_2);
    tree->SetBranchAddress("byVLooseDeepVSmu_2", &byVLooseDeepVSmu_2);
    tree->SetBranchAddress("byMediumDeepVSjet_2", &byMediumDeepVSjet_2);
    tree->SetBranchAddress("byVVVLooseDeepVSjet_2", &byVVVLooseDeepVSjet_2);
    tree->SetBranchAddress("byVLooseDeepVSe_2", &byVLooseDeepVSe_2);
    tree->SetBranchAddress("byTightDeepVSmu_2", &byTightDeepVSmu_2);
    
    TH1F * hist_m_et = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_et_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_etb = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_etb_qcd = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_etbb = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_m_etbb_qcd = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_e_pt = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_et_1 = new TH1F("", "", 8, 0., 64.);
    TH1F * hist_m_et_qcd_1 = new TH1F("", "", 8, 0., 64.);
    TH1F * hist_m_et_2 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_et_qcd_2 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_et_3 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_et_qcd_3 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_et_4 = new TH1F("", "", 10, 0., 200.);
    TH1F * hist_m_et_qcd_4 = new TH1F("", "", 10, 0., 200.);
    
    TH1F * hist_m_et_0b = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_et_0b_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_0b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_0b_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_0b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_0b_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_et_1b = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_et_1b_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_1b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_1b_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_1b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_1b_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_et_2b = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_et_2b_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_2b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_2b_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_2b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_2b_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_et_vbf = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_et_vbf_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_vbf = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_vbf_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_vbf = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_vbf_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_et_vv = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_et_vv_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_vv = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_vv_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_vv = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_vv_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_0bw_0 = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_0bw_1 = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_0bw_2 = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_1bw = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_2bw = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_al1bw = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_zpt = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_qcd = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_trg_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_eid_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_top = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_pu = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_gen_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_tid_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_trg_emb = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_eid_emb = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_embsel = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_gen_emb = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_tid_emb = new TH1F("", "", 40, 0., 2.);
    
    //declare workspace for scale factors
    TFile fwmc("htt_scalefactors_legacy_2018.root");
    RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
    fwmc.Close();
    
    //access pileup distributions in data/MC
    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");
    
    //Tau id sf files for MC and embedded
    TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco.root");
    TF1 *fct_tauid = (TF1*) ftauid->Get("Medium_cent");
    TFile *ftauid_emb = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco_EMB.root");
    TF1 *fct_tauid_emb = (TF1*) ftauid_emb->Get("Medium_cent");
    
    //access graphs for the tau fake rates
    TFile *f_taufr = new TFile("FitHistograms_tauFR_2018.root");
    TGraphAsymmErrors *g_taufr_dm0M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm0_deepmedium_hpt_dm0_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm1M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm1_deepmedium_hpt_dm1_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm10M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm10_deepmedium_hpt_dm10_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm11M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm11_deepmedium_hpt_dm11_deepveryveryveryloose");
    
    //loop over events
    int n = tree->GetEntries(); //no. of events after skimming
    for(int i = 0; i < n; i++){
        if(i % 10000 == 0) printf("event %d of %d...\n", i, n);
        tree->GetEntry(i);
        
        //MET filters
        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if (Flag_ecalBadCalibReducedMINIAODFilter) continue;
        
        //etau selection
        bool trigger32 = (passEle32 && pt_1>33 && matchEle32_1 && filterEle32_1);//main
        bool trigger35 = (passEle35 && pt_1>33 && matchEle35_1 && filterEle35_1);//side
        bool trigger2430 = (passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && matchEle24Tau30_2 && filterEle24Tau30_2 && pt_1>25 && pt_2>35 && fabs(eta_2)<2.1 && pt_1<=33);
        bool trigger2430HPS = (passEle24HPSTau30 && matchEle24HPSTau30_1 && filterEle24HPSTau30_1 && matchEle24HPSTau30_2 && filterEle24HPSTau30_2 && pt_1>25 && pt_2>35 && fabs(eta_2)<2.1 && pt_1<=33);
        if (sample=="embedded"){
            trigger2430HPS=(matchEmbFilter_Ele24Tau30_1 && matchEmbFilter_Ele24Tau30_2 && pt_1>25 && pt_2>35 && fabs(eta_2)<2.1 && pt_1<=33);
            trigger35=(pt_1>33 && passEle35 && matchEle35_1 && filterEle35_1);
            trigger32=(pt_1>33 && passEle32 && matchEle32_1 && filterEle32_1);
        }
        if (sample=="data_obs" && run<317509 && !trigger2430 && !trigger32 && !trigger35) continue; // data when the HPS trigger was not enabled
        if (sample=="data_obs" && run>=317509 && !trigger2430HPS && !trigger32 && !trigger35) continue; // data when the HPS trigger was enabled
        if (sample!="data_obs" && !trigger32 && !trigger35 && !trigger2430HPS) continue; // simulation and embedded
        
        if (!(pt_2>25)) continue;
        if (!(fabs(eta_1)<2.1 && fabs(eta_2)<2.3)) continue;
        if (!(iso_1<0.15)) continue;
        if (q_1*q_2>0) continue;
        
        //discriminators for e/mu faking tau_h (many Z->ee so tight for e; rare e+mu so loose for mu)
        if (!(byTightDeepVSe_2 && byVLooseDeepVSmu_2)) continue;
        
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mytau;
        mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepcsv_1,beta_deepcsv_1,bphi_deepcsv_1,bm_deepcsv_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepcsv_2,beta_deepcsv_2,bphi_deepcsv_2,bm_deepcsv_2);
        
        if (!(myele.DeltaR(mytau)>0.4)) continue;
        
        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
            if (numGenJets==0) weight = 3.630;
            else if (numGenJets==1) weight = 0.6304;
            else if (numGenJets==2) weight = 0.5528;
            else if (numGenJets==3) weight = 0.6009;
            else if (numGenJets==4) weight = 0.8314;
        }
        
        if (sample=="W" or sample=="W1" or sample=="W2" or sample=="W3" or sample=="W4"){
            if (numGenJets==0) weight = 25.46;
            else if (numGenJets==1) weight = 5.773;
            else if (numGenJets==2) weight = 1.792;
            else if (numGenJets==3) weight = 0.6829;
            else if (numGenJets==4) weight = 0.7365;
        }
        
        float sf_MC = 1.0;
        
        //scale factors for MC and corrections
        if (sample!="data_obs" && sample!="embedded"){
            
            //reject MC with a jet faking tau_h as duplicated in fake background estimation
            if (gen_match_2==6) continue;
            
            //reject MC with 2 taus as duplicated in embedded sample except for signal/Higgs
            if (sample!="gghbbtt15" && sample!="gghbbtt20" && sample!="gghbbtt25" && sample!="gghbbtt30" && sample!="gghbbtt35" && sample!="gghbbtt40" && sample!="gghbbtt45" && sample!="gghbbtt50" && sample!="gghbbtt55" && sample!="gghbbtt60" && sample!="VBFbbtt20" && sample!="VBFbbtt40" && sample!="VBFbbtt60" && name!="HTT"){
                if (gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) continue;
            }
            
            //initialize workspace with lepton kinematics
            wmc->var("t_pt")->setVal(pt_2);
            wmc->var("t_eta")->setVal(eta_2);
            wmc->var("t_phi")->setVal(phi_2);
            wmc->var("t_dm")->setVal(l2_decayMode);
            wmc->var("e_pt")->setVal(pt_1);
            wmc->var("e_eta")->setVal(eta_1);
            wmc->var("e_iso")->setVal(iso_1);
            
            //trigger scale factor
            float tautrgsf = wmc->function("t_trg_pog_deeptau_medium_etau_ratio")->getVal();
            if (myele.Pt()>33){ // single electron trigger
                sf_MC *= wmc->function("e_trg_ic_ratio")->getVal();
                hist_trg_mc->Fill(wmc->function("e_trg_ic_ratio")->getVal());
            }
            else{ // ele+tau cross trigger, multiplication of ele and tau legs
                sf_MC *= wmc->function("e_trg_24_ic_ratio")->getVal()*tautrgsf;
                hist_trg_mc->Fill(wmc->function("e_trg_24_ic_ratio")->getVal()*tautrgsf);
            }
            
            //electron ID/iso/tracking scale factors
            sf_MC *= wmc->function("e_trk_ratio")->getVal()*wmc->function("e_idiso_ic_ratio")->getVal();
            hist_eid_mc->Fill(wmc->function("e_trk_ratio")->getVal()*wmc->function("e_idiso_ic_ratio")->getVal());
            
            //re-weigh Z pT spectrum for DY samples
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                wmc->var("z_gen_mass")->setVal(genM);
                wmc->var("z_gen_pt")->setVal(genpT);
                float zptweight = wmc->function("zptmass_weight_nom")->getVal();
                sf_MC *= zptweight;
                hist_zpt->Fill(zptweight);
            }
            
            //re-weigh top pT spectrum for ttbar samples
            if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic"){
                float pttop1=pt_top1;
                if (pttop1>472) pttop1=472;
                float pttop2=pt_top2;
                if (pttop2>472) pttop2=472;
                float topfactor = sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
                sf_MC *= topfactor;
                hist_top->Fill(topfactor);
            }
            
            //re-weigh pileup distribution
            float puweight = LumiWeights_12->weight(npu);
            sf_MC *= puweight;
            hist_pu->Fill(puweight);
            
            //generator weight
            sf_MC *= genweight;
            hist_gen_mc->Fill(genweight);
            
            //tau id sf
            if (byMediumDeepVSjet_2 && gen_match_2==5) {sf_MC *= fct_tauid->Eval(mytau.Pt());
                hist_tid_mc->Fill(fct_tauid->Eval(mytau.Pt()));}
            //ele->tauh and muon->tauh sf
            if (gen_match_2==1 or gen_match_2==3){
                if (fabs(eta_2)<1.460) sf_MC *= 1.47;
                else if (fabs(eta_2)>1.558) sf_MC *= 0.66;
                else sf_MC *= 0.0;
            }
            if (gen_match_2==2 or gen_match_2==4){
                if (fabs(eta_2)<0.4) sf_MC *= 0.936*1.019;
                else if (fabs(eta_2)<0.8) sf_MC *= 0.874*1.154;
                else if (fabs(eta_2)<1.2) sf_MC *= 0.912*1.128;
                else if (fabs(eta_2)<1.7) sf_MC *= 0.953*0.974;
                else sf_MC *= 0.936*5.342;
            }
            
        }
        
        float sf_embed = 1.0;
        
        //scale factors for embedded Z->tautau and corrections
        if (sample=="embedded"){
            
            //rejecting buggy events
            if (genweight>1.0) continue;
            
            //initialize workspace with lepton kinematics
            wmc->var("t_pt")->setVal(pt_2);
            wmc->var("t_eta")->setVal(eta_2);
            wmc->var("t_phi")->setVal(phi_2);
            wmc->var("t_dm")->setVal(l2_decayMode);
            wmc->var("e_pt")->setVal(pt_1);
            wmc->var("e_eta")->setVal(eta_1);
            wmc->var("e_iso")->setVal(iso_1);
            
            //trigger scale factor
            wmc->var("t_pt")->setVal(35.0);
            if (myele.Pt()<33){
                sf_embed *= wmc->function("e_trg_24_ic_embed_ratio")->getVal()*wmc->function("t_trg_mediumDeepTau_etau_embed_ratio")->getVal();
                hist_trg_emb->Fill(wmc->function("e_trg_24_ic_embed_ratio")->getVal()*wmc->function("t_trg_mediumDeepTau_etau_embed_ratio")->getVal());
            }
            if (myele.Pt()>33){
                sf_embed *= wmc->function("e_trg_ic_embed_ratio")->getVal();
                hist_trg_emb->Fill(wmc->function("e_trg_ic_embed_ratio")->getVal());
            }
            
            //electron ID/iso/tracking scale factors
            sf_embed *= wmc->function("e_trk_embed_ratio")->getVal()*wmc->function("e_idiso_ic_embed_ratio")->getVal();
            hist_eid_emb->Fill(wmc->function("e_trk_embed_ratio")->getVal()*wmc->function("e_idiso_ic_embed_ratio")->getVal());
            
            //efficiency of selecting Z->mumu data
            float embsel=1.0;
            wmc->var("gt1_pt")->setVal(genpt_1);
            wmc->var("gt2_pt")->setVal(pt_2);
            wmc->var("gt1_eta")->setVal(geneta_1);
            wmc->var("gt2_eta")->setVal(eta_2);
            sf_embed *= wmc->function("m_sel_trg_ic_ratio")->getVal();
            embsel *= wmc->function("m_sel_trg_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(genpt_1);
            wmc->var("gt_eta")->setVal(geneta_1);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            embsel *= wmc->function("m_sel_id_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(pt_2);
            wmc->var("gt_eta")->setVal(eta_2);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            embsel *= wmc->function("m_sel_id_ic_ratio")->getVal();
            hist_embsel->Fill(embsel);
            
            //generator weight
            sf_embed *= genweight;
            hist_gen_emb->Fill(genweight);
            
            //tau id sf
            if (byMediumDeepVSjet_2 && gen_match_2==5) {sf_embed *= fct_tauid_emb->Eval(mytau.Pt());
                hist_tid_emb->Fill(fct_tauid_emb->Eval(mytau.Pt()));}
            
        }
        
        float weight_corr = weight * sf_MC * sf_embed;
        
        //counting reconstructed btagged jets
        int nbtag20 = 0;
        float bMpt_1 = 0;
        float bMflavor_1 = 0;
        float bMpt_2 = 0;
        float bMflavor_2 = 0;
        if (bpt_deepcsv_1>20 && bscore_deepcsv_1>0.4184){
            bMpt_1 = bpt_deepcsv_1;
            bMflavor_1 = bflavour_deepcsv_1;
            nbtag20++;
        }
        if (bpt_deepcsv_2>20 && bscore_deepcsv_2>0.4184){
            bMpt_2 = bpt_deepcsv_2;
            bMflavor_2 = bflavour_deepcsv_2;
            nbtag20++;
        }
        
        //btag weights for MC only
        float weight_btag_0b = 1.0;
        float weight_btag_1b = 1.0;
        float weight_btag_2b = 1.0;
        float weight_btag_atleast1b = 1.0;
        if (sample!="data_obs" && sample!="embedded"){
            //0 bjet (apply to events with any no. of b jet)
            weight_btag_0b = bTagEventWeight(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
            if (nbtag20>2) weight_btag_0b = 0;
            //1 bjet (apply to 1b events only)
            weight_btag_1b = GetSF(1, bMpt_1, bMflavor_1, 0);
            //2 bjets (apply to 2b events only)
            weight_btag_2b = GetSF(1, bMpt_1, bMflavor_1, 0)*GetSF(1, bMpt_2, bMflavor_2, 0);
            //at least 1 bjet (apply to 1b and 2b events)
            if (nbtag20==1) weight_btag_atleast1b = GetSF(1, bMpt_1, bMflavor_1, 0);
            if (nbtag20==2) weight_btag_atleast1b = GetSF(1, bMpt_1, bMflavor_1, 0)+GetSF(1, bMpt_2, bMflavor_2, 0)-GetSF(1, bMpt_1, bMflavor_1, 0)*GetSF(1, bMpt_2, bMflavor_2, 0);
            
            if (nbtag20==0) hist_0bw_0->Fill(weight_btag_0b);
            if (nbtag20==1) {hist_0bw_1->Fill(weight_btag_0b); hist_1bw->Fill(weight_btag_1b);}
            if (nbtag20==2) {hist_0bw_2->Fill(weight_btag_0b); hist_2bw->Fill(weight_btag_2b);}
            if (nbtag20==1 or nbtag20==2) hist_al1bw->Fill(weight_btag_atleast1b);
            
        }
        
        //defining variables for some categories
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);
        
        float mt_emet=TMass_F((myele).Pt(),mymet.Pt(),(myele).Px(),mymet.Px(),(myele).Py(),mymet.Py());
        float mt_taumet=TMass_F((mytau).Pt(),mymet.Pt(),(mytau).Px(),mymet.Px(),(mytau).Py(),mymet.Py());
        
        float norm_zeta=norm_F(myele.Px()/myele.Pt()+mytau.Px()/mytau.Pt(),myele.Py()/myele.Pt()+mytau.Py()/mytau.Pt());
        float x_zeta= (myele.Px()/myele.Pt()+mytau.Px()/mytau.Pt())/norm_zeta;
        float y_zeta= (myele.Py()/myele.Pt()+mytau.Py()/mytau.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(myele.Px()+mytau.Px())*x_zeta+(myele.Py()+mytau.Py())*y_zeta;
        float dzeta=p_zeta_mis-0.85*pzeta_vis;
        
        //filling histograms
        float m_et = (myele + mytau).M();
        float m_etb = (myele + mytau + myb1).M();
        float m_etbb = (myele + mytau + myb1 + myb2).M();
        
        //jet faking tau_h (to be failed in qcd)
        if (byMediumDeepVSjet_2){
            //at least 1 b
            if (((nbtag20==1 && fabs(beta_deepcsv_1)<2.4) or (nbtag20==2 && fabs(beta_deepcsv_1)<2.4 && fabs(beta_deepcsv_2)<2.4))){
                
                hist_m_et->Fill(m_et,weight_corr*weight_btag_atleast1b);
                hist_m_etb->Fill(m_etb,weight_corr*weight_btag_atleast1b);
                hist_e_pt->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                hist_t_pt->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                if (nbtag20==2) hist_m_etbb->Fill(m_etbb,weight_corr*weight_btag_atleast1b);
                
                //vbf at least 1 b
                if (mjj>500){
                    hist_m_et_vbf->Fill(m_et,weight_corr*weight_btag_atleast1b);
                    hist_e_pt_vbf->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                    hist_t_pt_vbf->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                }
                
                //the 4 categories
                if (mt_taumet<60){
                    //category 1
                    if (m_etb<80 && mt_emet<40){
                        hist_m_et_1->Fill(m_et,weight_corr*weight_btag_atleast1b);
                    }
                    //category 2
                    if (m_etb>80 && m_etb<100 && mt_emet<50){
                        hist_m_et_2->Fill(m_et,weight_corr*weight_btag_atleast1b);
                    }
                    //category 3
                    if (m_etb>100 && m_etb<120 && mt_emet<50){
                        hist_m_et_3->Fill(m_et,weight_corr*weight_btag_atleast1b);
                    }
                    //category 4
                    if (m_etb>120 && mt_emet<40){
                        hist_m_et_4->Fill(m_et,weight_corr*weight_btag_atleast1b);
                    }
                }
            }
            //0 bjet data/embedded
            if ((sample=="data_obs" or sample=="embedded") && nbtag20==0){
                hist_m_et_0b->Fill(m_et,weight_corr*weight_btag_0b);
                hist_e_pt_0b->Fill(pt_1,weight_corr*weight_btag_0b);
                hist_t_pt_0b->Fill(pt_2,weight_corr*weight_btag_0b);
                //diboson
                if (m_et>100){
                    hist_m_et_vv->Fill(m_et,weight_corr*weight_btag_0b);
                    hist_e_pt_vv->Fill(pt_1,weight_corr*weight_btag_0b);
                    hist_t_pt_vv->Fill(pt_2,weight_corr*weight_btag_0b);
                }
            }
            //0 bjet MC (keep events with any no. of bjet
            if (sample!="data_obs" && sample!="embedded"){
                hist_m_et_0b->Fill(m_et,weight_corr*weight_btag_0b);
                hist_e_pt_0b->Fill(pt_1,weight_corr*weight_btag_0b);
                hist_t_pt_0b->Fill(pt_2,weight_corr*weight_btag_0b);
                //diboson
                if (m_et>100){
                    hist_m_et_vv->Fill(m_et,weight_corr*weight_btag_0b);
                    hist_e_pt_vv->Fill(pt_1,weight_corr*weight_btag_0b);
                    hist_t_pt_vv->Fill(pt_2,weight_corr*weight_btag_0b);
                }
            }
            //1 bjet
            if (nbtag20==1){
                hist_m_et_1b->Fill(m_et,weight_corr*weight_btag_1b);
                hist_e_pt_1b->Fill(pt_1,weight_corr*weight_btag_1b);
                hist_t_pt_1b->Fill(pt_2,weight_corr*weight_btag_1b);
            }
            //2 bjets
            if (nbtag20==2){
                hist_m_et_2b->Fill(m_et,weight_corr*weight_btag_2b);
                hist_e_pt_2b->Fill(pt_1,weight_corr*weight_btag_2b);
                hist_t_pt_2b->Fill(pt_2,weight_corr*weight_btag_2b);
            }
        }
        
        //for qcd background
        if (byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2){
            //fake rates
            float fr = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dm0M,g_taufr_dm1M,g_taufr_dm10M,g_taufr_dm11M,0);
            float weight_qcd = 0.12;
            hist_qcd->Fill(weight_qcd);
            
            //at least 1 b
            if (((nbtag20==1 && fabs(beta_deepcsv_1)<2.4) or (nbtag20==2 && fabs(beta_deepcsv_1)<2.4 && fabs(beta_deepcsv_2)<2.4))){
                
                hist_m_et_qcd->Fill(m_et,weight_corr*weight_btag_atleast1b*weight_qcd);
                hist_m_etb_qcd->Fill(m_etb,weight_corr*weight_btag_atleast1b*weight_qcd);
                hist_e_pt_qcd->Fill(pt_1,weight_corr*weight_btag_atleast1b*weight_qcd);
                hist_t_pt_qcd->Fill(pt_2,weight_corr*weight_btag_atleast1b*weight_qcd);
                if (nbtag20==2) hist_m_etbb_qcd->Fill(m_etbb,weight_corr*weight_btag_atleast1b*weight_qcd);
                
                //vbf at least 1 b
                if (mjj>500){
                    hist_m_et_vbf_qcd->Fill(m_et,weight_corr*weight_btag_atleast1b*weight_qcd);
                    hist_e_pt_vbf_qcd->Fill(pt_1,weight_corr*weight_btag_atleast1b*weight_qcd);
                    hist_t_pt_vbf_qcd->Fill(pt_2,weight_corr*weight_btag_atleast1b*weight_qcd);
                }
                
                //the 4 categories
                if (mt_taumet<60){
                    //category 1
                    if (m_etb<80 && mt_emet<40){
                        hist_m_et_qcd_1->Fill(m_et,weight_corr*weight_btag_atleast1b*weight_qcd);
                    }
                    //category 2
                    if (m_etb>80 && m_etb<100 && mt_emet<50){
                        hist_m_et_qcd_2->Fill(m_et,weight_corr*weight_btag_atleast1b*weight_qcd);
                    }
                    //category 3
                    if (m_etb>100 && m_etb<120 && mt_emet<50){
                        hist_m_et_qcd_3->Fill(m_et,weight_corr*weight_btag_atleast1b*weight_qcd);
                    }
                    //category 4
                    if (m_etb>120 && mt_emet<40){
                        hist_m_et_qcd_4->Fill(m_et,weight_corr*weight_btag_atleast1b*weight_qcd);
                    }
                }
            }
            //0 bjet data/embedded
            if ((sample=="data_obs" or sample=="embedded") && nbtag20==0){
                hist_m_et_0b_qcd->Fill(m_et,weight_corr*weight_btag_0b*weight_qcd);
                hist_e_pt_0b_qcd->Fill(pt_1,weight_corr*weight_btag_0b*weight_qcd);
                hist_t_pt_0b_qcd->Fill(pt_2,weight_corr*weight_btag_0b*weight_qcd);
                //diboson
                if (m_et>100){
                    hist_m_et_vv_qcd->Fill(m_et,weight_corr*weight_btag_0b*weight_qcd);
                    hist_e_pt_vv_qcd->Fill(pt_1,weight_corr*weight_btag_0b*weight_qcd);
                    hist_t_pt_vv_qcd->Fill(pt_2,weight_corr*weight_btag_0b*weight_qcd);
                }
            }
            //0 bjet MC (keep events with any no. of bjet
            if (sample!="data_obs" && sample!="embedded"){
                hist_m_et_0b_qcd->Fill(m_et,weight_corr*weight_btag_0b*weight_qcd);
                hist_e_pt_0b_qcd->Fill(pt_1,weight_corr*weight_btag_0b*weight_qcd);
                hist_t_pt_0b_qcd->Fill(pt_2,weight_corr*weight_btag_0b*weight_qcd);
                //diboson
                if (m_et>100){
                    hist_m_et_vv_qcd->Fill(m_et,weight_corr*weight_btag_0b*weight_qcd);
                    hist_e_pt_vv_qcd->Fill(pt_1,weight_corr*weight_btag_0b*weight_qcd);
                    hist_t_pt_vv_qcd->Fill(pt_2,weight_corr*weight_btag_0b*weight_qcd);
                }
            }
            //1 bjet
            if (nbtag20==1){
                hist_m_et_1b_qcd->Fill(m_et,weight_corr*weight_btag_1b*weight_qcd);
                hist_e_pt_1b_qcd->Fill(pt_1,weight_corr*weight_btag_1b*weight_qcd);
                hist_t_pt_1b_qcd->Fill(pt_2,weight_corr*weight_btag_1b*weight_qcd);
            }
            //2 bjets
            if (nbtag20==2){
                hist_m_et_2b_qcd->Fill(m_et,weight_corr*weight_btag_2b*weight_qcd);
                hist_e_pt_2b_qcd->Fill(pt_1,weight_corr*weight_btag_2b*weight_qcd);
                hist_t_pt_2b_qcd->Fill(pt_2,weight_corr*weight_btag_2b*weight_qcd);
            }
        }
    }
    
    TFile * fout = TFile::Open(output.c_str(), "RECREATE");
    
    TDirectory * td1 = fout->mkdir("m_et_1");
    TDirectory * td2 = fout->mkdir("m_et_2");
    TDirectory * td3 = fout->mkdir("m_et_3");
    TDirectory * td4 = fout->mkdir("m_et_4");
    TDirectory * td5 = fout->mkdir("m_et");
    TDirectory * td6 = fout->mkdir("m_etb");
    TDirectory * td7 = fout->mkdir("m_etbb");
    TDirectory * td8 = fout->mkdir("pt_e");
    TDirectory * td9 = fout->mkdir("pt_t");
    
    TDirectory * td10 = fout->mkdir("m_et_0b");
    TDirectory * td11 = fout->mkdir("pt_e_0b");
    TDirectory * td12 = fout->mkdir("pt_t_0b");
    TDirectory * td13 = fout->mkdir("m_et_1b");
    TDirectory * td14 = fout->mkdir("pt_e_1b");
    TDirectory * td15 = fout->mkdir("pt_t_1b");
    TDirectory * td16 = fout->mkdir("m_et_2b");
    TDirectory * td17 = fout->mkdir("pt_e_2b");
    TDirectory * td18 = fout->mkdir("pt_t_2b");
    TDirectory * td19 = fout->mkdir("m_et_vbf");
    TDirectory * td20 = fout->mkdir("pt_e_vbf");
    TDirectory * td21 = fout->mkdir("pt_t_vbf");
    TDirectory * td22 = fout->mkdir("m_et_vv");
    TDirectory * td23 = fout->mkdir("pt_e_vv");
    TDirectory * td24 = fout->mkdir("pt_t_vv");
    
    TDirectory * td25 = fout->mkdir("weights");
    
    TString qcd="_qcd";
    
    td1->cd();
    hist_m_et_1->SetName(name.c_str());
    hist_m_et_1->Write();
    hist_m_et_qcd_1->SetName(name.c_str()+qcd);
    hist_m_et_qcd_1->Write();
    
    td2->cd();
    hist_m_et_2->SetName(name.c_str());
    hist_m_et_2->Write();
    hist_m_et_qcd_2->SetName(name.c_str()+qcd);
    hist_m_et_qcd_2->Write();
    
    td3->cd();
    hist_m_et_3->SetName(name.c_str());
    hist_m_et_3->Write();
    hist_m_et_qcd_3->SetName(name.c_str()+qcd);
    hist_m_et_qcd_3->Write();
    
    td4->cd();
    hist_m_et_4->SetName(name.c_str());
    hist_m_et_4->Write();
    hist_m_et_qcd_4->SetName(name.c_str()+qcd);
    hist_m_et_qcd_4->Write();
    
    td5->cd();
    hist_m_et->SetName(name.c_str());
    hist_m_et->Write();
    hist_m_et_qcd->SetName(name.c_str()+qcd);
    hist_m_et_qcd->Write();
    
    td6->cd();
    hist_m_etb->SetName(name.c_str());
    hist_m_etb->Write();
    hist_m_etb_qcd->SetName(name.c_str()+qcd);
    hist_m_etb_qcd->Write();
    
    td7->cd();
    hist_m_etbb->SetName(name.c_str());
    hist_m_etbb->Write();
    hist_m_etbb_qcd->SetName(name.c_str()+qcd);
    hist_m_etbb_qcd->Write();
    
    td8->cd();
    hist_e_pt->SetName(name.c_str());
    hist_e_pt->Write();
    hist_e_pt_qcd->SetName(name.c_str()+qcd);
    hist_e_pt_qcd->Write();
    
    td9->cd();
    hist_t_pt->SetName(name.c_str());
    hist_t_pt->Write();
    hist_t_pt_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_qcd->Write();
    
    td10->cd();
    hist_m_et_0b->SetName(name.c_str());
    hist_m_et_0b->Write();
    hist_m_et_0b_qcd->SetName(name.c_str()+qcd);
    hist_m_et_0b_qcd->Write();
    
    td11->cd();
    hist_e_pt_0b->SetName(name.c_str());
    hist_e_pt_0b->Write();
    hist_e_pt_0b_qcd->SetName(name.c_str()+qcd);
    hist_e_pt_0b_qcd->Write();
    
    td12->cd();
    hist_t_pt_0b->SetName(name.c_str());
    hist_t_pt_0b->Write();
    hist_t_pt_0b_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_0b_qcd->Write();
    
    td13->cd();
    hist_m_et_1b->SetName(name.c_str());
    hist_m_et_1b->Write();
    hist_m_et_1b_qcd->SetName(name.c_str()+qcd);
    hist_m_et_1b_qcd->Write();
    
    td14->cd();
    hist_e_pt_1b->SetName(name.c_str());
    hist_e_pt_1b->Write();
    hist_e_pt_1b_qcd->SetName(name.c_str()+qcd);
    hist_e_pt_1b_qcd->Write();
    
    td15->cd();
    hist_t_pt_1b->SetName(name.c_str());
    hist_t_pt_1b->Write();
    hist_t_pt_1b_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_1b_qcd->Write();
    
    td16->cd();
    hist_m_et_2b->SetName(name.c_str());
    hist_m_et_2b->Write();
    hist_m_et_2b_qcd->SetName(name.c_str()+qcd);
    hist_m_et_2b_qcd->Write();
    
    td17->cd();
    hist_e_pt_2b->SetName(name.c_str());
    hist_e_pt_2b->Write();
    hist_e_pt_2b_qcd->SetName(name.c_str()+qcd);
    hist_e_pt_2b_qcd->Write();
    
    td18->cd();
    hist_t_pt_2b->SetName(name.c_str());
    hist_t_pt_2b->Write();
    hist_t_pt_2b_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_2b_qcd->Write();
    
    td19->cd();
    hist_m_et_vbf->SetName(name.c_str());
    hist_m_et_vbf->Write();
    hist_m_et_vbf_qcd->SetName(name.c_str()+qcd);
    hist_m_et_vbf_qcd->Write();
    
    td20->cd();
    hist_e_pt_vbf->SetName(name.c_str());
    hist_e_pt_vbf->Write();
    hist_e_pt_vbf_qcd->SetName(name.c_str()+qcd);
    hist_e_pt_vbf_qcd->Write();
    
    td21->cd();
    hist_t_pt_vbf->SetName(name.c_str());
    hist_t_pt_vbf->Write();
    hist_t_pt_vbf_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_vbf_qcd->Write();
    
    td22->cd();
    hist_m_et_vv->SetName(name.c_str());
    hist_m_et_vv->Write();
    hist_m_et_vv_qcd->SetName(name.c_str()+qcd);
    hist_m_et_vv_qcd->Write();
    
    td23->cd();
    hist_e_pt_vv->SetName(name.c_str());
    hist_e_pt_vv->Write();
    hist_e_pt_vv_qcd->SetName(name.c_str()+qcd);
    hist_e_pt_vv_qcd->Write();
    
    td24->cd();
    hist_t_pt_vv->SetName(name.c_str());
    hist_t_pt_vv->Write();
    hist_t_pt_vv_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_vv_qcd->Write();
    
    td25->cd();
    hist_0bw_0->SetName("0bw_0b");
    hist_0bw_0->Write();
    hist_0bw_1->SetName("0bw_1b");
    hist_0bw_1->Write();
    hist_0bw_2->SetName("0bw_2b");
    hist_0bw_2->Write();
    hist_1bw->SetName("1bw");
    hist_1bw->Write();
    hist_2bw->SetName("2bw");
    hist_2bw->Write();
    hist_al1bw->SetName("al1bw");
    hist_al1bw->Write();
    hist_zpt->SetName("zptweight");
    hist_zpt->Write();
    hist_qcd->SetName("qcdweight");
    hist_qcd->Write();
    hist_trg_mc->SetName("trg_mc");
    hist_trg_mc->Write();
    hist_eid_mc->SetName("eid_mc");
    hist_eid_mc->Write();
    hist_top->SetName("top");
    hist_top->Write();
    hist_pu->SetName("pu");
    hist_pu->Write();
    hist_gen_mc->SetName("gen_mc");
    hist_gen_mc->Write();
    hist_tid_mc->SetName("tid_mc");
    hist_tid_mc->Write();
    hist_trg_emb->SetName("trg_emb");
    hist_trg_emb->Write();
    hist_eid_emb->SetName("eid_emb");
    hist_eid_emb->Write();
    hist_embsel->SetName("embsel");
    hist_embsel->Write();
    hist_gen_emb->SetName("gen_emb");
    hist_gen_emb->Write();
    hist_tid_emb->SetName("tid_emb");
    hist_tid_emb->Write();
    
    
    
    fout->Close();
    
    delete wmc;
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}





