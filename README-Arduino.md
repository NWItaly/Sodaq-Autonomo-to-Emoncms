Configurare Arduino IDE

Per poter compilare correttamente lo sketch affinchè sia compatibile con la scheda Autonomo è necessario seguire i seguenti passi:
1. Aggiungere il seguente url nella scheda File->Impostazioni: http://downloads.sodaq.net/package_sodaq_samd_index.json
2. Installare "Sodaq SAMD Boards by Sodaq" da Strumenti->Scheda->Gestore schede
3. Da Sketch->#include libreria->Gestione librerie installare i seguenti componenti: "Sodaq_BMP085", "Sodaq_SHT2x" e "Sdaq_wdt".
4. Scaricare i seguenti repository nella cartella Arduino\libraries 
	a. https://github.com/GabrielNotman/Sodaq_WifiBee
	b. https://github.com/GabrielNotman/RTCCounter

Link esterni:
1. https://support.sodaq.com/getting_started/
2. https://github.com/GabrielNotman/
