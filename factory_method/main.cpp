#include <iostream>

/* -------------------------------------- Product Part -------------------------------------- */
class IProduct /* Interface */
{
public:
    virtual void Drive() = 0;
    virtual ~IProduct() = default;
};

class Car : public IProduct /* Specific class */
{
public:
    void Drive() override
    {
        std::cout << "Car drive\n";
    }

    ~Car() override = default;
};

class Motorcycle : public IProduct /* Specific class */
{
public:
    void Drive() override
    {
        std::cout << "Motorcycle drive\n";
    }

    ~Motorcycle() override = default;
};

/* -------------------------------------- Creator Part -------------------------------------- */
class ICreator /* Interface */
{
public:
    virtual IProduct* Create_Product() = 0;
    virtual ~ICreator() = default;
};

class Creator_Car : public ICreator /* Specific class */
{
public:
    IProduct* Create_Product() override
    {
        return new Car();
    }

    ~Creator_Car() override = default;
};

class Creator_Motorcycle : public ICreator /* Specific class */
{
public:
    IProduct* Create_Product() override
    {
        return new Motorcycle();
    }

    ~Creator_Motorcycle() override = default;
};

int main()
{
    ICreator* creator = new Creator_Car();

    IProduct* car = creator->Create_Product();
    delete creator;

    creator = new Creator_Motorcycle();

    IProduct* moto = creator->Create_Product();
    delete creator;

    car->Drive();
    moto->Drive();

    delete car;
    delete moto;

    return 0;
}