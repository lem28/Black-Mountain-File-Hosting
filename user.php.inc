<?php
require_once("logger.php.inc");

class user
{
	private $db;
	private $salt;
	private $logger;
	public function __construct($ini_file)
		{
		$ini = parse_ini_file($ini_file,true);
		$logger = new error_logger("var/www/log/users.log");
		$this->db = new mysqli(
			$ini['db']['host'],
			$ini['db']['user'],
			$ini['db']['password'],
			$ini['db']['db']
		);
		$this->salt = $ini['db']['salt'];
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
	public function get_login_name($login_name)
	{
		$get_query = "select login_name from users where login_name='$login_name';";
		$get_results = $this->db->query($get_query);
		if(!$get_results)
		{
			$this->logger->log("error with results: ".$this->db->error);
			return 0;
		}
		$user = $get_results->fetch_assoc();
		if (isset($user['login_name']))
		{	
			return $user['login_name'];
		}
		return 0;
	}
	private function salt_password($password)
	{
		return $this->db->real_escape_string(sha1($password.$this->salt));
	}
	public function validate_user($login_name,$password)
	{
		if ($this->get_login_name($login_name) == 0)
		{
			$this->logger->log("user $login_name doesn't exist");
			return false;
		}
		$validate_query = "select login_name from users where user_name='$name';";
		$validate_results = $this->db->query($validate_query);
		if(!$validate_results)
		{
			$this->logger->log("error with results: ".$this->db->error);
			return 0;
		}
	}
	public function add_new_user($login_name,$password,$first_name,$last_name,$email)
	{
		if ($this->get_login_name($login_name) != 0)
		{
			$this->logger->log("user $login_name already exists");
			$response = array(
			"message"=>"file $filename already exists!",
			"success"=>false
			);
			return false;
		}
        $now = date("Y-m-d h:i:s",time());
		$name = $this->db->real_escape_string($name);
		$password = $this->salt_password($password);
		$add_query = "
			INSERT INTO users
			(
				user_login,
				user_pw,
				user_first_name,
				user_last_name,
				user_email,
				first_login,
				last_login
			)
			VALUES
			(
				'$login_name',
				'$password',
				'$first_name',
				'$last_name',
				'$email',
				'$now',
				'$now'
			);";
		$add_results = $this->db->query($add_query);
		if(!$results)
		{
			$this->logger->log("error with results: ".$this->db->error);
		}
		else
		{
			echo "Added $login_name".PHP_EOL;
		}
		return 0;
	}
}
?>
