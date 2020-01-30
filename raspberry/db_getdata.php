<?php
	$servername	= 'localhost';
	$username 	= 'root';
	$password 	= 'peri2019';
	$database 	= 'enclos';
	
	// Query infos - user choice
	$table		= $_GET['param'];
	
	// Create connection
	$bdd = new mysqli($servername, $username, $password, $database);

	// Check connection
	if ($bdd->connect_errno) {
			//echo "Connection failed: ". $bdd->connect_error(). "\n";
			exit;
	}
	
	// Retreive the last recent value from DB
	$sql = 'SELECT * from '. $table .' ORDER BY id DESC LIMIT 1';
	$result = $bdd->query($sql);
	
	if(!$result) {
		//echo "Could not get data: ". $bdd->error(). "\n";
		exit;
	}
	if($result->num_rows > 0){
		$row = $result->fetch_assoc();
		$value = $row[$table];
	}else{
		$value = "0";
	}
	
	// Close DB
	$result->free();
	$bdd->close();
	
	// Output resulat
	echo $value;
?>
