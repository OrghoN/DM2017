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
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
using namespace std;




float getBtagEfficiency(bool isData, bool passCSV, float pt, float eta, TH2F ** Btagg_TT){
    
    
    if ( isData) return 1;
    
    
    
    int ptBIN;
    if ( pt < 50 ) ptBIN=1;
    if (pt >= 50 && pt < 70 ) ptBIN=2;
    if (pt >= 70 && pt < 100 ) ptBIN=3;
    if (pt >= 100 && pt < 140) ptBIN=4;
    if (pt >= 140 && pt < 200) ptBIN=5;
    if (pt >= 200 && pt < 300) ptBIN=6;
    if (pt >= 300 && pt < 600) ptBIN=7;
    if (pt >= 600 ) ptBIN=8;
    
    int etaBIN;
    if (eta >= 0 && eta < 0.8 ) etaBIN=1;
    if (eta >= 0.8 && eta < 1.5 ) etaBIN=2;
    if (eta >= 1.5 ) etaBIN=3;
    
    
    
    TH2F * TTSF0_btagged=Btagg_TT[0];
    TH2F * TTSF0_total=Btagg_TT[1];
    TH2F * TTSF5_btagged=Btagg_TT[2];
    TH2F * TTSF5_total=Btagg_TT[3];
    
    //    cout << "Btag efficiency is = "<< pt << " ptBIN " <<ptBIN << "   "<<eta << " etaBIN " << etaBIN <<"  ratio=  " <<TTSF0_btagged->GetBinContent(ptBIN,etaBIN) << "    "<<TTSF0_total->GetBinContent(ptBIN,etaBIN) <<"\n";
    
    
    if (passCSV)
        return  TTSF5_btagged->GetBinContent(ptBIN,etaBIN)*1.0/TTSF5_total->GetBinContent(ptBIN,etaBIN);
    else
        return  TTSF0_btagged->GetBinContent(ptBIN,etaBIN)*1.0/TTSF0_total->GetBinContent(ptBIN,etaBIN);
    
    
}



float LandauFunc(float x){
    
    //return Landau(float x, Double_t mpv = 0, Double_t sigma = 1, Bool_t norm = kFALSE)
    
    float Land= 9.794 * TMath::Landau(x, 210, 137);
    if (x > 200)  Land= 9.794 * TMath::Landau(200, 210, 137);
    
    return Land;
    
}



// For light Jet
//2	 incl	 central	2	0	2.4	20	1000	0	1	 "0.963886+198.253/(x*x)+0.000871904*x"

//  for btagged jet
//2	 comb	 central	1	-2.4	2.4	20	1000	0	1	 "0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x)))"
//2	 comb	 central	0	-2.4	2.4	20	1000	0	1	 "0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x)))"




//-----------------------------------------------------------------------------
//https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration

//operatingPoint (loose = 0, medium = 1, tight = 2, disriminator reshaping = 3)
//measurementType (e.g. "ttbar", or "comb" for combination)
//sysType ("up", "central", "down", but arbitrary strings possible, like "up_generator" or "up_jec")
//jetFlavor (B = 0, C = 1, UDSG = 2)
//etaMin, etaMax
//ptMin, ptMax
//discrMin, discrMax (only for disriminator reshaping)
//(formula is the scale factor itself)
//
//-----------------------------------------------------------------------------
//0	 mujets	 central	0	-2.4	2.4	30	670	0	1	 "0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x)))"
//
//0	 mujets	 down	0	-2.4	2.4	30	50	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))-0.025967003777623177"
//0	 mujets	 down	0	-2.4	2.4	50	70	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))-0.024922125041484833"
//0	 mujets	 down	0	-2.4	2.4	70	100	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))-0.022432966157793999"
//0	 mujets	 down	0	-2.4	2.4	100	140	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))-0.027810061350464821"
//0	 mujets	 down	0	-2.4	2.4	140	200	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))-0.045993752777576447"
//0	 mujets	 down	0	-2.4	2.4	200	300	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))-0.060691386461257935"
//0	 mujets	 down	0	-2.4	2.4	300	670	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))-0.096668705344200134"
//
//0	 mujets	 up	0	-2.4	2.4	30	50	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))+0.025967003777623177"
//0	 mujets	 up	0	-2.4	2.4	50	70	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))+0.024922125041484833"
//0	 mujets	 up	0	-2.4	2.4	70	100	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))+0.022432966157793999"
//0	 mujets	 up	0	-2.4	2.4	100	140	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))+0.027810061350464821"
//0	 mujets	 up	0	-2.4	2.4	140	200	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))+0.045993752777576447"
//0	 mujets	 up	0	-2.4	2.4	200	300	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))+0.060691386461257935"
//0	 mujets	 up	0	-2.4	2.4	300	670	0	1	 "(0.953039*((1.+(0.00582506*x))/(1.+(0.00603666*x))))+0.096668705344200134"

//-----------------------------------------------------------------------------
//0	 comb	 central	0	-2.4	2.4	30	670	0	1	 "0.747498*((1.+(0.473236*x))/(1.+(0.375778*x)))"

//0	 comb	 down	0	-2.4	2.4	30	50	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))-0.018585335463285446"
//0	 comb	 down	0	-2.4	2.4	50	70	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))-0.018662562593817711"
//0	 comb	 down	0	-2.4	2.4	70	100	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))-0.018709532916545868"
//0	 comb	 down	0	-2.4	2.4	100	140	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))-0.027433760464191437"
//0	 comb	 down	0	-2.4	2.4	140	200	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))-0.045776486396789551"
//0	 comb	 down	0	-2.4	2.4	200	300	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))-0.060772690922021866"
//0	 comb	 down	0	-2.4	2.4	300	670	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))-0.098300635814666748"

//0	 comb	 up	0	-2.4	2.4	30	50	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))+0.018585335463285446"
//0	 comb	 up	0	-2.4	2.4	50	70	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))+0.018662562593817711"
//0	 comb	 up	0	-2.4	2.4	70	100	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))+0.018709532916545868"
//0	 comb	 up	0	-2.4	2.4	100	140	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))+0.027433760464191437"
//0	 comb	 up	0	-2.4	2.4	140	200	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))+0.045776486396789551"
//0	 comb	 up	0	-2.4	2.4	200	300	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))+0.060772690922021866"
//0	 comb	 up	0	-2.4	2.4	300	670	0	1	 "(0.747498*((1.+(0.473236*x))/(1.+(0.375778*x))))+0.098300635814666748"
//-----------------------------------------------------------------------------
//0	 incl	 central	2	0	2.4	20	1000	0	1	 "1.00317+0.000204778*x+7.49098e-07*x*x+-9.52146e-10*x*x*x"
//0	 incl	 down       2	0	2.4	20	1000	0	1	 "0.897474+0.000130807*x+8.17188e-07*x*x+-9.52657e-10*x*x*x"
//0	 incl	 up         2	0	2.4	20	1000	0	1	 "1.10884+0.000279575*x+6.77543e-07*x*x+-9.4973e-10*x*x*x"
//-----------------------------------------------------------------------------






//0	 comb	 central	1	-2.4	2.4	30	670	0	1	 "0.931535+(1.40704e-05*x)"  //These two are the same for b and c but uncertaities are different
//0	 comb	 central	0	-2.4	2.4	30	670	0	1	 "0.931535+(1.40704e-05*x)"

//0	 comb	 down	1	-2.4	2.4	30	50	0	1	 "0.931535+((1.40704e-05*x)-0.01710829883813858)"
//0	 comb	 down	1	-2.4	2.4	50	70	0	1	 "0.931535+((1.40704e-05*x)-0.020177565515041351)"
//0	 comb	 down	1	-2.4	2.4	70	100	0	1	 "0.931535+((1.40704e-05*x)-0.019350524991750717)"
//0	 comb	 down	1	-2.4	2.4	100	140	0	1	 "0.931535+((1.40704e-05*x)-0.027258865535259247)"
//0	 comb	 down	1	-2.4	2.4	140	200	0	1	 "0.931535+((1.40704e-05*x)-0.027310512959957123)"
//0	 comb	 down	1	-2.4	2.4	200	300	0	1	 "0.931535+((1.40704e-05*x)-0.039027795195579529)"
//0	 comb	 down	1	-2.4	2.4	300	670	0	1	 "0.931535+((1.40704e-05*x)-0.089093379676342122)"

//0	 comb	 down	0	-2.4	2.4	30	50	0	1	 "0.931535+((1.40704e-05*x)-0.0085541494190692902)"
//0	 comb	 down	0	-2.4	2.4	50	70	0	1	 "0.931535+((1.40704e-05*x)-0.010088782757520676)"
//0	 comb	 down	0	-2.4	2.4	70	100	0	1	 "0.931535+((1.40704e-05*x)-0.0096752624958753586)"
//0	 comb	 down	0	-2.4	2.4	100	140	0	1	 "0.931535+((1.40704e-05*x)-0.013629432767629623)"
//0	 comb	 down	0	-2.4	2.4	140	200	0	1	 "0.931535+((1.40704e-05*x)-0.013655256479978561)"
//0	 comb	 down	0	-2.4	2.4	200	300	0	1	 "0.931535+((1.40704e-05*x)-0.019513897597789764)"
//0	 comb	 down	0	-2.4	2.4	300	670	0	1	 "0.931535+((1.40704e-05*x)-0.044546689838171005)"

//0	 comb	 up	1	-2.4	2.4	30	50	0	1	 "(0.931535+(1.40704e-05*x))+0.01710829883813858"
//0	 comb	 up	1	-2.4	2.4	50	70	0	1	 "(0.931535+(1.40704e-05*x))+0.020177565515041351"
//0	 comb	 up	1	-2.4	2.4	70	100	0	1	 "(0.931535+(1.40704e-05*x))+0.019350524991750717"
//0	 comb	 up	1	-2.4	2.4	100	140	0	1	 "(0.931535+(1.40704e-05*x))+0.027258865535259247"
//0	 comb	 up	1	-2.4	2.4	140	200	0	1	 "(0.931535+(1.40704e-05*x))+0.027310512959957123"
//0	 comb	 up	1	-2.4	2.4	200	300	0	1	 "(0.931535+(1.40704e-05*x))+0.039027795195579529"
//0	 comb	 up	1	-2.4	2.4	300	670	0	1	 "(0.931535+(1.40704e-05*x))+0.089093379676342122"

//0	 comb	 up	0	-2.4	2.4	30	50	0	1	 "(0.931535+(1.40704e-05*x))+0.0085541494190692902"
//0	 comb	 up	0	-2.4	2.4	50	70	0	1	 "(0.931535+(1.40704e-05*x))+0.010088782757520676"
//0	 comb	 up	0	-2.4	2.4	70	100	0	1	 "(0.931535+(1.40704e-05*x))+0.0096752624958753586"
//0	 comb	 up	0	-2.4	2.4	100	140	0	1	 "(0.931535+(1.40704e-05*x))+0.013629432767629623"
//0	 comb	 up	0	-2.4	2.4	140	200	0	1	 "(0.931535+(1.40704e-05*x))+0.013655256479978561"
//0	 comb	 up	0	-2.4	2.4	200	300	0	1	 "(0.931535+(1.40704e-05*x))+0.019513897597789764"
//0	 comb	 up	0	-2.4	2.4	300	670	0	1	 "(0.931535+(1.40704e-05*x))+0.044546689838171005"








//0	 mujets	 central	0	-2.4	2.4	30	670	0	1	 "0.956768*((1.+(0.107522*x))/(1.+(0.110892*x)))"


//0	 incl	 central	2	0	2.4	20	1000	0	1	 "1.05636+0.000920353*x+-7.85916e-07*x*x+1.92221e-11*x*x*x"
//0	 incl	 down	2	0	2.4	20	1000	0	1	 "(1.05636+0.000920353*x+-7.85916e-07*x*x+1.92221e-11*x*x*x)*(1-(0.0539991+-6.29073e-06*x+-3.39895e-09*x*x))"
//0	 incl	 up	2	0	2.4	20	1000	0	1	 "(1.05636+0.000920353*x+-7.85916e-07*x*x+1.92221e-11*x*x*x)*(1+(0.0539991+-6.29073e-06*x+-3.39895e-09*x*x))"




//The name of the measurements is
//
//"incl" for light jets,
//"mujets" (from QCD methods only) or “comb” (combination of QCD and ttbar methods) for b and c jets for what concerns the pT/eta

//operatingPoint (loose = 0, medium = 1, tight = 2, disriminator reshaping = 3)
//measurementType (e.g. "ttbar", or "comb" for combination)
//sysType ("up", "central", "down", but arbitrary strings possible, like "up_generator" or "up_jec")
//jetFlavor (B = 0, C = 1, UDSG = 2)
//etaMin, etaMax
//ptMin, ptMax
//discrMin, discrMax (only for disriminator reshaping)
//(formula is the scale factor itself)


//************************************************************
//* https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration *
//************************************************************

//
//2	 incl	 central	2	0	2.4	20	1000	0	1	 "0.971945+163.215/(x*x)+0.000517836*x"
//2	 incl	 down	2	0	2.4	20	1000	0	1	 "(0.971945+163.215/(x*x)+0.000517836*x)*(1-(0.291298+-0.000222983*x+1.69699e-07*x*x))"
//2	 incl	 down_correlated	2	0	2.4	20	1000	0	1	 "(0.971945+163.215/(x*x)+0.000517836*x)*(1-(0.219249+-0.000309762*x+2.26184e-07*x*x))"
//2	 incl	 down_uncorrelated	2	0	2.4	20	1000	0	1	 "(0.971945+163.215/(x*x)+0.000517836*x)*(1-(0.190708))"
//2	 incl	 up	2	0	2.4	20	1000	0	1	 "(0.971945+163.215/(x*x)+0.000517836*x)*(1+(0.291298+-0.000222983*x+1.69699e-07*x*x))"
//2	 incl	 up_correlated	2	0	2.4	20	1000	0	1	 "(0.971945+163.215/(x*x)+0.000517836*x)*(1+(0.219249+-0.000309762*x+2.26184e-07*x*x))"
//2	 incl	 up_uncorrelated	2	0	2.4	20	1000	0	1	 "(0.971945+163.215/(x*x)+0.000517836*x)*(1+(0.190708))"
//
//
//
//
//
//
//
//2	 comb	 central	1	-2.4	2.4	20	1000	0	1	 "0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x)))"
//2	 comb	 central	0	-2.4	2.4	20	1000	0	1	 "0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x)))"
//
////2	 comb	 down	1	-2.4	2.4	20	30	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.11806446313858032"
//2	 comb	 down	1	-2.4	2.4	30	50	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.054699532687664032"
//2	 comb	 down	1	-2.4	2.4	50	70	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.047356218099594116"
//2	 comb	 down	1	-2.4	2.4	70	100	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.047634456306695938"
//2	 comb	 down	1	-2.4	2.4	100	140	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.04632849246263504"
//2	 comb	 down	1	-2.4	2.4	140	200	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.048323042690753937"
//2	 comb	 down	1	-2.4	2.4	200	300	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.068715795874595642"
//2	 comb	 down	1	-2.4	2.4	300	600	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.10824859887361526"
//2	 comb	 down	1	-2.4	2.4	600	1000	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.18500012159347534"
//
////2	 comb	 down	0	-2.4	2.4	20	30	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.033732704818248749"
//2	 comb	 down	0	-2.4	2.4	30	50	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.01562843844294548"
//2	 comb	 down	0	-2.4	2.4	50	70	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.013530348427593708"
//2	 comb	 down	0	-2.4	2.4	70	100	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.013609844259917736"
//2	 comb	 down	0	-2.4	2.4	100	140	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.013236711733043194"
//2	 comb	 down	0	-2.4	2.4	140	200	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.013806583359837532"
//2	 comb	 down	0	-2.4	2.4	200	300	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.019633084535598755"
//2	 comb	 down	0	-2.4	2.4	300	600	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.030928170308470726"
//2	 comb	 down	0	-2.4	2.4	600	1000	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.052857179194688797"
//
////2	 comb	 up	1	-2.4	2.4	20	30	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.11806446313858032"
//2	 comb	 up	1	-2.4	2.4	30	50	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.054699532687664032"
//2	 comb	 up	1	-2.4	2.4	50	70	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.047356218099594116"
//2	 comb	 up	1	-2.4	2.4	70	100	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.047634456306695938"
//2	 comb	 up	1	-2.4	2.4	100	140	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.04632849246263504"
//2	 comb	 up	1	-2.4	2.4	140	200	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.048323042690753937"
//2	 comb	 up	1	-2.4	2.4	200	300	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.068715795874595642"
//2	 comb	 up	1	-2.4	2.4	300	600	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.10824859887361526"
//2	 comb	 up	1	-2.4	2.4	600	1000	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.18500012159347534"
//
////2	 comb	 up	0	-2.4	2.4	20	30	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.033732704818248749"
//2	 comb	 up	0	-2.4	2.4	30	50	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.01562843844294548"
//2	 comb	 up	0	-2.4	2.4	50	70	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.013530348427593708"
//2	 comb	 up	0	-2.4	2.4	70	100	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.013609844259917736"
//2	 comb	 up	0	-2.4	2.4	100	140	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.013236711733043194"
//2	 comb	 up	0	-2.4	2.4	140	200	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.013806583359837532"
//2	 comb	 up	0	-2.4	2.4	200	300	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.019633084535598755"
//2	 comb	 up	0	-2.4	2.4	300	600	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.030928170308470726"
//2	 comb	 up	0	-2.4	2.4	600	1000	0	1	 "(0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.052857179194688797"
//
//






// Aplly Btag Scale Factor ----------------------------------------------------------------

float GetBJetSF(bool isData, float x, float jetEta, float jetHadFlvr){
    
    //    cout<< "--->Btag    pt= "<<x<<  "   jetHadFlvr" <<jetHadFlvr<< "  SF="<<1.05636+0.000920353*x+-7.85916e-07*x*x+1.92221e-11*x*x*x <<"   "<< 0.931535+(1.40704e-05*x) <<"\n";
    
    if (isData) return 1;
    else {
        if (jetHadFlvr ==0 )
            return 0.971945+163.215/(x*x)+0.000517836*x ;
        else if (jetHadFlvr ==4 || jetHadFlvr ==5 )
            return 0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x)));
        else
            return 1;
    }
}



//2	 comb	 central	1	-2.4	2.4	20	1000	0	1	 "0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x)))"
//2	 comb	 central	0	-2.4	2.4	20	1000	0	1	 "0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x)))"
//
//2	 incl	 central	2	0	2.4	20	1000	0	1	 "0.971945+163.215/(x*x)+0.000517836*x"


float GetBJetSFUp (bool isData,float x, float jetEta, float jetHadFlvr){
    
    if (isData) return 1;
    
    if (jetHadFlvr ==0 )
        return (1.05636+0.000920353*x+-7.85916e-07*x*x+1.92221e-11*x*x*x)*(1+(0.0539991+-6.29073e-06*x+-3.39895e-09*x*x)) ;
    //        return  1.10884+0.000279575*x+6.77543e-07*x*x+-9.4973e-10*x*x*x;
    
    else if (jetHadFlvr ==4  ){
        
        
        
        
        if (x >= 	30	 && x <50)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.054699532687664032;
        if (x >= 	50	 && x <70)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.047356218099594116;
        if (x >= 	70	 && x <100)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.047634456306695938;
        if (x >= 	100	 && x <140)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.04632849246263504;
        if (x >= 	140 && x <	200)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.048323042690753937;
        if (x >= 	200 && x <	300)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.068715795874595642;
        if (x >= 	300	 && x <600)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.10824859887361526;
        else return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.18500012159347534;
    }
    
    
    else if (jetHadFlvr ==5 ){
        
        
        
        
        
        if (x >= 	30	 && x <50)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.01562843844294548;
        if (x >= 	50	 && x <70)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.013530348427593708;
        if (x >= 	70	 && x <100)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.013609844259917736;
        if (x >= 	100	 && x <140)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.013236711733043194;
        if (x >= 	140 && x <	200)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.013806583359837532;
        if (x >= 	200 && x <	300)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.019633084535598755;
        if (x >= 	300	 && x <600)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.030928170308470726;
        else return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))+0.052857179194688797;
    }
    else
        
        return 1;
}


float GetBJetSFDown (bool isData,float x, float jetEta, float jetHadFlvr){
    
    if (isData) return 1;
    if (jetHadFlvr ==0 )
        return (1.05636+0.000920353*x+-7.85916e-07*x*x+1.92221e-11*x*x*x)*(1-(0.0539991+-6.29073e-06*x+-3.39895e-09*x*x))       ;
    //        return  0.897474+0.000130807*x+8.17188e-07*x*x+-9.52657e-10*x*x*x;
    
    else if (jetHadFlvr ==4 ){
        
        
        
        
        
        
        if (x >= 	30	 && x <50)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.054699532687664032;
        if (x >= 	50	 && x <70)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.047356218099594116;
        if (x >= 	70	 && x <100)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.047634456306695938;
        if (x >= 	100	 && x <140)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.04632849246263504;
        if (x >= 	140 && x <	200)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.048323042690753937;
        if (x >= 	200 && x <	300)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.068715795874595642;
        if (x >= 	300	 && x <600)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.10824859887361526;
        else return (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.18500012159347534;
        
    }
    else if (jetHadFlvr ==5 ){
        
        
        
        
        
        
        if (x >= 	30	 && x <50)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.01562843844294548;
        if (x >= 	50	 && x <70)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.013530348427593708;
        if (x >= 	70	 && x <100)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.013609844259917736;
        if (x >= 	100	 && x <140)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.013236711733043194;
        if (x >= 	140 && x <	200)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.013806583359837532;
        if (x >= 	200 && x <	300)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.019633084535598755;
        if (x >= 	300	 && x <600)  return   (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.030928170308470726;
        else return (0.817647*((1.+(0.038703*x))/(1.+(0.0312388*x))))-0.052857179194688797;
        
    }
    
    
    else
        
        return 1;
}


//-----------------------------------------------------------------------------

//  Apply W scale factor

float WShapeUnc(string InputROOT, float CLoseJetTauPt){
    
    
    //    if  (InputROOT.find("WJets"))
    //        return  LandauFunc(CLoseJetTauPt) ;
    //    else
    //        return 1;
    
    return 1;
}



//  Apply W k-factor scale factor


float Get_W_Z_BosonKFactor(float WBosonPt, TH1F* WLO, TH1F* WNLO){
    float LO=0;
    float NLO=0;
    float kfactor=1;
    for (int ibin =1; ibin < WLO->GetNbinsX()+1;ibin++){
        
        if ( WBosonPt > (WLO->GetBinCenter(ibin) - WLO->GetBinWidth(ibin)/2)   && WBosonPt < (WLO->GetBinCenter(ibin) + WLO->GetBinWidth(ibin)/2) ){
            LO=WLO->GetBinContent(ibin);
            NLO=WNLO->GetBinContent(ibin);
            kfactor=NLO/LO;
            //            cout << "    k-factor is "<<kfactor<<"\n";
            break;
        }
    }
    
    if ( WBosonPt < WLO->GetBinCenter(1) - WLO->GetBinWidth(1)/2){
        LO=WLO->GetBinContent(1);
        NLO=WNLO->GetBinContent(1);
        kfactor=NLO/LO;
    }
    if ( WBosonPt > WLO->GetBinCenter(WLO->GetNbinsX()) + WLO->GetBinWidth(WLO->GetNbinsX())/2){
        LO=WLO->GetBinContent(WLO->GetNbinsX());
        NLO=WNLO->GetBinContent(WLO->GetNbinsX());
        kfactor=NLO/LO;
    }
    
    //    cout << " WBosonPt = " << WBosonPt << "   & kfactor=" << kfactor<< "  WLO->GetBinCenter(1)="<<WLO->GetBinCenter(1) << " width=" << WLO->GetBinWidth(1)  <<  "\n";
    return kfactor;
    
    
}










int ptBIN=0;
int etaBIN=0;
int etaPOINT=-1;

//Lumi in fb-1 taken from  CMS AN-16-362
float LumiB=5.93;
float LumiC=2.65;
float LumiD=4.35;
float LumiE=4.12;
float LumiF=3.19;
float LumiG=7.72;
float LumiHv2=8.64;
float LumiHv3=0.22;

float LumiBCDEF=LumiB+LumiC+LumiD+LumiE+LumiF;
float LumiGH=LumiG+LumiHv2+LumiHv3;


//x min    x avg    x max     ratio    -err / +err
//------   ------   ------     -----  ------/------
//-2.400   -2.231   -2.100     98.79  - 0.27/+ 0.27
//-2.100   -1.828   -1.600     99.39  - 0.05/+ 0.04
//-1.600   -1.346   -1.100     99.70  - 0.03/+ 0.03
//-1.100   -0.843   -0.600     99.54  - 0.02/+ 0.02
//-0.600   -0.298    0.000     99.37  - 0.02/+ 0.02
//0.000    0.299    0.600     99.59  - 0.01/+ 0.01
//0.600    0.843    1.100     99.76  - 0.02/+ 0.02
//1.100    1.348    1.600     99.61  - 0.03/+ 0.03
//1.600    1.828    2.100     99.30  - 0.04/+ 0.04
//2.100    2.234    2.400     98.19  - 0.22/+ 0.21
/////////////////////////////////////////////////////
//  Muon TRK Correction 80X
////////////////////////////////////////////////////////////

float Cor80X_TRK_Mu_Full2016(float eta, TGraphAsymmErrors * graph ) {
    // take the ratio_eff_eta3_dr030e030_corr histogram (as function of eta).
    double * ipoint=NULL;
    double x_point,y_sf;
    ipoint=graph->GetX();
    if (eta >=(ipoint[0]-graph->GetErrorXlow(0))  && eta < (ipoint[0]+graph->GetErrorXhigh(0)) )  etaPOINT=0 ;
    else if (eta >= (ipoint[1]-graph->GetErrorXlow(1))  && eta < (ipoint[1]+graph->GetErrorXhigh(1)) ) etaPOINT=1;
    else if (eta >= (ipoint[2]-graph->GetErrorXlow(2)) && eta < (ipoint[2]+graph->GetErrorXhigh(2)) ) etaPOINT=2;
    else if (eta >= (ipoint[3]-graph->GetErrorXlow(3)) && eta < (ipoint[3]+graph->GetErrorXhigh(3)) ) etaPOINT=3;
    else if (eta >= (ipoint[4]-graph->GetErrorXlow(4)) && eta < (ipoint[4]+graph->GetErrorXhigh(4)) ) etaPOINT=4;
    else if (eta >= (ipoint[5]-graph->GetErrorXlow(5)) && eta < (ipoint[5]+graph->GetErrorXhigh(5)) ) etaPOINT=5;
    else if (eta >= (ipoint[6]-graph->GetErrorXlow(6)) && eta < (ipoint[6]+graph->GetErrorXhigh(6)) ) etaPOINT=6;
    else if (eta >= (ipoint[7]-graph->GetErrorXlow(7)) && eta < (ipoint[7]+graph->GetErrorXhigh(7)) ) etaPOINT=7;
    else if (eta >= (ipoint[8]-graph->GetErrorXlow(8)) && eta < (ipoint[8]+graph->GetErrorXhigh(8)) ) etaPOINT=8;
    else if (eta >= (ipoint[9]-graph->GetErrorXlow(9)) && eta < (ipoint[9]+graph->GetErrorXhigh(9)) ) etaPOINT=9;
    else if (eta >= (ipoint[10]-graph->GetErrorXlow(10)) && eta < (ipoint[10]+graph->GetErrorXhigh(10)) ) etaPOINT=10;
    else if (eta >= (ipoint[11]-graph->GetErrorXlow(11)) && eta < (ipoint[11]+graph->GetErrorXhigh(11)) ) etaPOINT=11;
    else if (eta >= (ipoint[12]-graph->GetErrorXlow(12)) && eta < (ipoint[12]+graph->GetErrorXhigh(12)) ) etaPOINT=12;
    else if (eta >= (ipoint[13]-graph->GetErrorXlow(13)) && eta < (ipoint[13]+graph->GetErrorXhigh(13)) ) etaPOINT=13;
    else if (eta >= (ipoint[14]-graph->GetErrorXlow(14)) && eta < (ipoint[14]+graph->GetErrorXhigh(14)) ) etaPOINT=14;
    else return 1;
    
    graph->GetPoint(etaPOINT,x_point,y_sf);
    return y_sf;
    
}


float Cor80X_TRK_Mu(float eta ) {
    
    if (eta >= -2.4 && eta < -2.1 ) return 0.9879;
    else if (eta >= -2.1 && eta < -1.6 ) return 0.9939;
    else if (eta >= -1.6 && eta < -1.1) return 0.9970;
    else if (eta >= -1.1 && eta < -0.6) return 0.9954;
    else if (eta >= -0.6 && eta < 0 ) return 0.9937;
    else if (eta >= 0 && eta < 0.6 ) return 0.9959;
    else if (eta >= 0.6 && eta < 1.1 ) return 0.9976;
    else if (eta >= 1.1 && eta < 1.6 ) return 0.9961;
    else if (eta >= 1.6 && eta < 2.1 ) return 0.9930;
    else if (eta >= 2.1 && eta < 2.4 ) return 0.9819;
    else return 1;
    
    
    
}

/////////////////////////////////////////////////////
//  Muon Id Correction 80X
////////////////////////////////////////////////////////////



float Cor80X_ID_Mu_BCDEF(float pt, float eta , TH2F * HistoId) {
    
    if (pt >= 20 && pt < 25 ) ptBIN=1;
    if (pt >= 25 && pt < 30 ) ptBIN=2;
    if (pt >= 30 && pt < 40 ) ptBIN=3;
    if (pt >= 40 && pt < 50 ) ptBIN=4;
    if (pt >= 50 && pt < 60 ) ptBIN=5;
    if (pt >= 60  ) ptBIN=6;
    
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
    
    
    //       cout<< "--->Muon Id    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoId->GetBinContent(ptBIN,etaBIN)<<"\n";
    return HistoId->GetBinContent(ptBIN,etaBIN);
}


float Cor80X_ID_Mu_GH(float pt, float eta , TH2F * HistoId) {
    
    if (pt >= 20 && pt < 25 ) ptBIN=1;
    if (pt >= 25 && pt < 30 ) ptBIN=2;
    if (pt >= 30 && pt < 40 ) ptBIN=3;
    if (pt >= 40 && pt < 50 ) ptBIN=4;
    if (pt >= 50 && pt < 60 ) ptBIN=5;
    if (pt >= 60  ) ptBIN=6;
    
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
    
    
    //    cout<< "--->Muon Id    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoId->GetBinContent(ptBIN,etaBIN)<<"\n";
    return HistoId->GetBinContent(ptBIN,etaBIN);
}



float Cor80X_ID_Mu(float pt, float eta , TH2F * HistoId) {
    
    if (pt >= 20 && pt < 25 ) ptBIN=1;
    if (pt >= 25 && pt < 30 ) ptBIN=2;
    if (pt >= 30 && pt < 40 ) ptBIN=3;
    if (pt >= 40 && pt < 50 ) ptBIN=4;
    if (pt >= 50 && pt < 60 ) ptBIN=5;
    if (pt >= 60 && pt < 100) ptBIN=6;
    if (pt >= 100 ) ptBIN=7;
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
    
    
    //    cout<< "--->Muon Id    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoId->GetBinContent(ptBIN,etaBIN)<<"\n";
    return HistoId->GetBinContent(ptBIN,etaBIN);
}

//float Cor74X_ID_Mu(float pt, float eta , TH2F * HistoId) {
//
//    if (pt >= 20 && pt < 25 ) ptBIN=1;
//    if (pt >= 25 && pt < 30 ) ptBIN=2;
//    if (pt >= 30 && pt < 40 ) ptBIN=3;
//    if (pt >= 40 && pt < 50 ) ptBIN=4;
//    if (pt >= 50 && pt < 60 ) ptBIN=5;
//    if (pt >= 60 && pt < 120000) ptBIN=6;
//
//    if (fabs(eta) <= 0.9) etaBIN=1;
//    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
//    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
//    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
//
//    return HistoId->GetBinContent(ptBIN,etaBIN);
//}
////////////////////////////////////////////////////////////
//  Muon Iso Correction 74X
////////////////////////////////////////////////////////////
//float Cor74X_Iso_Mu(float pt,float eta, TH2F* HistoIso){
//
//    if (pt >= 20 && pt < 25 ) ptBIN=1;
//    if (pt >= 25 && pt < 30 ) ptBIN=2;
//    if (pt >= 30 && pt < 40 ) ptBIN=3;
//    if (pt >= 40 && pt < 50 ) ptBIN=4;
//    if (pt >= 50 && pt < 60 ) ptBIN=5;
//    if (pt >= 60 && pt < 120000) ptBIN=6;
//
//    if (fabs(eta) <= 0.9) etaBIN=1;
//    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
//    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
//    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
//
//    return HistoIso->GetBinContent(ptBIN,etaBIN);;
//}


float Cor80X_Iso_Mu_BCDEF(float pt,float eta, TH2F* HistoIso){
    
    if (pt >= 20 && pt < 25 ) ptBIN=1;
    if (pt >= 25 && pt < 30 ) ptBIN=2;
    if (pt >= 30 && pt < 40 ) ptBIN=3;
    if (pt >= 40 && pt < 50 ) ptBIN=4;
    if (pt >= 50 && pt < 60 ) ptBIN=5;
    if (pt >= 60  ) ptBIN=6;
    
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
    
    //    cout<< "--->Muon Iso    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoIso->GetBinContent(ptBIN,etaBIN)<<"\n";
    return HistoIso->GetBinContent(ptBIN,etaBIN);
}


float Cor80X_Iso_Mu_GH(float pt,float eta, TH2F* HistoIso){
    
    if (pt >= 20 && pt < 25 ) ptBIN=1;
    if (pt >= 25 && pt < 30 ) ptBIN=2;
    if (pt >= 30 && pt < 40 ) ptBIN=3;
    if (pt >= 40 && pt < 50 ) ptBIN=4;
    if (pt >= 50 && pt < 60 ) ptBIN=5;
    if (pt >= 60 ) ptBIN=6;
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
    
    //    cout<< "--->Muon Iso    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoIso->GetBinContent(ptBIN,etaBIN)<<"\n";
    return HistoIso->GetBinContent(ptBIN,etaBIN);
}


float Cor80X_Iso_Mu(float pt,float eta, TH2F* HistoIso){
    
    if (pt >= 20 && pt < 25 ) ptBIN=1;
    if (pt >= 25 && pt < 30 ) ptBIN=2;
    if (pt >= 30 && pt < 40 ) ptBIN=3;
    if (pt >= 40 && pt < 50 ) ptBIN=4;
    if (pt >= 50 && pt < 60 ) ptBIN=5;
    if (pt >= 60  ) ptBIN=6;
    
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
    
    //    cout<< "--->Muon Iso    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoIso->GetBinContent(ptBIN,etaBIN)<<"\n";
    return HistoIso->GetBinContent(ptBIN,etaBIN);
}

///////////////////////////////////////////////
//  Muon Trigger Correction 80X
////////////////////////////////////////////////////////////

float Cor80X_Trigger_Mu_BCDEF(float pt,float eta, TH2F* HistoTrg ){
    
    if (pt >=52 && pt < 55 ) ptBIN=1;
    if (pt >= 55 && pt < 60 ) ptBIN=2;
    if (pt >= 60 && pt < 80) ptBIN=3;
    if (pt >= 80 && pt < 120) ptBIN=4;
    if (pt >= 120 && pt < 200) ptBIN=5;
    if (pt >= 200 && pt < 300) ptBIN=6;
    if (pt >= 300 && pt < 400) ptBIN=7;
    if (pt >= 400) ptBIN=8;
    
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
    
    if (pt > 750) pt=750;
    
        if (HistoTrg->GetBinContent(ptBIN,etaBIN)-HistoTrg->GetBinContent(HistoTrg->GetXaxis()->FindBin(pt),HistoTrg->GetYaxis()->FindBin(fabs(eta)))) cout<< "--->Trigger    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoTrg->GetBinContent(ptBIN,etaBIN)-HistoTrg->GetBinContent(HistoTrg->GetXaxis()->FindBin(pt),HistoTrg->GetYaxis()->FindBin(fabs(eta)))<<"\n";
    
//    float zpt_corr=histZ->GetBinContent(histZ->GetXaxis()->FindBin(genM),histZ->GetYaxis()->FindBin(genpT));
    
    
    
    return HistoTrg->GetBinContent(ptBIN,etaBIN);
    
}


float Cor80X_Trigger_Mu_GH(float pt,float eta, TH2F* HistoTrg ){
    
    if (pt >=52 && pt < 55 ) ptBIN=1;
    if (pt >= 55 && pt < 60 ) ptBIN=2;
    if (pt >= 60 && pt < 80) ptBIN=3;
    if (pt >= 80 && pt < 120) ptBIN=4;
    if (pt >= 120 && pt < 200) ptBIN=5;
    if (pt >= 200 && pt < 300) ptBIN=6;
    if (pt >= 300 && pt < 400) ptBIN=7;
    if (pt >= 400) ptBIN=8;
    
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    if (2.1 <= fabs(eta) && fabs(eta) < 2.4) etaBIN=4;
    
    
    if (pt > 750) pt=750;
    
    
    if (HistoTrg->GetBinContent(ptBIN,etaBIN)-HistoTrg->GetBinContent(HistoTrg->GetXaxis()->FindBin(pt),HistoTrg->GetYaxis()->FindBin(fabs(eta)))) cout<< "--->Trigger    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoTrg->GetBinContent(ptBIN,etaBIN)- HistoTrg->GetBinContent(HistoTrg->GetXaxis()->FindBin(pt),HistoTrg->GetYaxis()->FindBin(fabs(eta)))<<"\n";
    return HistoTrg->GetBinContent(ptBIN,etaBIN);
    
}






/////////////////////////  Only Eta

float Cor80X_Trigger_Mu_BCDEF_onlyEta(float eta, TH1F* HistoTrg ){
    
    
    if (eta >= -2.4 && eta < -2.1 ) etaBIN=1;
    if (eta >= -2.1 && eta < -1.6 ) etaBIN=2;
    if (eta >= -1.6 && eta < -1.2) etaBIN=3;
    if (eta >= -1.2 && eta < -0.9) etaBIN=4;
    if (eta >= -0.9 && eta < -0.3 ) etaBIN=5;
    if (eta >= -0.3 && eta < -0.2 ) etaBIN=6;
    if (eta >= -0.2 && eta < 0 ) etaBIN=7;
    if (eta >= 0 && eta < 0.2 ) etaBIN=8;
    if (eta >= 0.2 && eta < 0.3 ) etaBIN=9;
    if (eta >= 0.3 && eta < 0.9 ) etaBIN=10;
    if (eta >= 0.9 && eta < 1.2 ) etaBIN=11;
    if (eta >= 1.2 && eta < 1.6 ) etaBIN=12;
    if (eta >= 1.6 && eta < 2.1 ) etaBIN=13;
    if (eta >= 2.1 && eta < 2.4 ) etaBIN=14;
    
    
    
    
    
    //        cout<< "--->Trigger  BCDEF   eta" <<eta<< "  SF="<<HistoTrg->GetBinContent(etaBIN)<<"\n";
    return HistoTrg->GetBinContent(etaBIN);
    
}


float Cor80X_Trigger_Mu_GH_onlyEta(float eta, TH1F* HistoTrg ){
    
    if (eta >= -2.4 && eta < -2.1 ) etaBIN=1;
    if (eta >= -2.1 && eta < -1.6 ) etaBIN=2;
    if (eta >= -1.6 && eta < -1.2) etaBIN=3;
    if (eta >= -1.2 && eta < -0.9) etaBIN=4;
    if (eta >= -0.9 && eta < -0.3 ) etaBIN=5;
    if (eta >= -0.3 && eta < -0.2 ) etaBIN=6;
    if (eta >= -0.2 && eta < 0 ) etaBIN=7;
    if (eta >= 0 && eta < 0.2 ) etaBIN=8;
    if (eta >= 0.2 && eta < 0.3 ) etaBIN=9;
    if (eta >= 0.3 && eta < 0.9 ) etaBIN=10;
    if (eta >= 0.9 && eta < 1.2 ) etaBIN=11;
    if (eta >= 1.2 && eta < 1.6 ) etaBIN=12;
    if (eta >= 1.6 && eta < 2.1 ) etaBIN=13;
    if (eta >= 2.1 && eta < 2.4 ) etaBIN=14;
    
    
    //    cout<< "--->Trigger  GH  eta" <<eta<< "  SF="<<HistoTrg->GetBinContent(etaBIN)<<"\n";
    return HistoTrg->GetBinContent(etaBIN);
    
}



///////////////////////////////////////










float Cor80X_Trigger_Mu(float pt,float eta, TH2F* HistoTrg ){
    
    if (pt >= 45 && pt < 50 ) ptBIN=1;
    if (pt >= 50 && pt < 60 ) ptBIN=2;
    if (pt >= 60 && pt < 120) ptBIN=3;
    if (pt >= 120 && pt < 200) ptBIN=4;
    if (pt >= 200) ptBIN=5;
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    
    //    cout<< "--->Trigger    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoTrg->GetBinContent(ptBIN,etaBIN)<<"\n";
    return HistoTrg->GetBinContent(ptBIN,etaBIN);
    
}

////////////////////////////////////////////////////////////
vector<float> _getMuTrgWeight(float pt,float eta){
    
    
    //barrel
    //    1  p0           9.17305e-01   4.63004e-03   1.83763e-04  -1.39161e-04
    //    2  p1          -5.00202e-05   4.91184e-05   1.20000e-05  -1.31193e-02
    //Transition
    //    1  p0           9.17394e-01   1.01338e-02   1.29242e-04   5.58450e-05
    //    2  p1          -3.42661e-04   1.08333e-04   1.20000e-05   5.22137e-03
    //EndCap
    //    1  p0           9.36539e-01   8.43010e-03   1.20902e-04  -1.10272e-04
    //    2  p1          -1.11611e-03   9.05589e-05   1.20000e-05  -1.02555e-02
    
    
    vector<float> FitPar;
    FitPar.clear();
    
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    
    if (etaBIN==1){
        FitPar.push_back(9.17305e-01);
        FitPar.push_back(-5.00202e-05);
    }
    else if (etaBIN==2){
        FitPar.push_back(9.17394e-01);
        FitPar.push_back(-3.42661e-04);
    }
    else if (etaBIN==3){
        FitPar.push_back(9.36539e-01);
        FitPar.push_back(-1.11611e-03);
    }
    else {
        FitPar.push_back(9.36539e-01);
        FitPar.push_back(-1.11611e-03);
    }
    
    return FitPar;
}

//New
//    EXT PARAMETER                                   STEP         FIRST
//    NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
//    1  p0           9.22073e-01   3.72714e-03   1.86850e-04  -1.54306e-04
//    2  p1          -1.02098e-04   3.88883e-05   1.20000e-05  -1.47852e-02
//
//    EXT PARAMETER                                   STEP         FIRST
//    NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
//    1  p0           9.23993e-01   8.03439e-03   1.85149e-04  -2.18784e-04
//    2  p1          -4.14952e-04   8.46039e-05   1.20000e-05  -2.07779e-02
//
//
//    NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
//    1  p0           9.50527e-01   6.90139e-03   1.83512e-04   1.05129e-04
//    2  p1          -1.26964e-03   7.33305e-05   1.20000e-05   9.89566e-03


//    vector<float> FitPar;
//    FitPar.clear();
//
//
//    if (fabs(eta) <= 0.9) etaBIN=1;
//    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
//    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
//
//    if (etaBIN==1){
//        FitPar.push_back(9.22073e-01);
//        FitPar.push_back(-1.02098e-04);
//    }
//    else if (etaBIN==2){
//        FitPar.push_back(9.23993e-01);
//        FitPar.push_back(-4.14952e-04);
//    }
//    else if (etaBIN==3){
//        FitPar.push_back(9.50527e-01);
//        FitPar.push_back(-1.26964e-03);
//    }
//    else {
//        FitPar.push_back(9.50527e-01);
//        FitPar.push_back(-1.26964e-03);
//    }
//
//    return FitPar;
//}


////////////////////////////////////////////////////////////


float Cor80X_Trigger_Mu_FIT(float pt,float eta, TH2F* HistoTrg ){
    
    if (pt >= 45 && pt < 50 ) ptBIN=1;
    if (pt >= 50 && pt < 60 ) ptBIN=2;
    if (pt >= 60 && pt < 120) ptBIN=3;
    if (pt >= 120 && pt < 200) ptBIN=4;
    if (pt >= 200) ptBIN=5;
    
    if (fabs(eta) <= 0.9) etaBIN=1;
    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
    
    
    float Weight= HistoTrg->GetBinContent(ptBIN,etaBIN);
    
    
    
    if (pt > 60){
        //        cout<<" pt and eta= "<<pt << "  "<<fabs(eta)<<" "<< Weight<<"\t";
        vector<float>   Weight_vec=_getMuTrgWeight(pt,eta);
        Weight=Weight_vec[0] + Weight_vec[1]*pt;
        //        cout<< Weight<<"\n";
    }
    
    return Weight;
    
}

//float Cor74X_Trigger_Mu(float pt,float eta, TH2F* HistoTrg ){
//
//    if (pt >= 45 && pt < 50 ) ptBIN=1;
//    if (pt >= 50 && pt < 60 ) ptBIN=2;
//    if (pt >= 60 && pt < 120000) ptBIN=3;
//
//    if (fabs(eta) <= 0.9) etaBIN=1;
//    if (0.9 <= fabs(eta) && fabs(eta) < 1.2) etaBIN=2;
//    if (1.2 <= fabs(eta) && fabs(eta) < 2.1) etaBIN=3;
//
//    //    cout<< "pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoTrg->GetBinContent(ptBIN,etaBIN)<<"\n";
//    return HistoTrg->GetBinContent(ptBIN,etaBIN);
//
//
//}
//////////////////////////////////////////////////////////////
//  Electron Id/Iso Correction 74X  from HTT group
////////////////////////////////////////////////////////////

//https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2#Electron_efficiencies_and_scale
float Cor80X_IDIso_Ele(float pt, float eta,  TH2F * HistoEleSF){
    
    if (pt >= 10 && pt < 20 ) ptBIN=1;
    if (pt >= 20 && pt < 35 ) ptBIN=2;
    if (pt >= 35 && pt < 50) ptBIN=3;
    if (pt >= 50 && pt < 90) ptBIN=4;
    if (pt >= 90 && pt < 150) ptBIN=5;
    if (pt >= 150 ) ptBIN=6;
    
    if (eta >= -2.5 && eta < -2 ) etaBIN=1;
    if (eta >= -2 && eta < -1.566 ) etaBIN=2;
    if (eta >= -1.566 && eta < -1.444) etaBIN=3;
    if (eta >= -1.444 && eta < -0.800) etaBIN=4;
    if (eta >= -0.800 && eta < 0 ) etaBIN=5;
    if (eta >= 0 && eta < 0.800 ) etaBIN=6;
    if (eta >= 0.800 && eta < 1.444 ) etaBIN=7;
    if (eta >= 1.444 && eta < 1.566 ) etaBIN=8;
    if (eta >= 1.566 && eta < 2 ) etaBIN=9;
    if (eta >= 2 && eta < 2.5 ) etaBIN=10;
    
    //    float SF_0p5= HistoEleSF0p5->GetBinContent(etaBIN, ptBIN);
    //    float SF_5= HistoEleSF5->GetBinContent(etaBIN, ptBIN);
    //    float FinalSF= 0.05 * SF_0p5  + 0.95 * SF_5;   //approximation of 10/fb data
    
    //    cout << pt << "  " << eta << " "<<SF_0p5<<"  "<<SF_5 << "  "<< FinalSF <<"\n";
    //    cout<< "--->Electron    pt= "<<pt<<  "   eta" <<eta<< "  SF="<<HistoEleSF->GetBinContent(etaBIN, ptBIN)<<"\n";
    return HistoEleSF->GetBinContent(etaBIN, ptBIN);
    
}

// This is for efficiency of the electron
float Cor80X_Ele_EffVeto(float pt, float eta,  TH2F * HistoEleSF){
    
    if (pt >= 10 && pt < 20 ) ptBIN=1;
    if (pt >= 20 && pt < 35 ) ptBIN=2;
    if (pt >= 35 && pt < 50) ptBIN=3;
    if (pt >= 50 && pt < 90) ptBIN=4;
    if (pt >= 90 && pt < 150) ptBIN=5;
    if (pt >= 150 ) ptBIN=6;
    
    if (eta >= -2.5 && eta < -2 ) etaBIN=1;
    if (eta >= -2 && eta < -1.566 ) etaBIN=2;
    if (eta >= -1.566 && eta < -1.444) etaBIN=3;
    if (eta >= -1.444 && eta < -0.800) etaBIN=4;
    if (eta >= -0.800 && eta < 0 ) etaBIN=5;
    if (eta >= 0 && eta < 0.800 ) etaBIN=6;
    if (eta >= 0.800 && eta < 1.444 ) etaBIN=7;
    if (eta >= 1.444 && eta < 1.566 ) etaBIN=8;
    if (eta >= 1.566 && eta < 2 ) etaBIN=9;
    if (eta >= 2 && eta < 2.5 ) etaBIN=10;
    
    return HistoEleSF->GetBinContent(etaBIN, ptBIN);
    
}



float Cor80X_Trg_Ele(float pt, float eta){
    
    
    
    if (pt >= 50 && pt < 55){
        if (eta >= -2.5 && eta < -2 ) return   .729;
        if (eta >= -2 && eta < -1.566 ) return   .752;
        if (eta >= -1.566 && eta < -1.444) return   .684;
        if (eta >= -1.444 && eta < -0.800) return   .81;
        if (eta >= -0.800 && eta < 0 ) return  .833 ;
        if (eta >= 0 && eta < 0.800 ) return   .827;
        if (eta >= 0.800 && eta < 1.444 ) return   .825;
        if (eta >= 1.444 && eta < 1.566 ) return   .627;
        if (eta >= 1.566 && eta < 2 ) return   .755;
        if (eta >= 2 && eta < 2.5 ) return   .746;
    }
    else if (pt >= 55 && pt < 70){
        if (eta >= -2.5 && eta < -2 ) return  .812 ;
        if (eta >= -2 && eta < -1.566 ) return   .814;
        if (eta >= -1.566 && eta < -1.444) return  .781 ;
        if (eta >= -1.444 && eta < -0.800) return   .802;
        if (eta >= -0.800 && eta < 0 ) return   .869;
        if (eta >= 0 && eta < 0.800 ) return   .862;
        if (eta >= 0.800 && eta < 1.444 ) return   .879;
        if (eta >= 1.444 && eta < 1.566 ) return   .642;
        if (eta >= 1.566 && eta < 2 ) return   .843;
        if (eta >= 2 && eta < 2.5 ) return   .845;
    }
    else if (pt >= 70 && pt < 100){
        if (eta >= -2.5 && eta < -2 ) return   .788;
        if (eta >= -2 && eta < -1.566 ) return   .809;
        if (eta >= -1.566 && eta < -1.444) return   .833;
        if (eta >= -1.444 && eta < -0.800) return   .888;
        if (eta >= -0.800 && eta < 0 ) return   .883;
        if (eta >= 0 && eta < 0.800 ) return  .882 ;
        if (eta >= 0.800 && eta < 1.444 ) return   .884;
        if (eta >= 1.444 && eta < 1.566 ) return  .808 ;
        if (eta >= 1.566 && eta < 2 ) return   .833;
        if (eta >= 2 && eta < 2.5 ) return   .853;
    }
    else if (pt >= 100 && pt < 120){
        if (eta >= -2.5 && eta < -2 ) return  .919 ;
        if (eta >= -2 && eta < -1.566 ) return  .871 ;
        if (eta >= -1.566 && eta < -1.444) return   .894;
        if (eta >= -1.444 && eta < -0.800) return   .908;
        if (eta >= -0.800 && eta < 0 ) return  .902 ;
        if (eta >= 0 && eta < 0.800 ) return  .924 ;
        if (eta >= 0.800 && eta < 1.444 ) return  .927 ;
        if (eta >= 1.444 && eta < 1.566 ) return  .728 ;
        if (eta >= 1.566 && eta < 2 ) return  .87 ;
        if (eta >= 2 && eta < 2.5 ) return  .867 ;
    }
    else if (pt >= 120 && pt < 180){
        if (eta >= -2.5 && eta < -2 ) return  .955 ;
        if (eta >= -2 && eta < -1.566 ) return   .986;
        if (eta >= -1.566 && eta < -1.444) return  .887 ;
        if (eta >= -1.444 && eta < -0.800) return  .924 ;
        if (eta >= -0.800 && eta < 0 ) return  .941 ;
        if (eta >= 0 && eta < 0.800 ) return   .934;
        if (eta >= 0.800 && eta < 1.444 ) return  .956 ;
        if (eta >= 1.444 && eta < 1.566 ) return  .81 ;
        if (eta >= 1.566 && eta < 2 ) return  .977 ;
        if (eta >= 2 && eta < 2.5 ) return  .948 ;
    }
    else if (pt >= 180 && pt < 250){
        if (eta >= -2.5 && eta < -2 ) return  1 ;
        if (eta >= -2 && eta < -1.566 ) return  .984 ;
        if (eta >= -1.566 && eta < -1.444) return  .918 ;
        if (eta >= -1.444 && eta < -0.800) return  .934 ;
        if (eta >= -0.800 && eta < 0 ) return   .981;
        if (eta >= 0 && eta < 0.800 ) return   .937;
        if (eta >= 0.800 && eta < 1.444 ) return  .931 ;
        if (eta >= 1.444 && eta < 1.566 ) return   .939;
        if (eta >= 1.566 && eta < 2 ) return   .968;
        if (eta >= 2 && eta < 2.5 ) return  .954 ;
    }
    else if (pt >= 250 ){
        if (eta >= -2.5 && eta < -2 ) return  1 ;
        if (eta >= -2 && eta < -1.566 ) return  1 ;
        if (eta >= -1.566 && eta < -1.444) return 1  ;
        if (eta >= -1.444 && eta < -0.800) return  .927 ;
        if (eta >= -0.800 && eta < 0 ) return  .953 ;
        if (eta >= 0 && eta < 0.800 ) return   .959;
        if (eta >= 0.800 && eta < 1.444 ) return  .972 ;
        if (eta >= 1.444 && eta < 1.566 ) return  1 ;
        if (eta >= 1.566 && eta < 2 ) return  1 ;
        if (eta >= 2 && eta < 2.5 ) return   1;
    }
    return 1;
    
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

float Cor80X_Trg_Ele25(float pt,float eta,TGraphAsymmErrors **  Ele25Trg){
    
    float weight=1;
    if (fabs (eta)< 1.4 ) weight = Ele25Trg[3]->Eval(pt) /Ele25Trg[0]->Eval(pt);
    else if (fabs (eta)>= 1.4 &&  fabs (eta) < 2.1) weight = Ele25Trg[4]->Eval(pt) /Ele25Trg[1]->Eval(pt);
    else if (fabs (eta)>= 2.1 ) weight = Ele25Trg[5]->Eval(pt) /Ele25Trg[2]->Eval(pt);
    else weight =1;
    
    return weight;
    
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


//This function is called to calculate the weighted ID, Iso and Trigger SF's from the individual ones for run BCDEF and GH.
float CalcWeightedObj(float Obj_period1, float Obj_period2){
    
    float weighted_obj= (LumiBCDEF*Obj_period1+LumiGH*Obj_period2)/(LumiBCDEF+LumiGH);
    return weighted_obj;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



   float getCorrFactorMuon80X(bool isData, float pt, float eta, TH2F ** HistoId, TH2F ** HistoIso,TH2F ** HistoTrg, TGraphAsymmErrors * graph) { // This for pt_eta-Trigger
//float getCorrFactorMuon80X(bool isData, float pt, float eta, TH2F ** HistoId, TH2F ** HistoIso,TH1F ** HistoTrg, TGraphAsymmErrors * graph) {
    
    if (isData)
        return 1;
    else{
        float Weighted_IDSF=CalcWeightedObj(Cor80X_ID_Mu_BCDEF(pt,eta,HistoId[0]), Cor80X_ID_Mu_GH(pt,eta,HistoId[1]));
        float Weighted_IsoSF=CalcWeightedObj(Cor80X_Iso_Mu_BCDEF(pt,eta,HistoIso[0]), Cor80X_Iso_Mu_GH(pt,eta,HistoIso[1]));
        float Weighted_TriggerSF=CalcWeightedObj(Cor80X_Trigger_Mu_BCDEF(pt,eta,HistoTrg[0]), Cor80X_Trigger_Mu_GH(pt,eta,HistoTrg[1]));
//        float Weighted_TriggerSF=CalcWeightedObj(Cor80X_Trigger_Mu_BCDEF_onlyEta(eta,HistoTrg[0]), Cor80X_Trigger_Mu_GH_onlyEta(eta,HistoTrg[1]));
        float Tracking_SF=Cor80X_TRK_Mu_Full2016(eta, graph);
        return (Weighted_IDSF * Weighted_IsoSF * Tracking_SF * Weighted_TriggerSF);
    }
    
}


float getCorrFactorDiMuon80X(bool isData, float pt, float eta, TH2F ** HistoId, TH2F ** HistoIso,TH2F ** HistoTrg, TGraphAsymmErrors * graph) {
    
    if (isData)
        return 1;
    else{
        float Weighted_IDSF=CalcWeightedObj(Cor80X_ID_Mu_BCDEF(pt,eta,HistoId[0]), Cor80X_ID_Mu_GH(pt,eta,HistoId[1]));
        float Weighted_IsoSF=CalcWeightedObj(Cor80X_Iso_Mu_BCDEF(pt,eta,HistoIso[0]), Cor80X_Iso_Mu_GH(pt,eta,HistoIso[1]));
        //        float Weighted_TriggerSF=CalcWeightedObj(Cor80X_Trigger_Mu_BCDEF(pt,eta,HistoTrg[0]), Cor80X_Trigger_Mu_GH(pt,eta,HistoTrg[1]));
        float Weighted_TriggerSF=1;
        float Tracking_SF=Cor80X_TRK_Mu_Full2016(eta, graph);
        return (Weighted_IDSF * Weighted_IsoSF * Tracking_SF * Weighted_TriggerSF);
    }
    
}





float getCorrFactorMuon74X(bool isData, float pt, float eta, TH2F * HistoId, TH2F * HistoIso,TH2F * HistoTrg) {
    
    if (isData)
        return 1;
    else{
        
        //        cout << Cor74X_ID_Mu(pt,eta,HistoId) << "  "<< Cor74X_Iso_Mu(pt,eta,HistoIso) << "  "<< Cor74X_Trigger_Mu(pt,eta,HistoTrg) << "\n";
        //        return (Cor74X_ID_Mu(pt,eta,HistoId) * Cor74X_Iso_Mu(pt,eta,HistoIso) * Cor74X_Trigger_Mu(pt,eta,HistoTrg) );
        //        return (Cor74X_ID_Mu(pt,eta,HistoId) * Cor74X_Iso_Mu(pt,eta,HistoIso) * Cor74X_Trigger_Mu(pt,eta,HistoTrg) * Cor74X_TRK_Mu(eta)); //TMP for 80X
        //            return (Cor80X_ID_Mu(pt,eta,HistoId) * Cor80X_Iso_Mu(pt,eta,HistoIso) * Cor80X_Trigger_Mu(pt,eta,HistoTrg) * Cor80X_TRK_Mu(eta)); //TMP for 80X
        
        
        //            return (Cor80X_ID_Mu(pt,eta,HistoId) * Cor80X_Iso_Mu(pt,eta,HistoIso) * Cor80X_Trigger_Mu(pt,eta,HistoTrg) * Cor80X_Trigger_Mu_FIT(pt,eta,HistoTrg));
        
        //            return (Cor80X_ID_Mu(pt,eta,HistoId) * Cor80X_Iso_Mu(pt,eta,HistoIso) * Cor80X_TRK_Mu(eta) * Cor80X_Trigger_Mu_FIT(pt,eta,HistoTrg));
        return (Cor80X_ID_Mu(pt,eta,HistoId) * Cor80X_Iso_Mu(pt,eta,HistoIso) * Cor80X_TRK_Mu(eta) * Cor80X_Trigger_Mu(pt,eta,HistoTrg));
    }
    
}

float getCorrFactorElectron74X(bool isData, float pt, float eta,    TH2F * HistoEleSF ){
    if (isData)
        return 1;
    else
        return Cor80X_IDIso_Ele(pt,eta,HistoEleSF)*Cor80X_Trg_Ele(pt,eta);
}

// Loose WP of MVA Ele
float getCorrFactorMVA90WPElectron80X(bool isData, float pt, float eta,    TH2F * HistoEleSF ){
    if (isData)
        return 1;
    else
        return Cor80X_IDIso_Ele(pt,eta,HistoEleSF);
}

// Tight WP of MVA Ele
float getCorrFactorMVA80WPElectron80X(bool isData, float pt, float eta,    TH2F * HistoEleSF , TGraphAsymmErrors ** Ele25Trg){
    if (isData)
        return 1;
    else
        return Cor80X_IDIso_Ele(pt,eta,HistoEleSF)*Cor80X_Trg_Ele25(pt,eta,Ele25Trg);
}


float getEffVetoMVA90WPElectron80X(bool isData, float pt, float eta,    TH2F * HistoEleSF , TH2F*  HistoEleEffVetoMC, TH2F*  HistoEleEffVetoData){
    
    if (isData)
        return 1;
    else
    {
        
        //        float SF=getCorrFactorMVA90WPElectron80X( isData,  pt,  eta, HistoEleSF );
        float InEffMC= 1 - Cor80X_Ele_EffVeto(pt,eta,HistoEleEffVetoMC);
        float InEffData= 1 - Cor80X_Ele_EffVeto(pt,eta,HistoEleEffVetoData);
        //        float SFIneff=EffData/EffMC;
        //        return (1- SFIneff * EffMC)/(1-EffMC);
        return InEffData/InEffMC;
    }
}





float getCorrFactorMuon80X_TriMu(bool isData, float pt, float eta, TH2F ** HistoId, TH2F ** HistoIso,TH2F ** HistoTrg, TGraphAsymmErrors * graph) {
    
    if (isData)
        return 1;
    else{
        float Weighted_IDSF=CalcWeightedObj(Cor80X_ID_Mu_BCDEF(pt,eta,HistoId[0]), Cor80X_ID_Mu_GH(pt,eta,HistoId[1]));
        float Weighted_IsoSF=CalcWeightedObj(Cor80X_Iso_Mu_BCDEF(pt,eta,HistoIso[0]), Cor80X_Iso_Mu_GH(pt,eta,HistoIso[1]));
        float Tracking_SF=Cor80X_TRK_Mu_Full2016(eta, graph);
        return (Weighted_IDSF * Weighted_IsoSF * Tracking_SF);
    }
    
}







