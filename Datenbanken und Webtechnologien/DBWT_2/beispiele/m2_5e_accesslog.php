<?php
/**
 * Praktikum DBWT. Autoren:
 * Harun, Karacuban, 3158169
 * Thavarupan, Mahendralingham, 3130383
 */
//Informationen: Zeitstempel : Browser : IP
//Datei öffnen mit fopen - in Datei schreiben mit fwrite - Datei speichern/schließen mit fclose

$aclog = fopen('./accesslog.txt','a');//OptionA: Pointer zeigt auf Ende der Datei, wenn Datei nicht existiert, Datei erstellen
date_default_timezone_set("Europe/Berlin");//Aktuelle Zeit der Zeitzone: Europa/Berlin
fwrite($aclog, date("D.M.Y")." ".date("H:i:s\n"));//Datumsformat als Abkürzung der Tage/Monate in Englisch, Jahr komplett
fwrite($aclog,$_SERVER['HTTP_USER_AGENT']."\n");
fwrite($aclog,"IP Address : ".$_SERVER['REMOTE_ADDR']."\n");
fclose($aclog);

?>

<!DOCTYPE html>
<!--
- Praktikum DBWT. Autoren:
- Harun, Karacuban, 3158169
- Thavarupan, Mahendralingham, 3130383
Praktikum DBWT
-->
<html lang="de">
<head>
    <meta charset="UTF-8">
    <title>5e accesslog</title>
</head>
Logdatei erstellt
</html>