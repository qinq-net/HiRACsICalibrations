//const int Z=1;
//const int A=1;
const int TelNum=12;
const int CsINum=4;
const int ParticleType=3;


void PIDKinematicPunchThroughFit2()
{
  
  //---- Open Kinematics data files --------------------------
  
  //---- Files for protons
  Int_t NFiles=15;  
  std::string * FileIn_name[NFiles];
  FileIn_name[0] = new std::string(Form("datfile/HiRA_CsI_DEELowEnergy_Z%02d_A%02d.dat", 1, 1));
  FileIn_name[1] = new std::string(Form("datfile/HiRA_CsI_DEEMidEnergy_Z%02d_A%02d.dat", 1, 1));
  FileIn_name[2] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_2013_2037_40Ca39AMeV_gain 200.dat");
  FileIn_name[3] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_2312_2312_40Ca56AMeV_gain 170.dat");
  FileIn_name[4] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_4034_4037_48Ca28AMeV_gain 170.dat");
  FileIn_name[5] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_4332_4332_48Ca56AMeV_gain 170.dat");
  FileIn_name[6] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_4577_4584_48Ca28AMeV_gain 170.dat");
  FileIn_name[7] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_4585_4589_48Ca56AMeV_gain 170.dat");
  FileIn_name[8] = new std::string(Form("datfile/HiRA_CsI_PunchThrough_Z%02d_A%02d.dat", 1, 1));
  
  //--- files for deuterons
  FileIn_name[9]  = new std::string(Form("datfile/HiRA_CsI_DEELowEnergy_Z%02d_A%02d.dat", 1, 2));
  FileIn_name[10] = new std::string(Form("datfile/HiRA_CsI_DEEMidEnergy_Z%02d_A%02d.dat", 1, 2));
  FileIn_name[11] = new std::string(Form("datfile/HiRA_CsI_PunchThrough_Z%02d_A%02d.dat", 1, 2));
  
  //--- files for tritons
  FileIn_name[12] = new std::string(Form("datfile/HiRA_CsI_DEELowEnergy_Z%02d_A%02d.dat", 1, 3));
  FileIn_name[13] = new std::string(Form("datfile/HiRA_CsI_DEEMidEnergy_Z%02d_A%02d.dat", 1, 3));
  FileIn_name[14] = new std::string(Form("datfile/HiRA_CsI_PunchThrough_Z%02d_A%02d.dat", 1, 3));
  
  //-------- definition of TGraphErrors, TMultiGraph, TLengend -----------------------------------------
  TGraphErrors * DataSet[TelNum][CsINum][NFiles];
  TMultiGraph * DataGraph[TelNum][CsINum];
  TLegend * legend[TelNum][CsINum];
    
  //---- definition of variables to read the input data files ------------------------------------------ 
  int Npoints[TelNum][CsINum][NFiles];
  double CsI_V[TelNum][CsINum][NFiles][100];
  double err_CsI_V[TelNum][CsINum][NFiles][100];
  double Energy[TelNum][CsINum][NFiles][100];
  double err_Energy[TelNum][CsINum][NFiles][100];
  
  //------ definition of the number of data points for each input file ---------------------------------
  for(int FileNum=0; FileNum<NFiles; FileNum++)
  {
    for(int i=0; i<TelNum; i++)
    {
      for(int j=0; j<CsINum; j++)
      {
        Npoints[i][j][FileNum]=0;
      }
    }
    ifstream FileIn(FileIn_name[FileNum]->c_str());
 
    if(!FileIn.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name[FileNum]->c_str());
      return;
    }
    //------ Loop, to read each input data file --------------------------------
    while(!FileIn.eof())
    {
      std::string LineRead;
      std::getline(FileIn, LineRead);
    
      if(LineRead.empty()) continue;
      if(LineRead.find('*')==0) continue; 
  
      std::istringstream LineStream(LineRead);
    
      int telnum;
      int csinum;
    
      LineStream >> telnum >> csinum;
//    cout<< telnum << setw(10) << csinum <<endl;
      LineStream >> CsI_V[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]] >> err_CsI_V[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]] >> Energy[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]] >> err_Energy[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]];
//    cout<< CsI_V[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]] << setw(15) << err_CsI_V[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]] <<setw(15) << Energy[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]] << setw(15) << err_Energy[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]] <<setw(15) << endl;
      
      if(err_Energy[telnum][csinum][FileNum][Npoints[telnum][csinum][FileNum]]==0) continue;
      Npoints[telnum][csinum][FileNum]++;  
    }
    printf("Read file %s\n", FileIn_name[FileNum]->c_str());
    
    //----- to set graph color, markerstyle ----------------------------------------------------

//    TColor * color = new TColor(ci, 0.1*FileNum, 0.2*FileNum, 0.3*FileNum);
 
    for(int i=0; i<TelNum; i++)
    {
      for(int j=0; j<CsINum; j++)
      {
        
        if(Npoints[i][j][FileNum]>0)
        {
          DataSet[i][j][FileNum] = new TGraphErrors(Npoints[i][j][FileNum], Energy[i][j][FileNum], CsI_V[i][j][FileNum], err_Energy[i][j][FileNum], err_CsI_V[i][j][FileNum]);
          if(FileNum>=0 && FileNum<9)
          {
            DataSet[i][j][FileNum] -> SetMarkerStyle(20);
            DataSet[i][j][FileNum] -> SetMarkerColor(1+FileNum);
            DataSet[i][j][FileNum] -> SetLineColor(1+FileNum);
          }
          
          if(FileNum>=9 && FileNum<12)
          {
            DataSet[i][j][FileNum] -> SetMarkerStyle(21);
            DataSet[i][j][FileNum] -> SetMarkerColor(FileNum-3);
            DataSet[i][j][FileNum] -> SetLineColor(FileNum-3);
          }
          
          if(FileNum>=12 && FileNum<15)
          {
            DataSet[i][j][FileNum] -> SetMarkerStyle(27);
            DataSet[i][j][FileNum] -> SetMarkerColor(FileNum-6);
            DataSet[i][j][FileNum] -> SetLineColor(FileNum-6);
          }
        }
        else DataSet[i][j][FileNum]=0; 
      }
      
     FileIn.close();    
    }
  }
      
  
  //----- to add graphs and legends --------------------------------------
 
  for(int i=0; i<TelNum; i++)
  {
    for(int j=0; j<CsINum; j++)
    {
     
      legend[i][j]= new TLegend(0.12, 0.60, 0.62, 0.85);
      legend[i][j]-> SetBorderSize(0);
      DataGraph[i][j] = new TMultiGraph();
      for(int FileNum=0; FileNum<NFiles; FileNum++)
      {
        if(DataSet[i][j][FileNum]!=0)
        {
          legend[i][j]->AddEntry(DataSet[i][j][FileNum], FileIn_name[FileNum]->substr(FileIn_name[FileNum]->find_last_of("/")+1,FileIn_name[FileNum]->find_last_of(".")-FileIn_name[FileNum]->find_last_of("/")-1).c_str(), "P");
          DataGraph[i][j]->Add(DataSet[i][j][FileNum]);
        }
      } 
    }    
  } 
  
  //----- Draw graphs --------------------------------------
  TCanvas *c1 = new TCanvas("c1","", 1200, 800); 
  for(int i=0; i<TelNum; i++)
  {
    for(int j=0; j<CsINum; j++)
    {
      if(DataGraph[i][j]==0) continue;  // if DataGraph does not exist, continue
      
      //---- creating graphs ----------------------------------
      DataGraph[i][j]->SetName(Form("Graph_CsIVoltgae_LISEEnergy%02d_%02d", i, j));
      DataGraph[i][j]->SetTitle(Form("Tel%02d_CsI%02d Calibration", i, j));
      DataGraph[i][j]->Draw("APE");
      DataGraph[i][j]->GetXaxis()->SetTitle("LISE Energy (MeV)");
      DataGraph[i][j]->GetXaxis()->CenterTitle(true);
      DataGraph[i][j]->GetXaxis()->SetTitleSize(0.05);
      DataGraph[i][j]->GetXaxis()->SetLabelSize(0.05);
      DataGraph[i][j]->GetYaxis()->SetTitle("CsIVoltage (V)");
      DataGraph[i][j]->GetYaxis()->CenterTitle(true);
      DataGraph[i][j]->GetYaxis()->SetTitleSize(0.05);
      DataGraph[i][j]->GetYaxis()->SetLabelSize(0.05);
      
      legend[i][j]->Draw("SAME");
  
      TF1 * fit_func=new TF1(Form("fit_func%02d_%02d", i,j),"[0]*x^{[1]}",0, 320);
      fit_func->SetParameters(0.007,0.9);
      DataGraph[i][j]->Fit(fit_func,"W RC+");
      fit_func->Draw("SAME");

      c1->Modified();
      c1->Update();
  //  getchar();
      
      c1->Print(Form("pictures/PID_Kinematics_PunchThrough_Tel%02d_CsI%02d.png",i, j)); 
    }     
  }
 
}
