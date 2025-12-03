# Projekti dokumentatsioon

## 1. Projekti eesmärk ja seadme lühikirjeldus
**Mis asi see on, mida ja miks me teeme? Millist praktilist probleemi see lahendab?**

Näide stiilist:
- Meie projekti eesmärk on teha lamp, mille heledustase järkjärgult kustub ja jälle põlema läheb. Näiteks õhtul paned lambi põlema ja see hakkab järjest kustuma kuni on pime, siis on ooteaeg ja peale ooteaja lõppu hakkab järkjärgult põlema süttima kuni on täismahus ja siis kustub ära. 
- Seadet saab kasutada uinumiseks ja ärkamiseks koos valgusega. 
- Peamised komponendid: Real time clock, nupp, lamp (3D prinditud), Arduino mikrokontroller.

---

## 2. Sisendite loetelu
**Millised on süsteemi poolt loetavad / mõõdetavad sisendid? Millega neid mõõdetakse / tuvastatakse?**

Kirjelda kõik sisendid eraldi punktidena.  
Näited (asenda enda projektiga):

- Nupp vajutatakse -> Lamp süttib kõige eredamal reziimil (korra vilgub, et näidata tsükli algust)
- Taimer -> Real Time Clock
  
---

## 3. Väljundite loetelu
**Mida süsteem teeb / muudab? Millega väljund realiseeritakse?**

Näited (asenda enda projektiga):
- LED süttib / kustub → LED

---

## 4. Nõuded loodavale seadmele
**Mis peab toimuma, kui kasutaja teeb mingi toimingu? Kirjelda käitumisloogika.**

Näited (kohanda enda projektile):

- Kui vajutatakse nuppu -> LED süttib kõige eredamal reziimil
- RTC hakkab lugema 2h -> LED hakkab vaikselt eredust vähendama
- Kui LED on kustunud -> RTC hakkab lugema ootaega 6h
- Kui RTC 6h on täis -> LED süttib kõige hämaramal reziimil
- RTC hakkab lugema 2h -> LED hakkab eredust lisama
- LED töötab täiseredusel -> Tsükkel lõppeb, LED kustub

---

## 5. Süsteemi füüsiliste komponentide loetelu
**Millest seade koosneb? Lisa lingid või täpsed nimed, et keegi teine saaks sama asja uuesti osta / teha.**

Tabelina või punktidena. Nt:

- Arduino Uno R4 (mikrokontroller)
- Nupp 
- Real Time Clock - DS3132
- 3D-prinditud lamp (STL-failid lisage kataloogi `hardware/`)
- Toiteallikas (5V)


---

## 6. Ühendusskeem
**Kuidas kõik osad on omavahel ühendatud?**

- Lisa siia pilt või skeemi kirjeldus.
- Fail `hardware/wiring-diagram.png` peab näitama vähemalt:
  - milline pin Arduinol läheb millise komponendi sisendisse,
  - kuidas on toide ühendatud.

Kui skeemi pole veel joonistatud, siis vähemalt kirjelda tekstina, nt:

- IR-sensor OUT → Arduino digipin 7  
- Servo signaal → Arduino digipin 6  
- Mootoridraiveri IN1 → Arduino digipin 2  
- Mootoridraiveri IN2 → Arduino digipin 3  
- Mootoridraiveri ENA → Arduino pin 5 (PWM)  
- GND kõik ühises massis

👉 _Skeem peab lõpuks olemas olema, mitte ainult tekst._

---

## 7. Süsteemi juhtiv kood (või pseudokood)
**Kirjelda programmi loogikat nii, et seda on võimalik aru saada ka hiljem.**  
Kui kood töötab, pane siia lühike selgitus + viide failile `src/DIMMER_LAMP`.  
Programmi eesmärk on juhtida NeoPixel LED-rõngast nii, et toimub üks valgustsükkel, mis algab nupuvajutusega ja lõpeb automaatselt.

**Tsükli käivitamine**
Nuppu vajutades lülitatakse tsükkel sisse (cycleActive = true).
Kui tsükkel töötab, saab nupuga selle igal hetkel katkestada.

**Tsükli tööetapid**
Hämardumine – LEDid muutuvad järk-järgult heledast tumedaks.
Kustunud periood – LEDid on täielikult pimedad määratud aja.
Heledamaks muutumine – LEDid muutuvad uuesti järk-järgult heledaks.
Iga faasi ajal kontrollitakse, kas kasutaja vajutas nuppu. Vajutuse korral tsükkel peatub kohe.

**Tsükli lõpp**
Kui kõik kolm etappi on lõpetatud, kustutab programm LEDid (setBrightness(0)).
cycleActive pannakse false, mis peatab tsükli edasise kordumise.
Tsükkel ei lähe automaatselt uuesti käima.
Uus tsükkel algab ainult uue nupuvajutusega.

**Loop-funktsioon**
loop() kontrollib:
kas nuppu vajutati,
ja kui tsükkel on aktiivne, käivitab ühe korra runLightCycle().
Kui tsükkel on lõpetatud, jääb programm ooterežiimi kuni uuesti nuppu vajutatakse.
