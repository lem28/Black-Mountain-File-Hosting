<?php
require_once("logger.php.inc");

class file
{
	private $db;
	private $logger;
	public function __construct($ini_file)
	{
	$ini = parse_ini_file($ini_file,true);
	$logger = new error_logger("var/www/log/files.log");
	$this->db = new mysqli(
		$ini["db"]["host"],
		$ini["db"]["user"],
		$ini["db"]["password"],
		$ini["db"]["db"]
	);
	if ($this->db->connect_errno > 0)
	{
		$this->logger->log(__file__.__line__."Failed to connect to database".$this->db->connect_error);
		exit(0);
	}
	echo "Connected to db".PHP_EOL;
	}
	public function __destruct()
	{
		$this->db->close();
		echo "Closed connection to db".PHP_EOL;
	}
	public function get_file($filename)
	{
		$get_query = "select file_name from files where file_name='$filename';";
		$get_results = $this->db->query($get_query);
		if(!$get_results)
		{
			$this->logger->log("error with results: ".$this->db->error);
			return 0;
		}
		$user = $get_results->fetch_assoc();
		if (isset($filename["file_name"]))
		{	
			return $filename["file_name"];
		}
		return 0;
	}
	public function add_new_file($filename,$expiration)
	{
		if ($this->get_file_name($filename) != 0)
		{
			$this->logger->log("file $filename already exists!!!!!");
			$response = array(
			"message"=>"file $filename already exists!",
			"success"=>false
			);
			return $response;
		}
		$upload_path = 'uploads/';
		$target_file = $target_dir.basename($_FILES["$filename"]["name"]);
		$check = 1;
		$image_file_type = pathinfo($target_file,PATHINFO_EXTENSION);
		if (file_exists($target_file))
		{
			echo "Sorry, file already exists.";
			$check = 0;
		}
		if ($_FILES["$filename"]["size"] > 500000)
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
			if (move_uploaded_file($_FILES["$filename"]["tmp_name"], $target_file))
			{
		    	echo "The file ".basename( $_FILES["$filename"]["name"])." has been uploaded.";
				
			}
			else
			{
		    	echo "Sorry, there was an error uploading your file.";
			}
    	}
	    $now = date("Y-m-d h:i:s",time());
		$filename = $this->db->real_escape_string($filename);
		$add_query = "
			INSERT INTO files
			(
				file_name,
				file_url,
				upload_date,
				expiration_date
			)
			VALUES
			(
				'$filename',
				'$url',
				'$now',
				'$expiration'
			);";
		$add_results = $this->db->query($add_query);
		if(!$add_results)
		{
			$this->logger->log("error with results: ".$this->db->error);
		}
		else
		{
			echo "Added $filename".PHP_EOL;
		}
		return 0;
	}
	public function file_search($param)
	{
		$term = mysql_real_escape_string($param);
		$sql = "SELECT FROM LOWER(files) WHERE LOWER(file_name) LIKE LOWER('%".$term."%')";
		$r_query = mysql_query($sql);
		while ($row = mysql_fetch_array($r_query))
		{
			echo '<br>Filename: '.$row['file_name'];
		} 
	}
}
?>
