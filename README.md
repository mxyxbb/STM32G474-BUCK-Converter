# STM32G474CET6 HRTIM trigger ADC and dma Configuration 

- one channle high resolution pwm output using the hrtim of stm32g474cet6.
- one channle adc using DMA and tirggered by hrtim

let's see how i do it.

please refer to the brach `master` to see how to generate hign resolution pwm using hrtim.

Base on that, let's do some modification.

For `Compare Unit 3` section change the configuration setting to `Enable`. Enter a `Compare Value` of `50`. This is the event that is used to trigger the ADC sample. This can be moved to a clean point in the switching cycle, which means away from the turn on or turn off of the switch.

![image-20210222212037431](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222212037.png)

Then, the ADC trigger must be configured for the HRTIM1 module. Under `HRTIM1` select the `ADC Triggers Configuration` tab. Enable the `ADC Trigger 1` and set the `Update Trigger Source` to `Timer A`, enter the number of `Trigger Sources Selection` to `1`. From the `1st Trigger Source` drop-down box, select `ADC Trigger on Timer A compare 3`. This is the event that triggers the ADC.

![image-20210222212703557](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222212703.png)

**3rd.** for adc configuration enable IN1 in `Single-ended` mode.

Select the `parameter settings` tab, Here, under the `ADC_Settings section`, change the `DMA Continuous Requests` setting to `Enabled` and change the `Overrun behaviour` setting to `Overrun data overwritten` 

![image-20210222213707122](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222213707.png)

Under the `ADC_Regular_ConversionMode` section, set the `External Trigger Conversion Source` to `High Resolution Trigger 1 event`. Then set the `External Trigger Conversion Edge` to `Trigger detection on the rising edge`.

Then configure `Offset Number` to `1 Offset`. The offset feature of the ADC allows an offset to be subtracted from the ADC value before it is stored in the results register. This is used to perform the error calculation, VERR = VREF – VOUT, in hardware. 

Set the `Offset` value to REF. REF is a term that is defined in the code later on. By default, STM32CubeMX has error checking on the input fields. To disable this and allow the currently unknown value REF to be entered into this input field, click on the cog symbol on the right-hand side of the input value and change the check to `No check`.

![image-20210222213830938](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222213831.png)

CubeMX configuration has been done.

now you can generate code.

in the `main.c` , define a variable to save the adc value

```c
/* USER CODE BEGIN PV */
uint32_t adc1_value0=0;
/* USER CODE END PV */
```

then in the main function, use functions downbelow to `calibrate` the adc and `start DMA`.

```c
    /* Perform an ADC automatic self-calibration and enable ADC */
    if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED) != HAL_OK)
    {
        /* Configuration Error */
        Error_Handler();
    }
    /* Start the DMA which is used to move ADC result to the memory */
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *) &adc1_value0, 1) != HAL_OK)
    {
        /* Configuration Error */
        Error_Handler();
    }  
```

use functions downbelow to start the `hrtim counter` and start the `wave output`.

```c
	/* Start the PWMs */
	HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_TIMER_A);
	HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1);
```

use functions downbelow to modify the `freq` and `duty circle`.

```c
    //通过修改重装载值PER，从而修改PWM的频率-200k
	hhrtim1.Instance->sTimerxRegs[0].PERxR = 27200;
	//通过修改比较值CMP，从而修改占空比
    hhrtim1.Instance->sTimerxRegs[0].CMP1xR = 1-1;

    //sTimerxRegs[0]---->TimerA
    //sTimerxRegs[1]---->TimerB
    //sTimerxRegs[2]---->TimerC
    //sTimerxRegs[3]---->TimerD
```