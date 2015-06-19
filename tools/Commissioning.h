/*!

        \file                   Commissioning.h
        \brief                 class to do latency and threshold scans
        \author              Georg AUZINGER
        \version                1.0
        \date                   20/01/15
        Support :               mail to : georg.auzinger@cern.ch

 */

#ifndef COMMISSIONING_H__
#define COMMISSIONING_H__

#include "Tool.h"
#include "../Utils/Visitor.h"
#include "../Utils/Utilities.h"
#include "../Utils/CommonVisitors.h"


#include "TString.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"

using namespace Ph2_System;
using namespace Ph2_HwInterface;
using namespace Ph2_HwDescription;

typedef std::map<Cbc*, std::map<std::string, TObject*> >  CbcHistogramMap;
typedef std::map<Module*, std::map<std::string, TObject*> > ModuleHistogramMap;
typedef std::map<Module*, TCanvas*> CanvasMap;

/*!
 * \class Commissioning
 * \brief Class to perform latency and threshold scans
 */

class Commissioning : public Tool
{

  public:
	void Initialize();
	void ScanThreshold( bool pScanPedestal );
	std::map<Module*, uint8_t> ScanLatency( uint8_t pStartLatency = 0, uint8_t pLatencyRange = 20 );
	std::map<Module*, uint8_t> ScanStubLatency( uint8_t pStartLatency = 0, uint8_t pLatencyRange = 20 );
	// void ScanLatencyThreshold();
	void SaveResults();

  private:
	void initializeHists();
	void measureScurve( std::string pHistName, uint32_t pNEvents );
	int countHits( Module* pFe,  const Event* pEvent, std::string pHistName, uint8_t pParameter );
	int countStubs( Module* pFe,  const Event* pEvent, std::string pHistName, uint8_t pParameter );
	void updateHists( std::string pHistName, bool pFinal );
	void parseSettings();
	void dumpConfigFiles();

	// Histogram Methods
	// TObject* getHist( Cbc* pCbc, std::string pName );
	TObject* getHist( Module* pModule, std::string pName );

	//  Members
	CanvasMap fCanvasMap;
	// CbcHistogramMap fCbcHistMap;
	ModuleHistogramMap fModuleHistMap;
	uint32_t fNevents;
	uint32_t fInitialThreshold;
	uint32_t fHoleMode;
	uint32_t fNCbc;
};

#endif