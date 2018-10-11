
#include "include/EnergyLossModule.h"
#include "include/HiRACsICalibration.h"

//------ definition of struct MPart ---------------------
struct MPart
{
  Double_t x, y;
  Double_t Z,A;
};

// Function for DE-E identification based
// on formulas from N. Le Neindre et al. NIM A490 (2002) 251
// modified following the formula of W. Gawlikowicz
// for Light-Energy relation in CsI(Tl)
// NIM A491 (2002) 181. Adapted by Amalia Pop following
// ref.: J. Blicharska et al. LNS report 2005
// This formula needs 14 fit parameters
Double_t func14(MPart &p, Double_t *par)
{
  Double_t X = p.x;
  Double_t Z = p.Z;
  Double_t A = p.A;
  Double_t xx,exp1,exp2,res=1.0;
  Double_t reslog,ene;

  if(Z==0 && A==0)
  {
    return par[12];
  }
  xx = X-par[13];
  bool foffset=false; //this is true for fitting procedure, false for the analysis
  //if xx<0 never reached from data analysis
  if(xx<=0)
  {
    if(foffset)
    {
      xx=X;
    }
    else
    {
      return res;
    }
  }

 exp1 = par[2] + par[3] + 1;
 exp2 = 1./exp1;
 reslog = log(1.+ par[9]* Z)*(1.- exp(-par[10]*pow(Z,par[11])))/Z;
 ene = par[6] * reslog * xx ;
 ene = ene + par[7] * Z * sqrt(A) * log(1. + par[8] * reslog  * xx);
 res = pow(ene,exp1) +
       pow((par[4]* pow(Z,par[0]) * pow(A,par[1])),exp1) +
       par[5]*pow(Z,2) * pow(A,par[2]) * pow(ene,par[3]);
 res = pow(res,exp2) - ene + par[12];
 return res;
}

//------ complete macro DEEFIT ------------
void DEEFIT()
{
  ///////////////////////////////////////////////////////////////////
  //  suggestion values: take 10 points for examples
  //   Z     A       MinChannel     MaxChannel   StepChannel
  //   1     1       120            470          35
  //   1     2       120            520          40
  //   1     3       120            570          45
  //   2     3       120            820          70
  //   2     4       120            1120         100
  //   2     6       120            1320         120
  //   3     6       120            1270         115
  //   3     7       120            1470         135
  //   3     8       120            1220          110
  //   4     7       120            1270         115
  //   4     9       120            1020         90
  //   4     10      120            920          80
  //////////////////////////////////////////////////////////////////
  int Z=4;
  int A=7;
  double MinChannel=120.;
  double MaxChannel=1270.;
  double StepChannel=115;

  const int csi_gain_setting=170;
  int LiseModel=1; // LiseModel =1 used for low energy experiments

  ifstream FileIn("calibrations/Fitparameters.dat");
  ofstream FileOut(Form("calibrations/DEEFIT__Z%02d_A%02d.dat.dat", Z, A));
  FileOut << setw(5) << "*tel  " << setw(7) << "numcsi " << setw(10) << "CsIV " << setw(10) << "errCsIV" <<"  "<< setw(10) << "CsIE" <<"  "<< setw(10) << "errCsIE\n";

  // ------- pulser calibration setting --------------------------
  HiRACsICalibrationManager CsICalibrationModule;
  CsICalibrationModule.LoadPulserInfo(Form("calibrations/HiRA_CsI_Pulser_%dsetting.dat",csi_gain_setting));
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  //-------- Energy Loss Module ----------------------------------
  double TelSiThickness[12];
  TelSiThickness[0]=1537; TelSiThickness[1]=1521; TelSiThickness[2] =1500; TelSiThickness [3]=1496;
  TelSiThickness[4]=1517; TelSiThickness[5]=1512; TelSiThickness[6] =1491; TelSiThickness [7]=1460;
  TelSiThickness[8]=1537; TelSiThickness[9]=1536; TelSiThickness[10]=1471; TelSiThickness[11]=1491;
  double CsIMylarThickness=2.076;
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  EnergyLossModule LISEModule;

  while (FileIn.is_open() && !FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int numcsi;

    int ntel;
    int mf;
    int npar;
    double par0, par1, par2, par3, par4, par5, par6, par7, par8, par9, par10, par11, par12, par13;
    double chi2;

    LineStream >> ntel >> mf >> npar ;
    LineStream >> par0 >> par1 >> par2 >> par3 >> par4 >> par5 >> par6 >> par7 >> par8 >> par9 >> par10 >> par11 >> par12 >> par13 >> chi2;

    numtel = ntel/4; // take integer
    numcsi = ntel%4;

    MPart input;
    input.Z=Z;
    input.A=A;

    double par[14];
    par[0] = par0;
    par[1] = par1;
    par[2] = par2;
    par[3] = par3;
    par[4] = par4;
    par[5] = par5;
    par[6] = par6;
    par[7] = par7;
    par[8] = par8;
    par[9] = par9;
    par[10] = par10;
    par[11] = par11;
    par[12] = par12;
    par[13] = par13;
    for(int XChannel=MinChannel; XChannel<MaxChannel; XChannel+=StepChannel)
    {
      input.x = XChannel;
      double CsIV = CsICalibrationModule.GetVoltageValue(XChannel, numtel, numcsi);
      double ESi = func14(input, par);
      double Eresidual=LISEModule.GetResidualEnergy(Z,A,ESi,"Si",TelSiThickness[numtel],LiseModel);
      double EresidualOnCsI=Eresidual-LISEModule.GetEnergyLoss(Z,A,Eresidual,"Mylar",CsIMylarThickness,LiseModel);
      double CsIE=EresidualOnCsI;
      printf("Tel %02d CsI %02d: ESi=%.3f -> ECsI=%.3f\n", numtel, numcsi, CsIV, CsIE);
      FileOut << setw(5) << numtel << setw(7) << numcsi << setw(15) << CsIV << setw(10) << 0 <<"  "<< setw(10) << CsIE <<"  "<< setw(10) << 0 <<endl;
    }
  }
  FileOut.close();
}
