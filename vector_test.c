//#include "vector.h"
#include "vector_ilog.h"

int main()
{
    srand(NULL);
    v(float, 2, vec1);
//    vec_push_back(vec1, 0.0);
//    vec_push_back(vec1, 1.1);
//    vec_push_back(vec1, 2.2);
//    vec_push_back(vec1, 3.3);
//    vec_push_back(vec1, 4.4);
//    vec_push_back(vec1, 5.5);
    for(int i = 0; i<100; i++){
        vec_push_back(vec1,rand()%1024);
    }
//    vec_pop_back(vec1);
//    vec_pop_back(vec1);
//    vec_pop_back(vec1);
//    vec_pop_back(vec1);
//    vec_pop_back(vec1);
//    vec_pop_back(vec1);
    return 0;
}
