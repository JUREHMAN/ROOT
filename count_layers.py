import ROOT
from ROOT import gROOT
from ROOT import TCanvas, TPad, TFile, TPaveLabel, TPaveText

myFile = ROOT.TFile.Open("CDC_TRACKING_MY_OWN_MODULE_OUPUT01.root")
hit = myFile.Get('CDC/hHit')

#Internal layers hits
integ1 = hit.Integral(0,7,0,160)

#External layers hits
integ2 = hit.Integral(8,55,0,390)

print("Total hits in the internal layers ",integ1)
print("Total hits in the external layers ",integ2)

#Avergae internal hits
avg1 = integ1 / 8.0

#Average external hits
avg2 = integ2 / 48

print("Average hits in the internal layers ",avg1)
print("Average hits in the external layers ",avg2)

#Avergae internal hit per event
avg_per_event_internal = avg1 / 1000.00

#Average external hit per event
avg_per_event_external = avg2 / 1000.00

print("Average hits per event in the internal layers ",avg_per_event_internal)
print("Average hits per event in the external layers ",avg_per_event_external)

#Total number of hits per event
N = (integ1 + integ2) / 1000.00 

print("Total number of hits per event ", N)

#Rate calculation
#R = N/(T1*L1 + T2*L2) [Hz/wire]

T1 = 408.7 * 10**-9
T2 = 754.6 * 10**-9
L1 = 1280
L2 = 13056 
D = T1*L1 + T2*L2
R = N / D

print("The rate is ",R," Hz/wire") 
