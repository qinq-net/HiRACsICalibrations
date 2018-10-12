
//____________________________________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////
/// definition of Horn formula to fitting isotopes from Z=2 to Z=4
/// this formula is given in the following paper: D.Horn et al, NIM A320(1992) 273-276
double HornFit(double *x, double *par)
{
  // x[0]--E, x[1]--A
  if(x[1]==203 || x[1]==204 || x[1]==206 || x[1]==306 || x[1]==307 || x[1]==308 || x[1]==407 || x[1]==409)
  {
    int A = Int_t(x[1])%100;
    int Z = Int_t(x[1])/100;
    double consterm = par[2]*A*pow(Z,2);
    double lineterm = x[0]+consterm;
    double logterm = consterm*log(abs(lineterm/consterm));
    double light = par[0]+par[1]*(x[0]-logterm);
    return light;
  }
  return 0;
}

//______________________________________________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of 3He
double fit_He3(double *x, double *par)
{
  double consterm = par[2]*3*pow(2,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

//_____________________________________________________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of He4
double fit_He4(double *x, double *par)
{
  double consterm = par[2]*4*pow(2,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

//__________________________________________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of 6Li
double fit_Li6(double *x, double *par)
{
  double consterm = par[2]*6*pow(3,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

//________________________________________________________________________________________________________



void FitHorn()
{

//_______________________________________________________________________________________________________________________________
  ////////////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He3
  ////////////////////////////////////////////////////////////////////////////////////
  ifstream FileIn_He3;
  FileIn_He3.open("calibrations/DEEPoints_Z02_A03.dat");

  //////////////////////////////////////////////////////////////////////////////
  ////  definition of variables to read the data of He3
  std::vector<double> CsIV_He3[12][4];
  std::vector<double> errCsIV_He3[12][4];
  std::vector<double> CsIE_He3[12][4];
  std::vector<double> errCsIE_He3[12][4];

  if(!FileIn_He3.is_open())
  {
    printf("Error: file FileIn_He3 not found\n");
  }

  ////////////////////////////////////////////////////////////////
  //// loop to read the
  while(!FileIn_He3.eof())
  {
    std::string LineRead;
    std::getline(FileIn_He3, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int telnum;
    int csinum;
    double V;
    double errV;
    double E;
    double errE;

    LineStream >> telnum >> csinum >> V >> errV >> E >> errE;

    CsIV_He3[telnum][csinum].push_back(V);
    errCsIV_He3[telnum][csinum].push_back(errV);
    CsIE_He3[telnum][csinum].push_back(E);
    errCsIE_He3[telnum][csinum].push_back(errE);
  }



  ////////////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He4
  ////////////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He4=2;
  std::string * FileIn_name_He4[NFiles_He4];
  FileIn_name_He4[0] = new std::string("calibrations/DEEPoints_Z02_A04.dat"); //DEE points
  FileIn_name_He4[1] = new std::string("calibrations/WMUdata_Z02_A04.dat");

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe4[12][4][NFiles_He4];

  //////////////////////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He4[12][4][2];
  std::vector<double> errCsIV_He4[12][4][2];
  std::vector<double> CsIE_He4[12][4][2];
  std::vector<double> errCsIE_He4[12][4][2];

  /////////////////////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_He4; FileNum++)
  {
    ifstream FileIn_He4(FileIn_name_He4[FileNum]->c_str());
    if(!FileIn_He4.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_He4[FileNum]->c_str());
      return;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_He4.eof())
    {
      std::string LineRead;
      std::getline(FileIn_He4, LineRead);

      LineRead.assign(LineRead.substr(0, LineRead.find('*')));
      if(LineRead.empty()) continue;
      if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

      std::istringstream LineStream(LineRead);

      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> V >> errV >> E >> errE;

      CsIV_He4[telnum][csinum][FileNum].push_back(V);
      errCsIV_He4[telnum][csinum][FileNum].push_back(errV);
      CsIE_He4[telnum][csinum][FileNum].push_back(E);
      errCsIE_He4[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe4[i][j][FileNum] = new TGraphErrors(CsIV_He4[i][j][FileNum].size(), CsIE_He4[i][j][FileNum].data(), CsIV_He4[i][j][FileNum].data(), errCsIE_He4[i][j][FileNum].data() ,errCsIV_He4[i][j][FileNum].data());
        DataHe4[i][j][FileNum]->SetMarkerColor(6); // black marker for He4s
        DataHe4[i][j][FileNum]->SetLineColor(6);
        DataHe4[i][j][FileNum]->SetMarkerStyle(20+FileNum);
      }
    }
    FileIn_He4.close();
  }


//_______________________________________________________________________________________________________________________________
    ////////////////////////////////////////////////////////////////////////////////////
    ////   retriving data for He6
    ////////////////////////////////////////////////////////////////////////////////////
    ifstream FileIn_He6;
    FileIn_He6.open("calibrations/DEEPoints_Z02_A06.dat");

    //////////////////////////////////////////////////////////////////////////////
    ////  definition of variables to read the data of He6
    std::vector<double> CsIV_He6[12][4];
    std::vector<double> errCsIV_He6[12][4];
    std::vector<double> CsIE_He6[12][4];
    std::vector<double> errCsIE_He6[12][4];

    if(!FileIn_He6.is_open())
    {
      printf("Error: file FileIn_He6 not found\n");
    }

    ////////////////////////////////////////////////////////////////
    //// loop to read the
    while(!FileIn_He6.eof())
    {
      std::string LineRead;
      std::getline(FileIn_He6, LineRead);

      LineRead.assign(LineRead.substr(0, LineRead.find('*')));
      if(LineRead.empty()) continue;
      if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

      std::istringstream LineStream(LineRead);

      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> V >> errV >> E >> errE;

      CsIV_He6[telnum][csinum].push_back(V);
      errCsIV_He6[telnum][csinum].push_back(errV);
      CsIE_He6[telnum][csinum].push_back(E);
      errCsIE_He6[telnum][csinum].push_back(errE);
    }



//______________________________________________________________________________________________________________________________________________
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ////// creating a multigraph to draw all the Heavy calibrations
  TMultiGraph * multiHeavyIons[14][4];
  TGraphErrors * graph_He3[12][4];
  TGraphErrors * graph_He6[12][4];
  TGraphErrors * graph_Li6[12][4];
  TGraphErrors * graph_Li7[12][4];
  TGraphErrors * graph_Li8[12][4];
  TGraphErrors * graph_Be7[12][4];
  TGraphErrors * graph_Be9[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      multiHeavyIons[i][j] = new TMultiGraph();

      //////////////////////////////////////////////////////////////////////////////////
      /// add He3 data
      graph_He3[i][j] = new TGraphErrors(CsIV_He3[i][j].size(), CsIE_He3[i][j].data(), CsIV_He3[i][j].data(), errCsIE_He3[i][j].data(),errCsIV_He3[i][j].data());
      multiHeavyIons[i][j]->Add(graph_He3[i][j]);

      //////////////////////////////////////////////////////////////////////////////////////////
      ///// add He4 data
      for(FileNum=0; FileNum<NFiles_He4; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataHe4[i][j][FileNum]);
      }

      /////////////////////////////////////////////////////////////////////////////////////////
      /// add He6 data
      graph_He6[i][j] = new TGraphErrors(CsIV_He6[i][j].size(), CsIE_He6[i][j].data(), CsIV_He6[i][j].data(), errCsIE_He6[i][j].data(),errCsIV_He6[i][j].data());
      multiHeavyIons[i][j]->Add(graph_He6[i][j]);

    }
  }


//________________________________________________________________________________________________________________________________________________________________________
  /// Put all the dataset together
  std::vector<double> CsIV_HeavyIons[12][4];
  std::vector<double> errCsIV_HeavyIons[12][4];
  std::vector<double> CsIE_HeavyIons[12][4];
  std::vector<double> errCsIE_HeavyIons[12][4];
  std::vector<double> ZA_HeavyIons[12][4];
  std::vector<double> errZA_HeavyIons[12][4];


  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {

      /////////////////////////////////////////////////////////////////////////////
      ////   add He3 data
      for(int k=0; k< CsIV_He3[i][j].size(); k++)
      {
        CsIV_HeavyIons[i][j].push_back(CsIV_He3[i][j][k]);
        errCsIV_HeavyIons[i][j].push_back(errCsIV_He3[i][j][k]);
        CsIE_HeavyIons[i][j].push_back(CsIE_He3[i][j][k]);
        errCsIE_HeavyIons[i][j].push_back(errCsIE_He3[i][j][k]);
        ZA_HeavyIons[i][j].push_back(101);
        errZA_HeavyIons[i][j].push_back(0);

      }

      /////////////////////////////////////////////////////////////////////////////
      ////   add He4 data
      for(FileNum=0; FileNum<NFiles_He4; FileNum++)
      {
        for(int k=0; k< CsIV_He4[i][j][FileNum].size(); k++)
        {
          CsIV_HeavyIons[i][j].push_back(CsIV_He4[i][j][FileNum][k]);
          errCsIV_HeavyIons[i][j].push_back(errCsIV_He4[i][j][FileNum][k]);
          CsIE_HeavyIons[i][j].push_back(CsIE_He4[i][j][FileNum][k]);
          errCsIE_HeavyIons[i][j].push_back(errCsIE_He4[i][j][FileNum][k]);
          ZA_HeavyIons[i][j].push_back(102);
          errZA_HeavyIons[i][j].push_back(0);
        }
      }

      /////////////////////////////////////////////////////////////////////////////
      ////   add He6 data
      for(int k=0; k< CsIV_He6[i][j].size(); k++)
      {
        CsIV_HeavyIons[i][j].push_back(CsIV_He6[i][j][k]);
        errCsIV_HeavyIons[i][j].push_back(errCsIV_He6[i][j][k]);
        CsIE_HeavyIons[i][j].push_back(CsIE_He6[i][j][k]);
        errCsIE_HeavyIons[i][j].push_back(errCsIE_He6[i][j][k]);
        ZA_HeavyIons[i][j].push_back(103);
        errZA_HeavyIons[i][j].push_back(0);
      }
    }
  }


//________________________________________________________________________________________________________________________________________
 ///////////////////////////////////////////////////////////////////////////////////
 /////   Draw all the data set in the same 2D Graphs
 TGraph2DErrors * TotGraph[12][4];
 for(int i=0; i<12; i++)
 {
   for(int j=0; j<4; j++)
   {
     TotGraph[i][j] = new TGraph2DErrors(CsIV_HeavyIons[i][j].size(), CsIE_HeavyIons[i][j].data(), ZA_HeavyIons[i][j].data(), CsIV_HeavyIons[i][j].data(), errCsIE_HeavyIons[i][j].data(), errZA_HeavyIons[i][j].data(), errCsIV_HeavyIons[i][j].data());
     TotGraph[i][j]->SetName(Form("TEL%02d_CsI_%02d", i, j));
     TotGraph[i][j]->SetTitle(Form("HeavyIons_TEL%02d_CsI_%02d", i, j));
     TotGraph[i][j]->SetMarkerStyle(20);
   }
 }


//___________________________________________________________________________________________________________________________________________________
  /////////////////////////////////////////////////////////////////////////
  /////  Fit Heavy Ions Light(V)-Energy(MeV) with the Horn formula
  TF2 *fHeavyIon= new TF2("fHeavyIon",HornFit,0,400,200,300,3);
  fHeavyIon->SetParameters(0.02,2, 1);


//_________________________________________________________________________________________________________________________________________________
  ///// Draw
  TCanvas *c1 = new TCanvas("c1");
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      TotGraph[i][j]->Draw("P");
      TotGraph[i][j]->Fit("fHeavyIon");
      fHeavyIon->Draw("* SAME");

      gPad->Modified();
      gPad->Update();
      getchar();

    }
  }

}
