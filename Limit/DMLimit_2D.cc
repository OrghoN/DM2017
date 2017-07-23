#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "TPolyLine.h"
#include "TPad.h"
#include "TLatex.h"
#include "TMath.h"
#include "stdio.h"
#include "TBox.h"
#include "TPave.h"
#include "TPaveText.h"
#include "TColor.h"
#include "TGraphErrors.h"
#include <TPaletteAxis.h>
#include <iostream>     // std::cout, std::ostream, std::ios
#include <fstream>      // std::filebuf
#include <string>

void  SayHi(){
    
    std::cout<<"Hi  ---->\n";
};


#include <string>
#include <ostream>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include "TLorentzVector.h"



#include <stdlib.h>
#include "cJSON.h"

////using namespace std;
//
///* Parse text to JSON, then render back to text, and print! */
//void doit(char *text)
//{
//    char *out;cJSON *json;
//
//    json=cJSON_Parse(text);
//    if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
//    else
//    {
//        out=cJSON_Print(json);
//        cJSON_Delete(json);
////        if (std::string(out)==std::string("	},")) printf("%s\n",out);
//        std::cout<<out<<"\n";
//        std::cout << "The size of the chars is: "
//        << strlen( out )
//        << " chars (including null)\n";
////        printf("%s\n",out);
//        free(out);
//    }
//}
//
///* Read a file, parse, render back, etc. */
//void dofile(char *filename)
//{
//    FILE *f;long len;char *data;
//
//    f=fopen(filename,"rb");fseek(f,0,SEEK_END);len=ftell(f);fseek(f,0,SEEK_SET);
//    data=(char*)malloc(len+1);fread(data,1,len,f);data[len]='\0';fclose(f);
//    doit(data);
//    free(data);
//}


double intersection(double m1, double m2,
                    double y11, double y12, double y21, double y22) {
    // y = ax + b
    // y11 = am1 + b
    // y12 = am2 + b
    double a1 = (y11 - y12)/(m1 - m2);
    double b1 = y11 - a1*m1;
    
    double a2 = (y21 - y22)/(m1 - m2);
    double b2 = y21 - a2*m1;
    
    // overlap: a1*m + b1 = a2*m + b2 => (a1 - a2)*m = (b2 - b1)
    double m = (b2 - b1)/(a1 - a2);
    if ( m > m2 || m < m1 ) return 0;
    return m;
}




void DMLimit_2D(){
    using namespace std;
    //=========Macro generated from canvas: can2/can2
    //=========  (Wed Oct 14 14:57:25 2015) by ROOT version5.32/04
    //   TCanvas *can2 = new TCanvas("can2", "can2",183,30,800,746);
    TCanvas* can2 = new TCanvas("can2", "can2",800,800);
    SayHi();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    can2->Range(-20.96775,-3.205128,785.4839,48.07692);
    can2->SetFillColor(0);
    can2->SetBorderMode(0);
    can2->SetBorderSize(2);
    can2->SetTickx(1);
    can2->SetTicky(1);
    
    can2->SetBottomMargin(0.16);
    
    can2->SetLeftMargin(0.15);
    
    can2->SetRightMargin(0.23);
    
    can2->SetTopMargin(0.06);
    
    can2->SetFrameFillColor(1);
    can2->SetFrameFillStyle(0);
    can2->SetFrameLineStyle(0);
    can2->SetFrameBorderMode(0);
    can2->SetFrameFillColor(1);
    can2->SetFrameFillStyle(0);
    can2->SetFrameLineStyle(0);
    can2->SetFrameBorderMode(0);
//    can2->SetLogz();
    
    
    
    TH2D *hlimitxsec2 = new TH2D("hlimitxsec2","hlimitxsec2",8,750,1550,9,275,725);
    hlimitxsec2->SetBinContent(3,1,1.128906); // Bin_1_LQ_1000_DM_300_X_330
    hlimitxsec2->SetBinContent(3,2,1.167969); // Bin_2_LQ_1000_DM_350_X_385
    hlimitxsec2->SetBinContent(3,3,1.222656); // Bin_3_LQ_1000_DM_400_X_440
    hlimitxsec2->SetBinContent(3,4,1.152344); // Bin_4_LQ_1000_DM_450_X_495
    hlimitxsec2->SetBinContent(4,1,0.878906); // Bin_5_LQ_1100_DM_300_X_330
    hlimitxsec2->SetBinContent(4,2,0.925781); // Bin_6_LQ_1100_DM_350_X_385
    hlimitxsec2->SetBinContent(4,3,0.925781); // Bin_7_LQ_1100_DM_400_X_440
    hlimitxsec2->SetBinContent(4,4,0.980469); // Bin_8_LQ_1100_DM_450_X_495
    hlimitxsec2->SetBinContent(4,5,0.902344); // Bin_9_LQ_1100_DM_500_X_550
    hlimitxsec2->SetBinContent(5,1,0.740234); // Bin_10_LQ_1200_DM_300_X_330
    hlimitxsec2->SetBinContent(5,2,0.728516); // Bin_11_LQ_1200_DM_350_X_385
    hlimitxsec2->SetBinContent(5,3,0.732422); // Bin_12_LQ_1200_DM_400_X_440
    hlimitxsec2->SetBinContent(5,4,0.759766); // Bin_13_LQ_1200_DM_450_X_495
    hlimitxsec2->SetBinContent(5,5,0.800781); // Bin_14_LQ_1200_DM_500_X_550
    hlimitxsec2->SetBinContent(5,6,0.800781); // Bin_15_LQ_1200_DM_550_X_595
    hlimitxsec2->SetBinContent(6,1,0.638672); // Bin_16_LQ_1300_DM_300_X_330
    hlimitxsec2->SetBinContent(6,2,0.646484); // Bin_17_LQ_1300_DM_350_X_385
    hlimitxsec2->SetBinContent(6,3,0.648438); // Bin_18_LQ_1300_DM_400_X_440
    hlimitxsec2->SetBinContent(6,4,0.664062); // Bin_19_LQ_1300_DM_450_X_495
    hlimitxsec2->SetBinContent(6,5,0.632812); // Bin_20_LQ_1300_DM_500_X_550
    hlimitxsec2->SetBinContent(6,6,0.697266); // Bin_21_LQ_1300_DM_550_X_605
    hlimitxsec2->SetBinContent(6,7,0.669922); // Bin_22_LQ_1300_DM_600_X_660
    hlimitxsec2->SetBinContent(7,1,0.564453); // Bin_23_LQ_1400_DM_300_X_330
    hlimitxsec2->SetBinContent(7,2,0.595703); // Bin_24_LQ_1400_DM_350_X_385
    hlimitxsec2->SetBinContent(7,3,0.544922); // Bin_25_LQ_1400_DM_400_X_440
    hlimitxsec2->SetBinContent(7,4,0.587891); // Bin_26_LQ_1400_DM_450_X_495
    hlimitxsec2->SetBinContent(7,5,0.546875); // Bin_27_LQ_1400_DM_500_X_550
    hlimitxsec2->SetBinContent(7,6,0.564453); // Bin_28_LQ_1400_DM_550_X_605
    hlimitxsec2->SetBinContent(7,7,0.609375); // Bin_29_LQ_1400_DM_600_X_660
    hlimitxsec2->SetBinContent(7,8,0.564453); // Bin_30_LQ_1400_DM_650_X_715
    hlimitxsec2->SetBinContent(8,1,0.517578); // Bin_31_LQ_1500_DM_300_X_330
    hlimitxsec2->SetBinContent(8,2,0.509766); // Bin_32_LQ_1500_DM_350_X_385
    hlimitxsec2->SetBinContent(8,3,0.494141); // Bin_33_LQ_1500_DM_400_X_440
    hlimitxsec2->SetBinContent(8,4,0.505859); // Bin_34_LQ_1500_DM_450_X_495
    hlimitxsec2->SetBinContent(8,5,0.498047); // Bin_35_LQ_1500_DM_500_X_550
    hlimitxsec2->SetBinContent(8,6,0.486328); // Bin_36_LQ_1500_DM_550_X_605
    hlimitxsec2->SetBinContent(8,7,0.478516); // Bin_37_LQ_1500_DM_600_X_660
    hlimitxsec2->SetBinContent(8,8,0.537109); // Bin_38_LQ_1500_DM_650_X_715
    hlimitxsec2->SetBinContent(8,9,0.501953); // Bin_39_LQ_1500_DM_700_X_770
    hlimitxsec2->SetBinContent(1,1,1.960938); // Bin_40_LQ_800_DM_300_X_330
    hlimitxsec2->SetBinContent(1,2,1.757812); // Bin_41_LQ_800_DM_350_X_385
    hlimitxsec2->SetBinContent(2,1,1.425781); // Bin_42_LQ_900_DM_300_X_330
    hlimitxsec2->SetBinContent(2,2,1.570312); // Bin_43_LQ_900_DM_350_X_385
    hlimitxsec2->SetBinContent(2,3,1.441406); // Bin_44_LQ_900_DM_400_X_440
    hlimitxsec2->SetStats(0);
    
    
    TH2D *ExpctedExclusionLimit = new TH2D("ExpctedExclusionLimit","ExpctedExclusionLimit",6,1250,4250,12,875,3875);
    ExpctedExclusionLimit->SetBinContent(3,1,0.385292); // Bin_1_LQ_1000_DM_300_X_330
    ExpctedExclusionLimit->SetBinContent(3,2,0.398624); // Bin_2_LQ_1000_DM_350_X_385
    ExpctedExclusionLimit->SetBinContent(3,3,0.417289); // Bin_3_LQ_1000_DM_400_X_440
    ExpctedExclusionLimit->SetBinContent(3,4,0.393291); // Bin_4_LQ_1000_DM_450_X_495
    ExpctedExclusionLimit->SetBinContent(4,1,0.604059); // Bin_5_LQ_1100_DM_300_X_330
    ExpctedExclusionLimit->SetBinContent(4,2,0.636276); // Bin_6_LQ_1100_DM_350_X_385
    ExpctedExclusionLimit->SetBinContent(4,3,0.636276); // Bin_7_LQ_1100_DM_400_X_440
    ExpctedExclusionLimit->SetBinContent(4,4,0.673862); // Bin_8_LQ_1100_DM_450_X_495
    ExpctedExclusionLimit->SetBinContent(4,5,0.620168); // Bin_9_LQ_1100_DM_500_X_550
    ExpctedExclusionLimit->SetBinContent(5,1,0.986979); // Bin_10_LQ_1200_DM_300_X_330
    ExpctedExclusionLimit->SetBinContent(5,2,0.971354); // Bin_11_LQ_1200_DM_350_X_385
    ExpctedExclusionLimit->SetBinContent(5,3,0.976562); // Bin_12_LQ_1200_DM_400_X_440
    ExpctedExclusionLimit->SetBinContent(5,4,1.013021); // Bin_13_LQ_1200_DM_450_X_495
    ExpctedExclusionLimit->SetBinContent(5,5,1.067708); // Bin_14_LQ_1200_DM_500_X_550
    ExpctedExclusionLimit->SetBinContent(5,6,1.067708); // Bin_15_LQ_1200_DM_550_X_595
    ExpctedExclusionLimit->SetBinContent(6,1,1.606722); // Bin_16_LQ_1300_DM_300_X_330
    ExpctedExclusionLimit->SetBinContent(6,2,1.626376); // Bin_17_LQ_1300_DM_350_X_385
    ExpctedExclusionLimit->SetBinContent(6,3,1.631289); // Bin_18_LQ_1300_DM_400_X_440
    ExpctedExclusionLimit->SetBinContent(6,4,1.670597); // Bin_19_LQ_1300_DM_450_X_495
    ExpctedExclusionLimit->SetBinContent(6,5,1.591981); // Bin_20_LQ_1300_DM_500_X_550
    ExpctedExclusionLimit->SetBinContent(6,6,1.754127); // Bin_21_LQ_1300_DM_550_X_605
    ExpctedExclusionLimit->SetBinContent(6,7,1.685338); // Bin_22_LQ_1300_DM_600_X_660
    ExpctedExclusionLimit->SetBinContent(7,1,2.607174); // Bin_23_LQ_1400_DM_300_X_330
    ExpctedExclusionLimit->SetBinContent(7,2,2.751516); // Bin_24_LQ_1400_DM_350_X_385
    ExpctedExclusionLimit->SetBinContent(7,3,2.516960); // Bin_25_LQ_1400_DM_400_X_440
    ExpctedExclusionLimit->SetBinContent(7,4,2.715430); // Bin_26_LQ_1400_DM_450_X_495
    ExpctedExclusionLimit->SetBinContent(7,5,2.525982); // Bin_27_LQ_1400_DM_500_X_550
    ExpctedExclusionLimit->SetBinContent(7,6,2.607174); // Bin_28_LQ_1400_DM_550_X_605
    ExpctedExclusionLimit->SetBinContent(7,7,2.814665); // Bin_29_LQ_1400_DM_600_X_660
    ExpctedExclusionLimit->SetBinContent(7,8,2.607174); // Bin_30_LQ_1400_DM_650_X_715
    ExpctedExclusionLimit->SetBinContent(8,1,4.313151); // Bin_31_LQ_1500_DM_300_X_330
    ExpctedExclusionLimit->SetBinContent(8,2,4.248047); // Bin_32_LQ_1500_DM_350_X_385
    ExpctedExclusionLimit->SetBinContent(8,3,4.117839); // Bin_33_LQ_1500_DM_400_X_440
    ExpctedExclusionLimit->SetBinContent(8,4,4.215495); // Bin_34_LQ_1500_DM_450_X_495
    ExpctedExclusionLimit->SetBinContent(8,5,4.150391); // Bin_35_LQ_1500_DM_500_X_550
    ExpctedExclusionLimit->SetBinContent(8,6,4.052734); // Bin_36_LQ_1500_DM_550_X_605
    ExpctedExclusionLimit->SetBinContent(8,7,3.987630); // Bin_37_LQ_1500_DM_600_X_660
    ExpctedExclusionLimit->SetBinContent(8,8,4.475911); // Bin_38_LQ_1500_DM_650_X_715
    ExpctedExclusionLimit->SetBinContent(8,9,4.182943); // Bin_39_LQ_1500_DM_700_X_770
    ExpctedExclusionLimit->SetBinContent(1,1,0.143658); // Bin_40_LQ_800_DM_300_X_330
    ExpctedExclusionLimit->SetBinContent(1,2,0.128777); // Bin_41_LQ_800_DM_350_X_385
    ExpctedExclusionLimit->SetBinContent(2,1,0.231834); // Bin_42_LQ_900_DM_300_X_330
    ExpctedExclusionLimit->SetBinContent(2,2,0.255335); // Bin_43_LQ_900_DM_350_X_385
    ExpctedExclusionLimit->SetBinContent(2,3,0.234375); // Bin_44_LQ_900_DM_400_X_440

  
    
    TH2D *ObservedExclusionLimit = new TH2D("ObservedExclusionLimit","ObservedExclusionLimit",6,1250,4250,12,875,3875);
    ObservedExclusionLimit->SetBinContent(3,1,0.386274); // Bin_1_LQ_1000_DM_300_X_330
    ObservedExclusionLimit->SetBinContent(3,2,0.398505); // Bin_2_LQ_1000_DM_350_X_385
    ObservedExclusionLimit->SetBinContent(3,3,0.417866); // Bin_3_LQ_1000_DM_400_X_440
    ObservedExclusionLimit->SetBinContent(3,4,0.392601); // Bin_4_LQ_1000_DM_450_X_495
    ObservedExclusionLimit->SetBinContent(4,1,0.603250); // Bin_5_LQ_1100_DM_300_X_330
    ObservedExclusionLimit->SetBinContent(4,2,0.633537); // Bin_6_LQ_1100_DM_350_X_385
    ObservedExclusionLimit->SetBinContent(4,3,0.637537); // Bin_7_LQ_1100_DM_400_X_440
    ObservedExclusionLimit->SetBinContent(4,4,0.676276); // Bin_8_LQ_1100_DM_450_X_495
    ObservedExclusionLimit->SetBinContent(4,5,0.618270); // Bin_9_LQ_1100_DM_500_X_550
    ObservedExclusionLimit->SetBinContent(5,1,0.988830); // Bin_10_LQ_1200_DM_300_X_330
    ObservedExclusionLimit->SetBinContent(5,2,0.970691); // Bin_11_LQ_1200_DM_350_X_385
    ObservedExclusionLimit->SetBinContent(5,3,0.975384); // Bin_12_LQ_1200_DM_400_X_440
    ObservedExclusionLimit->SetBinContent(5,4,1.011646); // Bin_13_LQ_1200_DM_450_X_495
    ObservedExclusionLimit->SetBinContent(5,5,1.064251); // Bin_14_LQ_1200_DM_500_X_550
    ObservedExclusionLimit->SetBinContent(5,6,1.064251); // Bin_15_LQ_1200_DM_550_X_595
    ObservedExclusionLimit->SetBinContent(6,1,1.604753); // Bin_16_LQ_1300_DM_300_X_330
    ObservedExclusionLimit->SetBinContent(6,2,1.629778); // Bin_17_LQ_1300_DM_350_X_385
    ObservedExclusionLimit->SetBinContent(6,3,1.630510); // Bin_18_LQ_1300_DM_400_X_440
    ObservedExclusionLimit->SetBinContent(6,4,1.668278); // Bin_19_LQ_1300_DM_450_X_495
    ObservedExclusionLimit->SetBinContent(6,5,1.594519); // Bin_20_LQ_1300_DM_500_X_550
    ObservedExclusionLimit->SetBinContent(6,6,1.760214); // Bin_21_LQ_1300_DM_550_X_605
    ObservedExclusionLimit->SetBinContent(6,7,1.691553); // Bin_22_LQ_1300_DM_600_X_660
    ObservedExclusionLimit->SetBinContent(7,1,2.616200); // Bin_23_LQ_1400_DM_300_X_330
    ObservedExclusionLimit->SetBinContent(7,2,2.758427); // Bin_24_LQ_1400_DM_350_X_385
    ObservedExclusionLimit->SetBinContent(7,3,2.518132); // Bin_25_LQ_1400_DM_400_X_440
    ObservedExclusionLimit->SetBinContent(7,4,2.725046); // Bin_26_LQ_1400_DM_450_X_495
    ObservedExclusionLimit->SetBinContent(7,5,2.529306); // Bin_27_LQ_1400_DM_500_X_550
    ObservedExclusionLimit->SetBinContent(7,6,2.610252); // Bin_28_LQ_1400_DM_550_X_605
    ObservedExclusionLimit->SetBinContent(7,7,2.817858); // Bin_29_LQ_1400_DM_600_X_660
    ObservedExclusionLimit->SetBinContent(7,8,2.613974); // Bin_30_LQ_1400_DM_650_X_715
    ObservedExclusionLimit->SetBinContent(8,1,4.297786); // Bin_31_LQ_1500_DM_300_X_330
    ObservedExclusionLimit->SetBinContent(8,2,4.246777); // Bin_32_LQ_1500_DM_350_X_385
    ObservedExclusionLimit->SetBinContent(8,3,4.101127); // Bin_33_LQ_1500_DM_400_X_440
    ObservedExclusionLimit->SetBinContent(8,4,4.207039); // Bin_34_LQ_1500_DM_450_X_495
    ObservedExclusionLimit->SetBinContent(8,5,4.152112); // Bin_35_LQ_1500_DM_500_X_550
    ObservedExclusionLimit->SetBinContent(8,6,4.053450); // Bin_36_LQ_1500_DM_550_X_605
    ObservedExclusionLimit->SetBinContent(8,7,3.997823); // Bin_37_LQ_1500_DM_600_X_660
    ObservedExclusionLimit->SetBinContent(8,8,4.476638); // Bin_38_LQ_1500_DM_650_X_715
    ObservedExclusionLimit->SetBinContent(8,9,4.169279); // Bin_39_LQ_1500_DM_700_X_770
    ObservedExclusionLimit->SetBinContent(1,1,0.144124); // Bin_40_LQ_800_DM_300_X_330
    ObservedExclusionLimit->SetBinContent(1,2,0.129052); // Bin_41_LQ_800_DM_350_X_385
    ObservedExclusionLimit->SetBinContent(2,1,0.231627); // Bin_42_LQ_900_DM_300_X_330
    ObservedExclusionLimit->SetBinContent(2,2,0.256334); // Bin_43_LQ_900_DM_350_X_385
    ObservedExclusionLimit->SetBinContent(2,3,0.234216); // Bin_44_LQ_900_DM_400_X_440

    
    
//    Double_t XS[6] = {2.9E-1,6.563E-02,1.92E-02,6.030E-03,0.00209,0.000801};
    
    
    Double_t WMass[8] = {
        800,
        900,
        1000,
        1100,
        1200,
        1300,
        1400,
        1500};
    
    
    Double_t NuMass[8] = {
        300,
        350,
        400,
        450,
        500,
        550,
        600,
        650,
    };
    
    
    
    vector <float> exclusion_expected;
    vector <float> exclusion_observed;
    exclusion_expected.clear();
    exclusion_observed.clear();
    
    
    //    for (int ii =1 ; ii < ExpctedExclusionLimit->GetXaxis()->GetNbins()+1; ii++){
    //        for (int jj =1 ; jj < ExpctedExclusionLimit->GetYaxis()->GetNbins()+1; jj++){
    //
    //            ExpctedExclusionLimit->SetBinContent(ii,jj, hlimitxsec2->GetBinContent(ii,jj)/(XS[ii-1]*1000));
    //            cout<<ii<<" "<< jj<< " "<< ExpctedExclusionLimit->GetBinContent(ii,jj)<<"\n";
    //
    //        }
    //
    //
    //    }
    
    
    
    for (int jj =1 ; jj < ExpctedExclusionLimit->GetYaxis()->GetNbins()+1; jj++){
        float ExpLim =0;
        float ObsLim =0;
        
        for (int ii =1 ; ii < ExpctedExclusionLimit->GetXaxis()->GetNbins()+1; ii++){
            
            
            
             ExpLim = intersection(WMass[ii-1], WMass[ii], 1, 1, ExpctedExclusionLimit->GetBinContent(ii,jj), ExpctedExclusionLimit->GetBinContent(ii+1,jj));
             ObsLim = intersection(WMass[ii-1], WMass[ii], 1, 1, ObservedExclusionLimit->GetBinContent(ii,jj), ObservedExclusionLimit->GetBinContent(ii+1,jj));
            
            
            if (ExpLim) break;
        }
            if (ExpLim && ExpLim < 1500) {
                
            cout <<NuMass[jj-1] <<" Exp="<<ExpLim<< "    &&&&&&&  Obs="<<ObsLim<<"\n";
                
                
//                if (ExpLim > NuMass[jj-1] &&  ObsLim > NuMass[jj-1]){
                exclusion_expected.push_back(ExpLim);
                exclusion_observed.push_back(ObsLim);
//                }
            
        }
    }
    
    
    cout<<exclusion_expected.size()<<"    "<<exclusion_observed.size()<<"\n";
    
    
 
    
    
    Int_t ck;   // for color index setting
    ck = TColor::GetColor("#000099");
    hlimitxsec2->SetLineColor(ck);
    hlimitxsec2->GetYaxis()->SetTitle("M_{DM} (GeV)");
    hlimitxsec2->GetXaxis()->SetNdivisions(505);
    hlimitxsec2->GetXaxis()->SetLabelFont(42);
    hlimitxsec2->GetXaxis()->SetLabelOffset(0.007);
    hlimitxsec2->GetXaxis()->SetLabelSize(0.035);
    hlimitxsec2->GetXaxis()->SetTitleSize(0.05);
    hlimitxsec2->GetXaxis()->SetTitleFont(42);
    hlimitxsec2->GetXaxis()->SetTitle("M_{LQ} (GeV)");
    hlimitxsec2->GetYaxis()->SetNdivisions(505);
    hlimitxsec2->GetYaxis()->SetLabelFont(42);
    hlimitxsec2->GetYaxis()->SetLabelOffset(0.007);
    hlimitxsec2->GetYaxis()->SetLabelSize(0.035);
    hlimitxsec2->GetYaxis()->SetTitleSize(0.05);
    hlimitxsec2->GetYaxis()->SetTitleFont(42);
    hlimitxsec2->GetZaxis()->SetNdivisions(505);
    hlimitxsec2->GetZaxis()->SetLabelFont(42);
    hlimitxsec2->GetZaxis()->SetLabelOffset(0.007);
    hlimitxsec2->GetZaxis()->SetLabelSize(0.035);
    hlimitxsec2->GetZaxis()->SetTitleSize(0.045);
    hlimitxsec2->GetZaxis()->SetTitleFont(42);
    hlimitxsec2->Draw("COLZ ");
    
    
    
    
    
    TGraphErrors *gre = new TGraphErrors(exclusion_observed.size()-2);
    gre->SetName("Graph");
    gre->SetTitle("Graph");
    gre->SetFillColor(1);
//    gre->SetLineStyle(10);
    gre->SetLineWidth(4);
    
    
    for (int kk=0;kk<exclusion_observed.size()-2;kk++){
        
        gre->SetPoint(kk, exclusion_observed[kk], NuMass[kk]);
        gre->SetPointError(kk,0,0);
        cout <<"Obs----->"<<kk<< " " <<exclusion_observed[kk]<< " "  <<NuMass[kk]<<"\n";
        
    }
    
    
    TH1F *Graph_Graph_Graph11 = new TH1F("Graph_Graph_Graph11","Graph",12,875,3875);
    Graph_Graph_Graph11->SetDirectory(0);
    Graph_Graph_Graph11->SetStats(0);
    
    cj = TColor::GetColor("#000099");
    Graph_Graph_Graph11->SetLineColor(cj);
    Graph_Graph_Graph11->GetXaxis()->SetNdivisions(505);
    Graph_Graph_Graph11->GetXaxis()->SetLabelFont(42);
    Graph_Graph_Graph11->GetXaxis()->SetLabelOffset(0.007);
    Graph_Graph_Graph11->GetXaxis()->SetLabelSize(0.035);
    Graph_Graph_Graph11->GetXaxis()->SetTitleSize(0.045);
    Graph_Graph_Graph11->GetXaxis()->SetTitleFont(42);
    Graph_Graph_Graph11->GetYaxis()->SetNdivisions(505);
    Graph_Graph_Graph11->GetYaxis()->SetLabelFont(42);
    Graph_Graph_Graph11->GetYaxis()->SetLabelOffset(0.007);
    Graph_Graph_Graph11->GetYaxis()->SetLabelSize(0.035);
    Graph_Graph_Graph11->GetYaxis()->SetTitleSize(0.045);
    Graph_Graph_Graph11->GetYaxis()->SetTitleFont(42);
    Graph_Graph_Graph11->GetZaxis()->SetNdivisions(505);
    Graph_Graph_Graph11->GetZaxis()->SetLabelFont(42);
    Graph_Graph_Graph11->GetZaxis()->SetLabelOffset(0.007);
    Graph_Graph_Graph11->GetZaxis()->SetLabelSize(0.035);
    Graph_Graph_Graph11->GetZaxis()->SetTitleSize(0.045);
    Graph_Graph_Graph11->GetZaxis()->SetTitleFont(42);
    gre->SetHistogram(Graph_Graph_Graph11);
    gre->SetMarkerSize(2);
    gre->SetMarkerStyle(21);
//    gre->Draw("cp");
    
    
    
    
    
    
    TGraphErrors *greExp = new TGraphErrors(exclusion_observed.size()-2);
    greExp->SetName("Graph");
    greExp->SetTitle("Graph");
    greExp->SetFillColor(1);
    greExp->SetLineStyle(2);
    greExp->SetLineWidth(3);

    for (int kk=0;kk<exclusion_expected.size()-2;kk++){
        
        greExp->SetPoint(kk, exclusion_expected[kk], NuMass[kk]);
        greExp->SetPointError(kk,0,0);
        cout <<"Exp----->"<<kk<< " " <<exclusion_expected[kk]<< " "  <<NuMass[kk]<<"\n";
        
    }
    
    
    TH1F *Graph_Graph_Graph11Exp = new TH1F("Graph_Graph_Graph11Exp","Graph",1100,1000,3250);
    Graph_Graph_Graph11Exp->SetDirectory(0);
    Graph_Graph_Graph11Exp->SetStats(0);
    
    Int_t ci;
    ci = TColor::GetColor("#000099");
    Graph_Graph_Graph11Exp->SetLineColor(ci);
    Graph_Graph_Graph11Exp->GetXaxis()->SetNdivisions(505);
    Graph_Graph_Graph11Exp->GetXaxis()->SetLabelFont(42);
    Graph_Graph_Graph11Exp->GetXaxis()->SetLabelOffset(0.007);
    Graph_Graph_Graph11Exp->GetXaxis()->SetLabelSize(0.035);
    Graph_Graph_Graph11Exp->GetXaxis()->SetTitleSize(0.045);
    Graph_Graph_Graph11Exp->GetXaxis()->SetTitleFont(42);
    Graph_Graph_Graph11Exp->GetYaxis()->SetNdivisions(505);
    Graph_Graph_Graph11Exp->GetYaxis()->SetLabelFont(42);
    Graph_Graph_Graph11Exp->GetYaxis()->SetLabelOffset(0.007);
    Graph_Graph_Graph11Exp->GetYaxis()->SetLabelSize(0.035);
    Graph_Graph_Graph11Exp->GetYaxis()->SetTitleSize(0.045);
    Graph_Graph_Graph11Exp->GetYaxis()->SetTitleFont(42);
    Graph_Graph_Graph11Exp->GetZaxis()->SetNdivisions(505);
    Graph_Graph_Graph11Exp->GetZaxis()->SetLabelFont(42);
    Graph_Graph_Graph11Exp->GetZaxis()->SetLabelOffset(0.007);
    Graph_Graph_Graph11Exp->GetZaxis()->SetLabelSize(0.035);
    Graph_Graph_Graph11Exp->GetZaxis()->SetTitleSize(0.045);
    Graph_Graph_Graph11Exp->GetZaxis()->SetTitleFont(42);
    greExp->SetHistogram(Graph_Graph_Graph11Exp);
    
    greExp->SetMarkerSize(2);
    greExp->SetMarkerStyle(21);
    greExp->Draw("cp");
    
    TLegend *legendr = new TLegend(0.15,0.75,0.47,0.90,NULL,"brNDC");
    
    legendr->SetShadowColor(0);
    legendr->SetBorderSize(0);
    legendr->SetFillColor(0);
    legendr->AddEntry(gre,"Observed","L");
    legendr->AddEntry(greExp, "Expected", "L");
    legendr->SetFillStyle(0);
    legendr->SetTextSize(.04);
    
    legendr->SetTextFont(42);
    
    legendr->SetFillColor(0);
    
    legendr->SetBorderSize(0);
    
    legendr->Draw();
    
    
    
    
//    TLatex* tx = new TLatex(1600,.9101,"CMS");
//    tx->SetTextSize(0.05);
//    tx->Draw("SAME");
//    TLatex* tx2 = new TLatex(3000,.9101,"12.9 fb^{-1} (13 TeV)");
//    tx2->SetTextSize(0.04);
//    tx2->Draw("SAME");
    
    
    
//    
    TPaveText *pt = new TPaveText(0.1072864,0.9618663,0.4080402,0.9820056,"brNDC");
    
    pt->SetBorderSize(0);
    
    pt->SetFillColor(0);
    
    pt->SetLineColor(0);
    pt->SetTextSize(0.05);
    
    
    TText *textL = pt->AddText("CMS Preliminary");
//    textL->SetTextFont(42);
    pt->Draw();
    
    TText *textL2 = pt->AddText("                                                                                           35.9 fb^{-1} (13 TeV)");
    pt->SetTextSize(0.04);
    pt->Draw("samep");
    
    
    
    
    TText *text = new TText(4900,1404.522,"Cross section UL at 95% CL [fb]");
    text->SetTextFont(42);
    text->SetTextSize(0.04748603);
    text->SetTextAngle(90);
    text->Draw();
    can2->Modified();
    can2->cd();
    can2->SetSelected(can2);
    can2->SaveAs("lim2D.pdf");
    //     dofile("rhw.json");
    
}