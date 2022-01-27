% Praktikum 5

% zustand(X): X ist ein Zustand.
zustand(z0).
%zustand(z1).

% sigma(X): X ist im Alphabet.
sigma(0).
sigma(1).

% gamma(X): X ist im Kelleralphabet.
gamma(#).
gamma(0).
gamma(1).

% start(X): X ist ein Startzustand.
start(z0).

% boden(X): X ist Kellerboden.
boden(#).
%boden(vA).

/*
%Notlösung - Palin-Bin
%1.Fall: Terminalsymbol auf Stackspitze (löschen, epsilon):
delta(z0, 0, 0, z0, []).
delta(z0, 1, 1, z0, []).

%2.Fall: Variable auf Stackspitze (Regel, Übergang):
delta(z0, nix, #, z0, []).
delta(z0, nix, #, z0, [0]).
delta(z0, nix, #, z0, [1]).
delta(z0, nix, #, z0, [0,#,0]).
delta(z0, nix, #, z0, [1,#,1]).
*/

% Startsymbol S
% P = { 
        %S -> 0S,
        %S -> 1S,
        %S -> 01
%      }

%Typ-2
%Löschen
delta(z0, 0, 0, z0, []).
delta(z0, 1, 1, z0, []).

%Regel - Übergang
%delta(z0, nix, #, z0, []). %Wenn Kellersymbol, löschen
delta(z0, nix, #, z0, [0,#]).
delta(z0, nix, #, z0, [1,#]).
delta(z0, nix, #, z0, [0,1]). %Ende

% Startsymbol S
% P = { 
        %S -> 0S
        %S -> 1S
        %S -> 0A
        %A -> 1
%      }
/*
%Typ-3
%Löschen
delta(z0, 0, 0, z0, []).
delta(z0, 1, 1, z0, []).
delta(z1, 0, 0, z1, []).
delta(z1, 1, 1, z1, []).

%Übergang - Regel
%delta(z0,nix,#,z0,[]).
delta(z0,nix,#,z0,[0,#]).
delta(z0,nix,#,z0,[1,#]).
delta(z0,nix,#,z1,[0,vA]).
delta(z1,nix,vA,z1,[1]). 
*/

% sigma_stern(Xs): Xs ist in der Menge der Worte ueber dem Sigma
sigma_stern([]).
sigma_stern([W|Ws]) :- sigma(W), sigma_stern(Ws).

% es: Einzelschrittrelation
es(Z, [W|Ws], [Top|Stack], Zneu, Ws, StackNeu) :- delta(Z, W, Top, Zneu, StackAdd), append(StackAdd, Stack, StackNeu).
es(Z, Ws, [Top|Stack], Zneu, Ws, StackNeu) :- delta(Z, nix, Top, Zneu, StackAdd), append(StackAdd, Stack, StackNeu).

% es_plus: Transitiver Abschluss der Einzelschrittrelation
es_plus(Z, Ws, Stack, Z_N, Ws_N, Stack_N) :- es(Z, Ws, Stack, Z_N, Ws_N, Stack_N).
es_plus(Z, Ws, Stack, Z_N, Ws_N, Stack_N) :- es(Z, Ws, Stack, Z_1, Ws_1, Stack_1), es_plus(Z_1, Ws_1, Stack_1, Z_N, Ws_N, Stack_N).

% lvonM(Ws): Ws ist in der Sprache L von M. - Vom Startzustand in Epsilon kommen um gültig
%lvonM(Ws) :- sigma_stern(Ws), es_plus(z0, Ws, [K], Y, [], []).
lvonM(Ws) :- sigma_stern(Ws), start(X), zustand(Y), boden(K), es_plus(X, Ws, [K], Y, [], []).