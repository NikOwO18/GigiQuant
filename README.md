# GigiQuant - Portfolio Manager Simulation

Proiect în C structurat sub forma unei serii de interviuri tehnice pentru poziția de *Manager de Portofoliu*. Acesta rezolvă probleme financiare concrete folosind structuri de date dinamice.

## Task-uri și Structuri de Date

1. **Sharpe Ratio (Evaluare Performanță):** Calculează rentabilitatea unui portofoliu raportată la risc.
   * *Structură:* Listă simplu înlănțuită (`Node`).
2. **Arbitraj (Oportunități de trading):** Identifică diferențele de preț pentru un activ pe 3 piețe diferite.
   * *Structură:* Stive (`Node2`) pentru procesarea prețurilor și Cozi (`Queue`) pentru stocarea oportunităților.
3. **Diversificarea Portofoliului (Hedging):** Corelează acțiuni cu evoluții complet opuse (în oglindă) pentru reducerea riscului.
   * *Structură:* Arbore binar de căutare (`Node3` / `TreeNode`).
4. **Lanțuri Markov (Predicție):** Calculează probabilitatea exactă (ca fracție ireductibilă) ca o acțiune să ajungă la un preț țintă în $K$ zile.
   * *Structură:* Graf orientat reprezentat prin stări/intervale (`Markov`).

## Structura Fișierelor
* main.c` - Controlul fluxului, citirea argumentelor și gestionarea I/O.
* lib.h` - Definițiile structurilor (`Node`, `Queue`, `TreeNode`, `Fr` etc.) și prototipurile funcțiilor.
* lib.c` - Implementarea algoritmilor și managementul memoriei.

# Compilare (necesită -lm pentru math.h)
gcc main.c lib.c -lm
