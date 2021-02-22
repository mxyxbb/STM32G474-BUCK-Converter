# STM32G474CET6 HRTIM Configuration

This demo configures one channle high resolution pwm output using the hrtim of stm32g474cet6.

let's see how i do it.

**1st.** select `TA1 output active` at the pull bar of TimerA

![image-20210222202012349](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222202020.png)

**2nd.** set the period which decide the PWM frequency which can be calculated like this.

`5.44E9Hz / 27200 = 200000Hz`

![image-20210222202300310](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222202300.png)

> by the way, if you want to generate a pair of complementary PWM, you can insert a dead time by selecting `deadtime is inserted between output1 and output2` which is shown in the picture downbelow.

> ![image-20210222202534779](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222202534.png)

Now go back to the topic.

**3rd.**  For `Compare Unit 1` section change the configuration setting to `Enable`. Enter a `Compare Value` of `13600`. This is the initial value of the duty cycle fixed to 50%. The compare event is used later on as a reset source to clear the output.

when the counter come to this value, a `timer compare event` will be generated

> you can also enable other `compare unit` and set the `compare value`. You can use them for `ADC trigger event`.  This trick is talked in another branch in this repo. 

![image-20210222202900686](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222202900.png)

**4th.** set the `Set Source Selection` to `1` , and the `      1st Set Source  ` will come up, its defult content is `Timer period event forces the output to its active state`, which means the PWM output will be set to low level every time the timer count from 27200 to 0. We will leave it there, **we don't modify it.**

also, set the `Reset Source Selection` to `1` , and the `      1st Reset Source  ` will come up as well, its defult content is `Timer period event forces the output to its inactive state`, whose meaning has been explained just now. Here, we will modify it, select `Timer compare 1 event forces the output to its inactive`  in the dropdown list. This is the event that decide the PWM duty circle.

![image-20210222203929370](https://gitee.com/buddismblingblinghead/MxyPic/raw/master/img/20210222203929.png)

that's all for the hrtim configuration, then you can generate code to keil MDK.

then use this function to start the PWM output.

```
HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_TIMER_A);
HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1);
```

you can change the freq by changing `hhrtim1.Instance->sTimerxRegs[0].PERxR`, which you have set to 27200 in the cubeMX.

and you can set the compare value which decide the pwm duty circle by changing  `hhrtim1.Instance->sTimerxRegs[0].CMP1xR` , which you have set to 13600 in the cubeMX.

for other timers, refer to this

> sTimerxRegs[0]---->TimerA
> sTimerxRegs[1]---->TimerB
> sTimerxRegs[2]---->TimerC
> sTimerxRegs[3]---->TimerD