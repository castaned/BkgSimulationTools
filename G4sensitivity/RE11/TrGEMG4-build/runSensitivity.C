void runSensitivity()
{
gROOT->ProcessLine(".L Sensitivity.C");
TFile *f = TFile::Open("task3.root");
TTree *t4 = (TTree*)f->Get("MyRun");
Sensitivity *t = new Sensitivity(t4);
t->Loop();

f->Close();

}
