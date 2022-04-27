# Függvény illesztés ponthalmazra
A programozás alapja 2. házi feladat - Baki Bence István [BOIR4K]
## Informális házi feladat leírás
Mérnöki problémamegoldás során gyakran ütközik az ember mérés után feldolgozandó adathalmazba, melyre a legjobban illeszkedő függvényt keressük. Ahelyett, hogy keresnénk az interneten egy az igényeinknek 95%-ban megfelelő szolgáltatást 30 másodperc alatt, az egyszeri mérnök-hallgató megpróbál inkább saját programot írni rá 2 hét alatt, ami a maradék 5% igényt is megvalósítja (kézi szövegdobozba gépelés helyett .csv/.txt fájl feldolgozás).
## Formális házi feladat leírás
### Az elkészítendő szoftver célja
A program célja, hogy az annak megadott, formázott adathalmazt (.csv/.txt), mely síkbeli pontok koordinátáit tartalmazza, feldolgozza, illetve kiszámolja néhány előre megadott függvénytípusból (egyenes, parabola, hiperbola – n-ed fokú polinom? stb.) azt, ami a legjobban illeszkedik a pontokra.
### Elvárások
A program parancssori argumentumként megkapja a feldolgozandó fájl nevét, melyben az egyes síkbeli koordináták szóközökkel elválasztva szerepelnek a következő formátumban: (x,y). Megkapja emellett parancssoron az illeszteni kívánt függvénytípus nevét is.

A parancssorra kiírja a program a kiválasztott függvénytípusnak egy specifikus képletet, mely grafikonja a lehető legjobban illeszkedik a megadott ponthalmazra.
### Implementálandó funkciók
*	Mátrix és Vektor osztály működő aritmetikával (szorzás, transzponálás, invertálás)
* Mátrix QR felbontás képzése Householder módszerrel/Gram-Schmidt ortogonalizációval
* Minimális hiba keresésre legkisebb négyzetek módszerével

### Felhasználói interakció
A felhasználó az adathalmazt tartalmazó fájl címét és a kívánt illesztendő polinom típust parancssori argumentumként adja meg, ezekkel kapcsolatban hibás megadás esetén a program jelez (nincs ilyen előre megadott polinom, nem létezik a fájl stb.)
### Követelmények
**Futtató környezet követelményei**

A programomat Windows környezetre fogom lefuttatni Visual Studio 2019-ben, így a futtatható binárist azon is fogom tudni lefuttatni. Azonban igyekszem csak cross-platform nyelvi elemeket felhasználni a kód írása során.

**Célközönség**

Bárki, aki síkbeli ponthalmazra görbét szeretne illeszteni.




### Források:
https://algebra.math.bme.hu/sites/algebra.math.bme.hu/files/users/wettl/okt/HaladoLinAlg/2020/handout_e04_20fm_orto.pdf

https://web.cs.elte.hu/blobs/diplomamunkak/bsc_alkmat/2016/szalai_eszter.pdf

https://math.bme.hu/~pitrik/2021_22_2/A2_tav_9het.pdf

https://en.wikipedia.org/wiki/QR_decomposition#Computing_the_QR_decomposition

https://hu.wikipedia.org/wiki/Legkisebb_n%C3%A9gyzetek_m%C3%B3dszere

https://www.youtube.com/watch?v=FAnNBw7d0vg

https://people.inf.elte.hu/hozsaai/3_felev/Nummod1/Locsi-esti-ea-dia/nummod1esti_ea05.pdf

https://www.eltereader.hu/media/2013/06/Numerikus_modszerek_peldatar_opt.pdf
