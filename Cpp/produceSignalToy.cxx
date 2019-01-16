/* Compile with
g++ produceSignalToy.cxx -o produceSignalToy `root-config --glibs --cflags` -lRooFit -lRooFitCore
*/

#include "iostream"
#include "getopt.h"
#include "string"

#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooDataHist.h"

using namespace RooFit;

int Usage();

int main( int narg,char* argv[] ) {
  std::string outFileName = "signalToy.root";
  bool draw = false;
  int nEvents = 100000;
  double lowRange = 70;
  double upRange = 200;
  double meanValue = 125;
  double sigmaValue = 10;
  int rescale = -1;
  int nBins = 26;

  /* ===================================================================== */
  // Parse Input Arguments
  if ( narg > 1 ) {
    static struct option long_options[] = {
      { "help"           , no_argument       , 0 , 'h'},
      { "outputFile"     , optional_argument , 0 , 'f'},
      { "nEvents"        , optional_argument , 0 , 'n'},
      { "lowRange"       , optional_argument , 0 , 'l'},
      { "upRange"        , optional_argument , 0 , 'u'},
      { "nBins"          , optional_argument , 0 , 'b'},
      { "mean"           , optional_argument , 0 , 'm'},
      { "sigma"          , optional_argument , 0 , 's'},
      { "rescale"        , optional_argument , 0 , 'r'},
      { "draw"           , no_argument       , 0 , 'd'}
    };

    int option_index = 0;
    int c = 0;
    do {
      c = getopt_long( narg, argv, "n:f:l:u:m:s:b:r:dh", long_options, &option_index);
      switch (c) {
      case 'h':
	return Usage();
      case 'm':
	std::cout<< Form("Setting mean of the distribution to %.1f",std::stod( optarg)) << std::endl;
	meanValue = std::stod( optarg );
	break;
      case 's':
	std::cout<< Form("Setting sigma of the distribution to %.1f",std::stod( optarg)) << std::endl;
	sigmaValue = std::stod( optarg );
	break;
      case 'r':
	std::cout<< Form("Setting rescale of histogram to %d", std::stoi( optarg )) << std::endl;
	rescale = std::stoi( optarg );
	break;
      case 'f':
	std::cout<< Form("Setting output file name to \"%s\"",optarg) << std::endl;
	outFileName = std::string( optarg );
	if ( outFileName.find(".root") == std::string::npos ||
	     outFileName.find(".root") + 5 != outFileName.length() ) {
	  std::cout<< "Filename must end with '.root'" << std::endl;
	  return EXIT_FAILURE;
	}
	break;
      case 'n':
	std::cout<< Form("Setting number of simulated events to %d",std::stoi( optarg )) << std::endl;
	nEvents = std::stoi( optarg );
	break;
      case 'l':
	std::cout<< Form("Setting min range to %.0f",std::stod( optarg )) << std::endl;
	lowRange = std::stod( optarg );
	break;
      case 'u':
	std::cout<< Form("Setting max range to %.0f",std::stod( optarg )) << std::endl;
	upRange = std::stod( optarg );
	break;
      case 'b':
	std::cout<< Form("Setting number of bins to %d",std::stoi( optarg )) << std::endl;
	nBins = std::stoi( optarg );
	break;
      case 'd':
	std::cout<<"Setting draw option to True. The resulting simulated data will be drawn."<<std::endl;
	draw = true;
	break;
      case '?':
	return EXIT_FAILURE;
      }
	
    } while (c != -1);
  }

  std::cout<<std::endl;
  std::cout<<"Settings: "<< std::endl;
  std::cout<<"   Producing output file named: " << outFileName << std::endl;
  std::cout<<"   Number of simulated events: "<< nEvents << std::endl;
  if ( rescale > 0 )
    std::cout<<"     * Rescaling normalization to "<< rescale << std::endl;
  std::cout<<"   Distribution : mean "<< meanValue <<" : sigma "<< sigmaValue << std::endl; 
  std::cout<<"   Observable range: "<< lowRange <<" -- "<< upRange <<" [" << nBins <<" bins] "<<std::endl;
  std::cout<<std::endl;

  /* ===================================================================== */

  std::unique_ptr< TFile > outFile( new TFile(outFileName.c_str(),"recreate") );

  // Define Observable
  RooRealVar x("x","x",lowRange,upRange);

  // Define Function Parameters
  RooRealVar mean("mean","mean",meanValue);
  RooRealVar sigma("sigma","sigma",sigmaValue);

  // Define Pdf
  RooGaussian gaussian("gaussian","gaussian",x,mean,sigma);

  // Create Simulated Data
  std::unique_ptr< RooDataSet > simulatedSignalUnbinned( gaussian.generate(x,nEvents) );
  TH1D *simulatedSignalHistogram = (TH1D*) simulatedSignalUnbinned->createHistogram("x",nBins);
  if ( rescale > 0 )
    simulatedSignalHistogram->Scale( rescale/simulatedSignalHistogram->Integral() );

  // Store results into TFile
  outFile->cd();
  simulatedSignalHistogram->SetNameTitle("SimulatedSignal","SimulatedSignal");
  simulatedSignalHistogram->Write();

  if ( draw ) {
    TCanvas c0;
    simulatedSignalHistogram->Draw("HIST");
    c0.Draw();
    c0.Update();
    std::string outputPlotName = outFileName;
    outputPlotName.replace( outputPlotName.find(".root"),5,".pdf" );
    c0.SaveAs( outputPlotName.c_str() );
  }

  outFile->Close();
}

/* ===================================================================== */
int Usage() {
  std::cout<<"Usage:"<<std::endl;
  std::cout<<"  "<< "--help             (-h) : print instructions" << std::endl;
  std::cout<<"  "<< "--draw             (-d) : save the drawn resulting simulated data : default 'false'" << std::endl;
  std::cout<<"  "<< "--outputFile <arg> (-f) : define the name of the output TFile : default 'backgroundToy.root'" << std::endl;
  std::cout<<"  "<< "--nEvents <arg>    (-n) : number of events to be simulated : default '100000'" << std::endl;
  std::cout<<"  "<< "--lowRange <arg>   (-l) : minimum of the range for the observable x : default '70'" << std::endl;
  std::cout<<"  "<< "--upRange <arg>    (-u) : maximum of the range for the observable x : default '200'" << std::endl;
  std::cout<<"  "<< "--mean <arg>       (-m) : mean of the gaussian distribution : default 125 " << std::endl;
  std::cout<<"  "<< "--sigma <arg>      (-s) : sigma of the gaussian distribution : default 10 " << std::endl;
  std::cout<<"  "<< "--rescale <arg>    (-r) : rescaling event normalization if positive integer : default -1 " << std::endl;
  std::cout<<"  "<< "--nBins <arg>      (-b) : number of bins of the output histogram : default '26'" << std::endl;
  return 0;
}

