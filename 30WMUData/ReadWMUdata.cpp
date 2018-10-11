
void ReadWMUdata()
{
 
  
  ifstream FileIn("WMUdata.dat");
  
  std::string FileOutTag("WMUdata");
  
  ofstream FileOutProtons;
  FileOutProtons.open(Form("output/%s_Z01_A01", FileOutTag.c_str()));
  FileOutProtons << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<<setw(10)<<"Voltage (V)"<<"  "<<setw(10)<<"err_Voltage"<< setw(10) << "Energy(MeV)" <<"  "<<setw(10)<<"err_Energy"<<" "<<setw(5)<<"Z"<<"  "<<setw(5)<<"A\n";
  
   ofstream FileOutDeuterons;
  FileOutDeuterons.open(Form("output/%s_Z01_A02", FileOutTag.c_str()));
  FileOutDeuterons << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<<setw(10)<<"Voltage (V)"<<"  "<<setw(10)<<"err_Voltage"<< setw(10) << "Energy(MeV)" <<"  "<<setw(10)<<"err_Energy"<<" "<<setw(5)<<"Z"<<"  "<<setw(5)<<"A\n";
  
  ofstream FileOut4He;
  FileOut4He.open(Form("output/%s_Z02_A04", FileOutTag.c_str()));
  FileOut4He << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<<setw(10)<<"Voltage (V)"<<"  "<<setw(10)<<"err_Voltage"<< setw(10) << "Energy(MeV)" <<"  "<<setw(10)<<"err_Energy"<<" "<<setw(5)<<"Z"<<"  "<<setw(5)<<"A\n";
  
  

  
  while(FileIn.is_open() && !FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    
    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;
    
    std::stringstream LineStream(LineRead);
    
    int HiRANum;
    int TelNum;
    int CsINum;
    int ANum;
    int ZNum;
    double ECsI;
    double Voltage=0;

    
    LineStream >> HiRANum >> TelNum >> CsINum >> ANum >> ZNum >> ECsI >> Voltage;   
    if(HiRANum!=10) continue;
    
    if(ZNum==1 && ANum==1) 
    {
       FileOutProtons<< setw(5) << TelNum <<"  "<< setw(10) << CsINum <<"  "<<setw(10)<< Voltage/1000 <<"  "<<setw(10)<< 0 << setw(10) << ECsI <<"  "<<setw(10)<< 0 <<setw(5)<< ZNum <<"  "<<setw(5)<< ANum << endl;
    }
    
    if(ZNum==1 && ANum==2) 
    {
       FileOutDeuterons<< setw(5) << TelNum <<"  "<< setw(10) << CsINum <<"  "<<setw(10)<< Voltage/1000 <<"  "<<setw(10)<< 0 << setw(10) << ECsI <<"  "<<setw(10)<< 0 <<setw(5)<< ZNum <<"  "<<setw(5)<< ANum << endl;
    }
    
    if(ZNum==2 && ANum==4) 
    {
       FileOut4He<< setw(5) << TelNum <<"  "<< setw(10) << CsINum <<"  "<<setw(10)<< Voltage/1000 <<"  "<<setw(10)<< 0 << setw(10) << ECsI <<"  "<<setw(10)<< 0 <<setw(5)<< ZNum <<"  "<<setw(5)<< ANum << endl;
    }      
  } 
   
}
