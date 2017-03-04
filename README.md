#Xavxls
Xavxls是一个读取xls文件的PHP扩展（暂不支持写入）。在PHP开发中经常会读取excel，xlsx格式文件采用php直接读取速度还可以接受，xls格式文件就无法忍受了，一个10M的xls，根本就可以宣告无法读取了，因为消耗的内存和CPU实在太大了，而且慢的无可救药。因此，Xavxls就应运而生了。


##Xavxls 编译环境搭建
###Xavxls目录结构
phpcpp phpcpp的源码，一种采用C++来快速开发PHP扩展的sdk

libxls C语言读取xls的库

xavxls Xavxls 项目源码
###编译PHPCPP
[http://www.php-cpp.com/](http://www.php-cpp.com/ "PHPCPP官方")

```
git clone git@git.oschina.net:xavier007/Xavxls.git
```

```
cd phpcpp
```

```
make
```

```
sudo make install
```

项目中自带的PHPCPP是开发xavxls采用的版本，也可以直接从官网下载。由于PHPCPP版本问题，只支持PHP7或PHP7 up。如果需要支持PHP5.X可以下载PHPCPP的另外一个版本PHP-CPP-LEGACY，其中PHP-CPP-LEGACY和PHPCPP的API是一样的，只是为了兼容PHP7而开发的新的PHPCPP，所以老的版本重新取了个名字而已。

PHPCPP PHP7版本  github下载地址 [https://github.com/CopernicaMarketingSoftware/PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP)

PHP-CPP-LEGACY PHP5.X版本  github下载地址 [https://github.com/CopernicaMarketingSoftware/PHP-CPP-LEGACY](https://github.com/CopernicaMarketingSoftware/PHP-CPP-LEGACY)

###编译LIBXLS
libxls项目地址[http://libxls.sourceforge.net/](http://libxls.sourceforge.net/)
libxls是一个跨平台的xls读取库
上传的时候libxls的权限丢失了，所以需要修改一下权限

```
chmod +x configure
```

```
./configure
```

```
make
```

```
sudo make install
```

由于头文件跟库文件的目录放的位置不对，所以需要手动把它们拷贝到系统路径下面去

```
cp -r -v /usr/local/libxls/include/libxls/ /usr/include
cp -r -v /usr/local/libxls/lib/ /usr

cp -r -v /usr/local/libxls/include/xls.h /usr/include
```

一个简单的例子：read_xls.c
```
#include <stdio.h>  
#include <stdlib.h>  
#include <xls.h>  
#include <unistd.h>  
#include <string.h>  
int main(int argc, char **argv) {  
  xlsWorkBook *pWb;  
  xlsWorkSheet *pWs;  
  struct st_row_data *row;  
  int r,c;  
  char buf[512], result[512];  
  
  if (argc < 2) {  
    fprintf(stderr, "please input the xml file.");  
    return EXIT_FAILURE;  
  }  
  
  pWb = xls_open(argv[1], "UTF-8");  
  if (NULL == pWb) {  
    fprintf(stderr, "File not found!\n");  
    return EXIT_FAILURE;  
  }  
  
  pWs = xls_getWorkSheet(pWb, 0);   
  xls_parseWorkSheet(pWs);  
  
  for (r=0; r<=pWs->rows.lastrow; r++) {  
    row = &pWs->rows.row[r];  
  
    for (c=0; c<=pWs->rows.lastcol; c++) {  
      if (row->cells.cell[c].str != NULL) {  
        printf("%s\t",  
            row->cells.cell[c].str);  
      }     
    }     
    printf("\n");  
  }  
  
  xls_close_WS(pWs);  
  
  xls_close_WB(pWb);  
  
  return 0;  
}  
```

编译运行

```
error while loading shared libraries: libxlsreader.so.1: cannot open shared  

```



出现这类错误表示，系统不知道xxx.so放在哪个目录下，这时候就要在/etc/ld.so.conf中加入xxx.so所在的目录。
一般而言，有很多的so会存放在/usr/local/lib这个目录底下，去这个目录底下找，果然发现自己所需要的.so文件。

所以，在/etc/ld.so.conf中加入/usr/local/libxsl/lib这一行，保存之后，再运行：/sbin/ldconfig –v更新一下配置即可。

或者在/etc/ld.so.conf.d/下新建一个.conf文件，并在其中加入目标路径就可以了，在运行/sbin/ldconfig

###编译安装Xavxls


```
git clone git@git.oschina.net:xavier007/Xavxls.git
```

```
cd xavxls
```

```
make
```

```
sudo make install
```

编辑PHP.ini添加

```
extension=Xavxls.so
```




#为什么开发Xavxls

如果你做PHP开发，且经常需要读取xls，如果你用原生PHP来开发，比如采用phpexcel（一个很优秀的PHP EXCEL类库），excel文件很小还好，如果有2M，3M，甚至10M，你会怎么处理呢？增加PHP的运行时间，防止30秒挂掉，增加PHP的内存限制，防止读取excel的时候内存不足。PHP运行时间增加对整个服务的影响是很大的，为什么？因为处理xls格式比较慢，比如10M的excel，默认的内存限制肯定是不够用的，至少需要开到500M以上，时间肯定不是10S可以搞定的，对于一个10人同时访问的网站来说，消耗的内存就到达到四五G了，好恐怖吧！10来个人的网站消耗就这么大！

#Xavxls 接口

setfilename 参数 文件名，编码 ，无返回

```
$xav=new Xavxls();
$xav->setfilename('test2.xls','UTF-8');
```

inititerator 参数sheet的编号 从0开始，如第一个sheet就是0 

```
$xav->inititerator(0);
```

getversion  返回版本号

```
$xav->getversion();
```


getsheetname 参数 sheet编号， 返回指定编号的名字 如第一个sheet名字为sheet1，

```
$xav->getsheetname(0);//输出sheet1
```



getsheetcount  返回sheet的个数

```
$xav->getsheetcount();
```

GetRowCount   参数 sheet编号  获取指定sheet的总行数

```
$xav->GetRowCount(0);
```

GetColCount 参数 sheet编号  获取指定sheet的总列数

```
$xav->GetColCount(0);
```

GetCell 参数 sheet编号 ，行，列  行和列必须大于等于1， 返回指定cell的内容


```
$xav->GetCell(0,1,2);
```

#测试

采用原生PHP操作14.6M的excel直接提示内存不足了  使用的PHPEXCEL

```
<?php
echo memory_get_usage(), '<br />'; 
 $starttime = explode(' ',microtime());
 echo microtime();


include "Classes/PHPExcel.php";
$PHPExcel=new PHPExcel();
$PHPReader=null;

include "Classes/PHPExcel/Reader/Excel5.php";
$PHPReader=new PHPExcel_Reader_Excel5();
$PHPExcel=$PHPReader->load('1.xls');
$currentSheet = $PHPExcel->getSheet(0);        
$allColumn = $currentSheet->getHighestColumn();        
$allRow = $currentSheet->getHighestRow();  
for($rowIndex=2;$rowIndex<=$allRow;$rowIndex++){ 
		$data = array();       //循环读取每个单元格的内容。注意行从1开始，列从A开始
		        for($colIndex='A';$colIndex<=$allColumn;$colIndex++){
                        $addr = $colIndex.$rowIndex;
		                $cell = $currentSheet->getCell($addr)->getValue();
                }
}
 $endtime = explode(' ',microtime());
 $thistime = $endtime[0]+$endtime[1]-($starttime[0]+$starttime[1]);
 $thistime = round($thistime,3);
 echo "执行耗时：".$thistime." 秒。".time();

 echo "消耗内存:".memory_get_usage(); 
```

采用xavxls提示 执行耗时：39.002 秒。消耗内存:358000

```
<?php
echo memory_get_usage(), '<br />'; 
 $starttime = explode(' ',microtime());
 echo microtime();
$xav=new Xavxls();
$xav->setfilename('1.xls','UTF-8');

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
 echo "执行耗时：".$thistime." 秒。".time();

 echo "消耗内存:".memory_get_usage(); 

```

对于1-2M的excel都是0.2-0.4s就处理完了，用phpexcel肯定需要好几秒


358000byte=0.341415M内存  采用xavxls后处理14.6M的excel才消耗这么点内存，是不是很省，同时速度也很快


支持捐款，有你的支持，Xavxls会更加完善

![支付宝](http://git.oschina.net/uploads/images/2017/0105/143525_edbb5e09_2158.jpeg  "在这里输入图片标题")
![微信](http://git.oschina.net/uploads/images/2017/0105/143534_1a3baf92_2158.jpeg  "在这里输入图片标题")
