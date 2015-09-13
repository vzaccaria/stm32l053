#include "mbed.h"

/* Needed by RTOS when syntax checking through Emacs */
#define TOOLCHAIN_GCC
#include "rtos.h"

DigitalOut led1(LED2);

int main() {

    Thread thread([](void const *){
            while (true) {
                led1 = !led1;
                Thread::wait(200);
            }
        });


    while(true) {
    }
}
