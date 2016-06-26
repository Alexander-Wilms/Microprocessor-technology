/**
 * AD Wandler (Versuch 2)
 *
 * \package ADC
 * \author H. Frank - FB EIT - h_da
 * \copyright 2012 by FB EIT - h_da
 */

#ifndef VERSUCH2_H_
#define VERSUCH2_H_
#include <avr/io.h>

/**
 *  Spannungsreferenz für den AD Wandler
 *
 *  Zur Skalierung der digitalen Messwerte des AD-Wandlers in Spannungswerte mit den Funktionen MIT_ushort2Volt() und MIT_ushort2VoltInt(),
 *  muss der Wert für die Referenzspannung des Wandlers bekannt sein.
 *
 *  Die Referenzspannung ist von der Hardware- und Softwarekonfiguration des STK500/501 abhängig.
 *  Sie muss vor Einsatz eines Systems immer neu überprüft und ggf. eingestellt werden.
 *
 *	Der Wert für das jeweilige eingesetzte System muss in der Konstanten UREFV in Volt als Dezimalzahl angegeben werden
 *	(z.B. 5. oder 5.0 für 5 Volt) und kann dann in der Anwendung an MIT_ushort2Volt() als Parameter übergeben werden.
 *
 *	MIT_ushort2VoltInt() benötigt einen Integerwert in mV. Dieser wird in Abhängigkeit von UREFV berechnet und in UREFMV
 *	zur Verfügung gestellt.
 *
 *  UREFV muss vor Inklusion von \c libMIT.h bzw. \c mit_adc.h festgelegt werden, sonst wird UREFMV nicht korrekt berechnet.
 *  Wenn der Wert nicht von der Anwendung gesetzt wird, wird eine Warnung ausgegeben und der Wert auf 5V gesetzt.
 *
 *	\see MIT_ADCVREF
 */

/*
 * Der Klimmzug mit UREFWARN ist nötig, da ansonsten die Warnung in Eclipse immer ausgegeben wird,
 * egal ob UREFV bereits definiert ist oder nicht.
 */
#ifndef UREFV
#define UREFV 5.0
#define UREFWARN
#endif

#ifdef UREFWARN
#warning "UREFV not set by application; set to default value 5V"
#endif
# define UREFMV UREFV*1000

/**
 * Ergebnis der Wandlung bei interruptgesteuertem ADC
 */
extern unsigned short MIT_gADCres;

/**
 * Auflösung des AD-Wandlers
 *
 * Es werden immer 10 Bit gewandelt. Bei \c MIT_BIT8 werden die beiden niederwertigsten Bits (0 und 1) nicht berücksichtigt
 */
typedef enum MIT_ADCRES{MIT_BIT10=0, MIT_BIT8} MIT_eADCRES;

/**
 * Art der Messung
 *
 * Free Run: Der Wandler startet eine neue Messung, sobald die vorherige Messung abgeschlossen ist.
 *
 * Single Shot: Jede Wandlung muß durch Setzen des ADSC-Bits in ADCSRA
 * mit Aufruf von \c MIT_start_ADC()) gestartet werden
 */
typedef enum MIT_ADCRUNMODE{MIT_FREERUN=0, MIT_SINGLESHOT} MIT_eADCRUNMODE;

/**
 * Prescaler für Wandlungsfrequenz
 *
 * Teilt die Systemfrequenz um den angegebenen Faktor; Ergibt Wandlungsclock
 * Die eigentliche Abtastrate ist nochmal um den Faktor 13 niedriger, da
 * für eine vollständige Wandlung 13 Clocks benötigt werden.
 *
 * Wird MIT_ADCPRESC1 angegeben, so erhält man ebenfalls einen Prescalerwert von 2.
 */
typedef enum MIT_ADCPRESC {	MIT_ADCPRESC1,
							MIT_ADCPRESC2,
							MIT_ADCPRESC4,
							MIT_ADCPRESC8,
							MIT_ADCPRESC16,
							MIT_ADCPRESC32,
							MIT_ADCPRESC64,
							MIT_ADCPRESC128} MIT_eADCPRESC;

/**
 * Ausrichtung des 10 Bit Wandelergebnisses im 16-Bit Wort (Links-/Rechtsbündig)
 */
typedef enum MIT_ADCALIGN {MIT_ADCRIGHT,MIT_ADCLEFT} MIT_eADCALIGN;

/**
 * Quelle der Spannungsreferenz <i>(ist auch von Konfiguration des STK500 abhängig.)</i>
 *
 * - \b AREF: von AREF-Pin; Bei gesetztem Jumper AREF auf dem STK500, wird die Referenzspannung vom STK500 erzeugt und an AREF angelegt.
 * Die Höhe der Referenzspannung kann nur mit dem AVRSTudio eingestellt werden, nicht mit Eclipse. Ist der Jumper nicht gesetzt,
 * muß die Referenzspannung über PORTE Pin 5 zugeführt werden. Sie darf nicht über der Versorgungsspannung liegen.
 * - \b AVCC: als Referenzspannung wird die Versorgungsspannung verwendet. An AREF muß ein Kondensator angeschlossen werden
 * - \b INTERN: interne Referenzspannung mit Kondensator an AREF
 *
 * \warning Wenn eine externe Referenzspannungsquelle an AREF angeschlossen ist, dürfen die Modi \b AVCC und \b INTERN nicht verwendet werden,
 * da sonst der AREF-Pin über die externe Quelle kurzgeschlossen wird.
 *
 * Überprüfung der eingestellten Spannung vom STK500:
 * - AVR Studio 4 öffnen
 * - Tools - Program AVR - Auto Connect
 * - HW Settings
 */
typedef enum MIT_ADCVREF {MIT_AREF,MIT_AVCC,MIT_INTERN=3} MIT_eADCVREF;

/**
 * Kanalauswahl, Symmetrie, Verstärkung
 *
 *
 */
typedef enum MIT_ADCCHAN {	MIT_ADC_CHN0SNGL,
							MIT_ADC_CHN1SNGL,
							MIT_ADC_CHN2SNGL,
							MIT_ADC_CHN3SNGL,
							MIT_ADC_CHN4SNGL,
							MIT_ADC_CHN5SNGL,
							MIT_ADC_CHN6SNGL,
							MIT_ADC_CHN7SNGL} MIT_eADCCHAN;

/**
 * Initialisiert den ADC
 *
 * \param[in] ref Quelle Referenzspannung
 * \param[in] channel Kanal, Symmetrie, Verstärkung
 * \param[in] align Ausrichtung Messergebnis in Ergebnisregister
 * \param[in] presc Wert für Prescaler
 */
void MIT_init_ADC(MIT_eADCVREF ref,MIT_eADCCHAN channel,MIT_eADCALIGN align,MIT_eADCPRESC presc);

/**
 * Initialisiert den ADC im Interrupt-Modus, verwendet init_ADC() zur Initialisierung
 *
 * \param[in] ref Quelle Referenzspannung
 * \param[in] channel Kanal, Symmetrie, Verstärkung
 * \param[in] align Ausrichtung Messergebnis in Ergebnisregister
 * \param[in] presc Wert für Prescaler
 */
void MIT_init_ADC_INT(MIT_eADCVREF ref,MIT_eADCCHAN channel,MIT_eADCALIGN align,MIT_eADCPRESC presc);

/**
 * Startet den ADC in folgenden Modi:
 *
 * - MIT_FREERUN: fortlaufende Messung nach Start des ADC
 * - MIT_SINGLESHOT: einmalige Messung nach Start
 *
 * \see MIT_eADCRUNMODE
 * \param[in] mode Art der Messung
 */
void MIT_start_ADC(MIT_eADCRUNMODE mode);

/**
 * stoppt den ADC
 */
void MIT_stop_ADC();

/**
 * wartet auf das Ende einer Messung (Polling)
 */
void MIT_wait_ADC();


/**
 * liefert ein Messergebnis (binär) mit 8 oder 10 Bit Auflösung aus
 *
 * \param[in] res Auflösung
 * \return 16-Bit-Wert mit Messergebnis in der gewählten Auflösung
 */
unsigned short MIT_read_ADC(MIT_eADCRES res);

/**
 * rechnet ein binäres Wandlungsergebnis in einen Spannungswert um
 *
 * \param[in] value binäres Wandlungsergebnis
 * \param[in] res Auflösung des Wandlungsergebnisses
 * \param[in] uref Spannungsreferenzwert des ADC in V (entspricht Spannung bei maximalem Messwert)
 * \return Spannungswert in V
 */
float MIT_ushort2Volt(unsigned short value, MIT_eADCRES res, float uref);

/**
 * rechnet ein binäres Wandlungsergebnis in einen 4-stelligen Spannungswert in mV um
 *
 * Schneller als MIT_ushort2Volt(), da die aufwändige float-Arithmetik nicht benötigt wird
 *
 * \param[in] value binäres Wandlungsergebnis
 * \param[in] res Auflösung des Wandlungsergebnisses
 * \param[in] uref Spannungsreferenz des ADC in mV (entspricht Spannung bei maximalem Messwert)
 * \return Spannungswert in mV (0 ... 5000 bei 5V Spannungsreferenz)
 */
unsigned int MIT_ushort2VoltInt(unsigned short value, MIT_eADCRES res, unsigned int uref);


#endif /* VERSUCH2_H_ */
