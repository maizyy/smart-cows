# System SmartCows

## Wstęp

W ramach danego repozytorium zajęliśmy się problemem z obszaru gospodarstwa domowego. 

Zdecydowaliśmy się na wybór rozwiązania tego problemu i zaproponowaliśmy rozwiązanie w postaci
systemu do monitoringu stanu bydła, które pozwoli na łatwiejsze monitorowanie hodowanych zwierząt.
Farmerzy zostaną odciążeni (nie będą musieli już pilnować zwierząt przez cały czas) oraz zostanie
polepszony stan zdrowotny bydła (jako że już nie musi znajdywać się wyłącznie w ramach terenu
zamkniętego).

## Opis rozwiznia

Architektura proponowanego rozwiązania:

![network](https://user-images.githubusercontent.com/62251424/178584727-e3648502-79e7-47a9-aa56-10b8d0c484e8.jpg)

W tak zdefiniowanej architekturze, każde obserwowane zwierze posiada własny czujnik wyposa-
żony w **moduł GPS**, **czujnik temperatury**, **panel słoneczny** oraz **moduł LoRa**. W ten o to sposób
każdy z czujników jest w stanie komunikować się z bramą LoRa i przesyłać informację o obecnej
lokalizacji bydła, temperaturze środowiska otaczającego bydło oraz o poziomie naładowania baterii
takiego czujnika.

Aby taka komunikacja była możliwa, farma musi posiadać własną bramkę LoRa lub być umiej-
scowiona w zasięgu takiej bramki.

Przy pomocy bramki LoRa, dane sczytywane z czujnika są wysyłane do **The Things Network**
(TTN, czyli globalny ekosystem Internetu Rzeczy przeznaczony dla współpracy, który jest wykorzy-
stywany do utworzenia sieci, urządzeń i rozwiązań z wykorzystaniem LoRaWAN). TTN przetwarza
otrzymane dane (przykładowo, konwertuje dane z postaci bitowej na postać w postaci obiektu JSON,
czytelnej dla człowieka) oraz udostępnia je przez własnego **MQTT brokera** dla wszystkich chętnych
(którzy posiadają klucz dostępu).

Aby móc, odbierane dane w jakiś sposób udostępniać naszemu użytkownikowi, musimy nasze dane
gdzieś przechowywać. Zdecydowaliśmy zatem wybrać platformę **firebase** (utrzymywaną przez Go-
ogle) i jej usługę real-time-database do przechowywania danych, wysyłanych ”na żywo” i następnie
połączyć naszą usługę z aplikacją przy pomocy odpowiedniego API.

Jednym z ostatnich elementów, potrzebnych dla umożliwienia komunikacji między czujnikiem, a
aplikacją użytkownika jest połączenie TTN’u z firebase’em. Tutaj skorzystaliśmy z narzędzia znanego
jako NodeRED do pobierania danych udostępnianych przez TTN (w tym przypadku łączyliśmy się
przy pomocy protokołu MQTT do naszej sieci i wychwytywaliśmy wszystkie wiadomości, przesyłane
przez sieć), ich przefiltrowania oraz przekierowywania do bazy danych firebase’u.

Aby móc zwizualizować wyniki w odpowiedni sposób, skorzystaliśmy z języka javascript i frame-
work’u **React Native**, umożliwiającego tworzenie aplikacji natywnych (czyli takich, które mogą
być wykorzystywane na urządzeniach każdego typu, od urządzeń mobilnych do przeglądarek i kompu-
terów stacjonarnych) oraz bibliotek pomocniczych, umożliwiających pobieranie danych z bazy danych,
pokazywanie lokalizacji czujników, tworzenie ścieżek oraz rozpoznawanie lokalizacji użytkownika.

## Wykorzystane technologie 

### W ramach aplikacji mobilnej

- React.JS w wersji 18
- React Native
- Expo

### Wykorzytsane biblioteki

- expo, będącej zestawem narzędzi stworzonych dla React Native, które pomagają w bardzo szybkim
uruchomieniu aplikacji, zawiera ona listę narzędzi, które upraszczają tworzenie i testowanie aplikacji
React Native
- react-redux, będącej zestawem narzędzi, umożliwiających tworzenie, obserwowanie oraz zmianę
danych, przechowywanych wewnątrz aplikacji i pozwalającej na ich wykorzystywanie na dowolnym
poziome zagnieżdżenia komponentów, z których się składa aplikacja
- firebase, będącej zestawem narzędzi umożliwiającym komunikację aplikacji React Native z takim
narzędziem jak firebase (w naszej aplikacji wykorzystywanym do przechowywania danych, pobie-
ranych z czujników)
- react-native-maps, pomagającej na integrację usługi Google Maps z naszą aplikacją, czyli po-
zwalającej wykorzystanie jej map i dopełnień do nich (przykładowo, używanie pinów)
- react-native-maps-directions, pozwalającej na tworzenie ścieżek między dwoma punktami,
zgodnych z istniejącymi ścieżkami znanymi Google Maps
- react-native-geolocation-service, umożliwiającej pobieranie aktualnej geolokalizacji użytkow-
nika (po jego wcześniejszej zgodzie na to)

## Struktura bazy danych

<img width="1000" alt="incz-1" src="https://user-images.githubusercontent.com/62251424/178587090-76293d07-7d92-41b8-a8ec-cfd644c61784.png">

## Rozwiązanie zaprojektowane w Node-RED

<img width="1000" alt="incz-1" src="https://user-images.githubusercontent.com/62251424/178587457-87884e37-2526-47e6-9830-2da80b1eb240.jpg">

## Prototyp czujnika

<img width="1000" alt="incz-1" src="https://user-images.githubusercontent.com/62251424/178587025-432dcb26-f00f-4fa3-9641-cdd8ee92fef6.jpg">

## Widoki aplikacji

<img width="240" alt="incz-1" src="https://user-images.githubusercontent.com/62251424/178586469-01a8c066-204c-4e79-b747-1b5050b0ff57.jpg"> <img width="240" alt="incz-1" src="https://user-images.githubusercontent.com/62251424/178586476-124bdea2-1edf-4828-bcbc-18c9050e12a4.jpg"> <img width="240" alt="incz-1" src="https://user-images.githubusercontent.com/62251424/178586483-2f87a783-c3ed-4f5c-bb2b-7d0ba75d079a.jpg"> <img width="240" alt="incz-1" src="https://user-images.githubusercontent.com/62251424/178586490-5bff336e-ba93-478c-9f16-ad4116b53ab4.jpg">

## Uruchomienie aplikacji mobilnej

```
npm install
expo install
expo start
```
