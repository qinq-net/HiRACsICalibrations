
void ExtractDEEPointsOmitLow()
{
  int Z=1;
  int A=3;

  int Low_Estart=5;
  int Low_Eend=25;
  int Low_Estep=8;
  int Mid_Estart=30;
  int Mid_Eend=90; //  proton--80; deoteron & triton --90
  int Mid_Estep=10;

  ifstream FileIn("calibrations/DEEFITPointsFinal.dat");
  ofstream FileOut(Form("calibrations/OmitLowDEEPoints_Z%02d_A%02d.dat", Z, A));
  FileOut << setw(5) << "*tel" << setw(10) << "numcsi" << setw(15) << "CsIV" << setw(15) << "errCsIV" << setw(15) <<"CsIE"<< setw(15)<<"errCsIE\n";

  std::vector<double> VoltageValues[12][4];
  std::vector<double> EnergyValues[12][4];

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int numcsi;
    int Zread;
    int Aread;
    double V;
    double err_V;
    double E;
    double err_E;

    LineStream >> numtel >> numcsi >> Zread >> Aread >> V >> err_V >> E >> err_E;
    if(Zread!=Z || Aread!=A) continue;

    VoltageValues[numtel][numcsi].push_back(V);
    EnergyValues[numtel][numcsi].push_back(E);

  }

  double err[12][4];
  double Voltage[12][4];
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      for(int k=Low_Estart; k<Low_Eend; k+=Low_Estep)
      {
        for(int h=0; h<(EnergyValues[i][j].size()-1); h++)
        {
           if( (EnergyValues[i][j][h]>(k-1)) && (EnergyValues[i][j][h]<(k+1)))
           {
             err[i][j] =  fmin(EnergyValues[i][j][h] , EnergyValues[i][j][h+1]);
             Voltage[i][j]= VoltageValues[i][j][h];
           }
         }
         FileOut << setw(5) << i << setw(10) << j << setw(15) <<  Voltage[i][j] << setw(15) << 0 << setw(15) << err[i][j] << setw(15) << 0 << endl;
       }

       for(int k=Mid_Estart; k<Mid_Eend; k+=Mid_Estep)
       {
         for(int h=0; h<(EnergyValues[i][j].size()-1); h++)
         {
            if( (EnergyValues[i][j][h]>(k-1)) && (EnergyValues[i][j][h]<(k+1)))
            {
              err[i][j] =  fmin(EnergyValues[i][j][h] , EnergyValues[i][j][h+1]);
              Voltage[i][j]= VoltageValues[i][j][h];
            }
          }
          FileOut << setw(5) << i << setw(10) << j << setw(15) <<  Voltage[i][j] << setw(15) << 0 << setw(15) << err[i][j] << setw(15) << 0 << endl;
        }
    }

   }




  FileIn.close();
//  FileOut.close();



}
