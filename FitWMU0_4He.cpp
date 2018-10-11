
void FitWMU0_4He()
{

   const int TELNUM=12;
   const int CSINUM=4;
   const int Z=2;
   const int A=4;
   
   std::string FileOutTag("WMU_4He");
   
   ifstream FileInLowEnergy(Form("calibrations/HiRA_CsI_DEELowEnergy_Z%02d_A%02d.dat", Z, A));
   ifstream FileInMidEnergy(Form("calibrations/HiRA_CsI_DEEMidEnergy_Z%02d_A%02d.dat", Z, A));
   ifstream FileInWMU(Form("calibrations/WMUdata_Z%02d_A%02d.dat", Z, A));
   
   ofstream FileOut;
   FileOut.open(Form("40PID_KInematic_PunchThrough_Graph/Fitparameters_%s.dat", FileOutTag.c_str()));
   FileOut << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<< setw(10) << "Par0" <<"  "<<setw(10)<<"Par1\n";
   
   //---- retrieving lowenergy data ---------------
   int npoints_low[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_low[i][j]=0;
     }
   }
   double low_voltage[TELNUM][CSINUM][100];
   double errlow_voltage[TELNUM][CSINUM][100];
   double low_energy[TELNUM][CSINUM][100];
   double errlow_energy[TELNUM][CSINUM][100];
   while(FileInLowEnergy.is_open() && !FileInLowEnergy.eof())
   {
     std::string LineRead;
     std::getline(FileInLowEnergy, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> low_voltage[telnum][csinum][npoints_low[telnum][csinum]] >> errlow_voltage[telnum][csinum][npoints_low[telnum][csinum]] >> low_energy[telnum][csinum][npoints_low[telnum][csinum]] >> errlow_energy[telnum][csinum][npoints_low[telnum][csinum]] ;
     
     npoints_low[telnum][csinum]++;
   
   }

   //---- retrieving midenergy data ---------------
   int npoints_mid[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_mid[i][j]=0;
     }
   }
   double mid_voltage[TELNUM][CSINUM][100];
   double errmid_voltage[TELNUM][CSINUM][100];
   double mid_energy[TELNUM][CSINUM][100];
   double errmid_energy[TELNUM][CSINUM][100];
   while(FileInMidEnergy.is_open() && !FileInMidEnergy.eof())
   {
     std::string LineRead;
     std::getline(FileInMidEnergy, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> mid_voltage[telnum][csinum][npoints_mid[telnum][csinum]] >> errmid_voltage[telnum][csinum][npoints_mid[telnum][csinum]] >> mid_energy[telnum][csinum][npoints_mid[telnum][csinum]] >> errmid_energy[telnum][csinum][npoints_mid[telnum][csinum]] ;
          
     npoints_mid[telnum][csinum]++;
   
   }
   
   //---- retrieving WMUdata ---------------
   int npoints_WMU[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_WMU[i][j]=0;
     }
   }
   double WMU_voltage[TELNUM][CSINUM][100];
   double errWMU_voltage[TELNUM][CSINUM][100];
   double WMU_energy[TELNUM][CSINUM][100];
   double errWMU_energy[TELNUM][CSINUM][100];
   while(FileInWMU.is_open() && !FileInWMU.eof())
   {
     std::string LineRead;
     std::getline(FileInWMU, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> WMU_voltage[telnum][csinum][npoints_WMU[telnum][csinum]] >> errWMU_voltage[telnum][csinum][npoints_WMU[telnum][csinum]] >> WMU_energy[telnum][csinum][npoints_WMU[telnum][csinum]] >> errWMU_energy[telnum][csinum][npoints_WMU[telnum][csinum]] ;
     
     npoints_WMU[telnum][csinum]++;
   
   }
   
   //--- creating graphs ----------------
   TGraphErrors * data_low[TELNUM][CSINUM];
   TGraphErrors * data_mid[TELNUM][CSINUM];
   TGraphErrors * data_WMU[TELNUM][CSINUM];
   TMultiGraph * data_total[TELNUM][CSINUM];
   TMultiGraph * Fit_data_total[TELNUM][CSINUM];
   
   TLegend * legend[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
 
       if(npoints_WMU[i][j]==0) continue; 
       
       data_low[i][j]  = new TGraphErrors(npoints_low[i][j], low_energy[i][j], low_voltage[i][j], errlow_energy[i][j], errlow_voltage[i][j]);
       data_mid[i][j]  = new TGraphErrors(npoints_mid[i][j], mid_energy[i][j], mid_voltage[i][j], errmid_energy[i][j], errmid_voltage[i][j]);
       data_WMU[i][j]  = new TGraphErrors(npoints_WMU[i][j], WMU_energy[i][j], WMU_voltage[i][j], errWMU_energy[i][j], errWMU_voltage[i][j]);
       
       data_low[i][j]->SetMarkerStyle(24);  // open circle
       data_low[i][j]->SetMarkerColor(6);
       data_low[i][j]->SetMarkerSize(1.2);
       data_mid[i][j]->SetMarkerStyle(20);  // open circle
       data_mid[i][j]->SetMarkerColor(6);
       data_mid[i][j]->SetMarkerSize(1.2);
       data_WMU[i][j]->SetMarkerStyle(20);  // open circle
       data_WMU[i][j]->SetMarkerColor(4);
       data_WMU[i][j]->SetMarkerSize(1.2);
       
       data_total[i][j]= new TMultiGraph();
       data_total[i][j]->Add(data_mid[i][j]);
       data_total[i][j]->Add(data_WMU[i][j]);
       data_total[i][j]->Add(data_low[i][j]);
       
       //--- fit WMU data and mid energy data ----
       Fit_data_total[i][j]= new TMultiGraph();
       Fit_data_total[i][j]->Add(data_WMU[i][j]);
       Fit_data_total[i][j]->Add(data_mid[i][j]);
       
             
       legend[i][j]= new TLegend(0.50, 0.2, 0.80, 0.35);
       legend[i][j]->AddEntry(data_low[i][j], "LowEnergyExpData", "P");
       legend[i][j]->AddEntry(data_mid[i][j], "MidEnergyExpData", "P");
       legend[i][j]->AddEntry(data_WMU[i][j], "WMUExpData", "P");       
            
     }
   }
   
   TCanvas *c1=new TCanvas("c","", 1200, 800);
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       if(npoints_WMU[i][j]==0) continue;
       gPad->SetLogy(1);
     
       data_total[i][j]->Draw("AP");
       data_total[i][j]->SetTitle(Form("Graph_CsIVoltage_LISEEnergy%02d_%02d", i, j));
       data_total[i][j]->GetXaxis()->SetTitle("LISE Energy (MeV)");
       data_total[i][j]->GetXaxis()->CenterTitle(true);
       data_total[i][j]->GetXaxis()->SetTitleSize(0.05);
       data_total[i][j]->GetXaxis()->SetLabelSize(0.05);
       data_total[i][j]->GetYaxis()->SetTitle("CsIVoltage (V)");
       data_total[i][j]->GetYaxis()->CenterTitle(true);
       data_total[i][j]->GetYaxis()->SetTitleSize(0.05);
       data_total[i][j]->GetYaxis()->SetLabelSize(0.05);
       
      
             
       legend[i][j]->Draw("SAME");
       
       TF1 * fit_func=new TF1(Form("fit_func%02d_%02d", i,j),"[0]*x^{[1]}",0.1, 100);
       fit_func->SetParameters(0.003,1.2);
       Fit_data_total[i][j]->Fit(fit_func,"RC+");
       fit_func->Draw("SAME");
       double par0 = fit_func->GetParameter(0);
       double par1 = fit_func->GetParameter(1);
       FileOut << setw(5) << i <<"  "<< setw(10) << j <<"  "<< setw(10) << par0 <<"  "<<setw(10)<< par1 <<endl;
           
       gPad->Modified();
       gPad->Update();
       
       c1->Print(Form("40PID_KInematic_PunchThrough_Graph/PID_Kinematics_PunchThrough_Tel%02d_CsI%02d_%s.png",i, j, FileOutTag.c_str())); 
     
     }
   }
   
   
   
   
   
   
   
   
   
   


}
