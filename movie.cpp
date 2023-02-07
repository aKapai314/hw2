#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

/*
 **********************************
 * MOVIE CLASS
 *
 **********************************
 */

Movie::Movie(const std::string category, const std::string name, double price, int qty, 
	const std::string genre, const std::string rating)
	: Product(category, name, price, qty), genre_(genre), rating_(rating)
{

}

Movie::~Movie()
{

}
//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Movie::keywords() const
{
//keywords for product's name
std::set<std::string> keywords = parseStringToWords(name_);
//keyword for movie's genre
keywords.insert(convToLower(genre_));

return keywords;
}

std::string Movie::displayString() const
{
	stringstream ss; 
	ss << name_ << endl;
	ss << "Genre: " << genre_ << " ";
	ss << "Rating: " << rating_ << endl;
	ss << setprecision(2) << fixed << price_ << " " << qty_ << " left.";

	return ss.str();
}

void Movie::dump(std::ostream& os) const
{
	os << "movie" << endl << name_ << endl << setprecision(2) << fixed << price_ << endl << qty_ << endl;
	os << genre_ << endl << rating_ << endl;
}
	

