
#define RUN_SPEED_1_DEFAULT (100)
#define RUN_SPEED_2_DEFAULT (35)

#define ENCODER_ERROR_DEBOUNCE_MS (1000)
#define ENCODER_SCALE_VALUE_INCHES_PER_TICK (.01)



#define ENABLE_DEBUG (1)


// replace CREATE_JOB with CREATE_JOB_FULL_INIT if you need to control speed.

#define JOB_0  CREATE_JOB(0, 0)
#define JOB_1  CREATE_JOB(1, 0)
#define JOB_2  CREATE_JOB(2, 0)
#define JOB_3  CREATE_JOB(3, 0)
#define JOB_4  CREATE_JOB(4, 0)
#define JOB_5  CREATE_JOB(5, 0)
#define JOB_6  CREATE_JOB(6, 0)
#define JOB_7  CREATE_JOB(7, 0)
#define JOB_8  CREATE_JOB(8, 0)
#define JOB_9  CREATE_JOB(9, 0)
#define JOB_10 CREATE_JOB(10, 0)
#define JOB_11 CREATE_JOB(11, 0)
#if 0
#define JOB_0  CREATE_JOB(100, 10)
#define JOB_1  CREATE_JOB(110, 11)
#define JOB_2  CREATE_JOB(120, 12)
#define JOB_3  CREATE_JOB(130, 13)
#define JOB_4  CREATE_JOB(140, 14)
#define JOB_5  CREATE_JOB(150, 15)
#define JOB_6  CREATE_JOB(160, 16)
#define JOB_7  CREATE_JOB(170, 17)
#define JOB_8  CREATE_JOB(180, 18)
#define JOB_9  CREATE_JOB(190, 19)
#define JOB_10 CREATE_JOB(200, 20)
#define JOB_11 CREATE_JOB(210, 21)
#endif


#define PIN_BUTTON     (D8)
#define PIN_I2C_SCL    (D1)
#define PIN_I2C_SCA    (D2)
#define PIN_LED_RED    (D0)
#define PIN_LED_YELLOW (D3)
#define PIN_LED_GREEN  (D4)
#define PIN_ENCODER_A  (D6)
#define PIN_ENCODER_B  (D7)
#define PIN_MOTOR      (D5)
#define PIN_KNOB       (A0)