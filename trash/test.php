#!/usr/bin/php
<?php
echo "Garbage script".PHP_EOL;
$newArray = array();
$newArray[] = 1;
$newArray[] = 2;
$newArray[] = 3;
$newArray[4] = 5;
$newArray[] = 10;
$newArray[] = 20;
$newArray[ayy] = 50;
$newArray[100] = applesauce;
function agentOrange($word, array $arrayIn = NULL)
{
  if ($arrayIn === NULL)
  {
    echo __FILE__.":".__LINE__.": NULL ARRAY".PHP_EOL;
    $return = "Array not found, dummy.";
  }
  foreach ($arrayIn as $pawn)
  {
    echo __FILE__.":".__LINE__.": $word - $pawn".PHP_EOL;
    $return .= $pawn;
  }
  return $return;
}
$ret = agentOrange("davy in the navy");
echo $ret.PHP_EOL;
$ret = agentOrange("davy in the navy",$newArray);
echo $ret.PHP_EOL;
echo "Test PHP END".PHP_EOL;
?>
