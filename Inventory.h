#pragma once

#include "Book.h"
#include <vector>
#include "CheckInOrOutResult.h"

class Inventory
{
private:
	std::vector<Book> Books;

public:
	void DisplayAllBooks();
	void DisplayCheckedOutBooks();
	int NumberOfBooks();
	Book GetBookByIndex(int index);
	void AddBook(Book book);
	void LoadBooks();
	void RemoveBook(std::string booktitle);
	int FindBookByTitle(std::string booktitle);
	CheckInOrOutResult CheckInOrOutBook(std::string booktitle, bool checkOut);
};

