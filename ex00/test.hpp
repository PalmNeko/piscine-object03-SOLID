#include "TestContext.hpp"

#include <iostream>

#define TestTrue(case, x)                                  \
    do                                                     \
    {                                                      \
        const TestContext context = makeTestContext(case); \
        test_true(context, x);                             \
    } while (0)

#define TestEqual(case, actual, expected)                  \
    do                                                     \
    {                                                      \
        const TestContext context = makeTestContext(case); \
        test_equal(context, actual, expected);             \
    } while (0)

inline void test_true(const TestContext &context, bool actual)
{
    if (actual)
    {
        context.success(std::cerr);
        return;
    }
    context.error(std::cerr);
    std::cerr << " -> " << std::boolalpha << actual << std::endl;
}

template <typename T, typename U>
inline void test_equal(const TestContext &context, const T &actual, const U &expected)
{
    if (actual == expected)
    {
        context.success(std::cerr);
        return;
    }
    context.error(std::cerr);
    std::cerr << " -> " << actual << " == " << expected << std::endl;
}
