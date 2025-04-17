////////////////// A simple script for generating toys data and plot various distributions/////////////////
 
using namespace RooFit;

void bdt06(){

  TChain *tsig = new TChain("dataset/TrainTree");
  tsig->Add("bdt_test_train.root");

  TChain *tbkg1 = new TChain("incl");
  tbkg1->Add("reduced_bdt_appl_skimmed_updated_signal_charm_stream3.root");
  tbkg1->Add("reduced_bdt_appl_skimmed_updated_signal_uds_stream3.root");

  RooRealVar BDT("BDT", "BDT", -0.9, 0.9);
  RooRealVar classID("classID", "classID", -0.1,2);
  RooRealVar foxWolframR2("foxWolframR2", "foxWolframR2", 0,1);
  RooArgList *varset = new RooArgList(BDT);
  
  RooDataSet *BDTdata = new RooDataSet("BDTdata", "", tsig, RooArgList(BDT, classID));
  //Adding the ccbar and uds bkg component
  RooDataSet *bkgdata1 = new RooDataSet("bkgdata1", "", tbkg1, RooArgList(BDT, foxWolframR2));

  auto RooDataSet_sig = (RooDataSet*) BDTdata->reduce("classID==0");
  auto RooDataSet_bg0 = (RooDataSet*) BDTdata->reduce("classID==1");
  auto RooDataSet_bg1 = (RooDataSet*) bkgdata1->reduce("foxWolframR2<0.4");
  
  // Total background data
  RooDataSet *RooDataSet_bg = RooDataSet_bg0;
  RooDataSet_bg->append(*RooDataSet_bg1);

  // Creating Template PDFs
  TH1F* h100 = static_cast<TH1F*> (RooDataSet_sig->createHistogram("h100", BDT, Binning(18,-0.9,0.9))); 
  TH1* hist_sig = (TH1*)h100;
  RooDataHist sig_roohist("sig_roohist","",RooArgList(BDT), hist_sig);
  RooHistPdf sig_pdf("sig_pdf","",RooArgSet(BDT), sig_roohist,0);

  TH1F* h1000 = static_cast<TH1F*> (RooDataSet_bg->createHistogram("h1000", BDT, Binning(18,-0.9,0.9))); 
  TH1* hist_bg = (TH1*)h1000;
  RooDataHist bg_roohist("bg_roohist","",RooArgList(BDT), hist_bg);
  RooHistPdf bg_pdf("bg_pdf","",RooArgSet(BDT), bg_roohist,0);
  
  //RooRealVar Nsig("Nsig", "Nsig", 46, -100, 200);
  RooRealVar Nsig("Nsig", "Nsig", 29, -10, 150);
  //RooRealVar Nbg("Nbg", "Nbg", 785, 300, 2000);
  RooRealVar Nbg("Nbg", "Nbg", 827, 300, 2000);
  
  //RooAddPdf model("model","Signal + background PDF", RooArgList(sig_pdf, bg_pdf), RooArgList(Nsig, Nbg));
  RooAddPdf model("model","Signal + background PDF", RooArgList(sig_pdf, bg_pdf), RooArgList(Nsig, Nbg));
  // MC study
  RooMCStudy *mcstudy = new RooMCStudy(model,BDT,Binned(false),Silence(),Extended(true),FitOptions(Save(true),PrintEvalErrors(0)));
  mcstudy->generateAndFit(1000,0,true);
  
  /////////////////////Storing the toy data///////////
  TFile f("mcstudy_output.root", "RECREATE");
   for (int i = 0; i < 1000; i++) {
     const RooAbsData* dataset = mcstudy->genData(i);
     if (!dataset) break;
     dataset->Write(Form("dataset_%d", i));
   }
   f.Close();

  
  //RooDataSet* toyData = model.generate(BDT,1000); 
  
  
  RooPlot *frame1 = mcstudy->plotParam(Nsig, Bins(18));
  frame1->SetTitle("N_{sig}");
  frame1->GetXaxis()->SetTitle("N_{sig}");

  RooPlot *frame2 = mcstudy->plotError(Nsig, Bins(18));
  frame2->SetTitle("N_{sig} Error");
  frame2->GetXaxis()->SetTitle("N_{sig} Error");

  RooPlot *frame3 = mcstudy->plotPull(Nsig, Bins(18), FitGauss(true));
  frame3->SetTitle("N_{sig} Pull");
  frame3->GetXaxis()->SetTitle("N_{sig} Pull");

  RooPlot *frame4 = mcstudy->plotNLL(Bins(18));
  frame4->SetTitle("-log(Likelihood)");
  frame4->GetXaxis()->SetTitle("-log(Likelihood)");
  
  
  //////////////////////////////////////// Construct likelihood and profile likelihood //////////////
  RooAbsData* toyData = mcstudy->genData(27);
  RooAbsReal* nll = model.createNLL(*toyData,Extended(true));
  RooMinimizer m(*nll);
  m.minimize("Minuit2", "migrad+hesse");
  
  RooAbsReal* pll = nll->createProfile(Nsig);
  
  //RooPlot *frame9 = Nsig.frame(Bins(18), Range(1, 80)); //TO separate Nll from PLL as only PLL is not plotable somehow
  RooPlot *frame5 = Nsig.frame(Bins(18), Range(1, 80));
  nll->plotOn(frame5, ShiftToZero(),LineColor(kBlue)); //It is not possible to plot Pll only
  pll->plotOn(frame5,ShiftToZero(),LineColor(kRed));
  
  //Background
  RooPlot *frame6 = mcstudy->plotParam(Nbg, Bins(18));
  frame6->SetTitle("N_{bg}");
  frame6->GetXaxis()->SetTitle("N_{bg}");

  RooPlot *frame7 = mcstudy->plotError(Nbg, Bins(18));
  frame7->SetTitle("N_{bg} Error");
  frame7->GetXaxis()->SetTitle("N_{bg} Error");

  RooPlot *frame8 = mcstudy->plotPull(Nbg, Bins(18), FitGauss(true));
  frame8->SetTitle("N_{bg} Pull");
  frame8->GetXaxis()->SetTitle("N_{bg} Pull");
  
  ////////////////////////////////////////// FINISHED ////////////////////////////////////////////
  // First Canvas for MC Study Plots
  TCanvas *c1 = new TCanvas("c1", "MC Study Plots", 1200, 800);
  c1->Divide(2, 2);
  c1->cd(1);
  frame1->Draw();
  c1->cd(2);
  frame2->Draw();
  c1->cd(3);
  frame3->Draw();
  c1->cd(4);
  frame4->Draw();
  
  // Second Canvas for Likelihood & Profile Likelihood
  TCanvas *c2 = new TCanvas("c2", "Likelihood and Profile Likelihood", 1200, 800);
  frame5->Draw();
  frame5->SetMinimum(0);
  frame5->SetMaximum(2.7);
  TLegend* legend1 = new TLegend(0.2, 0.2, 0.3, 0.3);
  legend1->AddEntry(frame5->getObject(0), "Negative log likelihood (NLL)");
  legend1->AddEntry(frame5->getObject(1), "Profile likelihood (PLL)", "l");
  legend1->Draw();
  
  TCanvas *c3 = new TCanvas("c3", "BKg Plots", 1200, 800);
  c3->Divide(2, 2);
  c3->cd(1);
  frame6->Draw();
  c3->cd(2);
  frame7->Draw();
  c3->cd(3);
  frame8->Draw();
  
}
