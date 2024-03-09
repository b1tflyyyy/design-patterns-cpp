#include <iostream>
#include <vector>
#include <string>

enum EShape_Type : std::uint8_t
{
    Circle,
    Square,
};

class IShape
{
public:
    constexpr IShape() :
        Shape_Name{ " " }, Shape_Size{ 0 }
    { }

    explicit IShape(std::string_view shape_name, std::size_t shape_size) :
        Shape_Name{ shape_name }, Shape_Size{ shape_size }
    { }

    virtual ~IShape() = default;

    virtual IShape* Clone() = 0;

    virtual void Print_Info()
    {
        std::cout << "Shape_Name: " << Shape_Name << " Shape_Size: " << Shape_Size << '\n';
    }

protected:
    std::string_view Shape_Name;
    std::size_t Shape_Size;
};

class ACircle : public IShape
{
public:
    explicit ACircle(std::string_view circle_name, std::size_t circle_size, std::size_t circle_height) :
        IShape{ circle_name, circle_size }, Circle_Height{ circle_height }
    { }

    ~ACircle() override = default;

    IShape* Clone() override
    {
        return new ACircle{ *this };
    }

private:
    std::size_t Circle_Height;
};

class ASquare : public IShape
{
public:
    explicit ASquare(std::string_view circle_name, std::size_t circle_size, std::size_t square_height) :
        IShape{ circle_name, circle_size }, Square_Height{ square_height }
    { }

    ~ASquare() override = default;

    IShape* Clone() override
    {
        return new ASquare{ *this };
    }

private:
    std::size_t Square_Height;
};

class AShape_Factory
{
public:
    AShape_Factory()
    {
        Shapes.push_back(new ACircle{ "circle", 20, 100 });
        Shapes.push_back(new ASquare{ "square", 10, 50 });
    }

    ~AShape_Factory()
    {
        delete Shapes[EShape_Type::Circle];
        delete Shapes[EShape_Type::Square];
    }

    IShape* Create_Shape(EShape_Type shape_type)
    {
        return Shapes[shape_type]->Clone();
    }

private:
    std::vector<IShape*> Shapes;
};

int main()
{
    AShape_Factory shape_factory{};

    IShape* shape = shape_factory.Create_Shape(EShape_Type::Circle);
    shape->Print_Info();

    shape = shape_factory.Create_Shape(EShape_Type::Square);
    shape->Print_Info();

    return 0;
}