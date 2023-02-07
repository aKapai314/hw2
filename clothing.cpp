#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;	
/*
 **********************************
 * CLOTHING CLASS
 *
 **********************************
 */
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, 
  const std::string size, const std::string brand)
	: Product(category, name, price, qty)
{
	size_ = size;
	brand_ = brand;
}

Clothing::~Clothing()
{

}
//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Clothing::keywords() const
{
//get keywords from brand name
std::set<std::string> keywords = parseStringToWords(brand_);
//get keywords from product's name
std::set<std::string> temp = parseStringToWords(name_);
//add those keywords to the final list
keywords.insert(keywords.begin(), keywords.end());

return keywords;
}

std::string Clothing::displayString() const
{
	stringstream ss; 
	ss << name_ << endl;
	ss << "Size: " << size_ << " ";
	ss << "Brand: " << brand_ << endl;
	ss << setprecision(2) << fixed << price_ << " " << qty_ << " left.";

	return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
	os << "clothing" << endl << name_ << endl << setprecision(2) << fixed << price_ << endl << qty_ << endl;
	os << size_ << endl << brand_ << endl;
}