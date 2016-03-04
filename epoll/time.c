#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

int main()
{
    struct timeval oldtime, newtime;
    gettimeofday(&oldtime, NULL);
    for(int i =0; i < 10; i++) {
        sleep(1);
    }
    gettimeofday(&newtime, NULL);
    double usec = (newtime.tv_sec - oldtime.tv_sec)*(double)1000000+(newtime.tv_usec-oldtime.tv_usec);
    std::cout << "Time "<<usec/1000000<<std::endl;
}
