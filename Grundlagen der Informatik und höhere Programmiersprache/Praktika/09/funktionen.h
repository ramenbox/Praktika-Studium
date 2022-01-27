#pragma once

//Hilfs-funktionen
void cstring_einlesen(char* test, bool leer_sein=false);
void cstring_speichern(char* text, char* buff, unsigned int &pos);
unsigned int cstring_len(const char* text);
void cstring_ausgeben(char* text);
bool cstring_leer(const char* text);