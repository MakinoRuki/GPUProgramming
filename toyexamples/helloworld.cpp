#include <iostream>
#include <cstdio>
#include <cstring>
#include "hellosubb/hello_bot_b.hpp"
using namespace std;
int main() {
    SayHello<true> say_hello;
    say_hello.SayIt();
    SayHelloA<true> hello_bot_a;
    hello_bot_a.SayIt();
    SayHelloB<false> hello_bot_b;
    hello_bot_b.SayIt();
 //   say_hello.SayIt();
    //cout<<"Hello World !!!"<<endl;
    return 0;
}