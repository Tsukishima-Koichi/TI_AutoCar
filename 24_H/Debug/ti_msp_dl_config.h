/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_MOTOR */
#define PWM_MOTOR_INST                                                     TIMG7
#define PWM_MOTOR_INST_IRQHandler                               TIMG7_IRQHandler
#define PWM_MOTOR_INST_INT_IRQN                                 (TIMG7_INT_IRQn)
#define PWM_MOTOR_INST_CLK_FREQ                                         80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_MOTOR_C0_PORT                                             GPIOA
#define GPIO_PWM_MOTOR_C0_PIN                                     DL_GPIO_PIN_28
#define GPIO_PWM_MOTOR_C0_IOMUX                                   (IOMUX_PINCM3)
#define GPIO_PWM_MOTOR_C0_IOMUX_FUNC                  IOMUX_PINCM3_PF_TIMG7_CCP0
#define GPIO_PWM_MOTOR_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_MOTOR_C1_PORT                                             GPIOA
#define GPIO_PWM_MOTOR_C1_PIN                                     DL_GPIO_PIN_31
#define GPIO_PWM_MOTOR_C1_IOMUX                                   (IOMUX_PINCM6)
#define GPIO_PWM_MOTOR_C1_IOMUX_FUNC                  IOMUX_PINCM6_PF_TIMG7_CCP1
#define GPIO_PWM_MOTOR_C1_IDX                                DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                            (99U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMA1)
#define TIMER_1_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                          (7999U)



/* Defines for UART_DEBUG */
#define UART_DEBUG_INST                                                    UART0
#define UART_DEBUG_INST_FREQUENCY                                       40000000
#define UART_DEBUG_INST_IRQHandler                              UART0_IRQHandler
#define UART_DEBUG_INST_INT_IRQN                                  UART0_INT_IRQn
#define GPIO_UART_DEBUG_RX_PORT                                            GPIOA
#define GPIO_UART_DEBUG_TX_PORT                                            GPIOA
#define GPIO_UART_DEBUG_RX_PIN                                    DL_GPIO_PIN_11
#define GPIO_UART_DEBUG_TX_PIN                                    DL_GPIO_PIN_10
#define GPIO_UART_DEBUG_IOMUX_RX                                 (IOMUX_PINCM22)
#define GPIO_UART_DEBUG_IOMUX_TX                                 (IOMUX_PINCM21)
#define GPIO_UART_DEBUG_IOMUX_RX_FUNC                  IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_DEBUG_IOMUX_TX_FUNC                  IOMUX_PINCM21_PF_UART0_TX
#define UART_DEBUG_BAUD_RATE                                            (115200)
#define UART_DEBUG_IBRD_40_MHZ_115200_BAUD                                  (21)
#define UART_DEBUG_FBRD_40_MHZ_115200_BAUD                                  (45)
/* Defines for UART_GYRO */
#define UART_GYRO_INST                                                     UART1
#define UART_GYRO_INST_FREQUENCY                                        40000000
#define UART_GYRO_INST_IRQHandler                               UART1_IRQHandler
#define UART_GYRO_INST_INT_IRQN                                   UART1_INT_IRQn
#define GPIO_UART_GYRO_RX_PORT                                             GPIOA
#define GPIO_UART_GYRO_TX_PORT                                             GPIOA
#define GPIO_UART_GYRO_RX_PIN                                      DL_GPIO_PIN_9
#define GPIO_UART_GYRO_TX_PIN                                      DL_GPIO_PIN_8
#define GPIO_UART_GYRO_IOMUX_RX                                  (IOMUX_PINCM20)
#define GPIO_UART_GYRO_IOMUX_TX                                  (IOMUX_PINCM19)
#define GPIO_UART_GYRO_IOMUX_RX_FUNC                   IOMUX_PINCM20_PF_UART1_RX
#define GPIO_UART_GYRO_IOMUX_TX_FUNC                   IOMUX_PINCM19_PF_UART1_TX
#define UART_GYRO_BAUD_RATE                                             (115200)
#define UART_GYRO_IBRD_40_MHZ_115200_BAUD                                   (21)
#define UART_GYRO_FBRD_40_MHZ_115200_BAUD                                   (45)





/* Defines for DMA_GYRO */
#define DMA_GYRO_CHAN_ID                                                     (0)
#define UART_GYRO_INST_DMA_TRIGGER                           (DMA_UART1_RX_TRIG)


/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOA)

/* Defines for LED1: GPIOA.7 with pinCMx 14 on package pin 13 */
#define LED_LED1_PIN                                             (DL_GPIO_PIN_7)
#define LED_LED1_IOMUX                                           (IOMUX_PINCM14)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOA)

/* Defines for KEY1: GPIOA.12 with pinCMx 34 on package pin 27 */
// pins affected by this interrupt request:["KEY1"]
#define KEY_INT_IRQN                                            (GPIOA_INT_IRQn)
#define KEY_INT_IIDX                            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define KEY_KEY1_IIDX                                       (DL_GPIO_IIDX_DIO12)
#define KEY_KEY1_PIN                                            (DL_GPIO_PIN_12)
#define KEY_KEY1_IOMUX                                           (IOMUX_PINCM34)
/* Defines for KEY2: GPIOA.13 with pinCMx 35 on package pin 28 */
#define KEY_KEY2_PIN                                            (DL_GPIO_PIN_13)
#define KEY_KEY2_IOMUX                                           (IOMUX_PINCM35)
/* Defines for KEY3: GPIOA.14 with pinCMx 36 on package pin 29 */
#define KEY_KEY3_PIN                                            (DL_GPIO_PIN_14)
#define KEY_KEY3_IOMUX                                           (IOMUX_PINCM36)
/* Defines for KEY4: GPIOA.15 with pinCMx 37 on package pin 30 */
#define KEY_KEY4_PIN                                            (DL_GPIO_PIN_15)
#define KEY_KEY4_IOMUX                                           (IOMUX_PINCM37)
/* Port definition for Pin Group ENCODER */
#define ENCODER_PORT                                                     (GPIOB)

/* Defines for E1A: GPIOB.18 with pinCMx 44 on package pin 37 */
// pins affected by this interrupt request:["E1A","E1B","E2A","E2B"]
#define ENCODER_INT_IRQN                                        (GPIOB_INT_IRQn)
#define ENCODER_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define ENCODER_E1A_IIDX                                    (DL_GPIO_IIDX_DIO18)
#define ENCODER_E1A_PIN                                         (DL_GPIO_PIN_18)
#define ENCODER_E1A_IOMUX                                        (IOMUX_PINCM44)
/* Defines for E1B: GPIOB.6 with pinCMx 23 on package pin 20 */
#define ENCODER_E1B_IIDX                                     (DL_GPIO_IIDX_DIO6)
#define ENCODER_E1B_PIN                                          (DL_GPIO_PIN_6)
#define ENCODER_E1B_IOMUX                                        (IOMUX_PINCM23)
/* Defines for E2A: GPIOB.7 with pinCMx 24 on package pin 21 */
#define ENCODER_E2A_IIDX                                     (DL_GPIO_IIDX_DIO7)
#define ENCODER_E2A_PIN                                          (DL_GPIO_PIN_7)
#define ENCODER_E2A_IOMUX                                        (IOMUX_PINCM24)
/* Defines for E2B: GPIOB.8 with pinCMx 25 on package pin 22 */
#define ENCODER_E2B_IIDX                                     (DL_GPIO_IIDX_DIO8)
#define ENCODER_E2B_PIN                                          (DL_GPIO_PIN_8)
#define ENCODER_E2B_IOMUX                                        (IOMUX_PINCM25)
/* Defines for AIN1: GPIOA.2 with pinCMx 7 on package pin 8 */
#define MOTOR_AIN1_PORT                                                  (GPIOA)
#define MOTOR_AIN1_PIN                                           (DL_GPIO_PIN_2)
#define MOTOR_AIN1_IOMUX                                          (IOMUX_PINCM7)
/* Defines for AIN2: GPIOB.24 with pinCMx 52 on package pin 42 */
#define MOTOR_AIN2_PORT                                                  (GPIOB)
#define MOTOR_AIN2_PIN                                          (DL_GPIO_PIN_24)
#define MOTOR_AIN2_IOMUX                                         (IOMUX_PINCM52)
/* Defines for BIN1: GPIOB.20 with pinCMx 48 on package pin 41 */
#define MOTOR_BIN1_PORT                                                  (GPIOB)
#define MOTOR_BIN1_PIN                                          (DL_GPIO_PIN_20)
#define MOTOR_BIN1_IOMUX                                         (IOMUX_PINCM48)
/* Defines for BIN2: GPIOB.19 with pinCMx 45 on package pin 38 */
#define MOTOR_BIN2_PORT                                                  (GPIOB)
#define MOTOR_BIN2_PIN                                          (DL_GPIO_PIN_19)
#define MOTOR_BIN2_IOMUX                                         (IOMUX_PINCM45)
/* Port definition for Pin Group IIC */
#define IIC_PORT                                                         (GPIOA)

/* Defines for SCL: GPIOA.0 with pinCMx 1 on package pin 1 */
#define IIC_SCL_PIN                                              (DL_GPIO_PIN_0)
#define IIC_SCL_IOMUX                                             (IOMUX_PINCM1)
/* Defines for SDA: GPIOA.1 with pinCMx 2 on package pin 2 */
#define IIC_SDA_PIN                                              (DL_GPIO_PIN_1)
#define IIC_SDA_IOMUX                                             (IOMUX_PINCM2)
/* Defines for S1: GPIOA.25 with pinCMx 55 on package pin 45 */
#define TRACK_S1_PORT                                                    (GPIOA)
#define TRACK_S1_PIN                                            (DL_GPIO_PIN_25)
#define TRACK_S1_IOMUX                                           (IOMUX_PINCM55)
/* Defines for S2: GPIOA.24 with pinCMx 54 on package pin 44 */
#define TRACK_S2_PORT                                                    (GPIOA)
#define TRACK_S2_PIN                                            (DL_GPIO_PIN_24)
#define TRACK_S2_IOMUX                                           (IOMUX_PINCM54)
/* Defines for S3: GPIOA.23 with pinCMx 53 on package pin 43 */
#define TRACK_S3_PORT                                                    (GPIOA)
#define TRACK_S3_PIN                                            (DL_GPIO_PIN_23)
#define TRACK_S3_IOMUX                                           (IOMUX_PINCM53)
/* Defines for S4: GPIOA.22 with pinCMx 47 on package pin 40 */
#define TRACK_S4_PORT                                                    (GPIOA)
#define TRACK_S4_PIN                                            (DL_GPIO_PIN_22)
#define TRACK_S4_IOMUX                                           (IOMUX_PINCM47)
/* Defines for S5: GPIOA.21 with pinCMx 46 on package pin 39 */
#define TRACK_S5_PORT                                                    (GPIOA)
#define TRACK_S5_PIN                                            (DL_GPIO_PIN_21)
#define TRACK_S5_IOMUX                                           (IOMUX_PINCM46)
/* Defines for S6: GPIOB.9 with pinCMx 26 on package pin 23 */
#define TRACK_S6_PORT                                                    (GPIOB)
#define TRACK_S6_PIN                                             (DL_GPIO_PIN_9)
#define TRACK_S6_IOMUX                                           (IOMUX_PINCM26)
/* Defines for S7: GPIOA.17 with pinCMx 39 on package pin 32 */
#define TRACK_S7_PORT                                                    (GPIOA)
#define TRACK_S7_PIN                                            (DL_GPIO_PIN_17)
#define TRACK_S7_IOMUX                                           (IOMUX_PINCM39)
/* Defines for S8: GPIOA.16 with pinCMx 38 on package pin 31 */
#define TRACK_S8_PORT                                                    (GPIOA)
#define TRACK_S8_PIN                                            (DL_GPIO_PIN_16)
#define TRACK_S8_IOMUX                                           (IOMUX_PINCM38)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_MOTOR_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_UART_DEBUG_init(void);
void SYSCFG_DL_UART_GYRO_init(void);
void SYSCFG_DL_DMA_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
