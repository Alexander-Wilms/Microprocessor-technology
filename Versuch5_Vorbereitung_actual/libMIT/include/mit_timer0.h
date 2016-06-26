/**
 * Funktionen Timer0 (Versuch 4)
 *
 * \package TIM0
 * \author H. Frank - FBEIT -h_da
 * \copyright 2012 by FB EIT - h_da
 */

#ifndef VERSUCH4_H_
#define VERSUCH4_H_

#include <avr/io.h>
#ifndef F_CPU
/**
 * Systemfrequenz [Hz]
 */
#define F_CPU 	4000000UL
#endif

// Enums

/**
 * Betriebsarten von Timer 0
 *
 * - \b Normal : Zähler läuft bis Maximum (255) und beginnt dann wieder bei 0
 * - \b CTC : Zähler läuft bis Wert in Output Compare Register (OCR) erreicht und beginnt dann wieder bei 0
 *
 * s. <a href="https://lernen.h-da.de/pluginfile.php/35823/mod_folder/content/0/Datenbl%C3%A4tter/ATMEGA128_complete.pdf?forcedownload=1" target="_blank">Handbuch atMega128</a> S. 95 ff.
 * s. <a href="https://lernen.h-da.de/pluginfile.php/35823/mod_folder/content/0/Datenbl%C3%A4tter/ATMEGA32%20complete.pdf?forcedownload=1" target="_blank">Handbuch atMega32</a> S. 73 ff.
 */
typedef enum MIT_TIMERMODE{MIT_TMODE_NORMAL=0, MIT_TMODE_CTC} MIT_eTIMERMODE;

#if defined (__AVR_ATmega128__)

/**
 * Werte für Vorteiler Timer 0
 *
 * s. <a href="https://lernen.h-da.de/pluginfile.php/35823/mod_folder/content/0/Datenbl%C3%A4tter/ATMEGA128_complete.pdf?forcedownload=1" target="_blank">Handbuch atMega128</a> S. 103
 */
typedef enum MIT_PRESCALER{MIT_PRESC1=1, MIT_PRESC8, MIT_PRESC32, MIT_PRESC64, MIT_PRESC128, MIT_PRESC256, MIT_PRESC1024} MIT_ePRESCALER;
#else
/**
 * Werte für Vorteiler Timer 0
 *
 * s. <a href="https://lernen.h-da.de/pluginfile.php/35823/mod_folder/content/0/Datenbl%C3%A4tter/ATMEGA32%20complete.pdf?forcedownload=1" target="_blank">Handbuch atMega32</a> S. 82
 */
typedef enum MIT_PRESCALER{MIT_PRESC1=1, MIT_PRESC8, MIT_PRESC64, MIT_PRESC256, MIT_PRESC1024} MIT_ePRESCALER;
#endif

// Globals
/**
 * zählt Anzahl der Überläufe von Timer 0 (in ISR)
 */
extern unsigned int MIT_gOVLcomp;
/**
 * für die 4 Bitmuster der 7-Segmentanzeige
 * - 0: 1-er
 * - 1: 10-er
 * - 2: 100-er
 * - 3: 1000-er
 */
extern unsigned char MIT_gData[4];
/**
 * Vergleichswert für die High-Zeit der Steuersignale der 7-Segmentanzeige
 */
extern unsigned char MIT_gOcrHI;


// Prototypes

/**
 * Initialisiert Timer 0
 *
 * Setzt den Betriebsmode von Timer 0
 *
 * \see MIT_eTIMERMODE
 *
 * \param[in] tmode Betriebsmode des Timers (NORMAL/CTC)
 */
void MIT_init_Timer0(MIT_eTIMERMODE tmode);

/**
 * Initalisiert Timer 0 mit MIT_init_Timer0()
 * und aktiverit entsprechenden Interrupt (OCR oder OVL)
 *
 * \see MIT_eTIMERMODE
 *
 * Globales Interruptflag muss noch mit sei() gesetzt werden.
 *
 * \param[in] tmode Betriebsmode des Timers (NORMAL/CTC)
 */
void MIT_init_Timer0_INT(MIT_eTIMERMODE tmode);

/**
 * Startet Timer 0 durch setzen eines Prescalerwertes <> 0
 *
 * \see MIT_ePRESCALER
 *
 * \param[in] prescaler Wert für den Prescaler
 */
void MIT_start_Timer0(MIT_ePRESCALER prescaler);

/**
 * Stoppt Timer 0
 *
 * durch löschen des Prescalerwertes
 */
void MIT_stop_Timer0();

/**
 * Setzt Timer 0 auf Zählerwert 0 zurück
 *
 * kann bei laufendem Timer aufgerufen werden. Der Timer wird nicht angehalten.
 */
void MIT_clear_Timer0();

/**
 * Setzt das Vergleichsregister für den CTC Modus von Timer 0
 *
 * \param[in] ocrval Wert für das Vergleichsregister (max. 255)
 */
void MIT_setOCRval_Timer0(unsigned char ocrval);

/**
 * Wartet abhängig von tmode bis das jeweilge Timerereignis eingetreten ist
 *
 * - TMODE_NORMAL : Überlauf
 * - TMODE_CTC : Wert von OCR erreicht
 *
 * Das Verhalten von dieser Funktion hängt nur vom Parameter tmode ab und nicht davon,
 * in welchem Modus der Timer gestartet wurde. Läuft der Timer im Normalmodus,
 * kann hier trotzdem mit tmode = TMODE_CTC auf das Erreichen des OCR-Wertes gewartet werden.
 *
 * <b>ACHTUNG !!!!</b> Wurde der Timer im CTC-Modus gestartet, führt ein Warten auf den Überlauf zu einer Endlosschleife,
 * da dieser Wert nie erreicht wird.
 *
 * \param[in] tmode Ereignis, auf das gewartet werden soll.
 */
void MIT_wait_Timer0(MIT_eTIMERMODE tmode);

#endif /* VERSUCH4_H_ */
