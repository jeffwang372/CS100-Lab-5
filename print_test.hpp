#ifndef __PRINT_TEST_HPP
#define __PRINT_TEST_HPP

#include "gtest/gtest.h"
#include "spreadsheet.cpp"


TEST(PrintTest,SingleRow){

Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Purpose"});
sheet.add_row({"Jimmy", "Weezer", "21", "Print"});
std::stringstream out;
sheet.print_selection(out);
EXPECT_EQ(out.str(), "Jimmy Weezer 21 Print \n");


}//end first test

TEST(PrintTest,SingleNot){

Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Purpose"});
sheet.add_row({"Jimmy", "Weezer", "21", "Print"});
sheet.add_row({"Jimmy", "Neutron", "15", "Brain"});
sheet.set_selection( new Select_Not( new Select_Contains(&sheet, "Age", "21"))); 
std::stringstream out;
sheet.print_selection(out);
EXPECT_EQ(out.str(), "Jimmy Neutron 15 Brain \n");


}//end first test


TEST(PrintTest,SingleAnd){

Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Purpose"});
sheet.add_row({"Jimmy", "Weezer", "21", "Print"});
sheet.add_row({"Jimmy", "Neutron", "15", "Brain"});
sheet.set_selection( new Select_And( new Select_Contains(&sheet, "Age", "21") , new Select_Contains(&sheet,"Purpose", "Print"))); 
std::stringstream out;
sheet.print_selection(out);
EXPECT_EQ(out.str(), "Jimmy Weezer 21 Print \n");


}//end first test

TEST(PrintTest,SingleOr){

Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Purpose"});
sheet.add_row({"Jimmy", "Weezer", "21", "Print"});
sheet.add_row({"Jimmy", "Neutron", "15", "Brain"});
sheet.set_selection( new Select_Or( new Select_Contains(&sheet, "Age", "21") , new Select_Contains(&sheet,"Purpose", "Brain"))); 
std::stringstream out;
sheet.print_selection(out);
EXPECT_EQ(out.str(), "Jimmy Weezer 21 Print \nJimmy Neutron 15 Brain \n");


}//end first test


TEST(PrintTest,SingleContains){

Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Purpose"});
sheet.add_row({"Jimmy", "Weezer", "21", "Print"});
sheet.add_row({"Jimmy", "Neutron", "15", "Brain"});
sheet.set_selection(new Select_Contains(&sheet, "Age", "21")); 
std::stringstream out;
sheet.print_selection(out);
EXPECT_EQ(out.str(), "Jimmy Weezer 21 Print \n");


}//end first test







#endif
