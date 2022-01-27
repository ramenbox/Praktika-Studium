<?php declare(strict_types=1);

include_once __DIR__ . '/../config/db.php';

function connectdb() : mysqli {
    $link = mysqli_connect('p:'. HOST,          // Host der Datenbank (p: Persistent connection)
        USER,                                   // Benutzername zur Anmeldung
        PASSWORD,                           // Passwort zur Anmeldung
        DATABASE);                          // Auswahl der Datenbank
    if (!$link) {
        echo "Verbindung fehlgeschlagen: ", mysqli_connect_error();
        exit();
    }
    return $link;
}