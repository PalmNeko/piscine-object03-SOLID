#pragma once

#include <ostream>
#include <string>

#define makeTestContext(testcase) TestContext(testcase, __FILE__, __LINE__)

class TestContext
{
    std::string testcase_;
    std::string filename_;
    int line_;

public:
    const std::string &testcase() const { return testcase_; }
    const std::string &filename() const { return filename_; }
    int line() const { return line_; }

private:
    TestContext() : line_(0) {}

public:
    TestContext(const std::string &testcase,
                const std::string &filename,
                const int line)
        : testcase_(testcase),
          filename_(filename),
          line_(line) {}
    ~TestContext() {}
    TestContext(const TestContext &other)
        : testcase_(other.testcase_),
          filename_(other.filename_),
          line_(other.line_) {}

public:
    void success(std::ostream &os) const
    {
        os << "✅ " << testcase_ << std::endl;
    }

    void error(std::ostream &os) const
    {
        os << "\e[31m"
              "Error:"
              "\e[m "
           << *this;
    }

public:
    TestContext &operator=(const TestContext &other)
    {
        if (this != &other)
        {
            testcase_ = other.testcase_;
            filename_ = other.filename_;
            line_ = other.line_;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const TestContext &rhs)
    {
        os << rhs.filename_ << ":" << rhs.line_ << " " << rhs.testcase_;
        return os;
    }
};
