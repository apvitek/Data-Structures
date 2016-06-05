/**
 YOUR TASK is to read and understand this program. Then do the following:
 --> create and use a sentinel (or dummy) node
 // a sentinel node is an empty data node placed in the beginning of the list
 // insert/delete are shorter, simpler, and more eficient
 
 --> Display the number of countries in the list
 --> Display the countries whose capital contains 's' or 'S'.
 
 
 EXTRA CREDIT // 1 point
 --> create a circularly singly-linked list with a sentinel (or dummy) node
 // replace the head pointer by a tail pointer
 
 
 NAME: Andrea Borghi
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "CountryList.h"

using namespace std;

bool readCountries(CountryList *list);
void searchManager(CountryList *list);
void deleteManager(CountryList *list);
void displayCountry(Country showCountry);
string removeTrailingWhiteSpace(string str);

int main()
{
    // Define a CountryList object.
    CountryList *list = new CountryList;
    
    // Read Country information and creating link list nodes for country.
    if (!readCountries(list))
        return 1;
    
    // Display link list in CountryList object.
    list->displayList();
    
    // Search for country in CountryList object.
    searchManager(list);
    
    // Delete countries in CountryList object.
    deleteManager(list);
    list->displayList();
    
    // YOUR TASK ==================================
    // Display the number of countries in the list
    cout << endl << "The number of countries in the list is " << list -> size() << "." << endl << endl;
    
    // Display the countries whose capital contains 's' (or 'S')
    char letter = 's';
    
    cout << "Capitals which contain the letter '" << letter << "':" << endl;
    
    bool found = false;
    
    found = list -> searchLetterInCapital(letter);
    
    if (!found) {
        cout << "No Capital containing the letter '" << letter << "' could be found on the list." << endl;
    }
    
    // Display the countries whose capital contains 'C' (or 'c')
    letter = 'C';
    
    cout << endl << "Capitals which contain the letter '" << letter << "':" << endl;
    
    found = list -> searchLetterInCapital(letter);
    
    if (!found) {
        cout << "No Capital containing the letter '" << letter << "' could be found on the list." << endl;
    }
    
    // ================================================
    delete list;
    
    return 0;
}

//**************************************************
// Definition of function displayCountry.
// This function displays the country information in
// showCountry.
//**************************************************
void displayCountry(Country showCountry)
{
    // Display Country Data
    cout << showCountry.code << "; "
    << showCountry.name << "; "
    << showCountry.capital << "; "
    << showCountry.population;
}

//**************************************************
// Definition of function readCountries.
// This function will read all the country info from
// the file Countries.txt and insert them into a
// list, a reference parameter. This function returns
// true if read successfully, and false if it did
// not read successfully or read no country.
// ASSUMPTIONS: about Countries.txt
//  1) Each country's data member is on a separate line.
//  2) Each country is immediately after one another.
//  3) There is nothing after the last country's data.
//**************************************************
bool readCountries(CountryList *list)
{
    ifstream inFile;
    Country readCountry;
    string readStr;
    bool empty = true;
    
    // Open file to read, if couldn't open, display error
    // and exit with false
    inFile.open("/Users/andreaborghi/Documents/DAC - Data Structures/Data Stuctures Homework #1/Data Stuctures Homework #1/countries.txt");
    if (!inFile)
    {
        cout << "Error opening countries.txt!\n";
        return false;
    }
    
    while (getline(inFile, readStr))  // get Country's Code
    {
        // finish processing Country's Code
        strcpy(readCountry.code, removeTrailingWhiteSpace(readStr).c_str());
        
        // read and process Country's name
        getline(inFile, readStr);
        readCountry.name = removeTrailingWhiteSpace(readStr);
        
        // read and process Country's capital
        getline(inFile, readStr);
        readCountry.capital = removeTrailingWhiteSpace(readStr);
        
        // read and process Country's population
        getline(inFile, readStr);
        readCountry.population = atoi(readStr.c_str());
        
        list->insertNode(readCountry);
        empty = false;
    }
    
    inFile.close();
    
    if (empty)
        return false;
    
    return true;
}

//**************************************************
// Definition of function removeTrailingWhiteSpace.
// This function removes trailing white spaces at
// the back of the string, str, and returns the new
// string. Removes trailing tabs, line feeds,
// spaces, and carriage returns.
//**************************************************
string removeTrailingWhiteSpace(string str)
{
    int i = (int)str.length() - 1;  // zero based
    while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ' || str[i] == '\r')
    {
        str.erase(i, 1);
        i--;
    }
    return str;
}

//**************************************************
// Definition of function searchManager.
// This function will search for the country based
// upon the code entered by the user. If the country
// is found, the country data is returned in list, a
// reference parameter. Otherwise search not found
// will be displayed. This will cycle until the user
// enters QUIT.
//**************************************************
void searchManager(CountryList *list)
{
    Country searchCountry;
    string input;
    const string search_prompt = "[SEARCH COUNTRY] Please enter a code for a country:\n";
    
    while (cout << search_prompt, cin >> input, input != "QUIT")
    {
        strcpy(searchCountry.code, input.c_str());
        if (!list->searchNode(searchCountry))
            cout << "Search for " << searchCountry.code << " not found.\n";
        else
        {
            cout << "Country found: ";
            displayCountry(searchCountry);
            cout << ".\n";
        }
    }
}

//**************************************************
// Definition of function deleteManager.
// This function cycles, asking the user for a
// country to delete. The user enter a Code of the
// country to be deleted. If the Code is not found
// in the list, a reference parameter, then a
// message telling the user that country not found.
// If the Code was found, the node data that is
// deleted is shown. This function keeps going in a
// cycle until the user enter QUIT.
//**************************************************
void deleteManager(CountryList *list)
{
    string input;
    Country delCountry;
    const string delete_prompt = "[DELETE COUNTRY] Please enter a code for a country [QUIT to stop]:\n";
    
    while(cout << delete_prompt, cin >> input, input != "QUIT")
    {
        strcpy(delCountry.code, input.c_str());
        if (!list->deleteNode(delCountry))
            cout << "Country, " << delCountry.code << ", was not deleted because it was not found!\n";
        else
        {
            cout << "Country Info that was deleted: ";
            displayCountry(delCountry);
            cout << ".\n";
        }
    }
}

/*
 CODE  COUNTRY_NAME        CAPITAL             POPULATION
 AU    Australia           Canberra              20090437
 BR    Brazil              Brasilia             186112794
 BU    Bulgaria            Sofia                  7262675
 CA    Canada              Ottawa                32805041
 CN    China               Beijing             1306313812
 DO    Dominican Republic  Santo Domingo          8950034
 EG    Egypt               Cairo                 77505756
 ES    Spain               Madrid                40341462
 FJ    Figi                Suva                    893354
 FR    France              Paris                 60656178
 GR    Greece              Athens                10668354
 HU    Hungary             Budapest              10006835
 IR    Iran                Tehran                68017860
 JA    Japan               Tokyo                127288419
 LI    Liechtenstein       Vaduz                    33717
 MC    Monaco              Monaco                   32409
 MU    Mauritius           Port Louis             1230602
 MX    Mexico              Mexico City          106202903
 NP    Nepal               Kathmandu             27676547
 RU    Russia              Moscow               143420309
 TW    Taiwan              Taipei                22894384
 US    United States       Washington, DC       295734134
 [SEARCH COUNTRY] Please enter a code for a country:
 QUIT
 [DELETE COUNTRY] Please enter a code for a country [QUIT to stop]:
 QUIT
 CODE  COUNTRY_NAME        CAPITAL             POPULATION
 AU    Australia           Canberra              20090437
 BR    Brazil              Brasilia             186112794
 BU    Bulgaria            Sofia                  7262675
 CA    Canada              Ottawa                32805041
 CN    China               Beijing             1306313812
 DO    Dominican Republic  Santo Domingo          8950034
 EG    Egypt               Cairo                 77505756
 ES    Spain               Madrid                40341462
 FJ    Figi                Suva                    893354
 FR    France              Paris                 60656178
 GR    Greece              Athens                10668354
 HU    Hungary             Budapest              10006835
 IR    Iran                Tehran                68017860
 JA    Japan               Tokyo                127288419
 LI    Liechtenstein       Vaduz                    33717
 MC    Monaco              Monaco                   32409
 MU    Mauritius           Port Louis             1230602
 MX    Mexico              Mexico City          106202903
 NP    Nepal               Kathmandu             27676547
 RU    Russia              Moscow               143420309
 TW    Taiwan              Taipei                22894384
 US    United States       Washington, DC       295734134
 
 The number of countries in the list is 22.
 
 Capitals which contain the letter 's':
 Brasilia
 Sofia
 Santo Domingo
 Suva
 Paris
 Athens
 Budapest
 Port Louis
 Moscow
 Washington, DC
 
 Capitals which contain the letter 'C':
 Canberra
 Cairo
 Monaco
 Mexico City
 Moscow
 Washington, DC
*/