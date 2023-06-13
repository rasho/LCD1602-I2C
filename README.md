# LCD_I2C biblioteka za Arduino

Ova biblioteka omogućava jednostavno upravljanje LCD ekranom 16x2 preko I2C komunikacije koristeći Arduino mikrokontroler.

## Instalacija

1. Preuzmite ZIP arhivu biblioteke sa GitHub stranice.
2. Otvorite Arduino IDE.
3. Izaberite opciju "Sketch" u meniju, zatim "Include Library" i na kraju "Add .ZIP Library...".
4. Izaberite preuzetu ZIP arhivu biblioteke i kliknite na "OK".
5. Sada je biblioteka instalirana i spremna za upotrebu.

## Korišćenje

1. Uključite biblioteku dodavanjem sledeće linije na početak vašeg Arduino programa:

```cpp
#include "LCD_I2C.h"
```

2. Inicijalizujte objekat klase LCD_I2C sa odgovarajućim brojem kolona i redova LCD ekrana:

```cpp
LCD_I2C lcd(16, 2); // Inicijalizacija LCD ekrana sa 16 kolona i 2 reda
```

3. U funkciji `setup()` pozovite metodu `begin()` za inicijalizaciju LCD ekrana:

```cpp
void setup() {
  lcd.begin();
  // Ostali kod za inicijalizaciju
}
```

4. Sada možete koristiti različite metode klase LCD_I2C za upravljanje LCD ekranom. Na primer:

```cpp
void loop() {
  lcd.clear(); // Obriši ekran
  lcd.setCursor(0, 0); // Postavi kursor na prvu poziciju
  lcd.print("Hello, world!"); // Ispisi tekst na ekranu
  delay(2000);
}
```

5. Kompajlirajte i otpremite program na Arduino mikrokontroler.

## Metode

Ova biblioteka sadrži sledeće metode za upravljanje LCD ekranom:

- `begin()`: Inicijalizuje LCD ekran.
- `clear()`: Briše ekran.
- `setCursor(uint8_t col, uint8_t row)`: Postavlja kursor na određenu poziciju.
- `write(uint8_t value)`: Ispisuje jedan karakter.
- `print(const char* str)`: Ispisuje tekst na ekranu.
- `printAt(uint8_t col, uint8_t row, const char* str)`: Ispisuje tekst na određenoj poziciji.
- `printInt(int value)`: Ispisuje celobrojnu vrednost.
- `printFloat(float value, int decimalPlaces)`: Ispisuje decimalnu vrednost.
- `scrollDisplayLeft()`: Pomeranje teksta na ekranu ulevo.
- `scrollDisplayRight()`: Pomeranje teksta na ekranu udesno.
- `createChar(uint8_t location, uint8_t charmap[])`: Definiše korisnički karakter.

## Autor

Ova biblioteka je razvijena od strane Radenka Bogdanovica

## Doprinosi

Svi doprinosi su dobrodošli! Ako želite da unapredite ovu biblioteku, slobodno otvorite "Issue" ili "Pull Request" na GitHub stranici projekta.


## Napomene

- Ova biblioteka je prilagođena za korišćenje sa LCD ekranom 16x2 koji koristi I2C komunikaciju. Uverite se da vaš LCD ekran odgovara tim specifikacijama.
- Za I2C komunikaciju, LCD ekran mora imati odgovarajuću I2C ekspanzionu pločicu koja se povezuje na LCD pinove i komunicira sa Arduino mikrokontrolerom preko I2C magistrale.
