<?php
require_once("logger.php.inc");

class file_db
{
	private $db;
	private $salt;
	private $logger;
	public function __construct($ini_file)
		{
		$ini = parse_ini_file($ini_file,true);
		$logger = new error_logger("var/www/log/files.log");
		$this->db = new mysqli(
			$ini["user_db"]["host"],
			$ini["user_db"]["user"],
			$ini["user_db"]["password"],
			$ini["user_db"]["db"]
		);
		$this->salt = $ini['user_db']['salt'];
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
}
?>
