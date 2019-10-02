# Sodaq-Autonomo-to-Emoncms
Utilizzare la scheda Autonomo (Sodaq) per inviare dati al server EmonCMS.

Hardware:
  1. Sodaq Autonomo
    + Grove shield + TPH sensor
    + batteria e panello solare
    + WiFiBee
  2. Raspberry Pi 2 Model B (+ SD 8 GB)
    + emonPi (pcb only)
La mia configurazione:
  1. Sodaq Autonomo connesso in wifi
    + Il sensore di temperatura va collegato alla porta SDA/SCL
    + Lo switch del WifiBee va impostato su RUN. 
  2. RaspberryPi connesso in ethernet
  
Software:
  1. Arduino IDE per programmare e caricare il codice sulla scheda Autonomo
  2. Emoncms su SD installata sul RaspberryPi
  3. la variabile di compilazione TEST serve per abilitare/disabilitare l'utilizzo della porta seriale a scopo di test e ridurre il peso dello sketch nella versione di produzione
  4. Per tutte le stringhe "statiche" utilizzo la funzione F() per ridurre l'utilizzo della memoria
  
TODO:
  1. Ridurre il consumo della scheda nei tempi di inutilizzo (watchdog)
  2. Aumentare il tempo di attesa per l'invio dei dati
  3. Contare il numero di tentativi falliti di connessione al server e riavviare la scheda per risolvere problemi di memoria
  4. In caso di connessione fallita salvare i dati sulla SD ed inviarli alla prima riconnessione

Link esterni:
Arduino: https://www.arduino.cc/
Sodaq-Autonomo: https://support.sodaq.com/Boards/Autonomo/
OpenEnergyMonitor (Emoncms): https://openenergymonitor.org/
