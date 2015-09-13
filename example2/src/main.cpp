#include "mbed.h"

/* Needed by RTOS when syntax checking through Emacs */
#define TOOLCHAIN_GCC
#include "rtos.h"
#include "proto/message.pb-c.h"

/* We statically allocate the buffer in which to pack the message */
#define PCT_BUF_SIZE 128

Serial pc(SERIAL_TX, SERIAL_RX);

DigitalOut led1(LED2);

int main() {

    Thread thread([](void const *){
            uint8_t buf[PCT_BUF_SIZE];

            auto sendData = [&](const Pct *m) {
                auto len = pct__get_packed_size(m);
                pct__pack(m, buf);
                for(uint i=0; i<len; i++) {
                    pc.printf("%d", buf[i]);
                }
            };

            while (true) {
                led1 = !led1;
                Pct m = PCT__INIT;
                m.pressure = 0.3f;
                m.temp = 52.0f;
                m.humidity = 10.0f;
                sendData(&m);
                Thread::wait(200);
            }
        });

    while(true) {
    }
}
