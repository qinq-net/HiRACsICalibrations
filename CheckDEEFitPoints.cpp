void CheckDEEFitPoints()
{

  ifstream FileIn("calibrations/DEEFITPoints.dat");
  int Npoints[12][4][4][10];
  for(int Telnum=0; Telnum<12; Telnum++)
  {
    for(int Csinum=0; Csinum<4; Csinum++)
    {
      for(int Znum=1; Znum<5; Znum++)
      {
        for(int Anum=1; Anum<11; Anum++)
        {
          Npoints[Telnum][Csinum][Znum][Anum]=0;
        }
      }
    }
  }

  double V[12][4][4][10][500];
  double E[12][4][4][10][500]; 
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
    double err_V;
    double err_E;

    LineStream >> numtel >> numcsi >> Zread >> Aread; 
    LineStream >> V[numtel][numcsi][Zread][Aread][Npoints[numtel][numcsi][Zread][Aread]] >> err_V >> E[numtel][numcsi][Zread][Aread][Npoints[numtel][numcsi][Zread][Aread]] >> err_E;
    
    Npoints[numtel][numcsi][Zread][Aread]++;

  }
  
  TCanvas *c1 = new TCanvas("c1","",800,600);
  TGraph *graph[12][4][4][10];
  TMultiGraph * multi[12][4];
  for(int i=0; i<12; i++) 
  {
    for(int j=0; j<4; j++) 
    {
      for(int Z=1; Z<5; Z++)
      {
        for(int A=1; A<11; A++)
        {
          if(Npoints[i][j][Z][A]==0) continue;
          graph[i][j][Z][A] = new TGraph(Npoints[i][j][Z][A], E[i][j][Z][A], V[i][j][Z][A]);
          multi[i][j] = new TMultiGraph();
          multi[i][j]->Add(graph[i][j][Z][A]);
        }
      }   
      multi[i][j]->Draw("AP");
      getchar();
    }
  }
  FileIn.close();
}
