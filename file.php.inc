<?php
require_once("includes/file_db.php.inc");

class file
{
	public function file_upload($targetfile)
	{
		$uploadpath = 'uploads/';
		$target_file = $target_dir.basename($_FILES["file_to_upload"]["name"]);
		$check = 1;
		$image_file_type = pathinfo($target_file,PATHINFO_EXTENSION);
		if (file_exists($target_file))
		{
			echo "Sorry, file already exists.";
			$check = 0;
		}
		if ($_FILES["file_to_upload"]["size"] > 500000)
		{
			echo "Sorry, your file is too large.";
			$check = 0;
		}
		if ($check == 0)
		{
			echo "Sorry, your file was not uploaded.";
		}
		else
		{
			if (move_uploaded_file($_FILES["file_to_upload"]["tmp_name"], $target_file))
			{
		    	echo "The file ".basename( $_FILES["file_to_upload"]["name"])." has been uploaded.";
				
			}
			else
			{
		    	echo "Sorry, there was an error uploading your file.";
			}
    	}
	}	
	public function file_search()
	{
		$term = mysql_real_escape_string($_REQUEST['term']);
		$sql = "SELECT FROM LOWER(files) WHERE LOWER(file_name) LIKE LOWER('%".$term."%')";
		$r_query = mysql_query($sql);
		while ($row = mysql_fetch_array($r_query))
		{
			echo '<br>Filename: ' .$row['file_name'];
		} 
	}
}
?>
