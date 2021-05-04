#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column() {
	}
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};




class Select_Contains: public Select_Column
{

protected:

std::string cmn;
std::string toFind;
const Spreadsheet* thisSheet;

public:
std::string get_toFind() {
	return this->toFind;
}
Select_Contains(const Spreadsheet* sheet, const std::string& name, const std::string& toFind ) : Select_Column(sheet, name) {
	this->toFind = toFind;
	thisSheet = sheet;
	cmn = name;	
}

//end constructor

virtual bool select( const std::string& s ) const
{
        for(unsigned int i = 0; i < s.length(); ++i) {

                if( s.find(toFind) != std::string::npos) {

                        return true;

                }//check if column is data we are looking for

                else {
                        return false;
                }
        }

}//end select_contains function
};






class Select_Not: public Select_Column
{

protected:

Select_Contains* localselect;

public:

Select_Not(Select_Contains* selectptr)  {
        localselect = selectptr;

}

//end constructor

virtual bool select(const std::string& s) const
{
        for(unsigned int i = 0; i < s.length(); ++i) {

                if( s.find(localselect->get_toFind()) != std::string::npos) {

                        return false;

                }//check if column is data we are looking for

                else {
                        return true;
                }
        }


}//end select_contains function
};





#endif //__SELECT_HPP__
