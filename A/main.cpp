#include <iostream>
#include <cstdlib>
#include <string>

#include "seqinfileenumerator.hpp"
#include "summation.hpp"
#include "maxsearch.hpp"


class MyEnor : public Enumerator<int>{
	private:
		int n;
		int _current;
		bool _end;
	public:
		MyEnor(const int& n) : n(n) {}
		void first() { _current = 2; }
		void next();
		bool end() const { return _end; }
		int current() const { return _current; }
};

void MyEnor::next(){
	if (!(_end = _current > (n / 2)))
		++_current;
}

class MySummation : public Summation<int, int>{
	private:
		int num;

		void init() { *_result = 0; }

		bool cond(const int& n) const { return (num % n == 0); }

		void add(const int& n){ *_result += n; }
	public:
		MySummation(int num) : Summation<int, int>(), num(num) {}
};

class MyMax : public MaxSearch<int>{
	private:
		int func(const int& n) const{
			MyEnor me(n);
			MySummation ms(n);
			ms.addEnumerator(&me);
			ms.run();
			return ms.result();
		}
};

int main(){
	std::string file;
	std::cin >> file;
	SeqInFileEnumerator<int>* enor = new SeqInFileEnumerator<int>(file);
	MyMax mm;
	mm.addEnumerator(enor);
	mm.run();
	if (mm.found())
		std::cout << mm.optElem() << "-nek az osztoinak az osszege a legnagyobb: " << mm.opt() << std::endl;
	else
		std::cout << "Ures a fajl!" << std::endl;
	system("pause");
	return 0;
}