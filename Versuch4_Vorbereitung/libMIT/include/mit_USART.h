/**
 * Funktionen serielle Schnittstellen (Versuch 3)
 *
 * \package USART
 * \author H. Frank - FB EIT - h_da
 * \copyright 2012 by FB EIT - h_da
 */

#ifndef VERSUCH3_H_
#define VERSUCH3_H_
#include <stdarg.h>
#include "mit_adc.h"
#include "mit_parallel_io.h"

/**
 *	zulässige Baudraten
 *
 *	Der Bereich der möglichen Baudraten hängt von der Taktfrequenz des Controllers ab
 *	und von der Einstellung des Bits U2X, das entscheidet ob noch ein 2:1 Vorteiler
 *	vor den Baudratengenerator geschaltet wird.
 *
 *	Die hier angegebenen Baudraten im Bereich von 2400 bis 19200 funktionieren bei allen
 *	möglichen Taktfrequenzen (1 - 16 MHz)
 */
typedef enum MIT_BAUDRATE{
	MIT_BAUDRATE2400=2400,
	MIT_BAUDRATE4800=4800,
	MIT_BAUDRATE9600=9600,
	MIT_BAUDRATE19200=19200
} MIT_eBAUDRATE;

/**
 *	Parityprüfung (keine, gerade Anzahl, ungerade Anzahl)
 */
typedef enum MIT_PARITY {MIT_PARITYNONE=0,MIT_PARITYEVEN=2,MIT_PARITYODD=3} MIT_ePARITY;

/**
 *	Anzahl der Stopbits
 */
typedef enum MIT_STOP {MIT_STOP1=0,MIT_STOP2} MIT_eSTOP;

/**
 *	Anzahl der Datenbits
 */
typedef enum MIT_CHARSIZE{
	MIT_CHARSIZE5,
	MIT_CHARSIZE6,
	MIT_CHARSIZE7,
	MIT_CHARSIZE8
} MIT_eCHARSIZE;



// Prototypes

/**
 * Initalisiert eine serielle Schnittstelle fuer asynchronen Betrieb mit folgende Parametern
 *
 * - Baudrate
 * - Anzahl Datenbits
 * - Anzahl Stopbits
 * - Parity NONE/ODD/EVEN
 *
 * Bit U2X wird immer auf 0 gesetzt (keine Frequenzverdopplung).
 *
 * Es wird die Schnittstelle initialisiert, die in usart_no angegeben wird,
 * die vorher aktive Schnittstelle wird deaktiviert.
 *
 * Alle anderen Funktionen von libMIT verwenden dann die aktive Schnittstelle.
 *
 * Um während des Betriebs die Schnittstelle zu wechseln muss MIT_init_USART
 * mit einem anderen Wert für usart_no aufgerufen werden.
 *
 * \param[in] usart_no Nummer der USART Schnittstelle
 * \param[in] fcpu Systemfrequenz in Hz
 * \param[in] baudrate Baudrate
 * \param[in] charsize Anzahl Datenbits (5,6,7 oder 8)
 * \param[in] parity Parityprüfung (keine, gerade, ungerade)
 * \param[in] stop Anzahl Stopbits (1 oder 2)
 */
void MIT_init_USART(uint8_t usart_no, unsigned long fcpu, MIT_eBAUDRATE baudrate, MIT_eCHARSIZE charsize, MIT_ePARITY parity, MIT_eSTOP stop);
//void MIT_init_USART(unsigned long fcpu, MIT_eBAUDRATE baudrate, MIT_eCHARSIZE charsize, MIT_ePARITY parity, MIT_eSTOP stop, ...);

/**
 * Wartet, bis das Senderegister leer ist und versendet dann ein
 * Zeichen über die serielle Schnittstelle
 *
 * @param[in] sendchar zu sendendes Zeichen
 */
void MIT_putc_USART(unsigned char sendchar);

/**
 * Wartet solange bis ein Byte (ASCII-Zeichen) über serielle Schnittstelle 0 empfangen wurde (Polling)
 * und liefert es an das aufrufende Programm zurück.
 *
 * @return empfangenes Zeichen
 */
unsigned char MIT_getc_USART(void);

/**
 * Schaut nach, ob ein Byte (ASCII-Zeichen) über USART1 empfangen wurde
 * und kehrt sofort zurück falls das nicht der Fall ist.
 *
 * Falls kein empfangenes Zeichen bereitsteht wird 0xff zurueckgegeben.
 *
 * @return empfangenes Zeichen
 */
unsigned char MIT_lookc_USART(void);

/**
 * noch nicht implementiert
 * @param
 */
void MIT_putb2a_USART(unsigned char *);

/**
 * Gibt einen NULL-terminierten String auf der seriellen Schnittstelle aus
 *
 * @param[in] pMsg Zeiger auf Anfangsadresse String
 */
void MIT_puts_USART(unsigned char*);

/**
 * wandelt ein ASCII Zahlzeichen (0 - 9) in seinen numerischen Wert um
 *
 * @param[in] ascii ASCII Code des Zahlzeichens
 * @return Dezimalwert des ASCII Zeichens
 */
unsigned char MIT_ascii2num(unsigned char ascii);

/**
 * Wandelt einen numerischen Wert (0 - 9) in sein ASCII-Zahlzeichen um
 *
 * @param[in] numVal Numerischer Wert
 * @return ASCII Code des Zahlzeichens
 */
unsigned char MIT_num2ascii(unsigned char numVal);

/**
 * rechnet einen digitalen Messwert in einen Spannungswert in V um
 * und zeigt diesen mit je einer Stelle vor und nach dem Komma auf dem
 * Serial Terminal des PC an. Jeder Messwert soll in einer Zeile dargestellt werden, z.B.:
 *
 *     \c 0.2V
 *
 *     \c 1.7V
 *
 * u.s.w.
 *
 * \param[in] value binäres Wandelergebnis
 * \param[in] res Auflösung des Messwerts
 * \param[in] uref Referenzspannung des ADC in Volt
 */
void MIT_displayVoltage_PC(unsigned long value, MIT_eADCRES res, float uref);

#endif /* VERSUCH3_H_ */
