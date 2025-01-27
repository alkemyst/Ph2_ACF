/*!

        \file                                            BeBoardInterface.h
        \brief                                           User Interface to the Boards
        \author                                          Lorenzo BIDEGAIN, Nicolas PIERRE
        \version                                         1.0
        \date                        31/07/14
        Support :                    mail to : lorenzo.bidegain@gmail.com, nicolas.pierre@cern.ch


\mainpage Acquisition& Control Framework
*
* \section intro_sec Introduction
*
* The ACF middleware users should only use a BeBoardInterface( and a CbcInterface ) object and pass to its functions Hardware Description object pointers( from HWDescription namespace ) as arguments.
* \image html uml.png
* \section structure_sec Project structure
* The project compiles into the 5 following dynamic libraries
*
* \subsection lib1 HWDescription
* Hardware description of the shelves containing the boards, containing the modules, containing the CBC chips.\n
* The objects are:
FrontEndDescription, BeBoard, Cbc, Module, Shelve

* \subsection lib2 HWInterface
* Hardware interface seen by the ACF middleware users. \n
* Classes:
RegManager, BeBoardFWInterface, GlibFWInterface, CbcInterface, BeBoardInterface, FpgaConfig
*
* \subsection lib3 System
* Base class derivated by all command line tools from the src directory.\n
    * Class: SystemController
    *
    * \subsection lib4 Utils
    * Utility functions used by other libraries.\n
    * Classes: Exception, Utilities, Event, Data, argvparser

    * \subsection lib5 tools
    * Library using ROOT functions to perform calibration and other data processing.\n
    * Classes: Calibration, FastCalibration, Channel, HybridTester, CMTester
    * /

*/

#ifndef __BEBOARDINTERFACE_H__
#define __BEBOARDINTERFACE_H__

#include "BeBoardFWInterface.h"

using namespace Ph2_HwDescription;

/*!
 * \namespace Ph2_HwInterface
 * \brief Namespace regrouping all the interfaces to the hardware
 */
namespace Ph2_HwInterface
{

	typedef std::map<uint16_t, BeBoardFWInterface*> BeBoardFWMap;    /*!< Map of Board connected */

	/*!
	 * \class BeBoardInterface
	 * \brief Class representing the User Interface to the different boards
	 */
	class BeBoardInterface
	{

	  private:
		BeBoardFWMap fBoardMap;                     /*!< Map of Board connected */
		BeBoardFWInterface* fBoardFW;                     /*!< Board loaded */
		uint16_t prevBoardIdentifier;                     /*!< Id of the previous board */

	  private:
		/*!
		 * \brief Set the board to talk with
		 * \param pBoardId
		 */
		void setBoard( uint16_t pBoardIdentifier );

	  public:
		/*!
		 * \brief Constructor of the BeBoardInterface class
		 * \param pBoardMap Reference to the BoardFWInterface
		 */
		BeBoardInterface( const BeBoardFWMap& pBoardMap );
		/*!
		 * \brief Destructor of the BeBoardInterface class
		 */
		~BeBoardInterface();

		/*!
		 * \brief Update both Board register and Config File
		 * \param pBoard
		 * \param pRegNode : Node of the register to update
		 * \param pVal : Value to write
		 */
		void WriteBoardReg( BeBoard* pBoard, const std::string& pRegNode, const uint32_t& pVal );
		/*!
		     * \brief Write a block of a given size into the board
		    * \param pBoard
		    * \param pRegNode : Node of the register to write
		    * pValVec Vector of values to write
		     */
		void WriteBlockBoardReg( BeBoard* pBoard, const std::string& pRegNode, const std::vector<uint32_t>& pValVec );
		/*!
		 * \brief Write: Update both Board register and Config File
		 * \param pBoard
		 * \param pRegVec : Vector of Register/Value pairs
		 */
		void WriteBoardMultReg( BeBoard* pBoard, const std::vector < std::pair< std::string , uint32_t > >& pRegVec );
		/*!
		* \brief Update Config File with the value in the Board register
		* \param pBoard
		* \param pRegNode : Node of the register to update
		*/
		uint32_t ReadBoardReg( BeBoard* pBoard, const std::string& pRegNode );
		/*!
		     * \brief Read a block of a given size from the board
		    * \param pBoard
		    * \param pRegNode : Node of the register to read
		    * \param pSize Number of 32-bit words in the block
		     */
		std::vector<uint32_t> ReadBlockBoardReg( BeBoard* pBoard, const std::string& pRegNode, uint32_t pSize );
		/*!
		 * \brief Read a vector of Registers
		 * \param pBoard
		 * \param pRegVec : Vector of Register/Value pairs
		 */
		void ReadBoardMultReg( BeBoard* pBoard, std::vector < std::pair< std::string , uint32_t > >& pRegVec );
		/*!
		 * \brief Get the board infos
		 * \param pBoard
		 */
		void getBoardInfo( const BeBoard* pBoard );

		/*!
		 * \brief Configure the board with its Config File
		 * \param pBoard
		 */
		void ConfigureBoard( const BeBoard* pBoard );
		/*!
		 * \brief Start an acquisition in a separate thread
		 * \param pBoard Board running the acquisition
		 * \param uNbAcq Number of acquisition iterations (each iteration will get CBC_DATA_PACKET_NUMBER + 1 events)
		 * \param visitor override the visit() method of this object to process each event
		 */
		void StartThread( BeBoard* pBoard , uint32_t uNbAcq, HwInterfaceVisitor* visitor );
		/*! \brief Stop a running parallel acquisition
		 */
		void StopThread( BeBoard* pBoard );
		/*! \brief Get the parallel acquisition iteration number */
		int getNumAcqThread( BeBoard* pBoard );
		/*! \brief Is a parallel acquisition running ? */
		bool isRunningThread( BeBoard* pBoard );
		/*!
		 * \brief Start a DAQ
		 * \param pBoard
		 */
		void Start( BeBoard* pBoard );
		/*!
		 * \brief Stop a DAQ
		 * \param pBoard
		 * \param pNthAcq : actual number of acquisitions
		 */
		void Stop( BeBoard* pBoard, uint32_t pNthAcq );
		/*!
		 * \brief Pause a DAQ
		 * \param pBoard
		 */
		void Pause( BeBoard* pBoard );
		/*!
		 * \brief Resume a DAQ
		 * \param pBoard
		 */
		void Resume( BeBoard* pBoard );
		/*!
		 * \brief Read data from DAQ
		 * \param pBoard
		 * \param pNthAcq : actual number of acquisitions
		 * \param pBreakTrigger : if true, enable the break trigger
		 * \return cNPackets: the number of packets read
		 */
		uint32_t ReadData( BeBoard* pBoard, uint32_t pNthAcq, bool pBreakTrigger );
		/*!
		 * \brief Get next event from data buffer
		 * \param pBoard
		 * \return Next event
		 */
		const Event* GetNextEvent( const BeBoard* pBoard );
		/*!
		 * \brief Get the data buffer
		 * \param pBufSize : recovers the data buffer size
		 * \return Data buffer
		 */
		const char* GetBuffer( const BeBoard* pBeBoard, uint32_t& pBufSize );
		/*! \brief Get a uHAL node object from its path in the uHAL XML address file
		 * \param pBoard pointer to a board description
		 * \return Reference to the uhal::node object
		 */
		const uhal::Node& getUhalNode( const BeBoard* pBoard, const std::string& pStrPath );
		/*! \brief Access to the uHAL main interface for a given board
		 * \param pBoard pointer to a board description
		 * \return pointer to the uhal::HwInterface object
		 */
		uhal::HwInterface* getHardwareInterface( const BeBoard* pBoard );
		/*! \brief Upload a configuration in a board FPGA
		 * \param pBoard pointer to a board description
		 * \param numConfig FPGA configuration number to be uploaded
		 * \param pstrFile path to MCS file containing the FPGA configuration
		 */
		void FlashProm( BeBoard* pBoard, uint16_t numConfig, const char* pstrFile );
		/*! \brief Current FPGA configuration
		 * \param pBoard pointer to a board description
		 * \return const pointer to an FPGA uploading process. NULL means that no upload is been processed.
		 */
		const FpgaConfig* getConfiguringFpga( BeBoard* pBoard );

	};
}

#endif
