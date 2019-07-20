#include "pwm_thread.h"
#include "adc_tread.h"
/* pwm Thread entry function */
void pwm_thread_entry(void)
{

  UINT status;
  uint16_t ReceiveBuffer[1]={0};
  uint8_t STA=0;

  g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
  g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, 5, TIMER_PWM_UNIT_PERCENT, 1);
  g_timer1.p_api->start(g_timer1.p_ctrl);
  uint8_t dutycycle = 2;
  while (1) {

      tx_thread_sleep (10);

      status=_txe_queue_receive(&adc,ReceiveBuffer,TX_WAIT_FOREVER);
      STA=ReceiveBuffer[0]/3.2;

      dutycycle += 2;
      g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, (STA %100), TIMER_PWM_UNIT_PERCENT, 1);
  }


}

