<!DOCTYPE html>
<html>
<head>
	<title>ytget</title>
</head>
<body>
	<section class="main">
		<form method="get" action="/search.php">
			<div>
				<label for="search-input">Search on youtube:</label>
				<input type="text" id="search-input" name="searchInput" placeholder="e.g.: deadmau5 strobe"/>
			</div>
			<div style="margin-top: 20px;"><input type="submit" value="Search" /></div>
		</form>
	</section>
	<script type="text/javascript">
		document.getElementsByTagName('form')[0].onsubmit = function(e) {
			var message = document.createElement('span');
			message.innerHTML = 'Searching...';
			message.style.fontSize = '20px';
			message.style.color = 'red';
			message.style.marginTop = '10px';
			this.appendChild(message);
		};
	</script>
</body>
</html>
