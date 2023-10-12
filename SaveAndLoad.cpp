#include <map>
#include <iostream>
#include <vector>
#include <string>
#include "StudReestr.h"

using namespace std;

int main()
{
	StudReestr stud_reestr;
	//stud_reestr.insert({ "Petrov", {7, 9, 10, 1} });
	//stud_reestr.insert({ "Ivanov", {4, 10, 11} });
	//stud_reestr.insert({ "Sidarov", {12, 12, 12, 12, 12, 0} });
	//stud_reestr.show_reestr();
	//stud_reestr.save();
	stud_reestr.load("reestr.txt");
	stud_reestr.show_reestr();
	stud_reestr.save_bin();
}