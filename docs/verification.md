# Výsledky ověření implementace

Ověření provedeno na dodané výchozí verzi projektu (archiv `valka-mravenist-master (2).zip`).

| Prostředí | Výsledek |
| --- | --- |
| GCC 14.2, C++20, Debug | CMake configure + sestavení všech targetů úspěšné. CTest: 2/2 úspěšné. |
| Clang 17, C++20, Release | CMake configure + sestavení všech targetů úspěšné. CTest: 2/2 úspěšné. |
| GCC 14.2, Debug, AddressSanitizer + UndefinedBehaviorSanitizer | Sestavení úspěšné. CTest: 2/2 úspěšné, bez hlášených chyb. |
| Samostatná konzolová demonstrace | Unit umístěna na mapu, přesun úspěšný, odpovídající změna pozice a AP. |

`unit_tests.cpp` ověřuje deset skupin scénářů: statistiky a typ, validaci konstruktoru, obsazenost a umístění, komory a průchodnost, pohyb a AP, cenu terénu/obranu, objíždění překážek, drahou trasu přes kámen, poškození/smrt a životnost mapy a jednotky.

Původních šest mapových testů zůstává zachováno a je doplněna kontrola, že jednotku nelze vložit na komoru. V Release se nyní mapové aserce rovněž vykonají.

Testování proběhlo v Linuxu. Kompilace a běh na konkrétní konfiguraci Windows/Visual Studio/Qt nebyly v tomto prostředí ověřeny. Kód doménové logiky Qt nepotřebuje; bude připojen přes samostatné `GameController`/`MapModel` řešení.
