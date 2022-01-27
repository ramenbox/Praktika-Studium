<?php
/**
 * Praktikum DBWT. Autoren:
 * Harun, Karacuban, 3158169
 * Thavarupan, Mahendralingham, 3130383
 */

include('m2_5a_standardparameter.php');

 if(isset($_GET['add'])){
    $res = addieren($_GET['A'],$_GET['B']);
}
 else if(isset($_GET['mult'])){
    $res = multiplizieren($_GET['A'],$_GET['B']);
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
    <title>addform</title>
</head>
<body>
<form method="get">
    <input  type="text" name="A">
    <input  type="text" name="B">
    <button type="submit" name="mult">Multiplikation</button>
    <button type="submit" name="add">Addition</button>
</form>
<?php echo "$res";?>

</body>
</html>