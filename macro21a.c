#include "TGraphErrors.h"
void macro21a()
{
    
    TFile *f2 = TFile::Open("noL34_12_1000evts_PXDredON_FullTrackingValidationBkg.root");
    //TH1D *h2 = (TH1D*)f2->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h2= (TH1D*)f2->Get("FullBkg_finding_efficiency_by_theta");
    //TH1D *h2= (TH1D*)f2->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h2= (TH1D*)f2->Get("FullBkg_hit_efficiency_with_matched_tracks_by_theta");
    //TH1D *h2= (TH1D*)f2->Get("FullBkg_finding_and_charge_efficiency_for_primary_tracks_by_phi");
    //TH1D *h2= (TH1D*)f2->Get("expert/FullBkg_z0_res_resolution");
    //TH1D *h2= (TH1D*)f2->Get("expert/FullBkg_d0_estimates");
    //TH1D *h2= (TH1D*)f2->Get("expert/FullBkg_d0_pulls");
    //TH1D *h2= (TH1D*)f2->Get("expert/FullBkg_omega_estimates");
    //TH1D *h2= (TH1D*)f2->Get("expert/FullBkg_omega_pulls");
    //TH1D *h2= (TH1D*)f2->Get("expert/FullBkg_tan_lambda_estimates");
    //TGraphErrors *h2= (TGraphErrors*)f2->Get("expert/FullBkg_pt_res_resolution");
    //TGraphErrors *h2= (TGraphErrors*)f2->Get("expert/FullBkg_z0_res_resolution");
    TGraphErrors *h2= (TGraphErrors*)f2->Get("expert/FullBkg_d0_res_resolution");
    //h2->SetStats(0);
    h2->Draw("E");
    //h2->Draw("E");
    //h2->SetLineWidth(1);
    h2->SetLineColor(4);
    //h2->SetPointError(pointNumber, errorX, errorY);
    //h2->SetPointError();
       
    TFile *f1 = TFile::Open("def_1000evts_PXDredON_FullTrackingValidationBkg.root");
    //TH1D *h1= (TH1D*)f1->Get("FullBkg_finding_efficiency_by_phi");
    //TH1D *h1= (TH1D*)f1->Get("FullBkg_finding_efficiency_by_theta");
    //TH1D *h1= (TH1D*)f1->Get("FullBkg_hit_efficiency_with_matched_tracks_by_phi");
    //TH1D *h1= (TH1D*)f1->Get("FullBkg_hit_efficiency_with_matched_tracks_by_theta");
    //TH1D *h1= (TH1D*)f1->Get("FullBkg_finding_and_charge_efficiency_for_primary_tracks_by_phi");
    //TH1D *h1= (TH1D*)f1->Get("expert/FullBkg_z0_res_resolution");
    //TH1D *h1= (TH1D*)f1->Get("expert/FullBkg_d0_estimates");
    //TH1D *h1= (TH1D*)f1->Get("expert/FullBkg_d0_pulls");
    //TH1D *h1= (TH1D*)f1->Get("expert/FullBkg_omega_estimates");
    //TH1D *h1= (TH1D*)f1->Get("expert/FullBkg_omega_pulls");
    //TH1D *h1= (TH1D*)f1->Get("expert/FullBkg_tan_lambda_estimates");
    //TGraphErrors *h1= (TGraphErrors*)f1->Get("expert/FullBkg_pt_res_resolution");
    //TGraphErrors *h1= (TGraphErrors*)f1->Get("expert/FullBkg_z0_res_resolution");
    TGraphErrors *h1= (TGraphErrors*)f1->Get("expert/FullBkg_d0_res_resolution");
    //h1->SetStats(0);
    h1->Draw("same");
    //h1->Draw("E same");
    //h1->SetLineWidth(1);
    h1->SetLineColor(2);
    //h1->SetPointError();
    //h1->SetPointError(pointNumber, errorX, errorY);
    TLegend *leg = new TLegend(0.2,0.2,0.3,0.3);
    leg->AddEntry(h1,"No Masking","l");
    leg->AddEntry(h2,"Ladder 3,4 Masked","l");
    leg->Draw();
}
 

