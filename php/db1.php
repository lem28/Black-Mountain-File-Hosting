<?php
require_once("db.php.inc");

$command = $argv[1];

switch($command)
{
	case 'register':
		$login_name = $argv[2];
		$password = $argv[3];
		$first_name = $argv[4];
		$last_name = $argv[5];
		$email = $argv[6];
		$db = new user_db("connect.ini";
		$db->add_new_user($login_name,$password,$first_name,$last_name,$email);
		break;
	case 'login':
		$login_name = $argv[2];
		$password = $argv[3];
		$db = new user_db("connect.ini");
		if ($db->validate_user($login_name, $password) == 0)
		{
			echo "Invalid login".PHP_EOL;
		}
		else
		{
			echo "Logged in".PHP_EOL;
		}
		break;
	default:
		echo "usage:\n".$argv[0]."[register <login name> <password> <first name> <last name> <email> | login <login name> <password>".PHP_EOL;
}
?>
