//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// definition of the fitting formula for proton, deuteron and triton
//// this formula comes from Jerzy Lukasik
//// email: jerzy.lukasik@ifj.edu.pl
////////////////////////////////////////////////////////////////////////////////
double FitJerzy(double *x, double *par)
{
  if(par[1]<=par[2])
  {
    return -1;
  }
  //A=par[3], Z=par[4]
  double squareterm = pow(x[0], 2)+par[1]*par[3]*x[0];
  double linearterm = (x[0]+par[2]*par[3]);
  double light = par[0]*squareterm/linearterm;
  return light;
}
//______________________________________________________________________________


//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
/// definition of Horn formula to fitting isotopes from Z=2 to Z=4
/// this formula is given in the following paper:
//// D.Horn et al, NIM A320(1992) 273-276
////////////////////////////////////////////////////////////////////////////////
double HornFit(double *x, int A, int Z, double *par)
{
  double consterm = par[2]*A*pow(Z,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(abs(lineterm/consterm));
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

//______________________________________________________________________________


//______________________________________________________________________________

void PDT_EstimateErrOfSimultaneouslyFit()
{

   ofstream FileOut;
   FileOut.open("PDT_ErrofDataPointsToFitLine.dat");
<<<<<<< HEAD:70EstimateErrorOfSimultaneouslyFit/PDT_EstimateErrOfSimultaneouslyFit.cpp
   FileOut<< setw(5) << "*tel" <<"  "<< setw(5) << "csi" <<"  "<< setw(5) << "Z" <<"  "<< setw(5) << "A" <<"  "<< setw(10) << "CsIE(MeV)" <<"  "<< setw(10) << "CsIV-VCal"
         <<"  "<< setw(10) << "CsIV" <<"  "<< setw(10) <<"VCal\n";
=======
   FileOut<< setw(5) << "*tel" <<"  "<< setw(5) << "csi" <<"  "<< setw(5) << "Z" <<"  "<< setw(5) << "A" <<"  "<< setw(10) << "CsIE(MeV)" <<"  "<< setw(10) << "CsIV-VCal\n";
>>>>>>> b45927e7ec2f6dd3e7139c40c981c09aeeb8265e:70EstimateErrorOfSimultaneouslyFit/EstimateErrOfSimultaneouslyFit.cpp


  //============================================================================
  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for protons
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Proton=11;
  std::string * FileIn_name_Proton[NFiles_Proton];
  FileIn_name_Proton[0] = new std::string("../calibrations/WMUdata_Z01_A01.dat");   // WMU data
  FileIn_name_Proton[1] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A01.dat"); //DEE points
  FileIn_name_Proton[2] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_2013_2037_40Ca39.0AMeV_gain 200.dat"); // kinematics ponits
  FileIn_name_Proton[3] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_2312_2312_40Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  //FileIn_name_Proton[4] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_2825_2829_40Ca139.8AMeV_gain 130.dat"); // kinematics ponits
  FileIn_name_Proton[4] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4000_4005_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[5] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4021_4022_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[6] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4034_4037_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[7] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4332_4332_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[8] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4577_4584_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[9] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4585_4589_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[10] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A01.dat");  // punch through points


  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Proton[12][4][12];
  std::vector<double> CsIE_Proton[12][4][12];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
  {
    ifstream FileIn_Proton(FileIn_name_Proton[FileNum]->c_str());
    if(!FileIn_Proton.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Proton[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Proton.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Proton, LineRead);

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

      CsIV_Proton[telnum][csinum][FileNum].push_back(V);
      CsIE_Proton[telnum][csinum][FileNum].push_back(E);
    }
    FileIn_Proton.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for deuterons
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Deuteron=3;
  std::string * FileIn_name_Deuteron[NFiles_Deuteron];
  FileIn_name_Deuteron[0] = new std::string("../calibrations/WMUdata_Z01_A02.dat");   // WMU data
  FileIn_name_Deuteron[1] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A02.dat"); //DEE points
  FileIn_name_Deuteron[2] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A02.dat");  // punch through points

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Deuteron[12][4][3];
  std::vector<double> CsIE_Deuteron[12][4][3];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
  {
    ifstream FileIn_Deuteron(FileIn_name_Deuteron[FileNum]->c_str());
    if(!FileIn_Deuteron.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Deuteron[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Deuteron.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Deuteron, LineRead);

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

      CsIV_Deuteron[telnum][csinum][FileNum].push_back(V);
      CsIE_Deuteron[telnum][csinum][FileNum].push_back(E);
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for tritons
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Triton=2;
  std::string * FileIn_name_Triton[NFiles_Triton];
  FileIn_name_Triton[0] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A03.dat"); //DEE points
  FileIn_name_Triton[1] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A03.dat");  // punch through points

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Triton[12][4][2];
  std::vector<double> CsIE_Triton[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
  {
    ifstream FileIn_Triton(FileIn_name_Triton[FileNum]->c_str());
    if(!FileIn_Triton.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Triton[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Triton.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Triton, LineRead);

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

      CsIV_Triton[telnum][csinum][FileNum].push_back(V);
      CsIE_Triton[telnum][csinum][FileNum].push_back(E);
    }
  }
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  /// read fit parameters
  ifstream FileIn;
  FileIn.open("../calibrations/SimultaneouslyFitParForAll.dat");

  std::vector<int> AValues[12][4];
  std::vector<int> ZValues[12][4];
  std::vector<double> par0[12][4];
  std::vector<double> par1[12][4];
  std::vector<double> par2[12][4];

  while(FileIn.is_open() && !FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int telnum;
    int csinum;
    int ZValue;
    int AValue;
    std::string FitFormula;
    double Par0;
    double Par1;
    double Par2;

    LineStream >> telnum >> csinum >> ZValue >> AValue >> FitFormula >> Par0 >> Par1 >> Par2;

    ZValues[telnum][csinum].push_back(ZValue);
    AValues[telnum][csinum].push_back(AValue);
    par0[telnum][csinum].push_back(Par0);
    par1[telnum][csinum].push_back(Par1);
    par2[telnum][csinum].push_back(Par2);
  }
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  /// calculate the distance from the points to the fit line
  std::vector<double> CsIE[12][4];
  std::vector<double> ErrOfDataPointsToFitLine[12][4];
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      for(int k=0; k<ZValues[i][j].size(); k++)
      {
        double par[4];
        par[0] = par0[i][j][k];
        par[1] = par1[i][j][k];
        par[2] = par2[i][j][k];
        par[3] = AValues[i][j][k];

        ////////////////////////////////////////////////////////////////////////
        /// calculation for protons
        if(ZValues[i][j][k]==1 && AValues[i][j][k]==1)
        {
          for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
          {
            for(int h=0; h<CsIV_Proton[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_Proton[i][j][FileNum][h]);
              double VCal = FitJerzy(&CsIE_Proton[i][j][FileNum][h], par);
              double VRelative = CsIV_Proton[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
<<<<<<< HEAD:70EstimateErrorOfSimultaneouslyFit/PDT_EstimateErrOfSimultaneouslyFit.cpp
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 1 <<"  "<< setw(10) << CsIE_Proton[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_Proton[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }

        ////////////////////////////////////////////////////////////////////////
        /// calculation for deuterons
        if(ZValues[i][j][k]==1 && AValues[i][j][k]==2)
        {
          for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
          {
            if(CsIV_Deuteron[i][j][FileNum].size()==0) continue;
            for(int h=0; h<CsIV_Deuteron[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_Deuteron[i][j][FileNum][h]);
              double VCal = FitJerzy(&CsIE_Deuteron[i][j][FileNum][h], par);
              double VRelative = CsIV_Deuteron[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 2 <<"  "<< setw(10) << CsIE_Deuteron[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_Deuteron[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }

        ////////////////////////////////////////////////////////////////////////
        /// calculation for Tritons
        if(ZValues[i][j][k]==1 && AValues[i][j][k]==3)
        {
          for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
          {
            for(int h=0; h<CsIV_Triton[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_Triton[i][j][FileNum][h]);
              double VCal = FitJerzy(&CsIE_Triton[i][j][FileNum][h], par);
              double VRelative = CsIV_Triton[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 3 <<"  "<< setw(10) << CsIE_Triton[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_Triton[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }
      //========================================================================
=======
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 1 <<"  "<< setw(10) << CsIE_Proton[i][j][FileNum][h] <<"  "<< setw(10) << VRelative <<endl;
            }
          }
        }

        printf("proton\n");

        ////////////////////////////////////////////////////////////////////////
        /// calculation for deuterons
        if(ZValues[i][j][k]==1 && AValues[i][j][k]==2)
        {
          for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
          {
            if(CsIV_Deuteron[i][j][FileNum].size()==0) continue;
            for(int h=0; h<CsIV_Deuteron[i][j][FileNum].size(); h++)
            {
              printf("I am here\n");
              CsIE[i][j].push_back(CsIE_Deuteron[i][j][FileNum][h]);
              double VCal = FitJerzy(&CsIE_Deuteron[i][j][FileNum][h], par);
              double VRelative = CsIV_Deuteron[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 2 <<"  "<< setw(10) << CsIE_Proton[i][j][FileNum][h] <<"  "<< setw(10) << VRelative <<endl;
            }
          }
        }
/*
        printf("deuteron\n");

        ////////////////////////////////////////////////////////////////////////
        /// calculation for Tritons
        if(ZValues[i][j][k]==1 && AValues[i][j][k]==3)
        {
          for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
          {
            for(int h=0; h<CsIV_Triton[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_Triton[i][j][FileNum][h]);
              double VCal = FitJerzy(&CsIE_Triton[i][j][FileNum][h], par);
              double VRelative = CsIV_Triton[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 3 <<"  "<< setw(10) << CsIE_Proton[i][j][FileNum][h] <<"  "<< setw(10) << VRelative <<endl;
            }
          }
        }
*/
        printf("triton\n");

>>>>>>> b45927e7ec2f6dd3e7139c40c981c09aeeb8265e:70EstimateErrorOfSimultaneouslyFit/EstimateErrOfSimultaneouslyFit.cpp
      }
    }
  }
//______________________________________________________________________________



}
