# Streaming Server

This is a simple multithreaded streaming server created as a personal coding project mostly from scratch (not relying too much on other tools/apis). It will only support streaming movies (probably as mp4 h264) and audio (probably as mp3 aac). 

Content to stream is to be stored in the media folder following a specific naming convention as seen in media_id.txt and defines.h. 

defines.h contains some important parameters for customizing the server, currently it is setup to run on a four core laptop. 

server.c contains the code for the server relying only on socket programming.

The client will first be developed as an android app as a later project.

