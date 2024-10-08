#include <algorithm>
#include <numeric>
#include <vector>

// Сортировка подсчетом требует функцию, возвращающую ключ сортировки.
// Identity-функция возвращает переданный ей аргумент без изменений.
// Мы будем использовать ее в качестве функции для ключа по-умолчанию.
const auto identity = [](auto x) { return x; };
using Identity = decltype(identity);

// Сортировка подсчетом использует последовательный доступ для элементов на входе,
// и произвольный доступ для элементов на выходе алгоритма.
template<typename ForwardIterator, typename RandomAccessIterator, typename Key = Identity>
void counting_sort(
    ForwardIterator first, ForwardIterator last, // входная последовательность
    RandomAccessIterator out, // результат
    Key key = identity) // функция, выдающая ключ элемента
{
    // Проверяем что последовательность не пустая.
    if (first == last)
        return;

    // Определяем минимальный и максимальные ключи элементов.
    auto compare = [&](const auto& lhs, const auto& rhs) { return key(lhs) < key(rhs); };
    auto minmax = std::minmax_element(first, last, compare);
    auto min_key = key(*minmax.first);
    auto max_key = key(*minmax.second);
    // Если ключи не отличаются, то последовательность уже отсортирована.
    if (min_key == max_key) {
        std::copy(first, last, out);
        return;
    }

    // Выделяем массив для подсчета элементов.
    // Тут можно оптимизировать потребление памяти, если использовать счетчики меньшие
    // чем size_t, если размер входной последовательности достаточно мал.
    std::vector<std::size_t> count(max_key - min_key + 1);
    // Подсчитываем количество элементов с одинаковым ключом.
    std::for_each(first, last, [&](const auto& x) { ++count[key(x) - min_key]; });
    // Обнуляем первый счетчик и вычисляем частичные суммы.
    // Если после подсчета в count было {2,2,2,2},
    // то после partial_sum там будет   {0,2,4,6},
    // т.е. индексы, по которым должны лежать элементы с одинаковым ключом.
    count[0] = 0;
    std::partial_sum(count.begin(), count.end(), count.begin());
    // Копируем элементы в выходной массив, увеличивая индексы в "count".
    // Копирование можно заменить на перемещение.
    std::for_each(first, last, [&](auto& x) { out[count[key(x) - min_key]++] = x; });
    // Код "count[key(x) - min_key]" встречается два раза, и его можно вынести в отдельную функцию, например
    // auto count_ref = [&](const auto& x) -> std::size_t& { return count[key(x) - min_key]; };
}

