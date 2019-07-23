/* generated thread header file - do not edit */
#ifndef PWM_THREAD_H_
#define PWM_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void pwm_thread_entry(void);
#else
extern void pwm_thread_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer3;
#ifndef RPMS
void RPMS(timer_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq0;
#ifndef pwr
void pwr(external_irq_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1;
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* PWM_THREAD_H_ */
