<?php
require_once("includes/user.php.inc");
require_once("includes/file.php.inc");

$request = $_POST['request'];
$response = "FUCK<p>";

switch($request)
{
	case "login":
		$username = $_POST['username'];
		$password = $_POST['password'];
		$login = new user_db("../ini/connect.ini");
		$response = $login->validate_user($username, $password);
		if ($response['success'])
		{
			$response = "Login Successful!<p>";
		}
		else		
		{
			$response = "Login Failed...<p>";
		}
		break;
	case "register":
		$username = $_POST['username'];
		$password = $_POST['password'];
		$first_name = $_POST['first_name'];
		$last_name = $_POST['last_name'];
		$email = $_POST['user_email'];
		$login = new user_db("../ini/connect.ini");
		$response = $login->validate_user($username, $password);
		if ($response['success'])
		{
			$response = "Registration Failed:".$response['message']."<p>";			
		}
		else		
		{
			$login->add_new_user($username,$password,$first_name,$last_name,$email);
			$response = "$username Registered Successfully!<p>";
		}
		break;	
	case "search":
		$db = new file_db("../ini/connect.ini");
		$db->search($param);
		break;
	case "browse":
		$db = new file_db("../ini/connect.ini");
		$db->browse();
		break;		
}
echo $response;
?>
