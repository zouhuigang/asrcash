###微信小程序语音转化为文字

	1、微信小程序录音，提交到服务器（此时音频格式为silk）；
	
	2、利用silk-v3-decoder（https://github.com/kn007/silk-v3-decoder）， 把silk 转换成pcm格式 （silk/decoder  /data/test.silk  /data/1.pcm）；
	
	3、 用 ffmpeg  把 44100 采样率 单声道 16bts pcm 文件转 16000采样率 16bits 位深的单声道pcm文件 
	
	ffmpeg -y -f s16le -ac 1 -ar 44100 -i test44.pcm -acodec pcm_s16le -f s16le -ac 1 -ar 16000 16k.pcm （获得pcm文件）
	
	ffmpeg -y -f s16le -ar 24000 -ac 1 -i /data/1.pcm -f wav -ar 16000 -b:a 16 -ac 1 /data/1.wav  （获得wav文件）
	
	4、调用百度api 转换 pcm ， 就能获取百度转换后的 文字



https://github.com/ferrinweb/voicedictation-webapi-demo


wx468a3239ab5d6771


ddf98eb319bf58e9faa6c2f6635d67fe