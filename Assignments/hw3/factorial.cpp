#include <iostream>
#define TEST_ARRAY_SIZE 4

long int factorial(int num);

long int factorial(int num) {
  int fact = 1;
    for(unsigned int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int test[TEST_ARRAY_SIZE] = {1, 2, 5, 7};
    for (unsigned int i = 0; i < TEST_ARRAY_SIZE; i++) {
        std::cout << "Factorial of " << test[i] << " is " << factorial(test[i]) << std::endl;
    }
}
