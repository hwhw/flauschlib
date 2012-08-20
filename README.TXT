Bibliothek mit Routinen für das Flauschball-Projekt - oder für PIC32-Anwendungen allgemein

Bestandteile:
-------------
halbwegs fertig:

- profile_config.h:
  Konfiguration für die flauschlib
  Derzeit eingerichtet für das Pinguino-MX220-Developer-Board von Olimex

- fifo.c/.h:
  implementiert einen Byte-FIFO im RAM
  ohne Überlaufcheck, das wäre noch zu implementieren
  bisher nur Single-Byte-Push/Pop, könnte erweitert werden

- uart.c/.h:
  Routinen für UART-Eingabe/Ausgabe
  Interruptfähig für das Senden (zum Senden größerer Datenhäppchen)

- systick.c/.h:
  Verwendet TIMER3 zur Einrichtung eines Systicks (alle 100usec) mit hoher Interrupt-Priorität
  Zähler systick läuft über.
  Inklusive Funktion für das Warten für eine bestimmte Zahl an 100usec-Ticks
  (delay100usec())

in Arbeit:

- spi.c/.h:
  Routinen für die SPI-Kommunikation, noch nicht vollständig
- diskio.c/.h:
  portierter Teil aus dem FsFAT-Modul, noch nicht funktionstüchtig


