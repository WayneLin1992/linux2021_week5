#include "vector.h"

int main()
{
    v(float, 2, vec1);
    vec_push_back(vec1, 0.0);
    vec_push_back(vec1, 1.1);
    vec_push_back(vec1, 2.2);
    vec_push_back(vec1, 3.3);
    vec_push_back(vec1, 4.4);
    vec_push_back(vec1, 5.5);
    vec_pop_back(vec1);
    vec_pop_back(vec1);
    vec_pop_back(vec1);
    vec_pop_back(vec1);
    vec_pop_back(vec1);
    vec_pop_back(vec1);
    return 0;
}
