#include "Book.h"
#include <string>

 Book::Book(){}

Book::Book( std::string title, std::string author) 
{
	
	
	Book::BookTitle = title;
	Book::AuthorName = author;
	Book::CheckedOut = false;
}

void Book::InOrOutCheck(bool checkOut)
{
	CheckedOut = checkOut;
}

void Book::ShowBook()
{
	std::cout << Id << "\t" << BookTitle << "\t" << AuthorName  << std::endl;
}

bool Book::IsCheckedOut()
{
	return CheckedOut;
}

std::string Book::ObtainBookFileData()
{
	return std::to_string(Id) +   "|" + BookTitle + "|" + AuthorName + "|" + (CheckedOut ? "1" : "0");
}
