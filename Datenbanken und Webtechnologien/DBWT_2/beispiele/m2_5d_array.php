<?php
/**
 * Praktikum DBWT. Autoren:
 * Harun, Karacuban, 3158169
 * Thavarupan, Mahendralingham, 3130383
 */

$famousMeals = [
    1 => ['name' => 'Currywurst mit Pommes',
        'winner' => [2001, 2003, 2007, 2010, 2020]],
    2 => ['name' => 'Hähnchencrossies mit Paprikareis',
        'winner' => [2002, 2004, 2008]],
    3 => ['name' => 'Spaghetti Bolognese',
        'winner' => [2011, 2012, 2017]],
    4 => ['name' => 'Jägerschnitzel mit Pommes',
        'winner' => 2019]
];

function keinGewinnerjahr($famousMeals) {
    $year = new SplFixedArray(21);

    foreach ($famousMeals as $meal => $item) {
        if (is_array($famousMeals[$meal]['winner'])){ //Für den letzten Eintrag 2019 von Jägerschnitzel, ist das notwendig da dies kein Array ist
            for ($j =0; $j < count($famousMeals[$meal]['winner']); $j++) {
                $yearStr = (string)($famousMeals[$meal]['winner'][$j]);
                $year[(int)($yearStr[2].$yearStr[3])] = true;
            }
        }
        else {//Einfallbehandlung für den Eintrag Jägerschnitzel
            $yearstr = (string)($famousMeals[$meal]['winner']);
            $year[(int)($yearStr[2].$yearStr[3])] = true;
        }
    }
    echo "In den folgenden Jahren gab es keine Gewinner: ";
    foreach ($year as $nowinyear => $boo) {
        if ($nowinyear < 10 && $year[$nowinyear] != true) {
            echo "200".$nowinyear." ";
        }
        else if ($nowinyear > 9 && $year[$nowinyear] != true) {
            echo "20".$nowinyear." ";
        }
    }
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
    <title>5d array</title>
    <style>
        li {
            margin: 1%;
        }
    </style>
</head>
<body>
<ol>
    <?php
    foreach ($famousMeals as $meal => $item) {
        echo "<li>";
        echo $famousMeals[$meal]['name']."<br>";

        if (is_array($famousMeals[$meal]['winner'])){ //Für den letzten Eintrag 2019 von Jägerschnitzel, ist das notwendig da dies kein Array ist
            for ($i =count($famousMeals[$meal]['winner']); $i >= 0; $i--) { //Für die Ordnung aus der Aufgabenstellung muss das Array Rückwärts durchlaufen werden
                echo $famousMeals[$meal]['winner'][$i]." ";
            }
        }
        else {
            echo $famousMeals[$meal]['winner'];
        }
        echo "</li>";
    }
    ?>
</ol>
<?php keinGewinnerjahr($famousMeals); ?>
</body>
</html>