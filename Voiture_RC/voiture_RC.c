#if defined (__PCM__)
#include <16F877A.h>
#device ICD=TRUE
#fuses HS,NOWDT,NOPROTECT
#endif
#use delay(clock=20000000)

#define val 0X3E
byte n,i,var,var0,var1,var_tim0,ID;

#int_timer0
void tmer0_int()
{
set_timer0(104);
var_tim0=1;
}

void init(void);
void trans(void);

main()
{
init();
while(true){
set_timer0(12);
enable_interrupts(INT_TIMER0);
n=0;i=7;var=val;
trans();
disable_interrupts(INT_TIMER0);
output_low(pin_c4);
}
}

void init(void){
setup_counters(RTCC_INTERNAL,RTCC_DIV_64);
set_tris_c( 0x00);
output_c(0x00);
n=0;
do{
output_high(pin_b5);
delay_ms(500);
output_low(pin_b5);
delay_ms(500);
n++;
}while(n<=5);
enable_interrupts(GLOBAL);
}

void trans(void){
do{
while(var_tim0==0){};
var_tim0=0;
if(bit_test(var,i)==1)output_high(pin_c4);
else output_low(pin_c4);
i--;n++;
}while(n<8);
}
