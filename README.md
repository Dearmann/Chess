# Chess
Projekt semestr 3, Programowanie Komputerów

# Treść zadania
Celem projektu jest napisanie programu służącego do gry w szachy z dwoma ludzkimi graczami (bez komputera).
Każdy z graczy posiada 16 figur - 8 pionków, 2 gońce, 2 skoczki, 2 wieże, hetmana i króla. Każda z figur może poruszać się tylko w charakterystyczny dla siebie sposób. 
Rozgrywka odbywa się na planszy o rozmiarze 8 x 8 pokolorowanej na przemian. Gracz pierwszy posiada figury białe i one rozpoczynają rozgrywkę, gracz drugi posiada figury czarne. Celem gry jest zbicie króla gracza przeciwnego (szach mat).
Interfejs będzie realizowany z użyciem biblioteki SFML. Plansza jest rozmiaru 800x800px z jednym polem o rozmiarze 100x100px.

# Analiza zadania
Zagadnienie przedstawia problem stworzenia grafiki szachownicy i jej figur z użyciem biblioteki SFML. Reprezentacji w sposób obiektowy szachownicy z jej figurami, przy użyciu klas, dziedziczenia i polimorfizmu. Finalnie na połączeniu tych dwóch elementów - grafiki i obiektowego back-endu.

# Struktury danych
W programie wykorzystano strukturę tablicy dwuwymiarowej, rozmiaru 8 na 8 do przedstawienia szachownicy. Jest to tablica typu wskaźnik na klasę Piece (Piece* ). Tablica ta jest zawarta w klasie Board.

# Algorytmy
Program do wykonania wielu funkcji iteruje 8 razy przez pętle for, w której jest zawarta druga pętla for, przez którą również iteruje 8 razy. W ten sposób program przeszukuje całą szachownicę w celu znalezienia na danym polu figury lub jej braku. W taki sposób przedstawiane są grafiki figur szachowych, graficzna reprezentacja możliwości wykonania ruchu (w postaci zielonej kropki) oraz wyzerowanie tablicy po stworzeniu obiektu Board jak i usunięciu obiektów po zakończeniu pracy programu.
Algorytm przemieszczenia figury jest następujący: tymczasowe zapisanie aktualnych koordynatów figury do przemieszczenia, jeżeli na koordynatach do przemieszczenia znajduje się inna figura - usunięcie jej, zamiana koordynatów figury przemieszczanej, inkrementacja zmiennej oznaczającej ilość wykonanych ruchów przez figurę, umieszczenie figury w odpowiednim miejscu tablicy reprezentującej szachownicę, usunięciu z tablicy poprzedniego położenia figury poruszanej, zamiana tury na drugiego gracza, wyłączenie figury aktywnej.
Algorytmy ograniczające ruchy poszczególnych rodzajów figur są na tyle różnorodne, że nie dają się opisać w sposób ogólny.

# Specyfikacja zewnętrzna
Po uruchomieniu programu ukazuje się okno z szachownicą, pod którą znajdują się informacje dla użytkownika:

![board](https://user-images.githubusercontent.com/49723341/132592969-381248c3-685f-472a-87d8-f97889d12ca0.png)

Zawarte są tam informacje o:

1. Turze:

![turnwhite](https://user-images.githubusercontent.com/49723341/132593140-65fa06cf-ea8e-479d-9747-412811f35787.png)
![turnblack](https://user-images.githubusercontent.com/49723341/132593147-acbea3a6-df2d-47eb-9b6c-a2b036ef8c14.png)

2. Zwycięstwie i możliwości rozpoczęcia nowej gry klawiszem “Enter”:

![newgame](https://user-images.githubusercontent.com/49723341/132593157-28b4dc48-ed8a-477a-ad12-b1615357c464.png)

Pole, na którym znajduje się aktualnie poruszana przez gracza figura, jest podświetlone na zielono. Zielonymi kropkami są oznaczone wszystkie możliwe ruchy, które aktualnie aktywna figura może wykonać:

![movement](https://user-images.githubusercontent.com/49723341/132593190-3db5d1c4-7bd3-4b76-84ae-a11f70f2dc8d.png)

Możliwość wykonania roszady jest przedstawiona w następujący sposób:

![castling](https://user-images.githubusercontent.com/49723341/132593251-32b44457-0fdc-4334-96ac-505008a9df4f.png)

# Specyfikacja wewnętrzna
Program został zrealizowany zgodnie z paradygmatem strukturalnym, w sposób obiektowy. W programie rozdzielono interfejs (komunikację z użytkownikiem) od logiki aplikacji - poruszanie się i zbijanie figur szachowych, rozpoczynanie nowej gry i wyznaczanie zwycięzcy.

# Ogólna struktura programu
Funkcja główna zaczyna się od stworzenia elementów graficznych: załadowania tekstur z plików, utworzenia zmiennych biblioteki SFML, przyporządkowanie tym zmiennym odpowiednich tekstur i rozmiarów oraz położenie w oknie programu.
Następnym etapem jest utworzenie obiektów: szachownicy i jej figur oraz przyporządkowanie tym obiektom odpowiednich im wartości: koordynatów, koloru, tekstur.
Ostatecznie w pętli while realizowana jest graficzna reprezentacja programu, który można zamknąć klikając znak X w prawym górnym rogu okna.
Jeżeli kliknięty zostanie lewy przycisk myszy, funkcja klasy Board isMouseClickInsideWindow sprawdzi, czy kliknięcie odbyło się w oknie programu. Jeżeli tak, koordynaty kliknięcia w pikselach przy użyciu funkcji setClickedBoardSquare zostaną przekonwertowane na koordynaty na szachownicy i zapisane w zmiennych klasy Board xPressed i yPressed. Jeżeli kolor klikniętej figury odpowiada aktualnej turze gracza funkcja setClickedPieceAsActive ustawi figurę jako aktywną i gotową do ruchu. Jeżeli istnieje aktywna figura, następne kliknięcie będzie ruchem. Jego możliwość zostanie sprawdzona przez isMoveCorrect - funkcję polimorficzną podklas dziedziczących z klasy Piece, a następnie ruch zostanie zrealizowany przez moveActivePiece, po czym nastąpi zmiana tury gracza.
Jeżeli zostanie wciśnięty klawisz “Enter” rozpocznie się nowa gra funkcją startNewGame.
Obiekt szachownica zawiera zmienną winType, której wartość na początku gry wynosi 0. Funkcja removePiece po zbiciu króla czarnego ustanawia tę wartość na 1 a po zbiciu króla białego na 2. W zależności od tej wartości zostanie wyświetlona informacja o zwycięstwie i grę można kontynuować, tylko gdy jej wartość wynosi 0 (po wciśnięciu klawisza “Enter”).

# Szczegółowy opis klas i metod
Szczegółowy opis klas i metod zawarty w pliku "Dokumentacja - Chess.pdf".

# Testowanie
Program został przetestowany, używając różnych kombinacji ustawień figur na szachownicy. Próbując przemieścić się w miejsca, w które dana figura nie powinna mieć dostępu, próbując ruszyć figurę gracza, który nie ma aktualnie tury oraz próbując zbić figury własnego koloru. Warunki zajścia roszady zostały przetestowane dla obu graczy i dla obu wież. Kliknięcia myszy i konwersja koordynatów z pikseli na koordynaty szachowe jest wyświetlana w oknie konsoli, co umożliwiło łatwe sprawdzenie poprawności.
Program został sprawdzony pod kątem wycieków pamięci z użyciem biblioteki CRT.

# Wnioski
Program “Szachy” jest programem, którego zadaniem jest odwzorowanie tradycyjnej gry z użyciem biblioteki graficznej SFML i programowania obiektowego. Wykorzystuje nieskomplikowaną strukturę tablicy dwuwymiarowej, która bardzo dobrze nadaje się do przedstawienia szachownicy. Wykorzystuje również dwie klasy Board i Piece oraz 6 podklas klasy Piece odpowiadającej każdej z figur. Pomimo że szachy są grą tradycyjną, której zasady nie ulegają znacznym zmianom, to użycie dziedziczenia i polimorficznej funkcji do ograniczania ruchów umożliwia łatwą możliwość wprowadzenia nowych figur szachowych dla graczy chcących doświadczenia własnej wersji szachów.

# Literatura

https://www.sfml-dev.org/learn.php

https://en.wikipedia.org/wiki/Chess
