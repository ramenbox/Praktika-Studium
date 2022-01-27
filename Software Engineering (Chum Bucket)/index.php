<?php

//session_start(); //cleared die Session falls abgemeldet wurde
//$_SESSION['email'] = null;
$maxlifetime = 0; // Bis Browser closed
$secure = true; // if you only want to receive the cookie over HTTPS
$httponly = true; // prevent JavaScript access to session cookie
$samesite = 'lax';

session_set_cookie_params([
    'lifetime' => $maxlifetime,
    'path' => '/',
    'domain' => $_SERVER['HTTP_HOST'],
    'secure' => $secure,
    'httponly' => $httponly,
    'samesite' => $samesite
]);

session_start();
session_unset();

$email = $_POST['email'] ?? null;
$pw = $_POST['pw'] ?? null;

$fehler = false;
$accountFound = false;
$id = null;

include_once ('dbconfig/config.php');
$link = dbconnect();
?>

<link rel="stylesheet" href="css/LoginStyle.css">


<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <title> Anmelden</title>
</head>
<body>

<aside class="leftbar">
bar
</aside>
<aside class="rightbar">
bar
</aside>

<main>
    <div class="container-fluid text-center">
        <div class="row content">
            <div class="col-md-2 sidenav">
            </div>
            <p>
            <form action="index.php" method="post">
                <div><img src="img/swe.png" width="500" height="250" alt="bild" id="sewB"><br></div>
                <div><br></div>
                <h2>Anmelden</h2></p>

                <?php

                if ( isset($_GET['success']) && $_GET['success'] == 1 )
                {
                    echo "Registrierung erfolgreich, Sie k&ouml;nnen sich jetzt hier anmelden. <br>";
                }


                ?>
                <div><br></div>

                <?php


                if (isset($_POST['email']) && (!filter_var($email, FILTER_VALIDATE_EMAIL))) { //validiere Email
                    //echo 'Bitte �berpr�fen Sie Ihre Email Adresse <br>';
                    $fehler = true;
                } else if (isset($_POST['email'])) { //test ob es eine valide alumni email ist
                    $emailtest = $email;
                    $n = strpos($emailtest, '@');
                    $emailtest = substr($emailtest, $n + 1, strlen($emailtest));
                    if (($emailtest != 'alumni.fh-aachen.de')) { //test auf alumni
                        //echo 'Ihre Email Adresse muss der alumni Email entsprechen <br>';
                        $fehler = true;
                    }
                }

                if (empty($pw) && isset($_POST['pw'])) {
                    //echo 'Bitte geben Sie ein Passwort ein <br>';
                    $fehler = true;
                }


                $pw = hash('sha256', $pw); //erstelle hash vom passwort
                $sql = "select email, passwort from benutzer";
                $result = mysqli_query($link, $sql);
                while ($row = mysqli_fetch_assoc($result))
                {
                    if($email == $row['email'] && $pw == $row['passwort']) //testet email und passwort kombination
                    {
                        $accountFound = true;
                        break;
                    }
                }

                if (isset($_POST['email']) && $accountFound == false) //wenn keine email und passwort kombination gefunden wurde
                {
                    $fehler = true;
                }


                if ($fehler == true) //falls es irgendwo einen fehler gab
                {
                    echo '
    <dialog open>
        <form method="dialog">
                <i style="color:red;font-size:15px;">
                Fehler! Dein eingegebenes Passwort passt entweder nicht zu der E-Mail-<br>
                Adresse oder es existiert kein Account mit dieser E-Mail-Adresse. Bitte<br>
                verusche es erneut<br> <br> </i></label>
                <button type="submit">Ok</button>
        </form>
    </dialog>';


                }
                else if (isset($_POST['email']) && $accountFound == true)
                {
                    session_start();
                    $_SESSION['email'] = $email;


                    $sql = "select kontotyp from benutzer where email = '$email'";
                    $result = mysqli_query($link, $sql);

                    while ($row = mysqli_fetch_assoc($result))
                    {
                        $kontotyp = $row['kontotyp'];
                    }

                    if($kontotyp == 'Student') //falls als Student angemeldet wurde
                    {
                        echo '<dialog open><form method="dialog"><i style="color:green;font-size:15px;">Login Erfolgreich! <br>Sie werden automatisch weitergeleitet <br>';

                        $sql = "SELECT no_config_flag FROM student JOIN benutzer ON benutzer.id = student.benutzer_id WHERE benutzer.email = '$email'";
                        $result = $link->query($sql);
                        $no_config_flag = (bool)$result->fetch_assoc()['no_config_flag'];
                        if($no_config_flag)
                        {
                            echo '<a href="/a410.php">Oder Klicken Sie hier</a>
                    <script>setTimeout(function(){window.location.href="/a410.php"}, 3000)</script>';
                        } else {
                            echo '<a href="/mainpage.php">Oder Klicken Sie hier</a>
                    <script>setTimeout(function(){window.location.href="/mainpage.php"}, 3000)</script>';
                        }

                        echo '</form></dialog>';
                    }
                    else //wenn als verwalter angemeldet wurde
                    {
                        echo '
    <dialog open>
        <form method="dialog">
                <i style="color:green;font-size:15px;">
                    Login Erfolgreich! <br>
                    Sie werden automatisch weitergeleitet <br>
                    <a href="ListenansichtVerwalterU30.php">Oder Klicken Sie hier</a>
                    <script>setTimeout(function(){window.location.href="ListenansichtVerwalterU30.php"}, 3000)</script>
        </form>
    </dialog>';
                      header("Refresh:3; ListenansichtVerwalterU30.php");
                    }


                }


                ?>
                <div><input type="text" name="email" placeholder="E-Mail" value="<?php echo htmlspecialchars($email, ENT_QUOTES | ENT_HTML5) ?>"></div>
                <div><br></div>
                <div><input type="password" name="pw" placeholder="Passwort" value=""></div>
                <div><br></div>
                <p><input type="submit" value="Anmelden"/></p>
                <h3> <a href="Registrierung.php">Kein Konto? Konto erstellen</a></h3>
            </form>
        </div>
    </div>
</main>
</body>
</html>