#include "TMath.h"

void best_sum01()
{
//formulating the best sum of cosine angles
// Opening the signal and background files
TFile* inputFileSig = new TFile("signal_full_sample_without_cuts_and_with_decay_ids_match_mc.root");
TTree* sig = (TTree*)inputFileSig->Get("Allincltag");

TFile* inputFileBg_charged = new TFile("norm_BplusBminus_with_sin_cut.root");
TTree* bkg_charged = (TTree*)inputFileBg_charged->Get("Allincltag");

TFile* inputFileBg_mixed = new TFile("norm_BBbar_with_sin_cut.root");
TTree* bkg_mixed = (TTree*)inputFileBg_mixed->Get("Allincltag");

//Storing trees in an array
TTree* trees[3] = {sig, bkg_charged, bkg_mixed};

//Histograms
TH1F* hist[3];
hist[0] = new TH1F("hist_signal","Histogram",70,-2.5,2.5);
hist[1] = new TH1F("hist_charged","Histogram",70,-2.5,2.5);
hist[2] = new TH1F("hist_mixed","Histogram",70,-2.5,2.5);

//variables declaration
int are_equal,initial_sign;
Double_t sum_ang1_plus_tag, sum_ang2_plus_tag, min_abs_val, max_abs_val, max_val, tot_sign, prod, best_sum, bad_sum;
Long64_t nEntries = sig->GetEntries();

//Looping over the trees
for (int t = 0; t < 3; t++) {
    TTree* tree = trees[t];
    Long64_t nEntries = tree->GetEntries();
        
    //Addresses of tree
    tree->SetBranchAddress("sum_ang1_plus_tag", &sum_ang1_plus_tag);  
    tree->SetBranchAddress("sum_ang2_plus_tag", &sum_ang2_plus_tag);

    //For loop
    for (Long64_t i = 0; i < nEntries; i++){
        tree->GetEntry(i);
    
        //Selecting the minimum absolute value
        if (TMath::Abs(sum_ang1_plus_tag) < TMath::Abs(sum_ang2_plus_tag)){
           min_abs_val = TMath::Abs(sum_ang1_plus_tag);
           } else{
           min_abs_val = TMath::Abs(sum_ang2_plus_tag);
           }
    
        //Selcting the maximum absolute value
        if (TMath::Abs(sum_ang1_plus_tag)>TMath::Abs(sum_ang2_plus_tag)){
           max_abs_val = TMath::Abs(sum_ang1_plus_tag);
           } else{
           max_abs_val = TMath::Abs(sum_ang2_plus_tag);
           }
    
        //Selcting the maximum value
        if (sum_ang1_plus_tag>sum_ang2_plus_tag){
           max_val = sum_ang1_plus_tag;
           } else{
           max_val = sum_ang2_plus_tag;
           }

        //#Checking if max. absolute value is equal to the max. value or not
        if (max_abs_val == max_val) {
           are_equal = 1;
           } else {
           are_equal = 0;
           }

        //For preserving the initial sign
        initial_sign = (are_equal-0.5)*2;
        prod = sum_ang1_plus_tag*sum_ang2_plus_tag;
        tot_sign = prod / TMath::Abs(prod);

        //Best sum of cosine angles
        best_sum = initial_sign*tot_sign*min_abs_val;
   
        //Filling the hist
        hist[t]->Fill(best_sum);
        }
}

    //Drawing the histograms
    hist[0]->Draw("best_sum");
    //hist[2]->Draw("same");
    hist[1]->Draw("Same");

    //CLosing the files
    //inputFileSig->Close();
    //inputFileBg_charged->Close();
    //inputFileBg_mixed->Close();
}
