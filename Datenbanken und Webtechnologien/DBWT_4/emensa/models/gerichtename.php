<?php
/**
 * Diese Datei enthält alle SQL Statements für die Tabelle "gerichte"
 */
function db_gericht_select_all_name() {
    $link = connectdb();

    $sql = "SELECT  preis_intern,name FROM gericht ORDER BY name"; // Schummeln
    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_BOTH);

    mysqli_close($link);
    return $data;
}
