<?php
require_once("error.php.inc");
class file
{
	private $db;
	private $logger;
	public function __construct($ini_file)
	{
		$ini	  = parse_ini_file($ini_file, true);
		$logger   = new error_logger("logs/files.log");
		$this->db = new mysqli(
			$ini['db']['host'],
			$ini['db']['user'],
			$ini['db']['password'],
			$ini['db']['db']);
		if ($this->db->connect_errno > 0) {
			$this->logger->log("Failed to connect to database" . $this->db->connect_error);
			exit(0);
		}
		echo "<p>Connected to db" . PHP_EOL;
	}
	public function __destruct()
	{
		$this->db->close();
		echo "<p>Closed connection to db" . PHP_EOL;
	}
	public function file_get($filename)
	{
		$get_query   = "select file_name from files where file_name='$filename';";
		$get_results = $this->db->query($get_query);
		if (!$get_results) {
			$this->logger->log("error with results: " . $this->db->error);
			return 0;
		}
		$user = $get_results->fetch_assoc();
		if (isset($filename["file_name"])) {
			return $filename["file_name"];
		}
		return 0;
	}
	public function file_upload()
	{
		$filename = $this->db->real_escape_string(basename($_FILES['file_up']['name']));
		$temp = explode(".", $_FILES["file_up"]["name"]);
		$newfilename = round(microtime(true)) . '.' . end($temp);
		$host_url = "http://127.0.0.1/";
		$dir = "uploads/";
		$file_url = $host_url . $dir . $filename;
		$now = date("Y-m-d h:i:s", time());		
		$add_query   = "
			INSERT INTO files
			(
				file_name,
				file_url,
				upload_date
			)
			VALUES
			(
				'$filename',
				'$file_url',
				'$now'
			);";
		
		$add_results = $this->db->query($add_query);
		if (move_uploaded_file($_FILES['file_up']['tmp_name'], $dir . $newfilename) && $add_results)
		{
			echo "<p> The file " . basename($filename) . " has been uploaded";
		}
		else
		{
			$this->logger->log("error with results: " . $this->db->error);
			echo "<p> Sorry, there was a problem uploading your file.";
		}
		return array(
			"success" => true
		);
	}
	public function file_search($param)
	{
		$host_url = "http://127.0.0.1/";
		$dir = "uploads/";
		$term	= $this->db->real_escape_string($param);
		$search_query	 = "SELECT FROM files WHERE LOWER(file_name) LIKE LOWER('%" . $term . "%')";
		$search_results = $this->db->query($search_query);
		if ($search_results)
		{
			while ($search_result && $row = $search_results->fetch_assoc())
			{
				$filename = $row['file_name'];
				$file_url = '<a href="' . $host_url . $dir . $filename . '">' . $filename . '<a>';
				echo '<p>Filename: ' . $filename;
				echo '<p>URL: ' . $file_url;
			}
			return array(
				"success" => true
			);
		}
		else
		{
			echo '<p>No files containing "'. $term .'" found...';
		}
		return array(
			"success" => false
		);
	}
	public function file_browse()
	{
		$host_url = "http://127.0.0.1/";
		$dir = "uploads/";
		$files = glob($dir);
		foreach ($files as $file)
		{
			if($file->isDot()) continue;
			$filename = $file->getFilename();
			$file_url = '<a href="' . $host_url . $dir . $filename . '">' . $filename . '<a>';
			echo '<p>Filename: ' . $filename;
			echo '<p>URL: ' . $file_url;
		}
		echo "<p>Finished loading";
		return array(
			"success" => true
		);
	}
	public function file_scan()
	{
		$host_url = "http://127.0.0.1/";
		$dir = "uploads/";
		$files = glob($dir);
		foreach ($files as $file)
		{
			$filename = $file->getFilename();
			$file_url = $host_url . $dir . $filename;
			$now = date("Y-m-d h:i:s", time());
			$add_query   = "
			INSERT INTO files
			(
				file_name,
				file_url,
				upload_date
			)
			VALUES
			(
				'$filename',
				'$file_url',
				'$now'
			);";
			$add_results = $this->db->query($add_query);
		}
		echo "<p>Directory rescanned!";
		return array(
			"success" => true
		);
	}
}
?>
