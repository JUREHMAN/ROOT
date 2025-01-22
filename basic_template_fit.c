using namespace RooFit;

void DrawPADs(TCanvas* c, RooPlot* frame1, RooPlot* frame2,TLegend* leg){
  c->SetFillColor(0); //Can be set for example 18
  frame2->GetYaxis()->SetLabelSize(0.17);
  frame2->GetYaxis()->SetNdivisions(9,2,0);
  //frame2->GetXaxis()->SetTitleSize(0.12);
  frame2->GetXaxis()->SetLabelSize(0.12);
  TPad* pad1 = new TPad("pad1","", 0.05,0.25,0.95,0.95,0);
  TPad* pad2 = new TPad("pad2","", 0.05,0.05,0.95,0.22,0);
  pad1->Draw();  pad2->Draw();
  pad1->cd();    frame1->Draw();  leg->Draw();
  pad2->cd();    frame2->Draw();
  c->Update();
}

void mbc_CBRooHist(){
  TChain *tsig = new TChain("dataset/TestTree");
  tsig->Add("new_excl_test_train_4WG3.root");

  RooRealVar BDT("BDT", "BDT", 0.13, 0.9);
  RooRealVar classID("classID", "classID", -0.1,2);
  RooArgList *varset = new RooArgList(BDT);
  
  RooDataSet *BDTdata = new RooDataSet("BDTdata", "", tsig, RooArgList(BDT, classID));

  auto RooDataSet_sig = (RooDataSet*) BDTdata->reduce("classID==0");
  auto RooDataSet_bg = (RooDataSet*) BDTdata->reduce("classID==1");

  //Creating Template PDF for the bdt
  TH1F* h100 = static_cast<TH1F*> (RooDataSet_sig->createHistogram("h100", BDT, Binning(7,0.13,0.9)));
  TH1* hist_sig = (TH1*)h100;
  RooDataHist sig_roohist("sig_roohist","",RooArgList(BDT), hist_sig);
  RooHistPdf sig_pdf("sig_pdf","",RooArgSet(BDT), sig_roohist,0); //last parameter is for smoothness

  //background hist
  TH1F* h1000 = static_cast<TH1F*> (RooDataSet_bg->createHistogram("h1000", BDT, Binning(7,0.13,0.9)));
  TH1* hist_bg = (TH1*)h1000;
  RooDataHist bg_roohist("bg_roohist","",RooArgList(BDT), hist_bg);
  RooHistPdf bg_pdf("bg_pdf","",RooArgSet(BDT), bg_roohist,0); //last parameter is FOR SMOOTHNESS
  
  RooRealVar Nsig("Nsig", "Nsig", 600, 0,1500);
  RooRealVar Nbg("Nbg", "Nbg", 300, 50,1000);
  
  //RooRealVar Nsig_toy("Nsig_toy", "Nsig_toy", 26, 0,90);
  RooRealVar Nsig_toy("Nsig_toy", "Nsig_toy", 24, 0,200);
  //RooRealVar Nbg_toy("Nbg_toy", "Nbg_toy", 130, 50,400);
  RooRealVar Nbg_toy("Nbg_toy", "Nbg_toy", 109, 50,500);
  
  RooAddPdf model("model","Signal + background PDF", RooArgList(sig_pdf, bg_pdf), RooArgList(Nsig, Nbg));
  RooAddPdf model_toy("model_toy","Signal + background PDF", RooArgList(sig_pdf, bg_pdf), RooArgList(Nsig_toy, Nbg_toy));
  
  ////Toys data for sig and bg
  double nsig=24; //Number of signal events which we want to generate
  TRandom3*   rand1      = new TRandom3(0);
  double nsig_gen = rand1->Poisson(nsig);
  RooDataSet* data_sig   = sig_pdf.generate(*varset, nsig_gen);
  //data_sig->Print("V");
  
  double nbg=109;
  TRandom3*   rand      = new TRandom3(0);
  double nbg_gen = rand->Poisson(nbg);
  RooDataSet* data_bkg   = bg_pdf.generate(*varset, nbg_gen);
  
  // Toy data generation
  RooDataSet *toy_data = data_sig;
  toy_data->append(*data_bkg);
  
  //Results
  RooFitResult* result_actual = model.fitTo(*BDTdata, Minimizer("Minuit"),Extended(kTRUE),Minos(kTRUE),Save());
  RooFitResult* result_toy = model_toy.fitTo(*toy_data, Minimizer("Minuit"),Extended(kTRUE),Minos(kTRUE),Save());
 
  RooPlot* BDT_frame = BDT.frame();
  RooPlot* bkg_frame = BDT.frame();
  
  BDTdata->plotOn(BDT_frame,Binning(7));
  toy_data->plotOn(bkg_frame,Binning(7));
  BDTdata->statOn(BDT_frame);
  toy_data->statOn(bkg_frame);
  model.plotOn(BDT_frame);
  model_toy.plotOn(bkg_frame);
  
  double BDT_chis = BDT_frame->chiSquare();
  RooHist* BDTpull = BDT_frame->pullHist();
  BDTpull->SetFillStyle(1001);
  BDTpull->SetFillColor(4);
  for(int i=0;i<BDTpull->GetN();++i) BDTpull->SetPointError(i,0.0,0.0,0.0,0.0);
  RooPlot* BDTframepull = BDT.frame(Title("Data Pull Distirbution"));
  BDTframepull->addPlotable(BDTpull, "B");
  model.plotOn(BDT_frame, Components(sig_pdf), LineStyle(kDashed), LineColor(kBlue));
  model.plotOn(BDT_frame, Components(bg_pdf), LineStyle(kDashed), LineColor(kRed));
  model.paramOn(BDT_frame);
  model_toy.plotOn(bkg_frame, Components(sig_pdf), LineStyle(kDashed), LineColor(kBlue));
  model_toy.plotOn(bkg_frame, Components(bg_pdf), LineStyle(kDashed), LineColor(kRed));
  model_toy.paramOn(bkg_frame);
  
  //Pull for toy data
  double toys_chis = bkg_frame->chiSquare();
  RooHist* toyspull = bkg_frame->pullHist();
  toyspull->SetFillStyle(1001);
  toyspull->SetFillColor(4);
  for(int i=0;i<toyspull->GetN();++i) toyspull->SetPointError(i,0.0,0.0,0.0,0.0);
  RooPlot* toysframepull = BDT.frame(Title("Toys Pull Distirbution"));
  toysframepull->addPlotable(toyspull, "B");
  
  TCanvas *c1 = new TCanvas();
  TLegend* legend1 = new TLegend(0.2, 0.2, 0.3, 0.3);
  legend1->AddEntry(BDT_frame->getObject(0), "MC Data");
  legend1->AddEntry(BDT_frame->getObject(2), "Total pdf", "l");
  legend1->AddEntry(BDT_frame->getObject(3), "Signal pdf", "l");
  legend1->AddEntry(BDT_frame->getObject(4), "Background pdf", "l");
  
  legend1->SetBorderSize(0);
  
  DrawPADs(c1, BDT_frame, BDTframepull, legend1);
  
  TCanvas *c2 = new TCanvas();
  TLegend* legend2 = new TLegend(0.2, 0.2, 0.3, 0.3);
  legend2->AddEntry(bkg_frame->getObject(0), "Toys Data", "lep");
  legend2->AddEntry(bkg_frame->getObject(2), "Total pdf", "l");
  legend2->AddEntry(bkg_frame->getObject(3), "Signal pdf", "l");
  legend2->AddEntry(bkg_frame->getObject(4), "Background pdf", "l");
  
  legend2->SetBorderSize(0);
  DrawPADs(c2, bkg_frame, toysframepull, legend2);
  
  result_actual->Print();
  result_toy->Print();
  std::cout << "Quality of fit (chisquare/bin): BDT = " << BDT_chis <<  std::endl; 
  std::cout << "Quality of fit (chisquare/bin): Toys = " << toys_chis <<  std::endl; 

}

void bdt04(){
  mbc_CBRooHist();
}
