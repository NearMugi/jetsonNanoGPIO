# jetsonNanoGPIO
JetsonNano のGPIOを使う 

## C++向けのライブラリを追加する
[pjueon/JetsonGPIO](https://github.com/pjueon/JetsonGPIO)のライブラリを使う  
**Installation**だけ実行

### GPIOを使えるようにする
[「Jetson Nano」でにゃんこを判別してLチカで知らせるエッジAIデバイスを作る (2/4)](https://monoist.atmarkit.co.jp/mn/articles/1910/23/news038_2.html)

Pythonのパッケージをインストール
```
pip install Jetson.GPIO
```

gpioというグループを作って、そこにユーザーを追加する
```
sudo groupadd -f -r gpio
sudo usermod -a -G gpio your_user_name（←ここに自分のユーザー名を入れる）
```
グループ権限を追加　※ここが参考URLと違う
```
sudo cp ./.local/lib/python3.6/site-packages/Jetson/GPIO/99-gpio.rules /etc/udev/rules.d/
```
反映
```
sudo udevadm control --reload-rules && sudo udevadm trigger
```
再起動
```
sudo reboot
```
