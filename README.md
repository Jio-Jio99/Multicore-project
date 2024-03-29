# Multicore-project
Programming in C for system embeded and multicore
## PROGETTO 1
### Implementazione di algoritmi paralleli per string matching

Dato un insieme di stringhe S ed uno stream di pacchetti di dati (pacchetti contenenti traffico di rete
tipo TCP/UDP) T controllare se all’interno dei pacchetti è presente una delle stringhe di S. Utilizzare
almeno uno tra gli algoritmi Knuth-Morris-Pratt ed Aho-Corasick.

Realizzare sia un’implementazione che utilizza un sistema a memoria distribuita MPI e sia
un’implementazione che utilizza OpenMP.

Oltre a verificare la correttezza degli algoritmi implementati (ad esempio confrontando i risultati
con quelli ottenuti da una versione single-thread), valutare le prestazioni degli algoritmi sviluppati
in termini di Speed-up ed efficienza al variare del numero di thread e delle dimensioni del problema
(numero stringhe di S o numero di pacchetti di T).

La consegna del progetto (almeno una settimana prima dell’orale) consiste in:
(a) tutti i sorgenti (opportunamente commentati) necessari per il funzionamento;
(b) Una relazione contenente:
- La descrizione dettagliata dell’architettura dell’applicazione e delle scelte progettuali effettuate,
opportunamente motivate.
- La descrizione delle eventuali limitazioni riscontrate;
- I risultati in termini di prestazioni opportunamente commentati;
Il giorno dell’orale è necessario preparare una presentazione powerpoint ed una demo del progetto.

## TODO LIST:
* Il programma in MPI è da finire, poiché funziona solo su una macchina. (Da aggiungere le funzioni di invio dei dati)
