#include <iostream>

/* -------------------------------------- Product Part -------------------------------------- */
class IProduct /* Interface */
{
public:
    virtual void Drive() = 0;
    virtual ~IProduct() = default;
};

class ACar : public IProduct /* Specific class */
{
public:
    void Drive() override
    {
        std::cout << "ACar drive\n";
    }

    ~ACar() override = default;
};

class AMotorcycle : public IProduct /* Specific class */
{
public:
    void Drive() override
    {
        std::cout << "AMotorcycle drive\n";
    }

    ~AMotorcycle() override = default;
};

/* -------------------------------------- Creator Part -------------------------------------- */
class ICreator /* Interface */
{
public:
    virtual IProduct* Create_Product() = 0;
    virtual ~ICreator() = default;
};

class ACreator_Car : public ICreator /* Specific class */
{
public:
    IProduct* Create_Product() override
    {
        return new ACar();
    }

    ~ACreator_Car() override = default;
};

class ACreator_Motorcycle : public ICreator /* Specific class */
{
public:
    IProduct* Create_Product() override
    {
        return new AMotorcycle();
    }

    ~ACreator_Motorcycle() override = default;
};

int main()
{
    ICreator* creator = new ACreator_Car();

    IProduct* car = creator->Create_Product();
    delete creator;

    creator = new ACreator_Motorcycle();

    IProduct* moto = creator->Create_Product();
    delete creator;

    car->Drive();
    moto->Drive();

    delete car;
    delete moto;

    return 0;
}