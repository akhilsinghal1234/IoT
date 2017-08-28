<?php
include 'connect.php';
$query = mysqli_query($con,"SELECT id,temp  FROM tl_arduino_testing");

while( $row = mysqli_fetch_array($query))
{	
    $data[] = $row;
}
echo json_encode($data);

?>