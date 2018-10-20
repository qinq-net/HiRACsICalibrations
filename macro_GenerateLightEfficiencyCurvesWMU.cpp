//_______________________________________________________________________________

std::vector <double> ParticleEnergy; //MeV/u
std::vector <double> LiseELoss[NUM_MODELS];   //MeV/micron
std::vector <double> ParticleEnergyRange; //MeV/u
std::vector <double> LiseRange[NUM_RANGE_MODELS]; //micron

double Emax; //MeV/u
double Emin; //MeV/u
double ERangeMax; //MeV/u
double ERangeMin; //MeV/u
double RangeMin[NUM_RANGE_MODELS]; //micron
double RangeMax[NUM_RANGE_MODELS]; //micron

ROOT::Math::Interpolator SplineInterpolator[NUM_MODELS];

nuclear_masses *NucData=new nuclear_masses("Nuclear_Masses/masses.conf");

double TF1Derivative(TF1 * theFunc, double x, double step = 0.001)
{
   return (theFunc->Eval(x-2*step)-8*theFunc->Eval(x-step)+8*theFunc->Eval(x+step)-theFunc->Eval(x-2*step))/(12*step);
}
//_______________________________________________________________________________
//______________________________________________
int LoadEnergyLossFile(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    printf("Error: error while reading energy loss file\n");
    return -1;
  }

  ParticleEnergy.clear();

  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    double energy;
    double eloss;

    for(int i=0; i<NUM_MODELS; i++) {
      LineStream >> energy >> eloss;
      LiseELoss[i].push_back(eloss);
    }

    ParticleEnergy.push_back(energy);

    NRead++;
  }

  Emin=ParticleEnergy[0];
  Emax=ParticleEnergy[ParticleEnergy.size()-1];

  for(int i=0; i<NUM_MODELS; i++) {
    SplineInterpolator[i].SetData(ParticleEnergy,LiseELoss[i]);
  }

  return NRead;
}

void macro_GenerateLightEfficiencyCurvesWMU()
{
  int Z=1;
  int A=1;
  const int LISEModel=1;

//  std::string FileOutTag("InVoltage");
  std::string FileOutTag("InChannel");

  ifstream FileIn(Form("calibrations/WMUDataFullInfo.dat"));
  ofstream FileOut(Form("calibrations/LightEfficiencyDataWMU%s_Z%02d_A%02d.dat",FileOutTag.c_str(), Z, A));
  FileOut << setw(10) << "*tel" << setw(10) << "numcsi" << setw(10) << "Z" << setw(10) << "A" << setw(20) << "-dE/dx (MeV/um)" << setw(20) << "Leff" << setw(20) << "LeffErrUp" << setw(20) << "LeffErrLow\n";

  std::vector<double> LightOutput[12][4];
  std::vector<double> EnergyValues[12][4];
  std::vector<double> LightOutputError[12][4];
  std::vector<double> EnergyValuesError[12][4];
  std::vector<double> EnergyValuesSistematicError[12][4];
  std::vector<double> ZValues[12][4];
  std::vector<double> AValues[12][4];
  //ROOT::Math::Interpolator SplineInterpolator[12][4];

  TGraphErrors * LightEnergyGraph [12][4];

  TGraphAsymmErrors * LightEfficiencyGraph [12][4];
  TGraphAsymmErrors * LightEfficiencyGraph_Energy [12][4];
  std::vector<double> LightEfficiencyGraphData[12][4];
  std::vector<double> LowerErrLightEfficiencyGraphData[12][4];
  std::vector<double> UpperErrLightEfficiencyGraphData[12][4];
  std::vector<double> StoppingPowerGraphData[12][4];
  std::vector<double> EnergyGraphData[12][4];


  if(LoadEnergyLossFile(Form("input/LISE_ELoss_Z%02d_A%02d_%s.dat", Z, A, "CsI"))<=0) {
    printf("Error: information not present for Z=%d A=%d material=%s\n", Z, A, "CsI");
    return;
  }


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
    double Ch;
    double err_Ch;
    double V;
    double err_V;
    double E;
    double err_E;

    LineStream >> numtel >> numcsi >> Zread >> Aread >> Ch >> err_Ch >> V >> err_V >> E >> err_E;
    if(Zread!=Z || Aread!=A) continue;

    LightOutput[numtel][numcsi].push_back(Ch);
    EnergyValues[numtel][numcsi].push_back(E);
    LightOutputError[numtel][numcsi].push_back(err_Ch/0.1);
    EnergyValuesError[numtel][numcsi].push_back(E*0.01);
    EnergyValuesSistematicError[numtel][numcsi].push_back(err_E);
  }
  
  TF1 * FitLinear = new TF1("FitLinear","pol1",0,2000);
  TF1 * FitGamma = new TF1("FitGamma","[0]+[1]*x^[2]",0,2000);
  TF1 * FitGammaMax = new TF1("FitGammaMax","[0]+[1]*x^[2]",0,2000);
  TF1 * FitGammaMin = new TF1("FitGammaMin","[0]+[1]*x^[2]",0,2000);
  TF1 * FitJerzy = new TF1("FitJerzy","[0]+[1]*x*(x+[2])/(x+[3])",0,2000);
  FitGamma->SetParameters(60,4,1);
  FitJerzy->SetParameters(60,4,4,1);
  TF1 * FitFuncDerivative  = new TF1("FitFuncDerivative","pol1",0,2000);
  TF1 * FitHornLike = new TF1("FitHornLike","[0]+[1]*(x-[2]*log((x+[2])/[2]))",0,2000);

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
      if(EnergyValues[i][j].size()==0) continue;
      if(j!=0) continue;
      LightEnergyGraph[i][j]= new TGraphErrors(EnergyValues[i][j].size(),EnergyValues[i][j].data(),LightOutput[i][j].data(),EnergyValuesError[i][j].data(),LightOutputError[i][j].data());
      LightEnergyGraph[i][j]->Draw("APE*");
      LightEnergyGraph[i][j]->Fit("FitGamma");
      FitGammaMin->SetParameters(FitGamma->GetParameter(0), FitGamma->GetParameter(1), FitGamma->GetParameter(2)-FitGamma->GetParError(2));
      FitGammaMax->SetParameters(FitGamma->GetParameter(0), FitGamma->GetParameter(1), FitGamma->GetParameter(2)+FitGamma->GetParError(2));
      
      FitGammaMin->Draw("SAME");
      FitGammaMax->Draw("SAME");
      
      gPad->Modified();
      gPad->Update();
      getchar();
    }
  }

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
      if(EnergyValues[i][j].size()==0) continue;
      if(j!=0) continue;
       LightEnergyGraph[i][j]->Draw("AP *");
       int NumSteps=5;
       double EnergyStepData = (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])/300;
       for(int k=0; k<NumSteps; k++) {
         double Energy = EnergyValues[i][j][0]+ (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*(k+1)/NumSteps - (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*0.5/NumSteps;
         double minIntervaLocal = Energy-5*EnergyStepData;
         double maxIntervaLocal = Energy+5*EnergyStepData;

         double Derivative=-9999;
	 double UpperDerivative = -9999;
	 double LowerDerivative = -9999;

         //LightEnergyGraph[i][j]->Fit("FitFuncLocal","","",0,15);

         //FitFuncDerivative->SetParameter(0,FitFuncLocal->GetParameter(1));
         //FitFuncDerivative->SetParameter(1,2*FitFuncLocal->GetParameter(2));
         Derivative = pow(Energy,FitGamma->GetParameter(2)-1)*FitGamma->GetParameter(1)*FitGamma->GetParameter(2);
	 UpperDerivative = pow(Energy,FitGammaMax->GetParameter(2)-1)*FitGammaMax->GetParameter(1)*FitGammaMax->GetParameter(2);
	 LowerDerivative = pow(Energy,FitGammaMin->GetParameter(2)-1)*FitGammaMin->GetParameter(1)*FitGammaMin->GetParameter(2);

          //LightEnergyGraph[i][j]->Draw("AP *");
          //LightEnergyGraph[i][j]->GetXaxis()->SetRangeUser(minIntervaLocal-2*EnergyStepData,maxIntervaLocal+2*EnergyStepData);
          //LightEnergyGraph[i][j]->GetYaxis()->SetRangeUser(LightEnergyGraph[i][j]->Eval(minIntervaLocal-2*EnergyStepData),LightEnergyGraph[i][j]->Eval(maxIntervaLocal+2*EnergyStepData));
          //gPad->Modified();
          //gPad->Update();
          //getchar();

         LightEfficiencyGraphData[i][j].push_back(Derivative);
	 LowerErrLightEfficiencyGraphData[i][j].push_back(Derivative-LowerDerivative);
	 UpperErrLightEfficiencyGraphData[i][j].push_back(UpperDerivative-Derivative);
         StoppingPowerGraphData[i][j].push_back(SplineInterpolator[LISEModel].Eval(Energy/NucData->get_mass_Z_A_uma(Z,A)));
         EnergyGraphData[i][j].push_back(Energy);
         FileOut << setw(10) << i << setw(10) << j << setw(10) << Z << setw(10) << A << setw(20) << SplineInterpolator[LISEModel].Eval(Energy/NucData->get_mass_Z_A_uma(Z,A)) << setw(20) << Derivative << setw(20) << UpperDerivative-Derivative << setw(20) << Derivative-LowerDerivative << endl;
       }
    }
  }

  double ELoss20MeV = SplineInterpolator[LISEModel].Eval(20/NucData->get_mass_Z_A_uma(Z,A));
  double ELoss100MeV = SplineInterpolator[LISEModel].Eval(100/NucData->get_mass_Z_A_uma(Z,A));
  double ELoss200MeV = SplineInterpolator[LISEModel].Eval(200/NucData->get_mass_Z_A_uma(Z,A));
  double ELoss300MeV = SplineInterpolator[LISEModel].Eval(300/NucData->get_mass_Z_A_uma(Z,A));
  printf("dE/dX 20 MeV = %f MeV/um\ndE/dX 100 MeV = %f MeV/um\ndE/dX 200 MeV = %f MeV/um\ndE/dX 300 MeV = %f MeV/um\n", ELoss20MeV, ELoss100MeV, ELoss200MeV, ELoss300MeV);

  TCanvas * c1 = new TCanvas("c1","",1368,756);
  c1->SetLogy(true);
  c1->Divide(3,1);

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
      if(EnergyValues[i][j].size()==0) continue;
      if (j!=0) continue;
      LightEfficiencyGraph[i][j] = new TGraphAsymmErrors(StoppingPowerGraphData[i][j].size(), StoppingPowerGraphData[i][j].data(), LightEfficiencyGraphData[i][j].data(),0,0,LowerErrLightEfficiencyGraphData[i][j].data(),UpperErrLightEfficiencyGraphData[i][j].data());
      LightEfficiencyGraph_Energy[i][j] = new TGraphAsymmErrors(StoppingPowerGraphData[i][j].size(), EnergyGraphData[i][j].data(), LightEfficiencyGraphData[i][j].data(),0,0,LowerErrLightEfficiencyGraphData[i][j].data(),UpperErrLightEfficiencyGraphData[i][j].data());

      c1->cd(1);
      LightEnergyGraph[i][j]->Draw("AL");
      c1->cd(2);
      LightEfficiencyGraph_Energy[i][j]->Draw("AL *");
      c1->cd(3);
      LightEfficiencyGraph[i][j]->Draw("ALPE");



      /*
      TLine ELoss20MeVLine(ELoss20MeV,LightEfficiencyGraph[i][j]->GetYaxis()->GetXmin(),ELoss20MeV,LightEfficiencyGraph[i][j]->GetYaxis()->GetXmax());
      TLine ELoss100MeVLine(ELoss100MeV,LightEfficiencyGraph[i][j]->GetYaxis()->GetXmin(),ELoss100MeV,LightEfficiencyGraph[i][j]->GetYaxis()->GetXmax());
      TLine ELoss200MeVLine(ELoss200MeV,LightEfficiencyGraph[i][j]->GetYaxis()->GetXmin(),ELoss200MeV,LightEfficiencyGraph[i][j]->GetYaxis()->GetXmax());
      TLine ELoss300MeVLine(ELoss300MeV,LightEfficiencyGraph[i][j]->GetYaxis()->GetXmin(),ELoss300MeV,LightEfficiencyGraph[i][j]->GetYaxis()->GetXmax());
      ELoss20MeVLine.Draw("SAME");
      ELoss100MeVLine.Draw("SAME");
      ELoss200MeVLine.Draw("SAME");
      ELoss300MeVLine.Draw("SAME");
      */
      
      gPad->Modified();
      gPad->Update();
      getchar();
      
    }
  }

  FileIn.close();
  FileOut.close();



}
