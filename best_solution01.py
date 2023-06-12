import ROOT
from ROOT import gROOT
from ROOT import TCanvas, TPad, TFile, TPaveLabel, TPaveText
from ROOT import *
import numpy as np
import re
#import sys

###Loading the input file
myFile = ROOT.TFile.Open("Debug02.root","r") 

####Loading the inclusive tree
incl=myFile.Get("incltag")

min_value = []
max_value = []
    
#Loop over the full set of entries in the root file to get the required values
for event in incl:

    #After using this cut all the nan values removed
    if event.sin_phi <=1 and event.sin_phi >=-1:
    
       #max(cos_theta_1_tag+cos_pBtag_Dltag,cos_theta_2_tag+cos_pBtag_Dltag))
       max_of_12 = event.Max_1_2
    
       #min(cos_theta_1_tag+cos_pBtag_Dltag,cos_theta_2_tag+cos_pBtag_Dltag)
       min_of_12 = event.Min_1_2
    
       #max(abs(cos_theta_1_tag+cos_pBtag_Dltag),abs(cos_theta_2_tag+cos_pBtag_Dltag))
       max_of_abs_12 = event.Max_abs_1_2
    
       if max_of_12 != max_of_abs_12:
          min_value.append(max_of_12)
          max_value.append(min_of_12)
      
       else:
          min_value.append(min_of_12)
   
          max_value.append(max_of_12)
'''
#print("Program run successfuly till min and max value")
print("Length of maximum values..",len(max_value))
print("Lenght of minimum values..",len(min_value))

'''
#For difference and Average of the solution
dif=[]
avg=[]

for i in max_value[:100]:

    for j in min_value[:100]:
                     
        diff= i-j
        average=(i+j)/2.0
        dif.append(diff)
        avg.append(average)
        #print("Done with the i number ",i," and j number ",j," dif and avg value calculation..")
                
#Histogram for minimum solution
h1= TH1F("h1","Minimum and Maximum Solution",100,-2,2)
for entry in min_value:
       h1.Fill(entry)
c1=TCanvas()
h1.Draw()
h1.SetLineColor(4);
h1.SetStats(0);

#Histogram for maximum solution
h2= TH1F("h2","Minimum and Maximum Solution",100,-2,2)
for entry in max_value:
       h2.Fill(entry)
h2.Draw("Same")
h2.SetLineColor(2);
h2.SetStats(0);

#Difference between two solutions
h3= TH1F("h3","Minimum and Maximum Solution",100,-2,2)       
for entry in dif:
    h3.Fill(entry)
h3.Draw("Same")
h3.SetLineColor(6);
h3.SetStats(0);
  
#Average of two solutions
h4= TH1F("h4","Minimum and Maximum Solution",100,-2,2)       
for entry in avg:
    h4.Fill(entry)
h4.Draw("Same")
h4.SetLineColor(8);
h4.SetStats(0);
  
##Legend
leg = TLegend(0.2,0.2,0.3,0.3)
leg.AddEntry(h1,"Minimum Solution","l")
leg.AddEntry(h2,"Maximum Solution","l")
leg.AddEntry(h3,"Diff. of the two Solution","l")
leg.AddEntry(h4,"Average of the two  Solution","l")
leg.Draw()

input()
