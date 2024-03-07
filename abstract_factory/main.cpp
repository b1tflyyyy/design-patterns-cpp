#include <iostream>

/* ------------------------- Cars Group ------------------------- */
class ICar
{
public:
    virtual ~ICar() = default;
    virtual void Drive() = 0;
};

class AModern_Car : public ICar
{
public:
    ~AModern_Car() override = default;
    void Drive() override
    {
        std::cout << "Modern drive\n";
    }
};

class AOld_Car : public ICar
{
public:
    ~AOld_Car() override = default;
    void Drive() override
    {
        std::cout << "Old drive\n";
    }
};

/* ------------------------- Airplane Group ------------------------- */
class IAirplane
{
public:
    virtual ~IAirplane() = default;
    virtual void Fly() = 0;
};

class AModern_Airplane : public IAirplane
{
public:
    ~AModern_Airplane() override = default;
    void Fly() override
    {
        std::cout << "Modern fly\n";
    }
};

class AOld_Airplane : public IAirplane
{
public:
    ~AOld_Airplane() override = default;
    void Fly() override
    {
        std::cout << "Old fly\n";
    }
};

/* ------------------------- Factory Group ------------------------- */
class IAbstract_Factory
{
public:
    virtual ~IAbstract_Factory() = default;
    virtual ICar* Create_Car() = 0;
    virtual IAirplane* Create_Airplane() = 0;
};

/* ------------------------- Modern Factory ------------------------- */
class AModern_Transport_Factory : public IAbstract_Factory
{
public:
    ~AModern_Transport_Factory() override = default;

    ICar* Create_Car() override
    {
        return new AModern_Car{};
    }

    IAirplane* Create_Airplane() override
    {
        return new AModern_Airplane{};
    }
};

/* ------------------------- Old Factory ------------------------- */
class AOld_Transport_Factory : public IAbstract_Factory
{
public:
    ~AOld_Transport_Factory() override = default;

    ICar* Create_Car() override
    {
        return new AOld_Car{};
    }

    IAirplane* Create_Airplane() override
    {
        return new AOld_Airplane{};
    }
};

int main()
{
    IAbstract_Factory* factory{ new AOld_Transport_Factory{} };
    ICar* car{ factory->Create_Car() };
    car->Drive();

    IAirplane* airplane{ factory->Create_Airplane() };
    airplane->Fly();

    delete car;
    delete airplane;
    delete factory;

    factory = { new AModern_Transport_Factory{} };

    car = { factory->Create_Car() };
    car->Drive();

    airplane = { factory->Create_Airplane() };
    airplane->Fly();

    delete car;
    delete airplane;
    delete factory;

    return 0;
}