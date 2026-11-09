# Válka mravenišť

Pod starou hrušní na konci zahrady žije několik mravenčích kolonií. Léto končí, potravy ubývá a každé mraveniště chce ovládnout co největší kus zahrady dřív, než přijde zima. Hra je navržená jako tahová strategie pro dvě a více kolonií.

## Stav tohoto balíčku

Tento balíček navazuje na původní mapu (`GameBoard`, `Tile`, `Terrain`, `GrassTerrain`, `RockTerrain`) a přidává **abstraktní `Unit` a konkrétní `WorkerAnt`**. Implementuje:

- Uložení dělnice na volné a průchodné pole mapy.
- Pohyb se čtyřsměrnou navigací podle ceny terénu a dosahem jednotky.
- Blokaci pohybu obsazenými poli a komorami, kontrolu hranic mapy.
- Akční body, obnovení bodů po tahu, příjem poškození a smrt.
- Obranný bonus terénu dostupný pro budoucí soubojový systém.
- Testy a demonstraci v konzoli.

**QML grafické rozhraní a `GameController` jsou samostatný týmový úkol.** Proto nebylo přidáno do této větve; původní `src/main.cpp` zatím zůstává beze změny. Pro okamžité předvedení pohybu spusťte `valka_mravenist_unit_demo`.

## Sestavení a testování

Vyžaduje CMake 3.20+ a překladač s podporou C++20 (GCC, Clang nebo Visual Studio/MSVC).

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Demonstrace práce s dělnicí:

Linux / macOS:

```sh
./build/valka_mravenist_unit_demo
```

Windows s Visual Studiem (PowerShell):

```powershell
.\build\Debug\valka_mravenist_unit_demo.exe
```

U jednosestavovacích generátorů (Ninja/Makefiles) se spustitelný soubor na Windows může nacházet přímo ve složce `build`.

Očekávaný výstup demonstrace:

```text
WorkerAnt 1 at (1, 1)
Movement to (2, 1): OK
Position: (2, 1), remaining AP: 1
```

## Příklad integrace v C++

```cpp
#include "GameBoard.h"
#include "WorkerAnt.h"

GameBoard board(10, 8);
WorkerAnt worker(1, 0); // id jednotky, id kolonie

if (worker.placeOnBoard(board, 1, 1) && worker.canMoveTo(2, 1)) {
    (void)worker.moveTo(2, 1);
}

worker.resetActionPoints();
worker.takeDamage(3); // již vypočtené výsledné poškození
```

`GameBoard` musí existovat v době, kdy se s jednotkou hýbe. Pokud zanikne dříve než jednotka, jednotka pomocí slabého indikátoru životnosti pozná, že již není umístěna; její destruktor nepřistupuje k neplatné mapě.

Jednotky jsou záměrně nezkopírovatelné a nepřesouvatelné: `Tile` uchovává nevlastnící `Unit*`. Vlastnictví objektů jednotek bude později řešit `Colony` či herní logika. Pro umístění jednotky používejte `placeOnBoard`, nikoli samotné `Tile::placeUnit`, aby se synchronizovaly souřadnice a obsazenost.

## Rozhraní a další kroky

- Hlavičky: `src/units/Unit.h`, `src/units/WorkerAnt.h`.
- Nový CMake target: `units`, který veřejně odkazuje na existující target `map`.
- V `GameController` při tahu volat `worker.canMoveTo(x, y)` / `worker.moveTo(x, y)` a následně oznámit změny `MapModel` (signálem `dataChanged` pro původní a cílové pole). Samotná doménová třída `Unit` na Qt nezávisí.
- Detaily API, rozhodnutí o pravidlech a schéma integrace viz [docs/unit-worker-integration.md](docs/unit-worker-integration.md).
- UML pro import do Figmy: [SVG](docs/unit-worker-uml.svg), [PNG](docs/unit-worker-uml.png), [PlantUML](docs/unit-worker-uml.puml).

**Výchozí statistiky dělnice jsou prozatímní.** Zadání neobsahovalo konkrétní číselné hodnoty. Jsou soustředěné v `WorkerAnt.h`, takže je lze po dohodě týmu jednoduše změnit.
