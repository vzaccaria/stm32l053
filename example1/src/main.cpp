#include "mbed.h"
#include "x_cube_mems.h"

DigitalOut myled(LED1);
Serial pc(SERIAL_TX, SERIAL_RX);
volatile float temp_value_C;
volatile float hum_value;
volatile float pressure_value;


int main() {

    /* Create sensor board object */
    static X_CUBE_MEMS *mems_expansion_board = X_CUBE_MEMS::Instance();
    mems_expansion_board->hts221.Power_ON();
    mems_expansion_board->hts221.HTS221_Calibration();

    while(1) {
        myled = 1; // LED is ON
        wait(0.2); // 200 ms
        myled = 0; // LED is OFF
        wait(1.0); // 1 sec

        /* Get instantaneous data from all sensors */
        mems_expansion_board->hts221.GetTemperature((float *)&temp_value_C);
        mems_expansion_board->hts221.GetHumidity((float *)&hum_value);
        mems_expansion_board->lps25h.GetPressure((float *)&pressure_value);

        int tc = temp_value_C;
        int hv = hum_value;
        int pv = pressure_value;
        pc.printf("Temperature:\t\t %d C \r\n", tc);
        pc.printf("Humidity: \t\t %d \n", hv);
        pc.printf("Pressure: \t\t %d \n", pv);
        pc.printf("\r\n");
    }
}
