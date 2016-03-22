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
    public function get_file($filename)
    {
        $get_query   = "select file_name from files where file_name='$filename';";
        $get_results = $this->db->query($get_query);
        if (!$get_results) {
            $this->logger->log("error with results: " . $this->db->error);
            return 0;
        }
        $file = $get_results->fetch_assoc();
        if (isset($filename['file_name']))
            return $filename['file_name'];
        }
        return 0;
    }
    public function file_upload($expiration)
    {
        $filename = $this->db->real_escape_string($filename);
        if ($this->get_file($filename) != 0) {
            $this->logger->log("file $filename already exists!!!!!");
            $response = array(
                "message" => "file $filename already exists!",
                "success" => false
            );
            return $response;
        }
        $target = "uploads/";
        $target = $target . basename($_FILES['uploaded']['name']);
        $ok     = 1;
        if (move_uploaded_file($_FILES['uploaded']['tmp_name'], $target)) {
            echo "<p>The file " . basename($_FILES['uploadedfile']['name']) . " has been uploaded";
        } else {
            echo "<p>Sorry, there was a problem uploading your file.";
        }
        $now         = date("Y-m-d h:i:s", time());
        $expiration  = strtotime("$expiration days", strtotime($now));
        $expiration  = $expiration;
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
        if (!$add_results) {
            $this->logger->log("error with results: " . $this->db->error);
        } else {
            echo "<p>Added $filename" . PHP_EOL;
        }
        return 0;
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
		$dir='uploads';
		$handle=opendir($dir); 
		while(($file=readdir($handle))!==false) 
		{
		    if($file!=='.'&&$file!=='..') 
		    { 
		        echo $file . ' '; 
		    } 
		}		 
		echo '<br />';
		$list=scandir($dir);
		foreach($list as $file) 
		{
		    if($file!=='.'&&$file!=='..') 
		    {
		        echo $file . ' '; 
		    } 
		}
	}
}
?>
