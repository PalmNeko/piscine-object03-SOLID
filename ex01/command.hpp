#pragma once

#include <cctype>

class Command
{
protected:
    std::size_t id;
    std::size_t date;
    std::size_t client;
    std::size_t articles;

protected:
    Command() {}
    Command(const Command &other)
        : id(other.id), date(other.date), client(other.client), articles(other.articles) {}

public:
    Command(std::size_t id, std::size_t date, std::size_t client, std::size_t articles)
        : id(id), date(date), client(client), articles(articles) {}
    virtual ~Command() {}

    virtual std::size_t get_total_price()
    {
        return 10 * articles;
    }

protected:
    Command &operator=(Command &other)
    {
        if (this != &other)
        {
            id = other.id;
            date = other.date;
            client = other.client;
            articles = other.articles;
        }
        return *this;
    }
};
