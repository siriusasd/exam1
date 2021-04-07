#include "mbed.h"
#include "uLCD_4DGL.h"

AnalogOut aout(PA_5);
 
DigitalOut led1(LED1);    // Configure LED1 pin as output
DigitalOut led2(LED2);
DigitalOut led3(LED3);

DigitalIn Up(D7); // Configure P1_14 pin as input
DigitalIn Down(D6);
DigitalIn Select(D5);
 
uLCD_4DGL uLCD(D1, D0, D2);

float ADCdata[200];

int sample = 200;

void genWave(float freq)
{
    int counter=0, c=0,a=0,en=0;
    while(1)
    {   
        for (float i=0.0f; i < 1.0f; i += )
        { 
            aout = (float)i/110.0f;
            counter++;      //count how many loops of for loop
            if(counter%5==0&&c<sample&&a==50)
            {
                ADCdata[c++]=(double)i*3.3/100;
                //printf("%f\r\n", (double)i*3.3/10);
            }
            ThisThread::sleep_for(200ms/sample);
            //wait_us(time);
        }
    }
}



int main()
{
    int enable=0,index=1;
    uLCD.printf("\nSelect slew rates:\n"); //Default Green on black text
    uLCD.printf("\n1/8 <--\n");
    uLCD.printf("\n1/4\n");
    uLCD.printf("\n1/2\n");
    uLCD.printf("\n1\n");

    while(1) 
    {
        if(Up.read()==1&&Down.read()==0&&Select.read()==0) 
        {    
            enable=1;   
            if(index>1)
                index--;
            else
                index=4;
        } 
        else if(Up.read()==0&&Down.read()==1&&Select.read()==0) 
        {
            enable=1;   //<-----
            if(index<4)
                index++;
            else
                index=1;

        }
        else if(Up.read()==0&&Down.read()==0&&Select.read()==1) {
            //function
            break;
        }
        else {
            continue;
        }

        if(enable==1)
        {
            switch(index)
            {
                case 1:
                    uLCD.cls();
                    uLCD.printf("\nSelect slew rates:\n"); //Default Green on black text
                    uLCD.printf("\n1/8 <--\n");
                    uLCD.printf("\n1/4\n");
                    uLCD.printf("\n1/2\n");
                    uLCD.printf("\n1\n");
                    enable=0;
                    break;
                case 2:
                    uLCD.cls();
                    uLCD.printf("\nSelect slew rates:\n"); //Default Green on black text
                    uLCD.printf("\n1/8\n");
                    uLCD.printf("\n1/4 <--\n");
                    uLCD.printf("\n1/2\n");
                    uLCD.printf("\n1\n");
                    enable=0;
                    break;
                case 3:
                    uLCD.cls();
                    uLCD.printf("\nSelect slew rates:\n"); //Default Green on black text
                    uLCD.printf("\n1/8\n");
                    uLCD.printf("\n1/4\n");
                    uLCD.printf("\n1/2 <--\n");
                    uLCD.printf("\n1\n");
                    enable=0;
                    break;
                case 4:
                    uLCD.cls();
                    uLCD.printf("\nSelect slew rates:\n"); //Default Green on black text
                    uLCD.printf("\n1/8\n");
                    uLCD.printf("\n1/4\n");
                    uLCD.printf("\n1/2\n");
                    uLCD.printf("\n1 <--\n");
                    enable=0;
                    break;
            }
        }
        else {
            continue;
        }
    }
    switch(index)
    {
        case 1:
            uLCD.printf("\n\n1/8 is selected!!\n");
            genWave(1/8);
            break;
        case 2:
            uLCD.printf("\n\n1/4 is selected!!\n");
            genWave(1/4);
            break;
        case 3:
            uLCD.printf("\n\n1/2 is selected!!\n");
            genWave(1/2);
            break;
        case 4:
            uLCD.printf("\n\n1 is selected!\n");
            genWave(1);
            break;
    }
    return 0;
}