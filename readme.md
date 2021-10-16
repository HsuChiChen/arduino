# Single Chip System
Time : 2021 fall (first half semester of junior)

## lecture

|subject|teacher|
|:-:|:-:|
|[單晶片系統](http://class-qry.acad.ncku.edu.tw/syllabus/online_display.php?syear=0110&sem=1&co_no=E230900&class_code=)|[戴政祺](https://www.ee.ncku.edu.tw/teacher/index2.php?teacher_id=125)|

|周次|日期|課程|
|:-:|:-:|:-:|
|W1|09/16|[110學年課程介紹](https://hackmd.io/@nsyRI3v6SuG6fKQFyi9Ugg/Hy_OTeRWK)|
|W2|09/23|[跑馬燈、按鍵、多工七段顯示器、鍵盤](https://hackmd.io/@Alanzzzz/SJDW5IumK)|
|W4|09/30|[密碼鎖、計步器](https://hackmd.io/@G8HrHAUqQyCt9mHFYW05UA/rJSzxDQ-K#Arduino%E8%AC%9B%E7%BE%A9%EF%BC%9A%E8%A8%88%E6%AD%A5%E5%99%A8)|
|W5|10/07|[SPI、藍芽模組](https://hackmd.io/@9ScCWm6PQhCqJjg8JfJKzQ/SJ2Ig1nVt)|


<br>

## Report
> more info in the separate files
- [lab1](#lab1)
- [lab2](#lab2)
- [lab3](#lab3)
- [lab4](#lab4)
- [lab5](#lab5)

<br>

## Environment
1. OS
- `Windows 10 21H1`
2. IDE
- [`Arduino IDE 1.8.16`](https://www.arduino.cc/en/software)
3. Text Editor
- `VScode 1.60.2` with plug-in  [`Arduino`](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)

|項目|規格|
|:-:|:-:|
|板子|Arduino R3 with ATmega328P, 16 MHz|
|lab1 新增模組|Multiplexed(4-digit) seven-segment display(顯示器), 4x4 Keypad(輸入媒介)|
|lab2 新增模組|`MPU6050`(6軸傳感器)|
|lab3 新增模組|另一個Arduino Uno板子(SPI傳輸), HC-05(藍芽模組)|
|lab4 新增模組|16×2 I2C LCD(顯示器)|

<br>

## How to Run
1. download repo
```
git clone https://github.com/HsuChiChen/arduino.git
```
2. open vscode and press shortcut `Ctrl`+`Alt`+`U` <br> to verify Arduino sketch and upload to board.

<br>

## lab1
![](img/lab1.gif)
- GPIO呈現控制LED燈，呈現**跑馬燈**、向左或向右等狀態。
- 解決按鈕的de-bouncing問題。
- 控制多工七段顯示器，顯示特定數字、**計數器**。
- 掃描式鍵盤與七段顯示器之結合，實作**碼錶**，功能如下:

|按鍵|觸發功能|
|:-:|:-:|
|`A`|進入計時模式|
|`B`|進入倒數計時模式(先輸入欲倒數秒數)|
|`C`|開始|
|`D`|暫停|
|`*`|重新開始|
|`#`|離開並進入選擇模式|
> lab4-2、lab4-3需引入`Keypad.h`的header file。

<br>

## lab2
![](img/lab2.gif)
- 可修改密碼、添加驗證碼等功能的**密碼鎖**。
- **終極密碼**小遊戲。
- 利用`MPU-6050`做出**計步器**功能並顯示在七段顯示器上。
> lab2-1需引入`Password.h`的header file，而lab2-1v2為不使用`Password.h`，用傳統C-string風格字串進行比對的版本。

<br>

## lab3
![](img/lab3.gif)
- 利用SPI進行2個Arduino板子之間通訊 - 傳字串、操控彼此LED。
- Serial Monitor上輸入再透過藍芽傳資料，控制五顆LED跑馬燈。
- 手機終端機輸入再透過藍芽傳資料，實現碼錶、密碼鎖功能。

<br>

## lab4
![](img/lab4.gif)
- 利用I2C進行Arduino間通訊 - 傳字串。
- 利用keypad與LCD實現四則運算計算機。
> lab2、lab3、lab4需引入`LiquidCrystal_I2C.h`的header file。
<br>

## Contributions
|職稱|學號|姓名|email|
|:-:|:-:|:-:|:-:|
|組長   |F94089032|劉永勝|f94089032@gs.ncku.edu.tw|
|組員一 |E24099025|李宇洋|ppalee1217@gmail.com|
|組員二 |E24099059|陳旭祺|chenneil90121@gmail.com|