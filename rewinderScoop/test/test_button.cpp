#include <unity.h>
#include "button.hpp"


#define BUTTON_TEST_PIN (1)

button_t testButtonObj = BUTTON_INIT(BUTTON_TEST_PIN);
button_t * testButton = &testButtonObj;

void setUp(void) {
    // set stuff up here
    button__init(testButton);
}

void tearDown(void) {
    // clean stuff up here
}


void test_10ms_debounce()
{
    for (uint32_t i = 0; i < 9; i++)
    {
        button__update(testButton);
        TEST_ASSERT_FALSE(button__getStatus(testButton));
    }

    TEST_ASSERT_TRUE(button__update(testButton));
    TEST_ASSERT_TRUE(button__getStatus(testButton));

}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_10ms_debounce);
    UNITY_END();
}