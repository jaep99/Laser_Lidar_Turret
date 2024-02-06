
#include "mbed.h"
#include "rtos.h"
#include "SDFileSystem.h"
#include "wave_player.h"
#include "uLCD_4DGL.h"
#include "XNucleo53L0A1.h"
#include "Servo.h"


class RGBLed
{
public:
    RGBLed(PinName redpin, PinName greenpin, PinName bluepin);
    void write(float red,float green, float blue);
private:
    DigitalOut _redpin;
    DigitalOut _greenpin;
    DigitalOut _bluepin;
};

RGBLed::RGBLed (PinName redpin, PinName greenpin, PinName bluepin)
    : _redpin(redpin), _greenpin(greenpin), _bluepin(bluepin)
{
}

void RGBLed::write(float red,float green, float blue)
{
    _redpin = red;
    _greenpin = green;
    _bluepin = blue;
}

//I2C sensor pins
#define VL53L0_I2C_SDA   p28
#define VL53L0_I2C_SCL   p27

static XNucleo53L0A1 *board=NULL;

SDFileSystem sd(p5, p6, p7, p8, "sd");
AnalogOut DACout(p18);
wave_player waver(&DACout);
RGBLed rgb(p20,p19,p17);
Servo horizontal(p23);
Servo vertical(p21);
uLCD_4DGL uLCD(p9,p10,p30);
Serial bluemod(p13,p14);
Serial pc(USBTX,USBRX);
DigitalOut shdn(p22);
DigitalOut myLED(LED1);
// flag indicating current movement state (moving = false, stopped = true)
volatile bool valid = true;
// boolean to detect motion
volatile bool detected = false;
// horizontal servo value
volatile float x = 0.0;
// vertical servo value
volatile float y = 0.0;
// left button pressed
volatile bool left = false;
// right button pressed
volatile bool right = false;
// up button pressed
volatile bool up = false;
// down button pressed
volatile bool down = false;

void audio_thread(void const *args)
{
    while(1)
    {
        
        if (detected)
        {
            FILE *wave_file;
            printf("\r\n\nHello, wave world!\n\r");
            Thread::wait(1000);
            wave_file=fopen("/sd/mydir/Freeze.wav","r");
            if(wave_file==NULL) printf("file open error!\n\n\r");
            waver.play(wave_file);
            fclose(wave_file);
            Thread::wait(1000);
        }

    }
}

void move_right(void const*args)
{
    while(1)
    {
        if (!valid && x < 1.0 && right)
        {
            x += .05;
            horizontal = x;
            Thread::wait(200);
        }
    }
}


void move_left(void const*args)
{
    while (1)
    {
        if (!valid && x > 0.0 && left)
        {
            x -= .05;
            horizontal = x;
            Thread::wait(200);
        }
    }
}

void move_up(void const*args)
{
    while (1)
    {
        if (!valid && y > 0.0 && up)
        {
            y -= .05;
            vertical = y;
            Thread::wait(200);
        }
    }
}

void move_down(void const*args)
{
    while (1)
    {
        if (!valid && y < 1.0 && down)
        {
            y += .05;
            vertical = y;
            Thread::wait(200);
        }
    }
}

void Bluetooth_thread(void const *args)
{
    char bnum = 0;
    char bhit = 0;
    while(1) {
        if (bluemod.readable())
        {
            pc.printf("GOT HERE \n");
            if (bluemod.getc()=='!') {
                pc.printf("EXCLAIM \n");
                if (bluemod.getc()=='B') { 
                    pc.printf("BUTTON \n");
                    bnum = bluemod.getc();
                    bhit = bluemod.getc();
                    pc.printf("NUMBER = %c \n", bnum);
                    if (bluemod.getc()==char(~('!' + 'B' + bnum + bhit))) { //checksum OK?
                        switch(bnum)
                        {
                            case '5':
                                // UP ARROW
                                if (bhit == '1')
                                {
                                    valid = false;
                                    up = true;
                                    rgb.write(1.0, 0.0, 0.0);  // Red movement state
                                    Thread::wait(50);
                                } 
                                else
                                {
                                    up = false;
                                    rgb.write(1.0, 1.0, 0.0); // Yellow transition state
                                    Thread::wait(2000);
                                    rgb.write(0.0, 1.0, 0.0);  // Green ready state
                                    valid = true;
                                }
                                break;
                            
                            case '6':
                                // DOWN ARROW
                                if (bhit == '1')
                                {
                                    valid = false;
                                    down = true;
                                    rgb.write(1.0, 0.0, 0.0);
                                    Thread::wait(50);
                                } 
                                else
                                {
                                    down = false;
                                    rgb.write(1.0, 1.0, 0.0);
                                    Thread::wait(2000);
                                    rgb.write(0.0, 1.0, 0.0);
                                    valid = true; 
                                }
                                break;
                            case '7':
                                // LEFT ARROW
                                if (bhit == '1')
                                {
                                    valid = false;
                                    left = true;
                                    rgb.write(1.0, 0.0, 0.0);
                                    Thread::wait(50);
                                } 
                                else
                                {
                                    left = false;
                                    rgb.write(1.0, 1.0, 0.0);
                                    Thread::wait(2000);
                                    rgb.write(0.0, 1.0, 0.0);
                                    valid = true;
                                }
                                break;
                            case '8':
                                // RIGHT ARROW
                                if (bhit == '1')
                                {
                                    valid = false;
                                    right = true;
                                    rgb.write(1.0, 0.0, 0.0);
                                    Thread::wait(50);
                                } 
                                else
                                {
                                    right = false;
                                    rgb.write(1.0, 1.0, 0.0);
                                    Thread::wait(2000);
                                    rgb.write(0.0, 1.0, 0.0);
                                    valid = true;
                                }
                                break;
                            default:
                                break;
                        }
                        
                        Thread::wait(100);
                    }
                }
            }
        }
    }
}

int main()
{
    Thread thread6(move_up);
    Thread thread7(move_down);
    Thread thread1(move_left);
    Thread thread2(move_right);
    Thread thread3(audio_thread);
    Thread thread4(Bluetooth_thread);

    // Write constant LCD display
    uLCD.cls();
    uLCD.locate(0, 0);
    uLCD.text_height(2);
    uLCD.text_width(2);
    uLCD.printf("DONT MOVE WE WILL CATCH YOU");
    uLCD.filled_circle(84, 72, 10,  0xfff0);
    uLCD.filled_circle(40, 72, 10,  0xfff0);
    uLCD.filled_circle(84, 72, 4,  0x00ff);
    uLCD.filled_circle(40, 72, 4,  0x00ff);
    uLCD.filled_rectangle(15, 96, 113, 110, 0x0ff0);
    uLCD.filled_rectangle(15, 110, 23, 125, 0x0ff0);
    uLCD.filled_rectangle(105, 110, 113, 125, 0x0ff0);

    // Initialize LIDAR board and associated variables
    int status;
    int move;
    uint32_t distance;
    int first = 0;
    DevI2C *device_i2c = new DevI2C(VL53L0_I2C_SDA, VL53L0_I2C_SCL);
    /* creates the 53L0A1 expansion board singleton obj */
    board = XNucleo53L0A1::instance(device_i2c, A2, D8, D2);
    shdn = 0; //must reset sensor for an mbed reset to work
    wait(0.1);
    shdn = 1;
    wait(0.1);
    /* init the 53L0A1 board with default values */
    status = board->init_board();
    while (status) {
        pc.printf("Failed to init board! \r\n");
        status = board->init_board();
    }
    while (1) {
        if (valid)
        {
            status = board->sensor_centre->get_distance(&distance);
            if (status == VL53L0X_ERROR_NONE) {
                pc.printf("D=%ld mm\r\n", distance);
                first = distance;
            }
            Thread::wait(50);
            move = board->sensor_centre->get_distance(&distance);
            if (move == VL53L0X_ERROR_NONE) {
                pc.printf("Sec=%ld mm\r\n", distance);
            }
            pc.printf("Num1=%ld mm\r\n", abs((int)(first) - (int)(distance)));
            if(abs((int)(first) - (int)(distance)) > 50)
            {
                detected = true;
                Thread::wait(4000);
                detected = false;
            }
            Thread::wait(100);
        }
    }
}