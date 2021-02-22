// Analysis.C

#include"DrawTools.h"

TFile* input_file = new TFile("proton_pol.root");
TFile* output_file = nullptr;

TString pdf_name = "fig/analysis.pdf";

void CreateHistograms();
void DrawHistograms();

void Analysis(){
  gROOT->SetBatch(true);


  // initialization ---------------------------------------
  TTree* tree = (TTree*)input_file->Get("EventTree");     
  Int_t dcin_nhit;
  Float_t dcin_position_x, dcin_position_y, dcin_position_z;
  Float_t dcin_momentum_x, dcin_momentum_y, dcin_momentum_z;
  Int_t dcout_nhit;
  Float_t dcout_position_x, dcout_position_y, dcout_position_z;
  Float_t dcout_momentum_x, dcout_momentum_y, dcout_momentum_z;
  Float_t generate_momentum_x, generate_momentum_y, generate_momentum_z;
  Float_t generate_normal_x, generate_normal_y, generate_normal_z;
  Float_t generate_reference_x, generate_reference_y, generate_reference_z;

  tree->SetBranchAddress("dcin_nhit",&dcin_nhit);
  tree->SetBranchAddress("dcin_position_x",&dcin_position_x);
  tree->SetBranchAddress("dcin_position_y",&dcin_position_y);
  tree->SetBranchAddress("dcin_position_z",&dcin_position_z);
  tree->SetBranchAddress("dcin_momentum_x",&dcin_momentum_x);
  tree->SetBranchAddress("dcin_momentum_y",&dcin_momentum_y);
  tree->SetBranchAddress("dcin_momentum_z",&dcin_momentum_z);

  tree->SetBranchAddress("dcout_nhit",&dcout_nhit);
  tree->SetBranchAddress("dcout_position_x",&dcout_position_x);
  tree->SetBranchAddress("dcout_position_y",&dcout_position_y);
  tree->SetBranchAddress("dcout_position_z",&dcout_position_z);
  tree->SetBranchAddress("dcout_momentum_x",&dcout_momentum_x);
  tree->SetBranchAddress("dcout_momentum_y",&dcout_momentum_y);
  tree->SetBranchAddress("dcout_momentum_z",&dcout_momentum_z);

  tree->SetBranchAddress("generate_momentum_x",&generate_momentum_x);
  tree->SetBranchAddress("generate_momentum_y",&generate_momentum_y);
  tree->SetBranchAddress("generate_momentum_z",&generate_momentum_z);
  tree->SetBranchAddress("normal_momentum_x",&normal_momentum_x);
  tree->SetBranchAddress("normal_momentum_y",&normal_momentum_y);
  tree->SetBranchAddress("normal_momentum_z",&normal_momentum_z);
  tree->SetBranchAddress("reference_momentum_x",&reference_momentum_x);
  tree->SetBranchAddress("reference_momentum_y",&reference_momentum_y);
  tree->SetBranchAddress("reference_momentum_z",&reference_momentum_z);

  output_file = new TFile("output.root","RECREATE");
  CreateHistograms();
  // ------------------------------------------------------


  // analysis ---------------------------------------------
  Long64_t total_entries = tree->GetEntries();
  for(Long64_t i_entry=0; i_entry<total_entries; ++i_entry){
    if((i_entry+1)%(Int_t)pow(10, (Int_t)log10(i_entry+1)) ==0 ){
      std::cout << ">> " << i_entry+1 << std::endl;
    }
    tree->GetEntry(i_entry);

    TVector3 vec_dcin_position((Double_t)dcin_position_x,(Double_t)dcin_position_y,(Double_t)dcin_position_z);
    TVector3 vec_dcin_momentum((Double_t)dcin_momentum_x,(Double_t)dcin_momentum_y,(Double_t)dcin_momentum_z);
    TVector3 vec_dcout_position((Double_t)dcout_position_x,(Double_t)dcout_position_y,(Double_t)dcout_position_z);
    TVector3 vec_dcout_momentum((Double_t)dcout_momentum_x,(Double_t)dcout_momentum_y,(Double_t)dcout_momentum_z);
    TVector3 vec_generate_momentum((Double_t)generate_momentum_x,(Double_t)generate_momentum_y,(Double_t)generate_momentum_z);
    TVector3 vec_generate_normal((Double_t)generate_normal_x,(Double_t)generate_normal_y,(Double_t)generate_normal_z);
    TVector3 vec_generate_reference((Double_t)generate_reference_x,(Double_t)generate_reference_y,(Double_t)generate_reference_z);

    bool is_dcin_fired = false;
    if(dcin_nhit){
      is_dcin_fired = true;
    }
    bool is_dcout_fired = false;
    if(dcout_nhit){
      is_dcout_fired = true;
    }

    // angles
    Double_t momentum_cos_theta_to_normal = vec_generate_momentum.Dot(vec_generate_normal) / vec_generate_momentum.Mag() / vec_generate_normal.Mag();
    
    ((TH1F*)output_file->Get("generate_momentum"))->Fill(vec_generate_momentum.Mag());
    ((TH1F*)output_file->Get("momentum_cos_theta_to_normal"))->Fill(momentum_cos_theta_to_normal);
  }
  // ------------------------------------------------------

  DrawHistograms();

  output_file->Write();
  output_file->Close();
}

void CreateHistograms(){
  output_file->cd();
  
  // 1D histograms
  new TH1F("generate_momentum","momentum (generate);#font[12]{p} (MeV/#font[12]{c});counts",200,0.,1.);
  new TH1F("momentum_cos_theta_to_normal","momentum (generate);#font[12]{p} (MeV/#font[12]{c});counts",200,-1.,1.);

}

void DrawHistograms(){
  TCanvas* canvas = new TCanvas("canvas","canvas",500,500);
  canvas->cd();

  // open pdf file
  canvas->Print(pdf_name + "[");

  TH1F* hist_1d = nullptr;
  TH2F* hist_2d = nullptr;

  // --------------
  gPad->SetLogy();
  // --------------

  // generate_momentum
  hist_1d = (TH1F*)output_file->Get("generate_momentum");
  Draw(hist_1d);
  canvas->Print(pdf_name);

  // momentum_cos_theta_to_normal
  hist_1d = (TH1F*)output_file->Get("momentum_cos_theta_to_normal");
  Draw(hist_1d);
  canvas->Print(pdf_name);

  // close pdf file
  canvas->Print(pdf_name + "]");
}
