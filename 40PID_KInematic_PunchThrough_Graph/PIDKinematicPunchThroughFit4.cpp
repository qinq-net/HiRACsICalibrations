//const int Z=1;
//const int A=1;
const int TelNum=12;
const int CsINum=4;


void PIDKinematicPunchThroughFit4()
{
  

  std::string FileOutTag("3He");
  
  ofstream FileOut;
  FileOut.open(Form("datfile/FitParameters_%s", FileOutTag.c_str()));
  FileOut << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<< setw(10) << "Par0" <<"  "<<setw(10)<<"Par1\n";
  //---- Open Kinematics data files --------------------------
  
  //---- Files for protons
  Int_t NFiles=2;  
  std::string * FileIn_name[NFiles];
  
  
  //--- files for tritons
  FileIn_name[0] = new std::string(Form("datfile/HiRA_CsI_DEELowEnergy_Z%02d_A%02d.dat", 2, 3));
  FileIn_name[1] = new std::string(Form("datfile/HiRA_CsI_DEEMidEnergy_Z%02d_A%02d.dat", 2, 3));
  
   
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
          DataSet[i][j][FileNum] -> SetMarkerStyle(20);
          DataSet[i][j][FileNum] -> SetMarkerColor(FileNum+6);
          DataSet[i][j][FileNum] -> SetLineColor(FileNum+6);       
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
     
      legend[i][j]= new TLegend(0.55, 0.20, 0.80, 0.40);
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
    //   gPad->SetLogy(1);
       
      //---- creating graphs ----------------------------------
      DataGraph[i][j]->SetName(Form("Graph_CsIVoltgae_LISEEnergy%02d_%02d", i, j));
      DataGraph[i][j]->SetTitle(Form("Tel%02d_CsI%02d Calibration_for_%s", i, j, FileOutTag.c_str()));
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
  
      //------- The fit function: L(Z,E) = a*Z^{b}*E^{c}
/* 
      TF1 * fit_func=new TF1(Form("fit_func%02d_%02d", i,j),"[0]*x^{[1]}",0, 320);
      fit_func->SetParameters(0.005,1);
*/      
      TF1 * fit_func=new TF1(Form("fit_func%02d_%02d", i,j),"[0]*2^{[1]}*x^{[2]}",0, 320);
      fit_func->SetParameters(0.003,0.6,1);
       
      DataGraph[i][j]->Fit(fit_func,"W RC+");
      fit_func->Draw("SAME");
      double par0 = fit_func->GetParameter(0);
      double par1 = fit_func->GetParameter(1);     
      FileOut << setw(5) << i <<"  "<< setw(10) << j <<"  "<< setw(10) << par0 <<"  "<<setw(10)<< par1 <<endl;
      
      c1->Modified();
      c1->Update();
      
  //  getchar();
      
      c1->Print(Form("pictures/%s/PID_Kinematics_PunchThrough_Tel%02d_CsI%02d_%s.png",FileOutTag.c_str(), i, j, FileOutTag.c_str())); 
    }     
  }
 
}
