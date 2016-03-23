<?php
require_once("error.php.inc");
class file
{
    private $db;
    private $logger;
    public function __construct($ini_file)
    {
        $ini      = parse_ini_file($ini_file, true);
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
    public function file_upload()
    {
        $filename = basename($_FILES['file']['name']);
        $target = "uploads";
		if (move_uploaded_file($_FILES['file']['tmp_name'], $target))
		{
			echo "<p> The file " . basename($filename) . " has been uploaded";
		}
		else
		{
			echo "<p> Sorry, there was a problem uploading your file.";
		}
    }
    public function file_search($param)
    {
		foreach (glob("$param") as $filename)
		{
			echo "$filename" . $filename . "\n";
		}
    }
	public function file_browse()
	{
		$target = "uploads";
		$host_url = "http://127.0.0.1/";
		foreach (new DirectoryIterator(dirname(__FILE__) . "/" . $target) as $file)
		{
			if($file->isDot()) continue;
			$file = $file->getFilename();
			$file_url = $host_url . $target . $file;
			echo $file_url . '<br>';
		}
		echo "Finished loading";
	}
}
?>
