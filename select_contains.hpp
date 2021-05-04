#ifndef __SELECT_CONTAINS_HPP__
#define __SELECT_CONTAINS_HPP__

using namespace std;
#include <cstring>
#include "select.hpp"
class Select_Contains: public Select_Column
{

protected:

string toFind;

public:

Select_Contains(const Spreadsheet* sheet, const std::string& name, const std::string& toFind ){

	this.toFind = toFind;
	column = sheet->get_column_by_name(name);

}//end constructor 

virtual bool select( const std::string& s ) const 
{
	for(unsigned int i = 0; i < s.length(); ++i)

		if( s.substr(i,s.length()) == toFind ) {

		return true;	

	}//check if column is data we are looking for 
	
	else {
	return false;
	}

}//end select_contains function
};

#endif //__SELECT_CONTAINS_HPP__
