#ifndef HASHTUPLES_H
#define HASHTUPLES_H

#include <utility>

namespace HashTuples{

    struct hash3tuple {
    
        template <class T1, class T2, class T3>
        std::size_t operator()(const std::tuple<T1, T2, T3>& x) const
        {
            return std::get<0>(x) ^ std::get<1>(x) ^ std::get<2>(x);
        }
    };
    
    struct hash2tuple {
    
        template <class T1, class T2>
        std::size_t operator()(const std::tuple<T1, T2>& x) const
        {
            return std::get<0>(x) ^ std::get<1>(x);
        }
    };

}

#endif