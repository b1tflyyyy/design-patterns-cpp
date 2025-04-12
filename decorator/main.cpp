#include <iostream>
#include <format>
#include <string>
#include <memory>

class INotifier
{
public:
    virtual void Notify(std::string_view message) = 0;
    virtual ~INotifier() noexcept = default;
};

class EmailNotifier final : public INotifier
{
public: 
    void Notify(std::string_view message) override
    {
        std::cout << std::format("Email notifier: {}\n", message);
    }
};

class NotificationDecorator : public INotifier
{
public:
    explicit NotificationDecorator(std::unique_ptr<INotifier> notifier) :
        mInner{ std::move(notifier) }
    { }

    void Notify(std::string_view message) override 
    {
        mInner->Notify(message);
    }

private:
    std::unique_ptr<INotifier> mInner;
};

class PhoneNotificationDecorator final : public NotificationDecorator
{
public:
    explicit PhoneNotificationDecorator(std::unique_ptr<INotifier> notifier) :
        NotificationDecorator{ std::move(notifier) }
    { }

    void Notify(std::string_view message) override 
    {
        NotificationDecorator::Notify(message);
        std::cout << std::format("Phone notification: {}\n", message);
    }
};

class DiscordNotificationDecorator final : public NotificationDecorator
{
public:
    explicit DiscordNotificationDecorator(std::unique_ptr<INotifier> notifier) : 
        NotificationDecorator{ std::move(notifier) }
    { }

    void Notify(std::string_view message) override
    {
        NotificationDecorator::Notify(message);
        std::cout << std::format("Discord notification: {}\n", message);
    }
};

int main()
{
    auto notifier{ 
        std::make_unique<PhoneNotificationDecorator>(
            std::make_unique<DiscordNotificationDecorator>(
                std::make_unique<EmailNotifier>()
            )
        )
    };

    notifier->Notify("Really important message!!!");

    return 0;
}