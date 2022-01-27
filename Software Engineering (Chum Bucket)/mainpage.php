<?php
/*
 * @title AktivitÃ¤t 20
 * @description Hauptseite des Studierenden anzeigen
 * @author Thanh Dat Tan
 */
include_once 'u20.php';

if ( isset($_GET['deldialog']) && (int)$_GET['deldialog'] === 1)
{
 echo '
<dialog open>
    <form method="post" action="mainpage.php">
        <div class="inhalt">
            <div class="topbar">Konto L&ouml;schen</div>
        </div>

        <input type="submit" value="X" class="X">'. csrf_token_tag() .'
        <div class="dialogtext">
            Durch diese Aktion werden Ihr Benutzerkonto, <br>
            s&auml;mtliche benutzerbezogene Daten sowie Ihr <br>
            Studienverlaufsplan gel&ouml;scht. <br>
            M&ouml;chten Sie wirklich fortfahren? <br> <br>
        </div>
       

            <button type="reset" class="normalbutton" onclick="location.href=\'mainpage.php\'">  Abbrechen </button>
            <input type="submit" value="Best&auml;tigen" class="greenbutton" name="delete">
    </form>
</dialog>';
}

if ( isset($_GET['deldialog']) && (int)$_GET['deldialog'] === 2 )
{
    echo '
<dialog open>
    <form method="post" action="mainpage.php">
        <div class="container">
            <div class="topbar">Studienverlaufsplan zur&uuml;cksetzen</div>
        </div>
        <input type="submit" value="X" class="X"> '. csrf_token_tag() .'
        <div class="dialogtext">
            Durch diese Aktion wird Ihr pers&ouml;nlicher  <br>
            Studienverlaufsplan gel&ouml;scht. Sie gelangen anschlie&szlig;end <br>
            in die Konfigurations&uuml;bersicht. <br>
            M&ouml;chten Sie wirklich fortfahren? <br> <br>
        </div>
       
            <button type="reset" class="normalbutton" onclick="location.href=\'mainpage.php\'">  Abbrechen </button>
            <input type="submit" value="Best&auml;tigen" class="greenbutton" name="reset_svp">
    </form>
</dialog>';
}

if (isset($_POST['reset_svp'], $_SESSION['email'],  $_SESSION['csrf_token'], $_POST['csrf_token'] ) && $_POST['csrf_token'] === $_SESSION['csrf_token']) {
    include_once ('includes/SimpleDB.php');
    include_once ('includes/db.inc.php');
    $link = connectdb();

    $sdb = new SimpleDB();
    $sdb->setLink($link);
    $result_svp = $sdb->bind('SELECT stud.studienverlaufsplan_id, stud.benutzer_id, stud.matrikelnummer, stud.studiengang_id FROM student stud JOIN benutzer b on stud.benutzer_id = b.id WHERE b.email = ?', 's', [$_SESSION['email']]);
    if ($result_svp) {
        $student = $result_svp->fetch_object();
        $result_sem = $sdb->bind('SELECT sem.id FROM semester sem WHERE sem.studienverlaufsplan_id = ?', 'i', [$student->studienverlaufsplan_id]);
        if ($result_sem) {
            while($semester = $result_sem->fetch_object()) {
                $test = $sdb->tearDownTable('semester_hat_modul', "semester_id = $semester->id");
            }
        }
        $sdb->tearDownTable('semester', "studienverlaufsplan_id = $student->studienverlaufsplan_id");
        $sdb->tearDownTable('studienverlaufsplan', "id = $student->studienverlaufsplan_id");

        // Reset Studienverlaufsplan
        $sdb->seedTableRow('student',
            [
                'benutzer_id' => $student->benutzer_id,
                'matrikelnummer' => $student->matrikelnummer,
                'studienverlaufsplan_id' => 1,
                'studiengang_id' => $student->studiengang_id
            ]
            , 'iiii');

        //$sdb->bind('UPDATE student SET no_config_flag = ? WHERE email = ?', 'is', [true, $_SESSION['email']]);
        Header( 'Location: /a410.php' );
    }
}


if ( isset($_POST['delete'], $_SESSION['email'], $_SESSION['csrf_token'], $_POST['csrf_token'] ) && $_POST['csrf_token'] === $_SESSION['csrf_token'])
{
    include_once ('includes/db.inc.php');
    $link = connectdb();

    $email = $_SESSION['email'];
    $result = $link->query("SELECT id FROM benutzer WHERE benutzer.email = '$email'"); //sucht die ID von der DB die mit der angemeldeten Email übereinstimmt
    $email = null;

    while($row = $result->fetch_assoc()) {
        $id = $row["id"];   //speichert die ID des gerade angemeldeten Benutzers in $id
    }

    $result = $link->query("DELETE FROM benutzer WHERE benutzer.id = '$id'");

    Header( 'Location: /index.php' );
}

?>
<!DOCTYPE html>
<html lang="de">
<head>
    <title>Hauptseite Studierende</title>
    <link rel="stylesheet" href="/css/mainpage.css">
    <link rel="stylesheet" href="/css/dialog-style.css">
    <script src='https://kit.fontawesome.com/a076d05399.js'></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/dompurify/2.2.6/purify.min.js"></script>
    <script src="/js/mainpage.min.js"></script>
    <noscript>
        <style type="text/css">
            .container {display:none;}
            .board {display:none;}
        </style>
        <div class="noscriptmsg">
            You don't have javascript enabled.  Please enable Javascript.
        </div>
    </noscript>
</head>

<body>
<div class="maincontainer">
    <i class="fa fa-book" aria-hidden="true"></i>
    <div class="info">
        <h1>Mein Studienverlaufsplan</h1>
        <nav role='navigation'>
            <div id="menuToggle">
                <!--
                A fake / hidden checkbox is used as click reciever,
                so you can use the :checked selector on it.
                -->
                <input type="checkbox" />

                <!--
                Some spans to act as a hamburger.

                They are acting like a real hamburger,
                not that McDonalds stuff.
                -->
                <span></span>
                <span></span>
                <span></span>

                <!--
                Too bad the menu has to be inside of the button
                but hey, it's pure CSS magic.
                -->
                <ul id="menu">
                    <a href="/index.php"><li>Abmelden</li></a>
                    <a href="/mainpage.php?deldialog=2"><li>Studienverlaufsplan zur&uuml;cksetzen</li></a>
                    <a href="/mainpage.php?deldialog=1"><li>Konto l&ouml;schen</li></a>
                </ul>
            </div>
        </nav>


        <p class="under"><?php get_name_veroeffentlichungsjahr_po_from_studienverlaufsplan(); ?></p>
        Eingeloggt als <a id="logged_in"><?php logged_in(); ?></a>
    </div>
</div>

<div class="board" ondrop='drop(event)' ondragover='allowDrop(event)'>
    <div class="modules-board">

    </div>
</div>

<div id="studienverlaufsplan" class="board">
    <div class="semester-board">
        <button id="semester-button-add" onclick="addNewSemester()">
            <i class="fas fa-plus-circle">

            </i>
        </button>
    </div>
</div>

</body>

</html>