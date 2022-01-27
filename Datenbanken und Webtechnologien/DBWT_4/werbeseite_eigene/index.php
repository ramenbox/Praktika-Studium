<?php
/**
 * Praktikum DBWT. Autoren:
 * Harun, Karacuban, 3158169
 * Thavarupan, Mahendralingham, 3130383
 */

#Variablen
session_start();
#$_SESSION['count'] = 0;
if(!(isset($_SESSION['count']))){
    $_SESSION['count'] = 0;
}


$countMeals=0;
$file = fopen("speisen.txt", r);
while(!feof($file)) {
    $daten = fgets($file);
    $filtered = preg_split("/\|/", $daten);
    $meals[$countMeals]['name'] = $filtered[0];
    $meals[$countMeals]['preis-intern'] = $filtered[1];
    $meals[$countMeals]['preis-extern']  = $filtered[2];
    $meals[$countMeals]['bild'] =   $filtered[3];
    $countMeals++;
}
fclose($file);


function gueltigerName() {
    if (strlen(trim($_POST['user'])) == 0)
    {
        return false; //echo "Name kann nicht leer sein\n";
    }
    return true;
}

function gueltigeEmail() {
    if (stripos($_POST['email'],"@rcpt.at") == true ||
        stripos($_POST['email'],"@damnthespam.at") == true ||
        stripos($_POST['email'],"@wegwerfmail.de") == true ||
        stripos($_POST['email'], "@trashmail.de") == true||
        stripos($_POST['email'], "@trashmail.com") == true)
    {
        return false;
    }
    return true;
}

function gueltigeEingabe() {
    if (!isset($_POST['user']) && !isset($_POST['email']) && !isset($_POST['language']) && !isset($_POST['datenschutz'])) {
        return;
    }
    else if (gueltigerName()== false) {
        echo '<p style = "color: #ff0000">(Benutzer-)Name kann nicht leer sein' .'<br>';
    }
    else if (gueltigeEmail() == false) {
        echo '<p style = "color: red">Diese E-Mail entspricht nicht den Vorgaben'.'<br>';
    }

    else if (gueltigerName() == true && gueltigeEmail() == true)
    {
        $file = fopen("daten.txt",'a');
        $VerarbeiteteString = StrEdit();
        fwrite($file, $VerarbeiteteString."\n");
        fclose($file);
        echo '<p style = "color: green">Daten wurden erfolgreich abgespeichert';
    }
}

function StrEdit()
{
    return $_POST['user']." ".$_POST['email']." ".$_POST['sprache'] . " " .$_POST['datenschutz'];
}


#Zähle Besuche ,,(pro Tag)" - ein neuladen der Seite, ist ein Besuch
if(isset($_SESSION['count'])){
    $_SESSION['count'] = $_SESSION['count'] + 1;
}

#Zähle Newsletteranmeldungen
$count=0;
$file = fopen("daten.txt", r);
while(!feof($file)) {
    $daten = fgets($file);
    $count++;
}
fclose($file);

//Datenbank Verbindungsaufbau
$conn = mysqli_connect("localhost", "root", "root", "emensawerbeseite");
//Falls Verbindung fehlschlägt
if (!$conn) {
    echo ("Verbindung fehlgeschlagen: ") . mysqli_connect_error();
    exit();
}
//Abfrage für die Gerichte mit Allergenen die dazu gehören
$sql = "select g.id, g.name, g.preis_intern, g.preis_extern, group_concat(a.code separator ', ') as codes, group_concat(a.name separator ', ') as Allergene, group_concat(a.typ) from gericht g left join gericht_hat_allergen ha on ha.gericht_id=g.id left join allergen a on ha.code = a.code group by g.id order by g.name ASC LIMIT 5";

//Allergene Liste der Gerichte die angezigt wurde aber in Namen
$sql2 = "SELECT g.id, a.code,g.name, g.preis_intern, g.preis_extern, group_concat(a.code),  group_concat(a.name) AS Allergene, group_concat(a.typ)
        FROM gericht g
        JOIN gericht_hat_allergen ha ON ha.gericht_id=g.id
        JOIN allergen a ON ha.code = a.code
        GROUP BY g.name LIMIT 5";

$result2 = mysqli_query($conn, $sql2);
$result = mysqli_query($conn, $sql);

//Falls Fehler bei Abfrage
if (!$result) {
    echo "Fehler während Abfrage: " . mysqli_error($conn);
    exit();
}
if (!$result2) {
    echo "Fehler während Abfrage: " . mysqli_error($conn);
    exit();
}



?>

<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <title>Ihre E-Mensa</title>
    <link rel="stylesheet" href="stylesheet.css">
    <link rel="shortcut icon" href="https://fh-aachen.de/favicon.ico" />

</head>
<body>

<!-- <img width="200" height="40" src="FHAachen-logo2010.svg.png"> -->

<div class="photo" style="text-align: center">
    <img width="200" height="55" style="vertical-align:center" src="FHAachen-logo2010.svg.png" alt="">
    <span style="vertical-align:center">
        <nav>
            <ul>
                 <li><a href="#ankuendigung">Ankündigungen</a></li>
                 <li><a href="#speisen">Speisen</a></li>
                 <li><a href="#zahlen">Zahlen</a></li>
                 <li><a href="#kontakt">Kontakt</a></li>
                 <li><a href="#wichtig">Wichtig für uns</a></li>
            </ul>
        </nav>
    </span>
</div>

<div class="restaurant" style="text-align: center">
    <img width="1000" height="300" style="vertical-align:center" src="korean-restaurant.jpg" alt=""></div>
<div class="divider">
    <h2 id="ankuendigung">Bald gibt es Essen auch Online</h2>
    <fieldset>
        Lorem ipsum dolor sit amet, consectetur adipiscing elit.
        Nunc ultricies efficitur magna, non fringilla purus dictum pellentesque.
        Maecenas vehicula lorem erat, vitae vehicula elit pretium ut. Sed elementum,
        urna at lobortis accumsan, nunc magna tempus nunc, a iaculis libero erat ac enim.
    </fieldset>
    <br>
    <h2 id="speisen">Köstlichkeiten, die Sie erwarten</h2>
    <table style="border-collapse: collapse">
        <thead>
        <tr>
            <th>Speise</th>
            <th>Preis Intern</th>
            <th>Preis extern</th>
            <th>Bild</th>
        </tr>
        </thead>
        <tbody>
        <?php
        foreach ($meals as $i => $key)
        {
            echo "<tr>";
            echo "<td>" . $meals[$i]['name'] . "</td>";
            echo "<td>" . $meals[$i]['preis-intern'] . "</td>";
            echo "<td>" . $meals[$i]['preis-extern'] . "</td>";
            echo "<td>" . '<img src="./bilder/'.$meals[$i]['bild'].'" alt="Photo of food">'. "</td>";

            echo "</tr>";
        }
        ?>
        </tbody>
    </table>

    <table style="border-collapse: collapse">
        <thead>
        <tr>
            <th>Gericht</th>
            <th>Preis Intern</th>
            <th>Preis extern</th>
            <th>Allergene</th>
        </tr>
        </thead>
        <tbody>
        <br>
        <?php
        $speisen = 0;
        while ($row = mysqli_fetch_assoc($result)) {

            //Ausgeben der einzelnen Attributwerte
            echo "<tr class='auswahl'>";
            echo "<td>" . $row['name'] . "</td>";
            echo "<td class='tabelleheader'>" . $row['preis_intern'] . "€</td>";
            echo "<td class='tabelleheader'>" . $row['preis_extern'] . "€</td>";
            echo "<td class='tabelleheader'>" . $row['codes'] . "</td>";
            echo "</tr>";

            //Hochzählen wenn Gericht existiert und ausgegeben wurde
            $speisen++;

        }

        ?>
        </tbody>
    </table>
    <br>
    <?php
    echo "<span id='nutrition-note'>";
    echo "Allergiehinweise der Liste nach sortiert:";
    echo "<ul style='margin-top: 0px'>";
    echo "<br>";
    while ($row = mysqli_fetch_assoc($result2)) {
        echo "<li>" . $row['Allergene'] . "</li>";
    }
    echo "</ul>";
    echo "</span>";

    $zahlen['Speisen'] = $speisen;
    mysqli_free_result($result);
    mysqli_free_result($result2);
    mysqli_close($conn);
    ?>


    <h2 id="zahlen">E-Mensa in Zahlen</h2>
    <div class="gridbutton3">
        <div>
            <?php echo "{$_SESSION['count']}"  ?> Besucher
        </div>
        <div>
            <?php echo "$count"?> Anmeldungen zum Newsletter
        </div>
        <div>
            <?php echo "$countMeals"?> Speisen
        </div>
    </div>

    <h2 id="kontakt">Interesse geweckt? Wir Informieren Sie!</h2>

    <form id="newsletteranmeldung" action="indexphp.php#form" method="POST">
        <div class="gridbutton">
            <div>
                <label for="vname">Ihr Name:</label> <br>
                <input type="text" required id="vname" name="user" placeholder="Vorname"> <br><br>
            </div>
            <div>
                <label for="email">Ihre E-Mail:</label> <br>
                <input type="email" name="email" required id="email" placeholder=""> <br><br>
            </div>
            <div>
                <label for="sprache">Newsletter bitte in:</label> <br>
                <select name="sprache" id="sprache">
                    <option value="de" selected>Deutsch</option>
                    <option value="eng">Englisch</option>
                    <option value="sp">Spanisch</option>
                </select>
                <br><br>
            </div>
        </div>
        <div class="gridbutton2">
            <label for="datenschutz">
                <input type="checkbox" id="datenschutz" name="datenschutz" required>
                Den Datenschutzbestimmungen stimme ich zu
            </label>
            <input type="submit" id="submit" value="Zum Newsletter anmelden">
            <?php echo '<br>'; gueltigeEingabe();  ?>
        </div>

    </form>

    <h2 id="wunschgericht">Tragen Sie Ihr Wunschgericht hier ein:</h2>
    <ol class="orderedliste">
    <li><a href="wunschgericht.php">Wunschgericht wählen</a></li>
    </ol>

    <h2 id="wichtig">Das ist uns wichtig</h2>
    <ol class="orderedliste">
        <li>Beste frische Saisonale Zutaten</li>
        <li>Ausgewogene abwechslungreiche Gerichte</li>
        <li>Sauberkeit</li>
    </ol>

    <h1>Wir freuen uns auf Ihren Besuch!</h1>
</div>
<footer>
    <ul>
        <li>(c) E-Mensa GmbH</li>
        <li>Harun & Thava</li>
        <li>Impressum</li>
    </ul>
</footer>
</body>
</html>