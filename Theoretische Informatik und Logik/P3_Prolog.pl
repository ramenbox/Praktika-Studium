% Aufgabe 1 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%-- prefix --
% prefix(Xs, Ys) : Xs ist präfix von Ys.
% Fall 0: Liste Xs hat nur ein Element.
prefix([X], [X|Ys]).
% Fall 1: Liste Xs hat beliebige Elemente.
% Es werden X Elemente von Liste Xs vorne an Ys angehängt.
prefix([X|Xs], [X|Ys]) :- prefix(Xs, Ys).

%-- postfix -- 
% postfix(Xs, Ys) : Ys endet mit der Liste Xs.
% Xs2 ist wiedergespiegelte Liste von Xs und ist prefix von Ys2 ist und Ys2 ist wiedergespiegelte Liste von Ys.
% mit reverse
postfix(Xs, Ys) :- reverse(Xs, Xs2), prefix(Xs2, Ys2), reverse(Ys, Ys2).

% postfix durch in Prolog deifiniertes Prädikats append realisiert.
% Füge Xs hinten an einer Liste
postfix2(Xs, Ys) :- append(_, Xs, Ys).

% Aufgabe 2 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%-- binbaum -- 
binbaum(empty).
binbaum(node(_, Lb, Rb)) :- binbaum(Lb), binbaum(Rb).

%-- Membertree --
% membertree(X, Xb) : Baum Xb enthält den Eintrag X.
% Fall 0: Element X ist im Knoten.
membertree(X, node(X, Lb, Rb)) :- binbaum(Lb), binbaum(Rb).
% Fall 1: Element X ist entweder im linkem Teilbaum.
membertree(X, node(_, Lb, Rb)) :- membertree(X, Lb).
% Fall 2: Oder ist im rechtem Teilbaum.
membertree(X, node(_, Lb, Rb)) :- membertree(X, Rb).

% Aufgabe 3 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%-- Präorder -- 
% präorder(Xb, Ys) : Ys ist die Liste der Knotenbeschriftungen des Binärbaumes Xb in Präorder.
% Fall 0: Baum ist leer.
preorder(empty, []).
% Fall 1: Baum hat 2 Nachfolgerbäume.
% Wurzel, Links, Rechts
preorder(node(X, Lb, Rb), [X|Ys]) :- preorder(Lb, LYs), preorder(Rb, RYs), append(LYs, RYs, Ys), binbaum(Lb), binbaum(Rb).

%-- Postorder --
% postorder(Xb, Ys) : Ys ist die Liste der Knotenbeschriftungen des Binärbaumes Xb in Postorder.
% Fall 0: Baum ist leer.
postorder(empty, []).
% Fall 1: Baum hat 2 Nachfolgerbäume.
% Links, Rechts, Wurzel
postorder(node(X, Lb, Rb), Ys) :- postorder(Lb, LYs), postorder(Rb, RYs), append(LYs, RYs, Ys1), append(Ys1, [X], Ys).

%-- Roots --
% roots(Xbs, Ys) : Xbs ist eine Liste von Binärbäumen (geschachtelte Induktion).
% Die Liste Ys ist die Liste der Wurzelbeschriftungen der Binärbäume in Xbs in der richtigen Reihenfolge.
% Beachten Sie, dass ein leerer Binärbaum keine Wurzelbeschriftung hat
% und diese somit auch nicht aufgeführt wird.
% Fall 0: Xbs ist eine leere Liste (also keine Wurzelbeschriftung).
roots([],[]).
% Fall 1: Leerer Binärbaum ist keine Wurzelbeschriftung
roots([empty|Xbs], Ys) :- roots(Xbs, Ys).
% Fall 2: Xbs enthält Binärbäume als Element
roots([node(X, Lb, Rb)|Xbs], [X|Ys]) :- roots(Xbs,Ys).

/*
Tree* smallTree = new Tree();
Tree* bigTree = new Tree();
bigTree.add_node("a");

Tree* hugeTree = new Tree();
hugeTree.add_node("1");
hugeTree.add_node("2");

std::vector<Tree*> liste_tree;

liste_tree.push(smallTree, bigTree, hugeTree);
*/