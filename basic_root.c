//ROOT comands for plotting in the TBrowser
file->Draw("cos_theta_3_tag+cos_pBtag_Dmu","(cos_pBtag_Dmu<3) && (cos_pBtag_Dmu>-3)");
file->Draw("cos_theta_3_tag-cos_theta_4_tag","(cos_pBtag_Dmu<3) && (cos_pBtag_Dmu>-3)");
file->Draw("cos_theta_3_tag+cos_theta_4_tag","(cos_pBtag_Dmu<3) && (cos_pBtag_Dmu>-3)");
