#pragma once
#include <string.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef pair <string, vector<int>> SP;


class StudReestr : public map <string, vector<int>>
{
private:

public:
	void show_reestr();
	void save();
	void load(string);
	void save_bin();
	void load_bin(string);
};

void StudReestr::show_reestr()
{
	for(SP c : *this )
	{
		cout << c.first << "\t : \t";
		for ( int x : c.second)
		{
			cout << x << ", ";
		}
		cout << "\b\b " << endl;
	}
}

void StudReestr::save()
{
	ofstream f("reestr.txt", ios_base::out);
	for (SP c : *this)
	{
		f << c.first << ":";
		for (int x : c.second)
		{
			f << x << "|";
		}
		f << endl;
	}

	f.close();

}

void StudReestr::load(string fn)
{
	this->clear();

	ifstream f(fn, ios_base::in);
	char mas[500];
	char* p = nullptr;
	string key;
	while(!f.eof())
	{
		f.getline(mas, 500);
		// find separator ":"
		p = strchr(mas, ':');
		if (p == 0)
			break;
		// store the found key
		*p = '\0';
		key = mas;
		//cout << key << endl;  // FOR DEBUG !!!
		// parse the vector (char by char)
		vector<int> value;
		int v = 0;
		for (++p; *p != 0; p++)
		{
			if (*p == '|')
			{
				//cout << v << endl;
				value.push_back(v);
				v = 0;
				continue;
			}
			if (v == 0)
			{
				v = (*p) - '0'; // 0h30
			}
			else
			{
				v *= 10;
				v += (*p) - '0';
			}
		}
		//key and vector are ready
		pair<string, vector<int>> temp;
		temp.first = key;
		temp.second = value;
		//cout << temp.first << endl;
		
		this->insert(temp);
		//cout << (*this)["Ivanov"][0];
		
	}
	f.close();
}

// Save Map data into file
// (in binary format)
void StudReestr::save_bin()
{
	ofstream f;
	f.open("reestr.bin", ios_base::binary);
	// create 1 Mb buffer for data to be written
    unsigned char* arr = new unsigned char[1000000];
	unsigned char* iter = arr;
	for (SP element : *this)
	{
		// в переменную element попала очередная пара словаря
		for (char symbol : element.first)
		{
			//в symbol попадают символы ключа
			*iter = symbol;
			iter++;
		}
		*iter = 124;
		iter++;
		for (unsigned char num : element.second)
		{
			*iter = num;
			iter++;
		}
		*iter = 126;
		iter++;
	}
	f.write((const char*) arr, iter - arr);
	

	// close file and deallocate memory
	f.close();
	delete[]arr;
}


