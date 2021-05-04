#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
#include <iostream>
using namespace std;
#include <string>



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
    // Select_Column() {
//	}
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

public:
std::string cmn;
std::string toFind;
const Spreadsheet* thisSheet;


	

std::string get_toFind() {
	return this->toFind;
}

Select_Contains(const Spreadsheet* sheet, const std::string& name, const std::string& toFind ) : Select_Column(sheet, name) {
	this->toFind = toFind;
	thisSheet = sheet;
	cmn = name;	
}//end constructor

~Select_Contains() = default;

virtual bool select( const std::string& s ) const
{
                if(s.find(toFind) != std::string::npos) {
 		                       return true;

                }//check if column is data we are looking for

                else {
                        return false;
                }

}//end select_contains function
};






class Select_Not: public Select_Contains
{

protected:

Select_Contains* localselect;
string notToFind;

public:

Select_Not(Select_Contains* selectptr) : Select_Contains(selectptr->thisSheet, selectptr->cmn, selectptr->toFind)  {
        localselect = selectptr;
	notToFind = selectptr->get_toFind();
}

//end constructor


~Select_Not(){
	delete localselect;

}//end destructor 

virtual bool select(const std::string& s) const
{
                if(localselect->select(s) == true) {
                        return false;

                }//check if column is data we are looking for

                else {
                        return true;
                }


}//end select_contains function
};

class Select_And: public Select
{

protected:

Select* localselect = nullptr;
Select* localselect2 = nullptr;

public:

Select_And(Select* selectptr, Select* selectptr2){// : Select_Contains(selectptr->thisSheet, selectptr->cmn, selectptr->toFind)  {
        localselect = selectptr;
	localselect2 = selectptr2;

}//end constructor


~Select_And(){

	delete localselect;
	delete localselect2;

}//end destructor

virtual bool select(const Spreadsheet* sheet, int row) const 
{
			
	return localselect->select(sheet,row) && localselect2->select(sheet,row);

}//end select_contains function
};

class Select_Or: public Select
{

protected:

Select* localselect;
Select* localselect2;

public:

Select_Or(Select* selectptr, Select* selectptr2){// : Select_Contains(selectptr->thisSheet, selectptr->cmn, selectptr->toFind)  {
        localselect = selectptr;
	localselect2 = selectptr2;

}//end constructor

~Select_Or(){

	delete localselect;
	delete localselect2;

}//end destructor

virtual bool select(const Spreadsheet* sheet, int row) const
{
		
	return localselect->select(sheet,row) || localselect2->select(sheet,row);


}//end select_contains function
};

#endif //__SELECT_HPP__
