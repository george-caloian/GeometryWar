Sectiunea 1

Nume : Caloian George
Grupa : 332
Seria CC


======================================================


Sectiunea 2 - Utilizare aplicatie

5 butoane dupa cum urmeaza:
tasta W - deplasare nava in sus
tasta A - deplasare nava spre stanga
tasta D - deplasare nava spre dreapta
tasta S - deplasare nava in jos
Buton stanga mouse - lansare proiectil/glont

+Nava se roteste in functie de cursor

Alte observatii:
Rulare fara parametrii
Nu sunt folosite fisiere de intrare/iesire
Nu se afiseaza nimic in consola


======================================================


Sectiunea 3 - Detalii de implementare

Mediu de dezvoltare : Visual Studio 2015 Comunity
Framework : cel pus la dispozitie in cadrul laboratorului
	(s-a plecat de la laboratorul 3)
OS: Windows 7

Principiu general:

Utilizatorul controleaza nava player incercand sa reziste
cat mai mult timp atacurilor inamice.
Navele inamice apar succesiv la un interva de timp ce scade
treptat de la 2s la 0.5s.
Navele inamice se deplaseaza direct spre nava player
actualizandu-si mereu directia de deplasare in functie de
pozitia navei player.
Nava player poate lansa gloante/proiectile in directia navelor
inamice pentru a le distruge.

Structuri:

S-a folosit cate o sctructura pentru navele inamice si pentru
proiectil/glont.

Evenimente tratate:

coliziune inamic-glont : atat inamicul cat si glontul dispar
coliziune inamic-player : inamicul dispare iar numarul de vieti
al navei player ete decrementat fapt vizibil pentru utilizator
prin afisarea in dreapta sus a numarului curent de vieti ilustrat
prin dreptunghiuri asezate vertical.

Jocul se incheie cand nava player isi pierde toate cele 3 vieti


======================================================


Sectiunea 4 : Probleme aparute

Necitirea cu mare atentie a cerintei a cauzat ambiguitate cu privire 
la cele 2 tipuri de coliziuni crezand initial ca este nevoie 
tratarea in detaliu a acestora - mai exact tratarea cazului in care nava
inamica ajunge in "gaura" ilustrata de punct ( |>.<| ) 

Problema la coliziuni in ceea ce priveste eliminarea proiectilului 
cand se lansa un numar mare de proiectile, problema cauzata de
neverificarea depasirii cu indicele de iteratie a numarului de proiectile

Pe langa acestea Rotirea navei dupa mouse si deplasarea navelor inamice
in directia navei player constituie o proportie mare a timpului de
implementare, restul detaliilor fiind ceva mai accesibile.


======================================================


Sectiunea 5 - Continutul arhivei

Arhiva nu contine fisiere speciale


======================================================


Sectiunea 6 - Status implementare functionalitati si descriere bonus

Nu exista cel putin la data redactarii acestui document.


Sectiune Suplimentara

Tema a fost uploadata cu 1 zi de intarziere
fapt ce trebuie sa atraga o penalizare de 0.25p

Resurse suplimentare:
Anumite concepte in special cele trigonometrice si anumite neintelegeri
legate de functionalitatea unor elemente din framework
au fost mai mult sau mai putin dezbatute cu ceilalti studenti in 
pauze sau "ferestre" dintre cursuri putand fii catalogat ca un
oarecare suport.
Am urmarit de asemenea prezentari in format video (youtube) ale
altor jocuri din cadrul carora implementarea elementelor legate de 
fizica (precum inertia obiectelor) mi s-a aprut cel mai interesant aspect.
