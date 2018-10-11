//definition of the simutaneously fitting formula
//this formula comes from Jerzy Lukasik
//email: jerzy.lukasik@ifj.edu.pl
double fitfunc(double *x, double *par)
{
  if(par[1]<=par[2])  // condition given by Lukasik
  {
    return -1;
  }

  // x[0]--E, x[1]--A
  if(x[1]==101 || x[1]==102 || x[1]==103) {
    int A = Int_t (x[1])%100;
    int Z = Int_t (x[1])/100;
    double squareterm = pow(x[0], 2)+par[1]*A*x[0];
    double linearterm = (x[0]+par[2]*A);
    double light = par[0]*squareterm/linearterm;
    return light;
  }
  return 0;
}

////////////////////////////////////////////////////////////////
///  definition of function to fit protons
double fit_proton (double *x, double *par)
{
  double squareterm = pow(x[0], 2)+par[1]*1*x[0];
  double linearterm = (x[0]+par[2]*1)/par[0];
  double light = squareterm/linearterm;
  return light;
}

////////////////////////////////////////////////////////////////
///  definition of function to fit deuterons
double fit_deuteron (double *x, double *par)
{
  double squareterm = pow(x[0], 2)+par[1]*2*x[0];
  double linearterm = (x[0]+par[2]*2)/par[0];
  double light = squareterm/linearterm;
  return light;
}

////////////////////////////////////////////////////////////////
///  definition of function to fit tritons
double fit_triton (double *x, double *par)
{
  double squareterm = pow(x[0], 2)+par[1]*3*x[0];
  double linearterm = (x[0]+par[2]*3)/par[0];
  double light = squareterm/linearterm;
  return light;
}


void PDTFit1()
{
   const int TELNUM=12;
   const int CSINUM=4;

   ofstream FileOut;
   FileOut.open("calibrations/pdtFitResult.dat");
   FileOut << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<< setw(10) << "Par0" <<"  "<<setw(10)<<"Par1"<<"  "<<setw(10)<<"Par2\n";

   /************************************************************************************************************
    *                                                                                                          *
    *                                         For protons                                                      *
    *                                                                                                          *
    ************************************************************************************************************/

     /////////////////////////////////////////////////////////////////////////////////////////
     ///   read datas from input files
     Int_t NFiles_proton=12;
     std::string * FileIn_name_proton[NFiles_proton];
     FileIn_name_proton[0] = new std::string("calibrations/WMUdata_Z01_A01.dat");   // WMU data
     FileIn_name_proton[1] = new std::string("calibrations/OmitLowDEEPoints_Z01_A01.dat"); //DEE points
     FileIn_name_proton[2] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_2013_2037_40Ca39.0AMeV_gain 200.dat"); // kinematics ponits
     FileIn_name_proton[3] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_2312_2312_40Ca56.6AMeV_gain 170.dat"); // kinematics ponits
     FileIn_name_proton[4] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_2825_2829_40Ca139.8AMeV_gain 130.dat"); // kinematics ponits
     FileIn_name_proton[5] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_4000_4005_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
     FileIn_name_proton[6] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_4021_4022_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
     FileIn_name_proton[7] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_4034_4037_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
     FileIn_name_proton[8] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_4332_4332_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
     FileIn_name_proton[9] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_4577_4584_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
     FileIn_name_proton[10] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_4585_4589_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
     FileIn_name_proton[11] = new std::string("calibrations/HiRA_CsI_PunchThrough_Z01_A01.dat");  // punch through points

     ////////////////////////////////////////////////////////////////////////////////////////////////
     ///   definition of TGraphErrors, TMultiGraph, TLengend
     TGraphErrors * DataProton [12][4][NFiles_proton];

     //////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of variables to read the input data files
     int NPoints_proton[TELNUM][CSINUM][NFiles_proton];
     double CsIV_proton[TELNUM][CSINUM][NFiles_proton][100];
     double err_CsIV_proton[TELNUM][CSINUM][NFiles_proton][100];
     double Energy_proton[TELNUM][CSINUM][NFiles_proton][100];
     double err_Energy_proton[TELNUM][CSINUM][NFiles_proton][100];
     double ZA_proton[TELNUM][CSINUM][NFiles_proton][100];

     /////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of the number of data points for each input file
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

       /////////////////////////////////////////////////////////////////////////////////////
       ///    Loop, to read each input data file
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
         LineStream >> CsIV_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]];
         LineStream >> err_CsIV_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]];
         LineStream >> Energy_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]];
         LineStream >> err_Energy_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]];

         ZA_proton[telnum][csinum][FileNum][NPoints_proton[telnum][csinum][FileNum]]=101;  // Z_proton= ZA_proton/100, A_proton

         NPoints_proton[telnum][csinum][FileNum]++;
       }

       for(int i=0; i<TELNUM; i++)
       {
         for(int j=0; j<CSINUM; j++)
         {
           if(NPoints_proton[i][j][FileNum]!=0)
           {
             DataProton[i][j][FileNum] = new TGraphErrors(NPoints_proton[i][j][FileNum], Energy_proton[i][j][FileNum], CsIV_proton[i][j][FileNum], err_Energy_proton[i][j][FileNum] ,err_CsIV_proton[i][j][FileNum]);
             DataProton[i][j][FileNum]->SetMarkerColor(1); // black marker for protons
             DataProton[i][j][FileNum]->SetLineColor(1);
             DataProton[i][j][FileNum]->SetMarkerStyle(20+FileNum);
           }
           else DataProton[i][j][FileNum]=0;
         }
       }
       FileIn_proton.close();
     }


     /************************************************************************************************************
      *                                                                                                          *
      *                                         For deutorons                                                    *
      *                                                                                                          *
      ************************************************************************************************************/

     Int_t NFiles_deuteron=3;
     std::string * FileIn_name_deuteron[NFiles_deuteron];
     FileIn_name_deuteron[0] = new std::string("calibrations/WMUdata_Z01_A02.dat");   // WMU data
     FileIn_name_deuteron[1] = new std::string("calibrations/OmitLowDEEPoints_Z01_A02.dat"); //DEE points
     FileIn_name_deuteron[2] = new std::string("calibrations/HiRA_CsI_PunchThrough_Z01_A02.dat");  // punch through points

     //////////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of TGraphErrors, TMultiGraph, TLengend
     TGraphErrors * DataDeuteron [12][4][NFiles_deuteron];

     ///////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of variables to read the input data files
     int NPoints_deuteron[TELNUM][CSINUM][NFiles_deuteron];
     double CsIV_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];
     double err_CsIV_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];
     double Energy_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];
     double err_Energy_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];
     double ZA_deuteron[TELNUM][CSINUM][NFiles_deuteron][100];


     ///////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of the number of data points for each input file
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

       ///////////////////////////////////////////////////////////////////////////////////////
       ///   Loop, to read each input data file
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

         ZA_deuteron[telnum][csinum][FileNum][NPoints_deuteron[telnum][csinum][FileNum]]=102;

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
             DataDeuteron[i][j][FileNum]->SetLineColor(3);
             DataDeuteron[i][j][FileNum]->SetMarkerStyle(20+FileNum);
           }
           else DataDeuteron[i][j][FileNum]=0;
         }
       }
       FileIn_deuteron.close();
     }


    /************************************************************************************************************
     *                                                                                                          *
     *                                         For tritons                                                      *
     *                                                                                                          *
     ************************************************************************************************************/
     Int_t NFiles_triton=2;
     std::string * FileIn_name_triton[NFiles_triton];
     FileIn_name_triton[0] = new std::string("calibrations/OmitLowDEEPoints_Z01_A03.dat"); //DEE points
     FileIn_name_triton[1] = new std::string("calibrations/HiRA_CsI_PunchThrough_Z01_A03.dat");  // punch through points

     //////////////////////////////////////////////////////////////////////////////////////////////
     /// definition of TGraphErrors, TMultiGraph, TLengend
     TGraphErrors * DataTriton[12][4][NFiles_triton];

     ////////////////////////////////////////////////////////////////////////////////////////////////////
     /// definition of variables to read the input data files

     int NPoints_triton[TELNUM][CSINUM][NFiles_triton];
     double CsIV_triton[TELNUM][CSINUM][NFiles_triton][100];
     double err_CsIV_triton[TELNUM][CSINUM][NFiles_triton][100];
     double Energy_triton[TELNUM][CSINUM][NFiles_triton][100];
     double err_Energy_triton[TELNUM][CSINUM][NFiles_triton][100];
     double ZA_triton[TELNUM][CSINUM][NFiles_triton][100];


     /////////////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of the number of data points for each input file

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

       ///////////////////////////////////////////////////////////////////////////////////////////////////
       ///  Loop, to read each input data file

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

         ZA_triton[telnum][csinum][FileNum][NPoints_triton[telnum][csinum][FileNum]]= 103;

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
             DataTriton[i][j][FileNum]->SetLineColor(4);
             DataTriton[i][j][FileNum]->SetMarkerStyle(20+FileNum);
           }
           else DataTriton[i][j][FileNum]=0;
         }
       }
       FileIn_triton.close();
     }

     ////////////////////////////////////////////////////////////////////////////////////////////////
     /// To create a multigraph to draw all the firt in the same cnavas
     TMultiGraph * multi[12][4];
     for(int i=0; i<12; i++)
     {
       for(int j=0; j<4; j++)
       {
         multi[i][j] = new TMultiGraph();
         ///////////////////////////////////////////////////////////////////////////
         ///   Add data for protons
         for(int FileNum=0; FileNum<NFiles_proton; FileNum++)
         {
           if(DataProton[i][j][FileNum]!=0)
           {
             multi[i][j]->Add(DataProton[i][j][FileNum]);
           }
         }
        ////////////////////////////////////////////////////////////////////////////
        ///  Add data for deuteron
         for(int FileNum=0; FileNum<NFiles_deuteron; FileNum++)
         {
           if(DataDeuteron[i][j][FileNum]!=0)
           {
             multi[i][j]->Add(DataDeuteron[i][j][FileNum]);
           }
         }
         ///////////////////////////////////////////////////////////////////////////
         ///   Add data for triton
         for(int FileNum=0; FileNum<NFiles_triton; FileNum++)
         {
           if(DataTriton[i][j][FileNum]!=0)
           {
             multi[i][j]->Add(DataTriton[i][j][FileNum]);
           }
         }
       }
     }


    //Making the dataset
    int PointsNum[12][4]={{0}};
    double CsIV[12][4][1000];
    double errCsIV[12][4][1000];
    double CsIE[12][4][1000];
    double errCsIE[12][4][1000];
    double ZA[12][4][1000];

    //////////////////////////////////////////////////////////////////////////////////////
    //// put all the dataset together in one array, and then fit with 2D Graph
    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        ////////////////////////////////////////////////////////////////////////////
        ///  add proton data to the array
        for(int FileNum=0; FileNum<NFiles_proton; FileNum++)
        {
          for (int k=0; k< NPoints_proton[i][j][FileNum]; k++)
          {
            CsIV[i][j][PointsNum[i][j]] = CsIV_proton[i][j][FileNum][k];
            errCsIV[i][j][PointsNum[i][j]] = err_CsIV_proton[i][j][FileNum][k];
            CsIE[i][j][PointsNum[i][j]] = Energy_proton[i][j][FileNum][k];
            errCsIE[i][j][PointsNum[i][j]] = err_Energy_proton[i][j][FileNum][k];
            ZA[i][j][PointsNum[i][j]] = ZA_proton[i][j][FileNum][k];
            PointsNum[i][j]++;
          }
        }

        ////////////////////////////////////////////////////////////////////////////
        ///  add deuteron data to the array
        for(int FileNum=0; FileNum<NFiles_deuteron; FileNum++)
        {
          for (int k=0; k< NPoints_deuteron[i][j][FileNum]; k++)
          {
            CsIV[i][j][PointsNum[i][j]] = CsIV_deuteron[i][j][FileNum][k];
            errCsIV[i][j][PointsNum[i][j]] = err_CsIV_deuteron[i][j][FileNum][k];
            CsIE[i][j][PointsNum[i][j]] = Energy_deuteron[i][j][FileNum][k];
            errCsIE[i][j][PointsNum[i][j]] = err_Energy_deuteron[i][j][FileNum][k];
            ZA[i][j][PointsNum[i][j]] = ZA_deuteron[i][j][FileNum][k];
            PointsNum[i][j]++;
          }
        }

        ////////////////////////////////////////////////////////////////////////////
        ///  add triton data to the array
        for(int FileNum=0; FileNum<NFiles_triton; FileNum++)
        {
          for (int k=0; k< NPoints_triton[i][j][FileNum]; k++)
          {
            CsIV[i][j][PointsNum[i][j]] = CsIV_triton[i][j][FileNum][k];
            errCsIV[i][j][PointsNum[i][j]] = err_CsIV_triton[i][j][FileNum][k];
            CsIE[i][j][PointsNum[i][j]] = Energy_triton[i][j][FileNum][k];
            errCsIE[i][j][PointsNum[i][j]] = err_Energy_triton[i][j][FileNum][k];
            ZA[i][j][PointsNum[i][j]] = ZA_triton[i][j][FileNum][k];
            PointsNum[i][j]++;
          }
        }
      }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    ///   Definition of the total graph 2D
    TGraph2DErrors * TotGraph[12][4];

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Fill 2D Graph with the dataset set above
    for(int i=0; i<12; i++) {
      for(int j=0; j<4; j++) {
        TotGraph[i][j] = new TGraph2DErrors (PointsNum[i][j], CsIE[i][j], ZA[i][j], CsIV[i][j],  errCsIE[i][j], 0, errCsIV[i][j]);
        TotGraph[i][j]->SetName(Form("TEL%02d_CsI%02d", i, j));
        TotGraph[i][j]->SetTitle(Form("TEL%02d_CsI%02d", i, j));
        TotGraph[i][j]->SetMarkerStyle(20);
      }
    }
   /////////////////////////////////////////////////////////////////////////////
   /// Fit all the data with the same function -- fitfunc
   TF2 *fPDT = new TF2("fPDT",fitfunc, 0, 1000, 100, 500, 3);

   ///////////////////////////////////////////////////////////////////////////////////////////////////////
   //// since I failed to draw the fit in the 2D graph, I set new functions to fit
   ///  the datasets, but with the same parameters with fitfunc (which used for simultaneously fit)
   TF1 * fProton = new TF1("fProton", fit_proton, 0, 1000, 3);
   TF1 * fDeuteron = new TF1("fDeuteron", fit_deuteron, 0, 1000, 3);
   TF1 * fTriton = new TF1("fTriton", fit_triton, 0, 1000, 3);
   fProton->SetLineColor(1);
   fDeuteron->SetLineColor(3);
   fTriton->SetLineColor(4);
   fPDT->SetParameters(0.005,2000,1000);

   TCanvas *c1 = new TCanvas("c1");
   for(int i=0; i<TELNUM; i++)
   {
     if(i!=5) continue;
     for(int j=0; j<CSINUM; j++)
     {
      TotGraph[i][j]->Fit("fPDT");

      ///////////////////////////////////////////////////////////////////////////////////////////////
      /// To set the parameters of  fProton, fDeuteron, fTriton to be the same
      fProton->SetParameters(fPDT->GetParameters());
      fDeuteron->SetParameters(fPDT->GetParameters());
      fTriton->SetParameters(fPDT->GetParameters());

      multi[i][j]->Draw("APE");
      fProton->Draw("SAME");
      fDeuteron->Draw("SAME");
      fTriton->Draw("SAME");

      gPad->Modified();
      gPad->Update();
      getchar();
     }
   }




}
