#include <E15190Reader.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TChain.h>
#include <TH2.h>
#include <iostream>

int main (int argc, char ** argv)
{
  if(argc<=1) return -1;
  std::string data_path("/mnt/analysis/e15190/dellaqui/NW_Calibrations/output/");
  TChain *dataChain = (TChain*) new TChain("E15190");
  std::string first_run_name(argv[1]);
  int first_run = atoi(first_run_name.c_str());
  int last_run=first_run;
  Long64_t evt_amount=0;
  if(argc==4) {
    evt_amount=atoi(argv[3]);
  }
  if(argc>2) {
    std::string last_run_name(argv[2]);
    last_run = atoi(last_run_name.c_str());
  }
  // Run by Run loop ////////////////////////
  for(int cur_run=first_run; cur_run<=last_run; cur_run++)
  {
    char file_evt[100];
    sprintf (file_evt,"CalibratedData_ForwardArray_%04d*.root",cur_run);
    std::string file_evt_string(file_evt);
    std::string path_to_evt_file(data_path+file_evt_string);
    int n_files = dataChain->Add((data_path+file_evt).c_str());
    printf("%d Root files added to chain for run %d\n", n_files, cur_run);
    if(n_files<=0) continue;


    //Building framework /////////////////

    E15190Reader E15190Analyzer(dataChain, "NWB FA", 1);


    //Definition of the output file //////

    std::string FileOutName(Form("outputNW/UsefulHistograms_ForwardArray_%04d.root", cur_run));


    //Run the required method(s) /////////

    E15190Analyzer.CreateUsefulForwardArrayHistograms(FileOutName.c_str(), evt_amount);

    printf("\nproduced %s file\n", FileOutName.c_str());
  }
  // End of the main loop //////////////////
  printf("\nData Analyzed, Bye!\n");

  return 0;
}
