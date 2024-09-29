#include "catch_amalgamated.hpp"
#include "Wordset.hpp"
#include "convert.hpp"
#include <string>
#include <fstream>

namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.
// You MAY use isValidChange and validConversion in unit tests 
// 	(i.e., this file and any other unit tests in this folder you add),
// but you MAY NOT use it in your code otherwise. 


bool isValidChange(const std::string &s1, const std::string &s2)
{
	if( s1.length() != s2.length() )
	{
		return false;
	}
	int count = 0;
	for (size_t i=0; i < s1.length(); i++)
	{
		if( s1[i] != s2[i])
		{
			count++;
		}
	}
	return count == 1;
}

bool validConversion(const std::vector< std::string > &r, std::string s1, std::string s2,  std::istream & in)
{
	
	// read word list into std::set<std::string>

	std::set<std::string> words;
	std::string line, word;
	std::stringstream ss;

	if( r.size() == 0 )
	{
		return false; 
	}
	if( s1 == s2 and r.size() == 1 and r[0] == s1 )
	{
		return true;
	}
	if( r[0] != s1 or r[ r.size() - 1] != s2)
	{
		return false;
	}

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			//std::cout << "This is where you should add " << word << " into your WordSet." << std::endl;
			words.insert( word );
		}
	}


	for(unsigned i=0; i < r.size() - 1; i++)
	{
		if( words.count(r[i]) == 0 || ! isValidChange(r[i], r[i+1]))
		{
			return false;
		}
	}
	if( words.count(r[ r.size() -1 ] ) == 0 )
		return false;
	return true;
}












TEST_CASE("AntToArt", "[RequiredConversion]")
{
	WordSet words(11);
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);

 	std::vector< std::string > r  = convert("ant", "art", words);

 	// this was a success if r was a valid conversion of length 2.
	std::ifstream in2("words.txt");
 	REQUIRE(r.size() == 2);
 	REQUIRE(  validConversion(r, "ant", "art", in2) );
}



TEST_CASE("AntToEat", "[RequiredConversion]")
{
	WordSet words{11};
	std::ifstream in{"words.txt"};
	loadWordsIntoTable(words, in);

 	std::vector< std::string > r = convert("ant", "eat", words);

	std::ifstream in2{"words.txt"};

 	REQUIRE(r.size() == 5);
 	REQUIRE(  validConversion(r, "ant", "eat", in2) );
}

TEST_CASE("AntToEater", "[NONRequiredConversion]")
{
	WordSet words{11};
	std::ifstream in{"words.txt"};
	loadWordsIntoTable(words, in);

 	std::vector< std::string > r = convert("ant", "eater", words);

	std::ifstream in2{"words.txt"};

 	REQUIRE(r.size() == 0);
}

TEST_CASE("HeadToTail", "[NONRequiredConversion]")
{
	WordSet words{11};
	std::ifstream in{"words.txt"};
	loadWordsIntoTable(words, in);

 	std::vector< std::string > r = convert("head", "tail", words);

	std::ifstream in2{"words.txt"};

 	REQUIRE(r.size() == 6);
 	REQUIRE(  validConversion(r, "head", "tail", in2) );
}

TEST_CASE("AntToBal", "[NONRequiredConversion]")
{
	WordSet words{11};
	std::ifstream in{"words.txt"};
	loadWordsIntoTable(words, in);

 	std::vector< std::string > r = convert("ant", "bal", words);

	std::ifstream in2{"words.txt"};

 	REQUIRE(r.size() == 0);
}

}
