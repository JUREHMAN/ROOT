#include "TMath.h"

void best_sum()
{
// Opening the signal and background files
TFile* inputFileSig = new TFile("signal_full_sample_without_cuts_and_with_decay_ids_match_mc.root");
TTree* sig = (TTree*)inputFileSig->Get("Allincltag");

//formulating the best sum of cosine angles
//variables declaration
int are_equal,initial_sign;
Double_t sum_ang1_plus_tag, sum_ang2_plus_tag, min_abs_val, max_abs_val, max_val, tot_sign, prod, best_sum, bad_sum;
Long64_t nEntries = sig->GetEntries();

//Histograms
TH1F *hist = new TH1F("hist1","Histogram",70,-2.5,2.5);

//signal tree
sig->SetBranchAddress("sum_ang1_plus_tag", &sum_ang1_plus_tag);  
sig->SetBranchAddress("sum_ang2_plus_tag", &sum_ang2_plus_tag);

//For loop
for (Long64_t i = 0; i < nEntries; i++){
    sig->GetEntry(i);
    
    //Selecting the minimum absolute value
    if (TMath::Abs(sum_ang1_plus_tag) < TMath::Abs(sum_ang2_plus_tag)){
        min_abs_val = TMath::Abs(sum_ang1_plus_tag);
    } else{
        min_abs_val = TMath::Abs(sum_ang2_plus_tag);
    }
    
    //Selcting the maximum absolute value
    if(TMath::Abs(sum_ang1_plus_tag)>TMath::Abs(sum_ang2_plus_tag)){
        max_abs_val = TMath::Abs(sum_ang1_plus_tag);
    } else{
        max_abs_val = TMath::Abs(sum_ang2_plus_tag);
    }
    
    //Selcting the maximum value
    if(sum_ang1_plus_tag>sum_ang2_plus_tag){
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
   hist->Fill(best_sum);
   }
hist->Draw("best_sum");
}
