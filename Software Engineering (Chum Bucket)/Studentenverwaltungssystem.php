<?php
session_start();
echo "eingeloggt als: ".$_SESSION['email'];
?>
<meta charset="UTF-8">

<link rel="stylesheet" href="css/dialog-style.css">

<h3> <a href="index.php">Abmelden</a></h3>
<h3> <a href="Studentenverwaltungssystem.php?deldialog=1">Konto Löschen</a></h3>
<?php

//öffnet das Dialog um ein Konto zu Löschen falls der Get Parameter 'deldialog' gesetzt ist
if ( isset($_GET['deldialog']) && $_GET['deldialog'] == 1 )
{
    echo '
<dialog open>
    <form method="post" action="Studentenverwaltungssystem.php">
        <div class="container">
            <div class="topbar">Konto L&ouml;schen</div>
        </div>

        <input type="submit" value="X" class="X">

        <div class="dialogtext">
            Durch diese Aktion werden Ihr Benutzerkonto, <br>
            s&auml;mtliche benutzerbezogene Daten sowie Ihr <br>
            Studienverlaufsplan gel&ouml;scht. <br>
            M&ouml;chten Sie wirklich fortfahren? <br> <br>
        </div>
       

            <button type="reset" class="normalbutton" onclick="location.href=\'Studentenverwaltungssystem.php\'">  Abbrechen </button>
            <input type="submit" value="Best&auml;tigen" class="greenbutton" name="delete">
    </form>
</dialog>';
}

if ( isset($_POST['delete']))
{
    include_once ('dbconfig/config.php');
    $link = dbconnect();

    $email = $_SESSION['email'];
    $result = $link->query("SELECT id FROM benutzer WHERE benutzer.email = '$email'"); //sucht die ID von der DB die mit der angemeldeten Email übereinstimmt
    $email = null;

    while($row = $result->fetch_assoc()) {
        $id = $row["id"];   //speichert die ID des gerade angemeldeten Benutzers in $id
    }

    $result = $link->query("DELETE FROM benutzer WHERE benutzer.id = '$id'");

    Header( 'Location: index.php' );
}

?>

