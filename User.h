#pragma once
#include <iostream>
#include "Category.h"
class User
{
public:
	int Id;
	std::string firstName;
	std::string lastName;
	std::string userName;
	Category Category;

	bool operator==(const User& user) const
	{
		if (userName.compare(user.userName) == 0)
			return true;
		else
			return false;
	}
};

