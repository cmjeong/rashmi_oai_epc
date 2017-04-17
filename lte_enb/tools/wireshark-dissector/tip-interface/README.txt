Instructions to use tip.lua:

1. wireshark version > 1.10.10
2. lua version >= 5.1
3. Make sure wireshark is built with lua. 
   Lua support can be checked at Wireshark->Help->About.
4. If wireshark is built without lua, run the following command during wireshark installation:
   ./configure--with-lua
   make
   make install
5. load tip.lua in /usr/local/share/wireshark
6. Edit init.lua at /usr/local/share/wireshark to set following params:
   a. disable_lua = false
   b. run_user_scripts_when_superuser = true
7. Edit tip.lua for required ports. At the end of tip.lua, add the desired
   port to the DissectorTable.
   Ex: if you want to capture msgs on port number 6789, add below line:
   DissectorTable.get("udp.port"):add(6789,TIP)
8. Run wireshark with command:
   wireshark -X lua_script:tip.lua
9. Select interface as "any" and start the capture
10. filter for protocol name "tip"
