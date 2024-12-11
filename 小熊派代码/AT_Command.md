# 星闪链路建立逻辑
*（每条指令都要检测是否返回OK）*
1. 两端首先使用AT+SLEENABLE使能

2. G节点使用
|AT+SLESETADVPAR=<announce_handle>,<announce_mode>,<announce_interval_min>,<announce_interval_max>,<own_addr _type>,<own_addr_addr>,<peer_addr_type>,<peer_addr_addr>|
|-----|
<announce_handle>：设备公开句柄，取值范围[0, 0x10]
<announce_mode>：设备公开类型
<announce_interval_min>：最小设备公开周期, 0x000020~0xffffff, 单位125us
<announce_interval_max>：最大设备公开周期, 0x000020~0xffffff, 单位125us
<own_addr_type>：SLE本端地址类型，取值范围：0：公有地址。6：随机地址
<own_addr_addr>：SLE本端设备地址
<peer_addr_type>：SLE对端设备地址类型取值：0 - 公有地址,  6 - 随机地址
<peer_addr_addr>：SLE对端设备地址

同时使用设置命令
|AT+SLESETADVDATA=<adv_handle>,<announce_data_len >,<seek_rsp_data_len>,<announce_data>,<seek_rsp_data>|
|----|
<adv_handle>：广播handle，取值范围[0, 0x10]
<announce_data_len>：设备公开数据长度
<seek_rsp_data_len>：扫描响应数据长度
<announce_data>：设备公开数据(hex类型字符串，最大长度521个字符) 
<seek_rsp_data>：扫描响应数据(hex类型字符串，最大长度521个字符)

|AT+SLESETSCANPAR=<scan_type>,<scan_interval>,<scan_w indow>|
|---|
<scan_type>：扫描类型。0：被动扫描；1：主动扫描
<scan_interval>：扫描间隔。取值范围[0x14, 0xFFFF] ,单位125 μs 
<scan_window>：扫描窗口。取值范围[0x14, 0xFFFF] ,单位125 μs 


设置完成后启动广播
AT+SLESTARTADV=<adv_enable>
并使能扫描
AT+SLESTARTSCAN

3. T节点使用
|AT+SLESETNAME=<len>,<name>|
|---|
<len>:name长度<name>：名字

|AT+SLESETADDR=<addr_type>,<addr>|
|---|
<addr_type>：地址类型<addr>：地址

这两个AT指令设置本端参数，注意和G节点设置要扫描的参数一致

4. G节点检测到T节点后用
|AT+SLECONN=<sle_addr_type>,<sle_addr>|
|---|
< sle_addr_type >：SLE设备地址类型取值范围如下：0：公有地址；6：随机地址。<sle_addr>：SLE设备地址

来进行连接

5. 数据传输完后可由T节点主动断开连接，使用
|AT+SLEDISCONN=<sle_addr_type>，<sle_addr>|
|---|
< sle_addr_type >：SLE设备地址类型。取值范围如下：
0：公有地址；
6：随机地址。
<sle_addr>：SLE设备地址。

来断开连接

6. 两设备可使用
|AT+SLECONNPARUPD=<conn_id>,<interval_min>,<interval_ma x>,<max_latency>,<supervision_timeout>|
|---|
<conn_id>：连接ID
<interval_min>：链路调度最小间隔，取值范围[0x0002, 
0x32000]，单位125μs 
<interval_max>：链路调度最大间隔，取值范围[0x0002, 
0x32000]，单位125μs 
<max_latency>：延迟周期，单位slot(该值表示在设置值的周期内可以不回复, 为0时则表示每包都需回复) 
<supervision_timeout>：超时时间，单位10ms

来进行通信参数的设置