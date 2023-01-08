#include "TGraphErrors.h"
void tgraph()
{
    
    TFile *f2 = TFile::Open("noL34_12_1000evts_PXDredON_FullTrackingValidationBkg.root");
    TGraphErrors *h2= (TGraphErrors*)f2->Get("expert/FullBkg_d0_res_resolution");
    h2->Draw("");
    h2->Draw("Z");
    h2->SetLineColor(4);
    
    TFile *f1 = TFile::Open("def_1000evts_PXDredON_FullTrackingValidationBkg.root");
    TGraphErrors *h1= (TGraphErrors*)f1->Get("expert/FullBkg_d0_res_resolution");
    h1->Draw("same");
    h1->Draw("Z");
    h1->SetLineColor(2);

    TLegend *leg = new TLegend(0.2,0.2,0.3,0.3);
    leg->AddEntry(h1,"No Masking","l");
    leg->AddEntry(h2,"Ladder 3,4 Masked","l");
    leg->Draw();
}
