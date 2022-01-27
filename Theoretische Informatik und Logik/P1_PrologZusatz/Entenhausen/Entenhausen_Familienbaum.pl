/*
--Entenhausen Familienbaum--
Hierbei sei angemerkt, 
dass die angaben quasi richtig sind, 
also Mutter&Vater Beispielsweise nicht geschieden, 
auch wenn sie es eventuell schon sind.

Dadurch entstehen unten unter anderem Halbgeschwister, 
welche ich allerdings nicht weiter beachtet habe, also demnach Halb- schwester-/bruder == Schwester oder Bruder. 

Zudem sind fiktive Figuren eingefügt worden, um die Stammbaumlücken zu füllen.
Die Urgrosseltern sind ebenso in der Liste, allerdings nicht weiter in den ausgaben beachtet.
Da dies für den Grossonkel notwendig war.
*/

%Kind
maennlich(tickduck).
maennlich(trickduck).
maennlich(trackduck).

%Vater
maennlich(unbekanntduck).

%Onkel
maennlich(donaldduck).

%Grossvater
maennlich(degenhardduck).

%Grossonkel
maennlich(dagobertduck).

%Urgrossvater
maennlich(dietbertduck).
maennlich(hilmarduck).

%Mutter
weiblich(delladuck).

%Grossmutter
weiblich(dortelduck).

%Tante
weiblich(fiktivtante).

%Grosstante
weiblich(mathildaduck).

%Urgrossmutter
weiblich(dankradedrachenfels).
weiblich(doretteerpel).

%elternteil
elternteil(unbekanntduck,tickduck).
elternteil(unbekanntduck,trickduck).
elternteil(unbekanntduck,trackduck).

elternteil(delladuck,tickduck).
elternteil(delladuck,trickduck).
elternteil(delladuck,trackduck).

elternteil(degenhardduck,delladuck).
elternteil(degenhardduck,donaldduck).
elternteil(degenhardduck,fiktivtante).

elternteil(dortelduck,donaldduck).
elternteil(dortelduck,delladuck).
elternteil(dortelduck,fiktivtante).

elternteil(dietbertduck,mathildaduck).
elternteil(dietbertduck,dagobertduck).
elternteil(dietbertduck,dortelduck).

elternteil(dankradedrachenfels,mathildaduck).
elternteil(dankradedrachenfels,dagobertduck).
elternteil(dankradedrachenfels,dortelduck).

elternteil(hilmarduck,degenhardduck).
elternteil(doretteerpel,degenhardduck).

/*Ist Vater vom Kind, wenn Elternteil Vater vom Kind ist maennlich*/
%Vater
vater(Vater,Kind) :- elternteil(Vater,Kind), maennlich(Vater).

/*Ist Mutter vom Kind, wenn Elternteil Mutter vom Kind ist weiblich*/
%Mutter
mutter(Mutter,Kind) :- elternteil(Mutter,Kind), weiblich(Mutter).

/*Ist Kind von Vater wenn ist Mutter vom Kind und Kind ist maennlich(=Sohn) */
%Sohn
sohn(Kind,Mutter) :- elternteil(Mutter,Kind), maennlich(Kind), weiblich(Mutter).

/*Ist Tochter von Vater, wenn ist Vater von Tochter und Kind ist weiblich(=Tochter)*/
%Tochter
tochter(Kind,Vater) :- elternteil(Vater,Kind), weiblich(Kind).

/*Ist Geschwisternteil von Kind, wenn Vater von Kind und Vater vom Geschwisternteil die selben, dif um nicht gleichKindgleichGeschwisternteil*/
%Geschwister
geschwister(Kind,Geschwisternteil) :- elternteil(Vater,Kind), elternteil(Vater,Geschwisternteil), dif(Kind,Geschwisternteil). 

/*Ist bruder von Kind, wenn mutter von bruder und mutter von kind die selben und bruder maennlich + dif*/
%Bruder
bruder(Bruder,Kind) :- mutter(Mutter,Bruder), mutter(Mutter,Kind), maennlich(Bruder),dif(Kind,Bruder).

/*hier anders, ist kind seine/ihre schwester, wenn vater vom Kind und vater von Schwester die selben + dif*/
%Schwester
schwester(Kind,Schwester) :- vater(Vater,Kind), vater(Vater,Schwester), weiblich(Kind), dif(Kind,Schwester).

/*Onkel von Kind, wenn mutter ist von kind und geschwister onkel und mutter */
%Onkel
onkel(Onkel,Kind) :- elternteil(Mutter,Kind), bruder(Onkel,Mutter).

/*Da in diesem kleinen Teilbaum keine echte Tante vorhanden, habe ich ne fiktivetante hinzugefügt.*/
%Tante
tante(Tante,Kind) :- elternteil(Vater, Kind), schwester(Tante,Vater).

/*Grossvater von Kind, wenn mutter ist elternteil von kind und grossvater ist elternteil von mutter und grossvater maennlich*/
%Grossvater
grossvater(Grossvater,Kind) :- elternteil(Mutter, Kind), elternteil(Grossvater,Mutter), maennlich(Grossvater).

%Grossmutter
grossmutter(Grossmutter,Kind) :- elternteil(Mutter,Kind), elternteil(Grossmutter,Mutter), weiblich(Grossmutter).

%Grossonkel
grossonkel(Grossonkel,Kind):- elternteil(Mutter,Kind), elternteil(Grossmutter,Mutter), bruder(Grossonkel,Grossmutter).