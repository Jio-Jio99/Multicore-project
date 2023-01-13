# Multicore-project
Programming in C for system embeded and multicore

                                                PROGETTO 1
                          Implementazione di algoritmi paralleli per string matching

Dato un insieme di stringhe S ed uno stream di pacchetti di dati (pacchetti contenenti traffico di rete
tipo TCP/UDP) T controllare se all’interno dei pacchetti è presente una delle stringhe di S. Utilizzare
almeno uno tra gli algoritmi Knuth-Morris-Pratt ed Aho-Corasick.

Realizzare sia un’implementazione che utilizza un sistema a memoria distribuita MPI e sia
un’implementazione che utilizza OpenMP.

Oltre a verificare la correttezza degli algoritmi implementati (ad esempio confrontando i risultati
con quelli ottenuti da una versione single-thread), valutare le prestazioni degli algoritmi sviluppati
in termini di Speed-up ed efficienza al variare del numero di thread e delle dimensioni del problema
(numero stringhe di S o numero di pacchetti di T).

Il progetto è dimensionato per essere realizzato da un gruppo composto da due studenti.

La consegna del progetto (almeno una settimana prima dell’orale) consiste in:
(a) tutti i sorgenti (opportunamente commentati) necessari per il funzionamento;
(b) Una relazione contenente:
- La descrizione dettagliata dell’architettura dell’applicazione e delle scelte progettuali effettuate,
opportunamente motivate.
- La descrizione delle eventuali limitazioni riscontrate;
- I risultati in termini di prestazioni opportunamente commentati;
Il giorno dell’orale è necessario preparare una presentazione powerpoint ed una demo del progetto.

      TODO LIST:
  - Scelta algoritmo: Knuth-Morris-Pratt: http://www.dacrema.com/Informatica/Algoritmo_Knuth_Morris.htm (FATTO)
  - Realizzazione con il seriale: https://www.sanfoundry.com/c-program-implement-knuth-morris-pratt-algorithm-string-matching/ (FATTO)
  - Realizzazione con MPI;
  - Realizzazione con OpenMPI (slide 13-16) (FATTO)
  - Fixare la funzione SpltString che con l'assertion non funziona su testi grandi
