//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
/// definition of Horn formula to fitting isotopes from Z=2 to Z=4
/// this formula is given in the following paper:
//// D.Horn et al, NIM A320(1992) 273-276
////////////////////////////////////////////////////////////////////////////////
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
//______________________________________________________________________________
//______________________________________________________________________________
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
//______________________________________________________________________________
//______________________________________________________________________________
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
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of He6
double fit_He6(double *x, double *par)
{
  double consterm = par[2]*6*pow(2,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________



//------------------------------------------------------------------------------
void FitHornHes()
{
/*
  ofstream FileOut;
  FileOut.open("../calibrations/SimultaneouslyFitParHeavyIons.dat");
  FileOut << setw(5) <<"*tel" <<"  "<< setw(5) << "csi" <<"  "<<setw(5)<< "Z" <<"  "<<setw(5)<< "A" <<"  "<< setw(35) <<"Horn's Formula"
              <<"  "<<setw(45) << "Par0" <<"  "<< setw(10) <<"Par1"<<"  "<<setw(10)<<"Par2\n";
*/
  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He3
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He3=1;
  std::string * FileIn_name_He3[NFiles_He3];
  FileIn_name_He3[0] = new std::string("../calibrations/DEEPoints_Z02_A03.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe3[12][4][NFiles_He3];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He3[12][4][1];
  std::vector<double> errCsIV_He3[12][4][1];
  std::vector<double> CsIE_He3[12][4][1];
  std::vector<double> errCsIE_He3[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_He3; FileNum++)
  {
    ifstream FileIn_He3(FileIn_name_He3[FileNum]->c_str());
    if(!FileIn_He3.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_He3[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
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

      CsIV_He3[telnum][csinum][FileNum].push_back(V);
      errCsIV_He3[telnum][csinum][FileNum].push_back(errV);
      CsIE_He3[telnum][csinum][FileNum].push_back(E);
      errCsIE_He3[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe3[i][j][FileNum] = new TGraphErrors(CsIV_He3[i][j][FileNum].size(), CsIE_He3[i][j][FileNum].data(), CsIV_He3[i][j][FileNum].data(), errCsIE_He3[i][j][FileNum].data() ,errCsIV_He3[i][j][FileNum].data());
        DataHe3[i][j][FileNum]->SetMarkerColor(1); // black marker for He3s
        DataHe3[i][j][FileNum]->SetLineColor(1);
        DataHe3[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_He3.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He4
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He4=2;
  std::string * FileIn_name_He4[NFiles_He4];
  FileIn_name_He4[0] = new std::string("../calibrations/DEEPoints_Z02_A04.dat"); //DEE points
  FileIn_name_He4[1] = new std::string("../calibrations/WMUdata_Z02_A04.dat");

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe4[12][4][NFiles_He4];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He4[12][4][2];
  std::vector<double> errCsIV_He4[12][4][2];
  std::vector<double> CsIE_He4[12][4][2];
  std::vector<double> errCsIE_He4[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_He4; FileNum++)
  {
    ifstream FileIn_He4(FileIn_name_He4[FileNum]->c_str());
    if(!FileIn_He4.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_He4[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
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
        DataHe4[i][j][FileNum]->SetMarkerColor(2); // black marker for He4s
        DataHe4[i][j][FileNum]->SetLineColor(2);
        DataHe4[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_He4.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He6
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He6=1;
  std::string * FileIn_name_He6[NFiles_He6];
  FileIn_name_He6[0] = new std::string("../calibrations/DEEPoints_Z02_A06.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe6[12][4][NFiles_He6];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He6[12][4][1];
  std::vector<double> errCsIV_He6[12][4][1];
  std::vector<double> CsIE_He6[12][4][1];
  std::vector<double> errCsIE_He6[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_He6; FileNum++)
  {
    ifstream FileIn_He6(FileIn_name_He6[FileNum]->c_str());
    if(!FileIn_He6.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_He6[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
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

      CsIV_He6[telnum][csinum][FileNum].push_back(V);
      errCsIV_He6[telnum][csinum][FileNum].push_back(errV);
      CsIE_He6[telnum][csinum][FileNum].push_back(E);
      errCsIE_He6[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe6[i][j][FileNum] = new TGraphErrors(CsIV_He6[i][j][FileNum].size(), CsIE_He6[i][j][FileNum].data(), CsIV_He6[i][j][FileNum].data(), errCsIE_He6[i][j][FileNum].data() ,errCsIV_He6[i][j][FileNum].data());
        DataHe6[i][j][FileNum]->SetMarkerColor(3); // black marker for He6s
        DataHe6[i][j][FileNum]->SetLineColor(3);
        DataHe6[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_He6.close();
  }
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  ////// creating a multigraph to draw all the Heavy ../calibrations
  TMultiGraph * multiHeavyIons[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      multiHeavyIons[i][j] = new TMultiGraph();
      //////////////////////////////////////////////////////////////////////////
      ///// add He3 data
      for(int FileNum=0; FileNum<NFiles_He3; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataHe3[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add He4 data
      for(int FileNum=0; FileNum<NFiles_He4; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataHe4[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add He6 data
      for(int FileNum=0; FileNum<NFiles_He6; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataHe6[i][j][FileNum]);
      }
    }
  }
//______________________________________________________________________________


//______________________________________________________________________________
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
      //////////////////////////////////////////////////////////////////////////
      ////   add He3 data
      for(int FileNum=0; FileNum<NFiles_He3; FileNum++)
      {
        for(int k=0; k< CsIV_He3[i][j][FileNum].size(); k++)
        {
          CsIV_HeavyIons[i][j].push_back(CsIV_He3[i][j][FileNum][k]);
          errCsIV_HeavyIons[i][j].push_back(errCsIV_He3[i][j][FileNum][k]);
          CsIE_HeavyIons[i][j].push_back(CsIE_He3[i][j][FileNum][k]);
          errCsIE_HeavyIons[i][j].push_back(errCsIE_He3[i][j][FileNum][k]);
          ZA_HeavyIons[i][j].push_back(203);
          errZA_HeavyIons[i][j].push_back(0);
        }
      }

      //////////////////////////////////////////////////////////////////////////
      ////   add He4 data
      for(int FileNum=0; FileNum<NFiles_He4; FileNum++)
      {
        for(int k=0; k< CsIV_He4[i][j][FileNum].size(); k++)
        {
          CsIV_HeavyIons[i][j].push_back(CsIV_He4[i][j][FileNum][k]);
          errCsIV_HeavyIons[i][j].push_back(errCsIV_He4[i][j][FileNum][k]);
          CsIE_HeavyIons[i][j].push_back(CsIE_He4[i][j][FileNum][k]);
          errCsIE_HeavyIons[i][j].push_back(errCsIE_He4[i][j][FileNum][k]);
          ZA_HeavyIons[i][j].push_back(204);
          errZA_HeavyIons[i][j].push_back(0);
        }
       }

       /////////////////////////////////////////////////////////////////////////
       ////   add He6 data
       for(int FileNum=0; FileNum<NFiles_He6; FileNum++)
       {
         for(int k=0; k< CsIV_He6[i][j][FileNum].size(); k++)
         {
           CsIV_HeavyIons[i][j].push_back(CsIV_He6[i][j][FileNum][k]);
           errCsIV_HeavyIons[i][j].push_back(errCsIV_He6[i][j][FileNum][k]);
           CsIE_HeavyIons[i][j].push_back(CsIE_He6[i][j][FileNum][k]);
           errCsIE_HeavyIons[i][j].push_back(errCsIE_He6[i][j][FileNum][k]);
           ZA_HeavyIons[i][j].push_back(206);
           errZA_HeavyIons[i][j].push_back(0);
         }
       }
    }
  }
//______________________________________________________________________________


//______________________________________________________________________________
 ///////////////////////////////////////////////////////////////////////////////
 /////   Draw all the data set in the same 2D Graphs
 TGraph2DErrors * TotGraph[12][4];
 for(int i=0; i<12; i++)
 {
   for(int j=0; j<4; j++)
   {
     if(CsIV_HeavyIons[i][j].size()==0) continue;
     TotGraph[i][j] = new TGraph2DErrors(CsIV_HeavyIons[i][j].size(), CsIE_HeavyIons[i][j].data(), ZA_HeavyIons[i][j].data(), CsIV_HeavyIons[i][j].data(), errCsIE_HeavyIons[i][j].data(), 0, errCsIV_HeavyIons[i][j].data());
     TotGraph[i][j]->SetName(Form("TEL%02d_CsI_%02d", i, j));
     TotGraph[i][j]->SetTitle(Form("HeavyIons_TEL%02d_CsI_%02d", i, j));
     TotGraph[i][j]->SetMarkerStyle(20);
   }
 }
//______________________________________________________________________________


//______________________________________________________________________________
  /////////////////////////////////////////////////////////////////////////
  /////  Fit Heavy Ions Light(V)-Energy(MeV) with the Horn formula
  TF2 *fHeavyIon= new TF2("fHeavyIon",HornFit,0,500,200,500,3);
  fHeavyIon->SetParameters(0.01,0.01,0.1);

  TF1 * fHe3 = new TF1("fHe3",fit_He3,0,500,3);
  TF1 * fHe4 = new TF1("fHe4",fit_He4,0,500,3);
  TF1 * fHe6 = new TF1("fHe6",fit_He6,0,500,3);

  fHe3->SetLineColor(1);
  fHe4->SetLineColor(2);
  fHe6->SetLineColor(3);
//______________________________________________________________________________


//______________________________________________________________________________
  ///// Draw
  TCanvas *c1 = new TCanvas("c1","",1200,800);
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      if(CsIV_HeavyIons[i][j].size()==0) continue;

      TotGraph[i][j]->Fit("fHeavyIon");

      fHe3->SetParameters(fHeavyIon->GetParameters());
      fHe4->SetParameters(fHeavyIon->GetParameters());
      fHe6->SetParameters(fHeavyIon->GetParameters());

      multiHeavyIons[i][j]->Draw("AP");
      fHe3->Draw("SAME");
      fHe4->Draw("SAME");
      fHe6->Draw("SAME");

      gPad->Modified();
      gPad->Update();
      getchar();
/*
      //////////////////////////////////////////////////////////////////////////
      /// retrive the fit parameters
      double par0 = fHeavyIon->GetParameter(0);
      double par1 = fHeavyIon->GetParameter(1);
      double par2 = fHeavyIon->GetParameter(2);
      int Z;
      int A;
      for(int k=0; k<ZA_HeavyIons[i][j].size();k++)
      {
        Z = (int) ZA_HeavyIons[i][j][k]/100;
        A = (int) ZA_HeavyIons[i][j][k]%100;
        if(ZA_HeavyIons[i][j][k]==ZA_HeavyIons[i][j][k+1]) continue;
        FileOut << setw(5) << i <<"  "<< setw(5) << j <<"  "<<setw(5)<< Z <<"  "<<setw(5)<< A <<"  "<< setw(35)<< "[0]+[1].(x-[2].A.pow(Z,2).log(fabs((x+[2].A.pow(Z,2))/([2].A.pow(Z,2))))" <<"  "<<setw(15) << par0 <<"  "<< setw(10) << par1 <<"  "<<setw(10)<< par2 <<endl;
      }
*/
    }
  }
//______________________________________________________________________________

}
