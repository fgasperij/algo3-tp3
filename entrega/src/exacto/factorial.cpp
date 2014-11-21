#include <iostream>

int main() 
{
 long factorial = 1;
 long sumatoria_factorial = 0;
 for(int i = 1; i < 15; ++i) {
   factorial *= i;
   sumatoria_factorial += factorial;
   std::cout << i << ": " << factorial << ' ' << sumatoria_factorial << std::endl;
 }

 return 0;
}
