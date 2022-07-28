#ifndef UTIL_H
#define UTIL_H


class util
{
public:
    util(){};
    ~util(){};

    template <class T>
    static T limit(T x, T min, T max)
    {
        if(x < min) return min;
        else if(x > max) return max;
        return x;
    }

    static double map(double x, double in_min, double in_max, double out_min, double out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
      }
};

#endif // UTIL_H
