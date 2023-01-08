void macro20a()
{
    
    TFile *f1 = TFile::Open("def_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    TH1D *h1= (TH1D*)f1->Get("SVD4Layer_finding_efficiency_by_phi");
    //TH1D *h1= (TH1D*)f1->Get("SVD4Layer_finding_efficiency_by_theta");
    //TH1D *h1= (TH1D*)f1->Get("SVD4Layer_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h1= (TH1D*)f1->Get("SVD4Layer_hit_efficiency_with_matched_tracks_by_theta");
    //TH1D *h1= (TH1D*)f1->Get("SVD4Layer_finding_and_charge_efficiency_for_primary_tracks_by_phi");
    //TH1D *h1= (TH1D*)f1->Get("SVD4Layer_fake_rate_by_Seed_phi");
    h1->SetStats(0);
    h1->Draw("hist l");
    h1->Draw("E");
    h1->SetLineWidth(1);
    h1->SetLineColor(2);
    
    TFile *f2 = TFile::Open("noL34_12_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    TH1D *h2 = (TH1D*)f2->Get("SVD4Layer_finding_efficiency_by_phi");
    //TH1D *h2= (TH1D*)f2->Get("SVD4Layer_finding_efficiency_by_theta");
    //TH1D *h2= (TH1D*)f2->Get("SVD4Layer_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h2= (TH1D*)f2->Get("SVD4Layer_hit_efficiency_with_matched_tracks_by_theta");
    //TH1D *h2= (TH1D*)f2->Get("SVD4Layer_finding_and_charge_efficiency_for_primary_tracks_by_phi");
    //TH1D *h2= (TH1D*)f2->Get("SVD4Layer_fake_rate_by_Seed_phi");
    h2->SetStats(0);
    h2->Draw("hist l same");
    h2->Draw("E SAME");
    h2->SetLineWidth(1);
    h2->SetLineColor(4);
    TLegend *leg = new TLegend(0.2,0.2,0.3,0.3);
    leg->AddEntry(h1,"No Masking","l");
    leg->AddEntry(h2,"Ladder 3,4 Masked","l");
    leg->Draw();
}

