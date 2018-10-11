
void DrawHiRA_WMU()
{

   const int TELNUM=12;
   const int CSINUM=4;
   
   std::string FileOutTag1("LowEnergy");
   std::string FileOutTag2("MidEnergy");
   
   ifstream FileInHiRA_proton(Form("datfile/HiRA_CsI_DEE%s_Z01_A01.dat", FileOutTag1.c_str()));
   ifstream FileInHiRA_deuteron(Form("datfile/HiRA_CsI_DEE%s_Z01_A02.dat", FileOutTag1.c_str()));
   ifstream FileInHiRA_4He(Form("datfile/HiRA_CsI_DEE%s_Z02_A04.dat", FileOutTag1.c_str()));
   
   ifstream FileInHiRA_proton1(Form("datfile/HiRA_CsI_DEE%s_Z01_A01.dat", FileOutTag2.c_str()));
   ifstream FileInHiRA_deuteron1(Form("datfile/HiRA_CsI_DEE%s_Z01_A02.dat", FileOutTag2.c_str()));
   ifstream FileInHiRA_4He1(Form("datfile/HiRA_CsI_DEE%s_Z02_A04.dat", FileOutTag2.c_str()));
   
   
   ifstream FileInWMU_proton("datfile/WMUdata_Z01_A01.dat");
   ifstream FileInWMU_deuteron("datfile/WMUdata_Z01_A02.dat");
   ifstream FileInWMU_4He("datfile/WMUdata_Z02_A04.dat");
       
         
   //---- 1. retrieving HiRA_proton data low energy---------------
   int npoints_HiRA_proton[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_HiRA_proton[i][j]=0;
     }
   }
   double HiRA_proton_voltage[TELNUM][CSINUM][100];
   double errHiRA_proton_voltage[TELNUM][CSINUM][100];
   double HiRA_proton_energy[TELNUM][CSINUM][100];
   double errHiRA_proton_energy[TELNUM][CSINUM][100];
   while(FileInHiRA_proton.is_open() && !FileInHiRA_proton.eof())
   {
     std::string LineRead;
     std::getline(FileInHiRA_proton, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> HiRA_proton_voltage[telnum][csinum][npoints_HiRA_proton[telnum][csinum]] >> errHiRA_proton_voltage[telnum][csinum][npoints_HiRA_proton[telnum][csinum]] >> HiRA_proton_energy[telnum][csinum][npoints_HiRA_proton[telnum][csinum]] >> errHiRA_proton_energy[telnum][csinum][npoints_HiRA_proton[telnum][csinum]] ;
     
     npoints_HiRA_proton[telnum][csinum]++;
   
   }

   //----2. retrieving HiRA_deuteron data low energy---------------
   int npoints_HiRA_deuteron[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_HiRA_deuteron[i][j]=0;
     }
   }
   double HiRA_deuteron_voltage[TELNUM][CSINUM][100];
   double errHiRA_deuteron_voltage[TELNUM][CSINUM][100];
   double HiRA_deuteron_energy[TELNUM][CSINUM][100];
   double errHiRA_deuteron_energy[TELNUM][CSINUM][100];
   while(FileInHiRA_deuteron.is_open() && !FileInHiRA_deuteron.eof())
   {
     std::string LineRead;
     std::getline(FileInHiRA_deuteron, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> HiRA_deuteron_voltage[telnum][csinum][npoints_HiRA_deuteron[telnum][csinum]] >> errHiRA_deuteron_voltage[telnum][csinum][npoints_HiRA_deuteron[telnum][csinum]] >> HiRA_deuteron_energy[telnum][csinum][npoints_HiRA_deuteron[telnum][csinum]] >> errHiRA_deuteron_energy[telnum][csinum][npoints_HiRA_deuteron[telnum][csinum]] ;
          
     npoints_HiRA_deuteron[telnum][csinum]++;
   
   }
   
   //----3. retrieving HiRA_4He low energy---------------
   int npoints_HiRA_4He[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_HiRA_4He[i][j]=0;
     }
   }
   double HiRA_4He_voltage[TELNUM][CSINUM][100];
   double errHiRA_4He_voltage[TELNUM][CSINUM][100];
   double HiRA_4He_energy[TELNUM][CSINUM][100];
   double errHiRA_4He_energy[TELNUM][CSINUM][100];
   while(FileInHiRA_4He.is_open() && !FileInHiRA_4He.eof())
   {
     std::string LineRead;
     std::getline(FileInHiRA_4He, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> HiRA_4He_voltage[telnum][csinum][npoints_HiRA_4He[telnum][csinum]] >> errHiRA_4He_voltage[telnum][csinum][npoints_HiRA_4He[telnum][csinum]] >> HiRA_4He_energy[telnum][csinum][npoints_HiRA_4He[telnum][csinum]] >> errHiRA_4He_energy[telnum][csinum][npoints_HiRA_4He[telnum][csinum]] ;
     
     npoints_HiRA_4He[telnum][csinum]++;   
   }
   
   
    //---- 4. retrieving HiRA_proton data mid energy---------------
   int npoints_HiRA_proton1[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_HiRA_proton1[i][j]=0;
     }
   }
   double HiRA_proton1_voltage[TELNUM][CSINUM][100];
   double errHiRA_proton1_voltage[TELNUM][CSINUM][100];
   double HiRA_proton1_energy[TELNUM][CSINUM][100];
   double errHiRA_proton1_energy[TELNUM][CSINUM][100];
   while(FileInHiRA_proton1.is_open() && !FileInHiRA_proton1.eof())
   {
     std::string LineRead;
     std::getline(FileInHiRA_proton1, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> HiRA_proton1_voltage[telnum][csinum][npoints_HiRA_proton1[telnum][csinum]] >> errHiRA_proton1_voltage[telnum][csinum][npoints_HiRA_proton1[telnum][csinum]] >> HiRA_proton1_energy[telnum][csinum][npoints_HiRA_proton1[telnum][csinum]] >> errHiRA_proton1_energy[telnum][csinum][npoints_HiRA_proton1[telnum][csinum]] ;
     
     npoints_HiRA_proton1[telnum][csinum]++;
   
   }
   
   
    //----5. retrieving HiRA_deuteron data mid energy---------------
   int npoints_HiRA_deuteron1[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_HiRA_deuteron1[i][j]=0;
     }
   }
   double HiRA_deuteron1_voltage[TELNUM][CSINUM][100];
   double errHiRA_deuteron1_voltage[TELNUM][CSINUM][100];
   double HiRA_deuteron1_energy[TELNUM][CSINUM][100];
   double errHiRA_deuteron1_energy[TELNUM][CSINUM][100];
   while(FileInHiRA_deuteron1.is_open() && !FileInHiRA_deuteron1.eof())
   {
     std::string LineRead;
     std::getline(FileInHiRA_deuteron1, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> HiRA_deuteron1_voltage[telnum][csinum][npoints_HiRA_deuteron1[telnum][csinum]] >> errHiRA_deuteron1_voltage[telnum][csinum][npoints_HiRA_deuteron1[telnum][csinum]] >> HiRA_deuteron1_energy[telnum][csinum][npoints_HiRA_deuteron1[telnum][csinum]] >> errHiRA_deuteron1_energy[telnum][csinum][npoints_HiRA_deuteron1[telnum][csinum]] ;
          
     npoints_HiRA_deuteron1[telnum][csinum]++;
   
   }
   
   
   //----6. retrieving HiRA_4He mid energy---------------
   int npoints_HiRA_4He1[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_HiRA_4He1[i][j]=0;
     }
   }
   double HiRA_4He1_voltage[TELNUM][CSINUM][100];
   double errHiRA_4He1_voltage[TELNUM][CSINUM][100];
   double HiRA_4He1_energy[TELNUM][CSINUM][100];
   double errHiRA_4He1_energy[TELNUM][CSINUM][100];
   while(FileInHiRA_4He1.is_open() && !FileInHiRA_4He1.eof())
   {
     std::string LineRead;
     std::getline(FileInHiRA_4He1, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> HiRA_4He1_voltage[telnum][csinum][npoints_HiRA_4He1[telnum][csinum]] >> errHiRA_4He1_voltage[telnum][csinum][npoints_HiRA_4He1[telnum][csinum]] >> HiRA_4He1_energy[telnum][csinum][npoints_HiRA_4He1[telnum][csinum]] >> errHiRA_4He1_energy[telnum][csinum][npoints_HiRA_4He1[telnum][csinum]] ;
     
     npoints_HiRA_4He1[telnum][csinum]++;   
   }

   
   //----7.  retrieving  WMU_proton datas ---------------
   int npoints_WMU_proton[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_WMU_proton[i][j]=0;
     }
   }
   double WMU_proton_voltage[TELNUM][CSINUM][100];
   double errWMU_proton_voltage[TELNUM][CSINUM][100];
   double WMU_proton_energy[TELNUM][CSINUM][100];
   double errWMU_proton_energy[TELNUM][CSINUM][100];
   while(FileInWMU_proton.is_open() && !FileInWMU_proton.eof())
   {
     std::string LineRead;
     std::getline(FileInWMU_proton, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> WMU_proton_voltage[telnum][csinum][npoints_WMU_proton[telnum][csinum]] >> errWMU_proton_voltage[telnum][csinum][npoints_WMU_proton[telnum][csinum]] >> WMU_proton_energy[telnum][csinum][npoints_WMU_proton[telnum][csinum]] >> errWMU_proton_energy[telnum][csinum][npoints_WMU_proton[telnum][csinum]] ;
     
     npoints_WMU_proton[telnum][csinum]++;
   
   }
   
   //----8.  retrieving  WMU_deuteron datas ---------------
   int npoints_WMU_deuteron[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_WMU_deuteron[i][j]=0;
     }
   }
   double WMU_deuteron_voltage[TELNUM][CSINUM][100];
   double errWMU_deuteron_voltage[TELNUM][CSINUM][100];
   double WMU_deuteron_energy[TELNUM][CSINUM][100];
   double errWMU_deuteron_energy[TELNUM][CSINUM][100];
   while(FileInWMU_deuteron.is_open() && !FileInWMU_deuteron.eof())
   {
     std::string LineRead;
     std::getline(FileInWMU_deuteron, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> WMU_deuteron_voltage[telnum][csinum][npoints_WMU_deuteron[telnum][csinum]] >> errWMU_deuteron_voltage[telnum][csinum][npoints_WMU_deuteron[telnum][csinum]] >> WMU_deuteron_energy[telnum][csinum][npoints_WMU_deuteron[telnum][csinum]] >> errWMU_deuteron_energy[telnum][csinum][npoints_WMU_deuteron[telnum][csinum]] ;
     
     npoints_WMU_deuteron[telnum][csinum]++;
   
   }
   
    //----9.  retrieving  WMU_4He datas ---------------
   int npoints_WMU_4He[TELNUM][CSINUM];
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       npoints_WMU_4He[i][j]=0;
     }
   }
   double WMU_4He_voltage[TELNUM][CSINUM][100];
   double errWMU_4He_voltage[TELNUM][CSINUM][100];
   double WMU_4He_energy[TELNUM][CSINUM][100];
   double errWMU_4He_energy[TELNUM][CSINUM][100];
   while(FileInWMU_4He.is_open() && !FileInWMU_4He.eof())
   {
     std::string LineRead;
     std::getline(FileInWMU_4He, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int csinum;
     
     LineStream >> telnum >> csinum;
     LineStream >> WMU_4He_voltage[telnum][csinum][npoints_WMU_4He[telnum][csinum]] >> errWMU_4He_voltage[telnum][csinum][npoints_WMU_4He[telnum][csinum]] >> WMU_4He_energy[telnum][csinum][npoints_WMU_4He[telnum][csinum]] >> errWMU_4He_energy[telnum][csinum][npoints_WMU_4He[telnum][csinum]] ;
     
     npoints_WMU_4He[telnum][csinum]++;
   
   }
     
   
   
   //--- creating graphs ----------------
   TGraphErrors * data_HiRA_proton[TELNUM][CSINUM];
   TGraphErrors * data_HiRA_deuteron[TELNUM][CSINUM];
   TGraphErrors * data_HiRA_4He[TELNUM][CSINUM];
   TGraphErrors * data_HiRA_proton1[TELNUM][CSINUM];
   TGraphErrors * data_HiRA_deuteron1[TELNUM][CSINUM];
   TGraphErrors * data_HiRA_4He1[TELNUM][CSINUM];
   TGraphErrors * data_WMU_proton[TELNUM][CSINUM];
   TGraphErrors * data_WMU_deuteron[TELNUM][CSINUM];
   TGraphErrors * data_WMU_4He[TELNUM][CSINUM];
   
   TMultiGraph * data_total[TELNUM][CSINUM];     
   
   TLegend * legend[TELNUM][CSINUM];
   
   for(int i=0; i<TELNUM; i++)
   {
     if(i!=5) continue;
     
     for(int j=0; j<CSINUM; j++)
     {
       
       data_HiRA_proton[i][j]  = new TGraphErrors(npoints_HiRA_proton[i][j], HiRA_proton_energy[i][j], HiRA_proton_voltage[i][j], errHiRA_proton_energy[i][j], errHiRA_proton_voltage[i][j]);
       data_HiRA_deuteron[i][j]  = new TGraphErrors(npoints_HiRA_deuteron[i][j], HiRA_deuteron_energy[i][j], HiRA_deuteron_voltage[i][j], errHiRA_deuteron_energy[i][j], errHiRA_deuteron_voltage[i][j]);
       data_HiRA_4He[i][j]  = new TGraphErrors(npoints_HiRA_4He[i][j], HiRA_4He_energy[i][j], HiRA_4He_voltage[i][j], errHiRA_4He_energy[i][j], errHiRA_4He_voltage[i][j]);
       
       data_HiRA_proton1[i][j]  = new TGraphErrors(npoints_HiRA_proton1[i][j], HiRA_proton1_energy[i][j], HiRA_proton1_voltage[i][j], errHiRA_proton1_energy[i][j], errHiRA_proton1_voltage[i][j]);
       data_HiRA_deuteron1[i][j]  = new TGraphErrors(npoints_HiRA_deuteron1[i][j], HiRA_deuteron1_energy[i][j], HiRA_deuteron1_voltage[i][j], errHiRA_deuteron1_energy[i][j], errHiRA_deuteron1_voltage[i][j]);
       data_HiRA_4He1[i][j]  = new TGraphErrors(npoints_HiRA_4He1[i][j], HiRA_4He1_energy[i][j], HiRA_4He1_voltage[i][j], errHiRA_4He1_energy[i][j], errHiRA_4He1_voltage[i][j]);
              
       data_WMU_proton[i][j]  = new TGraphErrors(npoints_WMU_proton[i][j], WMU_proton_energy[i][j], WMU_proton_voltage[i][j], errWMU_proton_energy[i][j], errWMU_proton_voltage[i][j]);
       data_WMU_deuteron[i][j]  = new TGraphErrors(npoints_WMU_deuteron[i][j], WMU_deuteron_energy[i][j], WMU_deuteron_voltage[i][j], errWMU_deuteron_energy[i][j], errWMU_deuteron_voltage[i][j]);
       data_WMU_4He[i][j]  = new TGraphErrors(npoints_WMU_4He[i][j], WMU_4He_energy[i][j], WMU_4He_voltage[i][j], errWMU_4He_energy[i][j], errWMU_4He_voltage[i][j]);
              
       
       data_HiRA_proton[i][j]->SetMarkerStyle(30);  
       data_HiRA_proton[i][j]->SetMarkerColor(2);
       data_HiRA_proton[i][j]->SetMarkerSize(1.2);
       data_HiRA_proton1[i][j]->SetMarkerStyle(30);  
       data_HiRA_proton1[i][j]->SetMarkerColor(2);
       data_HiRA_proton1[i][j]->SetMarkerSize(1.2);
       data_WMU_proton[i][j]->SetMarkerStyle(30);  
       data_WMU_proton[i][j]->SetMarkerColor(4);
       data_WMU_proton[i][j]->SetMarkerSize(1.2);
       
       data_HiRA_deuteron[i][j]->SetMarkerStyle(25);  
       data_HiRA_deuteron[i][j]->SetMarkerColor(2);
       data_HiRA_deuteron[i][j]->SetMarkerSize(1.2);
       data_HiRA_deuteron1[i][j]->SetMarkerStyle(25);  
       data_HiRA_deuteron1[i][j]->SetMarkerColor(2);
       data_HiRA_deuteron1[i][j]->SetMarkerSize(1.2);
       data_WMU_deuteron[i][j]->SetMarkerStyle(25);  
       data_WMU_deuteron[i][j]->SetMarkerColor(4);
       data_WMU_deuteron[i][j]->SetMarkerSize(1.2);
       
       data_HiRA_4He[i][j]->SetMarkerStyle(24);  
       data_HiRA_4He[i][j]->SetMarkerColor(2);
       data_HiRA_4He[i][j]->SetMarkerSize(1.2);
       data_HiRA_4He1[i][j]->SetMarkerStyle(24);  
       data_HiRA_4He1[i][j]->SetMarkerColor(2);
       data_HiRA_4He1[i][j]->SetMarkerSize(1.2);
       data_WMU_4He[i][j]->SetMarkerStyle(24);  
       data_WMU_4He[i][j]->SetMarkerColor(4);
       data_WMU_4He[i][j]->SetMarkerSize(1.2);
           
       data_total[i][j]= new TMultiGraph();
     //  data_total[i][j]->Add(data_HiRA_proton[i][j]);
      // data_total[i][j]->Add(data_HiRA_proton1[i][j]);
     //  data_total[i][j]->Add(data_WMU_proton[i][j]);
        
     //  data_total[i][j]->Add(data_HiRA_deuteron[i][j]);
     //  data_total[i][j]->Add(data_HiRA_deuteron1[i][j]);
     //  data_total[i][j]->Add(data_WMU_deuteron[i][j]);
        
     //  data_total[i][j]->Add(data_HiRA_4He[i][j]);      
     //  data_total[i][j]->Add(data_HiRA_4He1[i][j]);      
     //  data_total[i][j]->Add(data_WMU_4He[i][j]);    
       
                    
       legend[i][j]= new TLegend(0.15, 0.65, 0.35, 0.85);
       legend[i][j]->AddEntry(data_HiRA_proton[i][j], "HiRA_proton", "P");
       legend[i][j]->AddEntry(data_WMU_proton[i][j], "WMU_proton", "P");
       legend[i][j]->AddEntry(data_HiRA_deuteron[i][j], "HiRA_deuteron", "P");
       legend[i][j]->AddEntry(data_WMU_deuteron[i][j], "WMU_deuteron", "P");
       legend[i][j]->AddEntry(data_HiRA_4He[i][j], "HiRA_4He", "P");             
       legend[i][j]->AddEntry(data_WMU_4He[i][j], "WMU_4He", "P");       
            
     }
   }
   
   TCanvas *c1=new TCanvas("c1","", 1200, 800);
   
   for(int i=0; i<TELNUM; i++)
   {
     if(i!=5) continue;
     
     for(int j=0; j<CSINUM; j++)
     {
   //  gPad->SetLogy(1);
     
       data_total[i][j]->Draw("APL");
       data_total[i][j]->SetTitle(Form("Graph_CsIVoltage_LISEEnergy%02d_%02d", i, j));
       data_total[i][j]->GetXaxis()->SetTitle("LISE Energy (MeV)");
       data_total[i][j]->GetXaxis()->CenterTitle(true);
       data_total[i][j]->GetXaxis()->SetTitleSize(0.05);
       data_total[i][j]->GetXaxis()->SetLabelSize(0.05);
       data_total[i][j]->GetYaxis()->SetTitle("CsIVoltage (V)");
       data_total[i][j]->GetYaxis()->CenterTitle(true);
       data_total[i][j]->GetYaxis()->SetTitleSize(0.05);
       data_total[i][j]->GetYaxis()->SetLabelSize(0.05);
     //  data_total[i][j]->GetXaxis()->SetRangeUser(0,20);
     //  data_total[i][j]->GetYaxis()->SetRangeUser(0,0.2);
       legend[i][j]->Draw("SAME");
                                
       gPad->Modified();
       gPad->Update();
       
       c1->Print(Form("figures/CompareWithWMUData_Tel%02d_CsI%02d.png",i, j));     
     }
   }
   
   
   
   
   
   
   
   
   
   


}
