以下是与STA启动、DHCP使能、连接到网络、创建UDP连接、发送UDP数据、断开IP连接和断开STA相关的AT指令：

1. **启动STA（Station Mode）**:
   - AT指令：`AT+STARTSTA`
   - 示例：`AT+STARTSTA`

2. **连接到网络**:
   - AT指令：`AT+CONN=<ssid>[,<bssid>,<passwd>][,<psk_type>]`
   - 示例：`AT+CONN="SSID_NAME",,"PASSWORD"`
   - 注意：替换`"SSID_NAME"`和`"PASSWORD"`为目标网络的SSID（网络名称）和密码（没有的话可以缺省）。

3. **DHCP使能**:
   - AT指令：`AT+DHCP=<wlan_if>,<stat>`
   - 示例：`AT+DHCP=wlan0,1`

4. **创建UDP连接**:
   - AT指令：`AT+IPSTART=<link_ID>,<IP_protocol>,<local_port>`
   - 示例：`AT+IPSTART=0,udp,5001`
    **创建本地端口为5001的udp客户端，占用socket0**

5. **发送UDP数据**:
   - AT指令：`AT+IPSEND=<link_ID>,<len>,<remote_IP>,<remote_port>,<string>`
   - 示例：`AT+IPSEND=0,9,192.168.3.1,5001,data test`
    **向192.168.3.1地址的5001端口发送9字节长度的数据data test**

6. **断开IP连接**:
   - AT指令：`AT+IPCLOSE=<link_ID>`
   - 示例：`AT+IPCLOSE=0`
    **关闭端口为0的socket**

7. **断开STA连接**:
   - AT指令：`AT+STOPSTA`
   - 示例：`AT+STOPSTA`


### 可选

**配置重连策略**:
   - AT指令：`AT+RECONN=<enable>[,<period>,<count>[,<timeout>]]`
   - 示例：`AT+RECONN=1,10,3600,50`
   - 参数说明：
     - `<enable>`：重连使能。
        - 0：不执行重连；
        - 1：执行重连。
     - `<period>`：重连间隔周期，单位为秒，取值范围：1～65535。
     - `<count>`：重连最大次数，取值范围：1～65535。
     - `<timeout>`：单次重连超时时间，取值范围：2~65535，默认 2，当取值为 65535 时，表示无限次循环重连。

这条指令用于配置模块的自动重连策略，包括是否启用重连、重连的时间间隔、最大重连次数以及单次重连的超时时间。通过设置这些参数，模块可以在失去连接后尝试自动重新连接到网络。
