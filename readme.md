# Single Chip System
Time : 2021 fall (first half semester of junior)

## lecture

|subject|teacher|
|:-:|:-:|
|[單晶片系統](http://class-qry.acad.ncku.edu.tw/syllabus/online_display.php?syear=0110&sem=1&co_no=E230900&class_code=)|[戴政祺](https://www.ee.ncku.edu.tw/teacher/index2.php?teacher_id=125)|

- [110學年課程介紹](https://hackmd.io/@nsyRI3v6SuG6fKQFyi9Ugg/Hy_OTeRWK)
- [跑馬燈＋按鍵+多工七段顯示器＋鍵盤](https://hackmd.io/@Alanzzzz/SJDW5IumK)

<br>

## Report
> more info in separate file
- [lab1](#lab1)
- [lab2](#lab2)
- [lab3](#lab3)
- [lab4](#lab4)

<br>

## Environment
1. OS
- `Windows 10 21H1`
2. IDE
- [`Arduino IDE 1.8.16`](https://www.arduino.cc/en/software)
3. Text Editor
- `VScode 1.60.2` with plug-in  [`Arduino`](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)

|規格|描述|
|:-:|:-:|
|板子|Arduino R3 with ATmega328P, 16 MHz|
|模組|多工七段顯示器, 4x4 Keypad, etc.|

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
- GPIO呈現控制LED燈，呈現跑馬燈、向左或向右等狀態。
- 解決按鈕的de-bouncing問題。
- 控制多工七段顯示器，顯示特定數字、計數器。
- 掃描式鍵盤與七段顯示器之結合，實作碼錶，功能如下:

|按鍵|觸發功能|
|:-:|:-:|
|`A`|進入計時模式|
|`B`|進入倒數計時模式(先輸入欲倒數秒數)|
|`C`|開始|
|`D`|暫停|
|`*`|重新開始|
|`#`|離開並進入選擇模式|
> lab4-2、lab4-3需引入`Keypad.h`的header file。

## Contributions
|職稱|學號|姓名|email|
|:-:|:-:|:-:|:-:|
|組長   |F94089032|劉永勝|f94089032@gs.ncku.edu.tw|
|組員一 |E24099025|李宇洋|ppalee1217@gmail.com|
|組員二 |E24099059|陳旭祺|chenneil90121@gmail.com|