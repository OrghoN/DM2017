#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.
#http://root.cern.ch/viewvc/trunk/tutorials/pyroot/hsimple.py?revision=20881&view=markup
__author__ = "abdollahmohammadi"
__date__ = "$Feb 23, 2013 10:39:33 PM$"

import math
import ROOT
from ROOT import Double
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TNtuple
from ROOT import TProfile
from ROOT import gBenchmark
from ROOT import gROOT
from ROOT import gRandom
from ROOT import gSystem
from ctypes import *
import ROOT as r
import array

##### Get Jet to Tau FR
from Step1_JetToMuFR_Data import Make_Mu_FakeRate
from Step1_JetToMuFR_Data import *
##### Get Jet to Tau FR

gROOT.Reset()
import os


ROOT.gROOT.SetBatch(True)
#ROOT.gROOT.ProcessLine('.x rootlogon.C')
#SubRootDir = 'OutFiles_DiMu/'
#SubRootDir = 'OutFiles_DiMu_ScaledWZ'
#SubRootDir = 'OutFiles_DiMu_NoZScale/'


verbos_ = True
RB_=1

#signal = ['LQ_']
#signalName = ['LQ_']
##mass = [200,250, 300, 350, 400, 450, 500, 550,  600, 650, 700, 750, 800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500]
##TOTMASS = [200,250, 300, 350, 400, 450, 500, 550,  600, 650, 700, 750, 800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500]
#mass = [1000,1100]
#TOTMASS = [1000,1100]
#lenghtSig = len(signal) * len(mass) +1
category = [""]

############################################################################################################
def _FileReturn(SubRootDir,Name, channel,cat,HistoName):

    if not os.path.exists(SubRootDir):
        os.makedirs(SubRootDir)
    myfile = TFile(SubRootDir + "/"+Name + '.root')
    if verbos_: print "##### --->>>>>>> File name is ", SubRootDir + Name + '.root'  "   and histo is -->  ", channel+HistoName + cat
    Histo =  myfile.Get(channel+HistoName + cat)
    if not os.path.exists("Extra"):
        os.makedirs("Extra")
    NewFile=TFile("Extra/HISTO.root","RECREATE")
    NewFile.WriteObject(Histo,"HISTO")
    myfile.Close()
    return NewFile


####################################################
##   Start Making the Datacard Histograms
####################################################
def MakeTheHistogram(SubRootDir,channel,NormMC,NormQCD,ShapeQCD,NormTTbar):
    
    OutFile = TFile(("TotalRoot_DiMu_"+SubRootDir+channel + NormMC+".root").replace('_OutFiles_DiMu','') , 'RECREATE') # Name Of the output file

    for NameCat in category:
        print "\nstarting NameCat and channel and HistoName ", NameCat, channel, NormMC

        tDirectory= OutFile.mkdir(channel + str(NameCat))
        tDirectory.cd()

        ################################################
        #   Filling Signal
        ################################################
#        print "--------------------------------------------------->     Processing Codex1400"
#        tDirectory.cd()
#
#        Name= "Codex_1200"
#        NameOut= "Codex_1200"
#        
#        NormFile= _FileReturn(SubRootDir,Name, channel,NameCat, NormMC)
#        NormHisto=NormFile.Get("HISTO")
##        
#        if not NormHisto:
#            raise Exception('Not valid %s'%NameOut)
#        else:
#            RebinedHist= NormHisto.Rebin(RB_)
#            tDirectory.WriteObject(RebinedHist,NameOut)

        ################################################
        #  Filling SingleTop
        ################################################
        print "--------------------------------------------------->     Processing SingleTop"
        tDirectory.cd()
    
        Name= "SingleTop"
        NameOut= "SingleTop"
        
        NormFile= _FileReturn(SubRootDir,Name, channel,NameCat, NormMC)
        NormHisto=NormFile.Get("HISTO")
        
        if not NormHisto:
            raise Exception('Not valid %s'%NameOut)
        else:
            RebinedHist= NormHisto.Rebin(RB_)
            tDirectory.WriteObject(RebinedHist,NameOut)
        
        ################################################
        #  Filling VV
        ################################################
        print "--------------------------------------------------->     Processing VV"
        tDirectory.cd()
    
        Name= "VV"
        NameOut= "VV"
        
        NormFile= _FileReturn(SubRootDir,Name, channel,NameCat, NormMC)
        NormHisto=NormFile.Get("HISTO")
        
        if not NormHisto:
            raise Exception('Not valid %s'%NameOut)
        else:
            RebinedHist= NormHisto.Rebin(RB_)
            tDirectory.WriteObject(RebinedHist,NameOut)


        ################################################
        #  Filling TOP
        ################################################
        print "--------------------------------------------------->     Processing TOP"
        tDirectory.cd()

        Name= "TTJets"
        NameOut= "TT"

        NormFileShape= _FileReturn(SubRootDir,Name, channel,NameCat, NormMC)
        NormHistoShape=NormFileShape.Get("HISTO")
        
        NormFile= _FileReturn(SubRootDir,Name, channel,NameCat, NormTTbar)
        NormHisto=NormFile.Get("HISTO")
        

        if not NormHistoShape:
            raise Exception('Not valid %s'%NameOut)
        else:
            print '######  TTbar norm with TopPtRW %d without TopPtRW %d and the ratio is %d #####'%(NormHistoShape.Integral(),NormHisto.Integral(),NormHistoShape.Integral()/NormHisto.Integral()*1.0)
            NormHistoShape.Scale(NormHisto.Integral()*1.0/NormHistoShape.Integral())
            RebinedHist= NormHistoShape.Rebin(RB_)
            tDirectory.WriteObject(NormHistoShape,NameOut)


        ################################################
        #  Filling ZTT
        ################################################
        print "--------------------------------------------------->     Processing ZTT"
        tDirectory.cd()

        Name= "DYJetsToLL"
        NameOut= "ZTT"

        NormFile= _FileReturn(SubRootDir,Name, channel,NameCat, NormMC)
        NormHisto=NormFile.Get("HISTO")

        if not NormHisto:
            raise Exception('Not valid %s'%NameOut)
        else:
            RebinedHist= NormHisto.Rebin(RB_)
            tDirectory.WriteObject(RebinedHist,NameOut)



        ################################################
        #  Filling W
        ################################################
        print "--------------------------------------------------->     Processing W"
        tDirectory.cd()

        Name="WJetsToLNu"
        NameOut= "W"

        NormFile= _FileReturn(SubRootDir,Name, channel,NameCat, NormMC)
        NormHisto=NormFile.Get("HISTO")
            
        if not NormHisto:
            raise Exception('Not valid %s'%NameOut)
        else:
            RebinedHist= NormHisto.Rebin(RB_)
            tDirectory.WriteObject(RebinedHist,NameOut)
        

#        ################################################
#        #  Filling QCD
#        ################################################
#        print "--------------------------------------------------->     Processing QCD"
#        tDirectory.cd()
#        
#        Name= "SingleTop"
#        SingleTSampleQCDNorm= _FileReturn(SubRootDir,Name, channel,NameCat, NormQCD)
#        SingleTSampleQCDShape= _FileReturn(SubRootDir,Name, channel,NameCat, ShapeQCD)
#        
#        Name= "VV"
#        VVSampleQCDNorm= _FileReturn(SubRootDir,Name, channel,NameCat, NormQCD)
#        VVSampleQCDShape= _FileReturn(SubRootDir,Name, channel,NameCat, ShapeQCD)
#
#        Name= "TTJets"
#        TTSampleQCDNorm= _FileReturn(SubRootDir,Name, channel,NameCat, NormQCD)
#        TTSampleQCDShape= _FileReturn(SubRootDir,Name, channel,NameCat, ShapeQCD)
#
#        Name= "DYJetsToLL"
#        ZTTSampleQCDNorm= _FileReturn(SubRootDir,Name, channel,NameCat, NormQCD)
#        ZTTSampleQCDShape= _FileReturn(SubRootDir,Name, channel,NameCat, ShapeQCD)
#
#        Name= "WJetsToLNu"
#        WSampleQCDNorm= _FileReturn(SubRootDir,Name, channel,NameCat, NormQCD)
#        WSampleQCDShape= _FileReturn(SubRootDir,Name, channel,NameCat, ShapeQCD)
#                    
#        Name="Data"
#        DataSampleQCDNorm= _FileReturn(SubRootDir,Name, channel,NameCat, NormQCD)
#        DataSampleQCDShape= _FileReturn(SubRootDir,Name, channel,NameCat, ShapeQCD)
#
#
#
#        SingleTSampleQCDShapeHist=SingleTSampleQCDShape.Get("HISTO")
#        VVSampleQCDShapeHist=VVSampleQCDShape.Get("HISTO")
#        TTSampleQCDShapeHist=TTSampleQCDShape.Get("HISTO")
#        ZTTSampleQCDShapeHist=ZTTSampleQCDShape.Get("HISTO")
#        WSampleQCDShapeHist=WSampleQCDShape.Get("HISTO")
#        DataSampleQCDShapeHist=DataSampleQCDShape.Get("HISTO")
#        dataBeforeSub=DataSampleQCDShapeHist.Integral()  #Here we get the data yeild before subtracting other background
##        if SingleTSampleQCDShapeHist: DataSampleQCDShapeHist.Add(SingleTSampleQCDShapeHist, -1)
##        if VVSampleQCDShapeHist: DataSampleQCDShapeHist.Add(VVSampleQCDShapeHist, -1)
##        DataSampleQCDShapeHist.Add(TTSampleQCDShapeHist, -1)
##        DataSampleQCDShapeHist.Add(ZTTSampleQCDShapeHist, -1)
##        DataSampleQCDShapeHist.Add(WSampleQCDShapeHist, -1)
#        dataAfterSub=DataSampleQCDShapeHist.Integral() #Here we get the data yeild after subtracting other background
#        if verbos_: print "\n##########\n QCD --Shape-- Purity is = ", dataAfterSub/dataBeforeSub, " which is ",  dataAfterSub, "/",dataBeforeSub
#
#
#
#        SingleTSampleQCDNormHist=SingleTSampleQCDNorm.Get("HISTO")
#        VVSampleQCDNormHist=VVSampleQCDNorm.Get("HISTO")
#        TTSampleQCDNormHist=TTSampleQCDNorm.Get("HISTO")
#        ZTTSampleQCDNormHist=ZTTSampleQCDNorm.Get("HISTO")
#        WSampleQCDNormHist=WSampleQCDNorm.Get("HISTO")
#        DataSampleQCDNormHist=DataSampleQCDNorm.Get("HISTO")
#        dataBeforeSub=DataSampleQCDNormHist.Integral() #Here we get the data yeild before subtracting other background
#        if SingleTSampleQCDNormHist:  DataSampleQCDNormHist.Add(SingleTSampleQCDNormHist, -1)
#        if VVSampleQCDNormHist: DataSampleQCDNormHist.Add(VVSampleQCDNormHist, -1)
#        DataSampleQCDNormHist.Add(TTSampleQCDNormHist, -1)
#        DataSampleQCDNormHist.Add(ZTTSampleQCDNormHist, -1)
#        DataSampleQCDNormHist.Add(WSampleQCDNormHist, -1)
#        dataAfterSub=DataSampleQCDNormHist.Integral() #Here we get the data yeild after subtracting other background
#        if verbos_: print "\n##########\n QCD ++Norm++ Purity is = ", dataAfterSub/dataBeforeSub, " which is ",  dataAfterSub, "/",dataBeforeSub
#        
#
#        FR_FitMaram=Make_Mu_FakeRate(channel)
#        QCDEstimation=0
#        for bin in xrange(50,1000):
#            value=DataSampleQCDNormHist.GetBinContent(bin)
#            if value < 0 : value=0
#            FR= _FIT_Jet_Function(bin+1.5,FR_FitMaram)
#            if FR> 0.9: FR=0.9
#            QCDEstimation += value * FR/(1-FR)
#        if verbos_: print "\n##########\n QCDEstimation",    QCDEstimation
#
#
#        NameOut= "QCD"
#        DataSampleQCDShapeHist.Scale(QCDEstimation/DataSampleQCDShapeHist.Integral())
#        RebinedHist= DataSampleQCDShapeHist.Rebin(RB_)
#        tDirectory.WriteObject(RebinedHist,NameOut)
#
        ################################################
        #  Filling Data
        ################################################
        print "--------------------------------------------------->     Processing Data"
        tDirectory.cd()

        Name='Data'
        NameOut='data_obs'


        NormFile= _FileReturn(SubRootDir,Name, channel,NameCat, NormMC)
        NormHisto=NormFile.Get("HISTO")
        
        if not NormHisto:
            raise Exception('Not valid %s'%NameOut)
        else:
            RebinedHist= NormHisto.Rebin(RB_)
            tDirectory.WriteObject(RebinedHist,NameOut)


    OutFile.Close()






if __name__ == "__main__":
    
#    PlotName=["_tmass_MuMet","_LepEta","_LepPt","_JetPt","_JetEta","_MET","_LQMass","_dPhi_Jet_Met","_dPhi_Mu_Jet","_dPhi_Mu_Met","_NumJet","_NumBJet"]
#    PlotName=["_NumJet","_NumBJet"]
    PlotName=["_LQMass","_WMass","_ZMass"]

    

#    Isolation=["_Iso", "_AntiIso","_Total"]
    Isolation=["_Iso"]
#    MT=["_NoMT", "_LowMT","_HighMT","_MT100","_MT150","_MT200","_MT250","_MT300"]
#    MT= ["_LowMT","_HighMT","_MT100","_MT150","_MT200","_MT300","_MT400"]
    MT=["_NoMT","_HighMT","_MT150","_MT200"]
    JPT=[ "_HighDPhi"]

    for Norm in PlotName:
        for iso in Isolation:
            for mt in MT:
                for jpt in JPT:

                    channel='MuJet'
                    
                    NormMC=Norm+mt+jpt+iso
#                            NormQCD="_CloseJetLepPt"+mt+jpt+etalq+reg+"_AntiIso"
                    NormQCD="_LepPt"+mt+jpt+"_AntiIso"
                    ShapeQCD=Norm+mt+jpt+"_AntiIso"
                    NormTTbar=Norm+"_NoTopRW"+mt+jpt+iso
                    
                    

                    MakeTheHistogram('OutFiles_DiMu_ScaledWZ',channel,NormMC,NormQCD,ShapeQCD,NormTTbar)
                    MakeTheHistogram('OutFiles_DiMu_NoZScale',channel,NormMC,NormQCD,ShapeQCD,NormTTbar)
                    MakeTheHistogram('OutFiles_DiMu_RealDiMu',channel,NormMC,NormQCD,ShapeQCD,NormTTbar)




