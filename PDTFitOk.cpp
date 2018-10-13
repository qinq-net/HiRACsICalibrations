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
  if(x[1]==101 || x[1]==102 || x[1]==103)
  {
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



//////////////////////////////////////////////////////////////////////////////////////////
/// definition of Horn formula to fitting isotopes from Z=2 to Z=4
/// this formula is given in the following paper: D.Horn et al, NIM A320(1992) 273-276
double HornFit(double *x, double *par)
{
  // x[0]--E, x[1]--A
  if(x[1]==203 || x[1]==204 || x[1]==306 || x[1]==307 || x[1]==308 || x[1]==407 || x[1]==409  )
  {
    int A = Int_t(x[1])%100;
    int Z = Int_t(x[1])/100;
    double consterm = par[2]*A*pow(Z,2);
    double lineterm = x[0]+consterm;
    double logterm = consterm*log(abs(lineterm/consterm));
    double light = par[0]+par[1]*(x[0]-logterm);
    return light;
  }
  return 0;
}

///////////////////////////////////////////////////////
///  definition of fitting function of 3He
double fit_He3(double *x, double *par)
{
  double consterm = par[2]*3*pow(2,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

///////////////////////////////////////////////////////
///  definition of fitting function of 4He
double fit_He4(double *x, double *par)
{
  double consterm = par[2]*4*pow(2,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}


///////////////////////////////////////////////////////
///  definition of fitting function of 6Li
double fit_Li6(double *x, double *par)
{
  double consterm = par[2]*6*pow(3,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

///////////////////////////////////////////////////////
///  definition of fitting function of 7Li
double fit_Li7(double *x, double *par)
{
  double consterm = par[2]*7*pow(3,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

///////////////////////////////////////////////////////
///  definition of fitting function of 8Li
double fit_Li8(double *x, double *par)
{
  double consterm = par[2]*8*pow(3,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

///////////////////////////////////////////////////////
///  definition of fitting function of 7Be
double fit_Be7(double *x, double *par)
{
  double consterm = par[2]*7*pow(4,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}

///////////////////////////////////////////////////////
///  definition of fitting function of 9Be
double fit_Be9(double *x, double *par)
{
  double consterm = par[2]*9*pow(4,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}



void PDTFitOk()
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
     int NFiles_proton=12;
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
     TGraphErrors * DataProton [12][4][12];

     //////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of variables to read the input data files
     std::vector<double> CsIV_proton[12][4][12];
     std::vector<double> err_CsIV_proton[12][4][12];
     std::vector<double> Energy_proton[12][4][12];
     std::vector<double> err_Energy_proton[12][4][12];
     std::vector<double> ZA_proton[12][4][12];

     /////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of the number of data points for each input file
     for(int FileNum=0; FileNum<NFiles_proton; FileNum++)
     {

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
         double V;
         double err_V;
         double E;
         double err_E;

         LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

         CsIV_proton[telnum][csinum][FileNum].push_back(V);
         err_CsIV_proton[telnum][csinum][FileNum].push_back(err_V);
         Energy_proton[telnum][csinum][FileNum].push_back(E);
         err_Energy_proton[telnum][csinum][FileNum].push_back(err_E);

       }

       for(int i=0; i<TELNUM; i++)
       {
         for(int j=0; j<CSINUM; j++)
         {

             DataProton[i][j][FileNum] = new TGraphErrors(CsIV_proton[i][j][FileNum].size(), Energy_proton[i][j][FileNum].data(), CsIV_proton[i][j][FileNum].data(), err_Energy_proton[i][j][FileNum].data() ,err_CsIV_proton[i][j][FileNum].data());
             DataProton[i][j][FileNum]->SetMarkerColor(1); // black marker for protons
             DataProton[i][j][FileNum]->SetLineColor(1);
             DataProton[i][j][FileNum]->SetMarkerStyle(20+FileNum);

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


     //////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of variables to read the input data files
     std::vector<double> CsIV_deuteron[12][4][3];
     std::vector<double> err_CsIV_deuteron[12][4][3];
     std::vector<double> Energy_deuteron[12][4][3];
     std::vector<double> err_Energy_deuteron[12][4][3];
     std::vector<double> ZA_deuteron[12][4][3];

     /////////////////////////////////////////////////////////////////////////////////////////////
     ///  definition of the number of data points for each input file
     for(int FileNum=0; FileNum<NFiles_deuteron; FileNum++)
     {

       ifstream FileIn_deuteron(FileIn_name_deuteron[FileNum]->c_str());

       if(!FileIn_deuteron.is_open())
       {
         printf("Error: file%s not found\n", FileIn_name_deuteron[FileNum]->c_str());
         return;
       }

       /////////////////////////////////////////////////////////////////////////////////////
       ///    Loop, to read each input data file
       while(!FileIn_deuteron.eof())
       {
         std::string LineRead;
         std::getline(FileIn_deuteron, LineRead);

         if(LineRead.empty()) continue;
         if(LineRead.find('*')==0) continue;

         std::istringstream LineStream(LineRead);

         int telnum;
         int csinum;
         double V;
         double err_V;
         double E;
         double err_E;

         LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

         CsIV_deuteron[telnum][csinum][FileNum].push_back(V);
         err_CsIV_deuteron[telnum][csinum][FileNum].push_back(err_V);
         Energy_deuteron[telnum][csinum][FileNum].push_back(E);
         err_Energy_deuteron[telnum][csinum][FileNum].push_back(err_E);

       }

       for(int i=0; i<TELNUM; i++)
       {
         for(int j=0; j<CSINUM; j++)
         {

             DataDeuteron[i][j][FileNum] = new TGraphErrors(CsIV_deuteron[i][j][FileNum].size(), Energy_deuteron[i][j][FileNum].data(), CsIV_deuteron[i][j][FileNum].data(), err_Energy_deuteron[i][j][FileNum].data() ,err_CsIV_deuteron[i][j][FileNum].data());
             DataDeuteron[i][j][FileNum]->SetMarkerColor(3); // black marker for deuterons
             DataDeuteron[i][j][FileNum]->SetLineColor(3);
             DataDeuteron[i][j][FileNum]->SetMarkerStyle(20+FileNum);

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

      //////////////////////////////////////////////////////////////////////////////////////////////
      ///  definition of variables to read the input data files
      std::vector<double> CsIV_triton[12][4][2];
      std::vector<double> err_CsIV_triton[12][4][2];
      std::vector<double> Energy_triton[12][4][2];
      std::vector<double> err_Energy_triton[12][4][2];
      std::vector<double> ZA_triton[12][4][2];

      /////////////////////////////////////////////////////////////////////////////////////////////
      ///  definition of the number of data points for each input file
      for(int FileNum=0; FileNum<NFiles_triton; FileNum++)
      {

        ifstream FileIn_triton(FileIn_name_triton[FileNum]->c_str());

        if(!FileIn_triton.is_open())
        {
          printf("Error: file%s not found\n", FileIn_name_triton[FileNum]->c_str());
          return;
        }

        /////////////////////////////////////////////////////////////////////////////////////
        ///    Loop, to read each input data file
        while(!FileIn_triton.eof())
        {
          std::string LineRead;
          std::getline(FileIn_triton, LineRead);

          if(LineRead.empty()) continue;
          if(LineRead.find('*')==0) continue;

          std::istringstream LineStream(LineRead);

          int telnum;
          int csinum;
          double V;
          double err_V;
          double E;
          double err_E;

          LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

          CsIV_triton[telnum][csinum][FileNum].push_back(V);
          err_CsIV_triton[telnum][csinum][FileNum].push_back(err_V);
          Energy_triton[telnum][csinum][FileNum].push_back(E);
          err_Energy_triton[telnum][csinum][FileNum].push_back(err_E);

        }

        for(int i=0; i<TELNUM; i++)
        {
          for(int j=0; j<CSINUM; j++)
          {

              DataTriton[i][j][FileNum] = new TGraphErrors(CsIV_triton[i][j][FileNum].size(), Energy_triton[i][j][FileNum].data(), CsIV_triton[i][j][FileNum].data(), err_Energy_triton[i][j][FileNum].data() ,err_CsIV_triton[i][j][FileNum].data());
              DataTriton[i][j][FileNum]->SetMarkerColor(4); // black marker for tritons
              DataTriton[i][j][FileNum]->SetLineColor(4);
              DataTriton[i][j][FileNum]->SetMarkerStyle(20+FileNum);

          }
        }
        FileIn_triton.close();
      }




      /************************************************************************************************************
       *                                                                                                          *
       *                                         For 3Hes                                                      *
       *                                                                                                          *
       ************************************************************************************************************/
       Int_t NFiles_3He=1;
       std::string * FileIn_name_3He[NFiles_3He];
       FileIn_name_3He[0] = new std::string("calibrations/DEEPoints_Z02_A03.dat"); //DEE points


       //////////////////////////////////////////////////////////////////////////////////////////////
       /// definition of TGraphErrors, TMultiGraph, TLengend
       TGraphErrors * Data3He[12][4][NFiles_3He];

       //////////////////////////////////////////////////////////////////////////////////////////////
       ///  definition of variables to read the input data files
       std::vector<double> CsIV_3He[12][4][1];
       std::vector<double> err_CsIV_3He[12][4][1];
       std::vector<double> Energy_3He[12][4][1];
       std::vector<double> err_Energy_3He[12][4][1];
       std::vector<double> ZA_3He[12][4][1];


       for(int FileNum=0; FileNum<NFiles_3He; FileNum++)
       {

         ifstream FileIn_3He(FileIn_name_3He[FileNum]->c_str());

         if(!FileIn_3He.is_open())
         {
           printf("Error: file%s not found\n", FileIn_name_3He[FileNum]->c_str());
           return;
         }

         /////////////////////////////////////////////////////////////////////////////////////
         ///    Loop, to read each input data file
         while(!FileIn_3He.eof())
         {
           std::string LineRead;
           std::getline(FileIn_3He, LineRead);

           if(LineRead.empty()) continue;
           if(LineRead.find('*')==0) continue;

           std::istringstream LineStream(LineRead);

           int telnum;
           int csinum;
           double V;
           double err_V;
           double E;
           double err_E;

           LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

           CsIV_3He[telnum][csinum][FileNum].push_back(V);
           err_CsIV_3He[telnum][csinum][FileNum].push_back(err_V);
           Energy_3He[telnum][csinum][FileNum].push_back(E);
           err_Energy_3He[telnum][csinum][FileNum].push_back(err_E);

         }

         for(int i=0; i<TELNUM; i++)
         {
           for(int j=0; j<CSINUM; j++)
           {

               Data3He[i][j][FileNum] = new TGraphErrors(CsIV_3He[i][j][FileNum].size(), Energy_3He[i][j][FileNum].data(), CsIV_3He[i][j][FileNum].data(), err_Energy_3He[i][j][FileNum].data() ,err_CsIV_3He[i][j][FileNum].data());
               Data3He[i][j][FileNum]->SetMarkerColor(5); // black marker for 3Hes
               Data3He[i][j][FileNum]->SetLineColor(5);
               Data3He[i][j][FileNum]->SetMarkerStyle(20+FileNum);
           }
         }
         FileIn_3He.close();
       }



       /************************************************************************************************************
        *                                                                                                          *
        *                                         For 4Hes                                                      *
        *                                                                                                          *
        ************************************************************************************************************/
        Int_t NFiles_4He=2;
        std::string * FileIn_name_4He[NFiles_4He];
        FileIn_name_4He[0] = new std::string("calibrations/DEEPoints_Z02_A04.dat"); //DEE points
        FileIn_name_4He[1] = new std::string("calibrations/WMUdata_Z02_A04.dat");

        //////////////////////////////////////////////////////////////////////////////////////////////
        /// definition of TGraphErrors, TMultiGraph, TLengend
        TGraphErrors * Data4He[12][4][NFiles_4He];

        //////////////////////////////////////////////////////////////////////////////////////////////
        ///  definition of variables to read the input data files
        std::vector<double> CsIV_4He[12][4][2];
        std::vector<double> err_CsIV_4He[12][4][2];
        std::vector<double> Energy_4He[12][4][2];
        std::vector<double> err_Energy_4He[12][4][2];
        std::vector<double> ZA_4He[12][4][2];

        /////////////////////////////////////////////////////////////////////////////////////////////
        ///  definition of the number of data points for each input file
        for(int FileNum=0; FileNum<NFiles_4He; FileNum++)
        {

          ifstream FileIn_4He(FileIn_name_4He[FileNum]->c_str());

          if(!FileIn_4He.is_open())
          {
            printf("Error: file%s not found\n", FileIn_name_4He[FileNum]->c_str());
            return;
          }

          /////////////////////////////////////////////////////////////////////////////////////
          ///    Loop, to read each input data file
          while(!FileIn_4He.eof())
          {
            std::string LineRead;
            std::getline(FileIn_4He, LineRead);

            if(LineRead.empty()) continue;
            if(LineRead.find('*')==0) continue;

            std::istringstream LineStream(LineRead);

            int telnum;
            int csinum;
            double V;
            double err_V;
            double E;
            double err_E;

            LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

            CsIV_4He[telnum][csinum][FileNum].push_back(V);
            err_CsIV_4He[telnum][csinum][FileNum].push_back(err_V);
            Energy_4He[telnum][csinum][FileNum].push_back(E);
            err_Energy_4He[telnum][csinum][FileNum].push_back(err_E);

          }

          for(int i=0; i<TELNUM; i++)
          {
            for(int j=0; j<CSINUM; j++)
            {

                Data4He[i][j][FileNum] = new TGraphErrors(CsIV_4He[i][j][FileNum].size(), Energy_4He[i][j][FileNum].data(), CsIV_4He[i][j][FileNum].data(), err_Energy_4He[i][j][FileNum].data() ,err_CsIV_4He[i][j][FileNum].data());
                Data4He[i][j][FileNum]->SetMarkerColor(6); // black marker for 4Hes
                Data4He[i][j][FileNum]->SetLineColor(6);
                Data4He[i][j][FileNum]->SetMarkerStyle(20+FileNum);
            }
          }
          FileIn_4He.close();
        }


        /************************************************************************************************************
         *                                                                                                          *
         *                                         For Li6s                                                         *
         *                                                                                                          *
         ************************************************************************************************************/
         Int_t NFiles_Li6=1;
         std::string * FileIn_name_Li6[NFiles_Li6];
         FileIn_name_Li6[0] = new std::string("calibrations/DEEPoints_Z03_A06.dat"); //DEE points

         //////////////////////////////////////////////////////////////////////////////////////////////
         /// definition of TGraphErrors, TMultiGraph, TLengend
         TGraphErrors * DataLi6[12][4][NFiles_Li6];

         //////////////////////////////////////////////////////////////////////////////////////////////
         ///  definition of variables to read the input data files
         std::vector<double> CsIV_Li6[12][4][1];
         std::vector<double> err_CsIV_Li6[12][4][1];
         std::vector<double> Energy_Li6[12][4][1];
         std::vector<double> err_Energy_Li6[12][4][1];
         std::vector<double> ZA_Li6[12][4][1];

         /////////////////////////////////////////////////////////////////////////////////////////////
         ///  definition of the number of data points for each input file
         for(int FileNum=0; FileNum<NFiles_Li6; FileNum++)
         {

           ifstream FileIn_Li6(FileIn_name_Li6[FileNum]->c_str());

           if(!FileIn_Li6.is_open())
           {
             printf("Error: file%s not found\n", FileIn_name_Li6[FileNum]->c_str());
             return;
           }

           /////////////////////////////////////////////////////////////////////////////////////
           ///    Loop, to read each input data file
           while(!FileIn_Li6.eof())
           {
             std::string LineRead;
             std::getline(FileIn_Li6, LineRead);

             if(LineRead.empty()) continue;
             if(LineRead.find('*')==0) continue;

             std::istringstream LineStream(LineRead);

             int telnum;
             int csinum;
             double V;
             double err_V;
             double E;
             double err_E;

             LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

             CsIV_Li6[telnum][csinum][FileNum].push_back(V);
             err_CsIV_Li6[telnum][csinum][FileNum].push_back(err_V);
             Energy_Li6[telnum][csinum][FileNum].push_back(E);
             err_Energy_Li6[telnum][csinum][FileNum].push_back(err_E);

           }

           for(int i=0; i<TELNUM; i++)
           {
             for(int j=0; j<CSINUM; j++)
             {

                 DataLi6[i][j][FileNum] = new TGraphErrors(CsIV_Li6[i][j][FileNum].size(), Energy_Li6[i][j][FileNum].data(), CsIV_Li6[i][j][FileNum].data(), err_Energy_Li6[i][j][FileNum].data() ,err_CsIV_Li6[i][j][FileNum].data());
                 DataLi6[i][j][FileNum]->SetMarkerColor(7); // black marker for Li6s
                 DataLi6[i][j][FileNum]->SetLineColor(7);
                 DataLi6[i][j][FileNum]->SetMarkerStyle(20+FileNum);
             }
           }
           FileIn_Li6.close();
         }


         /************************************************************************************************************
          *                                                                                                          *
          *                                         For Li7s                                                      *
          *                                                                                                          *
          ************************************************************************************************************/
          Int_t NFiles_Li7=1;
          std::string * FileIn_name_Li7[NFiles_Li7];
          FileIn_name_Li7[0] = new std::string("calibrations/DEEPoints_Z03_A07.dat"); //DEE points

          //////////////////////////////////////////////////////////////////////////////////////////////
          /// definition of TGraphErrors, TMultiGraph, TLengend
          TGraphErrors * DataLi7[12][4][NFiles_Li7];

          //////////////////////////////////////////////////////////////////////////////////////////////
          ///  definition of variables to read the input data files
          std::vector<double> CsIV_Li7[12][4][1];
          std::vector<double> err_CsIV_Li7[12][4][1];
          std::vector<double> Energy_Li7[12][4][1];
          std::vector<double> err_Energy_Li7[12][4][1];
          std::vector<double> ZA_Li7[12][4][1];

          /////////////////////////////////////////////////////////////////////////////////////////////
          ///  definition of the number of data points for each input file
          for(int FileNum=0; FileNum<NFiles_Li7; FileNum++)
          {

            ifstream FileIn_Li7(FileIn_name_Li7[FileNum]->c_str());

            if(!FileIn_Li7.is_open())
            {
              printf("Error: file%s not found\n", FileIn_name_Li7[FileNum]->c_str());
              return;
            }

            /////////////////////////////////////////////////////////////////////////////////////
            ///    Loop, to read each input data file
            while(!FileIn_Li7.eof())
            {
              std::string LineRead;
              std::getline(FileIn_Li7, LineRead);

              if(LineRead.empty()) continue;
              if(LineRead.find('*')==0) continue;

              std::istringstream LineStream(LineRead);

              int telnum;
              int csinum;
              double V;
              double err_V;
              double E;
              double err_E;

              LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

              CsIV_Li7[telnum][csinum][FileNum].push_back(V);
              err_CsIV_Li7[telnum][csinum][FileNum].push_back(err_V);
              Energy_Li7[telnum][csinum][FileNum].push_back(E);
              err_Energy_Li7[telnum][csinum][FileNum].push_back(err_E);

            }

            for(int i=0; i<TELNUM; i++)
            {
              for(int j=0; j<CSINUM; j++)
              {

                  DataLi7[i][j][FileNum] = new TGraphErrors(CsIV_Li7[i][j][FileNum].size(), Energy_Li7[i][j][FileNum].data(), CsIV_Li7[i][j][FileNum].data(), err_Energy_Li7[i][j][FileNum].data() ,err_CsIV_Li7[i][j][FileNum].data());
                  DataLi7[i][j][FileNum]->SetMarkerColor(8); // black marker for Li7s
                  DataLi7[i][j][FileNum]->SetLineColor(8);
                  DataLi7[i][j][FileNum]->SetMarkerStyle(20+FileNum);
              }
            }
            FileIn_Li7.close();
          }


          /************************************************************************************************************
           *                                                                                                          *
           *                                         For Li8s                                                      *
           *                                                                                                          *
           ************************************************************************************************************/
           Int_t NFiles_Li8=1;
           std::string * FileIn_name_Li8[NFiles_Li8];
           FileIn_name_Li8[0] = new std::string("calibrations/DEEPoints_Z03_A08.dat"); //DEE points

           //////////////////////////////////////////////////////////////////////////////////////////////
           /// definition of TGraphErrors, TMultiGraph, TLengend
           TGraphErrors * DataLi8[12][4][NFiles_Li8];

           //////////////////////////////////////////////////////////////////////////////////////////////
           ///  definition of variables to read the input data files
           std::vector<double> CsIV_Li8[12][4][1];
           std::vector<double> err_CsIV_Li8[12][4][1];
           std::vector<double> Energy_Li8[12][4][1];
           std::vector<double> err_Energy_Li8[12][4][1];
           std::vector<double> ZA_Li8[12][4][1];

           /////////////////////////////////////////////////////////////////////////////////////////////
           ///  definition of the number of data points for each input file
           for(int FileNum=0; FileNum<NFiles_Li8; FileNum++)
           {

             ifstream FileIn_Li8(FileIn_name_Li8[FileNum]->c_str());

             if(!FileIn_Li8.is_open())
             {
               printf("Error: file%s not found\n", FileIn_name_Li8[FileNum]->c_str());
               return;
             }

             /////////////////////////////////////////////////////////////////////////////////////
             ///    Loop, to read each input data file
             while(!FileIn_Li8.eof())
             {
               std::string LineRead;
               std::getline(FileIn_Li8, LineRead);

               if(LineRead.empty()) continue;
               if(LineRead.find('*')==0) continue;

               std::istringstream LineStream(LineRead);

               int telnum;
               int csinum;
               double V;
               double err_V;
               double E;
               double err_E;

               LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

               CsIV_Li8[telnum][csinum][FileNum].push_back(V);
               err_CsIV_Li8[telnum][csinum][FileNum].push_back(err_V);
               Energy_Li8[telnum][csinum][FileNum].push_back(E);
               err_Energy_Li8[telnum][csinum][FileNum].push_back(err_E);

             }

             for(int i=0; i<TELNUM; i++)
             {
               for(int j=0; j<CSINUM; j++)
               {

                   DataLi8[i][j][FileNum] = new TGraphErrors(CsIV_Li8[i][j][FileNum].size(), Energy_Li8[i][j][FileNum].data(), CsIV_Li8[i][j][FileNum].data(), err_Energy_Li8[i][j][FileNum].data() ,err_CsIV_Li8[i][j][FileNum].data());
                   DataLi8[i][j][FileNum]->SetMarkerColor(9); // black marker for Li8s
                   DataLi8[i][j][FileNum]->SetLineColor(9);
                   DataLi8[i][j][FileNum]->SetMarkerStyle(20+FileNum);
               }
             }
             FileIn_Li8.close();
           }

           /************************************************************************************************************
            *                                                                                                          *
            *                                         For Be7s                                                      *
            *                                                                                                          *
            ************************************************************************************************************/
            Int_t NFiles_Be7=1;
            std::string * FileIn_name_Be7[NFiles_Be7];
            FileIn_name_Be7[0] = new std::string("calibrations/DEEPoints_Z04_A07.dat"); //DEE points

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// definition of TGraphErrors, TMultiGraph, TLengend
            TGraphErrors * DataBe7[12][4][NFiles_Be7];

            //////////////////////////////////////////////////////////////////////////////////////////////
            ///  definition of variables to read the input data files
            std::vector<double> CsIV_Be7[12][4][1];
            std::vector<double> err_CsIV_Be7[12][4][1];
            std::vector<double> Energy_Be7[12][4][1];
            std::vector<double> err_Energy_Be7[12][4][1];
            std::vector<double> ZA_Be7[12][4][1];

            /////////////////////////////////////////////////////////////////////////////////////////////
            ///  definition of the number of data points for each input file
            for(int FileNum=0; FileNum<NFiles_Be7; FileNum++)
            {

              ifstream FileIn_Be7(FileIn_name_Be7[FileNum]->c_str());

              if(!FileIn_Be7.is_open())
              {
                printf("Error: file%s not found\n", FileIn_name_Be7[FileNum]->c_str());
                return;
              }

              /////////////////////////////////////////////////////////////////////////////////////
              ///    Loop, to read each input data file
              while(!FileIn_Be7.eof())
              {
                std::string LineRead;
                std::getline(FileIn_Be7, LineRead);

                if(LineRead.empty()) continue;
                if(LineRead.find('*')==0) continue;

                std::istringstream LineStream(LineRead);

                int telnum;
                int csinum;
                double V;
                double err_V;
                double E;
                double err_E;

                LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

                CsIV_Be7[telnum][csinum][FileNum].push_back(V);
                err_CsIV_Be7[telnum][csinum][FileNum].push_back(err_V);
                Energy_Be7[telnum][csinum][FileNum].push_back(E);
                err_Energy_Be7[telnum][csinum][FileNum].push_back(err_E);

              }

              for(int i=0; i<TELNUM; i++)
              {
                for(int j=0; j<CSINUM; j++)
                {

                    DataBe7[i][j][FileNum] = new TGraphErrors(CsIV_Be7[i][j][FileNum].size(), Energy_Be7[i][j][FileNum].data(), CsIV_Be7[i][j][FileNum].data(), err_Energy_Be7[i][j][FileNum].data() ,err_CsIV_Be7[i][j][FileNum].data());
                    DataBe7[i][j][FileNum]->SetMarkerColor(12); // black marker for Be7s
                    DataBe7[i][j][FileNum]->SetLineColor(12);
                    DataBe7[i][j][FileNum]->SetMarkerStyle(20+FileNum);
                }
              }
              FileIn_Be7.close();
            }


            /************************************************************************************************************
             *                                                                                                          *
             *                                         For Be9s                                                      *
             *                                                                                                          *
             ************************************************************************************************************/
             Int_t NFiles_Be9=1;
             std::string * FileIn_name_Be9[NFiles_Be9];
             FileIn_name_Be9[0] = new std::string("calibrations/DEEPoints_Z04_A09.dat"); //DEE points

             //////////////////////////////////////////////////////////////////////////////////////////////
             /// definition of TGraphErrors, TMultiGraph, TLengend
             TGraphErrors * DataBe9[12][4][NFiles_Be9];

             //////////////////////////////////////////////////////////////////////////////////////////////
             ///  definition of variables to read the input data files
             std::vector<double> CsIV_Be9[12][4][1];
             std::vector<double> err_CsIV_Be9[12][4][1];
             std::vector<double> Energy_Be9[12][4][1];
             std::vector<double> err_Energy_Be9[12][4][1];
             std::vector<double> ZA_Be9[12][4][1];

             /////////////////////////////////////////////////////////////////////////////////////////////
             ///  definition of the number of data points for each input file
             for(int FileNum=0; FileNum<NFiles_Be9; FileNum++)
             {

               ifstream FileIn_Be9(FileIn_name_Be9[FileNum]->c_str());

               if(!FileIn_Be9.is_open())
               {
                 printf("Error: file%s not found\n", FileIn_name_Be9[FileNum]->c_str());
                 return;
               }

               /////////////////////////////////////////////////////////////////////////////////////
               ///    Loop, to read each input data file
               while(!FileIn_Be9.eof())
               {
                 std::string LineRead;
                 std::getline(FileIn_Be9, LineRead);

                 if(LineRead.empty()) continue;
                 if(LineRead.find('*')==0) continue;

                 std::istringstream LineStream(LineRead);

                 int telnum;
                 int csinum;
                 double V;
                 double err_V;
                 double E;
                 double err_E;

                 LineStream >> telnum >> csinum >> V >> err_V >> E >> err_E;

                 CsIV_Be9[telnum][csinum][FileNum].push_back(V);
                 err_CsIV_Be9[telnum][csinum][FileNum].push_back(err_V);
                 Energy_Be9[telnum][csinum][FileNum].push_back(E);
                 err_Energy_Be9[telnum][csinum][FileNum].push_back(err_E);

               }

               for(int i=0; i<TELNUM; i++)
               {
                 for(int j=0; j<CSINUM; j++)
                 {

                     DataBe9[i][j][FileNum] = new TGraphErrors(CsIV_Be9[i][j][FileNum].size(), Energy_Be9[i][j][FileNum].data(), CsIV_Be9[i][j][FileNum].data(), err_Energy_Be9[i][j][FileNum].data() ,err_CsIV_Be9[i][j][FileNum].data());
                     DataBe9[i][j][FileNum]->SetMarkerColor(13); // black marker for Be9s
                     DataBe9[i][j][FileNum]->SetLineColor(13);
                     DataBe9[i][j][FileNum]->SetMarkerStyle(20+FileNum);
                 }
               }
               FileIn_Be9.close();
             }











/*

       ////////////////////////////////////////////////////////////////////////////////////////////////
       /// To create a multigraph to draw all the firt in the same cnavas
       TMultiGraph * multi_H[12][4];   // for Hygrogen isotopes
       TMultiGraph * multi_HI[12][4];  // for Heavy Ions

       for(int i=0; i<12; i++)
       {
         for(int j=0; j<4; j++)
         {
   /////////////////////////////////////////////////////////////////////////////////
  ///  For H isotopes (H)
  ///////////////////////////////////////////////////////////////////////////////

           multi_H[i][j] = new TMultiGraph();
           ///////////////////////////////////////////////////////////////////////////
           ///   Add data for protons
           for(int FileNum=0; FileNum<NFiles_proton; FileNum++)
           {
             if(DataProton[i][j][FileNum]!=0)
             {
               multi_H[i][j]->Add(DataProton[i][j][FileNum]);
             }
           }

           ////////////////////////////////////////////////////////////////////////////
           ///  Add data for deuteron
           for(int FileNum=0; FileNum<NFiles_deuteron; FileNum++)
           {
              if(DataDeuteron[i][j][FileNum]!=0)
              {
                 multi_H[i][j]->Add(DataDeuteron[i][j][FileNum]);

              }
           }
           ///////////////////////////////////////////////////////////////////////////
           ///   Add data for triton
           for(int FileNum=0; FileNum<NFiles_triton; FileNum++)
           {
              if(DataTriton[i][j][FileNum]!=0)
              {
                 multi_H[i][j]->Add(DataTriton[i][j][FileNum]);
              }
           }

   /////////////////////////////////////////////////////////////////////////////////
   ///  For Heavy Ions (HI)
   ///////////////////////////////////////////////////////////////////////////////
          multi_HI[i][j] = new TMultiGraph();
          for(int FileNum=0; FileNum<NFiles_3He; FileNum++)
          {
             if(Data3He[i][j][FileNum]!=0)
             {
                multi_HI[i][j]->Add(Data3He[i][j][FileNum]);
             }
          }

          for(int FileNum=0; FileNum<NFiles_4He; FileNum++)
          {
             if(Data4He[i][j][FileNum]!=0)
             {
                multi_HI[i][j]->Add(Data4He[i][j][FileNum]);
             }
          }

          for(int FileNum=0; FileNum<NFiles_Li6; FileNum++)
          {
             if(DataLi6[i][j][FileNum]!=0)
             {
                multi_HI[i][j]->Add(DataLi6[i][j][FileNum]);
             }
          }

          for(int FileNum=0; FileNum<NFiles_Li7; FileNum++)
          {
             if(DataLi7[i][j][FileNum]!=0)
             {
                multi_HI[i][j]->Add(DataLi7[i][j][FileNum]);
             }
          }

          for(int FileNum=0; FileNum<NFiles_Li8; FileNum++)
          {
             if(DataLi8[i][j][FileNum]!=0)
             {
                multi_HI[i][j]->Add(DataLi8[i][j][FileNum]);
             }
          }

          for(int FileNum=0; FileNum<NFiles_Be7; FileNum++)
          {
             if(DataBe7[i][j][FileNum]!=0)
             {
                multi_HI[i][j]->Add(DataBe7[i][j][FileNum]);
             }
          }

          for(int FileNum=0; FileNum<NFiles_Be9; FileNum++)
          {
             if(DataBe9[i][j][FileNum]!=0)
             {
                multi_HI[i][j]->Add(DataBe9[i][j][FileNum]);
             }
          }
         }
       }   */

    ////////////////////////////////////////////////////////////
    ///   Making the dataset  for Hydrogen isotopes
    std::vector<double> CsIV_H[12][4];
    std::vector<double> errCsIV_H[12][4];
    std::vector<double> CsIE_H[12][4];
    std::vector<double> errCsIE_H[12][4];
    std::vector<double> ZA_H[12][4];

    ////////////////////////////////////////////////////////////
    ///   Making the dataset  for Heavy Ions
    std::vector<double> CsIV_HI[12][4];
    std::vector<double> errCsIV_HI[12][4];
    std::vector<double> CsIE_HI[12][4];
    std::vector<double> errCsIE_HI[12][4];
    std::vector<double> ZA_HI[12][4];

    //////////////////////////////////////////////////////////////////////////////////////
    //// put all the dataset together in one array, and then fit with 2D Graph
    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
  //////////////////////////////////////////////////////////////////////////////////
  ///     add data for Hydrogen isotopes (H)
  ///////////////////////////////////////////////////////////////////////////////
        for(int FileNum=0; FileNum<NFiles_proton; FileNum++)
        {
          for (int k=0; k< CsIV_proton[i][j][FileNum].size(); k++)
          {
            CsIV_H[i][j].push_back(CsIV_proton[i][j][FileNum][k]);
            errCsIV_H[i][j].push_back(err_CsIV_proton[i][j][FileNum][k]);
            CsIE_H[i][j].push_back(Energy_proton[i][j][FileNum][k]);
            errCsIE_H[i][j].push_back(err_Energy_proton[i][j][FileNum][k]);
            ZA_H[i][j].push_back(101);
          }
        }

        for(int FileNum=0; FileNum<NFiles_deuteron; FileNum++)
        {
          for (int k=0; k< CsIV_deuteron[i][j][FileNum].size(); k++)
          {
            CsIV_H[i][j].push_back(CsIV_deuteron[i][j][FileNum][k]);
            errCsIV_H[i][j].push_back(err_CsIV_deuteron[i][j][FileNum][k]);
            CsIE_H[i][j].push_back(Energy_deuteron[i][j][FileNum][k]);
            errCsIE_H[i][j].push_back(err_Energy_deuteron[i][j][FileNum][k]);
            ZA_H[i][j].push_back(102);
          }
        }

        for(int FileNum=0; FileNum<NFiles_triton; FileNum++)
        {
          for (int k=0; k< CsIV_triton[i][j][FileNum].size(); k++)
          {
            CsIV_H[i][j].push_back(CsIV_triton[i][j][FileNum][k]);
            errCsIV_H[i][j].push_back(err_CsIV_triton[i][j][FileNum][k]);
            CsIE_H[i][j].push_back(Energy_triton[i][j][FileNum][k]);
            errCsIE_H[i][j].push_back(err_Energy_triton[i][j][FileNum][k]);
            ZA_H[i][j].push_back(103);
          }
        }


  //////////////////////////////////////////////////////////////////////////////////
  ///     add data for Heavy Ions (HI)
  ///////////////////////////////////////////////////////////////////////////////
        for(int FileNum=0; FileNum<NFiles_3He; FileNum++)
        {
          for (int k=0; k< CsIV_3He[i][j][FileNum].size(); k++)
          {
            CsIV_HI[i][j].push_back(CsIV_3He[i][j][FileNum][k]);
            errCsIV_HI[i][j].push_back(err_CsIV_3He[i][j][FileNum][k]);
            CsIE_HI[i][j].push_back(Energy_3He[i][j][FileNum][k]);
            errCsIE_HI[i][j].push_back(err_Energy_3He[i][j][FileNum][k]);
            ZA_HI[i][j].push_back(203);
          }
        }

        for(int FileNum=0; FileNum<NFiles_4He; FileNum++)
        {
          for (int k=0; k< CsIV_4He[i][j][FileNum].size(); k++)
          {
            CsIV_HI[i][j].push_back(CsIV_4He[i][j][FileNum][k]);
            errCsIV_HI[i][j].push_back(err_CsIV_4He[i][j][FileNum][k]);
            CsIE_HI[i][j].push_back(Energy_4He[i][j][FileNum][k]);
            errCsIE_HI[i][j].push_back(err_Energy_4He[i][j][FileNum][k]);
            ZA_HI[i][j].push_back(204);
          }
        }

        for(int FileNum=0; FileNum<NFiles_Li6; FileNum++)
        {
          for (int k=0; k< CsIV_Li6[i][j][FileNum].size(); k++)
          {
            CsIV_HI[i][j].push_back(CsIV_Li6[i][j][FileNum][k]);
            errCsIV_HI[i][j].push_back(err_CsIV_Li6[i][j][FileNum][k]);
            CsIE_HI[i][j].push_back(Energy_Li6[i][j][FileNum][k]);
            errCsIE_HI[i][j].push_back(err_Energy_Li6[i][j][FileNum][k]);
            ZA_HI[i][j].push_back(306);
          }
        }

        for(int FileNum=0; FileNum<NFiles_Li7; FileNum++)
        {
          for (int k=0; k< CsIV_Li7[i][j][FileNum].size(); k++)
          {
            CsIV_HI[i][j].push_back(CsIV_Li7[i][j][FileNum][k]);
            errCsIV_HI[i][j].push_back(err_CsIV_Li7[i][j][FileNum][k]);
            CsIE_HI[i][j].push_back(Energy_Li7[i][j][FileNum][k]);
            errCsIE_HI[i][j].push_back(err_Energy_Li7[i][j][FileNum][k]);
            ZA_HI[i][j].push_back(307);
          }
        }

        for(int FileNum=0; FileNum<NFiles_Li8; FileNum++)
        {
          for (int k=0; k< CsIV_Li8[i][j][FileNum].size(); k++)
          {
            CsIV_HI[i][j].push_back(CsIV_Li8[i][j][FileNum][k]);
            errCsIV_HI[i][j].push_back(err_CsIV_Li8[i][j][FileNum][k]);
            CsIE_HI[i][j].push_back(Energy_Li8[i][j][FileNum][k]);
            errCsIE_HI[i][j].push_back(err_Energy_Li8[i][j][FileNum][k]);
            ZA_HI[i][j].push_back(308);
          }
        }

        for(int FileNum=0; FileNum<NFiles_Be7; FileNum++)
        {
          for (int k=0; k< CsIV_Be7[i][j][FileNum].size(); k++)
          {
            CsIV_HI[i][j].push_back(CsIV_Be7[i][j][FileNum][k]);
            errCsIV_HI[i][j].push_back(err_CsIV_Be7[i][j][FileNum][k]);
            CsIE_HI[i][j].push_back(Energy_Be7[i][j][FileNum][k]);
            errCsIE_HI[i][j].push_back(err_Energy_Be7[i][j][FileNum][k]);
            ZA_HI[i][j].push_back(407);
          }
        }

        for(int FileNum=0; FileNum<NFiles_Be9; FileNum++)
        {
          for (int k=0; k< CsIV_Be9[i][j][FileNum].size(); k++)
          {
            CsIV_HI[i][j].push_back(CsIV_Be9[i][j][FileNum][k]);
            errCsIV_HI[i][j].push_back(err_CsIV_Be9[i][j][FileNum][k]);
            CsIE_HI[i][j].push_back(Energy_Be9[i][j][FileNum][k]);
            errCsIE_HI[i][j].push_back(err_Energy_Be9[i][j][FileNum][k]);
            ZA_HI[i][j].push_back(409);
          }
        }
      }
    }



    /////////////////////////////////////////////////////////////////////////////////////////////
    ///   Definition of the total graph 2D
    TGraph2DErrors * TotGraph_H[12][4];
    TGraph2DErrors * TotGraph_HI[12][4];

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Fill 2D Graph with the dataset set above
    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {

///////////////////////////////////////////////////////////////////////////////////////////////
////  2D graphs for Hydrogen isotopes
///////////////////////////////////////////////////////////////////////////////////////////////
        TotGraph_H[i][j] = new TGraph2DErrors (CsIV_H[i][j].size(), CsIE_H[i][j].data(), ZA_H[i][j].data(), CsIV_H[i][j].data(), errCsIE_H[i][j].data(), 0, errCsIV_H[i][j].data());
        TotGraph_H[i][j]->SetName(Form("TEL%02d_CsI%02d", i, j));
        TotGraph_H[i][j]->SetTitle(Form("TEL%02d_CsI%02d", i, j));
        TotGraph_H[i][j]->SetMarkerStyle(20);

///////////////////////////////////////////////////////////////////////////////////////////////
////  2D graphs for Heavy Ions
///////////////////////////////////////////////////////////////////////////////////////////////
        TotGraph_HI[i][j] = new TGraph2DErrors (CsIV_HI[i][j].size(), CsIE_HI[i][j].data(), ZA_HI[i][j].data(), CsIV_HI[i][j].data(), errCsIE_HI[i][j].data(), 0, errCsIV_HI[i][j].data());
        TotGraph_HI[i][j]->SetName(Form("TEL%02d_CsI%02d", i, j));
        TotGraph_HI[i][j]->SetTitle(Form("TEL%02d_CsI%02d", i, j));
        TotGraph_HI[i][j]->SetMarkerStyle(20);




      }
    }
/////////////////////////////////////////////////////////////////////////////
/// Fit for Hydrogen isotopes
/////////////////////////////////////////////////////////////////////////////
   TF2 *fH = new TF2("fH",fitfunc, 0, 1000, 100, 500, 3);
   TF1 * fProton = new TF1("fProton", fit_proton, 0, 1000, 3);
   TF1 * fDeuteron = new TF1("fDeuteron", fit_deuteron, 0, 1000, 3);
   TF1 * fTriton = new TF1("fTriton", fit_triton, 0, 1000, 3);
   fProton->SetLineColor(1);
   fDeuteron->SetLineColor(3);
   fTriton->SetLineColor(4);
   fH->SetParameters(0.005,2000,1000);

/////////////////////////////////////////////////////////////////////////////
/// Fit for Heavy Ions
/////////////////////////////////////////////////////////////////////////////
   TF2 *fHI = new TF2("fHI",HornFit, 0, 1000, 200, 500, 3);
   TF1 * fHe3 = new TF1("fHe3", fit_He3, 0, 1000, 3);
   TF1 * fHe4 = new TF1("fHe4", fit_He4, 0, 1000, 3);
   fHe3->SetLineColor(5);
   fHe4->SetLineColor(6);
   fHI->SetParameters(1,1,1);

   TCanvas *c1 = new TCanvas("c1");
   for(int i=0; i<TELNUM; i++)
   {
     //if(i!=5) continue;
     for(int j=0; j<CSINUM; j++)
     {
////////////////////////////////////////////////////////////////////////////
///  Fit for Hydrogen isotopes
///////////////////////////////////////////////////////////////////////////

//      TotGraph_H[i][j]->Fit("fH");
/*
      fProton->SetParameters(fH->GetParameters());
      fDeuteron->SetParameters(fH->GetParameters());
      fTriton->SetParameters(fH->GetParameters());
      multi_H[i][j]->Draw("APE");
      fProton->Draw("SAME");
      fDeuteron->Draw("SAME");
      fTriton->Draw("SAME");
*/

  //     TotGraph_HI[i][j]->Draw("P");
       TotGraph_HI[i][j]->Fit("fHI");
       fHI->Draw("SURF");


      //fHe3->SetParameters(fHI->GetParameters());
      //fHe4->SetParameters(fHI->GetParameters());
//      multi_HI[i][j]->Draw("APL");
      //fHe3->Draw("SAME");
      //fHe4->Draw("SAME");



      gPad->Modified();
      gPad->Update();
      getchar();
     }
   }




}
