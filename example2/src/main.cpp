#include "mbed.h"
#include "rtos.h"

D igitalOut led1(LED2);

void led1_thread(void const *args) {
    while (true) {
        led1 = !led1;
        Thread::wait(1000);
    }
}

int main() {
    Thread thread(led1_thread);
    while(true) {
    }
}
