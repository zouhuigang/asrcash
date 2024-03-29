//index.js
//获取应用实例
const app = getApp()
const recorderManager = wx.getRecorderManager();//录音
const innerAudioContext = wx.createInnerAudioContext();//播放录音

Page({
  data: {
    audioBtn: true,//录音按钮
    audioPath: null,//语音路径
    duration: null,//总时长,
    playBtn:true,//播放，暂停按钮,
    resultTxt:null,
    isShowAhturoizeWarning:true
  },
  onLoad: function () {
    
  },
  play(){
    //播放声音文件  
    var __this = this;
    innerAudioContext.src = __this.data.audioPath;
    if (__this.data.playBtn){
      innerAudioContext.play();
      __this.setData({
        playBtn: false
      });
      console.info("播放");
      
    }else{
      innerAudioContext.pause();
      __this.setData({
        playBtn: true
      });
      console.info("暂停");
    }

    //自然播放结束
    innerAudioContext.onEnded(() => {
       __this.setData({
         playBtn: true
       });
       console.info("播放结束");
      return;
    })

    //出错
    innerAudioContext.onError((res) => {
      console.log("出错"+res.errMsg)
      console.log("出错code:"+res.errCode)
    })
    
  },
  startAudio() {
  },
  touchStart(){
    console.info("长按开始");
    const options = {
      format: 'mp3',//音频格式，有效值 aac/mp3
      frameSize: 10,//指定帧大小，单位 KB
    }
    //开始录音
    wx.getRecorderManager().start(options);
    //开始时触发的事件
    wx.getRecorderManager().onStart(() => {
      this.setData({
        audioBtn: false,
        playBtn: true
      })
    });
    //出错
    wx.getRecorderManager().onError((res) => {
      console.log(res)
    })

  },
  touchEnd(){
    console.info("长按结束");
    wx.getRecorderManager().stop();
    wx.getRecorderManager().onStop((res) => {
      this.setData({
        audioBtn: true,
        audioPath: res.tempFilePath,
        duration: res.duration
      });
      //上传录音至服务器
      this.uploadFile();
    });

    
  },
  uploadFile(){
        var __this=this;
        wx.uploadFile({
          url: "http://c3.ab.51tywy.com/api/v1.0/cash/asr",
          filePath: __this.data.audioPath,
          name: 'audio',
          header: {
            'content-type': 'multipart/form-data'
          },

          success: function (res) {
            var str = res.data;
            var data = JSON.parse(str);
            __this.setData({
              resultTxt: data.data.result
            });
          },

          fail: function (res) {
            console.log(res);
          }
        });
  },
  //登录获取code
  getUserInfo: function () {
      wx.login({
        success(res) {
          var code = res.code;//登录凭证
          console.log('获取用户信息code=', code)
          if (code) {
              //2、调用获取用户信息接口
              wx.getUserInfo({
                withCredentials: true,
                success: function (res) {
                  console.log({ encryptedData: res.encryptedData, iv: res.iv, code: code })
                  //3.解密用户信息 获取unionId
                  //...
                },
                fail: function () {
                  console.log('获取用户信息失败')
                }
              })

          } else {
            console.log('登录失败！' + res.errMsg)
          }
        }
      })
  }

})
