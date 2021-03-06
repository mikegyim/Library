#pragma once

#include <iostream>

class Book
{
private:
	
	
	std::string BookTitle;
	std::string AuthorName;
	bool CheckedOut;

public:
	int Id;

	Book();
	Book( std::string booktitle, std::string author_name);

	void InOrOutCheck(bool checkOut);
	void ShowBook();
	bool IsCheckedOut();
	std::string ObtainBookFileData();

	bool operator==(const Book &book) const
	{
		if (BookTitle.compare(book.BookTitle) == 0)
			return true;
		else
			return false;
	}
};

