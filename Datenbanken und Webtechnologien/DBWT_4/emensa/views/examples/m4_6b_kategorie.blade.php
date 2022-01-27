<!DOCTYPE html>
<html lang="de">
<head>
    <title>m4_6b_kategorie</title>
</head>
<body>
@foreach ($kategorien as $kategorie)
    @if($loop->odd)
        <strong>{{ $kategorie['name'] }}</strong>
    @else
        {{ $kategorie['name'] }}
    @endif
    <br>
@endforeach
</body>
</html>