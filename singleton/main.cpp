#include <iostream>
#include <mutex>

/* Thread-safe version of Singleton */
class ASingleton
{
private:
    explicit ASingleton(std::uint8_t value) : Value(value)
    { }

    ~ASingleton() noexcept = default;

    std::uint8_t Value; // test value

    static ASingleton* Singleton;
    static std::mutex Mutex;

public:
    ASingleton(const ASingleton& other) = delete;
    ASingleton& operator=(const ASingleton& other) = delete;

    static ASingleton* Get_Instance(const std::uint8_t value);
    [[nodiscard]] std::uint8_t Get_Value() const
    {
        return Value;
    }
};

ASingleton* ASingleton::Singleton = nullptr;
std::mutex ASingleton::Mutex;

ASingleton* ASingleton::Get_Instance(const std::uint8_t value)
{
    std::lock_guard<std::mutex> locker(Mutex);
    if (!Singleton)
    {
        Singleton = new ASingleton(value);
    }

    return Singleton;
}

int main()
{
    ASingleton* singleton = ASingleton::Get_Instance(52);
    ASingleton* singleton_1 = ASingleton::Get_Instance(51);

    // output: 52, 52 or '4', '4' -> (like char)
    std::cout << "singleton: " << singleton->Get_Value() << " singleton_1: " << singleton_1->Get_Value() << '\n';


    return 0;
}