
red_cuts=PAWformula(alcut, math=1)

ttt=charg
#fred=TFile("reduced_try2024_DsDstst4_Ver3upd2_BmassConst_merged.root", "RECREATE")
fred=TFile("skimmed_charged_signal_with_el_mu_IDs_stream02.root", "RECREATE")

tired = ttt.CopyTree(red_cuts)

tired.Write()
fred.Close()
print("Done with the skimming......")


