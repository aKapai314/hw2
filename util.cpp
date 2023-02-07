#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"


using namespace std;


std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
std::set<char> puncSet = {'.', '\'', ',', ' ', '&'}; 

std::set<string> keywords;

int lastPunc = -1; //index of last punctuation in string

for(size_t i = 0; i < rawWords.length(); i++){
    string newVal = "";
    //if the character is a punctuation 

    if(puncSet.find(rawWords[i]) != puncSet.end())
    {
        newVal = rawWords.substr(lastPunc + 1, i - lastPunc - 1);
        lastPunc = i;
    }
    else if(i == (rawWords.length() - 1) )
    {
        newVal = rawWords.substr(lastPunc + 1, i - lastPunc);
    }
    
  	if(newVal.length() >= 2)
    {
        keywords.insert(convToLower(newVal));
    }
            
    
}
//potential problem if punctuation is the first char in the string

return keywords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
