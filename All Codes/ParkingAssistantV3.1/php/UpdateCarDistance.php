<?PHP
	try {
		$Token	  = $_GET["Token"];
		$Distance = $_GET["DISTANCE"];

		if ($Distance <= 100) { // This is to avoid the system from logging longg distances 
			include "ConnectionStringArduino.php"; // Create connection
			$sql 	  = "INSERT INTO `Garage` (`DateTime`,`Distance`) VALUES ('".time()."','".$Distance."');";
			$result   = $con->query( $sql ); if($result === FALSE) { die(mysqli_error()); };
			mysqli_close($con);
			echo "Added";
		};
	} catch (Exception $e) {
		echo "Error" . $e;
		$log_file = "sensor_log.txt";
    	file_put_contents($e . "\n", FILE_APPEND);
	};
?>