#include <sstream>
#include <iomanip>
#include "book.h"
#include <sstream> 
/*
 **********************************
 * BOOK CLASS
 *
 **********************************
 */
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, 
  const std::string ISBN, const std::string author) 
	: Product(category, name, price, qty)
{
	ISBN_ = ISBN;
	author_ = author;
}

Book::~Book()
{

}
//Returns the appropriate keywords that this product should be associated with
/* Searchable terms include:
- the words in the author’s name 
- the book’s ISBN number
*/
std::set<std::string> Book::keywords() const
{

//find keywords from author's name
std::set<std::string> keywords = parseStringToWords(author_);
//find keywords from product's name
std::set<std::string> temp = parseStringToWords(name_);
//add those keywords to the final list
keywords.insert(temp.begin(), temp.end());
//find keywords from book's ISBN
keywords.insert(ISBN_);

return keywords;
	
}

std::string Book::displayString() const
{
	stringstream ss; 
	ss << name_ << endl;
	ss << "Author: " << author_ << " ";
	ss << "ISBN: " << ISBN_ << endl;
	ss << setprecision(2) << fixed << price_ << " " << qty_ << " left.";

	return ss.str();
}

void Book::dump(std::ostream& os) const
{
	os << "book" << endl << name_ << endl << setprecision(2) << fixed << price_ << endl << qty_ << endl;
	os << ISBN_ << endl << author_ << endl;

}


