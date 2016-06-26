
typedef enum {TMODE_NORMAL, TMODE_CTC} eTIMERMODE;
typedef enum PRESCALER{PRESC1=1, PRESC8, PRESC32, PRESC64, PRESC128, PRESC256, PRESC1024=0b111} ePRESCALER;

void init_Timer0(eTIMERMODE mode);

void start_Timer0(ePRESCALER prescaler);

void stop_Timer0();

void clear_Timer0();

void wait_Timer0(eTIMERMODE mode);

void setOCRval_Timer0(unsigned char ocrval);
