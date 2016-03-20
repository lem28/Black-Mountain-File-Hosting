<?php
require_once("user.php.inc");
require_once("file.php.inc");

$request = $_POST['request'];
$response = "FUCK<p>";

switch($request)
{
	case "register":
		$username = $_POST['username'];
		$password = $_POST['password'];
		$first_name = $_POST['first_name'];
		$last_name = $_POST['last_name'];
		$email = $_POST['user_email'];
		$login = new user("connect.ini");
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
	case "login":
		$username = $_POST['username'];
		$password = $_POST['password'];
		$login = new user("connect.ini");
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
	case "upload":
		$file = $_POST['fileup'];
		$expire = $POST['expire'];
		$db = new file("connect.ini");
		$db->upload($param);
		break;
	case "search":
		$db = new file("connect.ini");
		$db->search($param);
		break;
	case "browse":
		$db = new file("connect.ini");
		$db->browse();
		break;		
}
echo $response;
?>
