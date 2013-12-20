#include <18F4550.h>
#device adc=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#use delay(clock=48000000)


 #define USB_CON_SENSE_PIN PIN_B2

 #include <usb_cdc.h>


void main() {
   BYTE i, j, address, value;

   int16 q,q1;
   float p;

   q1=0;
   
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);

   usb_cdc_init();
   usb_init();

//      while(!usb_cdc_connected()) {}

   do {
      usb_task();
      if (usb_enumerated()) {

      delay_ms(500);
      q = read_adc();
      if (q!=q1){
      p = 5.0 * q / 1024.0;
      printf(usb_cdc_putc,"\r Voltage=%01.2fV", p);
      }
      q1=q;
   }
      } while (TRUE);
}
