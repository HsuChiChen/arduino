# 單晶片lab11結報
###### tags: `stm32`
###### 實驗日期 : 2021/12/30
## 上課教材
- [USBHost](https://hackmd.io/@9ScCWm6PQhCqJjg8JfJKzQ/SkYDpZqoY)

## lab1
### SPEC
開發板連接滑鼠。
- 在serial monitor上顯示滑鼠的資訊
- 滑鼠控制LED燈 - 左鍵LED1閃爍、右鍵LED2閃爍、中鍵LED3閃爍

### 實現方法
與[lab2](https://hackmd.io/@arduino/report-11#lab2)寫在一起。

## lab2
### SPEC
開發板連接鍵盤。
- 在serial monitor上顯示使用者輸入字母或符號

### 實現方法
```cpp
Thread mouseTask(mouse_task, NULL, osPriorityNormal, 256 * 4);
Thread keyboardTask(keyboard_task, NULL, osPriorityNormal, 256 * 4);
```
新增兩個執行序，賦予它執行`mouse_task`與`keyboard_task`的task(subfunction)，當接收到滑鼠或是鍵盤的event時
```cpp
mouse.attachEvent(onMouseEvent);
keyboard.attach(onKey);
```
會觸發程序員自定義的`onMouseEvent`,`onKey`處理函式。

## 心得
### 劉永勝
這次利用鍵盤和滑鼠讓stm32，讀取USB的輸入值，同樣是利用之前`thread`的原理，stm32接收到讀取值後，再達成對應的實作要求。官方已有釋出`attach()`的基本使用方式，只要在`thread`執行程序中，添加LED的亮燈即可。實驗中也發現，若使用藍芽滑鼠，其滑鼠的x、y、z座標會無法顯示，可能是藍芽和USB的傳輸協定不同所造成。這次實驗並沒有比較了解USB之傳輸方式，只是知道stm32能讀取滑鼠和鍵盤的資訊而已。

### 李宇洋
此次實驗主要在熟悉stm32與USB的搭配使用，雖然一樣是使用`thread`進行，但是難度以及複雜度很明顯低於上兩次的實驗，雖然此次實驗較快做完但和上次一樣不太能確定學到了什麼。

### 陳旭祺
最後一次實驗能感覺到難度已大幅降低，學習使用[USBHost](https://os.mbed.com/handbook/USBHost)這個library，首先是創建一個thread，也就是一個task，當接收到滑鼠或是鍵盤的event時，就會呼叫我們自定義的函數，完成任務。

關於原理的部分，USB是一種數據通信方式，分為這次實驗的Host與OTG。
- **Host**<br>
USB是由Host端控制整個總線的數據傳輸的。單個USB總線上，只能有一個Host。
- **OTG**<br>
On The Go，這是在USB2.0引入的一種mode，提出了一個新的概念叫主機協商協議(Host Negotiation Protocol)，允許兩個設備間商量誰去當Host。
<br><br>
由於手機只有一個外接USB口，爲了方便用戶使用，如OTG上插上一條可以支持U盤插入的線，手機就可以直接訪問U盤的內容，不需要經過PC，手機給外設供電。若手機連上PC，PC上的USB口基本爲host端，爲方便使用，手機端作爲device端比較方便合理。因此手機端的USB支持host、device模式的自動切換。OTG即是增加了host、device協商機制的USB口。
- ref 1 : [USB HOST與 USB OTG的區別及工作原理](https://twgreatdaily.com/xCveIG4BMH2_cNUgi5Yc.html)
- ref 2 : [USB host、usb device、USB OTG的判斷](https://www.twblogs.net/a/5d166cf5bd9eee1e5c82a09b)