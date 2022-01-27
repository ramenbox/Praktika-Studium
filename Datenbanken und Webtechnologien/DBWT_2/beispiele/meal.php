<?php
/**
 * Praktikum DBWT. Autoren:
 * Harun, Karacuban, 3158169
 * Thavarupan, Mahendralingham, 3130383
 */

const GET_PARAM_MIN_STARS = 'search_min_stars';
const GET_PARAM_SEARCH_TEXT = 'search_text';
const GET_PARAM_SET_LANG = 'lang';

$language = [
    'rating' => ['de' => 'Bewertungen', 'en' => 'Stars'],
    'allergens' => ['de' => 'Allergien', 'en' => 'Allergies'],
    'meal' => ['de' => 'Mahlzeit', 'en' => 'Meal'],
    'price' => ['de' => 'Preis', 'en' => 'Price'],
    'internal' => ['de' => 'intern', 'en' => 'internal'],
    'external' => ['de' => 'extern', 'en' => 'external'],
    'search' => ['de' => 'Suchen', 'en' => 'Search'],
    'submit' => ['de' => 'Bestätigen', 'en' => 'Submit'],
    'reviews' => ['de' => 'Rezensionen', 'en' => 'Reviews'],
    'av' => ['de' => 'Durchschnitt', 'en' => 'Average'],
];

/**
 * Liste aller möglichen Allergene.
 */
$allergens = array(
    11 => 'Gluten',
    12 => 'Krebstiere',
    13 => 'Eier',
    14 => 'Fisch',
    17 => 'Milch'
);

$on_off = array(
    'on' => 'off' ,
    'off' => 'on' ,
);

$display = 'on';

$meal = [ // Kurzschreibweise für ein Array (entspricht = array())
    'name' => 'Süßkartoffeltaschen mit Frischkäse und Kräutern gefüllt',
    'description' => 'Die Süßkartoffeln werden vorsichtig aufgeschnitten und der Frischkäse eingefüllt.',
    'price_intern' => 2.90,
    'price_extern' => 3.90,
    'allergens' => [11, 13],
    'amount' => 42   // Anzahl der verfügbaren Gerichte.
];

$ratings = [
    [   'text' => 'Die Kartoffel ist einfach klasse. Nur die Fischstäbchen schmecken nach Käse. ',
        'author' => 'Ute U.',
        'stars' => 2 ],
    [   'text' => 'Sehr gut. Immer wieder gerne',
        'author' => 'Gustav G.',
        'stars' => 4 ],
    [   'text' => 'Der Klassiker für den Wochenstart. Frisch wie immer',
        'author' => 'Renate R.',
        'stars' => 4 ],
    [   'text' => 'Kartoffel ist gut. Das Grüne ist mir suspekt.',
        'author' => 'Marta M.',
        'stars' => 3 ]
];


$showRatings = [];
if (!empty($_GET[GET_PARAM_SEARCH_TEXT])) {
    $searchTerm = $_GET[GET_PARAM_SEARCH_TEXT];
    foreach ($ratings as $rating) {
        if (stripos($rating['text'], $searchTerm) !== false) {
            $showRatings[] = $rating;
        }
    }
} elseif (!empty($_GET[GET_PARAM_MIN_STARS])) {
    $minStars = $_GET[GET_PARAM_MIN_STARS];
    foreach ($ratings as $rating) {
        if ($rating['stars'] >= $minStars) {
            $showRatings[] = $rating;
        }
    }
} else {
    $showRatings = $ratings;
}

function calcMeanStars($ratings) : float { // : float gibt an, dass der Rückgabewert vom Typ "float" ist
    $sum = 0;
    $i = 0;
    foreach ($ratings as $rating) {
        $sum += $rating['stars'];
        $i++;
    }
    return $sum / count($ratings);
}


if (! empty ($_GET['display'])) {
    if(in_array ($_GET['display'] , $on_off)) {
        $display = $_GET['display'];
    }
}
$switch = '?display=' . $on_off[$display];

$lang = 'de';
$langInput = $_GET[GET_PARAM_SET_LANG] ?? NULL;
if (isset($langInput)) {
    if ($langInput == 'de') {
        $lang = 'de';
    } else if ($langInput == 'en') {
        $lang = 'en';
    }
}
?>
<!DOCTYPE html>
<html lang="de">
<head>
    <style>
        .off {display:none;}
        .on {display:block;}
    </style>

    <meta charset="UTF-8"/>
    <title>Gericht: <?php echo $meal['name']; ?></title>
    <style type="text/css">
        * {
            font-family: Arial, serif;
        }
        .rating {
            color: darkgray;
        }
    </style>
</head>
<body>


<h1><?php echo $language['meal'][$lang] . ': ' . $meal['name']; ?></h1>
<form method="get">
    <br/><br/>
    <select name="lang">
        <option value="en"
            <?php
            if ('en' == $lang) {
                echo 'selected="selected"';
            }
            ?>>English</option>
        <option value="de"
            <?php
            if ('de' == $lang) {
                echo 'selected="selected"';
            }
            ?>>Deutsch</option>
    </select>
    <input type="submit"/>
</form>
<br/>

<a href="<?php echo $switch; ?>">Beschreibung</a>
<div class="<?php echo $display; ?>">
    <?php echo $meal['description'];?>
</div>

<p>
<?php
echo "<ul>
<li>{$allergens[11]}</li>
<li>{$allergens[13]}</li>
</ul>";
?>
</p>

<br>
<?php echo number_format($meal['price_intern'], 2, ',', ' '). '€';?>
<br>
<?php echo number_format($meal['price_extern'], 2, ',', ' '). '€';?>

<h1><?php echo $language['reviews'][$lang] . ' (' . $language['av'][$lang] . ': '. calcMeanStars($ratings); ?>)</h1>

<form method="get">
    <label for="search_text">Filter:</label>
    <input id="search_text" type="text" name="search_text" value=<?php echo $searchTerm;?> >
    <input type="submit" value="submit">
</form>
<table class="rating">
    <thead>
    <tr>
        <td>Text</td>
        <td>Sterne</td>
        <td>Autor</td>
    </tr>
    </thead>
    <tbody>
    <?php
    foreach ($showRatings as $rating) {
        echo "<tr><td class='rating_text'>{$rating['text']}</td>
                      <td class='rating_stars'>{$rating['stars']}</td>
                      <td class='rating_author'>{$rating['author']}</td>
                  </tr>";
    }
    ?>
    </tbody>
</table>
</body>
</html>