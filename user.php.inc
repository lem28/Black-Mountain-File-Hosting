<?php
require_once("error.php.inc");
class user
{
	private $db;
	private $salt;
	private $logger;
	public function __construct($iniFile)
	{
		$ini		  = parse_ini_file($iniFile, true);
		$this->logger = new error_logger("logs/users.log");
		$this->db	  = new mysqli(
			$ini['db']["host"],
			$ini['db']["user"],
			$ini['db']["password"],
			$ini['db']["db"]);
		$this->salt   = $ini['db']["salt"];
		if ($this->db->connect_errno > 0)
		{
			$this->logger->log("failed to connect to database re: " . $this->db->connect_error);
			exit(0);
		}
		$this->logger->log("testing");
	}
	public function __destruct()
	{
		$this->db->close();
	}
	public function add_new_user($name, $password, $first_name, $last_name, $email)
	{
		if ($this->get_user_login($name) != 0)
		{
			$this->logger->log("user $name already exists!");
			$response = array(
				"message" => "user $name already exists!",
				"success" => false
			);
			return $response;
		}
		$now	   = date("Y-m-d h:i:s", time());
		$name	   = $this->db->real_escape_string($name);
		$password  = $this->salt_password($password);
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
				'$name',
				'$password',
				'$first_name',
				'$last_name',
				'$email',
				'$now',
				'$now'
			);";
		$results   = $this->db->query($add_query);
		if (!$results)
		{
			$this->logger->log("error: " . $this->db->error);
		}
		return array(
			"success" => true
		);
	}
	private function salt_password($password)
	{
		return $this->db->real_escape_string(sha1($password . $this->salt));
	}
	public function get_user_login($name)
	{
		$query   = "select user_login from users where user_login = '$name';";
		$results = $this->db->query($query);
		if (!$results)
		{
			$this->logger->log("error with results: " . $this->db->error);
			return 0;
		}
		$user = $results->fetch_assoc();
		if (isset($user['user_login']))
		{
			return $user['user_login'];
		}
		return 0;
	}
	public function validate_user($name, $password)
	{
		if ($this->get_user_login($name) == 0)
		{
			return array(
				"success" => false,
				"message" => "user does not exist"
			);
		}
		$query   = "select user_login from users where user_login = '$name';";
		$results = $this->db->query($query);
		if (!$results)
		{
			return array(
				"success" => false,
				"message" => "db failure"
			);
		}
		$user = $results->fetch_assoc();
		{
			if ($user['user_pw'] == $this->salt_password($password))
			{
				return array(
					"success" => true
				);
			}
		}
		return array(
			"success" => false,
			"message" => "failed to match password"
		);
	}
}
?>
