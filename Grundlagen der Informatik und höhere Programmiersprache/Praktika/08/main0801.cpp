#include <iostream>
#define CIMGGIP_MAIN
#include "CImgGIP05.h"

using namespace std;

struct Box
{
    int x;
    int y;
    int delta_y; // aktuelle Fallgeschwindigkeit dieses Kaestchens
};

const int box_max = 10, box_size = 40;
// draw_boxes():
// Die Anzahl der Kaestchen wird nicht als zweiter Parameter uebergeben,
// da diese Anzahl als globale Konstante box_max im gesamten Programm bekannt ist ...

void draw_boxes(Box boxes[])
{
    // Loesche den bisherigen Fensterinhalt komplett,
    // d.h. komplettes Neuzeichnen aller Kaestchen etc ...
    gip_white_background();
    // Und jetzt alle Kaestchen zeichnen mittels gip_draw_rectangle().
    // Linke obere Ecke: (boxes[i].x, boxes[i].y)
    // Groesse: box_size x box_size
    // Farbe: blue
    // TO DO
	for (int i = 0; i < box_max; i++)
	{
		gip_draw_rectangle(boxes[i].x, boxes[i].y, boxes[i].x + box_size, boxes[i].y + box_size, blue);
		//cout << "Box[" << i << "] : (" << boxes[i].x << "," << boxes[i].y << "," << boxes[i].x + box_size << "," << boxes[i].y + box_size << ")" << endl;
	}
}
// update_boxes():
// 1. Berechne neue y-Koordinate (jedes Kaestchen boxes[i] faellt um boxes[i].delta_y)
// 2. Pruefe, ob ein Kaestchen das untere Fensterende gip_win_size_y (ist ein int)
// ueberschritten hat. Falls ja: gib sofort false zurueck
// 3. (Sonst:) gib true zurueck, wenn keines der Kaestchen den unteren Rand
// ueberschritten hatte
// Die Anzahl der Kaestchen wird nicht als zweiter Parameter uebergeben,
// da diese Anzahl als globale Konstante box_max im gesamten Programm bekannt ist ...
bool update_boxes(Box boxes[])
{
    // TO DO
	for (int i = 0; i < box_max; i++)
	{
		boxes[i].y += boxes[i].delta_y;
		if (boxes[i].y + box_size >= gip_win_size_y)
		{
			cout << "Box[" << i << "] aus dem Fenster." << endl;
			return false;
		}
	}

	return true;
}

// handle_mouse_click():
// Annahme: Funktion wird nur aufgerufen, wenn die Maus wirklich
// geklickt wurde. Die Funktion braucht dies also nicht mehr zu pruefen.
//
// Nimm die Koordinaten der Mausposition und pruefe dann fuer jedes Kaestchen,
// ob die Koordinaten innerhalb des Kaestchens liegen.
// Falls ja:
// * Erhoehe die Fallgeschwindigkeit des Kaestchens um 10
// * Setze das Kaestchen an den oberen Rand
void handle_mouse_click(Box boxes[])
{
    int mouse_x = gip_mouse_x();
    int mouse_y = gip_mouse_y();
    // TO DO
	for (int i = 0; i < box_max; i++)
	{
		if ((mouse_x >= boxes[i].x && mouse_x <= boxes[i].x + box_size) &&
			(mouse_y >= boxes[i].y && mouse_y <= boxes[i].y + box_size))
		{
			boxes[i].delta_y += 10;
			boxes[i].y = 0;
			cout << "Box[" << i << "] y : " << boxes[i].y << " und delta_y : " << boxes[i].delta_y << endl;
		}
	}
}

int main()
{
    Box boxes[box_max] = { 0 };
    bool keep_going = true;
    // Initialisiere alle Kaestchen ...
    for (int i = 0; i < box_max; i++)
    {
        // Die "+10" bewirken, dass alle Kaestchen leicht nach rechts versetzt werden
        // und somit links vom linksten Kaestchen noch etwas Platz bleibt (dieses
        // also nicht am Rand klebt).
        // Die "+20" sorgen fuer einen Zwischenraum von 20 zwischen den Kaestchen ...
        boxes[i].x = i * (box_size + 20) + 10;
        boxes[i].y = 0;
        // Startgeschwindigkeit ist ganzzahlige Zufallszahl zwischen 10 und 30 ...
        boxes[i].delta_y = gip_random(10, 30);
    }
    while (keep_going && gip_window_not_closed())
    {
        draw_boxes(boxes);
        
        for (int loop_count = 0; loop_count < 200; loop_count++)
        {
            gip_wait(5); // warte 5 Milli-Sekunden
            if (gip_mouse_button1_pressed())
            {
                handle_mouse_click(boxes);
            }
        }
        // Berechne die neue Fall-Position aller Kaestchen und pruefe,
        // ob eines der Kaestchen unten aus dem Fenster "herausgefallen" ist
        // (falls ja, wird der Wert false zurueckgegeben) ...
        keep_going = update_boxes(boxes);
    }
    
	system("PAUSE");
    return 0;
}