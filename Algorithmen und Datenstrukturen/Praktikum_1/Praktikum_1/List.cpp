#include "List.h"

List::List()
{
	// Konstruktor fuer eine leere Liste
	head_tail = new Node;
	list_size = 0;
	temp = false;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}

List::List(const List & _List)
{
	// Konstruktor mit Uebergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List.list_form;
	head_tail = new Node;
	list_size = 0;
	temp = _List.temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node * tmp_node;
	tmp_node = _List.head_tail->next;
	while (tmp_node != _List.head_tail)
	{
		head_tail->prev = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;		// ist die uebergebene Liste eine temporaere Liste? -> aus Operator +
}

List::List(const List * _List)
{
	// Konstruktor mit Uebergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List->list_form;
	head_tail = new Node;
	list_size = 0;
	temp = _List->temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node * tmp_node;
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)
	{
		head_tail->prev = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die uebergebene Liste eine temporaere Liste? -> aus Operator +
}

List::~List()
{
	// Dekonstruktor
	// Alle Knoten der Liste muessen geloescht werden, wenn die Liste geloescht wird.
/*
	hier alle Knoten loeschen, die im Objekt List allokiert wurden
*/
	Node* anker = this->head_tail->prev;

	while (anker != this->head_tail)
	{
		//getted den zu loeschenden knoten
		Node* delKnoten = anker;
		//durchlaufe rueckwaerts
		anker = anker->prev;

		delete delKnoten;
		this->list_size--;
	}
	this->head_tail->next = this->head_tail; //zeigt zurueck^
	this->head_tail->prev = this->head_tail;
}

void List::insertFront(int key) //Umdenken, also insertBack, da 9,8,7...
{
	// Einfuegen eines neuen Knotens am Anfang der Liste
/*
	Einen neuen Knoten mit dem Schluesselwert key am Anfang der Liste einfuegen
*/

	// Erstelle einen neuen Knoten mit den Wert
	Node* neuerKnoten = new Node(key, this->head_tail, this->head_tail);
	//neuerKnoten->prev = head_tail;

	// Liste ist leer
	if (this->list_size == 0)
	{
		this->head_tail->next = neuerKnoten;
		this->head_tail->prev = neuerKnoten;
	}
	else // Liste enthaelt Knoten
	{
		Node* ersterKnoten = this->head_tail->next;
		// Der neue Knoten zeigt vorwaerts auf dem ersten Knoten
		neuerKnoten->next = ersterKnoten;
		// Der erste Knoten zeigt rueckwaerts auf den neuen Knoten
		ersterKnoten->prev = neuerKnoten;
		
		this->head_tail->next = neuerKnoten;
	}
	
	this->list_size++;

}

void List::insertBack(List & _List) //umdenken, also inserFront
{
	// Einfuegen einer vorhandenen Liste am Anfang
	/*	
	Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
	Die einzufuegende Liste _List ist anschliessend leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt uebergeben in dem Knoten vorhanden sein koennen.
	Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) uebertragen ohne sie zu kopieren!
*/

	// Liste ist nicht leer
	if (this->list_size)
	{
		Node* ersterKnoten1 = this->head_tail->next;
		Node* ersterKnoten2 = _List.head_tail->next;
		// Der erste Knoten der einen Liste zeigt auf den letzten Knoten der hinzufuegenden Liste
		Node* letzterKnoten2 = _List.head_tail->prev;
		
		ersterKnoten1->prev = letzterKnoten2;
		letzterKnoten2->next = ersterKnoten1;

		ersterKnoten2->prev = this->head_tail;

		// Erster Knoten der Liste (_List) wird erster Knoten von (this) Liste
		this->head_tail->next = _List.head_tail->next;

		// Die Anzahl der Knoten von der vorhandenen Liste addieren wir hinzu
		this->list_size += _List.list_size;


		// Die hinzufuegende Liste ist anschliessend leer
		_List.list_size = 0;
		_List.head_tail->next = _List.head_tail;
		_List.head_tail->prev = _List.head_tail;
	}

}

void List::insertBack(List * _List)
{
	// Einf�gen einer vorhandenen Liste am Anfang
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden. 	
	*/
/*
	Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
	Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
*/
// Liste ist nicht leer
	if (this->list_size)
	{
		Node* ersterKnoten1 = this->head_tail->next;
		Node* ersterKnoten2 = _List->head_tail->next;
		// Der erste Knoten der einen Liste zeigt auf den letzten Knoten der hinzufuegenden Liste
		Node* letzterKnoten2 = _List->head_tail->prev;
		ersterKnoten1->prev = letzterKnoten2;
		letzterKnoten2->next = ersterKnoten1;

		ersterKnoten2->prev = this->head_tail;

		// Erster Knoten der Liste (_List) wird erster Knoten von (this) Liste
		this->head_tail->next = _List->head_tail->next;

		// Die Anzahl der Knoten von der vorhandenen Liste addieren wir hinzu
		this->list_size += _List->list_size;


		// Die hinzufuegende Liste ist anschliessend leer
		_List->list_size = 0;
		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
	}
}

void List::insertBack(int key)
{
	// Einf�gen eines neuen Knotens am Ende der Liste
/*
	Einen neuen Knoten mit dem Schl�sselwert key am Ende der Liste einf�gen
*/

	// Erstellen neuen Knoten mit den hinzuzufuegenden Wert
	Node* neuerKnoten = new Node(key, this->head_tail, this->head_tail);
	//neuerKnoten->next = this->head_tail;

	// Liste ist leer
	if (this->list_size == 0)
	{
		this->head_tail->next = neuerKnoten;
		this->head_tail->prev = neuerKnoten;
	}
	else
	{
		// Letzter Knoten von der Liste (this)
		Node* letzterKnoten = this->head_tail->prev;

		letzterKnoten->next = neuerKnoten;
		neuerKnoten->prev = letzterKnoten;

		this->head_tail->prev = neuerKnoten;
	}

	this->list_size++;
}

void List::insertFront(List & _List)
{
	// Einf�gen einer vorhandenen Liste am Ende
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
	Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
*/

	// Die Liste (this) nicht leer
	if (this->list_size)
	{
		// Der letzter Knoten der Liste (this)
		Node* letzterKnoten1 = this->head_tail->prev;
		// Der erster Knoten der hinzuf�genden Liste
		Node* ersterKnoten2 = _List.head_tail->next;
		// Der letzter Knoten der hinzuf�genden Liste
		Node* letzterKnoten2 = _List.head_tail->prev;
		
		letzterKnoten1->next = ersterKnoten2;
		ersterKnoten2->prev = letzterKnoten1;

		letzterKnoten2->next = this->head_tail;
		// Letzter Knoten von Liste (this) ist der letzte Knoten von Liste (_List)
		this->head_tail->prev = letzterKnoten2;


		// Die Anzahl der Knoten von der vorhandenen Liste addieren wir hinzu
		this->list_size += _List.list_size;

		// Die hinzuf�gende Liste ist anschlie�end leer
		_List.list_size = 0;
		_List.head_tail->next = _List.head_tail;
		_List.head_tail->prev = _List.head_tail;
	}


}

void List::insertFront(List * _List)
{
	// Einf�gen einer vorhandenen Liste am Ende
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
	Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
*/
// Die Liste (this) nicht leer
	if (this->list_size)
	{
		// Der letzter Knoten der Liste (this)
		Node* letzterKnoten1 = this->head_tail->prev;
		// Der erster Knoten der hinzuf�genden Liste
		Node* ersterKnoten2 = _List->head_tail->next;
		// Der letzter Knoten der hinzuf�genden Liste
		Node* letzterKnoten2 = _List->head_tail->prev;

		letzterKnoten1->next = ersterKnoten2;
		ersterKnoten2->prev = letzterKnoten1;

		letzterKnoten2->next = this->head_tail;
		// Letzter Knoten von Liste (this) ist der letzte Knoten von Liste (_List)
		this->head_tail->prev = letzterKnoten2;


		// Die Anzahl der Knoten von der vorhandenen Liste addieren wir hinzu
		this->list_size += _List->list_size;

		// Die hinzuf�gende Liste ist anschlie�end leer
		_List->list_size = 0;
		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
	}
}

bool List::getFront(int & key)
{
	// entnehmen des Knotens am Anfang der Liste
	// der Wert wird als Parameter zur�ckgegeben
	// der Knoten wird entnommen
/*
	Der Wert des vorderen Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
	Die Methode del(key) darf nicht zum l�schen benutzt werden.
*/
	if (this->list_size == 0) return false;

	Node* ersterKnoten = this->head_tail->next;
	// Entnehme den Wert schonmal
	key = ersterKnoten->key;

	Node* zweiterKnoten = ersterKnoten->next;
	// Der zweiter Knoten wird zum ersten Knoten
	this->head_tail->next = zweiterKnoten;

	zweiterKnoten->prev = this->head_tail;
	ersterKnoten->next = nullptr;

	delete ersterKnoten;

	this->list_size--;

	return true;
}

bool List::getBack(int & key)
{	// entnehmen des Knotens am Ende der Liste
	// der Wert wird als Parameter zur�ckgegeben
	// der Knoten wird entnommen
/*
	Der Wert des letzten Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
	Die Methode del(key) darf nicht zum l�schen benutzt werden.
*/
	if (this->list_size == 0) return false;

	Node* letzterKnoten = this->head_tail->prev;
	// Entnehme den Wert schonmal
	key = letzterKnoten->key;

	Node* vorletzterKnoten = letzterKnoten->prev;
	// Der vorletzter Knoten wird zum letzten Knoten
	this->head_tail->prev = vorletzterKnoten;

	vorletzterKnoten->next = this->head_tail;
	letzterKnoten->prev = nullptr;

	delete letzterKnoten;

	this->list_size--;

	return true;
}

bool List::del(int key)
{
	// Loeschen eines gegebenen Knotens
/*
	Loeschen des Knotens mit dem Schluessel key
*/
	Node* anker = this->head_tail->next;

	while (anker != this->head_tail)
	{
		if (anker->key == key)
		{
			Node* midKnoten = anker;

			Node* linksKnoten = anker->prev;
			Node* rechtsKnoten = anker->next;

			linksKnoten->next = rechtsKnoten;
			rechtsKnoten->prev = linksKnoten;


			delete midKnoten;
			this->list_size--;
			return true;
		}
		// Traversiere vorwaerts
		anker = anker->next;


	}

	return false;
}

bool List::search(int key)
{
	// suchen eines Knotens
/*
	suchen ob ein Knoten mit dem Schluessel key existiert.
*/
	// Temporoerer Bewegungszeiger
	Node* anker = this->head_tail->next;
	while (anker != this->head_tail)
	{
		// Wenn der gesuchte Wert im Knoten liegt
		if (anker->key == key)
		{
			return true;
		}
		// Traversiere die Knoten vorwaerts
		anker = anker->next;
	}

	return false;
}

bool List::swap(int key1, int key2)
{
	// Vertauschen von zwei Knoten
	// Dabei werden die Zeiger der Knoten und deren Nachbarn veraendert.
/*
	Vertauschen von zwei Knoten mit dem key1 und dem key2
	Es duerfen nicht nur einfach die Schluessel in den Knoten getauscht werden!
	Die Knoten sind in der Kette umzuhaengen.
*/
	if (key1 == key2) return false;

	Node* anker = this->head_tail->next;

	Node* ersterKnoten = nullptr;
	Node* zweiterKnoten = nullptr;

	while (anker != head_tail)
	{
		if (ersterKnoten == nullptr && anker->key == key1)
		{
			ersterKnoten = anker;
		}
		if (zweiterKnoten == nullptr && anker->key == key2)
		{
			zweiterKnoten = anker;
		}
		anker = anker->next;
	}

	if (ersterKnoten && zweiterKnoten)
	{
		// 1 Fall: Nebeneinander

		// ersterKnoten ist links von zweiterKnoten
		if (ersterKnoten->next == zweiterKnoten && zweiterKnoten->prev == ersterKnoten)
		{
			Node* linksKnoten = ersterKnoten->prev;
			Node* rechtsKnoten = zweiterKnoten->next;

			// Vertausche ersterKnoten mit zweiterKnoten
			ersterKnoten->prev = zweiterKnoten;
			zweiterKnoten->next = ersterKnoten;

			ersterKnoten->next = rechtsKnoten;
			zweiterKnoten->prev = linksKnoten;

			linksKnoten->next = zweiterKnoten;
			rechtsKnoten->prev = ersterKnoten;

			return true;
		} // ersterKnoten ist rechts von zweiterKnoten
		else if (zweiterKnoten->next == ersterKnoten && ersterKnoten->prev == zweiterKnoten)
		{
			Node* linksKnoten = zweiterKnoten->prev;
			Node* rechtsKnoten = ersterKnoten->next;

			// Vertausche ersterKnoten mit zweiterKnoten
			ersterKnoten->next = zweiterKnoten;
			zweiterKnoten->prev = ersterKnoten;

			ersterKnoten->prev = linksKnoten;
			zweiterKnoten->next = rechtsKnoten;

			linksKnoten->next = ersterKnoten;
			rechtsKnoten->prev = zweiterKnoten;
			return true;
		}

		// 2 Fall: Nicht nebeneinander
		
		if (ersterKnoten->next != zweiterKnoten && zweiterKnoten->prev != ersterKnoten)
		{
			Node* links1 = ersterKnoten->prev;
			Node* rechts1 = ersterKnoten->next;

			Node* links2 = zweiterKnoten->prev;
			Node* rechts2 = zweiterKnoten->next;

			// Vertausche

			ersterKnoten->next = rechts2;
			zweiterKnoten->prev = links1;

			ersterKnoten->prev = links2;
			zweiterKnoten->next = rechts1;

			links1->next = zweiterKnoten;
			rechts2->prev = ersterKnoten;

			rechts1->prev = zweiterKnoten;
			links2->next = ersterKnoten;

			return true;
		}
	}

	return false;
}

int List::size(void)
{
	// R�ckgabe der Knoten in der Liste mit O(1)
/*
	Anzahl der Knoten in der Liste zur�ckgeben.
*/
	return this->list_size;
}

bool List::test(void)
{
	// Testmethode: die Methode durchl�uft die Liste vom Anfang bis zum Ende und zur�ck
	// Es werden dabei die Anzahl der Knoten gez�hlt.
	// Stimmt die Anzahl der Knoten �berein liefert die Methode true
	Node * tmp = head_tail->next;
	int i_next = 0, i_prev = 0;
	while (tmp != head_tail) {
		tmp = tmp->next;
		if (i_next > list_size) return false;
		i_next++;
	}
	if (i_next != list_size) return false;
	tmp = head_tail->prev;
	while (tmp != head_tail) {
		tmp = tmp->prev;
		if (i_prev > list_size) return false;
		i_prev++;
	}
	return i_prev == i_next;
}

List & List::operator = (const List & _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;		//  !! keine Aktion notwendig
	list_form = _List.list_form;
	Node * tmp_node;
	if (list_size)
	{
		Node * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List.head_tail->next;		// Die Listen-Knotenwerte werden kopiert
	while (tmp_node != _List.head_tail)
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}

List & List::operator = (const List * _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;		//  !! keine Aktion notwendig
	list_form = _List->list_form;
	Node * tmp_node;
	if (list_size)
	{
		Node * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)	// Die Listen-Knotenwerte werden kopiert
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}

List & List::operator + (const List & List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
	Node * tmp_node;
	List * tmp;
	if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {	
		tmp = new List(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
	}
	if (List_Append.list_size) {					// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append.head_tail->next;
		while (tmp_node != List_Append.head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht						
	return *tmp;
}

List & List::operator + (const List * List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
	Node * tmp_node;
	List * tmp;
	if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
	}
	if (List_Append->list_size) {					// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append->head_tail->next;
		while (tmp_node != List_Append->head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht					
	return *tmp;
}

void List::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	// Setzen des Formates f�r die Ausgabesteuerung der Liste bei cout
	// das Format wird f�r den �berladenen Operator << verwendet
	list_form.start = start;
	list_form.zwischen = zwischen;
	list_form.ende = ende;
}

std::ostream & operator<<(std::ostream  & stream, List const & Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste.list_form.start;
	for (Node * tmp = Liste.head_tail->next; tmp != Liste.head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.head_tail ? Liste.list_form.ende : Liste.list_form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}

std::ostream & operator << (std::ostream & stream, List const * Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste->list_form.start;
	for (Node * tmp = Liste->head_tail->next; tmp != Liste->head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->head_tail ? Liste->list_form.ende : Liste->list_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}
