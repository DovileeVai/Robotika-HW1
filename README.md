# Robotika-HW1
## Problema ir idėja
Reakcijos laikas yra kritinis rodiklis sporte, ypač automobilių lenktynėse. Todėl yra reikalingos tinkamos priemonės tiksliai matuojančios reakciją į netikėtą starto signalą bei užtikrinančių galimybę tobulinti savo rezultatus. 
**Šio darbo tikslas:** sukurti F1 _„5 lights“_ logika paremtą reakcijos testo simuliatorių su:
- atsitiktiniu starto momentu,
- klaidingo starto (JUMP START) aptikimu,
- aiškiu rezultato rodymu,
- garso signalais skirtingiems įvykiams.

## Dizainas
1. LCD ekrane rodomas „Press to start“.
2. Vartotojui paspaudus mygtuką – rodomas „Lights...“ ir po vieną užsidega 5 LED lemputės (kiekvieną lydi trumpas garso signalas).
3. Toliau vyksta atsitiktinis laukimas (1-4 s). Jei mygtukas paspaudžiamas prieš „GO“, registruojamas ankstyvas paspaudimas („JUMP START“) ir parodoma žynutė bei pasigirsta garso signalas.
4. „GO“ akimirka: visos lemputės užgęsta, pasigirsta ilgas garso signalas.
5. Matuojamas laikas iki mygtuko paspaudimo. Užfiksuotas rezultatas rodomas LCD ekrane ("Your time: XXX ms").
6. Po 3 s pasirodo klausimas: "Again? Press the button." – gamila kartoti bandymą.

## Komponentai
- 1 x Arduino UNO R3
- 1 x Maketinė plokštė + laidai
- 1 x 16x2 I2C LCD ekranas
- 5 x LED lemputės
- 5 x 220Ω rezistoriai
- 1x Mygtukas
- 1x Piezo garsiakalbis

## Schema ir sujungimas
- LCD I2C ekranas: VCC -> 5V, GND -> GND, SDA -> A4, SCL -> A5;
- LED lemputės: LED anodas -> rezistoriai (220Ω) -> naudojami skaitmeniniai (angl. _digital_)  ARDUINO kištukai nuo D2 iki D6; LED katodas -> GND;
- Mygtukas: viena kojelė (viršutinė dešinė) -> D7, kita (apatinė kairė) -> GND;
- Piezo garsiakalbis: neigiamas kontaktas -> GND; teigiamas kontaktas -> D8.
   
<img width="767" height="598" alt="pirmas HW" src="https://github.com/user-attachments/assets/be30aeb4-c43f-4212-8f16-dcc0a9763935" />

<img width="1007" height="782" alt="image" src="https://github.com/user-attachments/assets/91e6c664-0c49-4424-be80-e64cbcb2ecaa" />

## Kas veikia/kas neveikia
Kas veikia:
  - Veikia LED lempučių užsideimas paeiliui.
  - Garsiniai signalai skirtingiems įvykiams (lempučių užsidegimui, starto – „GO“ signalui, skubotam paspaudimui).
  -  LCD ekrane tinkamai rodomi pranešimai.
  -  Atsitiktinis laukimas iki starto.
  -  Ankstyvo paspaudimo (JUMP START) aptikimas.
Kas neveikia:
  - Tinkamas mygtuko veikimo užtikrinimas (vis dar kartais nidealiai reaguoja į paspaudimus). 

## Ateities tobulinimas
- Išsaugoti rekordą (geriausią laiką), kad būtų galima sekti reakcijos greičio progresą.
- Patobulinti mygtuko veikimą (visiškai tinkamą reagavimą į paspaudimus).

