<?php
include_once ('dbconfig/config.php');
$link = dbconnect();

$studienbeginn = '0';
$anzahl_semester = 0;
$name = "Unbenannter Studiengang";
$veröffentlicht = "";
$einschreibung = "WS";
$projekt = 0;
$public = 0;
$credits = 660;



$sql = "INSERT INTO studienverlaufsplan(studienbeginn, anzahl_fachsemester, name, veroeffentlichungsjahr_po, einschreibung, praxisprojekt, public, credits)
VALUES ('$studienbeginn', '$anzahl_semester', '$name', '$veröffentlicht', '$einschreibung', '$projekt', '$public', '$credits')";
mysqli_query($link, $sql);
$last_id = $link->insert_id; //$last_id = die letzte ID die in studienverlaufsplan eingefügt wurde

//echo $last_id;

$result = $link->query("select id from modul");
while($row = $result->fetch_assoc())
{
    $modul_id = $row["id"];

    $sql = "INSERT INTO studienverlaufsplan_data VALUES ('$last_id', '$modul_id', 0);";
    mysqli_query($link, $sql);
}

echo '<script>setTimeout(function(){window.location.href="ListenansichtVerwalterU30.php"}, 0)</script>';