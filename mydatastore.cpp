#include "mydatastore.h"
#include <set>
#include "product.h"
#include "user.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include <string>

using namespace std;

myDataStore::myDataStore()
{

}
myDataStore::~myDataStore()
{
	//needs to delete dynamically allocated memory in Users and Products sets
	set<User*>::iterator it1 = users_.begin();
	while(it1 != users_.end())
	{
		delete *it1;
		it1++;
	}
	users_.clear();

	set<Product*>::iterator it2 = products_.begin();
	while(it2 != products_.end())
	{
		delete *it2;
		it2++;
	}
	products_.clear();
}

void myDataStore::addProduct(Product* p)
{
	products_.insert(p);
	set<string> keywords = p->keywords(); //set of product p's keywords

	for(set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it)
	{
		string key = *it; //the key is the current keyword
		(prodKeyMap_[key]).insert(p);
	}
}

void myDataStore::addUser(User* u)
{
	users_.insert(u);

	deque<Product*> s;
	cartMap_[u] = s;

}

/**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
vector<Product*> myDataStore::search(vector<string>& terms, int type)
{
	set<Product*> finalSet;

	if(type == 0)
	{
		for(size_t i = 0; i < terms.size(); i++)
		{
			string key = terms.at(i);
			if(prodKeyMap_.find(key) != prodKeyMap_.end())
			{
				if(finalSet.empty())
					finalSet = prodKeyMap_[key];
				else
					finalSet = setIntersection(prodKeyMap_[key], finalSet);		
					
			}
		}
	}
	else
	{
		for(size_t i = 0; i < terms.size(); i++)
		{
			string key = terms.at(i);
			if(prodKeyMap_.find(key) != prodKeyMap_.end())
			{
				if(finalSet.empty())
					finalSet = prodKeyMap_[key];
				else
					finalSet = finalSet = setUnion(prodKeyMap_[key], finalSet);		
			}
		}
	}
	
	vector<Product*> finalVec;

	for(set<Product*>::iterator it = finalSet.begin(); it != finalSet.end(); ++it)
	{
		finalVec.push_back(*it);
	}
	
	return finalVec;
}

bool myDataStore::isValidUser(std::string username)
{
	map<User*, deque<Product*>>::iterator it;

	for(it = cartMap_.begin(); it != cartMap_.end(); it++)
	{
		if((it->first)->getName() == username)
			return true;
	}

	return false;
}

User* myDataStore::getUser(std::string username)
{
	if(isValidUser(username))
	{
		map<User*, deque<Product*>>::iterator it;
		for(it = cartMap_.begin(); it != cartMap_.end(); it++)
		{
			if((it->first)->getName() == username)
				return (it->first);
		}
	}
	return NULL;
}

void myDataStore::addToCart(std::string username, Product* p)
{
	if(isValidUser(username))
	{
		( cartMap_[getUser(username)] ).push_back(p);
	}
}

vector<Product*> myDataStore::viewCart(std::string username)
{
	vector<Product*> cartHits;
	if(isValidUser(username))
	{
		User* currUser = getUser(username);
		//iterate through the user's cart, aka a deque of Product*'s 
		for(size_t i = 0; i < (cartMap_[currUser]).size(); i++)
		{
			Product* p = (cartMap_[currUser]).at(i);
			cartHits.push_back(p);
		}
	}
	return cartHits;
}
void myDataStore::buyCart(std::string username)
{
	if(isValidUser(username))
	{
		deque<Product*> tobeRemoved; 
		deque<Product*>::iterator it;
		User* currUser = getUser(username);
		//iterate through the user's product* set (cart)
		for(it = (cartMap_[currUser]).begin(); it != (cartMap_[currUser]).end(); it++)
		{
			double balance = currUser->getBalance();
			Product* currProduct = *it; 
			double price = currProduct->getPrice();
			int qty = currProduct->getQty();
			if(balance >= price && qty > 0)
			{
				currProduct->subtractQty(1);
				currUser->deductAmount(price);
				tobeRemoved.push_back(currProduct);
			}
		}
		
		for(it = tobeRemoved.begin(); it != tobeRemoved.end(); it++)
		{
			deque<Product*>::iterator it2 = find((cartMap_[currUser]).begin(),(cartMap_[currUser]).end(), (*it));
			cartMap_[currUser].erase(it2);
		}
	}


}
/**
     * Reproduce the database file from the current Products and User values
     */
void myDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << endl;

	set<Product*>::iterator it1;
	for(it1 = products_.begin(); it1 != products_.end(); ++it1)
	{
		(*it1)->dump(ofile);
	}

	ofile << "</products>" << endl;
	ofile << "<users>" << endl;

	set<User*>::iterator it2;
	for(it2 = users_.begin(); it2 != users_.end(); ++it2)
	{
		(*it2)->dump(ofile);
	}

	ofile << "</users>" << endl;

	
}
