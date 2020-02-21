#include <stdlib.h>
#include <iostream>

class CashRegistor
{
public:
	void clear();
	void display() const;
	void add_item(double price);
	double get_total() const;
	int get_count() const;
	
private: 
	int item_count;
	double total_price;
};
/*
CashRegistor::CashRegistor()
{
	item_count=0;
	total_price=0;
}
*/
void CashRegistor::clear()
{
	item_count=0;
	total_price=0;
}

void CashRegistor::add_item(double price)
{
	item_count++;
	total_price += price;
}

void CashRegistor::display() const
{
	//std::cout << item_count <<" items, $" << total_price << std::endl;  degisiklerden etkilenmesin diye bunu kullanmiyoruz
	std::cout << get_count() 
			  <<" items, $" 
			  << get_total()
			  << std::endl;
}

int CashRegistor::get_count() const
{
	return item_count;
}

double CashRegistor::get_total() const
{
	return total_price;
}

int main()
{
	/*
	CashRegistor register1;
	//register1.clear();  satir 17 bununla ayni gorevi goruyor ustteki direk 56 ve 57 nin birlesmesini sagliyor!!
	register1.add_item(1.95);
	register1.display();
	register1.add_item(0.95);
	register1.display();
	*/
	
	CashRegistor* register1 = NULL;
	register1 = new CashRegistor;
	register1->clear();
	register1->add_item(1.95);
	register1->display();
	register1->add_item(0.95);
	register1->display();
	
	CashRegistor register2;
	register2.clear();
	register2.add_item(7.55);
	register2.display();
	return EXIT_SUCCESS;
}
