#define ENCODER_OPTIMIZE_INTERRUPTS

/*
*   Job and speed configuration
*/
#define RUN_SPEED_1_DEFAULT (100)
#define RUN_SPEED_2_DEFAULT (35)

// The percent of a custom run that should be fast. 1-X is then slow.
#define CUSTOM_PERCENT_FAST            (.75)
#define CUSTOM_DISTANCE_MIN            (1)
#define CUSTOM_DISTANCE_MAX            (500)
#define CUSTOM_KNOB_RESOLUTION         (14) // reduce this to have less fine control of knob. Max val on this hw is 14b

// replace CREATE_JOB with CREATE_JOB_FULL_INIT if you need to control speed.

#define JOB_0  CREATE_JOB(40, 10)
#define JOB_1  CREATE_JOB(85, 15)
#define JOB_2  CREATE_JOB(100, 20)
#define JOB_3  CREATE_JOB(280, 20)
#define JOB_4  CREATE_JOB(340, 20)
// currently unneeded jobs that can be added later
#define JOB_5  CREATE_JOB(0, 1)
#define JOB_6  CREATE_JOB(0, 2)
#define JOB_7  CREATE_JOB(0, 3)
#define JOB_8  CREATE_JOB(0, 4)
#define JOB_9  CREATE_JOB(0, 5)

// Job 10 is the custom job
#define JOB_10 CREATE_JOB(200, 20)


/*
* Encoder parameters
*/
/*
* Current encoder has a 300mm circumference. There are 200 pulses per revolution (PPR)
*/

#define ENCODER_A_TIME_OUT_MS           (1000)
#define ENCODER_FINISH_TIME_OUT_MS      (1000)
#define ENCODER_SCALE_MULTIPLIER        (5.9)
#define ENCODER_SCALE_DIVIDER           (100)
#define ENCODER_A_PULSES_PER_REVOLUTION (200)


/*
*  Board configuration
*/

#define ENABLE_DEBUG (1)

// TX                       (D0)
// RX                       (D1)
#define PIN_LED_GREEN       (D2)
#define PIN_LED_YELLOW      (D3)
#define PIN_LED_RED         (D4)
#define PIN_START_BUTTON    (D5)
#define PIN_HOLD_BUTTON     (D6)
#define UNUSED_0            (D7)
#define UNUSED_1            (D8)
#define UNUSED_2            (D9)
#define UNUSED_3            (D10)
#define PIN_MOTOR           (D11)
#define PIN_ENCODER_Z       (D12)
#define PIN_ENCODER_A       (D13)

#define PIN_KNOB            (A0)
#define PIN_DIAL            (A2)
#define PIN_SPEED_DIAL      (A1)

#define PIN_D16             (D16)
#define PIN_D17             (D17)
#define PIN_I2C_SCL         (D18)
#define PIN_I2C_SCA         (D19)



