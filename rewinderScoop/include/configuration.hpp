#define ENCODER_OPTIMIZE_INTERRUPTS

/*
*   Job and speed configuration
*/
#define RUN_SPEED_1_DEFAULT (100)
#define RUN_SPEED_2_DEFAULT (35)

// The percent of a custom run that should be fast. 1-X is then slow.
#define CUSTOM_PERCENT_FAST            (.75)
#define CUSTOM_DISTANCE_MIN            (10)
#define CUSTOM_DISTANCE_MIN            (999)
#define CUSTOM_KNOB_RESOLUTION         (14) // reduce this to have less fine control of knob. Max val on this hw is 14b

// replace CREATE_JOB with CREATE_JOB_FULL_INIT if you need to control speed.

#define JOB_0  CREATE_JOB(40, 10)
#define JOB_1  CREATE_JOB(85, 15)
#define JOB_2  CREATE_JOB(100, 20)
#define JOB_3  CREATE_JOB(280, 20)
#define JOB_4  CREATE_JOB(340, 20)
// currently unneeded jobs that can be added later
#define JOB_5  CREATE_JOB(150, 15)
#define JOB_6  CREATE_JOB(160, 16)
#define JOB_7  CREATE_JOB(170, 17)
#define JOB_8  CREATE_JOB(180, 18)
#define JOB_9  CREATE_JOB(190, 19)

// Job 10 is the custom job
#define JOB_10 CREATE_JOB(200, 20)


/*
* Encoder parameters
*/
#define ENCODER_ERROR_DEBOUNCE_MS            (1000)
/*
* Current encoder has a 300mm circumference. There are 200 pulses per revolution (PPR)
*/
#define ENCODER_CIRCUMFERENCE_MM ((float)300)
#define UNIT_MM_PER_INCHES ((float)0.0393701)
#define ENCODER_PULSES_PER_REVOLUTION ((float)200)
//#define ENCODER_SCALE_VALUE_INCHES_PER_TICK  ((float)((ENCODER_PULSES_PER_REVOLUTION/ENCODER_CIRCUMFERENCE_MM)/4))
#define ENCODER_SCALE_VALUE_INCHES_PER_TICK ((float) 1/1.5/2)

#define ENCODER_Z_COUNT_SCALE ((float)1/300)
#define ENCODER_Z_TIME_OUT_MS  (5000)

/*
*  Board configuration
*/

#define ENABLE_DEBUG (1)

// TX                  (D0)
// RX                  (D1)

#define PIN_LED_RED    (D6)
#define PIN_LED_YELLOW (D7)
#define PIN_LED_GREEN  (D4)

#define PIN_START_BUTTON (D5)

#define PIN_ENCODER_A  (D2)
#define PIN_ENCODER_B  (D3)
#define PIN_ENCODER_Z  (D8)

#define PIN_MOTOR      (D9)

//#define PIN_BUTTON_2   (D10)

#define PIN_KNOB_A     (D11)
#define PIN_KNOB_B     (D12)
#define PIN_KNOB_C     (D13)
#define PIN_KNOB_D     (D15)

#define PIN_DIAL       (D14)

// currently unsed D16 -> 17

#define PIN_D16        (D16)
#define PIN_D17        (D17)

#define PIN_I2C_SCL    (D18)
#define PIN_I2C_SCA    (D19)





