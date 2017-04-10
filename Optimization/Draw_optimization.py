#!/usr/bin/env python
import ROOT
import re
from array import array
import os
import json
from pprint import pprint
from ROOT import *


RB_=10
def add_lumi():
    lowX=0.65
    lowY=0.82
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.04)
    lumi.SetTextFont (   42 )
    lumi.AddText("35.9 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.11
    lowY=0.82
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.05)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.22
    lowY=0.82
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.05)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend():
    output = ROOT.TLegend(0.4, 0.65, 0.88, 0.88, "", "brNDC")
    output.SetLineWidth(0)
    output.SetLineStyle(0)
    output.SetFillStyle(0)
    output.SetBorderSize(0)
    output.SetTextFont(62)
    output.SetTextSize(.04)
    return output


def MakePlot(FileName,HistName,Info):
    ROOT.gStyle.SetFrameLineWidth(3)
    ROOT.gStyle.SetLineWidth(3)
    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetPaintTextFormat("1.2f");
    
    c=ROOT.TCanvas("canvas","",0,0,600,600)

    file=ROOT.TFile(FileName,"r")

    Data=file.Get(mass)
    
    
    Data.GetXaxis().SetTitle("")
    




    Data.GetXaxis().SetTitle("")
#    Data.GetXaxis().SetTitleSize(0)
    Data.GetXaxis().SetNdivisions(505)
    Data.GetYaxis().SetLabelFont(42)
    Data.GetYaxis().SetLabelOffset(0.01)
    Data.GetYaxis().SetLabelSize(0.03)
    Data.GetYaxis().SetTitleSize(0.04)
    Data.GetYaxis().SetTitleOffset(1.29904)
    Data.SetTitle("")
    Data.GetZaxis().SetTitle("r-value")
#    Data.GetXaxis().SetTitle(Xaxis)
#    Data.SetMaximum(Data.GetMaximum()*2.5)




    Data.GetXaxis().SetBinLabel(1,'E_{T}^{miss} > 100 GeV')
#    Data.GetXaxis().SetLabelAngle(45)  It seems that this function is not defined in the PYROOT!!!!!! ChangeLable
    Data.GetXaxis().SetBinLabel(2,'E_{T}^{miss} > 150 GeV')
    Data.GetXaxis().SetBinLabel(3,'E_{T}^{miss} > 200 GeV')
    Data.GetXaxis().SetBinLabel(4,'E_{T}^{miss} > 250 GeV')
    Data.GetXaxis().SetBinLabel(5,'E_{T}^{miss} > 300 GeV')

    Data.GetYaxis().RotateTitle(0)
    Data.GetYaxis().SetBinLabel(1,'M_{T}>100')
    Data.GetYaxis().SetBinLabel(2,'M_{T}>150')
    Data.GetYaxis().SetBinLabel(3,'M_{T}>200')
    Data.GetYaxis().SetBinLabel(4,'M_{T}>250')
    Data.GetYaxis().SetBinLabel(5,'M_{T}>300')
    
    
    
    Data.GetZaxis().SetNdivisions(505);
    Data.GetZaxis().SetLabelFont(42);
    Data.GetZaxis().SetLabelOffset(0.007);
    Data.GetZaxis().SetLabelSize(0.035);
    Data.GetZaxis().SetTitleSize(0.045);
    Data.GetZaxis().SetTitleFont(42);
    Data.GetZaxis().SetRangeUser(0.5, 8);
    c.SetLogz()
    ROOT.gStyle.SetPalette(74)
    Data.Draw("COLZtext");
#    Data.Draw("COLZ")



    l1=add_lumi()
    l1.Draw("same")
    l2=add_CMS()
    l2.Draw("same")
    l3=add_Preliminary()
    l3.Draw("same")
    l4=ROOT.TPaveText(0.1,0.82,0.3,0.89, "NDC")
    l4.AddText(Info)
    l4.SetBorderSize(   0 )
    l4.SetFillStyle(    0 )
    l4.SetTextAlign(   12 )
    l4.SetTextColor(    1 )
    l4.SetTextSize(0.04)
    l4.SetTextFont (   42 )
    l4.Draw('same')

    c.SaveAs("_opt_%s.pdf"%mass)









Met_Cat= ["_MET100", "_MET150","_MET200", "_MET250","_MET300"]
MT_Cat = ["_MT100", "_MT150","_MT200", "_MT250","_MT300"]


OutFile=TFile("file.root","RECREATE")
Hist2D=TH2F("2d","2d",5,0,5,5,0,5)
Mass=['800.0','900.0','1000.0','1100.0','1200.0','1300.0','1400.0','1500.0']
Sample=['LQ800_DM300','LQ900_DM350','LQ1000_DM400','LQ1100_DM450','LQ1200_DM500','LQ1300_DM550','LQ1400_DM600','LQ1500_DM650']

for mass in Mass:
    i=0
    for met in Met_Cat:
        i+=1
        j=0
        for mt in MT_Cat:
            j+=1
            with open('outputCodex/Codex%s%s/limits_LIMITS.json'%(mt,met)) as data_file:
                data = json.load(data_file)
                print i,j,data[mass]["exp0"]
                Hist2D.SetBinContent(i,j,data[mass]["exp0"])
    OutFile.WriteObject(Hist2D,mass)
OutFile.Close()


i=-1
for mass in Mass:
    FileName='file.root'
    i+=1
    MakePlot(FileName,mass,Sample[i])





