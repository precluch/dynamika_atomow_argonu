void wyk(const TString par, const TString hvt){
	TString name, tit,
	cnv_nameH="H(t) z symulacji ",
	cnv_nameV="V(t) z symulacji ",
	cnv_nameT="T(t) z symulacji ",
	cnv_nameP="P(t) z symulacji ",
	Hn=par+"_H(t).gif",
	Vn=par+"_V(t).gif",
	Tn=par+"_T(t).gif",
	Pn=par+"_P(t).gif";
	
	ifstream file_par, file_hvt;
	
	file_par.open(par.Data());
	int n, N, e, f, T0, So, Sd, Sout, Sxyz;
	double m0, L, RR, a, tau;
	file_par >> n;	file_par >> N;	file_par >> m0;	file_par >> e;	file_par >> L;	file_par >> f;	file_par >> RR;
	file_par >> a;	file_par >> T0;	file_par >> tau;	file_par >> So;	file_par >> Sd;	file_par >> Sout;	file_par >> Sxyz;
	file_par.close();
	
	file_hvt.open(hvt.Data());

	double t[100000]=.0, H[100000]=.0, V[100000]=.0, T[100000]=.0, P[100000]=.0;
	int j=0;
	
	while(
	file_hvt >> t[j] &&
	file_hvt >> H[j] &&
	file_hvt >> V[j] &&
	file_hvt >> T[j] &&
	file_hvt >> P[j]) j++;

	file_hvt.close();

	cnv_nameH+=par;
	cnv_nameV+=par;
	cnv_nameT+=par;
	cnv_nameP+=par;
	
	TCanvas *cnvH = new TCanvas("cnvH", cnv_nameH, 1200, 600);
	grH = new TGraph(j, t, H);
	double dd = abs(grH->GetHistogram()->GetMinimum()-grH->GetHistogram()->GetMaximum())/2;
	grH->SetTitle("H(t)");
	grH->SetMarkerColor(0);
	grH->SetLineColor(9);
	grH->GetXaxis()->SetTitle("t");
	grH->GetYaxis()->SetTitle("H(t)");
	grH->GetHistogram()->SetMinimum(grH->GetHistogram()->GetMinimum()-.2*dd);
	grH->GetHistogram()->SetMaximum(grH->GetHistogram()->GetMaximum()+.2*dd);
	grH->Draw("AL");
	cnvH->SaveAs(Hn.Data());
	cnvH->SetEditable(0);

	TCanvas *cnvV = new TCanvas("cnvV", cnv_nameV, 1200, 600);
	grV = new TGraph(j, t, V);
	grV->SetTitle("V(t)");
	grV->SetMarkerColor(0);
	grV->SetLineColor(9);
	grV->GetXaxis()->SetTitle("t");
	grV->GetYaxis()->SetTitle("H(t)");
	grV->Draw("AL");
	cnvV->SaveAs(Vn.Data());
	cnvV->SetEditable(0);

	TCanvas *cnvT = new TCanvas("cnvT", cnv_nameT, 1200, 600);
	grT = new TGraph(j, t, T);
	grT->SetTitle("T(t)");
	grT->SetMarkerColor(0);
	grT->SetLineColor(9);
	grT->GetXaxis()->SetTitle("t");
	grT->GetYaxis()->SetTitle("H(t)");
	grT->GetHistogram()->SetMinimum(.0);
	grT->Draw("AL");
	cnvT->SaveAs(Tn.Data());
	cnvT->SetEditable(0);

	TCanvas *cnvP = new TCanvas("cnvP", cnv_nameP, 1200, 600);
	grP = new TGraph(j, t, P);
	grP->SetTitle("P(t)");
	grP->SetMarkerColor(0);
	grP->SetLineColor(9);
	grP->GetXaxis()->SetTitle("t");
	grP->GetYaxis()->SetTitle("H(t)");
	grP->GetHistogram()->SetMinimum(grP->GetHistogram()->GetMaximum()*(-0.1));
	grP->Draw("AL");
	cnvP->SaveAs(Pn.Data());
	cnvP->SetEditable(0);
}
