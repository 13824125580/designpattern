#include<iostream>

using namespace std;

class Product
{
public:
    virtual void show() = 0;  
};

class Product_A : public Product
{
public:
    void show()
    {
        cout << "Product_A" << endl;
    }
};

class Product_B : public Product
{
public:
    void show()
    {
        cout << "Product_B" << endl;
    }
};

class Factory
{
public:
    virtual Product* create() = 0;
};

class Factory_A : public Factory
{
public:
    Product* create()
    {
        return new Product_A;
    }
};

class Factory_B : public Factory
{
public:
    Product* create()
    {
        return new Product_B;
    }
};

int main()
{
    Factory_A* productA = new Factory_A();
    Factory_B* productB = new Factory_B();

    productA->create()->show();
    productB->create()->show();
    cin.get();
    return 0;
}
