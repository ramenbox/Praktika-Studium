<?php
include_once ('ListenansichtVerwalterFunktionen.php');

session_start();
$kontotyp = get_kontotyp($_SESSION['email']);

if($kontotyp !== 'Verwalter')
{
    echo '<link rel="stylesheet" href="css/acess_denied.css">';
    echo '<div class="garfield_text"> Sie verfügen nicht über die benötigten Rechte um, auf diese Seite zuzugreifen</div> ';
    echo '<img class="garfield" src="img/AccessDenied.svg">';
    echo '<div class="garfield_text">Bitte versuchen Sie sich erneut <a class="garfield_link" href="index.php">Einzuloggen</a></div>';

    exit();
}

    include_once ('dbconfig/config.php');
    $link = dbconnect();
?>
<link rel="stylesheet" href="css/VerwaltungStudienverlaufsplanStyle.css">
<link rel="stylesheet" href="css/dialog-style.css">
<script type='text/javascript' src='js/jquery/jquery-3.5.1.js'></script>
<script type='text/javascript' src='js/jquery/jquery-ui.js'></script>
<script type='text/javascript' src='js/VerwaltungStudienverlaufsplan.js'></script>

<?php
$verlaufplanID = $_SESSION['verlaufsplanid']; //die ID vom Studienverlaufsplan als session ID

$modul_id = $_POST['modul_id'] ?? null;
$modul_name = $_POST['modul_name'] ?? null;
$veränderbar = $_POST['vb'] ?? null;
$prüfung = $_POST['prüfung'] ?? null;
$praktikum = $_POST['praktikum'] ?? null;
$vorlesung = $_POST['vorlesung'] ?? null;
$winter = $_POST['winter'] ?? null;
$sommer = $_POST['sommer'] ?? null;
$credits = $_POST['credits'] ?? null;
$po = $_POST['po'] ?? null;

$fehler = false;

if (isset($_GET['p']) && isset($_GET['c']))
{
    $parent = $_GET['p'];
    $child = $_GET['c'];

    $sql = "UPDATE studienverlaufsplan_data SET fachsemester = '$parent'
            WHERE verlaufsplan_id = '$verlaufplanID' AND modul_id = '$child'";
    mysqli_query($link, $sql);


    //echo "$parent $child";

}

if (isset($_POST['alter'])) //wenn das modul nur bearbeitet werden soll. alter steht für das englische wort to alter nicht das Alter
{
    $id = $_POST['alter'];

    if($veränderbar == 'on')
        $veränderbar = 1;
    else
        $veränderbar = 0;

    if($prüfung == 'on')
        $prüfung = 1;
    else
        $prüfung = 0;

    if($praktikum == 'on')
        $praktikum = 1;
    else
        $praktikum = 0;

    if($vorlesung == 'on')
        $vorlesung = 1;
    else
        $vorlesung = 0;

    if($winter == 'on')
        $winter = 1;
    else
        $winter = 0;

    if($sommer == 'on')
        $sommer = 1;
    else
        $sommer = 0;

   // echo "$id $modul_id  $modul_name $veränderbar $prüfung $praktikum $vorlesung $winter $sommer $credits $po";

    $sql = "UPDATE modul SET modulcode='$modul_id',
                             modulname='$modul_name',
                             anzeigename_veraenderbar='$veränderbar',
                             pruefung='$prüfung',
                             praktikum='$praktikum',
                             vorlesung='$vorlesung',
                             wintersemester='$winter',
                             sommersemester='$sommer',
                             leistungspunkte='$credits',
                             pruefungsordnung='$po'
            WHERE id='$id'";
    mysqli_query($link, $sql);
}

if (isset($_GET['del_approved']))
{
    $id = $_GET['del_approved'];

    $sql = "DELETE FROM modul WHERE id = '$id'";
    mysqli_query($link, $sql);

    $sql = "delete from studienverlaufsplan_data where modul_id = '$id'";
    mysqli_query($link, $sql);
}

if (isset($_GET['delete'])) //wenn auf den roten modul löschen button gedrückt wird
{
    $id = $_GET['delete'];
    /*

    $sql = "DELETE FROM modul WHERE id = '$id'";
    mysqli_query($link, $sql);*/

    echo"<dialog open>
    <form method=\"post\" action=\"\"> <!-- action = die Datei zu der gesendet werden soll -->
        <div class=\"container\">
            <div class=\"topbar\">Bestätigen</div> <!-- Der Graue Balken oben mit Überschrift -->
        </div>

        <button type=\"reset\" class=\"X\" onclick=\"location.href='VerwaltungStudienverlaufsplan.php?id=$id'\">
            X
        </button> <!-- Der X button oben Rechts -->

        <div class=\"dialogtext\">
            Sind Sie sicher, dass Sie dieses <br>
            Modul Löschen möchten? <!-- Text -->
        </div>


        <button type=\"reset\" class=\"normalbutton\" onclick=\"location.href='VerwaltungStudienverlaufsplan.php?id=$id'\">
            Abbrechen
        </button>

        <button type=\"reset\" class=\"greenbutton\" onclick=\"location.href='VerwaltungStudienverlaufsplan.php?del_approved=$id'\">
            Bestätigen
        </button>

        
    </form>
</dialog>";
}

if (isset($_GET['id'])) //wenn auf gear icon gedrückt wird
{
    $id = $_GET['id'];

    $result = $link->query("select * from modul where id = '$id'"); //wählt die reihe aus der DB in der id = $id

    while($row = $result->fetch_assoc())
    {
        $id = $row["id"];
        $mc = $row["modulcode"];
        $mn = $row["modulname"];
        $aznvb = $row["anzeigename_veraenderbar"];
        $prue = $row["pruefung"];
        $pra = $row["praktikum"];
        $vl = $row["vorlesung"];
        $ws = $row["wintersemester"];
        $ss = $row["sommersemester"];
        $lp = $row["leistungspunkte"];
        $ordnung = $row["pruefungsordnung"];

        /*
        echo $row["id"]." ".
            $row["modulcode"]." ".
            $row["modulname"]." ".
            $row["anzeigename_veraenderbar"]." ".
            $row["pruefung"]." ".
            $row["praktikum"]." ".
            $row["vorlesung"]." ".
            $row["wintersemester"]." ".
            $row["sommersemester"]." ".
            $row["leistungspunkte"]." ".
            $row["pruefungsordnung"];*/
    }
    if($aznvb)
        $aznvb = "checked";
    if($prue)
        $prue = "checked";
    if($pra)
        $pra = "checked";
    if($vl)
        $vl = "checked";
    if($ws)
        $ws = "checked";
    if($ss)
        $ss = "checked";


    if($ordnung === "2015/18")
        $po1518 = 'selected';
    if($ordnung === "2018/19")
        $po1819 = 'selected';

    echo"<dialog open>
    <form method=\"post\" action=\"VerwaltungStudienverlaufsplan.php\"> <!-- action = die Datei zu der gesendet werden soll -->
        <div class=\"container\">
            <div class=\"topbar\">Modul Erstellen</div> <!-- Der Graue Balken oben mit Überschrift -->
        </div>
        
        <button type=\"reset\" class=\"X\" onclick=\"location.href='VerwaltungStudienverlaufsplan.php'\">
            X
        </button>
        
        <div style=\"margin-top: 20px\">Modul ID:
            <input style=\"margin-left: 19px\" type=\"number\" min=\"0\" name=\"modul_id\" value=\"$mc\">
        </div>
        
        <div style=\"margin-top: 5px\">Modulname:
            <input  type=\"text\" name=\"modul_name\" value=\"$mn\">
        </div>
        
        <div style=\"margin-top: 20px\">
            <label class=\"check_label\"><input type=\"checkbox\" $aznvb name=\"vb\">Anzeigename Veränderbar</label>
        </div>
        
        <div style=\"margin-top: 5px\">
            <label class=\"check_label\"><input type=\"checkbox\" $prue name=\"prüfung\">Prüfung</label>
        </div>
        
        <div style=\"margin-top: 5px\">
            <label class=\"check_label\"><input type=\"checkbox\" $pra name=\"praktikum\">Praktikum</label>
        </div>
        
        <div style=\"margin-top: 5px\">
            <label class=\"check_label\"><input type=\"checkbox\" $vl name=\"vorlesung\">Vorlesung</label>
        </div>
        
        <div style=\"margin-top: 5px\">
            <label class=\"check_label\"><input type=\"checkbox\" $ws name=\"winter\">Im Wintersemester belegbar</label>
        </div>
        
        <div style=\"margin-top: 5px\">
            <label class=\"check_label\"><input type=\"checkbox\" $ss name=\"sommer\">Im Sommersemester belegbar</label>
        </div>
        
        <div style=\"margin-top: 5px\">Credits:
            <input  type=\"number\" min=\"0\" name=\"credits\" value=\"$lp\">
        </div>
        
        <div style=\"margin-top: 5px\">Prüfungsordnung:
        <select name=\"po\" id=\"po\">
         <option value=\"2015/18\" $po1518 >PO 2015/2018</option>
            <option value=\"2018/19\" $po1819 >PO 2018/2019</option>
            </select></div>
        
        <div class=\"dialogtext\">
             <!-- Hier kommt Text  -->
        </div>
        <button type=\"reset\" class=\"normalbutton\" onclick=\"location.href='VerwaltungStudienverlaufsplan.php'\"> <!-- sendet via GET daten die an die URL via ?daten=1 angehängt werden -->
            Abbrechen
        </button>

        <input  hidden class=\"alter\" type=\"text\" name=\"alter\" value=\"$id\">
        <input type=\"submit\" value=\"Speichern\" class=\"greenbutton\" name=\"delete\"> 
        
        <br>
        <img class=\"tonne\" src=\"img/tonne.png\" alt=\"del\">
        <button type=\"reset\" class=\"löschenbutton\" onclick=\"location.href='VerwaltungStudienverlaufsplan.php?delete=$id'\">
         Modul Löschen
        </button>
    </form>
</dialog>";

}


if ($_SERVER['REQUEST_METHOD'] == 'POST') //wenn die Form gesendet wurde
{
    if (!isset($_POST['prüfung']) && !isset($_POST['praktikum']) && !isset($_POST['vorlesung']) ) //aber prüfung vorlesung und praktikum leer sind
    {
        $fehler = true;
        echo'<dialog open>
    <form method="" action=""> 
        <div class="container">
            <div class="topbar">Fehler!</div> 
        </div>

        <input type="submit" value="X" class="X"> 

        <div class="dialogtext">
            Bitte wählen Sie mindestens eine der  <br>
            Veranstaltungen des Moduls <br> 
            (entweder das Praktikum, die Prüfung oder <br>
            die Vorlesung) aus!
        </div>
        
    </form>
</dialog>';
    }


    if (empty($_POST['modul_id']) || empty($_POST['modul_name'])) //wenn modul_id und modul_name leer sind
    {
        $fehler = true;
        echo'<dialog open>
    <form method="" action=""> 
        <div class="container">
            <div class="topbar">Fehler!</div> 
        </div>

        <button type="reset" class="X" onclick="location.href=\'VerwaltungStudienverlaufsplan.php?create_modul=1\'"> <!-- sendet via GET daten die an die URL via ?daten=1 angehängt werden -->
            X
        </button>

        <div class="dialogtext">
            Modul id und Modul name dürfen nicht leer sein!
        </div>
        
    </form>
</dialog>';
    }
}

if ( isset($_GET['create_modul']) && $_GET['create_modul'] == 1 )
{
    echo'<dialog open>
    <form method="post" action="VerwaltungStudienverlaufsplan.php"> <!-- action = die Datei zu der gesendet werden soll -->
        <div class="container">
            <div class="topbar">Modul Erstellen</div> <!-- Der Graue Balken oben mit Überschrift -->
        </div>

        
        <button type="reset" class="X" onclick="location.href=\'VerwaltungStudienverlaufsplan.php\'">
            X
        </button>
        
        <div style="margin-top: 20px">Modul ID:
            <input style="margin-left: 19px" type="number" min=\"0\" name="modul_id" value="">
        </div>
        
        <div style="margin-top: 5px">Modulname:
            <input  type="text" name="modul_name" value="">
        </div>
        
        <div style="margin-top: 20px">
            <label class="check_label"><input type="checkbox" name="vb">Anzeigename Veränderbar</label>
        </div>
        
        <div style="margin-top: 5px">
            <label class="check_label"><input type="checkbox" name="prüfung">Prüfung</label>
        </div>
        
        <div style="margin-top: 5px">
            <label class="check_label"><input type="checkbox" name="praktikum">Praktikum</label>
        </div>
        
        <div style="margin-top: 5px">
            <label class="check_label"><input type="checkbox" name="vorlesung">Vorlesung</label>
        </div>
        
        <div style="margin-top: 5px">
            <label class="check_label"><input type="checkbox" name="winter">Im Wintersemester belegbar</label>
        </div>
        
        <div style="margin-top: 5px">
            <label class="check_label"><input type="checkbox" name="sommer">Im Sommersemester belegbar</label>
        </div>
        
        <div style="margin-top: 5px">Credits:
            <input  type="number" min="0" name="credits" value="0">
        </div>
        
        <div style="margin-top: 5px">Prüfungsordnung:
        <select name="po" id="po">
         <option value="2015/18">PO 2015/2018</option>
            <option value="2018/19">PO 2018/2019</option>
            </select></div>
        
        <div class="dialogtext">
             <!-- Hier kommt Text  -->
        </div>
        <button type="reset" class="normalbutton" onclick="location.href=\'VerwaltungStudienverlaufsplan.php\'"> <!-- sendet via GET daten die an die URL via ?daten=1 angehängt werden -->
            Abbrechen
        </button>

        <input type="submit" value="Speichern" class="greenbutton" name="delete"> <!-- sendet via POST die daten von name=""-->
    </form>
</dialog>';
}

if (($_SERVER['REQUEST_METHOD'] == 'POST') && ($fehler == false) && !isset($_POST['alter']))
{
    /*$sql = "INSERT INTO student (email, password, vorname, nachname, zweitname, matrikelnummer, semester)
             VALUES ('$email', '$pw1', '$vorname', '$nachname', null, '$matrikel', 0)";*/


    if($veränderbar == 'on')
        $veränderbar = 1;
    else
        $veränderbar = 0;

    if($prüfung == 'on')
        $prüfung = 1;
    else
        $prüfung = 0;

    if($praktikum == 'on')
        $praktikum = 1;
    else
        $praktikum = 0;

    if($vorlesung == 'on')
        $vorlesung = 1;
    else
        $vorlesung = 0;

    if($winter == 'on')
        $winter = 1;
    else
        $winter = 0;

    if($sommer == 'on')
        $sommer = 1;
    else
        $sommer = 0;


    //echo "$modul_id  $modul_name $veränderbar $prüfung $praktikum $vorlesung $winter $sommer $credits $po";


    $sql = "INSERT INTO modul (modulcode, modulname, anzeigename_veraenderbar, pruefung, praktikum, vorlesung, wintersemester, sommersemester, leistungspunkte, pruefungsordnung)
            VALUE ('$modul_id','$modul_name','$veränderbar', '$prüfung', '$praktikum', '$vorlesung', '$winter', '$sommer', '$credits', '$po')";
    mysqli_query($link, $sql);
    $last_id = $link->insert_id; //$last_id = die letzte ID die in modul eingefügt wurde



    $result = $link->query("SELECT DISTINCT verlaufsplan_id from studienverlaufsplan_data");
    while($row = $result->fetch_assoc())
    {
        $id = $row["verlaufsplan_id"];

        $sql = "INSERT INTO studienverlaufsplan_data VALUES ('$id', $last_id, 0);";
        mysqli_query($link, $sql);
        //echo "$id ";
    }
}

?>
<!-- sandwitch menu -->
<nav role="navigation">
    <div id="menuToggle">
        <input type="checkbox" />
        <span></span>
        <span></span>
        <span></span>
        <ul id="menu">
            <a href="index.php" target="_self"><li>Abmelden</li></a>
            <a href="ListenansichtVerwalterU30.php" target="_self"><li>Zurück</li></a>
        </ul>
    </div>
</nav>

<div id="0" class="fenster 0" style="height: 300px">
    <?php
    /*
    $result = $link->query("select * from modul");
    while($row = $result->fetch_assoc()) //trägt alle module in der DB in die Liste ein
    {
        echo create_modul($row["id"],$row["modulname"]);
    }
    */

    $result = $link->query("select * from
(
    select verlaufsplan_id, modul_id, fachsemester, modulname
    from studienverlaufsplan_data
    join modul where modul_id = modul.id
)g
where verlaufsplan_id = '$verlaufplanID'");


    while($row = $result->fetch_assoc()) //trägt alle module in der DB in die Liste ein
    {
        if($row["fachsemester"] == 0)
        echo create_modul($row["modul_id"],$row["modulname"]);
    }

    ?>
    <button id="modul_erstellen_button" onclick="location.href='VerwaltungStudienverlaufsplan.php?create_modul=1'">&#10010 Modul Erstellen</button>
</div>

<?php
    $semester = $link->query("select anzahl_fachsemester from studienverlaufsplan where id = '$verlaufplanID'");
while($row = $semester->fetch_assoc())
{
   $fachsemester = $row["anzahl_fachsemester"];
}




for($i = 1; $i < $fachsemester+1; $i++) //erzeugt anzahl an fenster für fachsemester und füllt es mit modulen
{
    $result = $link->query("select * from
(
    select verlaufsplan_id, modul_id, fachsemester, modulname
    from studienverlaufsplan_data
    join modul where modul_id = modul.id
)g
where verlaufsplan_id = '$verlaufplanID'");

    echo '<div class="fensterlabel">'.$i.'. Regelsemester</div>';
    echo '<div class="fenster" id="'.$i.'">';

    while($row = $result->fetch_assoc())
    {
        $semester= $row["fachsemester"];
        $id = $row["modul_id"];
        $name= $row["modulname"];

        if($i == $semester)
            echo create_modul($id, $name);
    }

    echo'</div>';
}

function create_modul($id, $name) //erzeugt den HTML code für ein modul mit $id und $name
{
    $string = "<div class=\"modul\" id=\"".$id."\">".$name."<div class=\"gear\" id=\"".$id."\"onclick=\"gear_function(this);\">&#9881</div></div>";
    return $string;
}

?>

