<?php
include_once ('dbconfig/config.php');
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





$link = dbconnect();

if (isset($_GET['create']) && $_GET['create'] == 1 )
{
    $_GET['create'] = 0;
    echo '<script>setTimeout(function(){window.location.href="create_new_studienverlaufsplan.php"}, 0)</script>';
}

if (isset($_GET['id']))
{
    $id = $_GET['id'];
    $result = $link->query("select public from studienverlaufsplan where id = '$id'");
    $row = $result->fetch_assoc();


    $public = $row['public'];


    if($public == 1)
    {
        echo "
    <dialog open class='simpledialog'>
        <form method=\"dialog\">
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?details&id=$id'\">Details</button><br><br><br><br>
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?delete=0&id=$id'\">Löschen</button><br><br><br><br>
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?copy=0&id=$id'\">Duplizieren</button><br><br><br><br>
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">Abbrechen</button><br><br><br><br>              
        </form>
    </dialog>";
    }


    else if($public == 0)
    {
        echo "
    <dialog open class='simpledialog'>
        <form method=\"dialog\" >
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?alter=1&detid=$id'\">Details Bearbeiten</button><br><br><br><br>
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?verwalten&id=$id'\">Verwalten</button><br><br><br><br>
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?copy=0&id=$id'\">Duplizieren</button><br><br><br><br>
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?publish=0&id=$id'\">Veröffentlichen</button><br><br><br><br>
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?delete=0&id=$id'\">Löschen</button><br><br><br><br>
                    <button type=\"reset\" class=\"dialogbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">Abbrechen</button><br><br><br><br>              
        </form>
    </dialog>";
    }
}
if(isset($_GET['verwalten']) && isset($_GET['id']))
{
    //echo "test".$_GET['id'];
    $_SESSION['verlaufsplanid'] = $_GET['id'];
    echo '<script>setTimeout(function(){window.location.href="VerwaltungStudienverlaufsplan.php"}, 0)</script>';
}

if(isset($_GET['id']) && isset($_GET['publish']))
{
    $id = $_GET['id'];

    if($_GET['publish'] == 1){
        publish_svp($id);
        echo '<script>setTimeout(function(){window.location.href="ListenansichtVerwalterU30.php"}, 0)</script>';
    }
else {


    echo"<dialog open>
    <form method=\"post\" action=\"ListenansichtVerwalterU30.php\"> <!-- action = die Datei zu der gesendet werden soll -->
        <div class=\"container\">
            <div class=\"topbar\">Ver&ouml;ffentlichen</div> <!-- Der Graue Balken oben mit Überschrift -->
        </div>

        <button type=\"reset\" class=\"X\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            X
        </button> <!-- Der X button oben Rechts -->

        <div class=\"dialogtext\">
               Sind Sie sicher, dass Sie den ausgew&auml;hlten<br> Studienverlaufsplan ver&ouml;ffentlichen wollen? <br> <br>
        </div>

 
        <button type=\"reset\" class=\"normalbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            Abbrechen
        </button>

        <button type=\"reset\" class=\"greenbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?publish=1&id=$id'\">
            Ver&ouml;ffentlichen
        </button>

    </form>
</dialog>";
}

}



 if(isset($_GET['id']) && isset($_GET['delete']))
{
    $id = $_GET['id'];

    if($_GET['delete'] == 1){


        delete_svp($id);

        echo '<script>setTimeout(function(){window.location.href="ListenansichtVerwalterU30.php"}, 0)</script>';
    }
else{
    echo"<dialog open>
    <form method=\"post\" action=\"ListenansichtVerwalterU30.php\"> <!-- action = die Datei zu der gesendet werden soll -->
        <div class=\"container\">
            <div class=\"topbar\">Löschen</div> <!-- Der Graue Balken oben mit Überschrift -->
        </div>

        <button type=\"reset\" class=\"X\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            X
        </button> <!-- Der X button oben Rechts -->

        <div class=\"dialogtext\">
               Sind Sie sicher, dass Sie den ausgew&auml;hlten<br> Studienverlaufsplan l&ouml;schen wollen? <br> <br>
        </div>

 
        <button type=\"reset\" class=\"normalbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            Abbrechen
        </button>
        
        <button type=\"reset\" class=\"greenbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?delete=1&id=$id'\">
               L&ouml;schen
        </button>
         
    </form>
</dialog>";
}
}



if(isset($_GET['id']) && isset($_GET['copy']))
{
    $id = $_GET['id'];

    if($_GET['copy'] == 1){
        copy_svp($id);
        echo '<script>setTimeout(function(){window.location.href="ListenansichtVerwalterU30.php"}, 0)</script>';
    }
    else{
        echo"<dialog open>
    <form method=\"post\" action=\"ListenansichtVerwalterU30.php\"> <!-- action = die Datei zu der gesendet werden soll -->
        <div class=\"container\">
            <div class=\"topbar\">Duplizieren</div> <!-- Der Graue Balken oben mit Überschrift -->
        </div>

        <button type=\"reset\" class=\"X\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            X
        </button> <!-- Der X button oben Rechts -->

        <div class=\"dialogtext\">
               Sind Sie sicher, dass Sie den ausgew&auml;hlten<br> Studienverlaufsplan duplizieren wollen? <br> <br>
        </div>

 
        <button type=\"reset\" class=\"normalbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            Abbrechen
        </button>
        
        <button type=\"reset\" class=\"greenbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php?copy=1&id=$id'\">
               Duplizieren
        </button>
         
    </form>
</dialog>";
    }
}

if(isset($_GET['detid']) && $_GET['alter']==1)
{
    $id =  $_GET['detid'];
    $result = $link->query("select * from studienverlaufsplan where id = '$id'");
    while($row = $result->fetch_assoc())
    {
        $studienbeginn = $row["studienbeginn"];
        $anzahl = $row["anzahl_fachsemester"];
        $name = $row["name"];
        $vpo = $row["veroeffentlichungsjahr_po"];
        $einschr = $row["einschreibung"];
        $prax = $row["praxisprojekt"];
        $credits = $row["credits"];
    }

    if($einschr == SS)
        $ssv = 'checked';
    else
        $wsv = 'checked';

    if($prax == '1')
        $prax = 'checked';


    echo"<dialog open>
    <form method=\"post\" action=\"ListenansichtVerwalterU30.php\"> <!-- action = die Datei zu der gesendet werden soll -->
        <div class=\"container\">
            <div class=\"topbar\">Details</div> <!-- Der Graue Balken oben mit Überschrift -->
        </div>

        <button type=\"reset\" class=\"X\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            X
        </button> <!-- Der X button oben Rechts -->

        <div class=\"dialogtext\">
<table class=\"tablelinks\" width=\"50%\" style=\"float:left\">
                                <tr>
                                    <td>Fachsemester</td>
                                    <td style='background-color: white'> <input type='number' value='$anzahl' name='fachsemester'></td>
                                </tr>
                                <tr>
                                    <td>Studiengang</td><td style='background-color: white'><input type='text' value='$name' name='studiengang'></td>
                                </tr>
                                <tr>
                                    <td>Jahr</td><td style='background-color: white' ><input type='text' value='$vpo' name='jahr'></td>
                                </tr>
                                <tr>
                                    <td>Credits</td><td style='background-color: white'><input type='number' value='$credits' name='credits'></td>
                                </tr>
                                <tr>
                                    <td>Startsemester</td>
                                    <td style='background-color: white'  width=\"50%\">
                                    <label class=\"check_label\">Sommer</label>
                                    <input type=\"radio\" name=\"sommer\" value='1' $ssv>  
                                    <br>                            
                                    <label class=\"check_label\">Winter</label>
                                    <input type=\"radio\" name=\"sommer\" value='0' $wsv> 
                                    </td>
                                </tr>
                                <tr>
                                    <td>Praxisprojekt</td>
                                     <td style='background-color: white'  width=\"50%\">
                                    <label class=\"check_label\">
                                    <input type=\"checkbox\" name=\"praxis\" $prax>Vorhanden</label>
                                </td>
                                </tr>
                            </table>
        </div>
 
        <button type=\"reset\" class=\"normalbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            Abbrechen
        </button>

        <input  hidden class=\"alter\" type=\"text\" name=\"alter\" value=\"$id\">
        <input type=\"submit\" value=\"Speichern\" class=\"greenbutton\" name=\"delete\">
    </form>
</dialog>";
}

if(isset($_POST['alter']))
{
    $id = $_POST['alter'];

    $fachsemester = $_POST['fachsemester'];
    $studiengang = $_POST['studiengang'];
    $jahr = $_POST['jahr'];
    $credits = $_POST['credits'];

    $winter = $_POST['winter'];
    $sommer = $_POST['sommer'];
    $praxis = $_POST['praxis'];



    if($sommer == '1')
        $einschreibung = 'SS';
    else
        $einschreibung = 'WS';


    if($praxis == 'on')
        $praxis = 1;
    else
        $praxis = 0;

    //echo $id.' '.$fachsemester.' '.$studiengang.' '.$jahr.' '.$credits.' '.$einschreibung.' '.$praxis;

    $sql = "UPDATE studienverlaufsplan SET
                             studienbeginn = '2018',
                             anzahl_fachsemester = '$fachsemester',
                             name = '$studiengang',
                             veroeffentlichungsjahr_po='$jahr',
                             credits='$credits',
                             einschreibung='$einschreibung',
                             praxisprojekt='$praxis'
            WHERE id='$id'";
    mysqli_query($link, $sql);

}

if(isset($_GET['details']) && $_GET['id'])
{
    $id =  $_GET['id'];
    $result = $link->query("select * from studienverlaufsplan where id = '$id'");
    while($row = $result->fetch_assoc())
    {
        $studienbeginn = $row["studienbeginn"];
        $anzahl = $row["anzahl_fachsemester"];
        $name = $row["name"];
        $vpo = $row["veroeffentlichungsjahr_po"];
        $einschr = $row["einschreibung"];
        $prax = $row["praxisprojekt"];
        $credits = $row["credits"];
    }

    if($einschr == SS)
        $ssv = 'checked';
    else
        $wsv = 'checked';

    if($prax == '1')
        $prax = 'checked';


    echo"<dialog open>
    <form method=\"post\" action=\"ListenansichtVerwalterU30.php\"> <!-- action = die Datei zu der gesendet werden soll -->
        <div class=\"container\">
            <div class=\"topbar\">Bearbeiten</div> <!-- Der Graue Balken oben mit Überschrift -->
        </div>

        <button type=\"reset\" class=\"X\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            X
        </button> <!-- Der X button oben Rechts -->

        <div class=\"dialogtext\">
 <table class=\"tablelinks\" width=\"50%\" style=\"float:left\">
                                <tr>
                                    <td>Fachsemester</td>
                                    <td style='background-color: white' ><input disabled type='text' value='$anzahl' name='fachsemester'></td>
                                </tr>
                                <tr>
                                    <td>Studiengang</td><td style='background-color: white'  ><input disabled type='text' value='$name' name='studiengang'></td>
                                </tr>
                                <tr>
                                    <td>Jahr</td><td style='background-color: white' ><input disabled type='text' value='$vpo' name='jahr'></td>
                                </tr>
                                <tr>
                                    <td>Credits</td><td style='background-color: white' ><input disabled type='text' value='$credits' name='credits'></td>
                                </tr>
                                <tr>
                                    <td>Startsemester</td>
                                    <td style='background-color: white'  width=\"50%\">
                                    <label class=\"check_label\">Sommer</label>
                                    <input disabled type=\"radio\" name=\"sommer\" value='1' $ssv>  
                                    <br>                            
                                    <label class=\"check_label\">Winter</label>
                                    <input disabled type=\"radio\" name=\"sommer\" value='0' $wsv> 
                                    </td>
                                </tr>
                                <tr>
                                    <td>Praxisprojekt</td>
                                     <td style='background-color: white'  width=\"50%\">
                                    <label class=\"check_label\">
                                    <input disabled type=\"checkbox\" name=\"praxis\" $prax>Vorhanden</label>
                                </td>
                                </tr>
                            </table>
        </div>

 
        <button type=\"reset\" class=\"normalbutton\" onclick=\"location.href='ListenansichtVerwalterU30.php'\">
            Abbrechen
        </button>

        <input  hidden class=\"alter\" type=\"text\" name=\"alter\" value=\"$id\">
       
    </form>
</dialog>";
}
?>

<script type='text/javascript' src='js/ListenansichtVerwalterU30.js'></script>
<link rel="stylesheet" href="css/ListenansichtVerwalterU30.css">
<link rel="stylesheet" href="css/dialog-style.css">



<h1>Studienverlaufspläne</h1>
<div class="erstellen" onclick="svp_erstellen()">
    <div class="circle">
        <div class="plus-sign">+</div>
    </div>
    Studienverlaufsplan Erstellen
</div>


<div class="veröffenlicht-box">
    <div class="veröffentlicht-überschrift">veröffentlichte Studienverlaufspläne</div>

    <?php
    $result = $link->query("select id, name, veroeffentlichungsjahr_po, public from studienverlaufsplan");
    while($row = $result->fetch_assoc())
    {
        if($row["public"] == 1)
        {
            $name = $row["name"].$row["veroeffentlichungsjahr_po"];
            echo create_vitem($name, $row["id"]);
        }
    }

    ?>


</div>
<div class="unveröffenlicht-box">
    <div class="unveröffentlicht-überschrift">unveröffentlichte Studienverlaufspläne</div>
    <?php
    $result = $link->query("select id, name, veroeffentlichungsjahr_po, public from studienverlaufsplan");
    while($row = $result->fetch_assoc())
    {
        if($row["public"] == 0)
        {
            $name = $row["name"].$row["veroeffentlichungsjahr_po"];
            echo create_uvitem($name, $row["id"]);
        }
    }
    ?>

</div>

<!-- sandwitch menu -->
<nav role="navigation">
    <div id="menuToggle">
        <input type="checkbox" />
        <span></span>
        <span></span>
        <span></span>
        <ul id="menu">
            <a>
            <?php
            echo $_SESSION['email']
            ?>
            </a>
            <a href="index.php"><li>Abmelden</li></a>
        </ul>
    </div>
</nav>

