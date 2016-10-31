<!DOCTYPE html>
<html>
<head>
	<title>dafuq</title>
</head>
<body>
	<div style="margin-bottom: 40px;">
		<h2>Nem találod a listában?</h2>
		<p>Töltsd le youtube-ról, és azonnal felkerül a listára</p>
	</div>
	<section class="main">
		<form method="get" action="/search.php">
			<div>
				<label for="search-input">Keresés a Youtubeon:</label>
				<input type="text" id="search-input" name="searchInput" placeholder="például: deadmau5 strobe"/>
			</div>
			<div style="margin-top: 20px;"><input type="submit" value="Keres" /></div>
		</form>
	</section>
	<script type="text/javascript">
		document.getElementsByTagName('form')[0].onsubmit = function(e) {
			var message = document.createElement('span');
			message.innerHTML = 'Nyugi, már keres...';
			message.style.fontSize = '20px';
			message.style.color = 'red';
			message.style.marginTop = '10px';
			this.appendChild(message);
		};
	</script>
</body>
</html>
