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
			$response = "<p>Login Successful!";
		}
		else		
		{
			$response = "<p>Login Failed...";
		}
		break;
	case "upload":
		$file = new file("connect.ini");
		$response = $file->file_upload();
		if ($response['success'])
		{
			$response = "<p>File Upload Successful!";
		}
		else
		{
			$response = "<p>File Upload Failed...";
		}
		break;
	case "search":
		$param = $_POST['param'];
		$file = new file("connect.ini");
		$response = $file->file_search($param);
		if ($response['success'])
		{
			$response = "<p>File found!";
		}
		else
		{
			$response = "<p>File not found...";
		}
		break;
	case "browse":
		$file = new file("connect.ini");
		$repsonse = $file->file_browse();
		break;		
}
echo $response;
?>
