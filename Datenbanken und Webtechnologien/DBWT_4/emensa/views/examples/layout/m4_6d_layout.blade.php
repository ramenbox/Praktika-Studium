<!DOCTYPE html>
<html lang="de">
<head>
    <title>@yield('title')</title>
</head>
<body>
<head>
    @section('header')
    @show
</head>
@section('main')
@show
<footer>
    @section('foot')
    @show
</footer>
</body>
</html>