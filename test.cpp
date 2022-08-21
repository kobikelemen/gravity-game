
#include <utility>


int main()
{

    float o = 5.f;
    float t = 6.f;
    std::pair<*float,*float> x = {&o,&t};
}