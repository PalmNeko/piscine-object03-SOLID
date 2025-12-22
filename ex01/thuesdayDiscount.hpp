#pragma once

#include "command.hpp"

class ThuesdayDiscountCommand : public Command
{
    ThuesdayDiscountCommand() {}

public:
    ThuesdayDiscountCommand(std::size_t id, std::size_t date, std::size_t client, std::size_t articles)
        : Command(id, date, client, articles) {}
    ~ThuesdayDiscountCommand() {}
    ThuesdayDiscountCommand(const ThuesdayDiscountCommand &other)
        : Command(other) {}
    ThuesdayDiscountCommand &operator=(ThuesdayDiscountCommand &other)
    {
        if (this != &other)
        {
            Command::operator=(other);
        }
        return *this;
    }

    std::size_t get_total_price()
    {

        std::size_t total_price = Command::get_total_price();
        if (isThuesday(date))
            total_price = total_price - (total_price * 0.1);
        return total_price;
    }

private:
    bool isThuesday(std::size_t date)
    {
        return date % 7 == 2;
    }
};
