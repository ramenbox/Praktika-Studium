% Praktikum 5

% zustand(X): X ist ein Zustand.
zustand(z0).

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

% Palin-Bin
%1.Fall: Terminalsymbol auf Stackspitze (löschen, epsilon):
delta(z0, 0, 0, z0, []).
delta(z0, 1, 1, z0, []).

%2.Fall: Variable auf Stackspitze (Regel, Übergang):
delta(z0, nix, #, z0, []).
delta(z0, nix, #, z0, [0]).
delta(z0, nix, #, z0, [1]).
delta(z0, nix, #, z0, [0,#,0]).
delta(z0, nix, #, z0, [1,#,1]).

% sigma_stern(Xs): Xs ist in der Menge der Worte ueber dem Sigma
sigma_stern([]).
sigma_stern([W|Ws]) :- sigma(W), sigma_stern(Ws).

% es: Einzelschrittrelation
es(Z, [W|Ws], [Top|Stack], Zneu, Ws, StackNeu) :- delta(Z, W, Top, Zneu, StackAdd), append(StackAdd, Stack, StackNeu).
es(Z, Ws, [Top|Stack], Zneu, Ws, StackNeu) :- delta(Z, nix, Top, Zneu, StackAdd), append(StackAdd, Stack, StackNeu).

% es_plus: Transitiver Abschluss der Einzelschrittrelation
% Z zu Z_1, zu Z_N
es_plus(Z, Ws, Stack, Z_N, Ws_N, Stack_N) :- es(Z, Ws, Stack, Z_N, Ws_N, Stack_N).
es_plus(Z, Ws, Stack, Z_N, Ws_N, Stack_N) :- es(Z, Ws, Stack, Z_1, Ws_1, Stack_1), es_plus(Z_1, Ws_1, Stack_1, Z_N, Ws_N, Stack_N).

% lvonM(Ws): Ws ist in der Sprache L von M. - Vom Startzustand in Epsilon kommen um gültig
lvonM(Ws) :- sigma_stern(Ws), start(X), zustand(Y), boden(K), es_plus(X, Ws, [K], Y, [], []).