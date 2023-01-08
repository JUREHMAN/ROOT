void macro3a()
{

//This is for the full tracking case

    //Perfect Detector
    TFile *f1 = TFile::Open("def_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    //TH1D *h1= (TH1D*)f1->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h1= (TH1D*)f1->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h1= (TH1D*)f1->Get("FullBkg_finding_efficiency_by_theta");
    TH1D *h1= (TH1D*)f1->Get("SVD4Layer_finding_efficiency_by_theta");
    h1->SetStats(0);
    h1->Draw("hist l");
    h1->SetLineWidth(1);
    h1->SetLineColor(2);
    
    //No L3
    TFile *f8 = TFile::Open("noL3_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    //TH1D *h8 = (TH1D*)f8->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h8 = (TH1D*)f8->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h8= (TH1D*)f8->Get("FullBkg_finding_efficiency_by_theta");
    TH1D *h8= (TH1D*)f8->Get("SVD4Layer_finding_efficiency_by_theta");
    h8->SetStats(0);
    h8->Draw("hist l same");
    h8->SetLineWidth(1);
    h8->SetLineColor(15);
    
    //No L3 side 0
    TFile *f2 = TFile::Open("noL3_Side0_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    //TH1D *h2 = (TH1D*)f2->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h2= (TH1D*)f2->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h2= (TH1D*)f2->Get("FullBkg_finding_efficiency_by_theta");
    TH1D *h2= (TH1D*)f2->Get("SVD4Layer_finding_efficiency_by_theta");
    h2->SetStats(0);
    h2->Draw("hist l same");
    h2->SetLineWidth(1);
    h2->SetLineColor(3);
    
    //No L3 side1 
    TFile *f3 = TFile::Open("noL3_Side1_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    //TH1D *h3 = (TH1D*)f3->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h3= (TH1D*)f3->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h3= (TH1D*)f3->Get("FullBkg_finding_efficiency_by_theta");
    TH1D *h3= (TH1D*)f3->Get("SVD4Layer_finding_efficiency_by_theta");
    h3->SetStats(0);
    h3->Draw("hist l same");
    h3->SetLineWidth(1);
    h3->SetLineColor(4);
    
    //No L3 Lad 3,4 side 0
    TFile *f4 = TFile::Open("noL3Lad34_Side0_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    //TH1D *h4 = (TH1D*)f4->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h4= (TH1D*)f4->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h4= (TH1D*)f4->Get("FullBkg_finding_efficiency_by_theta");
    TH1D *h4= (TH1D*)f4->Get("SVD4Layer_finding_efficiency_by_theta");
    h4->SetStats(0);
    h4->Draw("hist l same");
    h4->SetLineWidth(1);
    h4->SetLineColor(6);
    
    //No L3 Lad 3,4 side 1
    TFile *f5 = TFile::Open("noL3Lad34_Side1_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    //TH1D *h5 = (TH1D*)f5->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h5= (TH1D*)f5->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h5= (TH1D*)f5->Get("FullBkg_finding_efficiency_by_theta");
    TH1D *h5= (TH1D*)f5->Get("SVD4Layer_finding_efficiency_by_theta");
    h5->SetStats(0);
    h5->Draw("hist l same");
    h5->SetLineWidth(1);
    h5->SetLineColor(8);
    
    //No L3 Lad 2,3,4,5 side 0
    TFile *f6 = TFile::Open("noL3Lad2345_Side0_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    //TH1D *h6 = (TH1D*)f6->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h6= (TH1D*)f6->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h6= (TH1D*)f6->Get("FullBkg_finding_efficiency_by_theta");
    TH1D *h6= (TH1D*)f6->Get("SVD4Layer_finding_efficiency_by_theta");
    h6->SetStats(0);
    h6->Draw("hist l same");
    h6->SetLineWidth(1);
    h6->SetLineColor(9);
    
    //No L3 Lad 2,3,4,5 side 1
    TFile *f7 = TFile::Open("noL3Lad2345_Side1_1000evts_PXDredON_SVDTrackingValidationBkg.root");
    //TH1D *h7 = (TH1D*)f7->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h7= (TH1D*)f7->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h7= (TH1D*)f7->Get("FullBkg_finding_efficiency_by_theta");
    TH1D *h7= (TH1D*)f7->Get("SVD4Layer_finding_efficiency_by_theta");
    h7->SetStats(0);
    h7->Draw("hist l same");
    h7->SetLineWidth(1);
    h7->SetLineColor(12);
    
    
    //Legends
    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
    leg->SetHeader("SVD Tracking Validation","C");
    leg->AddEntry(h1,"No Masking","l");
    leg->AddEntry(h8,"L3 Masked","l");
    leg->AddEntry(h2,"L3 side 0 Masked","l");
    leg->AddEntry(h3,"L3 side 1 Masked","l");
    leg->AddEntry(h4,"L3Lad3,4 side 0 Masked","l");
    leg->AddEntry(h5,"L3Lad3,4 side 1 Masked","l");
    leg->AddEntry(h6,"L3Lad2,3,4,5 side 0 Masked","l");
    leg->AddEntry(h7,"L3Lad2,3,4,5 side 1 Masked","l");
    leg->Draw();
}
