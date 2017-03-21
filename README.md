加密与解密程序
========

程序介绍：
--------
程序设置了友好的用户操作界面，可以使用__鼠标和键盘__两种操作方式，通过将文件与指定的密码进行__异或运算__，起到加密文件的效果。可以加密__任何文件__，包括图片，视频，文本，可执行文件等。

### 注意：
* 使用了`gets`，而不是`scanf`
* 不能使用`system("cls")`清屏，会使`ReadConsoleInput`失效，无法读取鼠标事件
* 程序设置了随机密码，每次打开都会提示四个英文字母，密码由四个英文字母的十进制ASCII码组成。如“abcd”，密码是“979899100”。为了方便操作，设置了快捷密码__5201314__

### 缺点：
* 因为程序中使用`ReadConsoleInput`读取鼠标或键盘输入，对于键盘输入是无缓冲，而不是行缓冲，所以一旦选择了选项就不能回退修改
* 程序中为了能读取空格，所以没有用以空格为分隔符的`scanf`函数，而用了`gets`，存在缓冲区溢出的风险。程序中设定了较长的缓冲区，防止无意识错误操作的风险，但无法阻止恶意操作。
* 加密或解密时输入密码是明文
* 当用户在输入加(解)密文件之后，程序创建了新文件准备写入，若用户在此时输入密码时选择退出，则不会删除之前创建的文件

截图：
--------
![](https://github.com/TianLanhe/Encrypt/raw/master/screenshot.png)
![](https://github.com/TianLanhe/Encrypt/raw/master/screenshot2.png)
