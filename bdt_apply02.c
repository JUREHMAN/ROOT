#include "TMath.h"

void bdt_apply02() {
   
    TFile* inputFile = new TFile("skimmed_mixed_signal_with_el_mu_IDs_stream01.root");
    TTree* Data = (TTree*)inputFile->Get("incl");
    
    TFile* outputFile = TFile::Open("bdt_mixedB_output02.root", "RECREATE");
    TTree* outputTree = Data->CloneTree(0); //cloning the input tree
    
    Double_t var0=-99., var1=-99.,var2=-99.,var3=-99.,var4=-99.,bdt=-1;
    Int_t var5=-99.;
    
    Data->SetBranchAddress("deltaE_Btag", &var0);
    Data->SetBranchAddress("best_sum", &var1);
    Data->SetBranchAddress("p_ltag", &var2);
    Data->SetBranchAddress("m_ROE", &var3);
    Data->SetBranchAddress("nLepton", &var4);
    Data->SetBranchAddress("nPhotonsSelected", &var5);
    //Data->SetBranchAddress("bdt", &bdt);
    
    TBranch* bdtBranch = outputTree->Branch("bdt", &bdt, "bdt/D"); //Creating the new branch for the bdt variable
    
    Float_t uservar0=-99., uservar1=-99.,uservar2=-99.,uservar3=-99.,uservar4=-99.,uservar5=-99.;
    
    TMVA::Reader *reader = new TMVA::Reader();
    
    reader->AddVariable("deltaE_Btag",&uservar0);
    reader->AddVariable("best_sum", &uservar1);
    reader->AddVariable("p_ltag", &uservar2);
    reader->AddVariable("m_ROE",&uservar3);
    reader->AddVariable("nLepton", &uservar4);
    reader->AddVariable("nPhotonsSelected", &uservar5);
    
    //Spectator
    //reader->AddSpectator("tanh(costheta_{tag}) := TMath::TanH(cos_pBtag_Dltag)", &uservar6);
    //reader->AddSpectator("costheta_{tag} := cos_pBtag_Dltag",&uservar6);
    //reader->AddSpectator("tanh(best_sum) := TMath::TanH(best_sum)",&uservar8);
    
    reader->BookMVA("My BDT", "dataset/weights/TMVAClassification_BDT.weights.xml");
    
    int nEnt = Data->GetEntries();
    
// ------- start your event loop
    for (Long64_t ievt=0; ievt<nEnt; ++ievt) {
         Data->GetEntry(ievt);
         //double fisher = reader->EvaluateMVA("Fisher discriminant");
         uservar0 = var0;
         uservar1 = TMath::TanH(var1);
         uservar2 = var2;
         uservar3 = var3;
         uservar4 = var4;
         uservar5 = var5;
         bdt = reader->EvaluateMVA("My BDT");
         //cout<<"var0= "<<var0<<" var1="<<var1<<" var2= "<<var2<<" var3= "<<var3<<" var4= "<<var4<<" var5= "<<var5<<" BDT= "<<bdt<<endl;
         //cout<<"entry = "<<ievt<<", BDT= "<<bdt<<endl;
         outputTree->Fill();
}
cout<<" Total number of entries for which BDT is evaluated= "<<nEnt<<endl;
outputFile->cd();
outputTree->Write();
delete reader;
inputFile->Close();
outputFile->Close();
}
