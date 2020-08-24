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
    float N = nevents->GetBinContent(2); //no. of generated events (before skimming) with genweight
    
    //sample weights
    float xs, weight, luminosity = 59740.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "bbtt60"){xs = 48.58*0.1133; weight = luminosity*xs/N;}
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
    tree->SetBranchAddress("passMu23E12DZ", &passMu23E12DZ);
    tree->SetBranchAddress("passMu8E23DZ", &passMu8E23DZ);
    tree->SetBranchAddress("matchMu23E12DZ_1", &matchMu23E12DZ_1);
    tree->SetBranchAddress("matchMu8E23DZ_1", &matchMu8E23DZ_1);
    tree->SetBranchAddress("filterMu23E12DZ_1", &filterMu23E12DZ_1);
    tree->SetBranchAddress("filterMu8E23DZ_1", &filterMu8E23DZ_1);
    tree->SetBranchAddress("matchMu23E12DZ_2", &matchMu23E12DZ_2);
    tree->SetBranchAddress("matchMu8E23DZ_2", &matchMu8E23DZ_2);
    tree->SetBranchAddress("filterMu23E12DZ_2", &filterMu23E12DZ_2);
    tree->SetBranchAddress("filterMu8E23DZ_2", &filterMu8E23DZ_2);
    tree->SetBranchAddress("bpt_deepcsv_1", &bpt_deepcsv_1);
    tree->SetBranchAddress("beta_deepcsv_1", &beta_deepcsv_1);
    tree->SetBranchAddress("bphi_deepcsv_1", &bphi_deepcsv_1);
    tree->SetBranchAddress("bm_deepcsv_1", &bm_deepcsv_1);
    tree->SetBranchAddress("bpt_deepcsv_2", &bpt_deepcsv_2);
    tree->SetBranchAddress("beta_deepcsv_2", &beta_deepcsv_2);
    tree->SetBranchAddress("bphi_deepcsv_2", &bphi_deepcsv_2);
    tree->SetBranchAddress("bm_deepcsv_2", &bm_deepcsv_2);
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
    
    
    TH1F * hist_m_em_OS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_em_SS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_emb_OS = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_emb_SS = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_embb_OS = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_m_embb_SS = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_e_pt_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_SS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_mu_pt_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_mu_pt_SS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_b1_pt_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_b1_pt_SS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_b2_pt_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_b2_pt_SS = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_em_OS_nobjet = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_em_SS_nobjet = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_OS_nobjet = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_SS_nobjet = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_mu_pt_OS_nobjet = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_mu_pt_SS_nobjet = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_em_OS_VBFenriched = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_em_SS_VBFenriched = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_emb_OS_VBFenriched = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_emb_SS_VBFenriched = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_embb_OS_VBFenriched = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_m_embb_SS_VBFenriched = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_e_pt_OS_VBFenriched = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_SS_VBFenriched = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_mu_pt_OS_VBFenriched = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_mu_pt_SS_VBFenriched = new TH1F("", "", 30, 0., 150.);
    
    
    //declare workspace for scale factors
    TFile fwmc("htt_scalefactors_legacy_2018.root");
    RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
    fwmc.Close();
    
    //access pileup distributions in data/MC
    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");
    
    //loop over events
    int n = tree->GetEntries(); //no. of events after skimming
    for(int i = 0; i < n; i++){
        if(i % 10000 == 0) printf("event %d of %d...\n", i, n);
        tree->GetEntry(i);
        
        //emu selection
        bool isMu8E23trigger = passMu8E23DZ && matchMu8E23DZ_1 && filterMu8E23DZ_1 && matchMu8E23DZ_2 && filterMu8E23DZ_2 && pt_1>24 && pt_2>10;
        bool isMu23E12trigger = passMu23E12DZ && matchMu23E12DZ_1 && filterMu23E12DZ_1 && matchMu23E12DZ_2 && filterMu23E12DZ_2 && pt_1>13 && pt_2>24;
        
        if (!isMu8E23trigger && !isMu23E12trigger) continue;
        if (!(fabs(eta_1)<2.5 && fabs(eta_2)<2.4)) continue;
        if (!(iso_1<0.15 && iso_2<0.15)) continue;
        
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepcsv_1,beta_deepcsv_1,bphi_deepcsv_1,bm_deepcsv_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepcsv_2,beta_deepcsv_2,bphi_deepcsv_2,bm_deepcsv_2);
        
        if (!(myele.DeltaR(mymu)>0.3)) continue;
        
        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
            if (numGenJets==0) weight = 3.630;
            else if (numGenJets==1) weight = 0.6304;
            else if (numGenJets==2) weight = 0.5528;
            else if (numGenJets==3) weight = 0.6009;
            else if (numGenJets==4) weight = 0.8314;
        }
        
        if (sample=="W" or sample=="W1" or sample=="W2" or sample=="W3" or sample=="W4"){
            if (numGenJets==0) weight = 51.81;
            else if (numGenJets==1) weight = 9.091;
            else if (numGenJets==2) weight = 4.516;
            else if (numGenJets==3) weight = 3.090;
            else if (numGenJets==4) weight = 3.227;
        }
        
        float sf_MC = 1.0;
        
        //scale factors for MC
        if (sample!="data_obs" && sample!="embedded"){
            
            //initialize workspace with lepton kinematics
            wmc->var("m_pt")->setVal(pt_2);
            wmc->var("m_eta")->setVal(eta_2);
            wmc->var("m_iso")->setVal(iso_2);
            wmc->var("e_pt")->setVal(pt_1);
            wmc->var("e_eta")->setVal(eta_1);
            wmc->var("e_iso")->setVal(iso_1);
            
            //compute trigger scale factor
            float probData = wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(isMu8E23trigger)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(isMu23E12trigger)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(isMu8E23trigger && isMu23E12trigger);
            float probMC = wmc->function("m_trg_8_ic_mc")->getVal()*wmc->function("e_trg_23_ic_mc")->getVal()*int(isMu8E23trigger)+wmc->function("m_trg_23_ic_mc")->getVal()*wmc->function("e_trg_12_ic_mc")->getVal()*int(isMu23E12trigger)-wmc->function("e_trg_23_ic_mc")->getVal()*wmc->function("m_trg_23_ic_mc")->getVal()*int(isMu8E23trigger && isMu23E12trigger);
            float sf_trg = probData/probMC;
            sf_MC *= sf_trg;
            
            //muon and electron ID/iso/tracking scale factors
            float sf_mu = wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_ratio")->getVal();
            float sf_e = wmc->function("e_trk_ratio")->getVal()*wmc->function("e_idiso_ic_ratio")->getVal();
            sf_MC *= sf_mu * sf_e;

            //re-weigh Z pT spectrum for DY samples
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                wmc->var("z_gen_mass")->setVal(genM);
                wmc->var("z_gen_pt")->setVal(genpT);
                float zptweight = wmc->function("zptmass_weight_nom")->getVal();
                sf_MC *= zptweight;
            }

            //re-weigh top pT spectrum for ttbar samples
            if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic"){
                float pttop1=pt_top1;
                if (pttop1>472) pttop1=472;
                float pttop2=pt_top2;
                if (pttop2>472) pttop2=472;
                float topfactor = sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
                sf_MC *= topfactor;
            }
            
            //re-weigh pileup distribution
            float puweight = LumiWeights_12->weight(npu);
            sf_MC *= puweight;
            
            //generator weight
            sf_MC *= genweight;
            
        }
        
        float sf_embed = 1.0;
/*
        //scale factors for embedded Z->tautau
        if (sample=="embedded"){
            
            //initialize workspace with lepton kinematics
            wmc->var("m_pt")->setVal(pt_2);
            wmc->var("m_eta")->setVal(eta_2);
            wmc->var("m_iso")->setVal(iso_2);
            wmc->var("e_pt")->setVal(pt_1);
            wmc->var("e_eta")->setVal(eta_1);
            wmc->var("e_iso")->setVal(iso_1);

            //compute trigger scale factor
            float probData = wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(isMu8E23trigger)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(isMu23E12trigger)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(isMu8E23trigger && isMu23E12trigger);
            float probEmbed = wmc->function("m_trg_8_ic_embed")->getVal()*wmc->function("e_trg_23_ic_embed")->getVal()*int(isMu8E23trigger)+wmc->function("m_trg_23_ic_embed")->getVal()*wmc->function("e_trg_12_ic_embed")->getVal()*int(isMu23E12trigger)-wmc->function("e_trg_23_ic_embed")->getVal()*wmc->function("m_trg_23_ic_embed")->getVal()*int(isMu8E23trigger && isMu23E12trigger);
            float sf_trg = probData/probEmbed;
            sf_embed *= sf_trg;

            //muon and electron ID/iso/tracking scale factors
            float sf_mu = wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_embed_ratio")->getVal();
            float sf_e = wmc->function("e_trk_embed_ratio")->getVal()*wmc->function("e_idiso_ic_embed_ratio")->getVal();
            sf_embed *= sf_mu * sf_e;
            
            //efficiency of selecting Z->mumu data
            wmc->var("gt1_pt")->setVal(genpt_1);
            wmc->var("gt2_pt")->setVal(genpt_2);
            wmc->var("gt1_eta")->setVal(geneta_1);
            wmc->var("gt2_eta")->setVal(geneta_2);
            sf_embed *= wmc->function("m_sel_trg_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(genpt_1);
            wmc->var("gt_eta")->setVal(geneta_1);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(genpt_2);
            wmc->var("gt_eta")->setVal(geneta_2);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            
            generator weight
            sf_embed *= genweight;
            
        }
*/
        float weight_corr = weight * sf_MC * sf_embed;
        
        //filling histograms
        float m_em = (myele + mymu).M();
        float m_emb = (myele + mymu + myb1).M();
        float m_embb = (myele + mymu + myb1 + myb2).M();
        
        //OS region
        if (q_1*q_2<0){
            //at least 1 bjet
            if (bpt_deepcsv_1 > 20){
                hist_m_em_OS->Fill(m_em, weight_corr);
                hist_m_emb_OS->Fill(m_emb, weight_corr);
                hist_e_pt_OS->Fill(pt_1, weight_corr);
                hist_mu_pt_OS->Fill(pt_2, weight_corr);
                hist_b1_pt_OS->Fill(bpt_deepcsv_1, weight_corr);
                
                if (bpt_deepcsv_2 > 20){
                    hist_m_embb_OS->Fill(m_embb, weight_corr);
                    hist_b2_pt_OS->Fill(bpt_deepcsv_2, weight_corr);
                }
            }
            
            //no bjet
            if (bpt_deepcsv_1 < 0){
                hist_m_em_OS_nobjet->Fill(m_em, weight_corr);
                hist_e_pt_OS_nobjet->Fill(pt_1, weight_corr);
                hist_mu_pt_OS_nobjet->Fill(pt_2, weight_corr);
            }
            
            //VBF-enriched
            if (mjj > 500){
                //at least 1 bjet
                if (bpt_deepcsv_1 > 20){
                    hist_m_em_OS_VBFenriched->Fill(m_em, weight_corr);
                    hist_m_emb_OS_VBFenriched->Fill(m_emb, weight_corr);
                    hist_e_pt_OS_VBFenriched->Fill(pt_1, weight_corr);
                    hist_mu_pt_OS_VBFenriched->Fill(pt_2, weight_corr);
                    
                    if (bpt_deepcsv_2 > 20){
                        hist_m_embb_OS_VBFenriched->Fill(m_embb, weight_corr);
                    }
                }
                
            }
        }
        
        //S region
        if (q_1*q_2>0){
            //at least 1 bjet
            if (bpt_deepcsv_1 > 20){
                hist_m_em_SS->Fill(m_em, weight_corr);
                hist_m_emb_SS->Fill(m_emb, weight_corr);
                hist_e_pt_SS->Fill(pt_1, weight_corr);
                hist_mu_pt_SS->Fill(pt_2, weight_corr);
                hist_b1_pt_SS->Fill(bpt_deepcsv_1, weight_corr);
                
                if (bpt_deepcsv_2 > 20){
                    hist_m_embb_SS->Fill(m_embb, weight_corr);
                    hist_b2_pt_SS->Fill(bpt_deepcsv_2, weight_corr);
                }
            }
            
            //no bjet
            if (bpt_deepcsv_1 < 20){
                hist_m_em_SS_nobjet->Fill(m_em, weight_corr);
                hist_e_pt_SS_nobjet->Fill(pt_1, weight_corr);
                hist_mu_pt_SS_nobjet->Fill(pt_2, weight_corr);
            }
            
            //VBF-enriched
            if (mjj > 500){
                //at least 1 bjet
                if (bpt_deepcsv_1 > 20){
                    hist_m_em_SS_VBFenriched->Fill(m_em, weight_corr);
                    hist_m_emb_SS_VBFenriched->Fill(m_emb, weight_corr);
                    hist_e_pt_SS_VBFenriched->Fill(pt_1, weight_corr);
                    hist_mu_pt_SS_VBFenriched->Fill(pt_2, weight_corr);
                    
                    if (bpt_deepcsv_2 > 20){
                        hist_m_embb_SS_VBFenriched->Fill(m_embb, weight_corr);
                    }
                }
                
            }
        }
                
    }
    
    TFile * fout = TFile::Open(output.c_str(), "RECREATE");
    TDirectory * td1 = fout->mkdir("m_em");
    TDirectory * td2 = fout->mkdir("m_emb");
    TDirectory * td3 = fout->mkdir("m_embb");
    TDirectory * td4 = fout->mkdir("e_pt");
    TDirectory * td5 = fout->mkdir("mu_pt");
    TDirectory * td6 = fout->mkdir("b1_pt");
    TDirectory * td7 = fout->mkdir("b2_pt");
    
    TDirectory * td8 = fout->mkdir("m_em_nobjet");
    TDirectory * td9 = fout->mkdir("e_pt_nobjet");
    TDirectory * td10 = fout->mkdir("mu_pt_nobjet");
    
    TDirectory * td11 = fout->mkdir("m_em_VBFenriched");
    TDirectory * td12 = fout->mkdir("m_emb_VBFenriched");
    TDirectory * td13 = fout->mkdir("m_embb_VBFenriched");
    TDirectory * td14 = fout->mkdir("e_pt_VBFenriched");
    TDirectory * td15 = fout->mkdir("mu_pt_VBFenriched");
    
    TString OS="_OS";
    TString SS="_SS";
    
    td1->cd();
    hist_m_em_OS->SetName(name.c_str()+OS);
    hist_m_em_OS->Write();
    hist_m_em_SS->SetName(name.c_str()+SS);
    hist_m_em_SS->Write();
    
    td2->cd();
    hist_m_emb_OS->SetName(name.c_str()+OS);
    hist_m_emb_OS->Write();
    hist_m_emb_SS->SetName(name.c_str()+SS);
    hist_m_emb_SS->Write();
    
    td3->cd();
    hist_m_embb_OS->SetName(name.c_str()+OS);
    hist_m_embb_OS->Write();
    hist_m_embb_SS->SetName(name.c_str()+SS);
    hist_m_embb_SS->Write();
    
    td4->cd();
    hist_e_pt_OS->SetName(name.c_str()+OS);
    hist_e_pt_OS->Write();
    hist_e_pt_SS->SetName(name.c_str()+SS);
    hist_e_pt_SS->Write();
    
    td5->cd();
    hist_mu_pt_OS->SetName(name.c_str()+OS);
    hist_mu_pt_OS->Write();
    hist_mu_pt_SS->SetName(name.c_str()+SS);
    hist_mu_pt_SS->Write();
    
    td6->cd();
    hist_b1_pt_OS->SetName(name.c_str()+OS);
    hist_b1_pt_OS->Write();
    hist_b1_pt_SS->SetName(name.c_str()+SS);
    hist_b1_pt_SS->Write();
    
    td7->cd();
    hist_b2_pt_OS->SetName(name.c_str()+OS);
    hist_b2_pt_OS->Write();
    hist_b2_pt_SS->SetName(name.c_str()+SS);
    hist_b2_pt_SS->Write();
    
    td8->cd();
    hist_m_em_OS_nobjet->SetName(name.c_str()+OS);
    hist_m_em_OS_nobjet->Write();
    hist_m_em_SS_nobjet->SetName(name.c_str()+SS);
    hist_m_em_SS_nobjet->Write();
    
    td9->cd();
    hist_e_pt_OS_nobjet->SetName(name.c_str()+OS);
    hist_e_pt_OS_nobjet->Write();
    hist_e_pt_SS_nobjet->SetName(name.c_str()+SS);
    hist_e_pt_SS_nobjet->Write();
    
    td10->cd();
    hist_mu_pt_OS_nobjet->SetName(name.c_str()+OS);
    hist_mu_pt_OS_nobjet->Write();
    hist_mu_pt_SS_nobjet->SetName(name.c_str()+SS);
    hist_mu_pt_SS_nobjet->Write();
    
    td11->cd();
    hist_m_em_OS_VBFenriched->SetName(name.c_str()+OS);
    hist_m_em_OS_VBFenriched->Write();
    hist_m_em_SS_VBFenriched->SetName(name.c_str()+SS);
    hist_m_em_SS_VBFenriched->Write();
    
    td12->cd();
    hist_m_emb_OS_VBFenriched->SetName(name.c_str()+OS);
    hist_m_emb_OS_VBFenriched->Write();
    hist_m_emb_SS_VBFenriched->SetName(name.c_str()+SS);
    hist_m_emb_SS_VBFenriched->Write();
    
    td13->cd();
    hist_m_embb_OS_VBFenriched->SetName(name.c_str()+OS);
    hist_m_embb_OS_VBFenriched->Write();
    hist_m_embb_SS_VBFenriched->SetName(name.c_str()+SS);
    hist_m_embb_SS_VBFenriched->Write();
    
    td14->cd();
    hist_e_pt_OS_VBFenriched->SetName(name.c_str()+OS);
    hist_e_pt_OS_VBFenriched->Write();
    hist_e_pt_SS_VBFenriched->SetName(name.c_str()+SS);
    hist_e_pt_SS_VBFenriched->Write();
    
    td15->cd();
    hist_mu_pt_OS_VBFenriched->SetName(name.c_str()+OS);
    hist_mu_pt_OS_VBFenriched->Write();
    hist_mu_pt_SS_VBFenriched->SetName(name.c_str()+SS);
    hist_mu_pt_SS_VBFenriched->Write();
    
    fout->Close();
    
    delete wmc;
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}
