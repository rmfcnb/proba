#include <iostream>
#include <cstdlib>

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

class Enor : public Enumerator<int>{
	private:
		SeqInFileEnumerator<int>* enor;
		int _current;
		bool _end;
	public:
		Enor(const std::string& file){
			enor = new SeqInFileEnumerator<int>(file);
		}
		~Enor(){ delete enor; }
		void first() { enor->first(); next(); }
		void next();
		bool end() const { return _end; }
		int current() const { return _current; }
};

void Enor::next(){

}

int main(){
	int n;
	std::cin >> n;
	if (std::cin.fail())
		exit(1);
	MySummation ms(n);
	MyEnor* me = new MyEnor(n);
	ms.addEnumerator(me);
	ms.run();
	std::cout << ms.result() << std::endl;
	system("pause");
	return 0;
}