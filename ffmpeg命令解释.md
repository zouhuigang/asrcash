### 参数拼接


	ffmpeg {常用参数} {输入音频参数} {输出音频参数}


示例： 输入是 32000HZ的单声道 16bits pcm文件。查询之前的输入参数为 “ -f s16le -ac 1 -ar 32000 -i test32.pcm” 输出是 16000HZ的单声道 16bits pcm文件。查询之前的输出参数为 “-f s16le -ac 1 -ar 16000 16k.pcm” 常用参数选择 -y


	ffmpeg  -y  -f s16le -ac 1 -ar 32000  -i test32.pcm -f s16le -ac 1 -ar 16000 16k.pcm


参数解释:

	-acodec pcm_s16le pcm_s16le 16bits 编码器 
	-f s16le 			#16bits pcm格式
	-ac 1 				#单声道
	-ar 16000  			#16000采样率



###输入(音频参数)

>wav amr 与mp3格式都自带头部， 含有采样率 编码 多声道等信息。
>
>而pcm为原始音频信息，没有类似头部。 wav（pcm编码）格式，仅仅在同样参数的pcm文件加了个几百k的文件头


输入 wav amr 及mp3格式：

	-i  test.wav
	//或test.mp3 或者 test.amr


输入 pcm格式： pcm需要额外告知编码格式，采样率，单声道信息

	-f s16le -ac 1 -ar 16000 -i 8k.pcm
	// 单声道 16000 采样率  16bits编码 pcm文件



### 输出

>在原始采样率 大于或者接近16000的时候，推荐使用16000的采样率。 8000的采样率会降低识别效果。 输出wav和amr格式时，如果不指定输出编码器的haunt，ffmpeg会选取默认编码器。


输出pcm音频:

	-f s16le -ac 1 -ar 16000 16k.pcm  
	// 单声道 16000 采样率 16bits编码 pcm文件

输出wav 音频：

	-ac 1 -ar 16000 16k.wav 
	// 单声道 16000 采样率 16bits编码 pcm编码的wav文件