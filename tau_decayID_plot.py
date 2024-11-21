from ROOT import THStack
#loading the required tools for usage of topoana variables
exe dec_utils.py

#Input file
fs = TFile('bdt_signal_output02.root')
get incl sig #Got the tree name

#Attaching the friend tree (Which is already created)
sig.AddFriend('friendTree', 'friend_bdt_signal_output02.root')

'''
#Forming the possible solutions
%form s1 sum_ang1_plus_tag
%form s2 sum_ang2_plus_tag

#Minimum of the absolute value
%form min_abs_value min(abs(s1),abs(s2))

#Maximum value
%form max_value max((s1),(s2))

#Maximum absolute value
%form max_abs_value max(abs(s1),abs(s2))

#Checking if max. absolute value is equal to the max. value or not 
%form is_equal max_value == max_abs_value

#it will return either 0 or 1
%form sign ((is_equal)-0.5)*2

#For preserving the inital sign(+ or -)
%form tot_ch (s1*s2)/(abs(s1*s2))

#Best solution
%form best_soln  sign*tot_ch*min_abs_value
'''
##Setting the bdt limit
%cut bdt_cut bdt > 0.10

#Plotting different decay channel
printDecs(sig, '', 2, 20)

#Defining the cuts
ktaunu_pinu=getCut('B+ -> K+ tau- mu+ | tau- -> pi- nu_tau')
anti_ktaunu_pinu=getCut('B- -> K- tau+ mu- | tau+ -> pi+ anti-nu_tau')
ktaunu_enu=getCut('B+ -> K+ tau- mu+ | tau- -> e- nu_tau anti-nu_e')
anti_ktaunu_enu=getCut('B- -> K- tau+ mu- | tau+ -> e+ anti-nu_tau nu_e')
ktaunu_munu=getCut('B+ -> K+ tau- mu+ | tau- -> mu- nu_tau anti-nu_mu')
anti_ktaunu_munu=getCut('B- -> K- tau+ mu- | tau+ -> mu+ anti-nu_tau nu_mu')
ktaunu_rhonu=getCut('B+ -> K+ tau- mu+ | tau- -> rho- nu_tau')
anti_ktaunu_rhonu=getCut('B- -> K- tau+ mu- | tau+ -> rho+ anti-nu_tau')
cut no_cutID !(ktaunu_pinu)&&(!anti_ktaunu_pinu)&&(!ktaunu_enu)&&(!anti_ktaunu_enu)&&(!ktaunu_munu)&&(!anti_ktaunu_munu)&&(!ktaunu_rhonu)&&(!anti_ktaunu_rhonu)

#Histogram
1d hmx 50 1 7
hicopy hmx hmx1_pinu
hicopy hmx hmx1_enu
hicopy hmx hmx1_munu
hicopy hmx hmx1_rhonu
hicopy hmx hmx1_other

#Stacked histogram
hmx_1 = THStack("hmx_1","")
ntpl sig nLepton ktaunu_pinu||anti_ktaunu_pinu hmx1_pinu
ntpl sig nLepton ktaunu_enu||anti_ktaunu_enu hmx1_enu
ntpl sig nLepton ktaunu_munu||anti_ktaunu_munu hmx1_munu
ntpl sig nLepton ktaunu_rhonu||anti_ktaunu_rhonu hmx1_rhonu
ntpl sig nLepton no_cutID hmx1_other
hmx_1.Add(hmx1_other)
hmx_1.Add(hmx1_rhonu)
hmx_1.Add(hmx1_munu)
hmx_1.Add(hmx1_enu)
hmx_1.Add(hmx1_pinu)

#Filling the color
hmx1_other.SetFillColor(1)
hmx1_rhonu.SetFillColor(2)
hmx1_munu.SetFillColor(3)
hmx1_enu.SetFillColor(4)
hmx1_pinu.SetFillColor(5)

#Setting the stats 
hmx1_other.SetStats(1)
hmx1_rhonu.SetStats(1)
hmx1_munu.SetStats(1)
hmx1_enu.SetStats(1)
hmx1_pinu.SetStats(1)

#Final plot
hipl hmx_1

#Setting the axis variable name
#hmx_1.GetXaxis().SetTitle("bdt for B^{+} #rightarrow K^{+} #tau^{-} #mu^{+}")
hmx_1.GetXaxis().SetTitle("Number of leptons")

#Drawing the legend
from ROOT import TLegend
leg1 = TLegend(0.2,0.2,0.3,0.3)
leg1.AddEntry(hmx1_other,"#tau #rightarrow all other","f")
leg1.AddEntry(hmx1_rhonu,"#tau #rightarrow #rho #nu_{#tau}","f")
leg1.AddEntry(hmx1_munu,"#tau #rightarrow #mu #nu_{#mu} #nu_{#tau}","f") 
leg1.AddEntry(hmx1_enu,"#tau #rightarrow e #nu_{e} #nu_{#tau}","f")
leg1.AddEntry(hmx1_pinu,"#tau #rightarrow #pi #nu_{#tau}","f")
leg1.Draw()
print("Done, please check the plot now..........")
