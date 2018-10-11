void FitHorn()
{

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
    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int telnum;
    int csinum;
    double V;
    double errV;
    double E;
    double errE;

    LineStream >> telnum >> csinum >> V >> errV >> E >> errE;
    cout<< telnum << setw(10)<< csinum << setw(20) << V <<endl;

    CsIV_He3[telnum][csinum].push_back(V);
    errCsIV_He3[telnum][csinum].push_back(errV);
    CsIE_He3[telnum][csinum].push_back(E);
    errCsIE_He3[telnum][csinum].push_back(errE);
  }

  




}
