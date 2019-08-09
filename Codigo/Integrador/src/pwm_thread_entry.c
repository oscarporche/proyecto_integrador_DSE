#include "pwm_thread.h"
#include "adc_tread.h"
/* pwm Thread entry function */
 uint16_t pwrcount=0;
 uint16_t pwrsum[10]={0},SendLCDBuffer[4]={0};
 uint16_t pwrtotal=0,rpmprom=0,rpm=0;
 float w_k=0,rev_k1=0,t=0.05;
 uint16_t rev;
 int sample=0;

 //variables de control

   float kp,ki,kd; //Constantes para parámetros de controlador PID
   float SetPoint; //Referencia de Temperatura
   float rT,eT,iT,dT,yT,iT0,eT0; //Variables de controlador PID
   UINT max,min; //Variables para anti-windup
   uint16_t status,ControlDutyCicle,muestras=0,uT;
   uint16_t ReceiveSetPoint[1]={0};

   //fin
void pwm_thread_entry(void)
{


  g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
  g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, 5, TIMER_PWM_UNIT_PERCENT, 1);
  g_timer1.p_api->start(g_timer1.p_ctrl);

  g_external_irq0.p_api->open(g_external_irq0.p_ctrl,g_external_irq0.p_cfg);

  g_timer3.p_api->open(g_timer3.p_ctrl, g_timer3.p_cfg);
  g_timer3.p_api->start (g_timer3.p_ctrl);


     min=0.0;
     max=1000.0;
     iT0=0.0;
     eT0=0.0;
     kp=0.16430001;
     ki=0.00100000005;
     kd=0.0;

  while (1) {

      tx_thread_sleep (10);
      status = _txe_queue_receive (&adc, ReceiveSetPoint, TX_WAIT_FOREVER);
      SetPoint = (float) ReceiveSetPoint[0] * 10;
      if (SetPoint<3000)
      {

      }
      else
      {
          SetPoint=3000;
      }

      SendLCDBuffer[0]=ControlDutyCicle/10;
      SendLCDBuffer[1]=SetPoint;
      SendLCDBuffer[2]=rpm;

                      status=tx_queue_send (&datadisplay,SendLCDBuffer,TX_NO_WAIT);


  }


}

void pwr(external_irq_callback_args_t * p_args)
{
    (void)p_args;
   // pwrcount++;
    // if(pwrcount>=4){
         rev++;
     //   pwrcount = 0;
     //}

}

void RPMS(timer_callback_args_t *p_args)
{
    (void)p_args;
//w_k = (float) ((rev - rev_k1) / t);
//w_k = w_k * (3.14f) / 30.0f;
//rev_k1 = rev;



//inicia el control
yT = (float)(rev*2400);//w_k; //Lectura de retroalimentacion y(kT)
rev=0;
rpm=yT/8;
rT = SetPoint*8; //Set Point r(kT)
eT = rT - yT; //Calcular senal de error e(kT)
iT = ki * eT + iT0; //Calcular termino integrativo i(kT)
dT = kd * (eT - eT0); //Calcular termino derivativo d(kT)

uT = (UINT)(iT + kp * eT + dT); //Calcular senal de control u(kT)

if (uT > max)
{ //Anti-windup
    uT = max;
}
else
{
    if (uT < min)
    {
        uT = min;
    }
}
ControlDutyCicle = 1000 - uT;
iT0 = iT;
eT0 = eT;
//fin del control
g_timer1.p_api->dutyCycleSet (g_timer1.p_ctrl, (ControlDutyCicle*100),TIMER_PWM_UNIT_PERCENT_X_1000, 1);

}
