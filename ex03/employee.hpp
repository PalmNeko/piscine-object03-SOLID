#pragma once

#include "hourlyEmployee.hpp"
#include "salariedEmployee.hpp"
#include <map>
#include <string>

class Employee
{
public:
    std::string name;

protected:
    std::map<std::size_t, int> pays;
    int hourlyValue;

public:
    virtual ~Employee() {}

protected:
    Employee(int hourlyValue) : hourlyValue(hourlyValue) {}
    Employee(Employee &other) : hourlyValue(other.hourlyValue) {}

public:
    virtual int executeWorkday(std::size_t day) = 0;
    int calculatePayroll(std::size_t begin_day, std::size_t end_day)
    {
        std::map<std::size_t, int>::iterator it = pays.lower_bound(begin_day);
        std::map<std::size_t, int>::iterator ite = pays.end();

        int pay = 0;
        while (it != ite && it->first < end_day)
        {
            if (it->first >= begin_day)
            {
                pay += it->second;
            }
            it++;
        }
        return pay;
    }

protected:
    Employee &operator=(Employee &other)
    {
        if (this != &other)
        {
            hourlyValue = other.hourlyValue;
        }
        return *this;
    }
};

class TempWorker : public Employee, public IHourlyEmployee
{
private:
    std::map<std::size_t, int> worktimes;

public:
    TempWorker(int hourlyValue) : Employee(hourlyValue) {}
    ~TempWorker() {}

protected:
    TempWorker(TempWorker &other) : Employee(other), worktimes(other.worktimes) {}

public:
    int executeWorkday(std::size_t day)
    {
        std::map<std::size_t, int>::iterator it = worktimes.find(day);
        if (it == worktimes.end())
            return 0;
        int worktime = it->second;
        pays[day] = worktime * hourlyValue;
        return (0);
    }

    void addWorkTime(std::size_t day, int time)
    {
        worktimes[day] = time;
    }
};

class ContractEmployee : public Employee, public ISalariedEmployee
{
private:
    std::map<std::size_t, int> breaktimes;

public:
    ContractEmployee(int hourlyValue) : Employee(hourlyValue) {}
    ~ContractEmployee() {}

protected:
    ContractEmployee(ContractEmployee &other) : Employee(other), breaktimes(other.breaktimes) {}

public:
    int executeWorkday(std::size_t day)
    {
        std::map<std::size_t, int>::iterator it = breaktimes.find(day);
        int breaktime = 0;
        if (it != breaktimes.end())
            breaktime = it->second;
        int worktime = 7 - breaktime;
        if (worktime < 0)
            return 0;
        pays[day] = worktime * hourlyValue;
        return 0;
    }

    void addBreakTime(std::size_t day, int time)
    {
        breaktimes[day] = time;
    }
};

class Apprentice : public Employee, public ISalariedEmployee
{
private:
    std::map<std::size_t, int> breaktimes;
    std::map<std::size_t, int> schooltimes;

public:
    Apprentice(int hourlyValue) : Employee(hourlyValue) {}
    ~Apprentice() {}

protected:
    Apprentice(Apprentice &other) : Employee(other), breaktimes(other.breaktimes), schooltimes(other.schooltimes) {}

public:
    int executeWorkday(std::size_t day)
    {
        int breaktime = 0;
        {
            std::map<std::size_t, int>::iterator it = breaktimes.find(day);
            if (it != breaktimes.end())
                breaktime = it->second;
        }

        int worktime = 7 - breaktime;
        if (worktime < 0)
            return 0;

        int schooltime = 0;
        {
            std::map<std::size_t, int>::iterator it = schooltimes.find(day);
            if (it != schooltimes.end())
                schooltime = it->second;
        }

        pays[day] = worktime * hourlyValue + schooltime * (hourlyValue / 2);
        return (0);
    }

    void addBreakTime(std::size_t day, int time)
    {
        breaktimes[day] = time;
    }

    void addSchoolTime(std::size_t day, int time)
    {
        schooltimes[day] = time;
    }
};
