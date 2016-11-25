
1 - 
-- Faça um programa que crie N threads 
--	(N é um dado de entrada lido do teclado).
-- A primeira thread criada é a "thread01", 
--	a segunda é a "thread02", e assim por diante.
-- Cada thread, quando executar, deverá imprimir na tela 
--	"Eu sou a threadXX e meu ID é YY", 
--	onde YY é o ID que o sistema operacional dá para a thread 
--		(tipo pthread_t, primeiro campo da função pthread_create).
--Explique as saídas do programa quando este é executado. 
--NÃO USE VARIÁVEIS GLOBAIS!!!

--Dica 1: para imprimir uma variável do tipo pthread_t use %u.  
--Dica 2: quando criar uma thread "threadXX", passe este valor como parâmetro para ela.
--Dica 3: pegue a ID da thread usando a função pthread_self().

2 - Tanto pthread_self() quanto gettid() retornam o ID da thread. Altere o programa do exercício 1 para imprimir a ID da thread usando ambas funções. Elas retornam o mesmo valor? Se não, pesquise qual a diferença entre elas.


USAGE:

```
$ make
```

```
$ ./ola_threads
```
or
```
$ ./sushibar
```