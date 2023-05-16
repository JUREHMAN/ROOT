import ROOT
from ROOT import gROOT
from ROOT import TCanvas, TPad, TFile, TPaveLabel, TPaveText
#import sys

###Loading the input file
myFile = ROOT.TFile.Open("belle_MC2.root","r") 

####Loading the inclusive tree
incl = myFile.incltag

##Mass of D
c = ROOT.TCanvas()
#var.Draw("m_D","abs(m_D)>2")
incl.Draw("m_D")
c.Draw()
c.SaveAs("mass_of_D_incl.png")

##Cosine of the tag angle
c1 = ROOT.TCanvas()
incl.Draw("cos_pBtag_Dltag")
c1.Draw()
c1.SaveAs("cos_pBtag_Dltag_incl.png")

##Cosine of the angle between visible momentum on the tag side and the first possible solution on the signal side
c2 = ROOT.TCanvas()
incl.Draw("cos_theta_1_tag")
c2.Draw()
c2.SaveAs("cos_theta_1_tag_incl.png")

##Cosine of the angle between visible momentum on the tag side and the second possible solution on the signal side
c3 = ROOT.TCanvas()
incl.Draw("cos_theta_2_tag")
c3.Draw()
c3.SaveAs("cos_theta_2_tag_incl.png")


##Sum of the angles between visible momentum on the tag side and the first possible solution on the signal side
c4 = ROOT.TCanvas()
incl.Draw("cos_theta_1_tag+cos_pBtag_Dltag")
c4.Draw()
c4.SaveAs("cos_theta_1_tag+cos_pBtag_Dltag_incl.png")

##Sum of the angles between visible momentum on the tag side and the second possible solution on the signal side
c5 = ROOT.TCanvas()
incl.Draw("cos_theta_2_tag+cos_pBtag_Dltag")
c5.Draw()
c5.SaveAs("cos_theta_2_tag+cos_pBtag_Dltag_incl.png")

####Loading the exclusive tree
excl = myFile.excl

##Mass of D
c01 = ROOT.TCanvas()

excl.Draw("m_D")
c01.Draw()
c01.SaveAs("mass_of_D_excl.png")

##Cosine of the tag angle
c02 = ROOT.TCanvas()
excl.Draw("cos_pBtag_Dltag")
c02.Draw()
c02.SaveAs("cos_pBtag_Dltag_excl.png")

##Cosine of the angle between visible momentum on the tag side and the first possible solution on the signal side
c03 = ROOT.TCanvas()
excl.Draw("cos_theta_1_tag")
c03.Draw()
c03.SaveAs("cos_theta_1_tag_excl.png")

##Cosine of the angle between visible momentum on the tag side and the second possible solution on the signal side
c04 = ROOT.TCanvas()
excl.Draw("cos_theta_2_tag")
c04.Draw()
c04.SaveAs("cos_theta_2_tag_excl.png")

##Sum of the angles between visible momentum on the tag side and the first possible solution on the signal side
c05 = ROOT.TCanvas()
excl.Draw("cos_theta_1_tag+cos_pBtag_Dltag")
c05.Draw()
c05.SaveAs("cos_theta_1_tag+cos_pBtag_Dltag_excl.png")

##Sum of the angles between visible momentum on the tag side and the second possible solution on the signal side
c06 = ROOT.TCanvas()
excl.Draw("cos_theta_2_tag+cos_pBtag_Dltag")
c06.Draw()
c06.SaveAs("cos_theta_2_tag+cos_pBtag_Dltag_excl.png")

