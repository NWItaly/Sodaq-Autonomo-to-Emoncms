# Sodaq-Autonomo-to-Emoncms
Utilizzare la scheda Autonomo (Sodaq) per inviare dati al server EmonCMS.

Hardware:
  1. Sodaq Autonomo
    + Grove shield + TPH sensor
    + batteria e panello solare
    + WiFiBee
  2. Raspberry Pi 2 Model B (+ SD 8 GB)
    + emonPi (pcb only)
Software:
  1. Arduino per programmare e caricare il codice sulla scheda Autonomo
  2. Emoncms su SD installata sul RaspberryPi

La mia configurazione:
  1. Sodaq Autonomo connesso in wifi
    + Il sensore di temperatura va collegato alla porta SDA/SCL
    + Lo switch del WifiBee va impostato su RUN. 
  2. RaspberryPi connesso in ethernet
  
TODO:
  1. Ridurre il consumo della scheda nei tempi di inutilizzo (watchdog)
  2. Aumentare il tempo di attesa per l'invio dei dati
  3. In caso di connessione fallita salvare i dati sulla SD ed inviarli alla prima riconnessione

Link esterni:
Arduino: https://www.arduino.cc/
Sodaq-Autonomo: https://support.sodaq.com/Boards/Autonomo/
OpenEnergyMonitor (Emoncms): https://openenergymonitor.org/
