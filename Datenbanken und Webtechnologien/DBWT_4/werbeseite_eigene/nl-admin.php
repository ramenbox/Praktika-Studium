<?php
const GET_PARAM_SEARCH_TEXT = 'search_text';

$Datenhaltung = array();
 /*
for ($i = 0; $i < 1 ; $i++) {

}
 */
#Lese Datei in ein Array ein - Pro Zeile (pro Nutzer) ein Schlüssel

$count=0;
$file = fopen("daten.txt", r);
while(!feof($file)) {
    $daten = fgets($file,) . "<br>";
    $filtered = preg_split("/ /", $daten);
    $Datenhaltung[$count]['name']  = $filtered[0];
    $Datenhaltung[$count]['email']  = $filtered[1];
    $Datenhaltung[$count]['sprache']   = $filtered[2];
    $Datenhaltung[$count]['datenschutz']  = $filtered[3];
    #array_push($Datenhaltung, $Datenhaltung[$count]['name'], $Datenhaltung[$count]['email'], $Datenhaltung[$count]['sprache'], $Datenhaltung[$count]['datenschutz']);
    $count++;
}
fclose($file);
$data = $Datenhaltung;

#Suche nach Namen - suche nach Teilstring im gesamten String mit(stripos) - Groß- und Kleinschreibung werden ignoriert mit(stripos)
if (!empty($_GET[GET_PARAM_SEARCH_TEXT])) {
    $searchTerm = $_GET[GET_PARAM_SEARCH_TEXT];
        foreach ($data as $index) {
            if (stripos ($index['name'], $searchTerm) !== false) {
                $sdata[] = $index;
            }
        }
        $data=$sdata;
}



/*
 * braucht man noch den Email Filter als @yahoo.de filter oder nur gesamte Mail filter ??
 */



#Sortiere nach Namen oder E-Mail Adressen
function array_msort($array, $cols)
{
    $colarr = array();
    foreach ($cols as $col => $order) {
        $colarr[$col] = array();
        foreach ($array as $k => $row) { $colarr[$col]['_'.$k] = strtolower($row[$col]); }
    }
    $eval = 'array_multisort(';
    foreach ($cols as $col => $order) {
        $eval .= '$colarr[\''.$col.'\'],'.$order.',';
    }
    $eval = substr($eval,0,-1).');';
    eval($eval);
    $ret = array();
    foreach ($colarr as $col => $arr) {
        foreach ($arr as $k => $v) {
            $k = substr($k,1);
            if (!isset($ret[$k])) $ret[$k] = $array[$k];
            $ret[$k][$col] = $array[$k][$col];
        }
    }
    return $ret;
}

if (isset($_GET['mail'])) {
if(($_GET['mail']) == "aufsteigend") {$data = array_msort($Datenhaltung, array('email'=>SORT_ASC)); }
else  {$data = $Datenhaltung;  }
}
if (isset($_GET['name'])) {
    if(($_GET['name'])== "aufsteigend") {$data = array_msort($Datenhaltung, array('name'=>SORT_ASC));}
    else  {$data = $Datenhaltung;}
}
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
    <title>Newsletter-Admin</title>
    <link rel="stylesheet" href="stylesheet.css">
</head>
<body>
<h2>Newsletter Anmeldungen [Admin]</h2>

<form id="mail"  action="nl-admin.php" method="get">
    <table>
        <thead>
        <th>Sortierung Namen aufsteigend</th>
        <th>Sortierung E-Mails aufsteigend</th>
        <th>Sortierung zurücksetzen</th>
        <th colspan="3">Filter nach Namen</th>
        </thead>
        <tbody>
        <tr>
            <td><input type="submit" name="name"   value="aufsteigend"></td>
            <td><input type="submit" name="mail"   value="aufsteigend"></td>
            <td><input type="submit" name="mail"   value="normal"></td>
            <td><input id="search_text" type="text" name="search_text">
                <input type="submit" value="Suchen"></td>
        </tr>
        </tbody>
    </table>
</form>



<table style="border-collapse: collapse">
    <thead>
    <th>Name</th>
    <th>E-Mail</th>
    <th>Sprache</th>
    <th>Datenschutz</th>
    </thead>
    <tbody>
    <?php
    #for ($i = 0; $i < $count ; $i++)
    foreach ($data as $i => $key)
    {
        echo "<tr>";
        echo "<td>" . $data[$i]['name'] . "</td>";
        echo "<td>" . $data[$i]['email'] . "</td>";
        echo "<td>" . $data[$i]['sprache'] . "</td>";
        echo "<td>" . $data[$i]['datenschutz'] . "</td>";
        echo "</tr>";
    }
    ?>
    </tbody>
</table>




</body>
</html>