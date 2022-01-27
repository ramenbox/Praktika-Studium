%lineare Liste ist leer
linListe(nil).
%linListe(list(X, Xs)) :- Xs ist eine Liste entweder mit beliebigen Einträgen oder ist leer.
linListe(list(X, Xs)) :- linListe(Xs).

% app (Xs, Ys, Rs) :- Liste Rs = Anhängen der Liste Ys an die Liste Xs / app = append
%Rs = Ys bei Xs = nil.
app(nil, Ys, Ys).
% Xs und Ys sind Listen mit beliebigen Elementen
% app(list(X, Xs), Ys, list(X, Rs)) :- Xs + Ys = Rs (Element X aus Liste Xs angehängt an Liste Rs)
app(list(X, Xs), Ys, list(X, Rs)) :- app(Xs, Ys, Rs).

% member(X, Ys) :- Liste Ys enthält Element X
% member(X, list(X, Ys)) :- X ist in list(X, Ys)
member(X, list(X, Ys)) :- linListe(Ys).
% member(X, list(Y, Ys)) :- X ist in ein Element in der restlichen liste von Ys
member(X, list(Y, Ys)) :- member(X, Ys), linListe(Ys).


/*
%infix(Xs,Xs) :- linListe(Xs).
% Xs ist anfang
infix(Xs, Ys) :- app(Xs, _, Ys).
% Xs ist ende
infix(Xs, Ys) :- app(_, Xs, Ys).
% Xs ist in der mitte
infix(Xs, list(Y,Ys)) :- infix(Xs, Ys).
*/

infix(Xs,Ys) :- app(_, Xs, Rs), app(Rs, _ , Ys).


% attach(Xs, X, Ys) :- Liste Ys ist Liste Xs verlängert um das Element X,hinzufügen
% Element X wird am Ende der Liste Xs angehängt.
attach(Xs, X, Ys) :- app(Xs, list(X, nil), Ys).

% rev(Xs, Ys) : Liste Ys ist die gespiegelte Liste Xs.
%Basisfall: Liste am Ende
rev(nil, nil).
%Liste muss traversiert werden
% rev(list(X, Xs), Ys) : Element X von Liste Xs wird am Ende appendiert
rev(list(X, Xs), Ys) :- rev(Xs, Rs), attach(Rs, X, Ys).



% Datenstruktur desBinärbaum
%Binärbaum ist leer.
binBaum(e).
%Binärbaum hat 2 Nachfolgerbäume und bei jeden Knoten einen Eintrag.
binBaum(node(Root, Lb, Rb)) :- binBaum(Lb), binBaum(Rb).

% construct(Root, Lb, Rb, Xneub) :- Xneub ist
%                                  - Wurzelbeschriftung = Root
%                                  - linkem Teilbaum (Lb)
%                                  - rechtem Teilbaum (Rb)
construct(Root, Lb, Rb, node(Root, Lb, Rb)) :- binBaum(Lb), binBaum(Rb).

% natSymb(X) :- X ist natürliche Zahl in symbolischer Darstellung
natSymb(o).
natSymb(s(X)) :- natSymb(X).

% add(X, Y, R) :- R = X+Y, symbolische Darstellung
add(o, X, X).
% add(s(X), Y, s(R)) :- (X+1)+Y = R+1
add(s(X), Y, s(R)) :- add(X, Y, R).

% knotenanz(Xb, N) :- N (nat. Zahl in symbolischer Darstellung) ist
% Anzahl der Knoten des Baumes (Xb)
%An der Wurzel:
knotenanz(e, o).
% knotenanz(node(Root, Lb, Rb), s(N)) :- traversiere Linken Teilbaum und addiere 1 zu LN (+1)
%                                       traversiere Rechten Teilbaum und addiere 1 zu RN (+1)
%                                       N = LN+RN.
knotenanz(node(Root, Lb, Rb), s(N)) :- knotenanz(Lb, LN), knotenanz(Rb, RN), add(LN, RN, N).