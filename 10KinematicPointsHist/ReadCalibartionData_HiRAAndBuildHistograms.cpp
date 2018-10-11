void ReadCalibartionData_HiRAAndBuildHistograms()
{
  const int FirstRun=4577;
  const int LastRun  =4584;
  const int E_projectile=28; //MeV
  const int Z_beam=20; 
  const int A_beam=48; 
  double RadToDeg=180./TMath::Pi();
  //--------------------------------------
 
 // To create a TChain with the content I want to read
  TChain myData("E15190");

 // I add a file (or some files) to the TChain
  for (int i=FirstRun; i<LastRun+1; i++)
  {
  myData.Add(Form("input/CalibratedData_HiRA_%04d.root",i));
  }
  
 // I declare here a File to e used as output  
  TFile FileOut(Form("output/HiRA_KinematicPlots_%4d_%4d_%2dCa+1H@%2dAMeV.root",FirstRun,LastRun,A_beam,E_projectile),"RECREATE");
  
 // 2-D histograms to be filled
  TH2D *histKinematicPlots[12][4];
  for(int i=0; i<12; i++){
    for(int j=0; j<4; j++)
    {
     histKinematicPlots[i][j]=new TH2D(Form("histKinematicPlots_%02d_%02d",i,j),Form("histKinematicPlots_%02d_%02d",i,j),500,25,80,500,0,1000);
    }
  }

 // I declare all the varibles that I use to read the tree
 // The content of the root tree that I will read will be stored in these variables
  int HiRA_fmulti;
  int HiRA_fnumtel[50];
  int HiRA_fnumcsi[50];
  UShort_t HiRA_fEnergycsi[50];
  double HiRA_fTheta[50];
  int HiRA_fZ[50];
  int HiRA_fA[50];
  
  
 // I set the branch address to the branches I need to reend 
  myData.SetMakeClass(1);
  myData.SetBranchAddress("HiRA.fmulti",&HiRA_fmulti);
  myData.SetBranchAddress("HiRA.fnumtel",HiRA_fnumtel); // for array, don't add "&"
  myData.SetBranchAddress("HiRA.fnumcsi",HiRA_fnumcsi);
  myData.SetBranchAddress("HiRA.fEnergycsi",HiRA_fEnergycsi);
  myData.SetBranchAddress("HiRA.fTheta",HiRA_fTheta);
  myData.SetBranchAddress("HiRA.fEnergycsi",HiRA_fEnergycsi);
  myData.SetBranchAddress("HiRA.fTheta",HiRA_fTheta);
  myData.SetBranchAddress("HiRA.fZ",HiRA_fZ);
  myData.SetBranchAddress("HiRA.fA",HiRA_fA);

 // I disable all the branches 
  myData.SetBranchStatus("*",false);
 
 // I enable only the branches I need
  myData.SetBranchStatus("HiRA.fmulti",true);
  myData.SetBranchStatus("HiRA.fnumtel",true);
  myData.SetBranchStatus("HiRA.fnumcsi",true);
  myData.SetBranchStatus("HiRA.fEnergycsi",true);
  myData.SetBranchStatus("HiRA.fTheta",true);
  myData.SetBranchStatus("HiRA.fZ",true);
  myData.SetBranchStatus("HiRA.fA",true);
  
 // number of enetries in the TChain 
  unsigned long nentries = myData.GetEntries();
  cout<< "Found" << nentries <<"entries\n";
 
// Loop on the data to fill my histograms. (Loop by entries)   
  for(unsigned long j=0; j<nentries; j++) 
  {
    myData.GetEntry(j);
    
    for (int i=0; i<HiRA_fmulti; i++)
    {       
       if(HiRA_fZ[i]==1 && HiRA_fA[i]==1) 
       {
         histKinematicPlots[HiRA_fnumtel[i]][HiRA_fnumcsi[i]]->Fill(HiRA_fTheta[i]*RadToDeg,HiRA_fEnergycsi[i]);  
       }
       else continue;
    }
 	
  }
  
 // TCanvas *c1=new TCanvas("c1","",1200,800);
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
     // histKinematicPlots[i][j]->SetTille();
      FileOut.WriteTObject(histKinematicPlots[i][j],histKinematicPlots[i][j]->GetName());
      
   //   histKinematicPlots[i][j]->Draw("cloz");
   //   gPad->Update();
   //   gPad->Modified();
   //   getchar();
    }
  }
  FileOut.Close();

  
}
  
  
  
 	
 	
