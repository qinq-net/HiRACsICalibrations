
void DEEFITExtractPointsOmitLow()
{
  int Z=1;
  int A=3;

  int Low_Estart=5;
  int Low_Eend=25;
  int Low_Estep=8;
  int Mid_Estart=30;
  int Mid_Eend=90; //  proton--80; deoteron & triton --90
  int Mid_Estep=10;

  ifstream FileIn("calibrations/DEEFITPointsFullInfo.dat");
  ofstream FileOut(Form("calibrations/DEEPointsOmitLow_Z%02d_A%02d.dat", Z, A));
  FileOut << setw(5) << "*tel" << setw(10) << "numcsi" << setw(15) << "CsIV" << setw(15) << "errCsIV" << setw(15) <<"CsIE"<< setw(15)<<"errCsIE\n";

  std::vector<double> LightOutput[12][4];
  std::vector<double> EnergyValues[12][4];
  std::vector<double> errLightOutput[12][4];
  std::vector<double> errEnergyValues[12][4];

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
    double Ch;
    double errCh;
    double V;
    double err_V;
    double E;
    double err_E;

    LineStream >> numtel >> numcsi >> Zread >> Aread >> Ch >> errCh >> V >> err_V >> E >> err_E;
    if(Zread!=Z || Aread!=A) continue;

    LightOutput[numtel][numcsi].push_back(V);
    EnergyValues[numtel][numcsi].push_back(E);
    errLightOutput[numtel][numcsi].push_back(err_V);
    errEnergyValues[numtel][numcsi].push_back(err_E);

  }

  double energy[12][4];
  double voltage[12][4];
  double err_energy[12][4];
  double err_voltage[12][4];
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      if(EnergyValues[i][j].size()==0) continue;

      for(int k=Low_Estart; k<Low_Eend; k+=Low_Estep)
      {
        for(int h=0; h<(EnergyValues[i][j].size()); h++)
        {
           if( (EnergyValues[i][j][h]>(k-1)) && (EnergyValues[i][j][h]<(k+1)))
           {
             energy[i][j] = EnergyValues[i][j][h];
             voltage[i][j]= LightOutput[i][j][h];
             err_energy[i][j]=errEnergyValues[i][j][h];
             err_voltage[i][j]=errLightOutput[i][j][h];
           }
         }
         FileOut << setw(5) << i << setw(10) << j << setw(15) <<  voltage[i][j] << setw(15) << err_voltage[i][j] << setw(15) << energy[i][j] << setw(15) << err_energy[i][j] << endl;
       }

       for(int k=Mid_Estart; k<Mid_Eend; k+=Mid_Estep)
       {
         for(int h=0; h<(EnergyValues[i][j].size()); h++)
         {
            if( (EnergyValues[i][j][h]>(k-1)) && (EnergyValues[i][j][h]<(k+1)))
            {
              energy[i][j] = EnergyValues[i][j][h];
              voltage[i][j]= LightOutput[i][j][h];
              err_energy[i][j]=errEnergyValues[i][j][h];
              err_voltage[i][j]=errLightOutput[i][j][h];
            }
          }
          FileOut << setw(5) << i << setw(10) << j << setw(15) <<  voltage[i][j] << setw(15) << err_voltage[i][j] << setw(15) << energy[i][j] << setw(15) << err_energy[i][j] << endl;
        }
    }

   }




  FileIn.close();
//  FileOut.close();



}
