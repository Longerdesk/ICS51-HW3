#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>
#include <vector>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}


// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words)
{
	std::vector< std::string > ret;
	int s1Length = s1.length();
	int s2Length = s2.length();
	if(s1Length != s2Length){
		return ret;
	}
	std::set<std::string> visited;
	std::queue<std::string> wordQueue;
	std::map<std::string , std::string> bFromA;
	wordQueue.push(s1);
	visited.insert(s1);
	std::string currentWord;
	std::string nextWord = s1;
	while(wordQueue.size() != 0){
		//std::cout << "search: " << nextWord << std::endl;
		currentWord = wordQueue.front();
		wordQueue.pop();
		for(int i = 0; i < s1Length; i++){
			nextWord = currentWord;
			nextWord[i] = 'a'; 
			for(int j = 0; j < 26; j++){
				nextWord[i] = ('a' + j);
				//std::cout << nextWord << std::endl; 
				if(words.contains(nextWord) && (visited.find(nextWord) == visited.end())){
				//	std::cout << "found " << nextWord << std::endl;
					visited.insert(nextWord);
					wordQueue.push(nextWord);
					bFromA.insert({nextWord, currentWord});
				//	std::cout << "insert success" << std::endl;
				}
				if(nextWord == s2 && words.contains(nextWord)){
					ret.insert(ret.begin(), nextWord);
					while(nextWord != s1){
						nextWord = bFromA[nextWord];
						ret.insert(ret.begin(), nextWord);
					}
					return ret;
				}
			}
		}
	}

	return ret;
}
