
void ExtractDEEPoints()
{
  int Z=4;
  int A=10;

  ifstream FileIn("calibrations/DEEFITPointsFinal.dat");
  ofstream FileOut(Form("calibrations/DEEPoints_Z%02d_A%02d.dat", Z, A));
  FileOut << setw(5) << "*tel" << setw(10) << "numcsi" << setw(10) << "CsIV" << setw(15) << "errCsIV" << setw(15) <<"CsIE"<< setw(15)<<"errCsIE\n";

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

  double energy[12][4];
  double voltage[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      int Estart = EnergyValues[i][j].front()+2;
      int Eend = EnergyValues[i][j].back();
      int Estep = (int)floor((EnergyValues[i][j].back()-EnergyValues[i][j].front())/20);

      for(int k=Estart; k<Eend; k+=Estep)
      {
        for(int h=1; h<(EnergyValues[i][j].size()); h++)
        {
           if( (EnergyValues[i][j][h]>(k-1)) && (EnergyValues[i][j][h]<(k+1)))
           {
             energy[i][j] =  fmin(EnergyValues[i][j][h] , EnergyValues[i][j][h-1]);
             voltage[i][j]= VoltageValues[i][j][h-1];
           }
         }
         FileOut << setw(5) << i << setw(10) << j << setw(15) <<  voltage[i][j] << setw(15) << 0 << setw(15) << energy[i][j] << setw(15) << 0 << endl;
       }
     }
   }

  FileIn.close();
}
