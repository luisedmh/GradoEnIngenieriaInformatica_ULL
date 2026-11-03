invertir(L1, L2) :-
    invertir_acc(L1, [], L2).

invertir_acc([], Acc, Acc).
invertir_acc([X|Xs], Acc, L2) :-
    invertir_acc(Xs, [X|Acc], L2).

#-------------------------------

suma([], 0).
suma([X|Xs], S) :-
    suma(Xs, S1),
    S is X + S1.

suma_acc(L, S) :-
    suma_acc_aux(L, 0, S).

suma_acc_aux([], Acc, Acc).
suma_acc_aux([X|Xs], Acc, S) :-
    Acc1 is Acc + X,
    suma_acc_aux(Xs, Acc1, S).

#---------------------------------

hanoi(N, L) :-
    hanoi(N, 1, 3, 2, L).

hanoi(0, _, _, _, []) :- !.
hanoi(N, A, C, B, L) :-
    N > 0,
    N1 is N - 1,
    hanoi(N1, A, B, C, L1),
    hanoi(N1, B, C, A, L3),
    append(L1, [mover(A, C)|L3], L).

hanoi_acc(N, L) :-
    hanoi_acc(N, 1, 3, 2, [], L).

hanoi_acc(0, _, _, _, Acc, Acc).
hanoi_acc(N, A, C, B, Acc, L) :-
    N > 0,
    N1 is N - 1,
    hanoi_acc(N1, A, B, C, Acc, L1),
    L2 = [mover(A, C) | L1],
    hanoi_acc(N1, B, C, A, L2, L).

hanoi_dif(N, L) :-
    hanoi_dif(N, 1, 3, 2, L-[]).

hanoi_dif(0, _, _, _, L-L).
hanoi_dif(N, A, C, B, L0-LF) :-
    N > 0,
    N1 is N - 1,
    hanoi_dif(N1, A, B, C, L0-L1),
    L1 = [mover(A, C)|L2],
    hanoi_dif(N1, B, C, A, L2-LF).