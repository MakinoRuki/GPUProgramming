#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
template <bool sayhello>
class SayHello {
public:
 void SayIt() {
   if (sayhello) {
     cout<<"hello !!!"<<endl;
   } else {
     cout<<"they don't want me to say hello !!!"<<endl;
   }
 }
};