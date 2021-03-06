#include "Nuclear_Masses/nuclear_masses.h"
#include "include/RelativisticKinematics.h"
#include "include/HiRACsICalibration.h"


const int Z_target = 1;
const int A_target = 1;
const double target_thickness =116.19; //um (9.8 mg/cm2)
const int Z_beam = 20;


//---- For Run2013 - Run 2037
const int A_beam = 40;
const double E_projectile = 39; //MeV/u       err: +/- 0.5%
const double errE_projectile =0.005 * E_projectile;
const int csi_gain_setting=200;
const int FirstRun = 2013;
const int LastRun = 2037;
const double tilt_angle =0.; //degF


/*
//---- For Run2312 - Run 2312
const int A_beam = 40;
const double E_projectile = 56.6; //MeV/u    err: +/- 0.5%
const double errE_projectile =0.005 * E_projectile;
const int csi_gain_setting=170;
const int FirstRun = 2312;
const int LastRun = 2312;
const double tilt_angle =0.; //degF
*/

/*
  //---- For Run2825 - Run 2829
  const int A_beam = 40;
  const double E_projectile = 139.8; //MeV/u    err: +/- 0.2%
  const double errE_projectile =0.002 * E_projectile;
  const int csi_gain_setting=130;
  const int FirstRun = 2825;
  const int LastRun = 2829;
  const double tilt_angle =0.; //degF
*/

/*
  //---- For Run4000 - Run 4005
  const int A_beam = 48;
  const double E_projectile = 139.8; //MeV/u    err: +/- 0.2%
  const double errE_projectile =0.002 * E_projectile;
  const int csi_gain_setting=170;
  const int FirstRun = 4000;
  const int LastRun = 4005;
  const double tilt_angle =0.; //degF
*/

/*
//---- For Run4021 - Run 4022
const int A_beam = 48;
const double E_projectile = 139.8; //MeV/u    err: +/- 0.2%
const double errE_projectile =0.002 * E_projectile;
const int csi_gain_setting=170;
const int FirstRun = 4021;
const int LastRun = 4022;
const double tilt_angle =0.; //degF
*/


/*
//---- For Run4034 - Run 4037
const int A_beam = 48;
const double E_projectile =28; //MeV/u    err: +/- 0.5%
const double errE_projectile =0.005 * E_projectile;
const int csi_gain_setting=170;
const int FirstRun = 4034;
const int LastRun = 4037;
const double tilt_angle =0.; //degF
*/

/*
//---- For Run4332 - Run4332
const int A_beam = 48;
const double E_projectile = 56.6; //MeV/u   err: +/- 0.5%
const double errE_projectile =0.005 * E_projectile;
const int csi_gain_setting=170;
const int FirstRun = 4332;
const int LastRun = 4332;
const double tilt_angle =0.; //degF
*/

/*
//---- For Run4577 - Run4584
const int A_beam = 48;
const double E_projectile = 28; //MeV/u      err: +/- 0.5%
const double errE_projectile =0.005 * E_projectile;
const int csi_gain_setting=170;
const int FirstRun = 4577;
const int LastRun = 4584;
const double tilt_angle =30.; //degF
*/

/*
//---- For Run4585 - Run4589
const int A_beam = 48;
const double E_projectile = 56.6; //MeV/u   err: +/- 0.5%
const double errE_projectile =0.005 * E_projectile;
const int csi_gain_setting=170;
const int FirstRun = 4585;
const int LastRun = 4589;
const double tilt_angle =30.; //degF
*/


// par[0] = E_Projectile
// par[1] = M_Projectile uma
// par[2] = M_Target uma
// par[3] = Eecc_Projectile MeV
double KinematicLine(double *x, double *par)
{
  RelativisticKinematics KinematicModule;
  double DegToRad = TMath::Pi()/180.;

  double TheoreticalEnergy=KinematicModule.GetEnergyTwoBodyRecoil(x[0]*DegToRad, par[0], par[1], par[2], par[3]);

  return TheoreticalEnergy;
}

// par[0] = E_Projectile
// par[1] = M_Projectile uma
// par[2] = M_Target uma
// par[3] = Eecc_Projectile MeV
// par[4] = target_thickness um
// par[5] = target_tilt_angle deg
// par[6] = SnPb thickness
// par[7] = Mylar thickness
double KinematicLineCorrected(double * x, double * par) {
  EnergyLossModule LISECalc;
  double DegToRad = TMath::Pi()/180.;
  char target_material[]="CH2";

  double TheoreticalEinc=par[0]*par[1];
  double InteractionPoint=(par[4]/2.)/cos(par[5]*DegToRad);
  double CorrectedEinc=TheoreticalEinc-LISECalc.GetEnergyLoss(Z_beam, A_beam, TheoreticalEinc, target_material, InteractionPoint);
  double CrossedTarget=(par[4]/2.)/cos((x[0]-par[5])*DegToRad);

  par[0]=CorrectedEinc/par[1];
  double TheoreticalEnergy=KinematicLine(x, par);

  EnergyLoss=LISECalc.GetEnergyLoss(1, 1, TheoreticalEnergy, target_material, CrossedTarget);
  DegradedEnergy=TheoreticalEnergy-EnergyLoss;
  EnergyLoss=LISECalc.GetEnergyLoss(1, 1, DegradedEnergy, "SnPb", par[6]);
  DegradedEnergy=DegradedEnergy-EnergyLoss;
  EnergyLoss=LISECalc.GetEnergyLoss(1, 1, DegradedEnergy, "Mylar", par[7]);
  DegradedEnergy=DegradedEnergy-EnergyLoss;

  return DegradedEnergy;
}

// par[0] = E_Projectile
// par[1] = M_Projectile uma
// par[2] = M_Target uma
// par[3] = Eecc_Projectile MeV
// par[4] = target_thickness um
// par[5] = target_tilt_angle deg
// par[6] = SnPb thickness
// par[7] = Mylar thickness
// par[8] = Si thickness
// par[9] = CsIMylar thickness
double KinematicLineCsI(double *x, double *par)
{
  EnergyLossModule LISECalc;
  double DegToRad = TMath::Pi()/180.;

  double CorrectedEnergyOnSi=KinematicLineCorrected(x, par);
  double EnergyLoss;
  double DegradedEnergy;
  EnergyLoss=LISECalc.GetEnergyLoss(1,1,CorrectedEnergyOnSi, "Si", par[8]);
  DegradedEnergy=CorrectedEnergyOnSi-EnergyLoss;
  EnergyLoss+=LISECalc.GetEnergyLoss(1,1,DegradedEnergy, "Mylar", par[9]);

  return CorrectedEnergyOnSi-EnergyLoss;
}


void CsIKinematicPointsCorrection()
{

// TCanvas *c1=new TCanvas("c1","",1200,800);
// c1->Divide(2,1);

   //--------- identify a theta mean, min and max of data I got in last step ----------------------------------------------------------------------
   ifstream FileInOfInitialGeo(Form("12KinematicLineProjection/NewGeo_HiRA_CsIKinematics_FullInfo_%4d_%4d_%dCa%.1fAMeV_gain%4d.dat", FirstRun, LastRun, A_beam, E_projectile, csi_gain_setting));
   ifstream FileInOfBeamShift(Form("13KinematicCorrectionWithBeamShift/pixelAngleWithError_%.1fMeV.dat", E_projectile));

   ofstream FileOutCorrected(Form("13KinematicCorrectionWithBeamShift/Corrected_HiRA_CsIKinimatics_%4d_%4d_%dCa%.1fAMeV_gain%4d.dat", FirstRun, LastRun, A_beam, E_projectile, csi_gain_setting));
   FileOutCorrected<<setw(5)<< "*telnum" <<"  "<<setw(5)<< "csinum"<<"  "<<setw(10)<<"CsI V"<<"  "<<setw(15)<<"err_CsI V"<<"  "<<setw(10)<<"energy"<<"  "<<setw(15)<<"corrected_err_energy\n";

   double SnPbThickness =18.;
   double MylarThickness =1.47; //um
   double TelSiThickness[12];
   TelSiThickness[0]=1537; TelSiThickness[1]=1521; TelSiThickness[2] =1500; TelSiThickness [3]=1496;
   TelSiThickness[4]=1517; TelSiThickness[5]=1512; TelSiThickness[6] =1491; TelSiThickness [7]=1460;
   TelSiThickness[8]=1537; TelSiThickness[9]=1536; TelSiThickness[10]=1471; TelSiThickness[11]=1491;
   double CsIMylarThickness =2.076; //um
   double UMA_MeV =931.494028; //MeV
   nuclear_masses NuclearDatabase("Nuclear_Masses/masses.conf");
   double mass_beam =NuclearDatabase.get_mass_Z_A(Z_beam, A_beam)/UMA_MeV;
   double mass_target =NuclearDatabase.get_mass_Z_A(Z_target, A_target)/UMA_MeV;

   HiRACsICalibrationManager CsICalibrationModule;
   CsICalibrationModule.LoadPulserInfo(Form("calibrations/HiRA_CsI_Pulser_%dsetting.dat",csi_gain_setting));


//---------------------------------------------------------------------------------------------------------
// ***************
// ****************    Begin our analysis here   ***************************************
//---------------------------------------------------------------------------------------------------------

  //------- Retrieving protons data -------------------------------------------


  //--- Definition of the number of data points of each telescope ----------
  int Npoints[12][4];
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      Npoints[i][j]=0;
    }
  }


  //-------------------------------------------------------------------------------------------
  //---- 1. get the mean ThetaMean, ThetaMin, ThetaMax values from the input file
  //-------------------------------------------------------------------------------------------
  double ECsI_Ch[12][4][100]={{{0}}};   // Energy in CsI (Channel), we get this values by projection-> gaussian fit / get mean values
  double err_ECsI_Ch[12][4][100]={{{0}}}; // this error comes from the error of gaussian fit/ RMS of mean values
  double ThetaMean[12][4][100]={{{0}}}; // we select a range of theta (X axis) to make projection to Y axis. From this range, we get ThetaMean
  double ThetaMin[12][4][100]={{{0}}}; // Thetamin and ThetaMax
  double ThetaMax[12][4][100]={{{0}}};
  double EnergyValue[12][4][100]={{{0}}};  //  Use ThetaMean to calculate the energy of elastic protons
  double err_EnergyValue[12][4][100]={{{0}}}; //
  double corrected_err_EnergyValue[12][4][100]={{{0}}};
  double CsI_V[12][4][100]={{{0}}};
  double err_CsI_V[12][4][100]={{{0}}};
  while (FileInOfInitialGeo.is_open() && !FileInOfInitialGeo.eof())
  {
    std::string LineRead;
    std::getline(FileInOfInitialGeo, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int telnum;
    int csinum;

    LineStream>> telnum >> csinum ;
    LineStream>> ECsI_Ch[telnum][csinum][Npoints[telnum][csinum]] >> err_ECsI_Ch[telnum][csinum][Npoints[telnum][csinum]] >> ThetaMean[telnum][csinum][Npoints[telnum][csinum]] >> ThetaMin[telnum][csinum][Npoints[telnum][csinum]] >> ThetaMax[telnum][csinum][Npoints[telnum][csinum]] >> EnergyValue[telnum][csinum][Npoints[telnum][csinum]] >> err_EnergyValue[telnum][csinum][Npoints[telnum][csinum]] >> CsI_V[telnum][csinum][Npoints[telnum][csinum]] >>err_CsI_V[telnum][csinum][Npoints[telnum][csinum]];

 //   cout<< telnum <<setw(10)<<csinum<<setw(10)<<ThetaMin[telnum][csinum][Npoints[telnum][csinum]]<<setw(10)<<ThetaMax[telnum][csinum][Npoints[telnum][csinum]]<<endl;

    if(err_EnergyValue[telnum][csinum][Npoints[telnum][csinum]]==0) continue;
    if(err_CsI_V[telnum][csinum][Npoints[telnum][csinum]]==0) continue;
    Npoints[telnum][csinum]++;
  }

  //------------- Read data points values of beam shift datas from Farnus --------------------------------------------------------
  double PixelTheta[12][32][32];  // degree
  double err_PixelTheta[12][32][32]; // degree
  double PixelPhi[12][32][32];
  double err_PixelPhi[12][32][32];
  while(FileInOfBeamShift.is_open() && !FileInOfBeamShift.eof())
  {
    std::string LineRead;
    std::getline(FileInOfBeamShift, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int telnum;
    int FrontStripNum;
    int BackStripNum;

    LineStream>> telnum >> FrontStripNum >> BackStripNum;
    LineStream>> PixelTheta[telnum][FrontStripNum][BackStripNum]>> err_PixelTheta[telnum][FrontStripNum][BackStripNum] >>PixelPhi[telnum][FrontStripNum][BackStripNum] >>err_PixelPhi[telnum][FrontStripNum][BackStripNum];
//    cout<<PixelTheta[telnum][FrontStripNum][BackStripNum]<<setw(10)<<err_PixelTheta[telnum][FrontStripNum][BackStripNum]<<endl;
  }

  //-------------------------------------------------------------------------------------------------------------------------
  //--- 2. make pixel match with a CsI, and get all the pixels inside the particular crystal of the particular telescope
  //--- 3. do the average of the errors on the theta of all the selected pixels that lie between thetamin and thetamax
  //--------------------------------------------------------------------------------------------------------------------------
  double AverageThetaErr[12][4][100]={{{0}}};
  for(int TelNum=0; TelNum<12; TelNum++)
  {
    for(int CsINum=0; CsINum<4; CsINum++)
    {
      for(int Npoints=0; Npoints<5; Npoints++)
      {
         if(ThetaMin[TelNum][CsINum][Npoints]==0) continue; // data of some telescopes do not exit

         int NSamples=0;
         double SumThetaErr=0;
         for(int FStripNum=0; FStripNum<32; FStripNum++)
         {
           for(int BStripNum=0; BStripNum<32; BStripNum++)
           {
             if((FStripNum/16)==(CsINum/2) && (BStripNum/16)!=abs(CsINum/2-CsINum%2))
             {
               if(PixelTheta[TelNum][FStripNum][BStripNum]>ThetaMin[TelNum][CsINum][Npoints] && PixelTheta[TelNum][FStripNum][BStripNum]<ThetaMax[TelNum][CsINum][Npoints])
               {
//               cout<<TelNum<<setw(10)<<CsINum<<setw(10)<<ThetaMin[TelNum][CsINum][Npoints]<<setw(10)<<ThetaMax[TelNum][CsINum][Npoints]<<setw(10)<<PixelTheta[TelNum][FStripNum][BStripNum]<<setw(10)<<err_PixelTheta[TelNum][FStripNum][BStripNum]<<endl;
                 NSamples++;
                 SumThetaErr+=err_PixelTheta[TelNum][FStripNum][BStripNum];
               }
             }
           }
         }
         AverageThetaErr[TelNum][CsINum][Npoints]=SumThetaErr/NSamples;
//       cout<< TelNum << setw(5)<< CsINum <<setw(5)<< Npoints <<setw(5)<< NSamples <<setw(10)<< SumThetaErr<<setw(10)<< SumThetaErr/NSamples <<setw(10)<< AverageThetaErr[TelNum][CsINum][Npoints] <<endl;

         //-------------------------------------------------------------------------------------------
         //--- 4. use ThetaMean to calculate the energy of the point
         //--- 5. use AverageThetaErr to calculate the error on energy
         //-------------------------------------------------------------------------------------------
         // The first set of parameters are used for calculating the error caused by theta
         double par_theta[10];
         par_theta[0]=E_projectile;
         par_theta[1]=mass_beam;
         par_theta[2]=mass_target;
         par_theta[3]=0;
         par_theta[4]=target_thickness;
         par_theta[5]=tilt_angle;
         par_theta[6]=SnPbThickness;
         par_theta[7]=MylarThickness;
         par_theta[8]=TelSiThickness[TelNum];
         par_theta[9]=CsIMylarThickness;

         // The second set of parameters are used for calculating the error caused by the error of incident energy
         double par_E[10];
         par_E[0]=E_projectile + errE_projectile; // add the error of incident energy to calculate
         par_E[1]=mass_beam;
         par_E[2]=mass_target;
         par_E[3]=0;
         par_E[4]=target_thickness;
         par_E[5]=tilt_angle;
         par_E[6]=SnPbThickness;
         par_E[7]=MylarThickness;
         par_E[8]=TelSiThickness[TelNum];
         par_E[9]=CsIMylarThickness;

         // To calculate the error caused by theta
         double EnergyValue_theta = KinematicLineCsI(&ThetaMean[TelNum][CsINum][Npoints], par_theta);  //Use ThetaMean to calculate the Kinematic energy of scattering protons
         double MaxErrTheta = ThetaMean[TelNum][CsINum][Npoints]+AverageThetaErr[TelNum][CsINum][Npoints]; //use beam shift corrected data to estimate the error of energy
         double err_EnergyValue1 = fabs(KinematicLineCsI(&MaxErrTheta, par_theta) - EnergyValue_theta); // error caused by beam shift correction
         double err_EnergyValue2 = fabs(KinematicLineCsI(&(ThetaMax[TelNum][CsINum][Npoints]), par_theta) - EnergyValue_theta); // error caused by the method to take kinematic points
         double err_EnergyValue3  = max(err_EnergyValue1, err_EnergyValue2);  // take the biggger one as the error causes by theta

         // To calculate the error caused by incident energy
         double EnergyValue_E =  KinematicLineCsI(&ThetaMean[TelNum][CsINum][Npoints], par_E);
         double err_EnergyValue4  = fabs(EnergyValue_E - EnergyValue_theta);

         //the total error
         double err_EnergyValue = sqrt(err_EnergyValue3 * err_EnergyValue3 + err_EnergyValue4 * err_EnergyValue4);

         FileOutCorrected<<setw(5)<< TelNum <<"  "<<setw(5)<< CsINum <<"  "<<setw(10)<< CsI_V[TelNum][CsINum][Npoints]<<"  "<<setw(15)<< err_CsI_V[TelNum][CsINum][Npoints] <<"  "<<setw(10)<< EnergyValue_theta <<"  "<<setw(15)<< err_EnergyValue <<endl;

       }
    }
  }




}
