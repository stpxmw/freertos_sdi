#include "gki_log.h"
#include "lcd.h"


void log_print(const char * s, int level, LOG_TYPE_ENUM log_type)
{
    LCD_Init();
    LCD_DisplayOn();
    printf("just test");
}





























