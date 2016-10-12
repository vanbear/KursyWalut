# KursyWalut
Daniel Wąs

Informatyka Stosowana i Systemy Pomiarowe, rok II

Uniwersytet Wroławski


## O aplikacji
Jest to projekt w ramach przedmiotu Projekt w C++. Za zadanie obrałem stworzenie aplikacji obliczającej średnie kursy między dwoma wybranymi walutami. Aplikacja ta napisana będzie w języku C++, posiadać będzie graficzny interfejs użytkownika z wykorzystaniem QML w środwisku Qt Creator. 


## Założenia:
- schludny, minimalistyzny, przystępny dla końcowego użytkownika interfejs
- aktualne dane na temat kursów pobierane będą bezpośrednio ze strony [Narodowego Banku Polskiego](www.nbp.pl)
- do pobierania i przetwarzania danych wykorzystywane będzie parsowanie plików .xml
- możliwość pracy w trybie offline, zapisywanie ostatnio pobranych danych na dysku (wraz z datą), które wykorzystywane będą w razie braku połączenia internetem
- mozliwość szybkiej zamiany przeliczanych walut miejscami
- graficzna reprezentacja waluty/kraju pochodzenia danej waluty w postaci ikon i/lub delikatnej zmiany kolorystyki tła
- historia przeliczeń
- możliwość kopiowania do schowka wyniku obliczeń w formie tekstu


## Kamienie milowe:
- [x] 13.10.16 - plan projektu
- [ ] 27.10.16 - wstępny, prowizoryczny projekt interfejsu graficznego oraz zaimplementowanie funkcji sieciowych i systemu obliczania kursów
- [ ] 3.11.16 - naprawa błędów, przygotowanie prototypu do prezentacji, prezentacja prototypu
- [ ] 17.11.16 - zaimplementowanie trybu offline
- [ ] 21.12.16 - reprezentacja graficzna każdej z dostępnych walut
- [ ] 12.01.17 - końowe poprawki, ewnetualne zmiany w interfejsie, deadline
