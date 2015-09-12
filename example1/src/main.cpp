#include "mbed.h"
#include "x_cube_mems.h"

DigitalOut myled(LED1);
Serial pc(SERIAL_TX, SERIAL_RX);
volatile float TEMPERATURE_Value_C;
volatile float TEMPERATURE_Value_F;
volatile float HUMIDITY_Value;
volatile float PRESSURE_Value;
volatile AxesRaw_TypeDef MAG_Value;
volatile AxesRaw_TypeDef ACC_Value;
volatile AxesRaw_TypeDef GYR_Value;

int main() {

    /* Create sensor board object */
    static X_CUBE_MEMS *mems_expansion_board = X_CUBE_MEMS::Instance();

    while(1) {
        myled = 1; // LED is ON
        wait(0.2); // 200 ms
        myled = 0; // LED is OFF
        wait(1.0); // 1 sec

        /* Get instantaneous data from all sensors */
        mems_expansion_board->hts221.GetTemperature((float *)&TEMPERATURE_Value_C);
        mems_expansion_board->hts221.GetHumidity((float *)&HUMIDITY_Value);
        mems_expansion_board->lps25h.GetPressure((float *)&PRESSURE_Value);
        mems_expansion_board->lis3mdl.GetAxes((AxesRaw_TypeDef *)&MAG_Value);
        mems_expansion_board->lsm6ds0.Acc_GetAxes((AxesRaw_TypeDef *)&ACC_Value);
        mems_expansion_board->lsm6ds0.Gyro_GetAxes((AxesRaw_TypeDef *)&GYR_Value);

        TEMPERATURE_Value_F = (TEMPERATURE_Value_C * 1.8f) + 32.0f;
        pc.printf("Temperature:\t\t %f C / %f F\r\n", TEMPERATURE_Value_C, TEMPERATURE_Value_F);
        pc.printf("Humidity:\t\t %f%%\r\n", HUMIDITY_Value);
        pc.printf("Pressure:\t\t %f hPa\r\n", PRESSURE_Value);
        pc.printf("Magnetometer (mGauss):\t X: %d, Y: %d, Z: %d\r\n", MAG_Value.AXIS_X, MAG_Value.AXIS_Y, MAG_Value.AXIS_Z);
        pc.printf("Accelerometer (mg):\t X: %d, Y: %d, Z: %d\r\n", ACC_Value.AXIS_X, ACC_Value.AXIS_Y, ACC_Value.AXIS_Z);
        pc.printf("Gyroscope (mdps):\t X: %d, Y: %d, Z: %d\r\n", GYR_Value.AXIS_X, GYR_Value.AXIS_Y, GYR_Value.AXIS_Z);
        pc.printf("\r\n");
    }
}
