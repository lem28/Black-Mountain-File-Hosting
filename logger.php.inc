<?php
class error_logger
{
	public function __construct($output_file = "var/log/php.log")
	{
		$this->fp = fopen($output_file,"a");
	}
	public function log()
	{
		fwrite($this->fp,$message.PHP_EOL);
	}
	public function __destruct()
	{
		fclose($this->fp);
	}
}
?>
