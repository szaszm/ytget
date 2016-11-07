<?php
require_once('../config.php');
chdir(MUSIC_DIRECTORY);
$id = $_REQUEST['id'];
$url = "http://youtube.com/watch?v=$id";
$ytgetsh = YTGET;
$dlout = trim(`$ytgetsh "$id" 2>&1`);
?>
<html>
<head>
	<title>GET</title>
	<meta http-equiv="Refresh" content="0; url=/">
	<style></style>
</head>
<body>
	<pre>
<?php
echo $dlout."\n";
?>
	</pre>
</body>
</html>
