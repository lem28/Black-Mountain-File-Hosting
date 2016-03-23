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
	public function get_file($filename)
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
		$filename = $this->db->real_escape_string(basename($_FILES['file']['name']));
		$host_url = "http://127.0.0.1/";
		$dir = "uploads";
		$url = $host_url . $dir . "/" . $filename;
		$add_query   = "
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
		$now = date("Y-m-d h:i:s", time());
		if (move_uploaded_file($_FILES['file']['tmp_name'], $dir) && $add_results)
		{
			echo "<p> The file " . basename($filename) . " has been uploaded";
		}
		else
		{
			$this->logger->log("error with results: " . $this->db->error);
			echo "<p> Sorry, there was a problem uploading your file.";
		}
	}
	public function file_search($param)
	{
		$host_url = "http://127.0.0.1/";
		$dir = "uploads";
		$term	= $this->db->mysql_real_escape_string($param);
		$search_query	 = "SELECT FROM files WHERE LOWER(file_name) LIKE LOWER('%" . $term . "%')";
		$r_query = mysql_query($search_query);
		while ($row = mysql_fetch_array($r_query))
		{
			$filename = $row['file_name'];
			$file_url = '<a href="' . $host_url . $dir . $filename . '">' . $filename . '<a>';
			echo '<br>Filename: ' . $filename;
			echo '<br>URL: ' . $file_url;
		}
	}
	public function file_browse()
	{
		$host_url = "http://127.0.0.1/";
		$dir = "uploads";
		foreach (new DirectoryIterator(dirname(__FILE__) . "/" . $dir) as $file)
		{
			if($file->isDot()) continue;
			$filename = $file->getFilename();
			$file_url = '<a href="' . $host_url . $dir . $filename . '">' . $filename . '<a>';
			echo '<br>Filename: ' . $filename;
			echo '<br>URL: ' . $file_url;
		}
		echo "Finished loading";
	}
}
?>
