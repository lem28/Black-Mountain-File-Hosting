<?php
require_once("user.php.inc");
require_once("file.php.inc");

$request = $_POST['request'];
$response = "didn't work :^)";

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
		$file_up = $_POST['fileup'];
		$expire = $POST['expire'];
		$file = new file("connect.ini");
		$response = $file->file_upload($param);
		if ($response['success'])
		{
			$response = "File Upload Successful!<p>";
		}
		else
		{
			$response = "File Upload Failed...<p>";
		}
		break;
	case "search":
		$param = $_POST['param'];
		$db = new file("connect.ini");
		$db->file_search($param);
		break;
	case "browse":
		$db = new file("connect.ini");
		$db->file_browse();
		break;		
}
echo $response;
?>
