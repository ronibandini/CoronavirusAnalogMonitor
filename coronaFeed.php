<?php

// Project: Retrieve Coronavirus stats from https and prepare feed to ESP8266
// Author: Roni Bandini
// Date: 3/2020
// @RoniBandini

$feed_url="https://YourFeedWithCoronavirusCasesHere.com";
	
$content 	= file_get_contents($feed_url);
    
$content	=strval($content);      

// edit this part to identify HTML values

$pTotal		=intval(retrieveNumber($content, "<cases>", "<span>"));
$pRecovered	=intval(retrieveNumber($content, "<recovered>", "<span>"));
$pDead		=intval(retrieveNumber($content, "<deaths>", "<span>"));

$pPercentageRecovered		=$pRecovered*100/$pTotal;
$pPercentageDead			=$pDead*100/$pTotal;

$pPercentageNotRecovered	=100-$pPercentageRecovered;

$pPercentageNotDead			=100-$pPercentageDead;

// calculate degrees 1 millon - 180
$pDegrees=$pTotal*180/1000000;

// to the other side
$pDegrees=180-$pDegrees;

// print feed to ESP8266
echo $pTotal."#".$pRecovered."#".$pDead. "#".number_format($pPercentageDead, 2, '.', '');
echo "#".round($pDegrees);
echo "#".number_format($pPercentageInfected, 4, '.', '');


function retrieveNumber($content, $firstLoc, $secondLoc)

{
	
	
	$pStartPos	 =strpos($content, $firstLoc);	

	if ($pStartPos==0){
		echo "Error";
		Die();	
	}

	// cut code fragment
	$pMyFragment =substr ($content , $pStartPos, 120);
	
	$pStartPos2	=strpos($pMyFragment, $secondLoc);
	
	
	if ($pStartPos2==0){
		echo "Error";
		Die();	
	}
	
	// edit this part to identify end position
	$pEndPos	 =strpos($pMyFragment, "</span>");
	
	
	$pValueToReturn = substr ($pMyFragment, $pStartPos2+strlen($secondLoc), $pEndPos-$pStartPos2-strlen($secondLoc));
	
		
	$pValueToReturn=trim(str_replace ( "," , "" ,$pValueToReturn ));
	return $pValueToReturn;
	
}


?>

