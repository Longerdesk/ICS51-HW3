#include "Wordset.hpp"
#include <string>
#include <iostream>


// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
	int sum = 0;
	char c;
	int numOfLetter;
	int basePowered = 1;
	int length = s.length();
	for(int i = 0; i < length; i++){
		basePowered = 1;
		c = s[i];
		numOfLetter = c - 'a' + 1;
		for(int j = 0; j < length - i - 1; j++){
			basePowered *= base;
		}
		sum += (numOfLetter*basePowered);
	}
	return sum % mod;
}




WordSet::WordSet(unsigned initialCapacity1, unsigned evictionThreshold1)
{	
	initialCapacity = initialCapacity1;
	evictionThreshold = evictionThreshold1;
	T1 = new std::string[initialCapacity];
	T2 = new std::string[initialCapacity];
	for(unsigned i = 0; i < initialCapacity; i++){
		T1[i] = "";
		T2[i] = "";
	}
	capacity = initialCapacity;
}

WordSet::~WordSet()
{
	delete[] T1;
	delete[] T2;
}

void WordSet::insert(const std::string & s)
{
	if(!this->contains(s)){
		//std::cout << "start inserting " << s << std::endl;
		unsigned countEvic = 0;
		int index;
		std::string currentElement = s;
		std::string nextElement;
		bool inserted = false;
		unsigned nextTable = 1;
		while(!inserted){
			if(countEvic > this->evictionThreshold){
				//reverse
				if(nextTable == 1){
					nextTable = 2;
				}else if(nextTable == 2){
					nextTable = 1;
				}	
				for(unsigned i = 0; i < countEvic; i++){
					if(nextTable == 1){
						index = polynomialHashFunction(currentElement, BASE_H1, this->capacity);
						nextElement = T1[index];
						T1[index] = currentElement;
						currentElement = nextElement;
						nextTable = 2;
					}else if(nextTable == 2){
						index = polynomialHashFunction(currentElement, BASE_H2, this->capacity);			
						nextElement = T2[index];
						T2[index] = currentElement;
						currentElement = nextElement;
						nextTable = 1;
					}
				}
				
				this->resizeRehash();
				countEvic = 0;
				nextTable = 1;
			}
			if(nextTable == 1){
				index = polynomialHashFunction(currentElement, BASE_H1, this->capacity);
				if(T1[index] == ""){
					T1[index] = currentElement;
					inserted = true;
					//std::cout << "T1[" << index << "] = " << currentElement << std::endl;
				}else{
					countEvic += 1;
					nextElement = T1[index];
					T1[index] = currentElement;
					currentElement = nextElement;
					nextTable = 2;
					//std::cout << "T1[" << index << "] = " << T1[index] << std::endl;
				}
			}else if(nextTable == 2){
				index = polynomialHashFunction(currentElement, BASE_H2, this->capacity);
				if(T2[index] == ""){
					T2[index] = currentElement;
					inserted = true;
					//std::cout << "T2[" << index << "] = " << currentElement << std::endl;
				}else{
					countEvic += 1;  
					nextElement = T2[index];
					T2[index] = currentElement;
					currentElement = nextElement;
					nextTable = 1;
					//std::cout << "T2[" << index << "] = " << T2[index] << std::endl;
				}
			}
		}
	}
}

void WordSet::resizeRehash(){
	bool primeFound = false;
	bool isPrime = true;
	unsigned originalCapacity = capacity;
	capacity *= 2;
	capacity += 1;
		while(!primeFound){
			for(unsigned i = 2; i <= capacity/2; i++){
				if(capacity%i == 0){
					isPrime = false;
				}
			}
			if(isPrime){
				primeFound = true;
			}else{
				isPrime = true;
				capacity += 2;
			}
		}
		std::cout << "capacity changed to " << capacity << std::endl;
		std::string *T3;
		std::string *T4;
		T3 = new std::string[capacity];
		T4 = new std::string[capacity];
		
		for(unsigned i = 0; i < capacity; i++){
			T3[i] = "";
			T4[i] = "";
		}
		unsigned index;

		for(unsigned i = 0; i < originalCapacity; i++){
			if(T1[i] != ""){
				index = polynomialHashFunction(T1[i], BASE_H1, capacity);
				T3[index] = T1[i];
			}
			if(T2[i] != ""){
				index = polynomialHashFunction(T2[i], BASE_H2, capacity);
				T4[index] = T2[i];
			}
		}
		//memory leak here
		delete[] T1;
		delete[] T2;
		
		T1 = T3;
		T2 = T4;
}


bool WordSet::contains(const std::string & s) const
{
	if(this->T1[polynomialHashFunction(s, BASE_H1, this->capacity)] == s){
		return true;
	}else if(this->T2[polynomialHashFunction(s, BASE_H2, this->capacity)] == s){
		return true;
	}else{
		return false;
	}
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
	unsigned count = 0;
	for(unsigned i = 0; i < capacity; i++){
		if(T1[i] != ""){
			count += 1;
		}

		if(T2[i] != ""){
			count += 1;
		}
	}
	return count;
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
	return this->capacity;
}

// removes this word if it is in the wordset. 
void WordSet::remove(const std::string &s)
{
	if(this->T1[polynomialHashFunction(s, BASE_H1, this->capacity)] == s){
		T1[polynomialHashFunction(s, BASE_H1, this->capacity)] = "";
		this->capacity -= 1;
	}else if(this->T2[polynomialHashFunction(s, BASE_H2, this->capacity)] == s){
		T2[polynomialHashFunction(s, BASE_H2, this->capacity)] = "";
		this->capacity -= 1;
	}
}