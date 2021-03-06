#include <adc_tread.h>
//#include "adc_tread.h"
#define C_FILTER_ORDER  8



UINT status;
uint16_t SendBuffer[1]={0};
uint16_t u16ADC_Data;
uint16_t u16ADC_Filtered;
uint16_t u16Volts;
bool bfmainTick;

/* ADC Thread entry function */
void adc_tread_entry(void)
{

      g_timer0.p_api->open (g_timer0.p_ctrl, g_timer0.p_cfg);
      g_timer0.p_api->start (g_timer0.p_ctrl);

      g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
      g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
      g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    /* TODO: add your own code here */
    while (1)
    {


        tx_thread_sleep (1);
    }

}
void filter_adc(timer_callback_args_t *p_args){
(void)p_args;

                   g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);

                   if(C_FILTER_ORDER > 1)
                       {
                         u16ADC_Filtered = (uint16_t)((u16ADC_Data + (C_FILTER_ORDER - 1) * u16ADC_Filtered) / C_FILTER_ORDER);
                       }
                   else
                       {
                         u16ADC_Filtered = u16ADC_Data;
                       }

                   u16Volts = ((uint16_t)((uint32_t)(1294 * u16ADC_Filtered) / 1000));

                   SendBuffer[0]=u16Volts;
                   status=tx_queue_send (&adc,SendBuffer,TX_NO_WAIT);


}
