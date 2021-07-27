<?php

include_once( $_SERVER['DOCUMENT_ROOT'] . "/config.inc.php" );
include_once(DIR_INC . "class.mysql.inc.php");
$bd = new class_mysql();
$bd->insertar($_GET['temp'] , $_GET['volt'], $_GET['hum']);
$result=$bd->listar();
?>

<!DOCTYPE html>
<html lang="en">
<head>
<title>ESP8266 GET</title>
		<meta charset="utf-8">
		<!-- Script for updating pages without refreshing the page -->
		<script src="jquery.min.js"></script>
		<script>
			$(document).ready(function() {
				setInterval(function(){get_data()},5000);
				function get_data()
				{
					jQuery.ajax({
						type:"GET",
						url: "read.php",
						data:"",
						beforeSend: function() {
						},
						complete: function() {
						},
						success:function(data) {
							$("table").html(data);
						}
					});
				}
			});
		</script>
		<style>
			table {
				border-collapse: collapse;
				width: 100%;
				color: #1f5380;
				font-family: monospace;
				font-size: 20px;
				text-align: left;
			} 
			th {
				background-color: #1f5380;
				color: white;
			}
			tr:nth-child(even) {background-color: #f2f2f2}
		</style>
</head>
<body>
    <div> <h1>Valores</h1></div>
    <table border="">
        <tr>
            <td>id</td>
            <td>Sensor1</td>
            <td>Sensor2</td>
            <td>Sensor3</td>
			<td>Fecha</td>
            <td>Tiempo</td>
        </tr>
        <?php
        
            while($mostrar=mysqli_fetch_array($result)){

        ?>
        <tr>
            <td><?php echo $mostrar['id'] ?></td>
            <td><?php echo $mostrar['temperatura'] ?></td>
            <td><?php echo $mostrar['humedad'] ?></td>
            <td><?php echo $mostrar['voltaje'] ?></td>
        </tr>
        <?php
        
            }?>
    </table>
</body>
</html>