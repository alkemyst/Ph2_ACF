/*!

        Filename :                              BeBoard.cc
        Content :                               BeBoard Description class, configs of the BeBoard
        Programmer :                    Lorenzo BIDEGAIN
        Version :               1.0
        Date of Creation :              14/07/14
        Support :                               mail to : lorenzo.bidegain@gmail.com

 */

#include "BeBoard.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

namespace Ph2_HwDescription
{

	// Constructors

	BeBoard::BeBoard() :
		fShelveId( 0 ),
		fBeId( 0 ) {}

	BeBoard::BeBoard( uint8_t pShelveId, uint8_t pBeId ) :
		fShelveId( pShelveId ),
		fBeId( pBeId )
	{
	}

	BeBoard::BeBoard( uint8_t pShelveId, uint8_t pBeId, const std::string& filename ) :
		fShelveId( pShelveId ),
		fBeId( pBeId )
	{
		loadConfigFile( filename );
	}

	// Public Members:

	uint32_t BeBoard::getReg( const std::string& pReg ) const
	{
		BeBoardRegMap::const_iterator i = fRegMap.find( pReg );
		if ( i == fRegMap.end() )
		{
			std::cout << "The Board object: " << +fBeId << " doesn't have " << pReg << std::endl;
			return 0;
		}
		else return i->second;
	}

	void BeBoard::setReg( const std::string& pReg, uint32_t psetValue )
	{
		BeBoardRegMap::iterator i = fRegMap.find( pReg );
		if ( i == fRegMap.end() )
			fRegMap.insert( std::make_pair( pReg, psetValue ) );
		else i->second = psetValue;
	}

	bool BeBoard::removeModule( uint8_t pModuleId )
	{

		bool found = false;
		std::vector<Module*>::iterator i;
		for ( i = fModuleVector.begin(); i != fModuleVector.end(); ++i )
		{
			if ( ( *i )->getModuleId() == pModuleId )
			{
				found = true;
				break;
			}
		}
		if ( found )
		{
			fModuleVector.erase( i );
			return true;
		}
		else
		{
			std::cout << "Error:The BeBoard: " << +fBeId
					  << " doesn't have the module " << +pModuleId << std::endl;
			return false;
		}
	}

	Module* BeBoard::getModule( uint8_t pModuleId ) const
	{
		for ( Module* m : fModuleVector )
		{
			if ( m->getModuleId() == pModuleId )
				return m;
		}
		return nullptr;
	}

	// Private Members:

	void BeBoard::loadConfigFile( const std::string& filename )

	{

		std::ifstream cFile( filename.c_str(), std::ios::in );
		if ( !cFile ) std::cerr << "The BeBoard Settings File " << filename << " could not be opened!" << std::endl;
		else
		{

			fRegMap.clear();
			std::string cLine, cName, cValue, cFound;

			while ( !( getline( cFile, cLine ).eof() ) )
			{

				if ( cLine.find_first_not_of( " \t" ) == std::string::npos ) continue;
				if ( cLine.at( 0 ) == '#' || cLine.at( 0 ) == '*' ) continue;
				if ( cLine.find( ":" ) == std::string::npos ) continue;

				std::istringstream input( cLine );
				input >> cName >> cFound >> cValue;


				// Here the Reg name sits in cName and the Reg value sits in cValue
				if ( cValue.find( "0x" ) != std::string::npos )
					fRegMap[cName] = strtol( cValue.c_str(), 0, 16 );
				else
					fRegMap[cName] = strtol( cValue.c_str(), 0, 10 );
			}

			cFile.close();

		}

	}

}
