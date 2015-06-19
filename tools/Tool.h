/*!

        \file                   Tool.h
        \brief                                   Controller of the System, overall wrapper of the framework
        \author                                  Georg AUZINGER
        \version                 1.0
        \date                                    06/02/15
        Support :                                mail to : georg.auzinger@cern.ch

 */


#ifndef __TOOL_H__
#define __TOOL_H__

#include "../System/SystemController.h"
#include "TROOT.h"
#include "TFile.h"

using namespace Ph2_System;


/*!
 * \class Tool
 * \brief A base class for all kinds of applications that have to use ROOT that inherits from SystemController which does not have any dependence on ROOT
 */
class Tool : public SystemController
{
  public:
	std::string fDirectoryName;             /*< the Directoryname for the Root file with results */
	TFile* fResultFile;                /*< the Name for the Root file with results */

	Tool() {}

	~Tool() {}

	/*!
	 * \brief Create a result directory at the specified path + ChargeMode + Timestamp
	 * \param pDirectoryname : the name of the directory to create
	 * \param pDate : apend the current date and time to the directoryname
	 */
	void CreateResultDirectory( const std::string& pDirname, bool pDate = true ) {
		bool cCheck;
		bool cHoleMode;
		auto cSetting = fSettingsMap.find( "HoleMode" );
		if ( cSetting != std::end( fSettingsMap ) ) {
			cCheck = true;
			cHoleMode = ( cSetting->second == 1 ) ? true : false;
		}
		std::string cMode;
		if ( cCheck ) {
			if ( cHoleMode ) cMode = "_Hole";
			else cMode = "_Electron";
		}

		std::string nDirname = pDirname;
		if ( cCheck ) nDirname +=  cMode;
		if ( pDate ) nDirname +=  currentDateTime();
		std::cout << std::endl << "Creating directory: " << nDirname << std::endl << std::endl;
		std::string cCommand = "mkdir -p " + nDirname;

		system( cCommand.c_str() );

		fDirectoryName = nDirname;
	}
	/*!
	 * \brief Initialize the result Root file
	 * \param pFilename : Root filename
	 */
	void InitResultFile( const std::string& pFilename ) {

		if ( !fDirectoryName.empty() ) {
			std::string cFilename = fDirectoryName + "/" + pFilename + ".root";
			fResultFile = TFile::Open( cFilename.c_str(), "RECREATE" );
		}
		else std::cout << RED << "ERROR: " << RESET << "No Result Directory initialized - not saving results!" << std::endl;
	}
};
#endif

