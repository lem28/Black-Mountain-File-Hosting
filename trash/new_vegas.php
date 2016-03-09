!#usr/bin/php
<?php
echo "war".PHP_EOL;

class new_vegas
{
	private $courier;
	private $faction;
	public function __construct($courier)
	{
		$this->courier = $courier;
	}
	public function print_courier()
	{
		echo "Courier: ".$this->courier.PHP_EOL;
	}
	public function faction($faction)
	{
		if ($faction = "NCR")
		{
			$this->faction = $faction;
			echo "Eureka".PHP_EOL;
		}
		elseif ($faction = "Legion")
		{
			$this->faction = $faction;
			echo "Vini Vidi Vici".PHP_EOL;
		}
		elseif ($faction = "House")
		{
			$this->faction = $faction;
			echo "The House Always Wins".PHP_EOL;
		}
		elseif ($faction = "Independent")
		{
			$this->faction = $faction;
			echo "No Gods, No Masters".PHP_EOL;
		}
		else
		{
		echo "Your choices are only: NCR, Legion, House or Independent".PHP_EOL;
		}
	}
}

$myMojave = new new_vegas("Richard");
$myMojave->faction("NCR");
echo "war never changes".PHP_EOL;
?>
