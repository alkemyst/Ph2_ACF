/*!

        \file                   HybridTester.h
        \brief                 class for validating x*CBC2 hybrids
        \author              Alireza KOKABI & Georg AUZINGER
        \version                1.0
        \date                   24/10/14
        Support :               mail to : georg.auzinger@cern.ch

 */

#ifndef HybridTester_h__
#define HybridTester_h__

#include "Tool.h"
#include "../Utils/Visitor.h"
#include "../Utils/Utilities.h"
#include "../Utils/CommonVisitors.h"



#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLine.h"

using namespace Ph2_HwDescription;
using namespace Ph2_HwInterface;
using namespace Ph2_System;

/*!
 * \class HybridTester
 * \brief Class to test x*CBC2 Hybrids
 */
class HybridTester : public Tool
{
  public:
	// Default C'tor
	HybridTester() {}
	// Default D'tor
	~HybridTester() {}
	/*!
	* \brief Initialize the Histograms and Canvasses for CMD line applications
	* \param pThresholdScan :  bool flag to initialize the additional canvas for the Threshold scan
	*/
	void Initialize( bool pThresholdScan );
	/*!
	    * \brief Initialise the Histograms and Canvasses for GUI applications
	*/
	void InitialiseGUI( int pVcth, int pNevents, bool pTestreg, bool pScanthreshold, bool pHolemode );
	/*!
	* \brief Test CBC registers by writing complimentary bit patterns (0x55, 0xAA)
	*/
	void TestRegisters();
	/*!
	* \brief Scan the thresholds to identify the threshold with no noise occupancy
	*/
	void ScanThreshold();
	/*!
	* \brief Measure the single strip efficiency
	*/
	void Measure();
	/*!
	* \brief Save the results to the file created with SystemController::InitializeResultFile
	*/
	void SaveResults();

  private:
	uint32_t fNCbc;   /*!< Number of CBCs in the Setup */
	TCanvas* fDataCanvas;   /*!<Canvas to output single-strip efficiency */
	TH1F* fHistTop;   /*!< Histogram for top pads */
	TH1F* fHistBottom;   /*!< Histogram for bottom pads */
	bool fThresholdScan; /*!< Flag for SCurve Canvas */
	TCanvas* fSCurveCanvas;   /*!< Canvas for threshold scan */

	std::map<Cbc*, TH1F*> fSCurveMap;  /*!< Histograms for SCurve */
	std::map<Cbc*, TF1*> fFitMap;   /*!< fits for SCurve*/

	/*!
	* \brief private method that calls the constructors for the histograms
	*/
	void InitializeHists();
	/*!
	* \brief private method that calls reads the settings from the settings map in private member variables
	*/
	void InitialiseSettings();
	/*!
	* \brief private method to periodically update the output graphs
	*/
	void UpdateHists() {
		fDataCanvas->cd( 1 );
		fHistTop->Draw();
		fDataCanvas->cd( 2 );
		fHistBottom->Draw();
		fDataCanvas->Update();
	}

	// To measure the occupancy per Cbc
	uint32_t fillSCurves( BeBoard* pBoard,  const Event* pEvent, uint8_t pValue );
	void updateSCurveCanvas( BeBoard* pBoard );
	void processSCurves( uint32_t pEventsperVcth );

	uint32_t fTotalEvents;
	bool fHoleMode;
	int fSigmas;
	uint8_t fVcth;


};


#endif

