#include "datastore.h"
#include <map>
#include <deque>
/*
	*
	* MYDATASTORE CLASS
	*
	*
*/

class myDataStore : public DataStore
{
public:
	myDataStore();
	~myDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	
	bool isValidUser(std::string username);
	void addToCart(std::string username, Product* p);
	vector<Product*> viewCart(std::string username);
	void buyCart(std::string username);
	User* getUser(std::string username);


private:
	std::set<Product*> products_;
	std::set<User*> users_;
	std::map<User*, deque<Product*>> cartMap_;
	std::map<std::string, std::set<Product*>> prodKeyMap_;


};