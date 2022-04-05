template <typename T, size_t n>
class AutoQueue
{
    T array[n] = {0};
    size_t curr_pos = n - 1;
    size_t sz = n;
    size_t real_size = 0;

    bool calculateMinMax = false;
    T minimum = 0;
    T maximum = 0;
    T average = 0;
    int avgSum = 0;

public:
    void push(T v)
    {
        // calc filled array size
        if (real_size < sz)
        {
            real_size++;
        }

        avgSum -= array[curr_pos];
        avgSum += v;
        average = avgSum / real_size;

        array[curr_pos] = v;
        curr_pos = curr_pos == 0 ? sz - 1 : curr_pos - 1;

        if (calculateMinMax)
        {
            minimum = 0;
            maximum = 0;
            for (size_t i = 0; i < real_size; ++i)
            {
                if (minimum == 0 || minimum > get(i))
                {
                    minimum = get(i);
                }
                if (maximum < get(i))
                {
                    maximum = get(i);
                }
            }
        }
    }

    const T &operator[](size_t pos) const
    {
        size_t index = curr_pos + 1 + pos;
        return array[index < sz ? index : index % sz];
    }

    const T get (size_t pos) const {
        size_t index = curr_pos + 1 + pos;
        return array[index < sz ? index : index % sz];
    }

    size_t size() const
    {
        return real_size;
    }

    T min()
    {
        return minimum;
    }

    T max()
    {
        return maximum;
    }

    T avg()
    {
        return average;
    }

    void calcMinMax(bool b)
    {
        calculateMinMax = b;
    }
};