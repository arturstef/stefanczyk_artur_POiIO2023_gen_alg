# clone repository
<code>git clone https://github.com/arturstef/stefanczyk_artur_POiIO2023_gen_alg.git</code>
# compile & run
<code>cd stefanczyk_artur_POiIO2023_gen_alg
./cmp</code>
# run(after compilation)
<code>cd stefanczyk_artur_POiIO2023_gen_alg
./run</code>

# Opis działania algorytmu:

Algorytm genetyczny został zaimplementowany poprzez dodanie do klasy _Talgorithm_ metod _roullet_, _cross_ i _mutate_. Metody odpowiedzialne są kolejno za wybór rodziców
następnej populacji, krzyżowanie ze sobą poszczególnych osobników i losowe wprowadzanie mutacji. Przedstawiona implementacja algorytmu genetycznego bazuje na 
książce `Metody i techniki sztucznej inteligencji - Lech Rutkowski`.

## Opis działania poszczególnych funkcji:

1. Funkcja `roullet`:
   - Ta funkcja wykonuje selekcję przy użyciu metody koła ruletki. Wybiera kandydatów z bieżącej populacji na podstawie ich wartości dopasowania lub kosztu. Im wyższe wartości funkcji celu tym większe prawdopodobieństwo wyboru. Wybrani kandydaci zostają rodzicami kolejnej populacji.
   - Najpierw oblicza sumaryczny koszt dla każdego kandydata w bieżącej populacji i przechowuje go w zmiennej `cummulative_cost`.
   - Następnie oblicza prawdopodobieństwa wyboru dla każdego kandydata, dzieląc jego koszt przez sumaryczny koszt i przechowuje te prawdopodobieństwa w wektorze `candidate_cost`.
   - Następnie używa funkcji `sampleVector`, aby losowo wybrać nowych kandydatów do następnej populacji na podstawie obliczonych prawdopodobieństw.
   - Na koniec zastępuje kandydatów w bieżącej populacji wybranymi kandydatami.

2. Funkcja `cross`:
   - Ta funkcja wykonuje krzyżowanie między parami kandydatów w bieżącej populacji. Krzyżowanie to operator genetyczny, który łączy materiał genetyczny dwóch rodziców, tworząc potomstwo o nowych cechach.
   - Najpierw sprawdza losową liczbę w porównaniu z współczynnikiem krzyżowania `cross_coef`, aby określić, czy należy wykonać krzyżowanie.
   - Jeśli losowa liczba jest większa niż współczynnik krzyżowania, funkcja kończy działanie bez wykonania krzyżowania.
   - W przeciwnym razie tworzy nowe potomstwo, wybierając pary rodziców przy użyciu funkcji `pick_parents` z buforowego wektora utworzonego przy pomocy metody ruletki.
   - Dla każdej pary rodziców pobiera ich genotypy, których parametry konwertowane są z typu double na std::string reprezentację binarną i wykonuje operację krzyżowania, aby utworzyć nowy genotyp dla potomstwa.
   - Operacja krzyżowania polega na połączeniu binarnej reprezentacji genotypów rodziców. Zostaje wylosowony indeks cięcia. Zostają utworzone dwa substringi, z czego każdy należy do innego rodzica. Następnie substringi są łączone tworząc nowy gen. Do wykonania tej operacji używana jest funkcja `combine_binary`.
   - Nowe genotypy są przypisywane kandydatom w bieżącej populacji.

3. Funkcja `mutate`:
   - Ta funkcja wykonuje mutację genotypów kandydatów w bieżącej populacji. Mutacja wprowadza losowe zmiany w materiale genetycznym w celu utrzymania różnorodności w populacji.
   - Dla każdego kandydata dokonuje konwersji parametrów genotypu z ciągi binarne. 
   - Iteruje po każdym ciągu bitów i losuje liczbę, jeśli jest ona niższa od zmiennej `mutation_coef` zamieniana jest wartość poszczególnego bitu(0 na 1 lub 1 na 0).

Dodatkowo zachowywany jest niezmieniony najlepszy osobnik danej populacji `candidate_to_keep` i znajduję się zawsze jako pierwszy element wektora `candidates` w celu zapewnienia, że konwergencja jest funkcją niemalejącą.
