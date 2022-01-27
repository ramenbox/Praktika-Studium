%Grossvater
elternteil(abraham,herb).
elternteil(abraham,homer).

elternteil(clancy,marge).
elternteil(clancy,patty).
elternteil(clancy,selma).

%Grossmutter
elternteil(mona,herb).
elternteil(mona,homer).

elternteil(jackie,marge).
elternteil(jackie,patty).
elternteil(jackie,selma).

%Vater
elternteil(homer,bart).
elternteil(homer,lisa).
elternteil(homer,maggie).

%Mutter
elternteil(marge,bart).
elternteil(marge,lisa).
elternteil(marge,maggie).

elternteil(selma,ling).

%Geschwister
geschwisternteil(herb,homer).
geschwisternteil(homer,herb).

geschwisternteil(marge,patty).
geschwisternteil(marge,selma).
geschwisternteil(patty,marge).
geschwisternteil(patty,selma).
geschwisternteil(selma,marge).
geschwisternteil(selma,patty).

geschwisternteil(bart,lisa).
geschwisternteil(bart,maggie).
geschwisternteil(lisa,bart).
geschwisternteil(lisa,maggie).
geschwisternteil(maggie,bart).
geschwisternteil(maggie,lisa).

%Maennlich
maennlich(abraham).
maennlich(clancy).
maennlich(herb).
maennlich(homer).
maennlich(bart).

%Weiblich
weiblich(mona).
weiblich(jackie).
weiblich(marge).
weiblich(patty).
weiblich(selma).
weiblich(lisa).
weiblich(maggie).
weiblich(ling).

vater(ZVater,ZKind):- elternteil(ZVater,ZKind), maennlich(ZVater).
mutter(ZMutter,ZKind):- elternteil(ZMutter,ZKind), weiblich(ZMutter).

sohn(ZKind,ZElternteil):- elternteil(ZElternteil,ZKind), maennlich(ZKind).
tochter(ZKind,ZElternteil):- elternteil(ZElternteil,ZKind), weiblich(ZKind).

grossvater(ZGrossvater,ZKind):- elternteil(ZGrossvater,ZX), elternteil(ZX,ZKind), maennlich(ZGrossvater).
grossmutter(ZGrossmutter,ZKind):- elternteil(ZGrossmutter,ZX), elternteil(ZX,ZKind), weiblich(ZGrossmutter).

cousine(ZCousine,ZKind):- elternteil(ZElternteil1,ZCousine), elternteil(ZElternteil,ZKind), geschwisternteil(ZElternteil1,ZElternteil), weiblich(ZCousine).
cousin(ZCousin,ZKind):- elternteil(ZElternteil1,ZCousin), elternteil(ZElternteil,ZKind), geschwisternteil(ZElternteil1,ZElternteil), maennlich(ZCousin).

onkel(ZOnkel,ZKind):- elternteil(ZElternteil,ZKind), geschwisternteil(ZElternteil,ZOnkel), maennlich(ZOnkel).
tante(ZTante,ZKind):- elternteil(ZElternteil,ZKind), geschwisternteil(ZElternteil,ZTante), weiblich(ZTante).

bruder(ZBruder,ZKind):- elternteil(ZElternteil,ZBruder), elternteil(ZElternteil,ZKind), maennlich(ZBruder), maennlich(ZElternteil), dif(ZBruder,ZKind).
schwester(ZSchwester,ZKind):- geschwisternteil(ZSchwester, ZKind), weiblich(ZSchwester).