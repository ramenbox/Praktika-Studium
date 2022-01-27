<?php

function dbconnect()
{

    $port = 3306;
    $link = mysqli_connect(
        "127.0.0.1",
        "root",
        "toor",
        "test_datenbank",
        $port
    );
    if (!$link) {
        echo "Verbindung fehlgeschlagen: ", mysqli_connect_error();
        exit();
    }

    return $link;
}



