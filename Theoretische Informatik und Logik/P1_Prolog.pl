/*
?- vater(ZVater,ZKind).
?- mutter(ZMutter,ZKind).
?- sohn(ZSohn,ZElter).
?- tochter(ZTochter,ZElter).
?- bruder(ZBruder,ZGeschwister).
?- schwester(ZSchwester,ZGeschwister).
?- onkel(ZOnkel, ZNichteNeffe).
?- cousine(ZCousine, ZCousin).
?- grossvater(ZGroßvater, ZEnkel).

, = und
; = oder
*/

%Fakten
maennlich(lukas). 	%Ich
maennlich(tom). 	%Bruder
maennlich(peter).  	%Vater
maennlich(will). 	%Grossvater
maennlich(otto).	%Onkel

weiblich(anna). 	%Mutter
weiblich(lisa). 	%Schwester
weiblich(julia).	%Schwester
weiblich(kim).	    %Cousine
weiblich(chanri).   %Grossmutter

%Relationen
%Vater
elternteil(peter, lukas).
elternteil(peter, lisa).
elternteil(peter, julia).
elternteil(peter, tom).

%Mutter
elternteil(anna, lukas).
elternteil(anna, lisa).
elternteil(anna, julia).
elternteil(anna, tom).

%Vater(Onkel)
elternteil(otto, kim).

%Vater(Grossvater)
elternteil(will, peter).
elternteil(will, otto).

%Mutter(Grossmutter)
elternteil(chanri, peter).
elternteil(chanri, otto).

%Ich(Bruder)
/*geschwisternteil(lukas, lisa). 
geschwisternteil(lukas, julia).
geschwisternteil(lukas, tom).

geschwisternteil(lisa, lukas).
geschwisternteil(lisa, julia).
geschwisternteil(lisa, tom).

geschwisternteil(julia, lukas).
geschwisternteil(julia, lisa).
geschwisternteil(julia, tom).

geschwisternteil(tom, lukas).
geschwisternteil(tom, lisa).
geschwisternteil(tom, julia).

geschwisternteil(peter, otto).
geschwisternteil(otto, peter).
*/

%Regeln
/*Vater von Kind wenn ist Elternteil vom Kind und maennlich*/
vater(ZVater, ZKind):- elternteil(ZVater, ZKind), maennlich(ZVater).
/*Mutter von Kind wenn ist Elternteil vom Kind und weiblich*/
mutter(ZMutter, ZKind):- elternteil(ZMutter, ZKind), weiblich(ZMutter).

/*Ist Sohn vom Elternteil, wenn ist Elternteil vom Sohn und Sohn maennlich*/
sohn(ZSohn,ZElter):- elternteil(ZElter, ZSohn), maennlich(ZSohn).
/*Ist Tochter vom Elternteil, wenn ist Elternteil von Tochter und Tochter weiblich*/
tochter(ZTochter,ZElter):- elternteil(ZElter, ZTochter), weiblich(ZTochter).

/*Ist Bruder vom Geschwisternteil, wenn beide gleichen Elternteil haben und der Bruder maennlich ist. Bruder und Geschwisternteil unterscheien sich*/
/*bruder3(ZBruder,ZGeschwister):- elternteil(ZElter, ZBruder), elternteil(ZElter, ZGeschwister), maennlich(ZBruder), dif(ZBruder, ZGeschwister).*/
/*bruder2(ZBruder, ZGeschwister):- geschwisternteil(ZBruder,ZGeschwister), maennlich(ZBruder).*/
bruder(ZBruder,ZGeschwister):- mutter(ZMutter, ZBruder), mutter(ZMutter, ZGeschwister), vater(ZVater, ZBruder), vater(ZVater, ZGeschwister), maennlich(ZBruder), dif(ZBruder, ZGeschwister).

/*Schwster vom Geschwisternteil, wenn beide Geschwister und Schwester weiblich*/
schwester(ZSchwester,ZGeschwister):- mutter(ZMutter, ZSchwester), mutter(ZMutter, ZGeschwister), vater(ZVater, ZSchwester), vater(ZVater, ZGeschwister), weiblich(ZSchwester), dif(ZSchwester, ZGeschwister).
/*schwester2(ZSchwester,ZGeschwister):- geschwisternteil(ZSchwester, ZGeschwister), weiblich(ZSchwester).*/

/*Ist Onkel vom Neffe, wenn Elternteil ist Elter von Neffe und Onkel und Eltern sind geschwister und Onkel ist maennlich*/
/*onkel(ZOnkel, ZNichteNeffe):- elternteil(ZElter, ZNichteNeffe), geschwisternteil(ZOnkel, ZElter), maennlich(ZOnkel).*/
onkel(ZOnkel, ZNichteNeffe):- elternteil(ZElternteil, ZNichteNeffe), bruder(ZOnkel, ZElternteil).

/*Ist Cousine von Cousin, wennn Eltern von Cousin und Cousine Geschwister sind und Cousine weiblich und maennlich Cousin*/
cousine(ZCousine, ZCousin):- elternteil(ZElternteil1,ZCousine), elternteil(ZElternteil,ZCousin), bruder(ZElternteil1,ZElternteil), weiblich(ZCousine), maennlich(ZCousin).

/*Grossvater von Enkel, wenn Vater des Vaters*/
grossvater(ZGrossvater, ZEnkel):- elternteil(ZGrossvater, ZElter), elternteil(ZElter, ZEnkel), maennlich(ZGrossvater).