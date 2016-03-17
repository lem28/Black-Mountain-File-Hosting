<?php
require_once("file_db.php.inc");

$command = $argv[1];

switch($command)
{
	case 'upload':
		$filename = $argv[2];
		$expiration = $argv[3];
		$db = new file_db("../ini/connect.ini");
		$db->add_new_file($login_name,$expiration);
		break;
	default:
		echo "usage:\n".$argv[0]."upload <file name> <expiration date>".PHP_EOL;
}
?>
