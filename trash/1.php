<?php
class clientDB
{
    private $db;
    public function __construct()
    {
	$this->db = new mysqli("localhost","root","asdfasdf","it202");

	if ($this->db->connect_errno > 0 )
	{
		echo __FILE__.__LINE__."failed to connect to database re: ".$this->db->connect_error.PHP_EOL;
		exit(0);
	}
	echo "db connected!".PHP_EOL;
    }
    public function __destruct()
    {
	$this->db->close();
	echo "db closed".PHP_EOL;
    }

    public function getClientId($name)
    {
	$query = "select clientId from clients where clientName = '$name';";
	$results = $this->db->query($query);
	if (!$results)
	{
	    echo "error with results: ".$this->db->error.PHP_EOL;
	    return 0;
	}
        $client = $results->fetch_assoc();
	if (isset($client['clientId']))
	{
	    return $client['clientId'];
	}
	return 0;
    }

    public function validateClient($name,$password)
    {
	if ($this->getClientId($name) == 0)
        {
	    echo "user $name does exists!!!!!".PHP_EOL;
	    return false;
	}
	$query = "select * from clients where clientName='$name';";
	$results = $this->db->query($query);
	if (!$results)
	{
	    echo "error with results: ".$this->db->error.PHP_EOL;
	    return false;
	}
        $client = $results->fetch_assoc();
        {
	    if ($client['clientPW'] == $password)
	    {
		return true;
	    }
        }
        return false;
    }

    public function addNewClient($name,$password)
    {
	if ($this->getClientId($name) != 0)
        {
	    echo "user $name already exists!!!!!".PHP_EOL;
	    return false;
	}
        $now = date("Y-m-d h:i:s",time());
        $addQuery = "insert into clients (clientName,clientPW, firstLogin, lastLogin) values ('$name','$password','$now','$now');";
	echo "executing statement: \n$addQuery".PHP_EOL;
        $results = $this->db->query($addQuery);
	if (!$results)
	{
	    echo "error: ".$this->db->error.PHP_EOL;
	}
    }

}
// at this point db is connected
?>
