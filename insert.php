<!-- This file displays all the data present in the database(present on an online web hosting service) in a tabular form and a button to display graph(by default Bar Graph) -->

<html>
<style>
		form
			{
				text-align : center;
				border: 1px solid black;
			}
</style>
<body>
<?php
include 'connect.php';
$d = date("d-m-Y");
$t = date("h:i:sa");
$timestamp = $d ." ". $t;
//echo $timestamp;
mysqli_query($con,"INSERT INTO tl_arduino_testing VALUES('0','$timestamp','".$_GET["temp"]."','".$_GET["humidity"]."','192.168.43.94','Yes')");
$query = mysqli_query($con,"SELECT * FROM tl_arduino_testing");
while($row = mysqli_fetch_array($query))
{
	echo 'id = '." ".$row['id']." ";
	echo 'timestamp = '." ".$row['timestamp']." ";
	echo 'temperature = '." ".$row['temp']." ";
	echo 'humidity = '." ".$row['humidity']." ";
	echo '</br>';
}?>
<form action = "graph.html">
<button type = "submit" value = "Submit">SEE GRAPH</button>
</form>
</body>
</html>