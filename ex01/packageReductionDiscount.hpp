#pragma once

#include "command.hpp"

class PackageReductionDiscountCommand : public Command
{
private:
    PackageReductionDiscountCommand() {}

public:
    PackageReductionDiscountCommand(std::size_t id, std::size_t date, std::size_t client, std::size_t articles)
        : Command(id, date, client, articles) {}
    ~PackageReductionDiscountCommand() {}
    PackageReductionDiscountCommand(const PackageReductionDiscountCommand &other)
        : Command(other) {}
    PackageReductionDiscountCommand &operator=(PackageReductionDiscountCommand &other)
    {
        if (this != &other)
        {
            Command::operator=(other);
        }
        return *this;
    }

    virtual std::size_t get_total_price()
    {
        std::size_t total_price = Command::get_total_price();
        if (total_price > 150)
            total_price -= 10;
        return total_price;
    }
};
