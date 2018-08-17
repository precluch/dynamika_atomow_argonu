void V(){
	ifstream v;
	v.open("V(a)");

	TCanvas *cnv = new TCanvas("cnv", "V(a)", 1200, 600);

	double a[1000]=.0, V[1000]=.0;
	int j=0;
	
	while(
	v >> a[j] &&
	v >> V[j]) j++;

	gr = new TGraph(j, a, V);
	gr->SetTitle("V(a)");
	gr->SetMarkerColor(0);
	gr->SetLineColor(9);
	gr->GetXaxis()->SetTitle("a");
	gr->GetYaxis()->SetTitle("V(a)");
	gr->Draw("AC");
	cnv->SaveAs("V(a).gif");
	cnv->SetEditable(0);
}


