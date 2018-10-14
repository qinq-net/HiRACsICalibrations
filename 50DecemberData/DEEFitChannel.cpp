
void DEEFitChannel()
{
   const int Z=1;
   const int A=1;
   const int TELNUM=12;
   const int CSINUM=4;
   TMultiGraph  * Graph[TELNUM][CSINUM];
   TLegend * legend[TELNUM][CSINUM];


   ofstream FileOut[5];
   FileOut[0].open("FitResult/FitParameters_proton.dat");
   FileOut[1].open("FitResult/FitParameters_deuteron.dat");
   FileOut[2].open("FitResult/FitParameters_triton.dat");
   FileOut[3].open("FitResult/FitParameters_3He.dat");
   FileOut[4].open("FitResult/FitParameters_4He.dat");

   FileOut[0] << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<<setw(10)<< "Z" <<"  "<<setw(10)<<"A"<<"  "<< setw(10) <<"Fit Formula"<<"  "<<setw(10) << "Par0" <<"  "<<setw(10)<<"Par1"<<"  "<<setw(10)<<"Par2\n";




/*

    FileOut[1] << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<< setw(10) << "Par0" <<"  "<<setw(10)<<"errPar0"<<"  "<<setw(10)<<"Par1" <<"  "<<setw(10)<<"errPar1\n";
   FileOut[2] << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<< setw(10) << "Par0" <<"  "<<setw(10)<<"errPar0"<<"  "<<setw(10)<<"Par1" <<"  "<<setw(10)<<"errPar1\n";
   FileOut[3] << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<< setw(10) << "Par0" <<"  "<<setw(10)<<"errPar0"<<"  "<<setw(10)<<"Par1" <<"  "<<setw(10)<<"errPar1\n";
   FileOut[4] << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<< setw(10) << "Par0" <<"  "<<setw(10)<<"errPar0"<<"  "<<setw(10)<<"Par1" <<"  "<<setw(10)<<"errPar1\n";


*/

   //---------------------------------------------------------
   // ***
   // ***  For protons
   // ***
   //---------------------------------------------------------

   //------- read datas from input files -----------------------
   Int_t NFiles_proton=1;
   std::string * FileIn_name_proton[NFiles_proton];
   FileIn_name_proton[0] = new std::string("calibrations/HiRA_CsI_DEEPointsChannels_Z01_A01.dat");

/*
   FileIn_name_proton[0] = new std::string("datfile/WMUdata_Z01_A01.dat");   // WMU data
   FileIn_name_proton[1] = new std::string("datfile/HiRA_CsI_DEEFullEnergy_Z01_A01.dat"); //DEE points
   FileIn_name_proton[2] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_2013_2037_40Ca39AMeV_gain 200.dat"); // kinematics ponits
   FileIn_name_proton[3] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_2312_2312_40Ca56AMeV_gain 170.dat"); // kinematics ponits
   FileIn_name_proton[4] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_4034_4037_48Ca28AMeV_gain 170.dat"); // kinematics ponits
   FileIn_name_proton[5] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_4332_4332_48Ca56AMeV_gain 170.dat"); // kinematics ponits
   FileIn_name_proton[6] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_4577_4584_48Ca28AMeV_gain 170.dat"); // kinematics ponits
   FileIn_name_proton[7] = new std::string("datfile/Corrected_HiRA_CsIKinimatics_4585_4589_48Ca56AMeV_gain 170.dat"); // kinematics ponits
   FileIn_name_proton[8] = new std::string("datfile/HiRA_CsI_PunchThrough_Z01_A01.dat");  // punch through points
 //  FileIn_name_proton[9] = new std::string("datfile/HiRA_KinematicPoints_CH2_1.2Tm_1H_12C_Z01_A01.dat");

*/

   //-------- definition of TGraphErrors, TMultiGraph, TLengend -----------------------------------------
   TGraphErrors * DataProton[TELNUM][CSINUM][NFiles_proton];

   //---- definition of variables to read the input data files ------------------------------------------
   int NPoints_proton[TELNUM][CSINUM][NFiles_proton];
   double CsIV_proton[TELNUM][CSINUM][NFiles_proton][100];
   double err_CsIV_proton[TELNUM][CSINUM][NFiles_proton][100];
   double Energy_proton[TELNUM][CSINUM][NFiles_proton][100];
   double err_Energy_proton[TELNUM][CSINUM][NFiles_proton][100];

   //------ definition of the number of data points for each input file ---------------------------------
   for(int FileNum=0; FileNum<NFiles_proton; FileNum++)
   {
     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         NPoints_proton[i][j][FileNum]=0;
       }
     }
     ifstream FileIn_proton(FileIn_name_proton[FileNum]->c_str());

     if(!FileIn_proton.is_open())
     {
       printf("Error: file%s not found\n", FileIn_name_proton[FileNum]->c_str());
       return;
     }

     //------ Loop, to read each input data file --------------------------------
     while(!FileIn_proton.eof())
     {
       std::string LineRead;
       std::getline(FileIn_proton, LineRead);

       if(LineRead.empty()) continue;
       if(LineRead.find('*')==0) continue;

       std::istringstream LineStream(LineRead);

       int telnum;
       int csinum;

       LineStream >> telnum >> csinum;
       LineStream >> CsIV_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]] >> err_CsIV_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]] >> Energy_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]] >> err_Energy_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]] ;

       if(err_Energy_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]]==0) continue;
       NPoints_proton[telnum][csinum][FileNum]++;
     }

     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         if(NPoints_proton[i][j][FileNum]!=0)
         {
           DataProton[i][j][FileNum] = new TGraphErrors(NPoints_proton[i][j][FileNum], Energy_proton[i][j][FileNum], CsIV_proton[i][j][FileNum], err_Energy_proton[i][j][FileNum], err_CsIV_proton[i][j][FileNum]);
      //   DataProton[i][j][FileNum] = new TGraphErrors(NPoints_proton[i][j][FileNum], CsIV_proton[i][j][FileNum], Energy_proton[i][j][FileNum], err_CsIV_proton[i][j][FileNum], err_Energy_proton[i][j][FileNum]);
           DataProton[i][j][FileNum]->SetMarkerColor(1); // black marker for protons
           DataProton[i][j][FileNum]->SetMarkerStyle(20+FileNum);
         }
         else DataProton[i][j][FileNum]=0;
       }
     }
     FileIn_proton.close();
   }


 /*
    //-----------------------------------------------------------------------------------------------------------------------------------
   // ***
   // ***  For deuterons
   // ***
   //------------------------------------------------------------------------------------------------------------------------------------

   Int_t NFiles_deuteron=3;
   std::string * FileIn_name_deuteron[NFiles_deuteron];
   FileIn_name_deuteron[0] = new std::string("datfile/WMUdata_Z01_A02.dat");   // WMU data
   FileIn_name_deuteron[1] = new std::string("datfile/HiRA_CsI_DEEFullEnergy_Z01_A02.dat"); //DEE points
   FileIn_name_deuteron[2] = new std::string("datfile/HiRA_CsI_PunchThrough_Z01_A02.dat");  // punch through points

   //-------- definition of TGraphErrors, TMultiGraph, TLengend -----------------------------------------
   TGraphErrors * DataDeuteron[TELNUM][CSINUM][NFiles_deuteron];

   //---- definition of variables to read the input data files ------------------------------------------
   int NPoints_deuteron[TELNUM][CSINUM][NFiles_deuteron];
   double CsIV_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];
   double err_CsIV_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];
   double Energy_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];
   double err_Energy_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];

   //------ definition of the number of data points for each input file ---------------------------------
   for(int FileNum=0; FileNum<NFiles_deuteron; FileNum++)
   {
     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         NPoints_deuteron[i][j][FileNum]=0;
       }
     }
     ifstream FileIn_deuteron(FileIn_name_deuteron[FileNum]->c_str());

     if(!FileIn_deuteron.is_open())
     {
       printf("Error: file%s not found\n", FileIn_name_deuteron[FileNum]->c_str());
       return;
     }

     //------ Loop, to read each input data file --------------------------------
     while(!FileIn_deuteron.eof())
     {
       std::string LineRead;
       std::getline(FileIn_deuteron, LineRead);

       if(LineRead.empty()) continue;
       if(LineRead.find('*')==0) continue;

       std::istringstream LineStream(LineRead);

       int telnum;
       int csinum;

       LineStream >> telnum >> csinum;
       LineStream >> CsIV_deuteron[telnum][csinum][FileNum][NPoints_deuteron[telnum][csinum][FileNum]] >> err_CsIV_deuteron[telnum][csinum][FileNum][NPoints_deuteron[telnum][csinum][FileNum]] >> Energy_deuteron[telnum][csinum][FileNum][NPoints_deuteron[telnum][csinum][FileNum]] >> err_Energy_deuteron[telnum][csinum][FileNum][NPoints_deuteron[telnum][csinum][FileNum]] ;

       if(err_Energy_deuteron[telnum][csinum][FileNum][NPoints_deuteron[telnum][csinum][FileNum]]==0) continue;
       NPoints_deuteron[telnum][csinum][FileNum]++;
     }

     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         if(NPoints_deuteron[i][j][FileNum]!=0)
         {
           DataDeuteron[i][j][FileNum] = new TGraphErrors(NPoints_deuteron[i][j][FileNum], Energy_deuteron[i][j][FileNum], CsIV_deuteron[i][j][FileNum], err_Energy_deuteron[i][j][FileNum], err_CsIV_deuteron[i][j][FileNum]);
           DataDeuteron[i][j][FileNum]->SetMarkerColor(3); // green marker for deuterons
           DataDeuteron[i][j][FileNum]->SetMarkerStyle(20+FileNum);
         }
         else DataDeuteron[i][j][FileNum]=0;
       }
     }
     FileIn_deuteron.close();
   }




    //---------------------------------------------------------------------------------------------------------------------------------
   // ***
   // ***  For tritons
   // ***
   //----------------------------------------------------------------------------------------------------------------------------------
   Int_t NFiles_triton=2;
   std::string * FileIn_name_triton[NFiles_triton];
   FileIn_name_triton[0] = new std::string("datfile/HiRA_CsI_DEEFullEnergy_Z01_A03.dat"); //DEE points
   FileIn_name_triton[1] = new std::string("datfile/HiRA_CsI_PunchThrough_Z01_A03.dat");  // punch through points

   //-------- definition of TGraphErrors, TMultiGraph, TLengend -----------------------------------------
   TGraphErrors * DataTriton[TELNUM][CSINUM][NFiles_triton];

   //---- definition of variables to read the input data files ------------------------------------------
   int NPoints_triton[TELNUM][CSINUM][NFiles_triton];
   double CsIV_triton[TELNUM][CSINUM][NFiles_triton][100];
   double err_CsIV_triton[TELNUM][CSINUM][NFiles_triton][100];
   double Energy_triton[TELNUM][CSINUM][NFiles_triton][100];
   double err_Energy_triton[TELNUM][CSINUM][NFiles_triton][100];

   //------ definition of the number of data points for each input file ---------------------------------
   for(int FileNum=0; FileNum<NFiles_triton; FileNum++)
   {
     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         NPoints_triton[i][j][FileNum]=0;
       }
     }
     ifstream FileIn_triton(FileIn_name_triton[FileNum]->c_str());

     if(!FileIn_triton.is_open())
     {
       printf("Error: file%s not found\n", FileIn_name_triton[FileNum]->c_str());
       return;
     }

     //------ Loop, to read each input data file --------------------------------
     while(!FileIn_triton.eof())
     {
       std::string LineRead;
       std::getline(FileIn_triton, LineRead);

       if(LineRead.empty()) continue;
       if(LineRead.find('*')==0) continue;

       std::istringstream LineStream(LineRead);

       int telnum;
       int csinum;

       LineStream >> telnum >> csinum;
       LineStream >> CsIV_triton[telnum][csinum][FileNum][NPoints_triton[telnum][csinum][FileNum]] >> err_CsIV_triton[telnum][csinum][FileNum][NPoints_triton[telnum][csinum][FileNum]] >> Energy_triton[telnum][csinum][FileNum][NPoints_triton[telnum][csinum][FileNum]] >> err_Energy_triton[telnum][csinum][FileNum][NPoints_triton[telnum][csinum][FileNum]] ;

       if(err_Energy_triton[telnum][csinum][FileNum][NPoints_triton[telnum][csinum][FileNum]]==0) continue;
       NPoints_triton[telnum][csinum][FileNum]++;
     }

     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         if(NPoints_triton[i][j][FileNum]!=0)
         {
           DataTriton[i][j][FileNum] = new TGraphErrors(NPoints_triton[i][j][FileNum], Energy_triton[i][j][FileNum], CsIV_triton[i][j][FileNum], err_Energy_triton[i][j][FileNum], err_CsIV_triton[i][j][FileNum]);
           DataTriton[i][j][FileNum]->SetMarkerColor(4); // blue marker for tritons
           DataTriton[i][j][FileNum]->SetMarkerStyle(20+FileNum);
         }
         else DataTriton[i][j][FileNum]=0;
       }
     }
     FileIn_triton.close();
   }



    //-------------------------------------------------------------------------------------------------------------------------------
    // ***
    // ***  For 3He
    // ***
   //-------------------------------------------------------------------------------------------------------------------------------
   Int_t NFiles_3He=1;
   std::string * FileIn_name_3He[NFiles_3He];
   FileIn_name_3He[0] = new std::string("datfile/HiRA_CsI_DEEFullEnergy_Z02_A03.dat"); //DEE points

   //-------- definition of TGraphErrors, TMultiGraph, TLengend -----------------------------------------
   TGraphErrors * Data3He[TELNUM][CSINUM][NFiles_3He];

   //---- definition of variables to read the input data files ------------------------------------------
   int NPoints_3He[TELNUM][CSINUM][NFiles_3He];
   double CsIV_3He[TELNUM][CSINUM][NFiles_3He][100];
   double err_CsIV_3He[TELNUM][CSINUM][NFiles_3He][100];
   double Energy_3He[TELNUM][CSINUM][NFiles_3He][100];
   double err_Energy_3He[TELNUM][CSINUM][NFiles_3He][100];

   //------ definition of the number of data points for each input file ---------------------------------
   for(int FileNum=0; FileNum<NFiles_3He; FileNum++)
   {
     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         NPoints_3He[i][j][FileNum]=0;
       }
     }
     ifstream FileIn_3He(FileIn_name_3He[FileNum]->c_str());

     if(!FileIn_3He.is_open())
     {
       printf("Error: file%s not found\n", FileIn_name_3He[FileNum]->c_str());
       return;
     }

     //------ Loop, to read each input data file --------------------------------
     while(!FileIn_3He.eof())
     {
       std::string LineRead;
       std::getline(FileIn_3He, LineRead);

       if(LineRead.empty()) continue;
       if(LineRead.find('*')==0) continue;

       std::istringstream LineStream(LineRead);

       int telnum;
       int csinum;

       LineStream >> telnum >> csinum;
       LineStream >> CsIV_3He[telnum][csinum][FileNum][NPoints_3He[telnum][csinum][FileNum]] >> err_CsIV_3He[telnum][csinum][FileNum][NPoints_3He[telnum][csinum][FileNum]] >> Energy_3He[telnum][csinum][FileNum][NPoints_3He[telnum][csinum][FileNum]] >> err_Energy_3He[telnum][csinum][FileNum][NPoints_3He[telnum][csinum][FileNum]] ;

       if(err_Energy_3He[telnum][csinum][FileNum][NPoints_3He[telnum][csinum][FileNum]]==0) continue;
       NPoints_3He[telnum][csinum][FileNum]++;
     }

     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         if(NPoints_3He[i][j][FileNum]!=0)
         {
           Data3He[i][j][FileNum] = new TGraphErrors(NPoints_3He[i][j][FileNum], Energy_3He[i][j][FileNum], CsIV_3He[i][j][FileNum], err_Energy_3He[i][j][FileNum], err_CsIV_3He[i][j][FileNum]);
           Data3He[i][j][FileNum]->SetMarkerColor(6); // purple marker for 3Hes
           Data3He[i][j][FileNum]->SetMarkerStyle(20+FileNum);
         }
         else Data3He[i][j][FileNum]=0;
       }
     }
     FileIn_3He.close();
   }



   //-------------------------------------------------------------------------------------------------------------------------------
   // ***
   // ***  For 4He
   // ***
   //------------------------------------------------------------------------------------------------------------------------------
   Int_t NFiles_4He=2;
   std::string * FileIn_name_4He[NFiles_4He];
   FileIn_name_4He[0] = new std::string("datfile/WMUdata_Z02_A04.dat");   // WMU data
   FileIn_name_4He[1] = new std::string("datfile/HiRA_CsI_DEEFullEnergy_Z02_A04.dat"); //DEE points

   //-------- definition of TGraphErrors, TMultiGraph, TLengend -----------------------------------------
   TGraphErrors * Data4He[TELNUM][CSINUM][NFiles_4He];

   //---- definition of variables to read the input data files ------------------------------------------
   int NPoints_4He[TELNUM][CSINUM][NFiles_4He];
   double CsIV_4He[TELNUM][CSINUM][NFiles_4He][100];
   double err_CsIV_4He[TELNUM][CSINUM][NFiles_4He][100];
   double Energy_4He[TELNUM][CSINUM][NFiles_4He][100];
   double err_Energy_4He[TELNUM][CSINUM][NFiles_4He][100];

   //------ definition of the number of data points for each input file ---------------------------------
   for(int FileNum=0; FileNum<NFiles_4He; FileNum++)
   {
     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         NPoints_4He[i][j][FileNum]=0;
       }
     }
     ifstream FileIn_4He(FileIn_name_4He[FileNum]->c_str());

     if(!FileIn_4He.is_open())
     {
       printf("Error: file%s not found\n", FileIn_name_4He[FileNum]->c_str());
       return;
     }

     //------ Loop, to read each input data file --------------------------------
     while(!FileIn_4He.eof())
     {
       std::string LineRead;
       std::getline(FileIn_4He, LineRead);

       if(LineRead.empty()) continue;
       if(LineRead.find('*')==0) continue;

       std::istringstream LineStream(LineRead);

       int telnum;
       int csinum;

       LineStream >> telnum >> csinum;
       LineStream >> CsIV_4He[telnum][csinum][FileNum][NPoints_4He[telnum][csinum][FileNum]] >> err_CsIV_4He[telnum][csinum][FileNum][NPoints_4He[telnum][csinum][FileNum]] >> Energy_4He[telnum][csinum][FileNum][NPoints_4He[telnum][csinum][FileNum]] >> err_Energy_4He[telnum][csinum][FileNum][NPoints_4He[telnum][csinum][FileNum]] ;

       if(err_Energy_4He[telnum][csinum][FileNum][NPoints_4He[telnum][csinum][FileNum]]==0) continue;
       NPoints_4He[telnum][csinum][FileNum]++;
     }

     for(int i=0; i<TELNUM; i++)
     {
       for(int j=0; j<CSINUM; j++)
       {
         if(NPoints_4He[i][j][FileNum]!=0)
         {
           Data4He[i][j][FileNum] = new TGraphErrors(NPoints_4He[i][j][FileNum], Energy_4He[i][j][FileNum], CsIV_4He[i][j][FileNum], err_Energy_4He[i][j][FileNum], err_CsIV_4He[i][j][FileNum]);
           Data4He[i][j][FileNum]->SetMarkerColor(7); // lakeblue marker for 4Hes
           Data4He[i][j][FileNum]->SetMarkerStyle(20+FileNum);
         }
         else Data4He[i][j][FileNum]=0;
       }
     }
     FileIn_4He.close();
   }
  */

   //----- definition of graphs for fitting -----------------------------
   TMultiGraph * graph_proton[TELNUM][CSINUM];
   TMultiGraph * graph_deuteron[TELNUM][CSINUM];
   TMultiGraph * graph_triton[TELNUM][CSINUM];
   TMultiGraph * graph_3He[TELNUM][CSINUM];
   TMultiGraph * graph_4He[TELNUM][CSINUM];


   //-------- to add graphs and legends ----------------------------------------
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
       legend[i][j] = new TLegend(0.11, 0.60, 0.50, 0.87);
       legend[i][j]->SetBorderSize(0);
       Graph[i][j] = new TMultiGraph();
 /*
       //---- add 4He data -------------------------------------
       graph_4He[i][j] = new TMultiGraph();
       for(int FileNum=0; FileNum<NFiles_4He; FileNum++)
       {
         if(Data4He[i][j][FileNum]!=0)
         {
           legend[i][j]->AddEntry(Data4He[i][j][FileNum], FileIn_name_4He[FileNum]->substr(FileIn_name_4He[FileNum]->find_last_of("/")+1,FileIn_name_4He[FileNum]->find_last_of(".")-FileIn_name_4He[FileNum]->find_last_of("/")-1).c_str(), "P");

           graph_4He[i][j]->Add(Data4He[i][j][FileNum]);
           Graph[i][j]->Add(Data4He[i][j][FileNum]);
         }
       }

       //---- add 3He data -------------------------------------
       graph_3He[i][j] = new TMultiGraph();
       for(int FileNum=0; FileNum<NFiles_3He; FileNum++)
       {
         if(Data3He[i][j][FileNum]!=0)
         {
           legend[i][j]->AddEntry(Data3He[i][j][FileNum], FileIn_name_3He[FileNum]->substr(FileIn_name_3He[FileNum]->find_last_of("/")+1,FileIn_name_3He[FileNum]->find_last_of(".")-FileIn_name_3He[FileNum]->find_last_of("/")-1).c_str(), "P");

           graph_3He[i][j]->Add(Data3He[i][j][FileNum]);
           Graph[i][j]->Add(Data3He[i][j][FileNum]);
         }
       }


       //---- add triton data -------------------------------------
       graph_triton[i][j] = new TMultiGraph();
       for(int FileNum=0; FileNum<NFiles_triton; FileNum++)
       {
         if(DataTriton[i][j][FileNum]!=0)
         {
           legend[i][j]->AddEntry(DataTriton[i][j][FileNum], FileIn_name_triton[FileNum]->substr(FileIn_name_triton[FileNum]->find_last_of("/")+1,FileIn_name_triton[FileNum]->find_last_of(".")-FileIn_name_triton[FileNum]->find_last_of("/")-1).c_str(), "P");

           graph_triton[i][j]->Add(DataTriton[i][j][FileNum]);
           Graph[i][j]->Add(DataTriton[i][j][FileNum]);
         }
       }

       //---- add deuteron data -----------------------------------
       graph_deuteron[i][j] = new TMultiGraph();
       for(int FileNum=0; FileNum<NFiles_deuteron; FileNum++)
       {
         if(DataDeuteron[i][j][FileNum]!=0)
         {
           legend[i][j]->AddEntry(DataDeuteron[i][j][FileNum], FileIn_name_deuteron[FileNum]->substr(FileIn_name_deuteron[FileNum]->find_last_of("/")+1,FileIn_name_deuteron[FileNum]->find_last_of(".")-FileIn_name_deuteron[FileNum]->find_last_of("/")-1).c_str(), "P");

           graph_deuteron[i][j]->Add(DataDeuteron[i][j][FileNum]);
           Graph[i][j]->Add(DataDeuteron[i][j][FileNum]);
         }
       }
*/

       //------- add proton datas ------------------------
       graph_proton[i][j] = new TMultiGraph();
       for(int FileNum=0; FileNum<NFiles_proton; FileNum++)
       {
         if(DataProton[i][j][FileNum]!=0)
         {
           legend[i][j]->AddEntry(DataProton[i][j][FileNum], FileIn_name_proton[FileNum]->substr(FileIn_name_proton[FileNum]->find_last_of("/")+1,FileIn_name_proton[FileNum]->find_last_of(".")-FileIn_name_proton[FileNum]->find_last_of("/")-1).c_str(), "P");

           graph_proton[i][j]->Add(DataProton[i][j][FileNum]);
           Graph[i][j]->Add(DataProton[i][j][FileNum]);
         }
         else graph_proton[i][j]=0;
       }






     }
   }


   //---- to draw graphs and fit ----------------------------
   TCanvas * c1 = new TCanvas("c1", "", 1200, 800);
   for(int i=0; i<TELNUM; i++)
   {
     for(int j=0; j<CSINUM; j++)
     {
      if(graph_proton[i][j]==0) continue;
      //---- creating graphs ----------------------------------
      Graph[i][j]->SetName(Form("Graph_CsIVoltgae_LISEEnergy%02d_%02d", i, j));
      Graph[i][j]->SetTitle(Form("Tel%02d_CsI%02d Calibration", i, j));
      Graph[i][j]->Draw("APE");
      Graph[i][j]->GetXaxis()->SetTitle("CsIVoltage (Channel)");
      Graph[i][j]->GetXaxis()->CenterTitle(true);
      Graph[i][j]->GetXaxis()->SetTitleSize(0.05);
      Graph[i][j]->GetXaxis()->SetLabelSize(0.05);
      Graph[i][j]->GetYaxis()->SetTitle("LISEEnergy (MeV)");
      Graph[i][j]->GetYaxis()->CenterTitle(true);
      Graph[i][j]->GetYaxis()->SetTitleSize(0.05);
      Graph[i][j]->GetYaxis()->SetLabelSize(0.05);
      legend[i][j]->Draw("SAME");

      //----- fit for protons -------------------------------------------------------------
      TF1 * fit_proton=new TF1(Form("fit_proton%02d_%02d", i,j),"[0]+[1]*x^{[2]}",0, 100);
      fit_proton->SetParameters(1,1,0.01);
  //  TF1 * fit_proton=new TF1(Form("fit_proton%02d_%02d", i,j),"([0]+[1]*x)^{[2]}",0, 1000);
  //  TF1 * fit_proton=new TF1(Form("fit_proton%02d_%02d", i,j),"[0]*x+[1]*(exp(-[2]*x)-1)",0, 1000);
  //  fit_proton->SetParameters(3,-100,0.01);
      graph_proton[i][j]->Fit(fit_proton,"RC+");
      fit_proton->Draw("SAME");
      fit_proton->SetLineColor(1);
      double par0_proton = fit_proton->GetParameter(0);
      double par1_proton = fit_proton->GetParameter(1);
      double par2_proton = fit_proton->GetParameter(2);
      FileOut[0] << setw(5) << i <<"  "<< setw(10) << j <<"  "<< setw(10) << Z <<"  "<<setw(10)<< A <<"  "<< setw(10) << "([0]+[1]*x)^{[2]}" <<"  "<<setw(10)<< par0_proton <<" "<<setw(10)<< par1_proton <<"  "<<setw(10) << par2_proton << endl;

  /*
      //----- fit for deuterons -------------------------------------------------------------
      TF1 * fit_deuteron=new TF1(Form("fit_deuteron%02d_%02d", i,j),"[0]*x^{[1]}",0, 320);
      fit_deuteron->SetParameters(0.003,1.2);
      graph_deuteron[i][j]->Fit(fit_deuteron,"RC+");
      fit_deuteron->Draw("SAME");
      fit_deuteron->SetLineColor(3);
      double par0_deuteron = fit_deuteron->GetParameter(0);
      double err_par0_deuteron = fit_deuteron->GetParError(0);
      double par1_deuteron = fit_deuteron->GetParameter(1);
      double err_par1_deuteron = fit_deuteron->GetParError(1);
      FileOut[1] << setw(5) << i <<"  "<< setw(10) << j <<"  "<< setw(10) << par0_deuteron <<"  "<<setw(10)<< err_par0_deuteron <<" "<<setw(10)<< par1_deuteron <<"  "<<setw(10) << err_par1_deuteron << endl;


      //----- fit for tritons -------------------------------------------------------------
      TF1 * fit_triton=new TF1(Form("fit_triton%02d_%02d", i,j),"[0]*x^{[1]}",0, 320);
      fit_triton->SetParameters(0.003,1.2);
      graph_triton[i][j]->Fit(fit_triton,"RC+");
      fit_triton->Draw("SAME");
      fit_triton->SetLineColor(4);
      double par0_triton = fit_triton->GetParameter(0);
      double err_par0_triton = fit_triton->GetParError(0);
      double par1_triton = fit_triton->GetParameter(1);
      double err_par1_triton = fit_triton->GetParError(1);
      FileOut[2] << setw(5) << i <<"  "<< setw(10) << j <<"  "<< setw(10) << par0_triton <<"  "<<setw(10)<< err_par0_triton <<" "<<setw(10)<< par1_triton <<"  "<<setw(10) << err_par1_triton << endl;


      //----- fit for 3Hes -------------------------------------------------------------
      TF1 * fit_3He=new TF1(Form("fit_3He%02d_%02d", i,j),"[0]*x^{[1]}",0, 320);
      fit_3He->SetParameters(0.003,1.2);
      graph_3He[i][j]->Fit(fit_3He,"RC+");
      fit_3He->Draw("SAME");
      fit_3He->SetLineColor(6);
      double par0_3He = fit_3He->GetParameter(0);
      double err_par0_3He = fit_3He->GetParError(0);
      double par1_3He = fit_3He->GetParameter(1);
      double err_par1_3He = fit_3He->GetParError(1);
      FileOut[3] << setw(5) << i <<"  "<< setw(10) << j <<"  "<< setw(10) << par0_3He <<"  "<<setw(10)<< err_par0_3He<<" "<<setw(10)<< par1_3He <<"  "<<setw(10) << err_par1_3He << endl;


      //----- fit for 4Hes -------------------------------------------------------------
      TF1 * fit_4He=new TF1(Form("fit_4He%02d_%02d", i,j),"[0]*x^{[1]}",0, 320);
      fit_4He->SetParameters(0.003,1.2);
      graph_4He[i][j]->Fit(fit_4He,"RC+");
      fit_4He->Draw("SAME");
      fit_4He->SetLineColor(7);
      double par0_4He = fit_4He->GetParameter(0);
      double err_par0_4He = fit_4He->GetParError(0);
      double par1_4He = fit_4He->GetParameter(1);
      double err_par1_4He = fit_4He->GetParError(1);
      FileOut[4] << setw(5) << i <<"  "<< setw(10) << j <<"  "<< setw(10) << par0_4He <<"  "<<setw(10)<< err_par0_4He<<" "<<setw(10)<< par1_4He <<"  "<<setw(10) << err_par1_4He<< endl;
 */


      c1->Print(Form("Fit/Tel%02d_CsI%02d Calibraion.png", i, j));
  //  c1->Print(Form("FitResult/Tel%02d_CsI%02d Calibraion.png", i, j));


      gPad->Modified();
      gPad->Update();
    //  getchar();
     }
   }




















}
