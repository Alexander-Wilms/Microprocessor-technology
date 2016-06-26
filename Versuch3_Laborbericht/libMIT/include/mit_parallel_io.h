/**
 * Funktionen LEDs- und Tastenansteuerung (Versuch 1)
 *
 * \package PIO
 * \author H. Frank - FBEIT -h_da
 * \copyright 2012 by FB EIT - h_da
 */

#ifndef VERSUCH1_H_
#define VERSUCH1_H_

#include <avr/io.h>
#include <util/delay.h>

#if defined (__AVR_ATmega128__)
/**
 * Portbezeichnungen für Ports von ATmega128
 */
typedef enum MIT_PORT {MIT_PIO_PORTA, MIT_PIO_PORTB, MIT_PIO_PORTC, MIT_PIO_PORTD, MIT_PIO_PORTE, MIT_PIO_PORTF, MIT_PIO_PORTG} MIT_ePORT;
#elif defined (__AVR_ATmega32__)
/**
 * Portbezeichnungen für Ports von ATmega32
 */
typedef enum MIT_PORT {MIT_PIO_PORTA, MIT_PIO_PORTB, MIT_PIO_PORTC, MIT_PIO_PORTD} MIT_ePORT;
#endif
/**
 * Datenrichtung der Ports
 */
typedef enum MIT_PORTDIR {MIT_PIO_OUT, MIT_PIO_IN} MIT_ePORTDIR;


/**
 * initialisiert die IO-Ports für Tasten und LEDs
 *
 * Standardbelegung für die Laborsysteme mit ATmega128
 *
 * - Port A: 8 Bit auf Input, alle Inputs mit Pull-Ups (Tasten)
 * - Port B: 8 Bit auf Output (LEDs)
 *
 * \return keine
*/
void MIT_initPorts_Ain_Bout(void);

/**
 * initialisiert die IO-Ports für Tasten und LEDs
 *
 * Alternative Belegung für die Leihsysteme mit ATmega32,
 * falls der AD Wandler verwendet werden soll, der den kompletten PORTA belegt
 *
 * - Port C: 8 Bit auf Input, alle Inputs mit Pull-Ups (Tasten)
 * - Port B: 8 Bit auf Output (LEDs)
 *
 * \return keine
*/
void MIT_initPorts_Cin_Bout(void);

/**
 * Konfiguriert einen Port komplett als Ein- oder Ausgang
 * \param[in] ePORT Port zum Konfigurieren
 * \param[in] ePORTDIR Richtung (Eingang / Ausgang)
 */
void MIT_initPort(MIT_ePORT port, MIT_ePORTDIR dir);

/**
 * gibt ein Byte auf dem LED-Port aus (LED an: 1, LED aus: 0)
 *
 * \param[in] byte 8-Bit-Wert zum Schalten der LEDs
 * \return keine
*/
void MIT_putByteLED_B(unsigned char byte);

/**
 * gibt ein Byte auf einen Port aus
 * \param[in] byte auszugebender 8-Bit-Wert
 * \param[in] port
 */
void MIT_putByte(unsigned char byte, MIT_ePORT port);

/**
 * wartet bis am Tastaturport eine Taste gedrückt wurde.
 *
 * Der Tastaturport kann frei gewählt werden.
 *
 * \param[in] port Bezeichnung des Tastaturports
 * \return 8-Bit-Wert mit Zustand des Tastaturports A zur Zeit der gedrückten Taste (Bit für gedrückte Taste ist 1, nicht gedrückte Taste 0)
*/
unsigned char MIT_wait4key(MIT_ePORT port);

/**
 * wartet bis am Tastaturport A eine Taste gedrückt wurde
 *
 * \return 8-Bit-Wert mit Zustand des Tastaturports A zur Zeit der gedrückten Taste (Bit für gedrückte Taste ist 1, nicht gedrückte Taste 0)
*/
unsigned char MIT_wait4key_A(void);

/**
 * Prüft den Tastaturport auf Tastendruck ohne auf Tastendruck zu warten.
 *
 * Die Funktion kehrt sofort zum aufrufenden Programm zurück. Der Tastaturport kann frei gewählt werden
 *
 * \param[in] port Bezeichnung des Tastaturports
 * \return Pattern des Tastaturports A (gedrückte Taste = 1) oder 255 wenn keine Taste gedrückt
 */
unsigned char MIT_look4key(MIT_ePORT port);

/**
 * Prüft den Tastaturport A auf Tastendruck ohne auf Tastendruck zu warten
 *
 * Die Funktion kehrt sofort zum aufrufenden Programm zurück
 *
 * \return Pattern des Tastaturports A (gedrückte Taste = 1) oder 255 wenn keine Taste gedrückt
 */
unsigned char MIT_look4key_A(void);

/**
 * Änderungsmodus für Funktion MIT_changeBit()
 *
 * - MIT_TOGGLE - Bit invertieren
 * - MIT_SET - Bit setzen
 * - MIT_CLEAR - Bit löschen
 */
typedef enum MIT_BITCHANGES{MIT_TOGGLE,MIT_SET,MIT_CLEAR} MIT_eBITCHANGES;

/**
 * Ändert ein Bit in einem Byte ohne die restlichen Bits zu beeinflussen.
 *
 * \param[in] byte Byte, in dem ein Bit geändert werden soll
 * \param[in] bitNr Nummer des Bits (MSB 7 ... LSB 0)
 * \param[in] how Art der Änderung
 * - MIT_TOGGLE : umschalten
 * - MIT_SET    : auf 1 setzen
 * - MIT_CLEAR  : auf 0 setzen
 * \return geändertes Byte
*/
unsigned char MIT_changeBit(unsigned char byte, unsigned char bitNr, MIT_eBITCHANGES how);

/**
 * ermittelt aus dem Status des Tastaturports die Nummer der gedrückten Taste
 *
 * \param[in] keyPort Bitmuster des Tastaturports bei gedrückter Taste
 * \return Nummer der gedrückten Taste (links 7 ... rechts 0)
*/
unsigned int MIT_getKeyNum(unsigned char keyPort);

/**
 * berechnet die 10er-Potenz eines uebergebenen Exponenten ohne Verwendung der avr-lib
 *
 * \param[in] exp Exponent der 10er-Potenz ( 0 <= exp <= 9 )
 * \return Wert der 10-er Potenz, 0 (false) falls Bereichsüberschreitung von \c exp
*/
unsigned long MIT_power10(unsigned char exp);

/**
 * konvertiert einen ganzzahligen Wert für eine 8-stellige, lineare Balkenanzeige
 *
 * \param[in] value Anzeigewert
 * \param[in] minVal minimaler Wert
 * \param[in] maxVal maximaler Wert
 * \return Bitmuster für LED Balkenanzeige
*/
unsigned char MIT_long2bar(long value, long minVal, long maxVal);

/**
 * niederwertigste Ziffer eines ganzzahligen Wertes als ungepackte BCD-Zahl
 *
 * liefert als Return-Wert die niederwertigste Ziffer einer long-Variablen als
 * ungepackte BCD-Zahl (z. B. 3 beim Eingangswert 123). In der Eingangsvariablen wird der
 * Rest zurückgeliefert (z. B. 12 beim Eingangswert 123)
 *
 * \param[in,out] value Zeiger auf den zu konvertierenden Wert,
 * enthält nach dem Aufruf den noch verbleibenden Rest
 * \return niederwertigste Ziffer als ungepackte BCD-Zahl
*/
unsigned char MIT_ulong2bcd_unpk(long* value);

/**
 * konvertiert einen ganzzahligen Wert in eine zweistellige, gepackte BCD-Zahl
 *
 * Der Wert von value darf maximal 99 betragen.
 *
 * Die höchstwertige Ziffer (10-er Stelle) wird in den höchstwertigen 4 Bit (upper nibble),
 * die niederwertige Ziffer (1-er Stelle) in den niederwertigen 4 Bit (lower nibble) gespeichert
 *
 * \param[in] value zu konvertierender Wert (max. 99)
 * \return gepackte BCD Zahl; 0xff wenn value> 99
*/
unsigned char MIT_ulong2bcd_pk(long value);

/**
 * konvertiert eine Ziffer (0 bis 9) in ein Bitmuster zur Ansteuerung
 * einer 7-Segment-Anzeige mit oder Dezimalpunkt
 * \param[in] num zu konvertierende Ziffer
 * \param[in] dpon Flag, ob Dezimalpunkt an oder aus
 * \return 7-Segment Bit-Muster der Ziffer
*/
unsigned char MIT_num2Seg7(unsigned char num, unsigned char dpon);

#endif /* VERSUCH1_H_ */
