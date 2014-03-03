## build

```
./configure --debug=1
make
```

## testcase

```
./test_my_curl 
./test_webwx
```

## 网页微信客户端封包大全

http://www.36kr.com/topics/4941

网页版微信功能只有一个：聊天。根据狼夜我这两天研究发现，网页版微信可以脱离手机微信，也就是手机微信退出、手机关机，都不影响网页端微信的在线以及聊天，关于如何使用加好友、朋友圈、摇一摇功能，我有个思路就是抓手机封包，然后使用，不过这个想法因为时间问题没有去实践，希望大家能研究出来的话在本页面留一个链接，十分感谢！

以下是Post/Get的封包大全，如果能看懂这个，基本上你就可以做出来了。

获取uuid

https://login.weixin.qq.com/jslogin?appid=wx782c26e4c19acffb&redirect_uri=https%3A%2F%2Fwx.qq.com%2Fcgi-bin%2Fmmwebwx-bin%2Fwebwxnewloginpage&fun=new&lang=zh_CN&_=1388994062250

获取二维码

https://login.weixin.qq.com/qrcode/uuid?t=webwx＋

等待扫描Get

https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?uuid=454d958c7f6243&tip=1&_=1388975894359

https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?uuid=454d958c7f6243&tip=1&_=1388975873359

https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?uuid=454d958c7f6243&tip=1&_=1388975883859

扫描了-返回

window.code=201;

未扫描返回空

扫描之后-第一次请求成功

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxstatreport?type=1&r=1388975895453

{"BaseRequest":{"Uin":0,"Sid":0},"Count":1,"List":[{"Type":1,"Text":"/cgi-bin/mmwebwx-bin/login, First Request Success, uuid: 454d958c7f6243"}]}

扫描之后-第二次请求开始

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxstatreport?type=1&r=1388975895453

{"BaseRequest":{"Uin":0,"Sid":0},"Count":1,"List":[{"Type":1,"Text":"/cgi-bin/mmwebwx-bin/login, Second Request Start, uuid: 454d958c7f6243"}]}

等待确认Get

https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?uuid=454d958c7f6243&tip=0&_=1388975895453

https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?uuid=454d958c7f6243&tip=0&_=1388975900953

https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?uuid=454d958c7f6243&tip=0&_=1388975906453

https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?uuid=454d958c7f6243&tip=0&_=1388975911953

手机确认-返回

window.code=200;

window.redirect_uri="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxnewloginpage?ticket=03f725a8039d418ab79c69b6ffbd771b&lang=zh_CN&scan=1388975896";

未确认返回空

get 登陆获取Cookie

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxnewloginpage?ticket=03f725a8039d418ab79c69b6ffbd771b&lang=zh_CN&scan=1388975896&fun=new

--设置Cookie 返回一个状态

post 第二次请求成功

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxstatreport?type=1&r=1388976086218

{"BaseRequest":{"Uin":0,"Sid":0},"Count":1,"List":[{"Type":1,"Text":"/cgi-bin/mmwebwx-bin/login, Second Request Success, uuid: 454d958c7f6243, time: 190765ms"}]}

post 表示登陆成功-返回重要的数据key123

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxinit?r=1388976086484

{"BaseRequest":{"Uin":"750366800","Sid":"e75TXbI7TnKUevmI","Skey":"","DeviceID":"e519062714508114"}}

post 可能是获取列表

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxsync?sid=e75TXbI7TnKUevmI&r=1388976086734

{"BaseRequest":{"Uin":750366800,"Sid":"e75TXbI7TnKUevmI"},"SyncKey":{"Count":4,"List":[{"Key":1,"Val":620916854},{"Key":2,"Val":620917961},{"Key":3,"Val":620917948},{"Key":1000,"Val":1388967977}]},"rr":1388976086734}

--这里的内容在上一步返回结果里

post 可能是获取当前会话列表-大数据

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgetcontact?r=1388976086734

{}

post 可能是在手机上显示的提示信息

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxstatusnotify?r=1388976086750

{"BaseRequest":{"Uin":750366800,"Sid":"e75TXbI7TnKUevmI","Skey":"","DeviceID":"e519062714508114"},"Code":3,"FromUserName":"langyeie","ToUserName":"langyeie","ClientMsgId":"1388976086750"}

get 获取头像图片

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgeticon?seq=1388335457&username=langyeie

get 同理可以获取其他微信好友的头像

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgeticon?seq=620917759&username=wxid_xx3mtgeux5511

post 更改什么状态？标记已读？

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxbatchgetcontact?type=ex&r=1388976086812

{"BaseRequest":{"Uin":750366800,"Sid":"e75TXbI7TnKUevmI","Skey":"","DeviceID":"e519062714508114"},"Count":10,"List":[{"UserName":"z_zer0v","ChatRoomId":3445229833},{"UserName":"huobao002","ChatRoomId":3445229833},{"UserName":"wxid_jo4qxoep4go411","ChatRoomId":3445229833},{"UserName":"jijunlong123456","ChatRoomId":3445229833},{"UserName":"wxid_toyaj4qwrynb21","ChatRoomId":3445229833},{"UserName":"wxid_6655286553012","ChatRoomId":3445229833},{"UserName":"wxid_rankrke1kkyd12","ChatRoomId":3445229833},{"UserName":"wxid_chcblpm846k022","ChatRoomId":3445229833},{"UserName":"tw297554396","ChatRoomId":3445229833},{"UserName":"wxid_3076050756212","ChatRoomId":3445229833}]}

get headimg ？头像？

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgetheadimg?seq=620917806&username=3445229833chatroom@

get 监听会话

https://webpush.weixin.qq.com/cgi-bin/mmwebwx-bin/synccheck?callback=jQuery18308660551080269895_1388975862078&r=1388976091937&sid=e75TXbI7TnKUevmI&uin=750366800&deviceid=e519062714508114&synckey=1_620916854%7C2_620917963%7C3_620917948%7C201_1388976090%7C1000_1388967977&_=1388976091937

https://webpush.weixin.qq.com/cgi-bin/mmwebwx-bin/synccheck?callback=jQuery18308660551080269895_1388975862078&r=1388976119062&sid=e75TXbI7TnKUevmI&uin=750366800&deviceid=e519062714508114&synckey=1_620916854%7C2_620917963%7C3_620917948%7C201_1388976090%7C1000_1388967977&_=1388976119078

https://webpush.weixin.qq.com/cgi-bin/mmwebwx-bin/synccheck?callback=jQuery18308660551080269895_1388975862078&r=1388976173375&sid=e75TXbI7TnKUevmI&uin=750366800&deviceid=e519062714508114&synckey=1_620916854%7C2_620917963%7C3_620917948%7C201_1388976090%7C1000_1388967977&_=1388976173390

https://webpush.weixin.qq.com/cgi-bin/mmwebwx-bin/synccheck?callback=jQuery18308660551080269895_1388975862078&r=1388976146265&sid=e75TXbI7TnKUevmI&uin=750366800&deviceid=e519062714508114&synckey=1_620916854%7C2_620917963%7C3_620917948%7C201_1388976090%7C1000_1388967977&_=1388976146265

正常返回结果

window.synccheck={retcode:"0",selector:"0"}

有消息返回结果

window.synccheck={retcode:"0",selector:"6"}

发送消息返回结果

window.synccheck={retcode:"0",selector:"2"}

朋友圈有动态

window.synccheck={retcode:"0",selector:"4"}

获取消息-post-设置Cookie

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxsync?sid=e75TXbI7TnKUevmI&r=1388977398062

{"BaseRequest":{"Uin":750366800,"Sid":"e75TXbI7TnKUevmI"},"SyncKey":{"Count":5,"List":[{"Key":1,"Val":620916854},{"Key":2,"Val":620917978},{"Key":3,"Val":620917975},{"Key":201,"Val":1388977392},{"Key":1000,"Val":1388967977}]},"rr":1388977398062}

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxsync?sid=e75TXbI7TnKUevmI&r=1388977583250

{"BaseRequest":{"Uin":750366800,"Sid":"e75TXbI7TnKUevmI"},"SyncKey":{"Count":5,"List":[{"Key":1,"Val":620916854},{"Key":2,"Val":620917980},{"Key":3,"Val":620917975},{"Key":201,"Val":1388977400},{"Key":1000,"Val":1388967977}]},"rr":1388977583250}

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxsync?sid=e75TXbI7TnKUevmI&r=1388977660750

{"BaseRequest":{"Uin":750366800,"Sid":"e75TXbI7TnKUevmI"},"SyncKey":{"Count":5,"List":[{"Key":1,"Val":620916854},{"Key":2,"Val":620917982},{"Key":3,"Val":620917975},{"Key":201,"Val":1388977585},{"Key":1000,"Val":1388967977}]},"rr":1388977660750}

post 发送消息

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxsendmsg?sid=e75TXbI7TnKUevmI&r=1388977830140

{"BaseRequest":{"Uin":750366800,"Sid":"e75TXbI7TnKUevmI","Skey":"D6EBA5FA425CAE258F24E75CF51F2E1B4EEA9C5338BE456C","DeviceID":"e519062714508114"},"Msg":{"FromUserName":"langyeie","ToUserName":"pp80000","Type":1,"Content":"55","ClientMsgId":1388977830140,"LocalID":1388977830140}}

https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxsync?sid=e75TXbI7TnKUevmI&r=1388977830390

{"BaseRequest":{"Uin":750366800,"Sid":"e75TXbI7TnKUevmI"},"SyncKey":{"Count":5,"List":[{"Key":1,"Val":620916854},{"Key":2,"Val":620917986},{"Key":3,"Val":620917975},{"Key":201,"Val":1388977776},{"Key":1000,"Val":1388967977}]},"rr":1388977830390}

get 有消息来，响铃

https://res.wx.qq.com/zh_CN/htmledition/swf/msg17ced3.mp3

原文地址：http://www.langyeweb.com/Program/70.html，转载请保留出处。
