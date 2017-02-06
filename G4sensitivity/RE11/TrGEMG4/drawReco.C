
//Fit functions____________________________________________________________________________________________________

Double_t fitf(Double_t *v, Double_t *par){

	//Double_t aa1 = 0.3/(sqrt(6.28)*par[2]);
	Double_t aa2 = 0.0004/(sqrt(6.28)*par[5]);
	Double_t arg = 0;
	if (par[2] != 0) arg = (v[0] - par[1])/par[2];
	Double_t arg2 = 0;
	if (par[5] != 0) arg2 = (v[0] - par[4])/par[5];
	
	Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg)+par[3]*aa2*TMath::Exp(-0.5*arg2*arg2);
	//Double_t fitval =par[0]*((1-par[3])*aa1*TMath::Exp(-0.5*arg*arg)+par[3]*aa2*TMath::Exp(-0.5*arg2*arg2));

	return fitval;
}

Double_t fitf2(Double_t *v, Double_t *par){

	Double_t aa2 = 0.0004/(sqrt(6.28)*par[5]);
	Double_t arg2 = 0;
	if (par[5] != 0) arg2 = (v[0] - par[4])/par[5];

	Double_t fitval = par[0]+par[1]*v[0]+par[2]*v[0]*v[0]+par[3]*aa2*TMath::Exp(-0.5*arg2*arg2);

	return fitval;
}
//____________________________________________________________________________________________________________________

 void drawReco(Int_t runNumber,Int_t g3=0){ 
 
	Char_t filename[100];
	sprintf(filename,"../root/gDetReco-%d.root",runNumber);
	TFile *fname = TFile::Open(filename);
	gROOT->Reset();
	gROOT->ProcessLine(".L alistyle.C");
	setTDRStyle();
	TCanvas *reco;
//	TCanvas *clus;
	
/*	gStyle->SetOptStat("m");
 	clus = new TCanvas("clus", "Number of clusters",500,500);
	clus->SetGrid();  hNclus->GetXaxis()->SetNdivisions(-10); 
	hNclus->GetYaxis()->SetRangeUser(1e-3,2*1e2);
	hNclus->GetXaxis()->SetTitleOffset(1.2);      hNclus->GetYaxis()->SetTitleOffset(1.4);      hNclus->Draw();
  	clus->SaveAs("clusF50.png");
*/
 	reco = new TCanvas("reco", "Reconstruction",900,600);
  	reco->Divide(3,2);



	//  gStyle->SetOptStat(110); // To display the mean and RMS:   SetOptStat("mr");
 	gStyle->SetOptStat("e");
 	reco->cd(1); hNst->GetXaxis()->SetTitleOffset(1.2);      hNst->GetYaxis()->SetTitleOffset(1.4);      hNst->Draw();  
 	reco->cd(2); hETot->GetXaxis()->SetTitleOffset(1.2);     hETot->GetYaxis()->SetTitleOffset(1.4);     hETot->Draw();

	//  gStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
 	//reco->cd(3); hYc->Draw();
 	reco->cd(3); hasym->GetXaxis()->SetTitleOffset(1.2);     hasym->GetYaxis()->SetTitleOffset(1.4);     hasym->Draw();
 
	reco->cd(4); hE0suEtot->GetXaxis()->SetTitleOffset(1.2); hE0suEtot->GetYaxis()->SetTitleOffset(1.4); hE0suEtot->Draw();
 	reco->cd(5); hE1suE0->GetXaxis()->SetTitleOffset(1.2);   hE1suE0->GetYaxis()->SetTitleOffset(1.4);   hE1suE0->Draw();
 	reco->cd(6);  hDY->GetXaxis()->SetTitleOffset(1.2);   hDY->GetYaxis()->SetTitleOffset(1.4);hDY->Draw();
	
	hDY->SetTitleSize(0.05,"xy"); hDY->SetLabelSize(0.045,"xy");
	hETot->SetTitleSize(0.05,"xy"); hETot->SetLabelSize(0.045,"xy");
	hasym->SetTitleSize(0.05,"xy"); hasym->SetLabelSize(0.045,"xy");
	hE0suEtot->SetTitleSize(0.05,"xy"); hE0suEtot->SetLabelSize(0.045,"xy");
	hE1suE0->SetTitleSize(0.05,"xy"); hE1suE0->SetLabelSize(0.045,"xy");
	hNst->SetTitleSize(0.05,"xy"); hNst->SetLabelSize(0.045,"xy");

	hNst->GetXaxis()->SetNdivisions(-504);
	hDY->GetXaxis()->SetNdivisions(-504);
	hNst->SetStats(0); 
	hasym->SetStats(0); 
	hE0suEtot->SetStats(0); 
	hE1suE0->SetStats(0); 
	hDY->SetStats(1); 

	gROOT->Reset();
        TF1 *fun3=new TF1("fun3",fitf2,-0.01,0.01,6);
        fun3->SetLineColor(kRed);

	
//	fun3->SetParameter(0,100.);
//	fun3->SetParameter(1,0.);
//	fun3->SetParameter(2,0.3);

	fun3->SetParameter(3,700.);
	fun3->FixParameter(4,0.);		
	fun3->FixParameter(5,0.0007);
        

        hDY->Fit(fun3,"rvm");
	fun3->ReleaseParameter(4);
	fun3->ReleaseParameter(5);
	hDY->Fit(fun3,"rvm");
	fun3->Draw("same");
 	Int_t integ= hDY->Integral(37,63);
 	Double_t max= hDY->GetMaximum();
 	Double_t max1= max-0.2 *max;
 	Double_t max2= max1-0.2 *max;
 	Double_t max3= max2-0.2 *max;
 	Double_t max4= max3-0.2 *max;

  	char aa[100];
  	char bb[100];
  	char cc[100];
  	char dd[100];
	sprintf(aa,"#mu = %5.2f  #pm %5.2f [#mum]",fun3->GetParameter(4)*10000.,fun3->GetParError(4)*10000.);
	sprintf(bb,"#sigma = %5.2f #pm %5.2f [#mum]",fun3->GetParameter(5)*10000.,fun3->GetParError(5)*10000.);
	sprintf(cc,"Yield = %10.2f #pm %5.2f ev",fun3->GetParameter(3),fun3->GetParError(3));
	sprintf(dd,"Integral = %d ",integ);
  	TLatex *t;  t = new TLatex();
  	t->SetTextSize(0.06);
  	t->DrawLatex(-0.015,max1,aa);
  	t->DrawLatex(-0.015,max2,bb);
 	t->DrawLatex(-0.015,max3,cc);
  	t->DrawLatex(-0.015,max4,dd);


 	reco->SaveAs("reco_2050_DC_02.png"); 
//	reco->SaveAs("reco_2050_D_GerCut.eps"); 

}
