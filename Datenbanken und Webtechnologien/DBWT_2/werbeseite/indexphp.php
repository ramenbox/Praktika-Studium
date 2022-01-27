<?php
/**
 * Praktikum DBWT. Autoren:
 * Harun, Karacuban, 3158169
 * Thavarupan, Mahendralingham, 3130383
 */
$meals = array(
    '0' => [ 'name' => 'Rindfleisch mit Bambus, Kaiserschoten und rotem Paprika, dazu Mie Nudeln',
        'preis-intern' => "3.50",
        'preis-extern' => "6.20",
        'bild' =>  "rind.jpg"
    ],
    '1' => [ 'name' => 'Spinatrisotto mit kleinen Samosateigecken und gemischter Salat',
        'preis-intern' => "3.50",
        'preis-extern' => "6.20",
        'bild' =>  "spina.jpg"
    ],
    '2' => [ 'name' => 'Türkische Lahmacun',
        'preis-intern' => "3.96",
        'preis-extern' => "6.97",
        'bild' =>  "lahmacun.jpg"

    ],
    '3' => [ 'name' => 'Hähnchenbrust, Jalapenós, Paprika und Ei',
        'preis-intern' => "4.98",
        'preis-extern' => "9.99",
        'bild' =>  "hahn.jpg"
    ]
);


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
    else if (gueltigerName()== false)
    {
        echo '<p style = "color: red">(Benutzer-)Name kann nicht leer sein'.'<br>';
    }

    else if (gueltigeEmail() == false)
    {
        echo '<p style = "color: red">Diese E-Mail entspricht nicht den Vorgaben'.'<br>';
    }

    else if (gueltigerName() == true && gueltigeEmail() == true)
    {
        $file = fopen("daten.txt",'a');
        $VerarbeiteteString = StrEdit();
        fwrite($file, $VerarbeiteteString."\n");
        echo '<p style = "color: green">Daten wurden erfolgreich abgespeichert';
    }
}

function StrEdit()
{
    return $_POST['user'].";".$_POST['email'].";".$_POST['language'].".";
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
            <th></th>
            <th>Preis Intern</th>
            <th>Preis extern</th>
            <th>Bild</th>
        </tr>
        </thead>
        <tbody>
        <?php
        foreach ($meals as $index => $key) {
            echo "<tr>";
            echo "<td>" . $meals[$index]['name'] . "</td>";
            echo "<td>" . $meals[$index]['preis-intern'] . "</td>";
            echo "<td>" . $meals[$index]['preis-extern'] . "</td>";
            echo "<td>" . '<img src="./bilder/'.$meals[$index]['bild'].'" alt="Photo of food">'. "</td>";
            echo "</tr>";
        }
        ?>
        </tbody>
    </table>

    <h2 id="zahlen">E-Mensa in Zahlen</h2>
    <div class="gridbutton3">
        <div>
            10 Besucher
        </div>
        <div>
            20 Anmeldungen zum Newsletter
        </div>
        <div>
            30 Speisen
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