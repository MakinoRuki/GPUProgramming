#include <iostream>
#include <cstdio>

#include "../helloworld.h"

template<bool sayhello>
class SayHelloA : public SayHello<sayhello> {
};