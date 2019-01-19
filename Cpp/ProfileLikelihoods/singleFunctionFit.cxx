/*
g++ singleFunctionFit.cxx -o singleFunctionFit `root-config --glibs --cflags` -lRooFit -lRooFitCore
*/

#include "iostream"
#include "getopt.h"

#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"

#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooMinimizer.h"
#include "RooMsgService.h"
#include "TGraph.h"

using namespace RooFit;

TApplication Runner("gui",0,NULL);

int Usage();
void setVerbositySettings();
void createTgraph(std::unique_ptr< RooWorkspace >&, RooAbsReal&);

bool usePolynomial = false;

int main( int narg,char* argv[] ) {

  setVerbositySettings();

  /* ===================================================================== */
  double muHinj = 0;
  bool save = false;

  if ( narg > 1 ) {
    static struct option long_options[] = {
      { "help"           , no_argument       , 0 , 'h'},
      { "inject"         , optional_argument , 0 , 'i'},
      { "poly"           , optional_argument , 0 , 'p'},
      { "save"           , no_argument       , 0 , 's'}
    };

    int option_index = 0;
    int c = 0;
    do {
      c = getopt_long( narg, argv, "i:shp", long_options, &option_index);
      switch (c) {
      case 'h':
	return Usage();
      case 'i':
	std::cout<< Form("Setting injected mu_H to %.1f",std::stod( optarg )) << std::endl;
	muHinj = std::stod( optarg );
	break;
      case 'p':
	std::cout<<"Setting background model to a polynomial"<<std::endl;
	usePolynomial = true;
	break;
      case 's':
	std::cout<<"Setting save option to True. The resuls will be saved."<<std::endl;
	save = true;
	break;
      case '?':
	return EXIT_FAILURE;
      }
      
    } while (c != -1);
  }

  /* ===================================================================== */

  // Prepare Workspace 
  std::unique_ptr< RooWorkspace > workspace( new RooWorkspace("CombinedWorkspace") );

  // Define observable
  workspace->factory("mBB[70,200]");

  // Define Background Function
  workspace->factory("def[70]");
  workspace->factory("trasl[130]");

  if ( not usePolynomial ) {
    workspace->factory("a0[37,0,500]");
    workspace->factory("a1[11,0,500]");
    workspace->factory("a2[7,0,100]");
    workspace->factory("a3[2,0,100]");
    workspace->factory("EXPR::background('@3*pow(1-(@0-@2)/@1,2)+2*@4*pow(1-(@0-@2)/@1,1)+@5*pow((@0-@2)/@1,2)',mBB,a0,a1,a2,def,trasl)");
    //  workspace->factory("EXPR::background('@1*pow(1-(@0-@6)/@5,3)+@2*3*(@0-@6)/@5*pow(1-(@0-@6)/@5,2)+3*@3*pow((@0-@6)/@5,2)*pow(1-(@0-@6)/@5,1)+@4*pow((@0-@6)/@5,3)',mBB,a0,a1,a2,a3,def,trasl)");
  } else {
    workspace->factory("a0[37,-100,100]");
    workspace->factory("a1[11,-100,100]");
    workspace->factory("a2[11,-100,100]");
    workspace->factory("EXPR::background('@1+@0*@2+@0*@3',mBB,a0,a1,a2)");
  }

  // Define Signal Function 
  workspace->factory("mean[125]");
  workspace->factory("sigma[10]");
  
  workspace->factory("Gaussian::signal(mBB,mean,sigma)");

  // Normalization and co.
  workspace->factory("nBKG[70000,0,2000000]");

  workspace->factory("muH[1,-100,100]");
  workspace->factory("prod::nSGN(muH,100)");

  // Complete Model
  workspace->factory("SUM::model(nBKG*background,nSGN*signal)");

  // Print
  std::cout<<std::endl<<"==========================================================================================="<<std::endl<<std::endl;
  workspace->Print();
  std::cout<<std::endl<<"==========================================================================================="<<std::endl<<std::endl;

  // ************************** //
  // Getting Background
  std::unique_ptr< TFile > inFileBackground( new TFile("backgroundToy.root","read") );
  TH1D *histoBackground = (TH1D*) inFileBackground->Get("SimulatedData");
  // Getting Signal
  std::unique_ptr< TFile > inFileSignal( new TFile("signalToy.root","read") );
  TH1D *histoSignal = (TH1D*) inFileSignal->Get("SimulatedSignal");
  // Create 'Data'
  histoBackground->Add(histoSignal,muHinj);
  RooDataHist dataHisto( "dataHisto","dataHisto",*workspace->var("mBB"),histoBackground );
  // ************************** //

  // Create nll
  RooAbsReal *nll = workspace->pdf("model")->createNLL(dataHisto,Extended(true));
  // Perform Fit
  RooMinimizer minuit(*nll);
  minuit.setMinimizerType("Minuit2");
  minuit.migrad();
  minuit.hesse();

  std::cout<<std::endl<<"==========================================================================================="<<std::endl<<std::endl;

  // Plot Fit Result
  TCanvas c0;
  RooPlot *frameMBB = workspace->var("mBB")->frame();
  dataHisto.plotOn(frameMBB);
  workspace->pdf("model")->plotOn(frameMBB);
  workspace->pdf("model")->plotOn(frameMBB,LineStyle(2),LineColor(2),Components("background"));

  frameMBB->Draw();
  c0.Draw();
  c0.Update();
  if ( save )
    c0.SaveAs( Form("mBBfit_inj_%.1f_%s.pdf",muHinj,usePolynomial?"poly":"bern") );

  // Plot nll as a function of muH
  double minimumValue = workspace->var("muH")->getValV();
  workspace->var("muH")->setVal(-100);
  double lowerBound = nll->getVal();
  workspace->var("muH")->setVal(100);
  double upperBound = nll->getVal();
  workspace->var("muH")->setVal( minimumValue );

  double maximumNLL = std::max(lowerBound,upperBound);
  double minimumNLL = nll->getVal();

  TCanvas c1;
  RooPlot *frameMuH = workspace->var("muH")->frame();
  nll->plotOn(frameMuH);
  frameMuH->SetAxisRange(minimumNLL,maximumNLL,"Y");
  frameMuH->Draw();
  c1.Draw();
  c1.Update();
  if ( save )
    c1.SaveAs( Form("nllPlot_inj_%.1f_%s.pdf",muHinj,usePolynomial?"poly":"bern") );

  createTgraph( workspace,*nll );

  Runner.Run(true);

  inFileBackground->Close();
  inFileSignal->Close();
}

/* ============================================================================== */

int Usage() {
  std::cout<<"Usage:"<<std::endl;
  std::cout<<"  "<< "--help             (-h) : print instructions" << std::endl;
  std::cout<<"  "<< "--save             (-s) : draw the results data : default 'false'" << std::endl;
  std::cout<<"  "<< "--inject <arg>     (-i) : the mu_H to be injected : default '0'" << std::endl;
  std::cout<<"  "<< "--poly             (-p) : use polynomial for describing the background : default 'false' "<<std::endl;
  return EXIT_FAILURE;
}

void setVerbositySettings() {
  RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Eval) ;

  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
}

void createTgraph(std::unique_ptr< RooWorkspace > &workspace, RooAbsReal &nll) {
  std::unique_ptr< TFile > outFile( new TFile(usePolynomial?"nll_poly.root":"nll_bern.root","recreate") );

  int nPoints = 0;
  TGraph gr;

  double value = -100;
  while( value < 100 ) {
    workspace->var("muH")->setVal( value );
    gr.SetPoint( nPoints++,value,nll.getVal() );
    value += 0.01;    
  }

  outFile->cd();
  gr.SetNameTitle("nll","nll");
  gr.Write();
  outFile->Close();
}
