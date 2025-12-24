#include "employee.hpp"
#include "employeeManagement.hpp"
#include "salariedEmployee.hpp"
#include "hourlyEmployee.hpp"
#include <vector>

template <typename BEGIN, typename END>
void addBreakTime(BEGIN it, END end, std::size_t day, int time)
{
    while (it != end)
    {
        (*it)->addBreakTime(day, time);
        it++;
    }
}

template <typename BEGIN, typename END>
void addWorkTime(BEGIN it, END end, std::size_t day, int time)
{
    while (it != end)
    {
        (*it)->addWorkTime(day, time);
        it++;
    }
}

int main(void)
{
    EmployeeManager manager;
    Apprentice a_employee(1000);
    ContractEmployee c_employee(2000);
    TempWorker t_employee(1000);

    t_employee.name = "t";
    c_employee.name = "c";
    a_employee.name = "a";

    std::vector<IHourlyEmployee *> hourlyEmployees;
    std::vector<ISalariedEmployee *> salariedEmployees;

    hourlyEmployees.push_back(&t_employee);
    salariedEmployees.push_back(&c_employee);
    salariedEmployees.push_back(&a_employee);

    manager.addEmployee(&t_employee);
    manager.addEmployee(&c_employee);
    manager.addEmployee(&a_employee);

    addWorkTime(hourlyEmployees.begin(), hourlyEmployees.end(), 4, 3);

    addBreakTime(salariedEmployees.begin(), salariedEmployees.end(), 4, 4);
    addBreakTime(salariedEmployees.begin(), salariedEmployees.end(), 14, 5);

    a_employee.addSchoolTime(14, 8);

    manager.day = 4;
    manager.executeWorkday();

    manager.day = 14;
    manager.executeWorkday();
    manager.executeWorkday();

    /**
     * 労働条件まとめ
     * t: 1000円/h
     * c: 2000円/h
     * a: 1000円/h
     *
     * 出勤時間マトリクス
     * day | 4d | 14d | 15d |
     * t   | 4h |  0h |  0h |
     * c   | 3h |  2h |  7h |
     * a   | 3h |  2h |  7h |
     *
     * 学校時間マトリクス
     * day | 4d | 14d | 15d |
     * a   | 0h |  8h |  0h |
     *
     * 給与計算予測
     * t = 1000円 * 3h = 3000円
     * c = 2000円 * (2h + 3h + 7h) = 24000円
     * a = 1000円 * (2h + 3h + 7h) + 500円 * 8h = 16000円
     *
     * まとめ
     * t 3000
     * c 24000
     * a 16000
     */
    manager.day += 30;
    manager.calculatePayroll();
}
