typedef enum {TMODE_NORMAL, TMODE_CTC} eTIMERMODE;
typedef int ePRESCALER;

void init_Timer0(eTIMERMODE mode);

void start_Timer0(ePRESCALER prescaler);

void stop_Timer0();

void clear_Timer0();

void wait_Timer0(eTIMERMODE mode);

void setOCRval_Timer0(unsigned char ocrval);
