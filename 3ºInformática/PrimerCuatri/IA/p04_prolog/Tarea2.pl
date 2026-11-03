pertenece(X, A, B) :- X >= A, X =< B.

#-----------------------------

generado_int(X, Inf, Sup) :-
    X = Inf.

generado_int(X, Inf, Sup) :-
    Inf < Sup,
    Inf1 is Inf + 1,
    generado_int(X, Inf1, Sup).


#------------------------------

mcd(X, A, 0) :- X = A.

mcd(X, A, B) :-
    B \= 0,
    R is A mod B,
    mcd(X, B, R).

mcm(X, A, B) :-
    mcd(M, A, B),
    X is A * B // M.

#--------------------------------

mes(1, 0).  % Enero
mes(2, 3).  % Febrero
mes(3, 3).  % Marzo
mes(4, 6).  % Abril
mes(5, 1).  % Mayo
mes(6, 4).  % Junio
mes(7, 6).  % Julio
mes(8, 2).  % Agosto
mes(9, 5).  % Septiembre
mes(10, 0). % Octubre
mes(11, 3). % Noviembre
mes(12, 12).% Diciembre

dia_numero_nombre(1, lunes).
dia_numero_nombre(2, martes).
dia_numero_nombre(3, miercoles).
dia_numero_nombre(4, jueves).
dia_numero_nombre(5, viernes).
dia_numero_nombre(6, sabado).
dia_numero_nombre(7, domingo).

% Predicado auxiliar para años bisiestos (arimética con =:=)
es_bisiesto(A) :-
    ( A mod 400 =:= 0 -> true
    ; A mod 100 =:= 0 -> false
    ; A mod 4   =:= 0 -> true
    ; false ).

dia_semana(D, M, A, X) :-
    % 1. Siglos
    Siglo is A // 100,
    AnoSiglo is A mod 100,
    RestoDiv4 is Siglo mod 4,

    % Reforma Gregoriana
    ((A < 1752 ; (A =:= 1752, M < 9) ; (A =:= 1752, M =:= 9, D < 14)) -> 
    	Minuendo = 18; 
    	Minuendo = 3),
	
    RestaMin is (Minuendo - RestoDiv4) mod 7,
    Mult2 is RestaMin * 2,

    % 2. El año
    ADiv12 is AnoSiglo // 12,
    RDiv12  is AnoSiglo mod 12,
    Num4s   is RDiv12 // 4,
    SumAno  is (ADiv12 + RDiv12 + Num4s) mod 7,
    SumAnoFinal is (SumAno + Mult2) mod 7,

    % 3. El mes
    mes(M, MesVal),
    SumaMes is (MesVal + SumAnoFinal) mod 7,

    % 4. El día
    DiaMod7 is D mod 7,
    SumaDiaTemp is (DiaMod7 + SumaMes) mod 7,

    (SumaDiaTemp =:= 0 -> SumaDia1 = 7 ; SumaDia1 = SumaDiaTemp ),

    % Ajuste bisiestos
    (es_bisiesto(A), (M =:= 1 ; M =:= 2) ->
        (SumaDia1 =:= 1 -> SumaDiaFinal = 7 ; SumaDiaFinal is SumaDia1 - 1 );
        SumaDiaFinal = SumaDia1),

    (SumaDiaFinal =:= 0 -> SumaDiaFinal2 = 7 ; SumaDiaFinal2 = SumaDiaFinal ),

    % Asignar átomo al día
    dia_numero_nombre(SumaDiaFinal2, X).