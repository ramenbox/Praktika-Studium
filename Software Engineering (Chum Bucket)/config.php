<?php
//Temporär
function connectdb() {
    $link = mysqli_connect(
        'localhost',
        'root',
        'toor',
        'test_datenbank'
    );
    if (!$link) {
        echo "Verbindung fehlgeschlagen: ", mysqli_connect_error();
        exit();
    }

    return $link;
}

?>