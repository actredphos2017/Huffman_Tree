#include <map>
#include <cmath>
#include <string>

using namespace std;

unsigned int count_of_decimal_digits(double x) {
    unsigned int count = 0;
    while (x - (int)x > 0.000001 || x - (int)x < -0.000001) {
        x *= 10;
        count++;
    }
    return count;
}

map<char, int> double_map_to_int(map<char, double> m) {
    unsigned int max_count = 0;
    for (auto& c : m) {
        unsigned int count = count_of_decimal_digits(c.second);
        if (count > max_count)
            max_count = count;
    }
    map<char, int> m_int;
    for (auto& c : m)
        m_int[c.first] = (int)(c.second * pow(10, max_count));
    return m_int;
}

double string_to_double(string s) {
    double x = 0;
    bool flag = false;
    unsigned int count = 0;
    for (auto i = s.begin(); i != s.end(); i++) {
        if (*i == '.') {
            flag = true;
            continue;
        }
        x = x * 10 + (*i - '0');
        if (flag) count++;
    }
    while (count--)
        x /= 10;
    return x;
}