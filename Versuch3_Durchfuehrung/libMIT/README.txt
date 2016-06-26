libMIT - Bibliothek der Funktionen für das MIT-Labor des Fachbereichs EIT an der h_da

1. Verwendung
-------------
Diese Bibliothek enthält die Funktionen, die im Rahmen der Versuche des MIT-Labors von den Studenten
selbst entwickelt werden sollen.
Falls ein Studierender nicht alle bei einem Termin geforderten Funktionen lauffähig machen kann, kann er 
mit der Bibliothek libMIT auf lauffähige Versionen zurückgreifen, um die Aufgaben der nachfolgenden Termine bearbeiten
zu können.




2. Installation
---------------
- zip im Workspace von Eclipse auspacken (Das Anlegen eines Eclipse-Projekts ist NICHT notwendig !!!!!)




3. Inhalt
---------
 - html: 			Die HTML Dokumentation für die Bibliothek
 - include: 	alle h-Files zur Einbindung in die eigenen Projekte
 - libMIT.a		Die Bibliothek
 - README.txt	Diese Datei




4. Einbindung in MIT Projekte
-----------------------------
- neues Projekt erstellen
- in den Projekteigenschaften folgende Einstellungen machen:

- C/C++ General | Paths and Symbols | Includes | Add
	- 'to all configurations' ankreuzen
	- File system -> Pfad zum Verzeichnis 'libMIT/include' angeben



- C/C++ Build | Settings | Tool settings

1.
Die gewünschte Build Konfiguration (Debug/Release) unter "Configuration" auswählen

ACHTUNG !!!!!!!!!
Die Einstellungen für den Linker müssen für alle gewünschten Build Konfigurationen extra eingetragen werden
(üblicherweise Debug und Release). 


2.
jetzt folgende Einstellungen machen unter "AVR C Linker | Libraries"
			- Libraries (-l) | Add
				- MIT eingeben (ohne Suffix und Prefix)
			- Libraries Path (-L) | Add
				- 'File system -> Pfad zum Verzeichnis 'libMIT' angeben
		
		



5. Fragen & Probleme
--------------------
Diese Library wird betreut von Holger Frank, Fachbereich EIT, Hochschule Darmstadt
holger.frank@h-da.de