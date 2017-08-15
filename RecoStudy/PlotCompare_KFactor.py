import os
import ROOT
from ROOT import *
import array

rb_=array.array("d",[0,50,100,150,200,250,300,375,450,525,600,700,1000])

def MakeCompare(root1,hist1, root2,hist2, root3, hist3,Name):
    
    ROOT.gStyle.SetFrameLineWidth(3)
    ROOT.gStyle.SetLineWidth(3)
    ROOT.gStyle.SetOptStat(0)
    
    c=ROOT.TCanvas("canvas","",0,0,600,600)
    c.cd()
    
    
    file1=TFile(root1,"open")
    print "---->,", file1.GetName()
    Histo1_=file1.Get(hist1)
    Histo1=Histo1_.Rebin(len(rb_)-1,"",rb_)
    Histo1.SetLineColor(2)
    Histo1.SetLineWidth(2)
    Histo1.SetMaximum(Histo1.GetMaximum()*2)
    
    file2=TFile(root2,"open")
    Histo2_=file2.Get(hist2)
    Histo2=Histo2_.Rebin(len(rb_)-1,"",rb_)
    Histo2.SetLineColor(3)
    Histo2.SetLineWidth(3)
    
    file3=TFile(root3,"open")
    Histo3_=file3.Get(hist3)
    Histo3=Histo3_.Rebin(len(rb_)-1,"",rb_)
    Histo3.SetLineColor(4)
    Histo3.SetLineWidth(4)
    

    Histo1.SetTitle('')
    Histo1.GetXaxis().SetTitle('boson p_{T} (GeV)')
    Histo1.GetXaxis().SetLabelSize(0.04)
    Histo1.GetXaxis().SetNdivisions(505)
    Histo1.GetXaxis().SetTitleSize(0.05)
    Histo1.GetXaxis().SetTitleOffset(0.9)
    Histo1.GetXaxis().SetLabelSize(0.04)
    Histo1.GetXaxis().SetTitleFont(42)
    Histo1.GetYaxis().SetTitle("Events")
    Histo1.GetXaxis().SetRangeUser(0,1000)
    




    pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
#    if isLOG: pad1.SetLogy()
    pad1.Draw()
    pad1.cd()
    pad1.SetFillColor(0)
    pad1.SetBorderMode(0)
    pad1.SetBorderSize(10)
    pad1.SetTickx(1)
    pad1.SetTicky(1)
    pad1.SetLeftMargin(0.18)
    pad1.SetRightMargin(0.05)
    pad1.SetTopMargin(0.122)
    pad1.SetBottomMargin(0.026)
    pad1.SetFrameFillStyle(0)
    pad1.SetFrameLineStyle(0)
    pad1.SetFrameLineWidth(3)
    pad1.SetFrameBorderMode(0)
    pad1.SetFrameBorderSize(10)
    
    
    
    
    
    
    Histo1.Draw()
    Histo2.Draw('same')
    Histo3.Draw('same')

    leg=TLegend(.5,.3,.9,.5, "", "brNDC")
    leg.SetLineWidth(1)
    leg.SetLineStyle(0)
    leg.SetFillStyle(0)
#    leg.SetBorderSize(0)
    leg.SetTextFont(62)
    leg.AddEntry(Histo1,hist1.replace("_CMS_scale",""),'l')
    leg.AddEntry(Histo2,hist2.replace("_CMS_scale",""),'l')
    leg.AddEntry(Histo3,hist3.replace("_CMS_scale",""),'l')
    leg.Draw()
    
    
    
    c.cd()
    pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
    pad2.SetTopMargin(0.05);
    pad2.SetBottomMargin(0.35);
    pad2.SetLeftMargin(0.18);
    pad2.SetRightMargin(0.05);
    pad2.SetTickx(1)
    pad2.SetTicky(1)
    pad2.SetFrameLineWidth(3)
    pad2.SetGridx()
    pad2.SetGridy()
    pad2.Draw()
    pad2.cd()
    
    
    
    
    h1=Histo1.Clone()
    h1.SetMaximum(2)
    h1.SetMinimum(0)
    h1.SetMarkerStyle(20)
    
    h3=Histo2.Clone()
    
    h3.Sumw2()
    h1.Sumw2()
    
    
    h1.SetStats(0)
    h3.SetStats(0)
    h1.SetTitle("")
    
    h1.Divide(h3)
    
    
    h1.GetXaxis().SetTitle("")
    h1.GetXaxis().SetLabelSize(0.08)
    h1.GetYaxis().SetLabelSize(0.08)
    h1.GetYaxis().SetTitle("Obs./Exp.")
    h1.GetXaxis().SetNdivisions(505)
    h1.GetYaxis().SetNdivisions(5)
    h1.GetXaxis().SetTitleSize(0.15)
    h1.GetYaxis().SetTitleSize(0.15)
    h1.GetYaxis().SetTitleOffset(0.56)
    h1.GetXaxis().SetTitleOffset(1.04)
    h1.GetXaxis().SetLabelSize(0.11)
    h1.GetYaxis().SetLabelSize(0.11)
    h1.GetXaxis().SetTitleFont(42)
    h1.GetYaxis().SetTitleFont(42)
    
    h1.Draw("ep2")
#    h3.Draw("E0psame")

    c.cd()
    pad1.Draw()
    
    ROOT.gPad.RedrawAxis()
    
    c.Modified()
    
    
    
    c.SaveAs('kfactor%s.pdf'%Name)


location='OutFiles_LO/'
MakeCompare(location+'DYJetsToLL_FXFX.root','_ZBosonPt',location+'DYJetsToLL_LO.root','_ZBosonPt',location+'DYJetsToLL_LO.root','_ZBosonPt_KFactor','_Z')



MakeCompare(location+'WJetsToLNu_FXFX.root','_WBosonPt',location+'WJetsToLNu_LO.root','_WBosonPt',location+'WJetsToLNu_LO.root','_WBosonPt_KFactor','_W')


