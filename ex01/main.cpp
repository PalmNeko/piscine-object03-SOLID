#include "command.hpp"
#include "packageReductionDiscount.hpp"
#include "thuesdayDiscount.hpp"
#include <iostream>
#include <cassert>

void testCommand();
void testPackageReductionDiscountCommand();
void testThuesdayDiscountCommand();

int main(void)
{
    testCommand();
    testPackageReductionDiscountCommand();
    testThuesdayDiscountCommand();
}

void testCommand()
{
    std::cout << " === Command" << std::endl;
    Command cmd(1, 1, 1, 100);

    assert(cmd.get_total_price() == 1000);
    std::cout << cmd.get_total_price() << std::endl;
}

void testPackageReductionDiscountCommand()
{
    std::cout << " === PackageReductionDiscountCommand" << std::endl;
    PackageReductionDiscountCommand cmd(1, 1, 1, 100);

    assert(cmd.get_total_price() == 990);
    std::cout << cmd.get_total_price() << std::endl;
}

void testThuesdayDiscountCommand()
{
    std::cout << " === ThuesdayDiscountCommand" << std::endl;
    ThuesdayDiscountCommand cmd1(1, 2, 1, 100);
    ThuesdayDiscountCommand cmd2(1, 1, 1, 100);

    assert(cmd1.get_total_price() == 900);
    std::cout << cmd1.get_total_price() << std::endl;
    assert(cmd2.get_total_price() == 1000);
    std::cout << cmd2.get_total_price() << std::endl;
}
