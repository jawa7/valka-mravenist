# Unit + WorkerAnt – integrační specifikace

## Záměr

Implementace náleží tasku **Bázová jednotka Unit a kasta WorkerAnt**. Oproti dosavadnímu stavu přidává do existujícího mapového modelu skutečný životní cyklus jednotky a přesuny. Neobsahuje žádná pravidla v QML/JavaScriptu ani implementaci jiných kast, `TurnManager` či soubojové strategie.

## Struktura

| Objekt | Odpovědnost |
| --- | --- |
| `Unit` | Abstraktní společná data a chování; polymorfní `getType()`; umístění, pohyb, zásah, akční body. |
| `WorkerAnt` | Konkrétní odvozená kasta, vrací `UnitType::Worker` a používá výchozí statistiky. |
| `GameBoard` | Původní mapa; nově pouze lehký `getLifetimeToken()` pro bezpečné rozpoznání zániku mapy. |
| `Tile` | Původní pole, uchovává **nevlastnící** `Unit*`; opraveno, aby nebylo možné umístit jednotku na komoru. |
| `Terrain` | Původní rozhraní `getMovementCost()`, `getDefenseBonus()`, `isPassableFor(UnitType)`. |

## Pravidla zvolená pro 1. obhajobu

1. Umístění `placeOnBoard` nespotřebovává akční bod. Zamítá neplatné souřadnice, obsazené/neprůchodné pole, mrtvou či již umístěnou jednotku.
2. `moveTo` je povolen jen na již existující mapě a živé jednotce s alespoň jedním AP. Stejná pozice není platný pohyb.
3. Trasa vede pouze přes čtyři ortogonálně sousední pole. Dijkstra hledá nejlevnější trasu z hlediska součtu `getMovementCost()` vstupovaných polí (výchozí pole se nepočítá). Záporná cena je odmítnuta.
4. Přes jednotku ani komoru nelze projít a nelze vstoupit na obsazené cílové pole. Neprůchodnost pro danou kastu určuje `Terrain::isPassableFor`.
5. Celková cena cesty nesmí překročit `movementRange`. **Jeden úspěšný přesun spotřebuje právě 1 AP**, nezávisle na délce trasy. Neúspěšný přesun nezmění stav ani AP.
6. `takeDamage(damage)` přijímá výslednou velikost poškození (až po budoucím výpočtu soubojovou strategií). Negativní a nulové zásahy se ignorují, HP nepoklesne pod nulu. Při smrti se jednotka odebere z mapy a AP se vynulují.
7. `getEffectiveDefense()` poskytuje `baseDefense + terrain.getDefenseBonus()` (neumístěná jednotka má jen základní obranu). Samotný `takeDamage` obranu znovu neodečítá.
8. `resetActionPoints()` obnoví maximální počet AP u živé jednotky, u mrtvé ponechá nulu.

Číselné hodnoty WorkerAnt jsou **návrhové, nikoli potvrzené zadáním**: HP 10, útok 2, obrana 1, dosah 3, AP 2. Jsou definovány jako statické konstanty v `WorkerAnt.h`.

## Vlastnictví a bezpečnost

- Jednotka si nepřivlastňuje mapu. `Tile` si nepřivlastňuje jednotku. Vlastníkem jednotky se má stát `Colony` nebo vyšší logika pomocí `std::unique_ptr<Unit>`.
- Kopírování a přesun objektů `Unit`/`GameBoard` jsou zakázány, aby nevznikaly neplatné ukazatele.
- Destruktor `Unit` odstraní referenci z živé mapy; pokud již `GameBoard` zanikl, přístup se přeskočí.
- Jednotka smí být umístěna jen jednou; před změnou mapy je nutné `removeFromBoard()`.
- Předpokládá se jednovláknová herní logika (typická Qt GUI smyčka); metody neprovádějí synchronizaci.

## Integrace do `GameController` a `MapModel` (úkol Ilyi)

Při volbě startovního pole může controller uložit ukazatel na `Tile::getUnit()`. Při pokusu o tah ověřit `selectedUnit && selectedUnit->canMoveTo(toX, toY)`; zapamatovat původní souřadnice; zavolat `selectedUnit->moveTo(toX, toY)`; při úspěchu informovat `MapModel` o změně obou buněk. Všechny herní validace se odehrávají v C++, QML pouze vykresluje a předává kliknutí.

Jednotky, které bude controller nebo kolonie vytvářet, musejí mít životnost zajištěnou v C++ (např. `std::vector<std::unique_ptr<Unit>>`). Lokální dočasná `WorkerAnt` by po opuštění funkce zmizela z herního plánu.

## Integrace do Gitu

Dodaný vstupní archiv neobsahoval `.git` metadata ani remote, proto nebylo možné přímo publikovat větev ani vytvořit Pull Request. Doporučený postup v existujícím klonovaném repozitáři:

```bash
git switch main
git pull --ff-only
git switch -c feature/unit-worker
# Teď do klonu přenést soubory z balíčku nebo aplikovat přiložený .patch.
git add CMakeLists.txt README.md src/map/GameBoard.cpp src/map/GameBoard.h src/map/Tile.cpp src/units examples tests docs
git commit -m "feat: implement Unit and WorkerAnt with map movement and tests"
git push -u origin feature/unit-worker
```

Poté v Bitbucketu nebo GitHubu vytvořit PR do `main`, nechat zkontrolovat spoluhráčem a dle týmových pravidel sloučit až po schválení.

## Stav kritérií

- [x] Základní abstraktní `Unit` a konkrétní `WorkerAnt`.
- [x] Všechny jmenované atributy a virtuální metody.
- [x] Umístění na `Tile`, změna souřadnic a validovaný pohyb s terénem.
- [x] Integrace do původního CMake projektu.
- [x] Testy mapy a jednotek, konzolové demo.
- [x] UML diagram připraven pro import do Figmy (`.svg`, `.png`, `.puml`).
- [ ] Nahrání diagramu do sdílené Figmy – vyžaduje přístup k týmovému boardu.
- [ ] Push větve a PR do `main` – vyžaduje přístup k vzdálenému repozitáři.
