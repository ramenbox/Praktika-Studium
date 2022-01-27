<!DOCTYPE html>
<html lang="de">
<head>
    <title>@yield('title')</title> <!-- E-Mensa -->
    <!-- Layout -->

    @section('header')
    @show
</head>
<body>

    @section('nav')
    @show

    <div class="divider">
    @section('text')
    @show

    @section('gerichte')
    @show

    </div>

<footer>
    @section('footer')
    @show
</footer>

</body>
</html>