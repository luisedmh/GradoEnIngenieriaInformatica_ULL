min_lista([X], X).

min_lista([H|T], H) :-
    min_lista(T, Mcola),
    H < Mcola.

min_lista([H|T], Mcola) :-
    min_lista(T, Mcola),
    H >= Mcola.

#------------------------

cuadrado([], []).

cuadrado([H1|T1], [H2|T2]) :-
    H2 is H1 * H1,
    cuadrado(T1, T2).

#--------------------------

entrelaza([], [], []).

entrelaza([H1|T1], [H2|T2], [H1,H2|T3]) :-
    entrelaza(T1, T2, T3).

#--------------------------------

comienza([], _).
comienza([H|T1], [H|T2]) :-
    comienza(T1, T2).

subtramo(L1, L2) :-
    comienza(L1, L2).

subtramo(L1, [_|T2]) :-
    subtramo(L1, T2).

#----------------------------

previo(X, Y, [X|T]) :-
    miembro(Y, T).

previo(X, Y, [_|T]) :-
    previo(X, Y, T).

miembro(Y, [Y|_]).
miembro(Y, [_|T]) :-
    miembro(Y, T).

#-------------------------------

aplana([], []).

aplana([H|T], L2) :-
    islist(H),
    aplana(H, H2),
    aplana(T, T2),
    unir(H2, T2, L2).

aplana([H|T], [H|T2]) :-
    \+ islist(H),
    aplana(T, T2).

unir([], L, L).
unir([X|L1], L2, [X|L12]) :-
    unir(L1, L2, L12).

islist([]).
islist([_|_]).