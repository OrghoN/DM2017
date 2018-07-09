#!/usr/bin/env python
import ROOT
import re
from array import array

def returnSF_TT(FileName,bin):


    file=ROOT.TFile(FileName,"r")
    categoriy="EleJet"
    Data=file.Get(categoriy).Get("data_obs")
    Data.Rebin(bin)
    # QCD=file.Get(categoriy).Get("QCD")
    # QCD.Rebin(bin)
    W=file.Get(categoriy).Get("W")
    W.Rebin(bin)
    TT=file.Get(categoriy).Get("TT")
    TT.Rebin(bin)
    SingleT=file.Get(categoriy).Get("SingleTop")
    SingleT.Rebin(bin)
    VV=file.Get(categoriy).Get("VV")
    VV.Rebin(bin)
    DYS=file.Get(categoriy).Get("ZTT")
    DYS.Rebin(bin)


    ################################################################################################################
    #   Here we compute the TT scale factor
    #   (Data - allBkg)/TT
    ################################################################################################################
    # TTScale=(Data.Integral() - SingleT.Integral() - DYS.Integral() - VV.Integral()- W.Integral() - QCD.Integral()) / TT.Integral()
    TTScale=(Data.Integral() - SingleT.Integral() - DYS.Integral() - VV.Integral()- W.Integral()) / TT.Integral()
    print "TT SF = %.2f , TT purity %.2f, TT normalization %.2f "%(TTScale,TT.Integral()/Data.Integral(),TT.Integral())
    ################################################################################################################

    return TTScale


def returnSF_W(FileName,TTSF,bin):


    file=ROOT.TFile(FileName,"r")
    categoriy="EleJet"
    Data=file.Get(categoriy).Get("data_obs")
    Data.Rebin(bin)
    # QCD=file.Get(categoriy).Get("QCD")
    # QCD.Rebin(bin)
    W=file.Get(categoriy).Get("W")
    W.Rebin(bin)
    TT=file.Get(categoriy).Get("TT")
    TT.Rebin(bin)
    TT.Scale(TTSF)
    SingleT=file.Get(categoriy).Get("SingleTop")
    SingleT.Rebin(bin)
    VV=file.Get(categoriy).Get("VV")
    VV.Rebin(bin)
    DYS=file.Get(categoriy).Get("ZTT")
    DYS.Rebin(bin)

    ################################################################################################################
    #   Here we compute the W scale factor
    #   (Data - allBkg)/W
    ################################################################################################################
    # WScale=(Data.Integral() - SingleT.Integral() - DYS.Integral() - VV.Integral()- TT.Integral() - QCD.Integral()) / W.Integral()
    WScale=(Data.Integral() - SingleT.Integral() - DYS.Integral() - VV.Integral()- TT.Integral()) / W.Integral()

    print "W SF = %.2f , W purity %.2f, W normalization %.2f "%(WScale,W.Integral()/Data.Integral(),W.Integral())
    # print "W purity =%.2f (%.2f , %.2f)"%(W.Integral()/Data.Integral() ,  W.Integral(), Data.Integral())
    # ErrData=Data.GetBinError(1)
    # ErrW=W.GetBinError(1)
    # print "DEBUG" + str(Data.GetBinContent(1)) + "|" + str(W.GetBinContent(1))
    # TotErr=(Data.GetBinError(1)/Data.GetBinContent(1) + W.GetBinError(1)/W.GetBinContent(1))* WScale
    # print "SF= %.2f +- %.2f"  %(WScale, TotErr)
    ################################################################################################################

    return WScale
