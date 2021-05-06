# PROIECT 3

## Cerințe comune tuturor temelor:
1. utilizarea sabloanelor  <br>
2. utilizarea STL  <br>
3. utilizarea variabilelor, funcțiilor statice, constantelor și a unei functii const  <br>
4. utilizarea conceptelor de RTTI raportat la templat-uri (ex: upcast & dynamic_cast)  <br>
5. tratarea excepțiilor  <br> 
6. citirea informațiilor complete a n obiecte, memorarea și afișarea acest ora  <br>

<b>Cerințe generale aplicate fiecărei teme: </b> <br>
- să se identifice și să se implementeze ierarhia de clase;  <br>
- clasele să conțină constructori, destructori, =, supraincarcare pe >> si << pentru citire si 
afisare;  <br>
- clasa de baza sa conțină funcție virtuala de afisare si citire, rescrisa în clasele derivate, iar 
operatorul de citire si afisare să fie implementat ca funcție prieten (în clasele derivate să 
se facă referire la implementarea acestuia în clasa de baza).  <br>


## Cerinte specifice fiecarei teme:
### Tema 6. 
Se dorește implementarea unei aplicații OOP care sa permita gestionarea activității 
unor farmacii apartinand proprietarului X. Pentru fiecare farmacie se cunoaște cel puțin 
denumirea, numărul de angajați și profiturile pe fiecare luna. Farmaciile pot fi și online. În 
acest caz se cunoaște doar adresa web, numărul de vizitatori și discountul utilizat.
Structura de date: vector sau list <tuple<web, nr_vizitatori, discount>> se rețin farmaciile 
online<br><br>

<b>Cerința suplimentară: </b><br>
- Să se adauge toate campurile relevante pentru modelarea acestei probleme.<br>
- Să se construiască clasa template GestionareFarmacii care sa conțină informații despre 
diversele tipuri de farmacii. Clasa conține indexul farmaciei (incrementat automat la 
adaugarea unei noi file), id-ul lanțului (constant) și o structura de obiecte, alocată dinamic. Sa 
se supraincarce operatorul += pentru inserarea unei noi farmacii online în structura.<br>
- Să se construiască o specializare pentru tipul Farmacie_online care sa conțină și să afișeze 
doar numărul total de vizitatori ai farmaciilor online.<br>
