# 将ram运行的代码跳转到sdram中运行

     
    ------------       ---------------     -------------
	|          |       |             |     |           | 
	|nandflash |------>| jz2440 ram  |---> |  sdram    |
	|          |       |             |     |           |
    -------------      ---------------     -------------




	----------       ----------
    |        |A0     | 1|2|3|4| 0x00000地址存放4个字节的数据1,2,3,4
    |        |---    |--------|   
    |        |A1     |        |
    |        |---    | SDRAM  |
    | jz2440 |A2   A0|        |
    |        |-------|        |
    |        |A3   A |        |
    |        |-------|        |
    ----------       --------
