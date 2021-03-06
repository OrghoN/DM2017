#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TSystem.h"
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
#include <TLorentzVector.h>
using namespace std;


float WScaleFactor=1.0; // computed on Apr 20th
//float TTScaleFactor=0.91;
//float WScaleFactor=1.22;
//float TTScaleFactor=0.856;


float XSection(std::string OutName) {
    
    
    ////////////////////////////////////////////////////////////////
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
    
    ////////////////////////////////////////////////////////////////
    
    //    https://docs.google.com/spreadsheets/d/1rWM3AlFKO8IJVaeoQkWZYWwSvicQ1QCXYSzH74QyZqE/edit?alt=json#gid=398123591
    
    
    
    
    
    
    
//        if (OutName.find("WJetsToLNu_Inc") != string::npos) return 50690;   // As we have large cut at Skim, this one is not needed
    if (OutName.find("WJetsToLNu_HT-70to100") != string::npos) return 1372;
    else if (OutName.find("WJetsToLNu_HT-100to200") != string::npos) return 1343;
    else if (OutName.find("WJetsToLNu_HT-200to400") != string::npos) return 359.6;
    else if (OutName.find("WJetsToLNu_HT-400to600") != string::npos) return 48.85;
    else if (OutName.find("WJetsToLNu_HT-600to800") != string::npos) return 12.05;
    else if (OutName.find("WJetsToLNu_HT-800to1200") != string::npos) return 5.501;
    else if (OutName.find("WJetsToLNu_HT-1200to2500") != string::npos) return 1.329;
    else if (OutName.find("WJetsToLNu_HT-2500toInf") != string::npos) return 0.03216;
    
    
    //    else if (OutName.find("DYJetsToLL_Inc") != string::npos) return 4895 * 1.012; // As we have large cut at Skim, this one is not needed
    else if (OutName.find("DYJetsToLL_M-50_HT-70to100") != string::npos) return 175.3; // from 	EXO-16-049
    else if (OutName.find("DYJetsToLL_M-50_HT-100to200") != string::npos) return 148;
    else if (OutName.find("DYJetsToLL_M-50_HT-200to400") != string::npos) return 40.94;
    else if (OutName.find("DYJetsToLL_M-50_HT-400to600") != string::npos) return 5.497;
    else if (OutName.find("DYJetsToLL_M-50_HT-600to800") != string::npos) return 1.354;
    else if (OutName.find("DYJetsToLL_M-50_HT-800to1200") != string::npos) return 0.625;
    else if (OutName.find("DYJetsToLL_M-50_HT-1200to2500") != string::npos) return 0.151;
    else if (OutName.find("DYJetsToLL_M-50_HT-2500toInf") != string::npos) return 0.003647;
    
    
    //Di-boson   Pythia is not useful in this analysis
//    else if (OutName.find("WW_pythia") != string::npos) return 115.0;
//    else if (OutName.find("WZ_pythia") != string::npos) return 47.13;
//    else if (OutName.find("ZZ_pythia") != string::npos) return 16.523;
    
    
    
    
    else if (OutName.find("WWTo2L2Nu_powheg") != string::npos) return  12.178 ;
    else if (OutName.find("WWTo4Q_powheg") != string::npos) return  51.723 ;
    else if (OutName.find("WWToLNuQQ_powheg") != string::npos) return  49.997 ;
    
    else if (OutName.find("WZTo1L3Nu_amcatnloFXFX") != string::npos) return 3.033e+00;
    else if (OutName.find("WZTo2L2Q_amcatnloFXFX") != string::npos) return  5.595 ;
    else if (OutName.find("WZTo2Q2Nu_amcatnloFXFX") != string::npos) return 10.000; // NOTE THIS IS JUST MY ESTIMATION small effect
    else if (OutName.find("WZTo3LNu_powheg") != string::npos) return  4.42965 ;
    else if (OutName.find("WZToLNu2Q_powheg") != string::npos) return  10.71 ;
    // The missing one is WZto4Q
    
    else if (OutName.find("ZZTo2L2Nu_powheg") != string::npos) return  0.564 ;
    else if (OutName.find("ZZTo2L2Q_powheg") != string::npos) return  3.22 ;
    else if (OutName.find("ZZTo2Q2Nu_powheg") != string::npos) return  4.04 ;
    else if (OutName.find("ZZTo4L_powheg") != string::npos) return  1.212 ;
    else if (OutName.find("ZZTo4Q_amcatnloFXFX") != string::npos) return 6.000;   // NOTE THIS IS JUST MY ESTIMATION
    // The missing one is ZZto4Nu
    
    
    
    
    
    
    //SingleTop
    else if (OutName.find("ST_t-channel_antitop") != string::npos) return 80.95;
    else if (OutName.find("ST_t-channel_top") != string::npos) return 136.02;
    else if (OutName.find("ST_tW_antitop_5f") != string::npos) return 35.6;
    else if (OutName.find("ST_tW_top_5f") != string::npos) return 35.6;
    
    
    else if (OutName.find("TTJets") != string::npos) return (831.76);
    
    //    //    https://twiki.cern.ch/twiki/bin/view/CMS/Exo2015LQ1AndLQ2Analyses
    //    else if (OutName.find("skimed_lq200") != string::npos) return 60.6;
    //    else if (OutName.find("skimed_lq250") != string::npos) return 20.3;
    //    else if (OutName.find("skimed_lq300") != string::npos) return     8.05E+00;
    //    else if (OutName.find("skimed_lq350") != string::npos) return     3.58E+00;
    //    else if (OutName.find("skimed_lq400") != string::npos) return     1.74E+00;
    //    else if (OutName.find("skimed_lq450") != string::npos) return     9.05E-01;
    //    else if (OutName.find("skimed_lq500") != string::npos) return     4.96E-01;
    //    else if (OutName.find("skimed_lq550") != string::npos) return     2.84E-01;
    //    else if (OutName.find("skimed_lq600") != string::npos) return     1.69E-01;
    //    else if (OutName.find("skimed_lq650") != string::npos) return     1.03E-01;
    //    else if (OutName.find("skimed_lq700") != string::npos) return     6.48E-02;
    //    else if (OutName.find("skimed_lq750") != string::npos) return     4.16E-02;
    //    else if (OutName.find("skimed_lq800") != string::npos) return     2.73E-02;
    //    else if (OutName.find("skimed_lq850") != string::npos) return     1.82E-02;
    //    else if (OutName.find("skimed_lq900") != string::npos) return     1.23E-02;
    //    else if (OutName.find("skimed_lq950") != string::npos) return     8.45E-03;
    //    else if (OutName.find("skimed_lq1000") != string::npos) return     5.86E-03;
    //    else if (OutName.find("skimed_lq1050") != string::npos) return     4.11E-03;
    //    else if (OutName.find("skimed_lq1100") != string::npos) return     2.91E-03;
    //    else if (OutName.find("skimed_lq1150") != string::npos) return     2.08E-03;
    //    else if (OutName.find("skimed_lq1200") != string::npos) return     1.50E-03;
    //    else if (OutName.find("skimed_lq1250") != string::npos) return     1.09E-03;
    //    else if (OutName.find("skimed_lq1300") != string::npos) return     7.95E-04;
    //    else if (OutName.find("skimed_lq1350") != string::npos) return     5.85E-04;
    //    else if (OutName.find("skimed_lq1400") != string::npos) return     4.33E-04;
    //    else if (OutName.find("skimed_lq1450") != string::npos) return     3.21E-04;
    //    else if (OutName.find("skimed_lq1500") != string::npos) return     2.40E-04;
    //
    //
    //
    
    else if (OutName.find("Codex") != string::npos ) return      1.0;
    
    
    
    else if (OutName.find("QCD_Pt-20toInf_MuEnrichedPt15") != string::npos) return     720648000  * 0.00042 ;
    else if (OutName.find("QCD") != string::npos) return     720648000  * 0.00042 ;
    
    //    https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets
    
    else if (OutName.find("WJetsToLNu_FXFX") != string::npos) return  61526.7   ;
    else if (OutName.find("WJetsToLNu_Pt-50To100_FXFX") != string::npos) return  8053   ;
    else if (OutName.find("WJetsToLNu_Pt-100To250_FXFX") != string::npos) return  676.3   ;
    else if (OutName.find("WJetsToLNu_Pt-250To400_FXFX") != string::npos) return  23.94   ;
    else if (OutName.find("WJetsToLNu_Pt-400To600_FXFX") != string::npos) return  3.031   ;
    else if (OutName.find("WJetsToLNu_Pt-600ToInf_FXFX") != string::npos) return  0.4524   ;
    
    
    
    else if (OutName.find("DYJetsToLL_M-50_FXFX") != string::npos) return          5765.4 ;
    else if (OutName.find("DYJetsToLL_Pt-100To250_FXFX") != string::npos) return   83.12 ;
    else if (OutName.find("DYJetsToLL_Pt-250To400_FXFX") != string::npos) return   3.047 ;
    else if (OutName.find("DYJetsToLL_Pt-400To650_FXFX") != string::npos) return   0.3921 ;
    else if (OutName.find("DYJetsToLL_Pt-650ToInf_FXFX") != string::npos) return   0.03636 ;
    
    else if (OutName.find("LQ") != string::npos ) return      1.0;
    
    
    
    else {
        cout<<"\n\n*********\nNot Listed in XSection menu !!!! Watch cout    "<<OutName<< "\n\n*********\n";
        return 1;
    }
}


//##################################################################
//   Needed for Stitching for LO W and Z
//##################################################################


vector <float> W_HTBin(std::string FileLoc){

    const int WSize=8;
    std::string W_ROOTFiles[WSize]={"WJetsToLNu_Inc.root", "WJetsToLNu_HT-100To200.root","WJetsToLNu_HT-200To400.root","WJetsToLNu_HT-400To600.root", "WJetsToLNu_HT-600To800.root","WJetsToLNu_HT-800To1200.root","WJetsToLNu_HT-1200To2500.root","WJetsToLNu_HT-2500ToInf.root"};

    vector<float> W_events;
    W_events.clear();

    for (int i=0; i <WSize;i++){

        TFile * File_W = new TFile((FileLoc+W_ROOTFiles[i]).c_str());
        TH1F * Histo_W = (TH1F*) File_W->Get("hcount");
        W_events.push_back(Histo_W->GetBinContent(2));
        cout<<"Number of proccessed evenets for "<<W_ROOTFiles[i]<<" = "<<Histo_W->GetBinContent(2)<<"\n";
    }

    return W_events ;

}

//vector <float> DY_HTBin(std::string FileLoc){
//
//    const int DYSize=5;
//    std::string DY_ROOTFiles[DYSize]={"DYJetsToLL_M-50_Inc.root", "DYJetsToLL_M-50_HT-100to200.root","DYJetsToLL_M-50_HT-200to400.root","DYJetsToLL_M-50_HT-400to600.root", "DYJetsToLL_M-50_HT-600toInf.root"};
//
//    vector<float> DY_events;
//    DY_events.clear();
//
//    for (int i=0; i < DYSize;i++){
//
//        TFile * File_DY = new TFile((FileLoc+DY_ROOTFiles[i]).c_str());
//        TH1F * Histo_DY= (TH1F*) File_DY->Get("hcount");
//        DY_events.push_back(Histo_DY->GetBinContent(2));
//        cout<<"Number of proccessed evenets for "<<DY_ROOTFiles[i]<<" = "<<Histo_DY->GetBinContent(2)<<"\n";
//    }
//
//    return DY_events ;
//
//}



//##################################################################
//   Fill out a vector with the lumi weight for each FXFX W sample
//##################################################################

vector <float> W_PTBinNLO(std::string FileLoc){
    
    const int WSizeNLO=5;
    std::string W_ROOTFilesNLO[WSizeNLO]={"WJetsToLNu_FXFX.root",  "WJetsToLNu_Pt-100To250_FXFX.root","WJetsToLNu_Pt-250To400_FXFX.root","WJetsToLNu_Pt-400To600_FXFX.root", "WJetsToLNu_Pt-600ToInf_FXFX.root"};
    
    vector<float> W_eventsNLO;
    W_eventsNLO.clear();
    
    for (int i=0; i <WSizeNLO;i++){
        
        TFile * File_WNLO = new TFile((FileLoc+W_ROOTFilesNLO[i]).c_str());
        TH1F * Histo_WNLO = (TH1F*) File_WNLO->Get("hcount");
        W_eventsNLO.push_back(Histo_WNLO->GetBinContent(2));
        cout<<"Number of proccessed evenets for "<<W_ROOTFilesNLO[i]<<" = "<<Histo_WNLO->GetBinContent(2)<<"\n";
    }
    
    return W_eventsNLO ;
    
}




//##################################################################
//   Fill out a vector with the lumi weight for each FXFX DY sample
//##################################################################

vector <float> Z_PTBinNLO(std::string FileLoc){
    
    const int ZSizeNLO=5;
    std::string Z_ROOTFilesNLO[ZSizeNLO]={"DYJetsToLL_M-50_FXFX.root", "DYJetsToLL_Pt-100To250_FXFX.root", "DYJetsToLL_Pt-250To400_FXFX.root","DYJetsToLL_Pt-400To650_FXFX.root","DYJetsToLL_Pt-650ToInf_FXFX.root"};
    
    vector<float> Z_eventsNLO;
    Z_eventsNLO.clear();
    
    for (int i=0; i <ZSizeNLO;i++){
        
        TFile * File_ZNLO = new TFile((FileLoc+Z_ROOTFilesNLO[i]).c_str());
        TH1F * Histo_ZNLO = (TH1F*) File_ZNLO->Get("hcount");
        Z_eventsNLO.push_back(Histo_ZNLO->GetBinContent(2));
        cout<<"Number of proccessed evenets for "<<Z_ROOTFilesNLO[i]<<" = "<<Histo_ZNLO->GetBinContent(2)<<"\n";
    }
    
    return Z_eventsNLO ;
    
}








//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
//     For Analysis
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################


float weightCalc(TH1F *Histo,std::string outputName, float genHT) {
    
    
    stringstream ss(outputName);
    
    string token;
    string M;
    while (getline(ss,token, '/'))  M=token;
    
    std::string FirstPart = "";
    std::string LastPart = ".root";
    std::string newOut = M.substr(FirstPart.size());
    newOut = newOut.substr(0, newOut.size() - LastPart.size());
    
    
    //    float LOtoNLO_DY = 1.230888662;
    float LOtoNLO_DY = 1; // Now we boson have pt dependent SF
    //    float LOtoNLO_W = 1.213783784;
    float LOtoNLO_W = 1;  // Now we boson have pt dependent SF
    //    float luminosity=    12900;
    float luminosity=    35867;
    
    
    size_t isSingleMu = outputName.find("SingleMu");
    size_t isSingleEle = outputName.find("SingleEle");
    
    
    if (isSingleMu != string::npos || isSingleEle!= string::npos)   return 1;
    
    
    else if (genHT < 70 &&  newOut.find("WJetsToLNu_Inc") != string::npos) return luminosity * 50690*1.0 / Histo->GetBinContent(2) ;   // As we have large cut at Skim, this one is not needed
    else if (genHT >70 &&  newOut.find("WJetsToLNu_Inc") != string::npos) return 0 ;   // As we have large cut at Skim, this one is not needed
    
    
    else
        return luminosity * XSection(newOut)*1.0 / Histo->GetBinContent(2);
    
    
}


//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
//     ONLY for FXFX sample for K-factor Study
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################


float weightCalc_Stitching(TH1F *Histo,std::string outputName , float WPt, float ZPt, vector<float> W_eventsNLO,vector<float> Z_eventsNLO) {
    
    float luminosity=    35867;
    
    size_t isWjet = outputName.find("WJets");
    size_t isFXFX = outputName.find("FXFX");
    size_t isDYJet = outputName.find("DYJets");
    
    //##################################################################
    //   Stitching for  FXFX W sample
    //##################################################################
    if (isWjet != string::npos && isFXFX != string::npos) {
        
        if (WPt <= 100)                  return   luminosity / (W_eventsNLO[0] / XSection("WJetsToLNu_FXFX"));
        
        else if (WPt > 100 && WPt <= 250)return   luminosity / (W_eventsNLO[1] / XSection("WJetsToLNu_Pt-100To250_FXFX") + W_eventsNLO[0] / XSection("WJetsToLNu_FXFX"));
        else if (WPt > 250 && WPt <=400) return   luminosity / (W_eventsNLO[2] / XSection("WJetsToLNu_Pt-250To400_FXFX") + W_eventsNLO[0] / XSection("WJetsToLNu_FXFX"));
        else if (WPt > 400 && WPt <=600) return   luminosity / (W_eventsNLO[3] / XSection("WJetsToLNu_Pt-400To600_FXFX") + W_eventsNLO[0] / XSection("WJetsToLNu_FXFX"));
        else if (WPt > 600 )               return   luminosity / (W_eventsNLO[4] / XSection("WJetsToLNu_Pt-600ToInf_FXFX") + W_eventsNLO[0] / XSection("WJetsToLNu_FXFX"));
        else   {cout<<"**********   wooow  ********* There is a problem here\n";return 0;}
    }
    //##################################################################
    //   Stitching for  FXFX DY sample
    //##################################################################
    else if (isDYJet != string::npos && isFXFX != string::npos) {
        
        if (ZPt <= 100)                  return   luminosity / (Z_eventsNLO[0] / XSection("DYJetsToLL_M-50_FXFX"));
        else if (ZPt > 100 && ZPt <= 250)return   luminosity / (Z_eventsNLO[1] / XSection("DYJetsToLL_Pt-100To250_FXFX") + Z_eventsNLO[0] / XSection("DYJetsToLL_M-50_FXFX"));
        else if (ZPt > 250 && ZPt <=400) return   luminosity / (Z_eventsNLO[2] / XSection("DYJetsToLL_Pt-250To400_FXFX") + Z_eventsNLO[0] / XSection("DYJetsToLL_M-50_FXFX"));
        else if (ZPt > 400 && ZPt <=600) return   luminosity / (Z_eventsNLO[3] / XSection("DYJetsToLL_Pt-400To650_FXFX") + Z_eventsNLO[0] / XSection("DYJetsToLL_M-50_FXFX"));
        else if (ZPt > 600 )               return   luminosity / (Z_eventsNLO[4] / XSection("DYJetsToLL_Pt-650ToInf_FXFX") + Z_eventsNLO[0] / XSection("DYJetsToLL_M-50_FXFX"));
        else   {cout<<"**********   wooow  ********* There is a problem here\n";return 0;}
    }
    
    else{
        cout<<"\n\n*********\nNot a FXFX sample  !!!! Watch cout    "<<outputName<< "\n\n*********\n";
        return 1;}
}













