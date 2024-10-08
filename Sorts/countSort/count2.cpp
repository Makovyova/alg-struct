#include <algorithm>
#include <numeric>
#include <vector>

// ���������� ��������� ������� �������, ������������ ���� ����������.
// Identity-������� ���������� ���������� �� �������� ��� ���������.
// �� ����� ������������ �� � �������� ������� ��� ����� ��-���������.
const auto identity = [](auto x) { return x; };
using Identity = decltype(identity);

// ���������� ��������� ���������� ���������������� ������ ��� ��������� �� �����,
// � ������������ ������ ��� ��������� �� ������ ���������.
template<typename ForwardIterator, typename RandomAccessIterator, typename Key = Identity>
void counting_sort(
    ForwardIterator first, ForwardIterator last, // ������� ������������������
    RandomAccessIterator out, // ���������
    Key key = identity) // �������, �������� ���� ��������
{
    // ��������� ��� ������������������ �� ������.
    if (first == last)
        return;

    // ���������� ����������� � ������������ ����� ���������.
    auto compare = [&](const auto& lhs, const auto& rhs) { return key(lhs) < key(rhs); };
    auto minmax = std::minmax_element(first, last, compare);
    auto min_key = key(*minmax.first);
    auto max_key = key(*minmax.second);
    // ���� ����� �� ����������, �� ������������������ ��� �������������.
    if (min_key == max_key) {
        std::copy(first, last, out);
        return;
    }

    // �������� ������ ��� �������� ���������.
    // ��� ����� �������������� ����������� ������, ���� ������������ �������� �������
    // ��� size_t, ���� ������ ������� ������������������ ���������� ���.
    std::vector<std::size_t> count(max_key - min_key + 1);
    // ������������ ���������� ��������� � ���������� ������.
    std::for_each(first, last, [&](const auto& x) { ++count[key(x) - min_key]; });
    // �������� ������ ������� � ��������� ��������� �����.
    // ���� ����� �������� � count ���� {2,2,2,2},
    // �� ����� partial_sum ��� �����   {0,2,4,6},
    // �.�. �������, �� ������� ������ ������ �������� � ���������� ������.
    count[0] = 0;
    std::partial_sum(count.begin(), count.end(), count.begin());
    // �������� �������� � �������� ������, ���������� ������� � "count".
    // ����������� ����� �������� �� �����������.
    std::for_each(first, last, [&](auto& x) { out[count[key(x) - min_key]++] = x; });
    // ��� "count[key(x) - min_key]" ����������� ��� ����, � ��� ����� ������� � ��������� �������, ��������
    // auto count_ref = [&](const auto& x) -> std::size_t& { return count[key(x) - min_key]; };
}

