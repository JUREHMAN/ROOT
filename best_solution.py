import ROOT
from ROOT import gROOT
from ROOT import TCanvas, TPad, TFile, TPaveLabel, TPaveText
from ROOT import *
#import sys

###Loading the input file
myFile = ROOT.TFile.Open("Debug02.root","r") 

####Loading the inclusive tree
incl=myFile.Get("incltag")

min_value = []
max_value = []
    
#Loop over the full set of entries in the root file to get the required values
for event in incl:
    
    #abs(cos_theta_1_tag+cos_pBtag_Dltag)
    abs_value_of_soln_1 = event.abs_val_1
    
    #abs(cos_theta_2_tag+cos_pBtag_Dltag)
    abs_value_of_soln_2 = event.abs_val_2
    
    #min(abs(cos_theta_1_tag+cos_pBtag_Dltag),abs(cos_theta_2_tag+cos_pBtag_Dltag))
    min_of_abs_12 = event.Min_abs_1_2
    
    #max(cos_theta_1_tag+cos_pBtag_Dltag,cos_theta_2_tag+cos_pBtag_Dltag))
    max_of_12 = event.Max_1_2
    
    #min(cos_theta_1_tag+cos_pBtag_Dltag,cos_theta_2_tag+cos_pBtag_Dltag)
    min_of_12 = event.Min_1_2
    
    #max(abs(cos_theta_1_tag+cos_pBtag_Dltag),abs(cos_theta_2_tag+cos_pBtag_Dltag))
    max_of_abs_12 = event.Max_abs_1_2
    
    #cos_theta_1_tag+cos_pBtag_Dltag
    sum_of_1_tag = event.sum_ang1_plus_tag
    
    #cos_theta_2_tag+cos_pBtag_Dltag
    sum_of_2_tag = event.sum_ang2_plus_tag
    
    #min_value = float()
    #max_value = float()
     
    if max_of_12 != max_of_abs_12:
       #min_value += event.Max_1_2
       #max_value += event.Min_1_2
       min_value.append(max_of_12)
       max_value.append(min_of_12)
       
       #print("if:",min_value,max_value)
      
    else:
       #min_value += event.Min_1_2
       #max_value += event.Max_1_2
       min_value.append(min_of_12)
       max_value.append(max_of_12)
       #print("else:",min_value,max_value)

#Histogram for minimum solution
h1= TH1F("h1","Minimum and Maximum Solution",50,-10,10)
for entry in min_value:
       h1.Fill(entry)
c1=TCanvas()
h1.Draw()
h1.SetLineColor(4);
h1.SetStats(0);

#Histogram for maximum solution
h2= TH1F("h2","Minimum and Maximum Solution",50,-10,10)
for entry in max_value:
       h2.Fill(entry)
h2.Draw("Same")
h2.SetLineColor(2);
h2.SetStats(0);

##Legend
leg = TLegend(0.2,0.2,0.3,0.3)
leg.AddEntry(h1,"Minimum Solution","l")
leg.AddEntry(h2,"Maximum Solution","l")
leg.Draw()

input()
    

