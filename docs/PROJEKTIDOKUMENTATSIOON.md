# Projekti dokumentatsioon

## 1. Projekti eesmärk ja seadme lühikirjeldus
**Mis asi see on, mida ja miks me teeme? Millist praktilist probleemi see lahendab?**

- Meie projekti eesmärk on teha lamp, mille heledustase järkjärgult kustub ja jälle põlema läheb. Näiteks õhtul paned lambi põlema ja see hakkab järjest kustuma kuni on pime, siis on ooteaeg ja peale ooteaja lõppu hakkab järkjärgult põlema süttima kuni on täismahus ja siis kustub ära. 
- Seadet saab kasutada uinumiseks ja ärkamiseks koos valgusega. 
- Peamised komponendid: Real time clock, nupp, lamp (3D prinditud), Arduino mikrokontroller.

---

## 2. Sisendite loetelu
**Millised on süsteemi poolt loetavad / mõõdetavad sisendid? Millega neid mõõdetakse / tuvastatakse?**


- Nupp vajutatakse -> Lamp süttib kõige eredamal reziimil (korra vilgub, et näidata tsükli algust)
- Taimer -> Real Time Clock
  
---

## 3. Väljundite loetelu
**Mida süsteem teeb / muudab? Millega väljund realiseeritakse?**

- LED süttib / kustub → LED

---

## 4. Nõuded loodavale seadmele
**Mis peab toimuma, kui kasutaja teeb mingi toimingu? Kirjelda käitumisloogika.**


- Kui vajutatakse nuppu -> LED süttib kõige eredamal reziimil
- RTC hakkab lugema 2h -> LED hakkab vaikselt eredust vähendama
- Kui LED on kustunud -> RTC hakkab lugema ootaega 6h
- Kui RTC 6h on täis -> LED süttib kõige hämaramal reziimil
- RTC hakkab lugema 2h -> LED hakkab eredust lisama
- LED töötab täiseredusel -> Tsükkel lõppeb, LED kustub

---

## 5. Süsteemi füüsiliste komponentide loetelu
**Millest seade koosneb? Lisa lingid või täpsed nimed, et keegi teine saaks sama asja uuesti osta / teha.**


- Arduino Uno R4 (mikrokontroller)
- Nupp 
- Real Time Clock - DS3132
- 3D-prinditud lamp (STL-failid lisage kataloogi `hardware/`)
- Toiteallikas (5V)


---

## 6. Ühendusskeem
**Kuidas kõik osad on omavahel ühendatud?**


 ![alt text](https://github.com/user-attachments/assets/0e8d8867-b328-45fb-b893-fa0c2da9e362)

punane - toitejuhe 5V

hall - ground 

kollane - signaaljuhe 

roheline - SCL

kollane RTC küljes - SDA

---

## 7. Süsteemi juhtiv kood (või pseudokood)
viide failile `src/DIMMER_LAMP`.  
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
