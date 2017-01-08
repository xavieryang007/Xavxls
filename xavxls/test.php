<?php
echo memory_get_usage(), '<br />'; // 313864 
 $starttime = explode(' ',microtime());
 echo microtime();
$xav=new Xavxls();
$xav->setfilename('test2.xls','UTF-8');

$xav->inititerator(0);
echo $col=$xav->GetColCount(0);
echo $row=$xav->GetRowCount(0);

for($i=1;$i<$row;$i++){
    for($j=1;$j<$col;$j++){
        $xav->GetCell(0,$i,$j);
    }
}

 $endtime = explode(' ',microtime());
 $thistime = $endtime[0]+$endtime[1]-($starttime[0]+$starttime[1]);
 $thistime = round($thistime,3);
 echo "本网页执行耗时：".$thistime." 秒。".time();

 echo "neicun:".memory_get_usage(); // 313952 
