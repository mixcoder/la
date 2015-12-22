#include <vector>
#include <functional>
#include "la/la.h"
#include "ebt/ebt.h"

std::vector<std::pair<std::string, std::function<void(void)>>> tests = {
    {"test-size", []() {
        la::matrix<double> a {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        ebt::assert_equals(3, a.rows());
        ebt::assert_equals(3, a.cols());
        la::vector<double> b {1, 2, 3};
        ebt::assert_equals(3, b.size());
    }},

    {"test-mult", []() {
        la::matrix<double> a {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        la::vector<double> b {1, 2, 3};
        la::vector<double> r = mult(a, b);
        ebt::assert_equals(3, r.size());
        ebt::assert_equals(14, r(0));
        ebt::assert_equals(32, r(1));
        ebt::assert_equals(50, r(2));
    }},
};

int main()
{
    for (auto& t: tests) {
        std::cout << t.first << std::endl;
        t.second();
    }

    return 0;
}
