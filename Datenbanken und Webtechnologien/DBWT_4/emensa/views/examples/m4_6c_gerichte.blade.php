<!DOCTYPE html>
<html lang="de">
<head>
    <title>m4_6c_gerichte</title>
</head>
<body>
@forelse ($meals as $meal)
@if($meal['preis_intern'] >= 2)
    {{ $meal['name'] }}
    {{ number_format($meal['preis_intern'], 2) }} &euro;
<br>
@endif
@empty
    <p>Es sind keine Gerichte vorhanden</p>
    <br>
@endforelse
</body>
</html>