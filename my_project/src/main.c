#include <stdbool.h>
#include <stdint.h>

#define GPIO_PORT_F       (volatile uint32_t *)0x40025000
#define GPIO_F_DATA_R     *(GPIO_PORT_F + 0x000)
#define GPIO_F_LOCK_R     *(GPIO_PORT_F + 0x520)
#define GPIO_F_CR_R       *(GPIO_PORT_F + 0x524)
#define GPIO_F_AMSEL_R    *(GPIO_PORT_F + 0x528)
#define GPIO_F_PCTL_R     *(GPIO_PORT_F + 0x52C)
#define GPIO_F_DIR_R      *(GPIO_PORT_F + 0x400)
#define GPIO_F_AFSEL_R    *(GPIO_PORT_F + 0x420)
#define GPIO_F_PUR_R      *(GPIO_PORT_F + 0x510)
#define GPIO_F_DEN_R      *(GPIO_PORT_F + 0x51C)

#define SYSCTL_RCG2_R   (*((volatile uint32_t *)0x400FE608))

unsigned long In;
unsigned long Out;

void delay_ms(unsigned int time) {
    
    while(time -- > 0);
}


void Port_F_Init(void) {

    SYSCTL_RCG2_R |= 0x00000020;
    delay_ms(2000000);

    GPIO_F_LOCK_R    = 0x4C4F434B;
    GPIO_F_CR_R      = 0x1F;
    GPIO_F_AMSEL_R  = 0x00;
    GPIO_F_PCTL_R    = 0x00000000;
    GPIO_F_DIR_R     = 0xFF;
    GPIO_F_AFSEL_R   = 0x00;
    GPIO_F_PUR_R     = 0x11;
    GPIO_F_DEN_R     = 0x1F;

}


int main(void) {

    Port_F_Init();
#if 1
    while(1) {
        GPIO_F_DATA_R = 0xFF;
        delay_ms(4000000);
        GPIO_F_DATA_R = 0x00;
        delay_ms(4000000);
    }
#else
    while(1) {
        In = GPIO_F_DATA_R & 0x10;
        In= In>>2;
        Out = GPIO_F_DATA_R;
        Out &= 0xFB;
#endif

    return 0;
}
