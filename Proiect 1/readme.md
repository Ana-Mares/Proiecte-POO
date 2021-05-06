# PROIECT 1

## Cerinte comune tuturor temelor:
• implementare in C++ folosind clase <br>
• datele membre private <br>
• ATENTIE: functiile pe care le-am numit mai jos metode (fie ca sunt supraincarcari de 
operatori, fie altfel de functii), pot fi implementate ca functii prieten in loc de metode ale claselor 
respective, daca se considera ca aceasta alegere este mai naturala; <br>
• supraincarcarea operatorilor << si >> pentru iesiri si intrari de obiecte, dupa indicatiile de 
mai jos, astfel incat sa fie permise (si ilustrate in program): <br>
• sa existe o metoda publica prin care se realizeaza citirea informațiilor complete a n obiecte, 
memorarea și afisarea acestora. <br>
• programul sa aiba un meniu interactiv <br>

## Cerinte specifice fiecarei teme:
### Tema 11.
Clasa ”Polinom_dinamic” - reprezentat ca lista inlantuita (ca polinoame rare, prin lista 
perechilor (coeficient,exponent), ordonata crescator dupa exponent, si nu neaparat cu exponentii 
consecutivi. <br>
Cerintele sunt aceleași ca la <b>Tema 10</b>, adaptate pentru liste alocate dinamic.  <br>

### Tema 10. 
Clasa ”Polinom” - reprezentat ca tablou unidimensional (prin gradul polinomului si 
vectorul coeficientilor (coeficientii vor apartine la monoame de grade consecutive), de dimensiune 
egala cu gradul plus 1, de la cel al termenului liber la cel de grad maxim. <br>
- fiecare coeficient va fi de tip double; <br>
- membri privati pentru vectorul propriuzis si numarul de elemente; <br>
 - constructori pentru initializare si copiere; <br>
- destructor (în cazul alocarii statice, se seteaza dimensiunea vectorului la zero, iar în cazul 
alocarii dinamice, se dezaloca zona de memorie utilizata); <br>
- metoda publica pentru calculul valorii unui polinom intr-un punct; <br>
- suma a doua polinoame, implementata prin supraincarcarea operatorului +; <br>
- diferenta a doua polinoame, implementata prin supraincarcarea operatorului -;- produsul a doua polinoame, implementat prin supraincarcarea operatorului *; <br>
