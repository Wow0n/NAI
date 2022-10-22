**Jaka metoda daje najlepsze wyniki?**
> Najlepsze wyniki osiąga hill climbing. Różnice wyników minimów w porównaniu z globalnym minimum dla poszególnych fukcji wynosi odpowiednio:
> - Ackley &rarr; 0,016020724 do 0
> - Himmelblau &rarr; 0,000311335 do 0
> - Hölder table &rarr; -19,208184 do -19,2085 (0,000316) 
> 
**Jaka metoda jest najszybsza dla podobnej jakości wyników?**
> Metodą z najlepszym stosunkiem szybkości do jakości wyników, w porówaniu ze wszystkimi metodami, okazał się brute force.
> 
**Jaka metoda kompletnie się nie nadaje?**
> Metoda simulated annealing. Ma ona największe róznice wyników od globalnych minimów przy najdłużyszych czasach wykonywania w porównaniu do pozostałych metod.
>
<br>

**Średnia wyników**

| **Funkcja**      | **Brute force** | **Hill climbing** | **Simulated annealing** |
|:----------------:|:---------------:|:-----------------:|:-----------------------:|
| **Ackley**       | 0,014669605     | 0,016020724       |       0,07679074        |
| **Himmelblau**   | 0,000253966     | 0,000311335       |       0,043533443       |
| **Hölder table** | -19,2081          | -19,208184        |       -19,141244        |





<br>

**Średnia czasów [μs]**

| **Funkcja**      | **Brute force** | **Hill climbing** | **Simulated annealing** |
|:----------------:|:---------------:|:-----------------:|:-----------------------:|
| **Ackley**       | 510723,88       | 790718,96         |        1702892,2        |
| **Himmelblau**   | 255821,96       | 539516,12         |        442923,08        |
| **Hölder table** | 544137,48       | 757962,84         |       1000430,96        |









