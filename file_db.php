#!usr/bin/php
<?php
require_once("includes/file.php.inc");

$command = $argv[1];

switch($command)
{
	case 'upload':
		$db = new file_db("../ini/connect.ini");
		$db->upload($file,$expiration);
		break;
	case 'search':
		$db = new file_db("../ini/connect.ini");
		$db->search($param);
		break;
	case 'browse':
		$db = new file_db("../ini/connect.ini");
		$db->browse();
		break;
	case 'login':
		$db = new file_db("../ini/connect.ini");
		$db->file($file,$expiration);
		break;
	default:
		echo "usage:\n".$argv[0]."upload <file> <expiration> | search <param> | browse".PHP_EOL;
}
?>
