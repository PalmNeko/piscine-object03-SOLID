#pragma once

#include "employee.hpp"
#include <set>
#include <iostream>

class EmployeeManager
{
public:
    std::size_t day;

protected:
    std::set<Employee *> employees;

public:
    virtual ~EmployeeManager() {}
    EmployeeManager() : day(0) {}

protected:
    EmployeeManager(EmployeeManager &other) : day(other.day), employees(other.employees) {}

public:
    void addEmployee(Employee *employee)
    {
        if (employee)
            employees.insert(employee);
    }

    void removeEmployee(Employee *employee)
    {
        if (employee)
            employees.erase(employee);
    }

    void executeWorkday()
    {
        std::set<Employee *>::iterator it = employees.begin();
        std::set<Employee *>::iterator ite = employees.end();

        while (it != ite)
        {
            (*it)->executeWorkday(day);
            it++;
        }
        day += 1;
    }

    void calculatePayroll()
    {
        std::set<Employee *>::iterator it = employees.begin();
        std::set<Employee *>::iterator ite = employees.end();
        std::size_t now_month = day / 30;

        if (now_month == 0)
            return;
        std::size_t pre_month = now_month - 1;
        std::size_t start_day = pre_month * 30;
        std::size_t end_day = now_month * 30;

        while (it != ite)
        {
            std::cout << (*it)->name << " " << (*it)->calculatePayroll(start_day, end_day) << std::endl;
            it++;
        }
    }

protected:
    EmployeeManager &operator=(EmployeeManager &other)
    {
        if (this != &other)
        {
            employees = other.employees;
            day = other.day;
        }
        return *this;
    }
};
