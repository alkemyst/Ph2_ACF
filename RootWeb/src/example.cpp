#include <rootweb.hh>
#include <string>
#include <cstdlib>
#include <TH1D.h>
#include <TCanvas.h>

void makePageOne(RootWSite& site) {
  // Adding one page
  auto& home = site.addPage("Home");
  home.setAddress("index.html");
  // With one collapsing content (default is open)
  auto& content1 = home.addContent("Section 1");
  // With a table of strings 
  auto& aTableS = content1.addTable();
  for (int i=1; i<=10; ++i) {
    for (int j=1; j<=10; ++j) {
      aTableS.setContent(i, j, Form("G%d", i*j));
    }
  }
  // With a table of doubles (3 decimal places)
  auto& aTableD = content1.addTable();
  for (int i=1; i<=10; ++i) {
    for (int j=1; j<=10; ++j) {
      aTableD.setContent(i, j, sqrt(i*j), 3);
    }
  }
  // The second content is collapsed by defauls
  auto& content2 = home.addContent("Section 2", false);
  content2.addText("Hello, there, I was hiding here");
}

TH1D* createPlot() {
  TH1D* myHisto = new TH1D("test", "Here I am", 10, 0, 10);
  myHisto->Fill(3); 
  myHisto->Fill(3); 
  myHisto->Fill(4); 
  myHisto->Fill(5); 
  return myHisto;
}

void makePageTwo(RootWSite& site) {
  // Adding another page 
  auto& myPage = site.addPage("Other stuff"); 
  // With a content containing some plots
  auto& content1 = myPage.addContent("All plots here");

  // Creating the plot first
  TH1D* myHisto = createPlot();
  TCanvas* myCanvas = new TCanvas("c1", "c1", 500, 500);
  myCanvas->cd();
  myHisto->Draw();
  // Add an image to the content (with the corresponding canvas)
  auto& myImage = content1.addImage(myCanvas, 600, 400);
  myImage.setComment("A little explanation here always helps");
  myImage.setName("sensibleName");

  auto& content2 = myPage.addContent("All plots here");
  content2.addBinaryFile("summary.root" , "content of all your plots is here", "summary.root");
}

void prepareSiteStuff(RootWSite& site) {
  int runNumber=34;
  std::string siteTitle=Form("Run%06d", runNumber);

  std::string myDirectory="/afs/cern.ch/work/m/mersi/Ph2BeamTest/"+siteTitle;
  site.setTargetDirectory(myDirectory);
  site.setTitle(siteTitle);
  site.setComment("Complete run list");
  site.setCommentLink("../");
  site.addAuthor("Mickey Mouse");
  site.addAuthor("Dylan Dog");
  site.addAuthor("Nathan Never");
  site.setRevision("0.1");
  site.setProgram("Ph2_DAQ", "https://github.com/gauzinge/Ph2_ACF");
}

int main(int argc, char* argv[]) {
  RootWSite site;
  prepareSiteStuff(site);
  makePageOne(site);
  makePageTwo(site);
  site.makeSite(false);
}
