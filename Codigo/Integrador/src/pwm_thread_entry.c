#include "pwm_thread.h"
#include "adc_tread.h"
/* pwm Thread entry function */
uint16_t pwrcount=0;

 volatile uint16_t pwrsum[10]={0};
 volatile uint16_t pwrtotal=0;
 int sample=0;
void pwm_thread_entry(void)
{
    //variables de control
    float a,b,c; //Constantes para parámetros de controlador PID
    float SetPoint; //Referencia de Temperatura
    float rT,eT,iT,dT,yT,uT,iT0,eT0; //Variables de controlador PID
    float max,min; //Variables para anti-windup
    min=0.0;
    max=100.0;
    iT0=0.0;
    eT0=0.0;
    a=0.1243;
    b=0.0062;
    c=0.6215;
    //fin
  UINT status,ControlDutyCicle;
  uint16_t ReceiveSetPoint[1]={0};
  g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
  g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, 5, TIMER_PWM_UNIT_PERCENT, 1);
  g_timer1.p_api->start(g_timer1.p_ctrl);

  g_external_irq0.p_api->open(g_external_irq0.p_ctrl,g_external_irq0.p_cfg);

  g_timer3.p_api->open(g_timer3.p_ctrl, g_timer3.p_cfg);
  g_timer3.p_api->start (g_timer3.p_ctrl);

  while (1) {

      tx_thread_sleep (10);

      status=_txe_queue_receive(&adc,ReceiveSetPoint,TX_WAIT_FOREVER);

      SetPoint=(float)ReceiveSetPoint[0]*10;


         //inicia el control

      yT=pwrtotal; //Lectura de retroalimentacion y(kT)
      rT=SetPoint;//Set Point r(kT)
      eT=rT-yT; //Calcular senal de error e(kT)
      iT=b*eT+iT0; //Calcular termino integrativo i(kT)
      dT=c*(eT-eT0); //Calcular termino derivativo d(kT)
      uT=iT+a*eT+dT; //Calcular senal de control u(kT)
      if (uT>max){ //Anti-windup
      uT=max;
      }
      else {
       if (uT<min){
      uT=min;
       }
      }
      ControlDutyCicle=100-uT;
      iT0=iT;
      eT0=eT;
          //fin del control
      g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, (ControlDutyCicle), TIMER_PWM_UNIT_PERCENT, 1);
  }


}

void pwr(external_irq_callback_args_t * p_args)
{
     pwrcount++;
}

void RPMS(timer_callback_args_t * p_args)
{

pwrsum[sample]=pwrcount;
    if(sample<9)
    {
        sample++;
    }else
    {
        sample=0;
    }
    pwrtotal=((pwrsum[0]+pwrsum[1]+pwrsum[2]+pwrsum[3]+pwrsum[4]+pwrsum[5]+pwrsum[6]+pwrsum[7]+pwrsum[8]+pwrsum[9])*600)/4;
    pwrcount=0;
}
