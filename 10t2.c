#include <stdio.h>

int dec2bin(int number)
{
    int bin = 0, k = 1;

    while (number)
    {
        bin += (number % 2) * k;
        k *= 10;
        number /= 2;
    }

    return bin;
}

int main() {

	int number = 0;
	scanf("%d", &number);

	printf("%d\n", dec2bin(number));

}
