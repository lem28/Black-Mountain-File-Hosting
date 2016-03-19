#!usr/bin/php
<?php
require_once("includes/file.php.inc");

$command = $argv[1];

switch($command)
{
	case 'upload':
		$db = new user_db("../ini/connect.ini");
		$db->add_new_user($login_name,$password,$first_name,$last_name,$email);
		break;
	case 'login':
		$db = new user_db("../ini/connect.ini");
	case 'login':
		$db = new user_db("../ini/connect.ini");
	case 'login':
		$db = new user_db("../ini/connect.ini");
	default:
		echo "usage:\n".$argv[0]."register <login name> <password> <first name> <last name> <email> | login <login name> <password>".PHP_EOL;
}
?>
