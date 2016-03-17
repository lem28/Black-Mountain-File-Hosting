<?php
require_once("file_db.php");

$uploadpath = 'upload/';
$max_size = 100;
$alwidth = 100000;
$alheight = 100000;
$allowtype = array('bmp', 'gif', 'jpg', 'jpeg', 'png');

if(isset($_FILES['fileup']) && strlen($_FILES['fileup']['name']) > 1) {
	$uploadpath = $uploadpath . basename( $_FILES['fileup']['name']);
	$sepext = explode('.', strtolower($_FILES['fileup']['name']));
	$type = end($sepext);
	list($width, $height) = getimagesize($_FILES['fileup']['tmp_name']);
	$err = '';

	if(!in_array($type, $allowtype))
		$err .= 'The file: <b>'. $_FILES['fileup']['name']. '</b> not has the allowed extension type.';
	if($_FILES['fileup']['size'] > $max_size*1000000)
		$err .= '<br/>Maximum file size must be: '. $max_size. ' MB.';
	if(isset($width) && isset($height) && ($width >= $alwidth || $height >= $alheight))
		$err .= '<br/>The maximum Width x Height must be: '. $alwidth. ' x '. $alheight;

	if($err == '') {
		if(move_uploaded_file($_FILES['fileup']['tmp_name'], $uploadpath)) { 
			echo 'File: <b>'. basename( $_FILES['fileup']['name']). '</b> successfully uploaded:';
			echo '<br/>File type: <b>'. $_FILES['fileup']['type'] .'</b>';
			echo '<br />Size: <b>'. number_format($_FILES['fileup']['size']/1024, 3, '.', '') .'</b> KB';
			if(isset($width) && isset($height)) echo '<br/>Image Width x Height: '. $width. ' x '. $height;
			echo '<br/><br/>Image address: <b>http://'.$_SERVER['HTTP_HOST'].rtrim(dirname($_SERVER['REQUEST_URI']), '\\/').'/'.$uploadpath.'</b>';
		}
		else echo '<b>Unable to upload the file.</b>';
	}
	else echo $err;
}
?>
