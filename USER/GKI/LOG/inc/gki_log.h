#ifndef _GKI_LOG_H_
#define _GKI_LOG_H_



typedef enum {
	LOG_BY_LCD, 
	LOG_BY_WIN
} LOG_TYPE_ENUM;
    
void log_print(const char * s, int level, LOG_TYPE_ENUM log_type);

#endif
