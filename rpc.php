<?php
require_once("db.php.inc");

$request = $_POST['request'];
$response = "FUCK<p>";

switch($request)
{
	case "login":
		$username = $_POST['username'];
		$password = $_POST['password'];
		$login = new login_db("connect.ini");
		$response = $login->validate_client($username, $password);
		if ($response['success'])
		{
			$response = "Login Successful!<p>";
		}
		else		
		{
			$response = "Login Failed...<p>";
		}
		break;
}
?>
