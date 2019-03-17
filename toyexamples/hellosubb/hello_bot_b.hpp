#include <iostream>
#include <cstdio>

#include "../hellosuba/hello_bot_a.hpp"

template<bool sayhello>
class SayHelloB : public SayHello<sayhello> {
};