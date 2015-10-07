#include "mbed.h"

/* Needed by RTOS when syntax checking through Emacs */
#define TOOLCHAIN_GCC
#include "rtos.h"
#include "proto/message.pb-c.h"

/* We statically allocate the buffer in which to pack the message */
#define PCT_BUF_SIZE 128

/* Initialize sensor board */
#include "x_cube_mems.h"

volatile float temp_value_C;
volatile float hum_value;
volatile float pressure_value;

static X_CUBE_MEMS *mems_expansion_board = X_CUBE_MEMS::Instance();

Serial pc(SERIAL_TX, SERIAL_RX);
DigitalOut led1(LED2);

union { unsigned char bytes[4]; uint32_t value; } o32_to_bytes;

int main() {
    uint8_t buf[PCT_BUF_SIZE];

    auto sendData = [&](const Pct *m) {

        auto len = pct__get_packed_size(m);
        pct__pack(m, buf);

        auto sendHeader = [](uint32_t len) {
            o32_to_bytes.value = len;
            /* ;; magic sync word */
            pc.printf("VZ");
            for(uint i=0; i<4; i++) {
                pc.printf("%c", o32_to_bytes.bytes[i]);
            }
        };

        auto sendPayload = [](const unsigned char *buf, uint32_t len) {
            for(uint i=0; i<len; i++) {
                pc.printf("%c", buf[i]);
            }
        };

        sendHeader(len);
        sendPayload(buf, len);
    };

    auto initSensors = [&]() {
        mems_expansion_board->hts221.Power_ON();
        mems_expansion_board->hts221.HTS221_Calibration();
    };

    auto getSensorValues = [&](Pct &m) {
        mems_expansion_board->hts221.GetTemperature((float *)&m.temp_value_c);
        mems_expansion_board->hts221.GetHumidity((float *)&m.hum_value);
        mems_expansion_board->lps25h.GetPressure((float *)&m.pressure_value);
    };

    initSensors();

    while (true) {
        led1 = !led1;
        Pct m = PCT__INIT;
        getSensorValues(m);
        sendData(&m);
        Thread::wait(200);
    }
}
