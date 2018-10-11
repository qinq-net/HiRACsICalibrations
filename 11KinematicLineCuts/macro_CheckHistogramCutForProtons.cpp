
void macro_CheckHistogramCutForProtons()
{

  TFile FileIn("output/HiRA_KinematicPlotsCut_4332_4332_48Ca+1H@56AMeV.root");
  
  TCanvas *c1=new TCanvas("c1","",1200,800);
  c1->SetLogz(1);
  
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      TH2D * HiRA_KinematicPlots = (TH2D*)FileIn.Get(Form("histKinematicPlots_%02d_%02d",i,j));
      if(HiRA_KinematicPlots==0) continue;
      HiRA_KinematicPlots->Draw("colz");
    
    
      TCutG * CutProtons = (TCutG*)FileIn.Get(Form("histKinematicPlots_%02d_%02d_Z%02d_A%02d",i,j,1,1));
      CutProtons->SetLineColor(kRed);
      CutProtons->SetLineWidth(2);
      CutProtons->SetMarkerColor(kRed);
      CutProtons->Draw("SAME L*"); 
  
      gPad->Modified();
      gPad->Update();  
      getchar();
    }
  }
}
