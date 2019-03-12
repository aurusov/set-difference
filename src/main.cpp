#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> get_diff_v1(const std::vector<std::string> & set1, const std::vector<std::string> & set2)
{
    std::vector<std::string> diff;
    for (std::size_t set1_index = 0; set1_index < set1.size(); ++set1_index)
    {
        bool found = false;
        for (std::size_t set2_index = 0; set2_index < set2.size(); ++set2_index)
        {
            found = set1[set1_index] == set2[set2_index];
            if (found)
                break;
        }

        if (!found)
            diff.push_back(set1[set1_index]);
    }
    return diff;
}

std::vector<std::string> get_diff_v2(const std::vector<std::string> & set1, const std::vector<std::string> & set2)
{
    std::vector<std::string> diff;
    for (const auto & value1 : set1)
    {
        if (std::find(set2.begin(), set2.end(), value1) == set2.end())
            diff.push_back(value1);
    }
    return diff;
}

std::vector<std::string> get_diff_v3(const std::vector<std::string> & set1, const std::vector<std::string> & set2)
{
    auto set1_sorted{set1};
    auto set2_sorted{set2};
    std::sort(set1_sorted.begin(), set1_sorted.end());
    std::sort(set2_sorted.begin(), set2_sorted.end());

    std::vector<std::string> diff;
    diff.resize(set1_sorted.size());

    const auto diff_end = std::set_difference(
        set1_sorted.begin(), set1_sorted.end(),
        set2_sorted.begin(), set2_sorted.end(),
        diff.begin());

    std::cout << "diff.size() before erase = " << diff.size() << std::endl;
    diff.erase(diff_end, diff.end());
    std::cout << "diff.size() after erase = " << diff.size() << std::endl;

    return diff;
}

std::vector<std::string> get_diff_v4(const std::vector<std::string> & set1, const std::vector<std::string> & set2)
{
    auto set1_sorted{set1};
    auto set2_sorted{set2};
    std::sort(set1_sorted.begin(), set1_sorted.end());
    std::sort(set2_sorted.begin(), set2_sorted.end());

    std::vector<std::string> diff;
    std::set_difference(
        set1_sorted.begin(), set1_sorted.end(),
        set2_sorted.begin(), set2_sorted.end(),
        std::inserter(diff, diff.begin()));

    return diff;
}

void print(const std::vector<std::string> & set)
{
    for (const auto & value : set)
        std::cout << value << std::endl;
}

int main()
{
    const std::vector<std::string> set1 {
        "text_1",
        "text_2",
        "text_3",
        "text_4",
        "text_5",
        "text_6",
        "text_7",
    };

    const std::vector<std::string> set2 {
        "text_5",
        "text_4",
        "text_3",
    };

    std::cout << "set1" << std::endl;
    print(set1);
    std::cout << std::endl;

    std::cout << "set2" << std::endl;
    print(set2);
    std::cout << std::endl;

    std::cout << "diff" << std::endl;
    print(get_diff_v4(set1, set2));

    return 0;
}
