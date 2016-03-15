<?php
require_once("logger.php.inc");

class user_db
{
	private $db;
	private $salt;
	private $logger;
	public function __construct($ini_file)
		{
		$ini = parse_ini_file($ini_file,true);
		$logger = new error_logger("var/www/log/it202.log");
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

	public function get_user_login($username)
	{
		$get_query = "select user_login from users where user_login='$username';";
		$get_results = $this->db->query($get_query);
		if(!$get_results)
		{
			$this->logger->log("error with results: ".$this->db->error);
			return 0;
		}
		$user = $get_results->fetch_assoc();
		if (isset($username["user_login"]))
		{	
			return $username["user_login"];
		}
		return 0;
	}

	private function salt_password($password)
	{
		return $this->db->real_escape_string(sha1($password.$this->salt));
	}

	public function validate_user($username,$password)
	{
		if ($this->get_user_login($username) == 0)
        {
			return array("success"=>false,
			"message"=>"user does not exist");
		}
		$validate_query = "select * from users where user_login='$username';";
		$validate_results = $this->db->query($validate_query);
		if (!$validate_results)
		{
			return array("success"=>false,
			"message"=>"db failure");
		}
        $user = $results->fetch_assoc();
        {
			if ($user['user_pw'] == $this->saltPassword($password))
			{
				return array("success"=>true);
			}
        }
        return array("success"=>false,"message"=>"failed to match password");
	}
	public function add_new_user($username,$password,$first_name,$last_name,$email)
	{
		if ($this->get_user_login($username) != 0)
		{
			$this->logger->log("user $username already exists!!!!!");
			$response = array(
			"message"=>"user $username already exists!",
			"success"=>false
			);
			return $response;
		}
        $now = date("Y-m-d h:i:s",time());
		$username = $this->db->real_escape_string($username);
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
				'$username',
				'$password',
				'$first_name',
				'$last_name',
				'$email',
				'$now',
				'$now'
			);";
		$add_results = $this->db->query($add_query);
		if(!$add_results)
		{
			$this->logger->log("error with results: ".$this->db->error);
		}
		else
		{
			echo "Added $username".PHP_EOL;
		}
		return 0;
	}
}
?>
