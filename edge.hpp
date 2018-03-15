#ifndef __EDGE__
#define __EDGE__

struct edge
{
    double left, right;
    int32_t parent, child;

    edge(double l, double r, int32_t p, int32_t c)
        : left{ l }, right{ r }, parent{ p }, child{ c }
    {
    }
};

#endif
