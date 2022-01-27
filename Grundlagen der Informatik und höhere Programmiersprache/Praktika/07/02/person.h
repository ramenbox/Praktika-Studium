#pragma once
#include <string>

struct Person
{
    std::string vorname,
                nachname,
                geburtsdatum;
};

Person extrahiere_person(std::string eingabezeile);