hijo(X, Y) :- masculino(X), progenitor(Y, X).
hija(X, Y) :- femenino(X), progenitor(Y, X).
nieto(X, Z) :- masculino(X), progenitor(Y, X), progenitor(Z, Y).
nieta(X, Z) :- femenino(X), progenitor(Y, X), progenitor(Z, Y).


#-------------------------------------------------------------

#Si intentamos definir estas relaciones solo con progenitor/2 y la conjunción, obtendríamos algo como:

hermano(X,Y) :- masculino(X), progenitor(P,X), progenitor(P,Y).

#Pero con esto Prolog también diría que una persona es hermano de sí misma, porque todavía no sabemos expresar desigualdad (X \= Y). Esa herramienta aún no se ha visto en el temario. Ocurre lo mismo con sobrino y primo, por ejemplo:

primo(A,B) :- progenitor(P,A), progenitor(Q,B), progenitor(G,P), progenitor(G,Q).

#De nuevo, no podemos impedir que P = Q o que A = B.

#Además, para algunos casos haría falta expresar una “o” lógica (por ejemplo, compartir padre o madre), lo cual requiere disyunción (;), que tampoco ha sido explicada aún.

#Por eso, aunque podemos intuir las relaciones, no podemos definirlas correctamente todavía porque faltan dos cosas que aún no forman parte del temario: desigualdad y disyunción.