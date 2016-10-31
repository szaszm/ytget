<?php
chdir('/home/szaszm/zene/youtube');
$id = $_REQUEST['id'];
$url = "http://youtube.com/watch?v=$id";
$dlout = trim(`/home/szaszm/bin/ytget.sh "$id" 2>&1`);
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
