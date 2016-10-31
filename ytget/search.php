<?php

function multiexplode ($delimiters,$string) {
	$ready = str_replace($delimiters, $delimiters[0], $string);
	$launch = explode($delimiters[0], $ready);
	$launch = array_filter($launch, function($item) { return $item != ""; });
	return  $launch;
}

$searchValue = '';
if(isset($_REQUEST['searchInput'])) {
	$searchValue = $_REQUEST['searchInput'];
	$svLen = strlen($searchValue);
	$svWords = multiexplode([" ", "_", ",", "-"], $searchValue);

	$playlist = explode("\n", `mpc playlist`);
	$matches = [];
	$minSimilarity = 0.5;
	foreach($playlist as $item) {
		$itemLen = strlen($item);
		$itemWords = multiexplode([" ", "_", ",", "-"], $item);
		$avgLen = ($svLen + $itemLen) / 2.0;
		$similarity = 0;
		for($i = 0; $i < count($svWords); ++$i) {
			for($j = 0; $j < count($itemWords); ++$j) {
				$word1 = strtolower($svWords[$i]);
				$word2 = strtolower($itemWords[$j]);
				#$curSim = -1 * levenshtein($word1, $word2) * floatval(strlen($word1) + strlen($word2));;
				if($word1 == $word2) {
					$curSim = strlen($word1);
				} else {
					$res = similar_text($word1, $word2);
					$curSim = ($res > 3 ? $res / 3 : 0);
				}
				$similarity += floatval($curSim);
			}
		}
		if(abs($similarity) >= $minSimilarity)
			$matches[] = ['similarity' => $similarity, 'item' => $item ];
	}
	usort($matches, function($a, $b) { return floatval($b['similarity']) - floatval($a['similarity']); });
	$matches = array_slice($matches, 0, 10);

	$results = `/home/szaszm/sources/youtube/youtube_search "$searchValue"`;
	$resultsStr = $results;
	$results = explode("\n", $results);
	$results = array_filter($results, function($line) { return !empty($line != ""); });
	$results = array_map(function($line) {
		$splitline = explode(' ', $line);
		$id = array_shift($splitline);
		$title = implode(' ', $splitline);
		return ['id' => $id, 'title' => $title];
	}, $results);
}
?><html>
<head>
	<title><?php echo $searchValue; ?> - Keresés</title>
	<style>
	</style>
</head>
<body>
	<a href="/">&lt;&lt; Vissza</a>
	<div>
		<h2>Lista találatok</h2>
		<p>Ha itt látod, amit keresel, akkor ne töltsd le, hanem keresd ki a listából!</p>
		<ul>
			<?php foreach($matches as $match): ?>
			<li><?php echo '<b>'.number_format($match['similarity'], 2).'</b> - '.$match['item']; ?></li>
			<?php endforeach; ?>
		</ul>
	</div>
	<div>
		<h2>Youtube találatok:</h2>
		<?php if(is_array($results) && count($results) > 0): ?>
		<ul>
			<?php foreach($results as $result): if(!empty($result['id'])): ?>
			<li><a href="/get.php?id=<?php echo $result['id']?>"><?php echo $result['title'];?></a></li>
			<?php endif; endforeach; ?>
		</ul>
		<?php else: ?>
		<p>Gyengélkedik a kapcsolat, próbáld újra!</p>
		<?php endif; ?>
	</div>
	<script type="text/javascript">
		document.querySelectorAll('a').forEach(function(a) { a.onclick = function(e) { document.write('Letöltés...'); }; });
	</script>
</body>
</html>
