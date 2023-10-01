#ifndef INTERVAL_MATH
#define INTERVAL_MATH

#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>

namespace interval_math
{

enum class Infinity
{
    POSITIVE,
    NEGATIVE
};

enum class BadState
{
    NaN,
};

enum class Zero
{
    POSITIVE,
    NEGATIVE
};

/*
    Приоритеты значений:
    1) Если NaN == true, то число считать NaN
    2) Если inf == true, то число считать infinity (учитываем параметр negative)
    3) Если не NaN и не infinity, то считать как обычное число (используем параметр num, при этом параметр negative УЧИТЫВАЕТСЯ)
*/

enum class NumType
{
    NaN = 0,
    NEGATIVE_INFINITY = 1,
    NEGATIVE_NUMBER = 2,
    NEGATIVE_ZERO = 3,
    POSITIVE_ZERO = 4,
    POSITIVE_NUMBER = 5,
    POSITIVE_INFINITY = 6,
};

template <typename T>
class ExtendedSetPrivate
{
private:
    T _num;
    bool _inf;
    bool _negative;
    bool _NaN;

public:
    T num() const { return _num; }
    bool inf() const { return _inf; }
    bool negative() const { return _negative; }
    bool NaN() const { return _NaN; }
    T sign_num() const { return _num * (_negative ? -1 : 1); }

    ExtendedSetPrivate() : _num(0), _inf(false), _negative(false), _NaN(false)
    {

    }

    ExtendedSetPrivate(T num) : ExtendedSetPrivate()
    {
        _num = num;
        if (_num < 0) {
            _num = -_num;
            _negative = true;
        }
    }

    ExtendedSetPrivate(Infinity inf_type) : ExtendedSetPrivate()
    {
        _inf = true;
        if (inf_type == Infinity::POSITIVE) {
            _negative = false;
        }
        else if (inf_type == Infinity::NEGATIVE) {
            _negative = true;
        }
    }

    ExtendedSetPrivate(BadState bad_state_type) : ExtendedSetPrivate()
    {
        _NaN = true;
    }

    ExtendedSetPrivate(Zero zero_type) : ExtendedSetPrivate()
    {
        if (zero_type == Zero::NEGATIVE) {
            _negative = true;
        }
    }
};


template <typename T>
class ExtendedSet : public ExtendedSetPrivate<T>
{
public:
    static NumType getNumType(const ExtendedSet<T> & es) {
        if (es.NaN()) return NumType::NaN;
        if (es.inf() && es.negative()) return NumType::NEGATIVE_INFINITY;
        if (es.inf() && !es.negative()) return NumType::POSITIVE_INFINITY;
        if (!es.inf() && es.num() == 0 && es.negative()) return NumType::NEGATIVE_ZERO;
        if (!es.inf() && es.num() == 0 && !es.negative()) return NumType::POSITIVE_ZERO;
        if (!es.inf() && es.num() != 0 && es.negative()) return NumType::NEGATIVE_NUMBER;
        if (!es.inf() && es.num() != 0 && !es.negative()) return NumType::POSITIVE_NUMBER;
        return NumType::NaN;
    }

    ExtendedSet() : ExtendedSetPrivate()
    {

    }

    ExtendedSet(T num) : ExtendedSetPrivate(num)
    {

    }

    ExtendedSet(Infinity inf_type) : ExtendedSetPrivate(inf_type)
    {

    }

    ExtendedSet(BadState bad_state_type) : ExtendedSetPrivate(bad_state_type)
    {
        
    }

    ExtendedSet(Zero zero_type) : ExtendedSetPrivate(zero_type)
    {
        
    }


    friend std::ostream & operator<<(std::ostream & out, const ExtendedSet<T> & es) {
        NumType es_type = getNumType(es);
        if (es_type == NumType::NEGATIVE_INFINITY) out << "-Infinity";
        else if (es_type == NumType::NEGATIVE_NUMBER) out << es.sign_num();
        else if (es_type == NumType::NEGATIVE_ZERO) out << "-0";
        else if (es_type == NumType::POSITIVE_ZERO) out << "+0";
        else if (es_type == NumType::POSITIVE_NUMBER) out << es.sign_num();
        else if (es_type == NumType::POSITIVE_INFINITY) out << "+Infinity";
        return out;
    }

    friend bool operator==(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        if (es_1.NaN() || es_2.NaN()) return false;
        if (es_1.negative() != es_2.negative()) return false;
        if (es_1.num() != es_2.num()) return false;
        if (es_1.inf() != es_2.inf()) return false;
        return true;
    }

    friend bool operator!=(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        return !(es_1 == es_2);
    }

    friend bool operator>(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        if (es_1.NaN() || es_2.NaN()) return false;

        NumType es_1_type = getNumType(es_1);
        NumType es_2_type = getNumType(es_2);
        if (es_1_type > es_2_type) return true;
        else if (es_1_type < es_2_type) return false;

        if (es_1_type == es_2_type)
        {
            if (es_1_type == NumType::NEGATIVE_NUMBER) return es_1.num() < es_2.num();
            if (es_1_type == NumType::POSITIVE_NUMBER) return es_1.num() > es_2.num();
        }

        return false;
    }

    friend bool operator>=(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        if (es_1.NaN() || es_2.NaN()) return false;
        return es_1 > es_2 || es_1 == es_2;
    }

    friend bool operator<(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        if (es_1.NaN() || es_2.NaN()) return false;
        return !(es_1 >= es_2);
    }

    friend bool operator<=(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        if (es_1.NaN() || es_2.NaN()) return false;
        return !(es_1 > es_2);
    }

    friend ExtendedSet<T> operator+(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        if (es_1.NaN() || es_2.NaN()) return ExtendedSet<T>(BadState::NaN);

        NumType es_1_type = getNumType(es_1);
        NumType es_2_type = getNumType(es_2);

        /* Special cases */
        if (es_1_type == NumType::NEGATIVE_INFINITY)
        {
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
            else return ExtendedSet<T>(Infinity::NEGATIVE);
        }
        if (es_1_type == NumType::NEGATIVE_NUMBER)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(Infinity::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(Infinity::POSITIVE);
        }
        if (es_1_type == NumType::NEGATIVE_ZERO)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(Infinity::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(Infinity::POSITIVE);
            if (es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Zero::NEGATIVE);
        }
        if (es_1_type == NumType::POSITIVE_ZERO)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(Infinity::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(Infinity::POSITIVE);
        }
        if (es_1_type == NumType::POSITIVE_NUMBER)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(Infinity::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(Infinity::POSITIVE);
        }
        if (es_1_type == NumType::POSITIVE_INFINITY)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
            else return ExtendedSet<T>(Infinity::POSITIVE);
        }

        /* Usual math case */
        T num_1 = es_1.sign_num();
        T num_2 = es_2.sign_num();

        return ExtendedSet<T>(num_1 + num_2);
    }

    friend ExtendedSet<T> operator-(const ExtendedSet<T> & es)
    {
        if (es.NaN()) return ExtendedSet<T>(BadState::NaN);

        NumType es_type = getNumType(es);

        /* Special cases */
        if (es_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(Infinity::POSITIVE);
        if (es_type == NumType::NEGATIVE_NUMBER) return ExtendedSet<T>(es.num());
        if (es_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Zero::POSITIVE);
        if (es_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Zero::NEGATIVE);
        if (es_type == NumType::POSITIVE_NUMBER)  return ExtendedSet<T>(-es.num());
        if (es_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(Infinity::NEGATIVE);

        return ExtendedSet<T>(BadState::NaN);
    }

    friend ExtendedSet<T> operator-(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        return es_1 + -es_2;
    }

    friend ExtendedSet<T> operator*(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        if (es_1.NaN() || es_2.NaN()) return ExtendedSet<T>(BadState::NaN);

        NumType es_1_type = getNumType(es_1);
        NumType es_2_type = getNumType(es_2);

        /* Special cases */
        if (es_1_type == NumType::NEGATIVE_INFINITY) {
            if (es_2_type == NumType::NEGATIVE_INFINITY || es_2_type == NumType::NEGATIVE_NUMBER) return ExtendedSet<T>(Infinity::POSITIVE);
            if (es_2_type == NumType::NEGATIVE_ZERO || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(BadState::NaN);
            if (es_2_type == NumType::POSITIVE_INFINITY || es_2_type == NumType::POSITIVE_NUMBER) return ExtendedSet<T>(Infinity::NEGATIVE);
        }
        if (es_1_type == NumType::NEGATIVE_NUMBER) {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(Infinity::POSITIVE);
            if (es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Zero::POSITIVE);
            if (es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Zero::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(Infinity::NEGATIVE);
        }
        if (es_1_type == NumType::NEGATIVE_ZERO) {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
            if (es_2_type == NumType::NEGATIVE_NUMBER || es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Zero::POSITIVE);
            if (es_2_type == NumType::POSITIVE_NUMBER || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Zero::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
        }
        if (es_1_type == NumType::POSITIVE_ZERO) {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
            if (es_2_type == NumType::NEGATIVE_NUMBER || es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Zero::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_NUMBER || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Zero::POSITIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
        }
        if (es_1_type == NumType::POSITIVE_NUMBER) {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(Infinity::NEGATIVE);
            if (es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Zero::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Zero::POSITIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(Infinity::POSITIVE);
        }
        if (es_1_type == NumType::POSITIVE_INFINITY) {
            if (es_2_type == NumType::NEGATIVE_INFINITY || es_2_type == NumType::NEGATIVE_NUMBER) return ExtendedSet<T>(Infinity::NEGATIVE);
            if (es_2_type == NumType::NEGATIVE_ZERO || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(BadState::NaN);
            if (es_2_type == NumType::POSITIVE_INFINITY || es_2_type == NumType::POSITIVE_NUMBER) return ExtendedSet<T>(Infinity::POSITIVE);
        }

        /* Usual math case */
        T num_1 = es_1.sign_num();
        T num_2 = es_2.sign_num();

        return ExtendedSet<T>(num_1 * num_2);
    }

    friend ExtendedSet<T> operator/(const ExtendedSet<T> & es_1, const ExtendedSet<T> & es_2)
    {
        if (es_1.NaN() || es_2.NaN()) return ExtendedSet<T>(BadState::NaN);

        NumType es_1_type = getNumType(es_1);
        NumType es_2_type = getNumType(es_2);

        /* Special cases */
        if (es_1_type == NumType::NEGATIVE_INFINITY)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
            if (es_2_type == NumType::NEGATIVE_NUMBER || es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Infinity::POSITIVE);
            if (es_2_type == NumType::POSITIVE_NUMBER || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Infinity::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
        }
        if (es_1_type == NumType::NEGATIVE_NUMBER)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY || es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Zero::POSITIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Zero::NEGATIVE);
        }
        if (es_1_type == NumType::NEGATIVE_ZERO)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY || es_2_type == NumType::NEGATIVE_NUMBER) return ExtendedSet<T>(Zero::POSITIVE);
            if (es_2_type == NumType::NEGATIVE_ZERO || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(BadState::NaN);
            if (es_2_type == NumType::POSITIVE_INFINITY || es_2_type == NumType::POSITIVE_NUMBER) return ExtendedSet<T>(Zero::NEGATIVE);
        }
        if (es_1_type == NumType::POSITIVE_ZERO)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY || es_2_type == NumType::NEGATIVE_NUMBER) return ExtendedSet<T>(Zero::NEGATIVE);
            if (es_2_type == NumType::NEGATIVE_ZERO || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(BadState::NaN);
            if (es_2_type == NumType::POSITIVE_INFINITY || es_2_type == NumType::POSITIVE_NUMBER) return ExtendedSet<T>(Zero::POSITIVE);
        }
        if (es_1_type == NumType::POSITIVE_NUMBER)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY || es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Zero::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Zero::POSITIVE);
        }
        if (es_1_type == NumType::POSITIVE_INFINITY)
        {
            if (es_2_type == NumType::NEGATIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
            if (es_2_type == NumType::NEGATIVE_NUMBER || es_2_type == NumType::NEGATIVE_ZERO) return ExtendedSet<T>(Infinity::NEGATIVE);
            if (es_2_type == NumType::POSITIVE_NUMBER || es_2_type == NumType::POSITIVE_ZERO) return ExtendedSet<T>(Infinity::POSITIVE);
            if (es_2_type == NumType::POSITIVE_INFINITY) return ExtendedSet<T>(BadState::NaN);
        }

        /* Usual math case */
        T num_1 = es_1.sign_num();
        T num_2 = es_2.sign_num();

        return ExtendedSet<T>(num_1 / num_2);
    }
};



template <typename T>
class MultiInterval;



template <typename T>
class Interval
{
private:
    ExtendedSet<T> a, b;

public:
    Interval() : a(0), b(0) {};
    Interval(const ExtendedSet<T> & a) : a(a), b(a) {}
    Interval(const ExtendedSet<T> & a, const ExtendedSet<T> & b) : a(a), b(b) {}

    ExtendedSet<T> get_a() const { return a; }
    ExtendedSet<T> get_b() const { return b; }
    void set_a(ExtendedSet<T> a) { this->a = a; }
    void set_b(ExtendedSet<T> b) { this->b = b; }


    friend std::ostream & operator<<(std::ostream & out, const Interval<T> & interval) {
        out << "[" << interval.a << ";" << interval.b << "]";
        return out;
    }

    friend bool operator==(const Interval<T> & interval_1, const Interval<T> &interval_2)
    {
        return interval_1.a == interval_2.a && interval_1.b == interval_2.b; 
    }

    friend bool operator!=(const Interval<T> & interval_1, const Interval<T> &interval_2)
    {
        return !(interval_1 == interval_2);
    }

    friend MultiInterval<T> operator+(const Interval<T> & interval_1, const Interval<T> &interval_2)
    {
        return Interval<T>(interval_1.a + interval_2.a, interval_1.b + interval_2.b);
    }

    friend MultiInterval<T> operator-(const Interval<T> & interval_1, const Interval<T> &interval_2)
    {
        return Interval<T>(interval_1.a - interval_2.b, interval_1.b - interval_2.a);
    }

    friend MultiInterval<T> operator-(const Interval<T> & interval)
    {
        return Interval<T>(-interval.b, -interval.a);
    }

    friend MultiInterval<T> operator*(const Interval<T> & interval_1, const Interval<T> &interval_2)
    {
        return Interval<T>(
            std::min({
                interval_1.a * interval_2.a,
                interval_1.a * interval_2.b,
                interval_1.b * interval_2.a,
                interval_1.b * interval_2.b
            }),
            std::max({
                interval_1.a * interval_2.a,
                interval_1.a * interval_2.b,
                interval_1.b * interval_2.a,
                interval_1.b * interval_2.b
            })
        );
    }

    friend MultiInterval<T> operator/(T val, const Interval<T> &interval)
    {
        if (interval.a != 0 && interval.b == 0)
        {
            return Interval<T>(Infinity::NEGATIVE, val / interval.a);
        }
        else if (interval.a == 0 && interval.b != 0)
        {
            return Interval<T>(val / interval.b, Infinity::POSITIVE);
        }
        else if (interval.a * interval.b < 0)
        {
            return {
                Interval<T>(Infinity::NEGATIVE, val / interval.a),
                Interval<T>(val / interval.b, Infinity::POSITIVE)
            };
        }

        return Interval<T>(val / interval.b, val / interval.a);
    }

    friend MultiInterval<T> operator/(const Interval<T> & interval_1, const Interval<T> &interval_2)
    {
        return interval_1 * (1 / interval_2);
    }
};



template <typename T>
class MultiInterval
{
private:
    std::vector<Interval<T>> intervals;

protected:
    std::vector<Interval<T>> mergeIntervals()
    {
        if (intervals.empty()) return {};

        // Сортировка интервалов по начальной точке
        std::sort(intervals.begin(), intervals.end(), [](const Interval<T> & interval_1, const Interval<T> & interval_2) {
            return interval_1.get_a() < interval_2.get_a();
        });

        std::vector<Interval<T>> merged;
        merged.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i) {
            if (merged.back().get_b() >= intervals[i].get_a()) {
                // Объединение перекрывающихся интервалов
                merged.back().set_b(std::max(merged.back().get_b(), intervals[i].get_b()));
            } else {
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }

public:
    MultiInterval()
    {

    }

    MultiInterval(std::initializer_list<Interval<T>> lst)
    {
        intervals.insert(intervals.end(), lst.begin(), lst.end());
        intervals = mergeIntervals();
    }

    MultiInterval(const Interval<T> & interval)
    {
        intervals.push_back(interval);
    }


    friend std::ostream & operator<<(std::ostream & out, const MultiInterval<T> & m_interval) {
        out << "{";
        for (int i = 0; i < m_interval.intervals.size(); i++) {
            out << m_interval.intervals[i];
            if (i < m_interval.intervals.size() - 1) out << ", ";
        }
        out << "}";
        return out;
    }

    friend bool operator==(const MultiInterval<T> & m_interval_1, const MultiInterval<T> & m_interval_2)
    {
        if (m_interval_1.intervals.size() != m_interval_2.intervals.size()) return false;
        for (int i = 0; i < m_interval_1.intervals.size(); i++) {
            if (m_interval_1.intervals[i] != m_interval_2.intervals[i]) return false;
        }
        return true;
    }

    friend bool operator!=(const MultiInterval<T> & m_interval_1, const MultiInterval<T> & m_interval_2)
    {
        return !(m_interval_1 == m_interval_2);
    }

    friend MultiInterval<T> operator+(const MultiInterval<T> & m_interval_1, const MultiInterval<T> & m_interval_2)
    {
        MultiInterval<T> result;
        for (auto & interval_1 : m_interval_1.intervals) {
            for (auto & interval_2 : m_interval_2.intervals) {
                std::vector<Interval<T>> op = (interval_1 + interval_2).intervals;
                std::copy(op.begin(), op.end(), std::back_inserter(result.intervals));
            }
        }
        result.intervals = result.mergeIntervals();

        return result;
    }

    friend MultiInterval<T> operator-(const MultiInterval<T> & m_interval_1, const MultiInterval<T> & m_interval_2)
    {
        MultiInterval<T> result;
        for (auto & interval_1 : m_interval_1.intervals) {
            for (auto & interval_2 : m_interval_2.intervals) {
                std::vector<Interval<T>> op = (interval_1 - interval_2).intervals;
                std::copy(op.begin(), op.end(), std::back_inserter(result.intervals));
            }
        }
        result.intervals = result.mergeIntervals();

        return result;
    }

    friend MultiInterval<T> operator-(const MultiInterval<T> & m_interval)
    {
        MultiInterval<T> result;
        for (auto & interval : m_interval.intervals) {
            std::vector<Interval<T>> op = (-interval).intervals;
            std::copy(op.begin(), op.end(), std::back_inserter(result.intervals));
        }
        result.intervals = result.mergeIntervals();

        return result;
    }

    friend MultiInterval<T> operator*(const MultiInterval<T> & m_interval_1, const MultiInterval<T> & m_interval_2)
    {
        MultiInterval<T> result;
        for (const Interval<T> & interval_1 : m_interval_1.intervals) {
            for (const Interval<T> & interval_2 : m_interval_2.intervals) {
                std::vector<Interval<T>> op = (interval_1 * interval_2).intervals;
                std::copy(op.begin(), op.end(), std::back_inserter(result.intervals));
            }
        }
        result.intervals = result.mergeIntervals();

        return result;
    }

    friend MultiInterval<T> operator/(const MultiInterval<T> & m_interval_1, const MultiInterval<T> & m_interval_2)
    {
        MultiInterval<T> result;
        for (auto & interval_1 : m_interval_1.intervals) {
            for (auto & interval_2 : m_interval_2.intervals) {
                std::vector<Interval<T>> op = (interval_1 / interval_2).intervals;
                std::copy(op.begin(), op.end(), std::back_inserter(result.intervals));
            }
        }
        result.intervals = result.mergeIntervals();

        return result;
    }
};

}
#endif // INTERVAL_MATH
