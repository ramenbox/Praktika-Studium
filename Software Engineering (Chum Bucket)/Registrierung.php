<?php
session_start();
$vorname = $_POST['vorname'] ?? null;
$nachname = $_POST['nachname'] ?? null;
$email = $_POST['email'] ?? null;
$matrikel = $_POST['matrikel'] ?? null;
$pw1 = $_POST['pw1'] ?? null;
$pw2 = $_POST['pw2'] ?? null;
$date = date('Y-m-d H:i:s');


//echo "$vorname   $nachname   $email   $matrikel   $pw1   $pw2";
$fehler = false;

include_once ('dbconfig/config.php');
$link = dbconnect();
$link->set_charset('utf8mb4');
?>
<link rel="stylesheet" href="css/RegisterStyle.css">

<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <title>Registrieren</title>


</head>
<body>
<main>
    <aside class="leftbar">
        bar
    </aside>
    <aside class="rightbar">
        bar
    </aside>
    <div class="container-fluid text-center">
        <div class="row content">
            <div class="col-md-2 sidenav">
            </div>

            <p>
            <h2>Registrieren</h2></p>
            <form action="Registrierung.php" method="post">
                <div><img src="img/swe.png" width="500" height="250" alt="bild" id="sewB"><br></div>
                <div><br></div>
                <?php


                if (isset($_POST['vorname']) && empty(trim($vorname))) { //test ob der vorname leer ist
                    //echo 'Bitte geben Sie ihren Vornamen ein <br>';
                    $fehler = true;
                }
                if (isset($_POST['nachname']) && empty(trim($nachname))) { //test ob nachname leer ist
                    //echo 'Bitte geben Sie ihren nachname ein <br>';
                    $fehler = true;
                }
                if (isset($_POST['email']) && (!filter_var($email, FILTER_VALIDATE_EMAIL))) { //validiere Email
                    //echo 'Bitte überprüfen Sie Ihre Email Adresse <br>';
                    $fehler = true;
                } else if (isset($_POST['email'])) { //test ob es eine valide alumni email ist
                    $emailtest = $email;
                    $n = strpos($emailtest, '@');
                    $emailtest = substr($emailtest, $n + 1, strlen($emailtest));
                    $vornametest = stristr($email, '@', true);
                    $nachnametest = stristr($vornametest, '.');
                    $nachnametest = str_replace('.', '', $nachnametest);

                    $vornametest = stristr($vornametest, '.', true);

                    $vornametest = strtolower($vornametest);
                    $nachnametest = strtolower($nachnametest);

                    if (($emailtest != 'alumni.fh-aachen.de')) { //test auf alumni
                        //echo 'Ihre Email Adresse muss der alumni Email entsprechen <br>';
                        $fehler = true;
                    }
                    else if($vornametest != strtolower($_POST['vorname']))//test der richtige Vorname //getrennt vom Punkt
                    {
                        //echo 'Ihre Vorname muss in der alumni E-Mail enthalten sein <br>';
                        $fehler = true;
                    }
                    else if($nachnametest != strtolower($_POST['nachname']))//test der richtige Vorname //getrennt vom Punkt
                    {
                        //echo 'Ihre Vorname muss in der alumni E-Mail enthalten sein <br>';
                        $fehler = true;
                    }
                }
                if (empty(trim($matrikel)) && isset($_POST['matrikel'])) //testet ob die textbox mit der Matrikelnummer nicht leer ist
                {
                    //echo 'Bitte geben Sie Ihre Matrikelnummer ein <br>';
                    $fehler = true;
                }
                else
                    {
                    if (strlen((string)$matrikel) >= 7 && strlen((string)$matrikel) < 11)//teste ob die matrikelnummer min 7 zeichen lang ist
                    {
                        if (is_numeric($matrikel)) //testet ob die matrikelnummer nur aus zahlen besteht
                        {
                            //matrikelnummer gültig
                        }
                        else
                            {
                            //echo "Ihre Matrikelnummer darf nur Zahlen enthalten <br>";
                            $fehler = true;
                        }

                    }
                    else if ($matrikel != 0)
                    {
                        //echo "Ihre Matrikelnummer muss 7 Zeichen Lang sein <br>";
                        $fehler = true;
                    }
                }

                if (empty($pw1) && isset($_POST['pw1'])) {
                    //echo 'Bitte geben Sie ein Passwort ein <br>';
                    $fehler = true;
                }

                if ($pw1 != $pw2) {
                    //echo 'Ihr Bestätigungspasswort war inkorrekt <br>';
                    $fehler = true;
                }

                $matrikel = $link->real_escape_string($matrikel);

                $result = $link->query("SELECT matrikelnummer FROM student WHERE matrikelnummer = '$matrikel'");
                if ($result->num_rows > 0) //testet ob die matrikelnummer bereits existiert
                {
                    $fehler = true;
                    //echo "Matrikelnummer bereits registriert <br>";
                }

                $email = $link->real_escape_string($email);

                $result = $link->query("SELECT email FROM benutzer WHERE email = '$email'");
                if ($result->num_rows > 0)//testet ob die email bereits existiert
                {
                    $fehler = true;
                    //echo "Email bereits registriert <br>";
                }


                if ($fehler == true) //falls es irgendwo einen fehler gab
                {
                    echo '
    <dialog open>
        <form method="dialog">
                <i style="color:red;font-size:15px;">
                Fehler! Ihre eingegebenen Daten entsprechen nicht dem vorgegebenen Format <br>
                (Vorname.Nachname@alumni.fh-aachen.de) (Matrikelnummer muss zwischen 7 und 10 Ziffern haben) <br>
                oder es existiert bereits ein Account mit diesen Daten <br> <br> </i></label>
                <button type="submit">Ok</button>
        </form>
    </dialog>';


                } else if (isset($_POST['vorname'])) //sonst in die DB einfügen
                {
                    $pw1 = hash('sha256', $pw2);

                    //$vorname = $link->real_escape_string($vorname);
                    //$nachname = $link->real_escape_string($nachname);


                    /*$sql = "INSERT INTO student (email, password, vorname, nachname, zweitname, matrikelnummer, semester)
                                VALUES ('$email', '$pw1', '$vorname', '$nachname', null, '$matrikel', 0)";  alter insert*/

                    $sql = "INSERT INTO benutzer (kontotyp, email, passwort, vorname, nachname, erstellt_am)
                            VALUES ('Student', '$email', '$pw1', '$vorname', '$nachname', '$date')";
                    mysqli_query($link, $sql);
                    $last_id = $link->insert_id; //$last_id = die letzte ID die in benutzer eingefügt wurde

                    $sql = "INSERT INTO student (benutzer_id, matrikelnummer, studienverlaufsplan_id, studiengang_id, fachsemester)
                            VALUES('$last_id', '$matrikel', 1, 1, 0)";
                    mysqli_query($link, $sql);

                    $_SESSION['email'] = $email;

                    echo '
    <dialog open>
        <form method="dialog">
                <i style="color:green;font-size:15px;">
                    Eingabedaten erfolgreich gespeichert <br>
                    Sie werden automatisch weitergeleitet <br>
                    <a href="/a410.php">Hier bitte klicken falls Sie nicht weitergeleitet werden</a>
                    <script>setTimeout(function(){window.location.href="/a410.php"}, 3000)</script>
        </form>
    </dialog>';

                    //Header( 'Location: index.php?success=1' );
                }


                ?>


                <div><br></div>
                <div><br></div>
                <div><input type="text" name="vorname" placeholder="Vorname" value="<?php echo htmlspecialchars($vorname, ENT_QUOTES | ENT_HTML5) ?>">
                </div>
                <div><input type="text" name="nachname" placeholder="Nachname" value="<?php echo htmlspecialchars($nachname, ENT_QUOTES | ENT_HTML5) ?>">
                </div>
                <div><input type="text" name="email" placeholder="E-Mail" value="<?php echo htmlspecialchars($email, ENT_QUOTES | ENT_HTML5) ?>"></div>
                <div><input type="text" name="matrikel" placeholder="Matrikelnummer"
                            value="<?php echo htmlspecialchars($matrikel, ENT_QUOTES | ENT_HTML5) ?>"></div>
                <div><input type="password" name="pw1" placeholder="Passwort" value=""></div>
                <div><input type="password" name="pw2" placeholder="Passwort Bestätigen" value=""></div>
                <div><br></div>
                <p><input type="submit" value="Registrieren"/></p>
            </form>
        </div>
    </div>
</main>
</body>
</html>

