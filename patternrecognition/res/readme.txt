/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150		0,050		0,008
    200		0,122		0,048
    300		0,340		0,066
    400		0,833		0,077
    800		5,858		0,244
   1600		46,997		0,974
   3200		ca 500		4,344
   6400		ca 75000	15,884
  12800		ca 1000000	67,611


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4) �r den v�rstafallstiden (i komplexitet) d� den best�r utav 4 n�stlade 'for'-loopar som itererar igenom hela punktlistan. 

Sortering: O(n^2 * log2(n)) �r v�rstafallstiden (i komplexitet) d� 'sort' funktionen har en komplexitet p� N*log2(N) och vi kommer att k�ra den N antal g�nger i 'while'-loopen.
