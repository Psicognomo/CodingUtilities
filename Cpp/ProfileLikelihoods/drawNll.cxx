
#include "iostream"
#include "vector"

#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"

TApplication Runner("gui",0,NULL);

int main() {

  std::vector< std::string > inputFiles;
  inputFiles.push_back("nll_bern.root");
  inputFiles.push_back("nll_poly.root");

  std::vector< TGraph* > graphs;

  for ( const std::string& name : inputFiles ) {
    TFile *inFile = new TFile(name.c_str(),"read");
    graphs.push_back( (TGraph*) inFile->Get("nll") );
  }

  TLegend legenda(0.7,0.8,0.85,0.87);
  legenda.SetFillColor(0);
  legenda.SetLineColor(0);

  TCanvas c0;
  for ( unsigned int i(0); i < graphs.size(); i++ ) {
    graphs.at( i )->SetLineColor( i+1 );
    graphs.at( i )->SetMarkerColor( i+1 );
    graphs.at( i )->SetMarkerSize(0);
    graphs.at( i )->Draw( i == 0 ? "APL":"PLSAME" );

    legenda.AddEntry( graphs.at( i ) , inputFiles.at(i).c_str(), "lp" );
  }

  legenda.Draw("SAME");

  c0.Draw();
  c0.Update();
  c0.SaveAs("nllProfiles.pdf");

  Runner.Run(true);
}
