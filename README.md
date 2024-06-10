# Hodnocení

7/7 bodů

# Zadání
V tomto projektu se seznámíte s jednoduchou substituční šifrou, konkrétně s Afinitní šifrou, která se používá k šifrování textových zpráv. Její základní princip spočívá v lineární transformaci jednotlivých písmen v textu. Váš program v jazyce C/C++ bude umět šifrovat, dešifrovat a prolamovat tuto šifru. Afinitní šifra se skládá ze dvou klíčů "a" a "b". Tyto klíče ovlivňují, jaké písmeno bude z původního textu zakódováno na konkrétní písmeno v zašifrovaném textu. 

## Detailnější zadání naleznete v přiloženém pdf souboru.
Testovací zašifrovaný text pro dešifrování bez znalosti klíče nalezenete v souboru ciphertext.csv.

## Formát vstupních a výstupních textů

Vstupní text pro šifrování se znalostí klíče se bude skládat pouze ze znaků velké/malé abecedy a
znaku mezery, který ve výstupní textu zachováte. Vstupní text pro šifrování bude v českém jazyce
bez diakritiky a interpunkce (Jinak řečeno pouze [a-zA-Z]+ a znak mezery) nebo anglickém v případě
jejich mix. Pro šifrování/dešifrování se znalostí klíče je jazyk nepodstatný, podstatné jsou pouze znaky!
Příkladem vstupních textů:
- Naprogramuj affine cipher
- Vysledny kod odevdej do Moodle vcetne dokumentace v souboru pdf

## Výstupní text pro šifrování
Výstupní text bude zašifrován pomocí Afinitní šifry a zadaným klíčem.
Příklady zašifrovaných textů:
Naprogramuj affine cipher -> REBLWILEMAX EDDSRY OSBNYL (klíč a=5, b=4)
Vysledny kod odevdej do Moodle vcetne dokumentace v souboru pdf ->
VEMRWTXE OAT ATWVTWL TA UAATRW VQWPXW TAOSUWXPKQW V MASNAJS DTZ (klíč a=3, b=10)


## Výstupní text pro dešifrování:
Výstupní text po dešifrování bude napsán pomocí české velké abecedy bez interpunkce a diakritiky.
Přiklad dešifrování:
REBLWILEMAX EDDSRY OSBNYL -> NAPROGRAMUJ AFFINE CIPHER (klíč a=5, b=4)

## Vstupní a výstupní text pro dešifrování bez znalosti klíče:
Vstupní soubor bude obsahovat jeden řádek se zašifrovaným textem pomocí Afinitní šifry a klíče.
Vaším úkolem bude tuto zprávu dešifrovat pomocí frekvenční analýzy a získat klíč. Hodnotit se bude
jak dešifrovaný text, tak získané klíče. Zašifrovaný text bude vždy v českém jazyce bez diakritiky a
interpunkce (takže zase jen [a-zA-Z]+ a znak mezery).

## Výstupní text:
Výstupní text následně uložíte do souboru, který dostanete pomocí parametrů. Výstupní text bude
ve stejném formátu jako při znalosti klíče tedy pouze velká písmena a mezery. S tím že na standartní
výstup vypíšete odhadované klíče, viz příklady spuštění.
