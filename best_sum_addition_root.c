#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
//This macro will add the best_sum variable to the existing root file
void best_sum_addition_root() {
    // Open the input file and get the tree
    TFile* inputFile = new TFile("signal_full_sample_without_cuts_and_with_decay_ids.root", "UPDATE");
    TTree* tree = (TTree*)inputFile->Get("Allincltag");

    // Declare variables
    Double_t sum_ang1_plus_tag, sum_ang2_plus_tag, best_sum;
    int are_equal, initial_sign;
    Double_t min_abs_val, max_abs_val, max_val, tot_sign, prod;

    // Set branch addresses
    tree->SetBranchAddress("sum_ang1_plus_tag", &sum_ang1_plus_tag);
    tree->SetBranchAddress("sum_ang2_plus_tag", &sum_ang2_plus_tag);

    // Create a new branch for best_sum
    TBranch* newBranch = tree->Branch("best_sum", &best_sum, "best_sum/D");

    // Loop over the entries to calculate and fill best_sum
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);

        // Calculate best_sum (same logic as before)
        if (TMath::Abs(sum_ang1_plus_tag) < TMath::Abs(sum_ang2_plus_tag)) {
            min_abs_val = TMath::Abs(sum_ang1_plus_tag);
        } else {
            min_abs_val = TMath::Abs(sum_ang2_plus_tag);
        }

        if (TMath::Abs(sum_ang1_plus_tag) > TMath::Abs(sum_ang2_plus_tag)) {
            max_abs_val = TMath::Abs(sum_ang1_plus_tag);
        } else {
            max_abs_val = TMath::Abs(sum_ang2_plus_tag);
        }

        if (sum_ang1_plus_tag > sum_ang2_plus_tag) {
            max_val = sum_ang1_plus_tag;
        } else {
            max_val = sum_ang2_plus_tag;
        }

        if (max_abs_val == max_val) {
            are_equal = 1;
        } else {
            are_equal = 0;
        }

        initial_sign = (are_equal - 0.5) * 2;
        prod = sum_ang1_plus_tag * sum_ang2_plus_tag;

        if (prod != 0) {
            tot_sign = prod / TMath::Abs(prod);
        } else {
            tot_sign = 0;
        }

        best_sum = initial_sign * tot_sign * min_abs_val;
        
        // Fill the new branch
        newBranch->Fill();
    }

    // Write the changes to the tree and close the file
    tree->Write("", TObject::kOverwrite);
    inputFile->Close();
}

