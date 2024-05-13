#include <iostream>
#include <vector>
#include <type_traits>
#include <limits>
#include <algorithm>
#include <iterator>

template <typename T>
std::enable_if_t<std::is_arithmetic_v<T>, std::vector<std::uint8_t>> to_digits(const std::vector<T>& numbers)
{
    std::vector<std::uint8_t> digits;
    digits.reserve(numbers.size() * std::numeric_limits<T>::digits10);
    std::for_each(numbers.cbegin(), numbers.cend(), [&digits](auto n) {
        std::uint8_t d[std::numeric_limits<T>::digits10];
        if (n < 0) n = -n;
        std::uint8_t l = n != 0 ? 0 : (d[0] = 0, 1);
        for (; n; n /= 10, ++l) d[l] = n % 10;
        do digits.push_back(d[l - 1]); while (--l);
        });
    return digits;
}

int main()
{
    std::vector<int> iv{ 1200, 2450, 643, -7896, 90345 };
    std::cout << "Original vector iv: ";
    std::copy(iv.cbegin(), iv.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    auto iv_digits = to_digits(iv);
    std::cout << "Digits of original vector iv: ";
    std::copy(iv_digits.cbegin(), iv_digits.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::vector<long long> llv{ 234567, -987654321, 908070, 14253647 };
    std::cout << "Original vector llv: ";
    std::copy(llv.cbegin(), llv.cend(), std::ostream_iterator<long long>(std::cout, " "));
    std::cout << std::endl;
    auto llv_digits = to_digits(llv);
    std::cout << "Digits of original vector llv: ";
    std::copy(llv_digits.cbegin(), llv_digits.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}