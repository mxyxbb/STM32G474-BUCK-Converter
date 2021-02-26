
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MYMATH_H__
#define __MYMATH_H__
/*********************************/
/*          通用宏定义库         */
/*  提升代码的精简程度以及可读性 */
#define abs(x) (((x) > 0) ? (x) : -(x))
#define min(a,b)                ((a)<(b)?(a):(b))
#define max(a,b)                ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

/**
  * @brief  获取一个数组的元素个数
  * @param  arr:数组名(任意类型)
  * @retval 这个数组的元素个数
  */
#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))
/**
  * @brief  将一个值的变化区间线性映射到另一个区间
  * @param  x:被映射的值(任意类型)
  * @param  in_min:被映射的值的最小值
  * @param  in_min:被映射的值的最大值
  * @param  out_min:被映射的值的最小值
  * @param  out_min:被映射的值的最大值
  * @retval 映射值输出
  */
#define __Map(x,in_min,in_max,out_min,out_max) \
    (((x)-(in_min))*((out_max)-(out_min))/((in_max)-(in_min))+(out_min))
/**
  * @brief  将一个值限制在一个范围内
  * @param  x:被限制的值(任意类型)
  * @param  min:最小值(任意类型)
  * @param  max:最大值(任意类型)
  * @retval 无
  */
#define __LimitValue(x,min,max) ((x)=constrain((x),(min),(max)))
/**
  * @brief  让一个变量增加或者减去一个值，在大于等于最大值后从0开始，低于0后从最大值开始
  * @param  src:被控变量
  * @param  step:增加或者减少的值
  * @param  max:最大值
  * @retval 无
  */
#define __ValueStep(src,step,max) ((src)=(((step)>=0)?(((src)+(step))%(max)):(((src)+(max)+(step))%(max))))
/**
  * @brief  函数只执行一次，常用于初始化
  * @param  func:被调用函数(也可以是赋值等其他语句)
  * @retval 无
  */
#define __ExecuteOnce(func)\
do{\
    static bool isInit = false;\
    if(!isInit){func,isInit=true;}\
}while(0)




#define MSB(x) (((x) >> 8) & 0xff) /* x占2byte（如short）2byte的高地址的1byte */
#define LSB(x) ((x) & 0xff)	/* x占2byte（如short）2byte的低地址的1byte*/

#define MSW(x) (((x) >> 16) & 0xffff) /* x占4byte（如int）  4byte的高地址的2byte */
#define LSW(x) ((x) & 0xffff) 		  			
#define WORDSWAP(x) (MSW(x) | (LSW(x) << 16)) /* x占4byte（如int） 低2字节与高2字节内容交换 */	

#define LLSB(x)	((x) & 0xff)	/*x占4byte（如int） 取低地址1byte*/					
#define LNLSB(x) (((x) >> 8) & 0xff)
#define LNMSB(x) (((x) >> 16) & 0xff)
#define LMSB(x)	 (((x) >> 24) & 0xff)


/* number of elements in an array */
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0])) 	
	
#endif
