### Threads e Exclusão Mútua
---
#### Sushi Bar Problem

Descrição do Trabalho

1. Exercicio 1
   
   Faça um programa que crie N threads (N é um dado de entrada lido do teclado). A primeira thread criada é a "thread01", a segunda é a "thread02", e assim por diante. Cada thread, quando executar, deverá imprimir na tela
   > "Eu sou a threadXX e meu ID é YY",

   onde YY é o ID que o sistema operacional dá para a thread (tipo pthread_t, primeiro campo da função pthread_create). Explique as saídas do programa quando este é executado.
   
   Tanto pthread_self() quanto gettid() retornam o ID da thread. Altere o programa [...] para imprimir a ID da thread usando ambas funções. Elas retornam o mesmo valor? Se não, pesquise qual a diferença entre elas.
   
   **NÃO USE VARIÁVEIS GLOBAIS!!!**
   
2. Exercício 2 - Sushi Bar Problem
   
   Trecho retirado do livro [The Little Book of Semaphores](http://greenteapress.com/wp/semaphores/), cap 7, 7.1 - The Sushi Bar Problem
   
   > This problem was inspired by a problem proposed by Kenneth Reek. Imagine
a sushi bar with 5 seats. If you arrive while there is an empty seat, you can take
a seat immediately. But if you arrive when all 5 seats are full, that means that
all of them are dining together, and you will have to wait for the entire party
to leave before you sit down.
 
&nbsp;

---

#### Usage:
```
$ make
```
```
$ ./ola_threads
```
_or_
```
$ ./sushibar
```
