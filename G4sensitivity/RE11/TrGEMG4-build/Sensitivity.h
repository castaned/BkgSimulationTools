//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 13 14:50:50 2014 by ROOT version 5.34/08
// from TTree MyRun/Run with awesome data
// found on file: Task1.root
//////////////////////////////////////////////////////////

#ifndef Sensitivity_h
#define Sensitivity_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <fstream>

// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class Sensitivity {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           elexevt;
   Int_t           posxevt;
   Int_t           gammaxevt;
   Int_t           secoxevt;
   Double_t        driftEdep[9];
   Double_t        driftEdepI[9];
   Double_t        transferEdep[9];
   Double_t        transferEdepI[9];
   Double_t        transfer2Edep[9];
   Double_t        transfer2EdepI[9];
   Double_t        inductionEdep[9];
   Double_t        inductionEdepI[9];
   Double_t        driftEdep_B[9];
   Double_t        driftEdepI_B[9];
   Double_t        transferEdep_B[9];
   Double_t        transferEdepI_B[9];
   Double_t        transfer2Edep_B[9];
   Double_t        transfer2EdepI_B[9];
   Double_t        inductionEdep_B[9];
   Double_t        inductionEdepI_B[9];
   Bool_t          neutronSensitivity;
   Bool_t          eleGap;
   Bool_t          eleGap_B;
   Bool_t          chargeGap;
   Bool_t          chargeGap_B;
   Double_t        primaryEne;
   vector<int>     *gapTrackPart;
   vector<string>  *gapTrackGenProcess;
   vector<string>  *gapTrackVolume;
   vector<double>  *gapTrackGenZ;
   vector<string>  *gapTrackGap;
   vector<double>  *gapTrackEne;
   vector<int>     *postTrackPart;
   vector<double>  *postTrackEne;

   // List of branches
   TBranch        *b_elexevt;   //!
   TBranch        *b_posxevt;   //!
   TBranch        *b_gammaxevt;   //!
   TBranch        *b_secoxevt;   //!
   TBranch        *b_driftEdep;   //!
   TBranch        *b_driftEdepI;   //!
   TBranch        *b_transferEdep;   //!
   TBranch        *b_transferEdepI;   //!
   TBranch        *b_transfer2Edep;   //!
   TBranch        *b_transfer2EdepI;   //!
   TBranch        *b_inductionEdep;   //!
   TBranch        *b_inductionEdepI;   //!
   TBranch        *b_driftEdep_B;   //!
   TBranch        *b_driftEdepI_B;   //!
   TBranch        *b_transferEdep_B;   //!
   TBranch        *b_transferEdepI_B;   //!
   TBranch        *b_transfer2Edep_B;   //!
   TBranch        *b_transfer2EdepI_B;   //!
   TBranch        *b_inductionEdep_B;   //!
   TBranch        *b_inductionEdepI_B;   //!
   TBranch        *b_neutronSensitivity;   //!
   TBranch        *b_eleGap;   //!
   TBranch        *b_eleGap_B;   //!
   TBranch        *b_chargeGap;   //!
   TBranch        *b_chargeGap_B;   //!
   TBranch        *b_primaryEne;   //!
   TBranch        *b_gapTrackPart;   //!
   TBranch        *b_gapTrackGenProcess;   //!
   TBranch        *b_gapTrackVolume;   //!
   TBranch        *b_gapTrackGenZ;   //!
   TBranch        *b_gapTrackGap;   //!
   TBranch        *b_gapTrackEne;   //!
   TBranch        *b_postTrackPart;   //!
   TBranch        *b_postTrackEne;   //!

 
  Sensitivity(TTree *tree=0);
   virtual ~Sensitivity();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Sensitivity_cxx
Sensitivity::Sensitivity(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Task1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("task3.root");
      }
      f->GetObject("MyRun",tree);

   }
   Init(tree);
   
}

Sensitivity::~Sensitivity()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Sensitivity::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Sensitivity::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Sensitivity::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   // Set object pointer
   gapTrackPart = 0;
   gapTrackGenProcess = 0;
   gapTrackVolume = 0;
   gapTrackGenZ = 0;
   gapTrackGap = 0;
   gapTrackEne = 0;
   postTrackPart = 0;
   postTrackEne = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("elexevt", &elexevt, &b_elexevt);
   fChain->SetBranchAddress("posxevt", &posxevt, &b_posxevt);
   fChain->SetBranchAddress("gammaxevt", &gammaxevt, &b_gammaxevt);
   fChain->SetBranchAddress("secoxevt", &secoxevt, &b_secoxevt);
   fChain->SetBranchAddress("driftEdep", driftEdep, &b_driftEdep);
   fChain->SetBranchAddress("driftEdepI", driftEdepI, &b_driftEdepI);
   fChain->SetBranchAddress("transferEdep", transferEdep, &b_transferEdep);
   fChain->SetBranchAddress("transferEdepI", transferEdepI, &b_transferEdepI);
   fChain->SetBranchAddress("transfer2Edep", transfer2Edep, &b_transfer2Edep);
   fChain->SetBranchAddress("transfer2EdepI", transfer2EdepI, &b_transfer2EdepI);
   fChain->SetBranchAddress("inductionEdep", inductionEdep, &b_inductionEdep);
   fChain->SetBranchAddress("inductionEdepI", inductionEdepI, &b_inductionEdepI);
   fChain->SetBranchAddress("driftEdep_B", driftEdep_B, &b_driftEdep_B);
   fChain->SetBranchAddress("driftEdepI_B", driftEdepI_B, &b_driftEdepI_B);
   fChain->SetBranchAddress("transferEdep_B", transferEdep_B, &b_transferEdep_B);
   fChain->SetBranchAddress("transferEdepI_B", transferEdepI_B, &b_transferEdepI_B);
   fChain->SetBranchAddress("transfer2Edep_B", transfer2Edep_B, &b_transfer2Edep_B);
   fChain->SetBranchAddress("transfer2EdepI_B", transfer2EdepI_B, &b_transfer2EdepI_B);
   fChain->SetBranchAddress("inductionEdep_B", inductionEdep_B, &b_inductionEdep_B);
   fChain->SetBranchAddress("inductionEdepI_B", inductionEdepI_B, &b_inductionEdepI_B);
   fChain->SetBranchAddress("neutronSensitivity", &neutronSensitivity, &b_neutronSensitivity);
   fChain->SetBranchAddress("eleGap", &eleGap, &b_eleGap);
   fChain->SetBranchAddress("eleGap_B", &eleGap_B, &b_eleGap_B);
   fChain->SetBranchAddress("chargeGap", &chargeGap, &b_chargeGap);
   fChain->SetBranchAddress("chargeGap_B", &chargeGap_B, &b_chargeGap_B);
   fChain->SetBranchAddress("primaryEne", &primaryEne, &b_primaryEne);
   fChain->SetBranchAddress("gapTrackPart", &gapTrackPart, &b_gapTrackPart);
   fChain->SetBranchAddress("gapTrackGenProcess", &gapTrackGenProcess, &b_gapTrackGenProcess);
   fChain->SetBranchAddress("gapTrackVolume", &gapTrackVolume, &b_gapTrackVolume);
   fChain->SetBranchAddress("gapTrackGenZ", &gapTrackGenZ, &b_gapTrackGenZ);
   fChain->SetBranchAddress("gapTrackGap", &gapTrackGap, &b_gapTrackGap);
   fChain->SetBranchAddress("gapTrackEne", &gapTrackEne, &b_gapTrackEne);
   fChain->SetBranchAddress("postTrackPart", &postTrackPart, &b_postTrackPart);
   fChain->SetBranchAddress("postTrackEne", &postTrackEne, &b_postTrackEne);
   Notify();

}

Bool_t Sensitivity::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Sensitivity::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Sensitivity::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Sensitivity_cxx
