
//------------------------------------------------------------------------------
void DrawLightOutput()
{
  ofstream FileOut;
  FileOut.open("../calibrations/SimultaneouslyFitParForAll.dat");
  FileOut << setw(5) <<"*tel" <<"  "<< setw(5) << "csi" <<"  "<<setw(5)<< "Z" <<"  "<<setw(5)<< "A" <<"  "<< setw(35) <<"Fit Formula"
              <<"  "<<setw(45) << "Par0" <<"  "<< setw(10) <<"Par1"<<"  "<<setw(10)<<"Par2\n";

//==============================================================================
////////////////////////////////////////////////////////////////////////////////
////   retriving data for protons
////////////////////////////////////////////////////////////////////////////////
const Int_t NFiles_Proton=1;
std::string * FileIn_name_Proton[NFiles_Proton];
FileIn_name_Proton[0] = new std::string("../calibrations/DEEFITPointsFinal.dat");   // WMU data

////////////////////////////////////////////////////////////////////////////////
///   definition of TGraphErrors, TMultiGraph, TLengend
TGraphErrors * DataProton [12][4][NFiles_Proton];
////////////////////////////////////////////////////////////////////////////////
///  definition of variables to read the input data files
std::vector<double> CsIV_Proton[12][4][NFiles_Proton];
std::vector<double> errCsIV_Proton[12][4][NFiles_Proton];
std::vector<double> CsIE_Proton[12][4][NFiles_Proton];
std::vector<double> errCsIE_Proton[12][4][NFiles_Proton];

////////////////////////////////////////////////////////////////////////////////
///  definition of the number of data points for each input file
for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
{
  ifstream FileIn_Proton(FileIn_name_Proton[FileNum]->c_str());
  if(!FileIn_Proton.is_open())
  {
    printf("Error: file%s not found\n", FileIn_name_Proton[FileNum]->c_str());
    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///    Loop, to read each input data file
  while(!FileIn_Proton.eof())
  {
    std::string LineRead;
    std::getline(FileIn_Proton, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int Zread;
    int Aread;
    int telnum;
    int csinum;
    double V;
    double errV;
    double E;
    double errE;

    LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

    if (Zread!=1 || Aread!=1) continue;

    CsIV_Proton[telnum][csinum][FileNum].push_back(V);
    errCsIV_Proton[telnum][csinum][FileNum].push_back(errV);
    CsIE_Proton[telnum][csinum][FileNum].push_back(E);
    errCsIE_Proton[telnum][csinum][FileNum].push_back(errE);
  }

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      DataProton[i][j][FileNum] = new TGraphErrors(CsIV_Proton[i][j][FileNum].size(), CsIE_Proton[i][j][FileNum].data(), CsIV_Proton[i][j][FileNum].data(),  0, 0);
      DataProton[i][j][FileNum]->SetMarkerColor(2); // black marker for Protons
      DataProton[i][j][FileNum]->SetLineColor(2);
      DataProton[i][j][FileNum]->SetMarkerStyle(20+FileNum);
    }
  }
  FileIn_Proton.close();
 }


 ///////////////////////////////////////////////////////////////////////////////
////   retriving data for deuterons
////////////////////////////////////////////////////////////////////////////////
Int_t NFiles_Deuteron=1;
std::string * FileIn_name_Deuteron[NFiles_Deuteron];
FileIn_name_Deuteron[0] = new std::string("../calibrations/DEEFITPointsFinal.dat");

////////////////////////////////////////////////////////////////////////////////
/// definition of TGraphErrors, TMultiGraph, TLengend
TGraphErrors * DataDeuteron[12][4][NFiles_Deuteron];

////////////////////////////////////////////////////////////////////////////////
///  definition of variables to read the input data files
std::vector<double> CsIV_Deuteron[12][4][3];
std::vector<double> errCsIV_Deuteron[12][4][3];
std::vector<double> CsIE_Deuteron[12][4][3];
std::vector<double> errCsIE_Deuteron[12][4][3];

////////////////////////////////////////////////////////////////////////////////
///  definition of the number of data points for each input file
for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
{
  ifstream FileIn_Deuteron(FileIn_name_Deuteron[FileNum]->c_str());
  if(!FileIn_Deuteron.is_open())
  {
    printf("Error: file%s not found\n", FileIn_name_Deuteron[FileNum]->c_str());
    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///    Loop, to read each input data file
  while(!FileIn_Deuteron.eof())
  {
    std::string LineRead;
    std::getline(FileIn_Deuteron, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int Zread;
    int Aread;
    int telnum;
    int csinum;
    double V;
    double errV;
    double E;
    double errE;

    LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

    if (Zread!=1 || Aread!=2) continue;

    CsIV_Deuteron[telnum][csinum][FileNum].push_back(V);
    errCsIV_Deuteron[telnum][csinum][FileNum].push_back(errV);
    CsIE_Deuteron[telnum][csinum][FileNum].push_back(E);
    errCsIE_Deuteron[telnum][csinum][FileNum].push_back(errE);
  }

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      DataDeuteron[i][j][FileNum] = new TGraphErrors(CsIV_Deuteron[i][j][FileNum].size(), CsIE_Deuteron[i][j][FileNum].data(), CsIV_Deuteron[i][j][FileNum].data(),  0, 0);
      DataDeuteron[i][j][FileNum]->SetMarkerColor(3); // black marker for Deuterons
      DataDeuteron[i][j][FileNum]->SetLineColor(3);
    }
  }
  FileIn_Deuteron.close();
}


////////////////////////////////////////////////////////////////////////////////
////   retriving data for tritons
////////////////////////////////////////////////////////////////////////////////
Int_t NFiles_Triton=1;
std::string * FileIn_name_Triton[NFiles_Triton];
FileIn_name_Triton[0] = new std::string("../calibrations/DEEFITPointsFinal.dat");

////////////////////////////////////////////////////////////////////////////////
/// definition of TGraphErrors, TMultiGraph, TLengend
TGraphErrors * DataTriton[12][4][NFiles_Triton];

////////////////////////////////////////////////////////////////////////////////
///  definition of variables to read the input data files
std::vector<double> CsIV_Triton[12][4][2];
std::vector<double> errCsIV_Triton[12][4][2];
std::vector<double> CsIE_Triton[12][4][2];
std::vector<double> errCsIE_Triton[12][4][2];

////////////////////////////////////////////////////////////////////////////////
///  definition of the number of data points for each input file
for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
{
  ifstream FileIn_Triton(FileIn_name_Triton[FileNum]->c_str());
  if(!FileIn_Triton.is_open())
  {
    printf("Error: file%s not found\n", FileIn_name_Triton[FileNum]->c_str());
    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///    Loop, to read each input data file
  while(!FileIn_Triton.eof())
  {
    std::string LineRead;
    std::getline(FileIn_Triton, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int Zread;
    int Aread;
    int telnum;
    int csinum;
    double V;
    double errV;
    double E;
    double errE;

    LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

    if (Zread!=1 || Aread!=3) continue;

    CsIV_Triton[telnum][csinum][FileNum].push_back(V);
    errCsIV_Triton[telnum][csinum][FileNum].push_back(errV);
    CsIE_Triton[telnum][csinum][FileNum].push_back(E);
    errCsIE_Triton[telnum][csinum][FileNum].push_back(errE);
  }

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      DataTriton[i][j][FileNum] = new TGraphErrors(CsIV_Triton[i][j][FileNum].size(), CsIE_Triton[i][j][FileNum].data(), CsIV_Triton[i][j][FileNum].data(),  0, 0);
      DataTriton[i][j][FileNum]->SetMarkerColor(6); // black marker for Tritons
      DataTriton[i][j][FileNum]->SetLineColor(6);
    }
  }
  FileIn_Triton.close();
}


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He3
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He3=1;
  std::string * FileIn_name_He3[NFiles_He3];
  FileIn_name_He3[0] = new std::string("../calibrations/DEEFITPointsFinal.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe3[12][4][NFiles_He3];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He3[12][4][2];
  std::vector<double> errCsIV_He3[12][4][2];
  std::vector<double> CsIE_He3[12][4][2];
  std::vector<double> errCsIE_He3[12][4][2];

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

      int Zread;
      int Aread;
      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

      if (Zread!=2 || Aread!=3) continue;

      CsIV_He3[telnum][csinum][FileNum].push_back(V);
      errCsIV_He3[telnum][csinum][FileNum].push_back(errV);
      CsIE_He3[telnum][csinum][FileNum].push_back(E);
      errCsIE_He3[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe3[i][j][FileNum] = new TGraphErrors(CsIV_He3[i][j][FileNum].size(), CsIE_He3[i][j][FileNum].data(), CsIV_He3[i][j][FileNum].data(),  0, 0);
        DataHe3[i][j][FileNum]->SetMarkerColor(1); // black marker for He3s
        DataHe3[i][j][FileNum]->SetLineColor(1);
      }
    }
    FileIn_He3.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He4
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He4=1;
  std::string * FileIn_name_He4[NFiles_He4];
  FileIn_name_He4[0] = new std::string("../calibrations/DEEFITPointsFinal.dat");

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

      int Zread;
      int Aread;
      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

      if (Zread!=2 || Aread!=4) continue;

      CsIV_He4[telnum][csinum][FileNum].push_back(V);
      errCsIV_He4[telnum][csinum][FileNum].push_back(errV);
      CsIE_He4[telnum][csinum][FileNum].push_back(E);
      errCsIE_He4[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe4[i][j][FileNum] = new TGraphErrors(CsIV_He4[i][j][FileNum].size(), CsIE_He4[i][j][FileNum].data(), CsIV_He4[i][j][FileNum].data(),  0, 0);
        DataHe4[i][j][FileNum]->SetMarkerColor(2); // black marker for He4s
        DataHe4[i][j][FileNum]->SetLineColor(2);
      }
    }
    FileIn_He4.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He6
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He6=1;
  std::string * FileIn_name_He6[NFiles_He6];
  FileIn_name_He6[0] = new std::string("../calibrations/DEEFITPointsFinal.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe6[12][4][NFiles_He6];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He6[12][4][2];
  std::vector<double> errCsIV_He6[12][4][2];
  std::vector<double> CsIE_He6[12][4][2];
  std::vector<double> errCsIE_He6[12][4][2];

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

      int Zread;
      int Aread;
      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

      if (Zread!=2 || Aread!=6) continue;

      CsIV_He6[telnum][csinum][FileNum].push_back(V);
      errCsIV_He6[telnum][csinum][FileNum].push_back(errV);
      CsIE_He6[telnum][csinum][FileNum].push_back(E);
      errCsIE_He6[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe6[i][j][FileNum] = new TGraphErrors(CsIV_He6[i][j][FileNum].size(), CsIE_He6[i][j][FileNum].data(), CsIV_He6[i][j][FileNum].data(),  0, 0);
        DataHe6[i][j][FileNum]->SetMarkerColor(3); // black marker for He6s
        DataHe6[i][j][FileNum]->SetLineColor(3);
      }
    }
    FileIn_He6.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Li6
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Li6=1;
  std::string * FileIn_name_Li6[NFiles_Li6];
  FileIn_name_Li6[0] = new std::string("../calibrations/DEEFITPointsFinal.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataLi6[12][4][NFiles_Li6];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Li6[12][4][2];
  std::vector<double> errCsIV_Li6[12][4][2];
  std::vector<double> CsIE_Li6[12][4][2];
  std::vector<double> errCsIE_Li6[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Li6; FileNum++)
  {
    ifstream FileIn_Li6(FileIn_name_Li6[FileNum]->c_str());
    if(!FileIn_Li6.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Li6[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Li6.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Li6, LineRead);

      LineRead.assign(LineRead.substr(0, LineRead.find('*')));
      if(LineRead.empty()) continue;
      if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

      std::istringstream LineStream(LineRead);

      int Zread;
      int Aread;
      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

      if (Zread!=3 || Aread!=6) continue;

      CsIV_Li6[telnum][csinum][FileNum].push_back(V);
      errCsIV_Li6[telnum][csinum][FileNum].push_back(errV);
      CsIE_Li6[telnum][csinum][FileNum].push_back(E);
      errCsIE_Li6[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataLi6[i][j][FileNum] = new TGraphErrors(CsIV_Li6[i][j][FileNum].size(), CsIE_Li6[i][j][FileNum].data(), CsIV_Li6[i][j][FileNum].data(),  0, 0);
        DataLi6[i][j][FileNum]->SetMarkerColor(4); // black marker for Li6s
        DataLi6[i][j][FileNum]->SetLineColor(4);
      }
    }
    FileIn_Li6.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Li7
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Li7=1;
  std::string * FileIn_name_Li7[NFiles_Li7];
  FileIn_name_Li7[0] = new std::string("../calibrations/DEEFITPointsFinal.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataLi7[12][4][NFiles_Li7];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Li7[12][4][2];
  std::vector<double> errCsIV_Li7[12][4][2];
  std::vector<double> CsIE_Li7[12][4][2];
  std::vector<double> errCsIE_Li7[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Li7; FileNum++)
  {
    ifstream FileIn_Li7(FileIn_name_Li7[FileNum]->c_str());
    if(!FileIn_Li7.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Li7[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Li7.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Li7, LineRead);

      LineRead.assign(LineRead.substr(0, LineRead.find('*')));
      if(LineRead.empty()) continue;
      if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

      std::istringstream LineStream(LineRead);

      int Zread;
      int Aread;
      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

      if (Zread!=3 || Aread!=7) continue;

      CsIV_Li7[telnum][csinum][FileNum].push_back(V);
      errCsIV_Li7[telnum][csinum][FileNum].push_back(errV);
      CsIE_Li7[telnum][csinum][FileNum].push_back(E);
      errCsIE_Li7[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataLi7[i][j][FileNum] = new TGraphErrors(CsIV_Li7[i][j][FileNum].size(), CsIE_Li7[i][j][FileNum].data(), CsIV_Li7[i][j][FileNum].data(),  0, 0);
        DataLi7[i][j][FileNum]->SetMarkerColor(6); // black marker for Li7s
        DataLi7[i][j][FileNum]->SetLineColor(6);
      }
    }
    FileIn_Li7.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Li8
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Li8=1;
  std::string * FileIn_name_Li8[NFiles_Li8];
  FileIn_name_Li8[0] = new std::string("../calibrations/DEEFITPointsFinal.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataLi8[12][4][NFiles_Li8];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Li8[12][4][2];
  std::vector<double> errCsIV_Li8[12][4][2];
  std::vector<double> CsIE_Li8[12][4][2];
  std::vector<double> errCsIE_Li8[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Li8; FileNum++)
  {
    ifstream FileIn_Li8(FileIn_name_Li8[FileNum]->c_str());
    if(!FileIn_Li8.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Li8[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Li8.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Li8, LineRead);

      LineRead.assign(LineRead.substr(0, LineRead.find('*')));
      if(LineRead.empty()) continue;
      if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

      std::istringstream LineStream(LineRead);

      int Zread;
      int Aread;
      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

      if (Zread!=3 || Aread!=8) continue;

      CsIV_Li8[telnum][csinum][FileNum].push_back(V);
      errCsIV_Li8[telnum][csinum][FileNum].push_back(errV);
      CsIE_Li8[telnum][csinum][FileNum].push_back(E);
      errCsIE_Li8[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataLi8[i][j][FileNum] = new TGraphErrors(CsIV_Li8[i][j][FileNum].size(), CsIE_Li8[i][j][FileNum].data(), CsIV_Li8[i][j][FileNum].data(),  0, 0);
        DataLi8[i][j][FileNum]->SetMarkerColor(7); // black marker for Li8s
        DataLi8[i][j][FileNum]->SetLineColor(7);
      }
    }
    FileIn_Li8.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Be7
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Be7=1;
  std::string * FileIn_name_Be7[NFiles_Be7];
  FileIn_name_Be7[0] = new std::string("../calibrations/DEEFITPointsFinal.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataBe7[12][4][NFiles_Be7];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Be7[12][4][2];
  std::vector<double> errCsIV_Be7[12][4][2];
  std::vector<double> CsIE_Be7[12][4][2];
  std::vector<double> errCsIE_Be7[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Be7; FileNum++)
  {
    ifstream FileIn_Be7(FileIn_name_Be7[FileNum]->c_str());
    if(!FileIn_Be7.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Be7[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Be7.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Be7, LineRead);

      LineRead.assign(LineRead.substr(0, LineRead.find('*')));
      if(LineRead.empty()) continue;
      if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

      std::istringstream LineStream(LineRead);

      int Zread;
      int Aread;
      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

      if (Zread!=4 || Aread!=7) continue;

      CsIV_Be7[telnum][csinum][FileNum].push_back(V);
      errCsIV_Be7[telnum][csinum][FileNum].push_back(errV);
      CsIE_Be7[telnum][csinum][FileNum].push_back(E);
      errCsIE_Be7[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataBe7[i][j][FileNum] = new TGraphErrors(CsIV_Be7[i][j][FileNum].size(), CsIE_Be7[i][j][FileNum].data(), CsIV_Be7[i][j][FileNum].data(), 0, 0);
        DataBe7[i][j][FileNum]->SetMarkerColor(9); // black marker for Be7s
        DataBe7[i][j][FileNum]->SetLineColor(9);
      }
    }
    FileIn_Be7.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Be9
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Be9=1;
  std::string * FileIn_name_Be9[NFiles_Be9];
  FileIn_name_Be9[0] = new std::string("../calibrations/DEEFITPointsFinal.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataBe9[12][4][NFiles_Be9];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Be9[12][4][2];
  std::vector<double> errCsIV_Be9[12][4][2];
  std::vector<double> CsIE_Be9[12][4][2];
  std::vector<double> errCsIE_Be9[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Be9; FileNum++)
  {
    ifstream FileIn_Be9(FileIn_name_Be9[FileNum]->c_str());
    if(!FileIn_Be9.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Be9[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Be9.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Be9, LineRead);

      LineRead.assign(LineRead.substr(0, LineRead.find('*')));
      if(LineRead.empty()) continue;
      if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

      std::istringstream LineStream(LineRead);

      int Zread;
      int Aread;
      int telnum;
      int csinum;
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> Zread >> Aread >> V >> errV >> E >> errE;

      if (Zread!=4 || Aread!=9) continue;

      CsIV_Be9[telnum][csinum][FileNum].push_back(V);
      errCsIV_Be9[telnum][csinum][FileNum].push_back(errV);
      CsIE_Be9[telnum][csinum][FileNum].push_back(E);
      errCsIE_Be9[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataBe9[i][j][FileNum] = new TGraphErrors(CsIV_Be9[i][j][FileNum].size(), CsIE_Be9[i][j][FileNum].data(), CsIV_Be9[i][j][FileNum].data(),  0, 0);
        DataBe9[i][j][FileNum]->SetMarkerColor(11); // black marker for Be9s
        DataBe9[i][j][FileNum]->SetLineColor(11);
      }
    }
    FileIn_Be9.close();
  }
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  //// create a multigraph to draw all the Hydrogen isotopes
  TMultiGraph * multiHydrogen[12][4];
  //////////////////////////////////////////////////////////////////////////////
  ////// creating a multigraph to draw all the Heavy ../calibrations
  TMultiGraph * multiHeavyIons[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      //========================================================================
      multiHeavyIons[i][j] = new TMultiGraph();
      //////////////////////////////////////////////////////////////////////////
      ///   Add data for protons
      for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataProton[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///  Add data for deuteron
      for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataDeuteron[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///   Add data for triton
      for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataTriton[i][j][FileNum]);
      }

      //========================================================================
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

      //////////////////////////////////////////////////////////////////////////
      ///// add Li6 data
      for(int FileNum=0; FileNum<NFiles_Li6; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataLi6[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Li7 data
      for(int FileNum=0; FileNum<NFiles_Li7; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataLi7[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Li8 data
      for(int FileNum=0; FileNum<NFiles_Li8; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataLi8[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Be7 data
      for(int FileNum=0; FileNum<NFiles_Be7; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataBe7[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Be9 data
      for(int FileNum=0; FileNum<NFiles_Be9; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataBe9[i][j][FileNum]);
      }
    }
  }
//______________________________________________________________________________


//______________________________________________________________________________
  ///// Draw
  TCanvas *c1 = new TCanvas("c1","",1200,800);
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
    //==========================================================================

      multiHeavyIons[i][j]->Draw("A");
      multiHeavyIons[i][j]->SetTitle(Form("Tel%02d_%02d",i,j));
      c1->Modified();
      c1->Update();

      getchar();
    }

  }

}
