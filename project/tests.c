#include <stdio.h>
#include <stdlib.h>

#include "./functions/messages/__tests__/dataHandler.test.h"
#include "./functions/messages/__tests__/convert.test.h"
#include "./functions/messages/__tests__/parse.test.h"
#include "./functions/__tests__/controllers.test.h"
#include "./functions/__tests__/rooms.test.h"
#include "./functions/__tests__/weather.test.h"
#include "./functions/__tests__/aquarium.test.h"
int main(void) {
printf("%-40s %10s\n", "test_convert_to_MSG1",
        test_convert_to_MSG1() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_convert_to_MSG2",
        test_convert_to_MSG2() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_convert_to_MSG3",
        test_convert_to_MSG3() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_parse_MSG1",
        test_parse_MSG1() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_parse_MSG2",
        test_parse_MSG2() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_parse_MSG3",
        test_parse_MSG3() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_temperatureControlModel",
        test_temperatureControlModel() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_phControlModel",
        test_phControlModel() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_roomTemperatureModel",
        test_roomTemperatureModel() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_roomLuminosityModel",
        test_roomLuminosityModel() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_noisySinusoid",
        test_noisySinusoid() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_updateWeatherTemperature",
        test_updateWeatherTemperature() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_line",
        test_line() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_setTwilightLuminosity",
        test_setTwilightLuminosity() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_luminosityModel",
        test_luminosityModel() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
printf("%-40s %10s\n", "test_phModel",
        test_phModel() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
  return EXIT_SUCCESS;
}
