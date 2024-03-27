# Network Transcription (recommended mode)
Aside from being useful for Linux systems that do not have the power to transcribe speech efficiently, this mode also shows speedup of local transcription on faster machines which run a whisper.cpp server on localhost. See below.

### Setup
Speech is recorded on the local machine and sent via an API call, to a whisper.cpp [server](https://github.com/ggerganov/whisper.cpp/tree/master/examples/server), typically on the local network or at localhost (127.0.0.1).

* To make BlahST work in network transcription mode, one should use the `wsi` script with `-n` flag when setting up keyboard shortcuts for speech input.

* **wsi** can be found in this repository and should be placed in $HOME/.local/bin. 

* The IP/hostname and port number for the server should be entered in the configuration block of the script.

* The script will check that a running server is present at the specified IP or hostname and complain if not found. To properly set up the server, please, look at its [documentation](https://github.com/ggerganov/whisper.cpp/tree/master/examples/server)

* Please, run the script from the command line first to check for its dependencies and have them installed.

When **wsi** is properly set up, BlahST will work the same way as with local instance of whisper.cpp. Likely faster.


## Signifficant Speedup
### ... when running a local whisper.cpp server (on the same machine or LAN) versus using main executable

This expands on a previous observation / [comment](https://github.com/ggerganov/whisper.cpp/discussions/1706#discussioncomment-8559750):

Before, I was getting ~30x-faster-than-realtime transcription with a local whisper.cpp (**main** executable) instance that was loading the model file on each call instead of keeping it loaded in memory.
Take a look at the transcription speed when a call to a local whisper.cpp **server** instance is made (excluding the time for speech input, the curl call (transcription) takes the bulk of the time in my tools, so its timing is the largest contributor to speed of transcription ):

The first screenshot shows that the server instance (on localhost) is processing a 12.5 second speech clip, using 8 threads and assisted by GPU with CUDA:

![Screenshot from 2024-02-22 11-55-52](https://github.com/QuantiusBenignus/blurt/assets/120202899/0e601ea2-9743-42e3-b7b5-f1cd0ca96351)


And the request itself (timed to stderr with curl itself, tcurl is just a shell function wrapper to curl with timing feedback turned on) shows ~140 ms of total transcription time:

![Screenshot from 2024-02-22 11-58-06](https://github.com/QuantiusBenignus/blurt/assets/120202899/6f0b352a-b8dd-424d-a3e9-9727dd4ba4eb)


This is almost **90x-faster-than-real-time** (~140 ms for a 12.5s speech clip). Loading the model takes about 110 ms for the "main" executable, which does not account for this big difference (3 times).
Seems like there is extra advantage to running a local server with the model preloaded.

Seeing this consistently, I would recommend using this **client - server** mode of operation with BlahST. 
Just use the netwrsi script, which makes a call to whisper.cpp **server** (server should be compiled along with main in your whisper.cpp repo).
The server instance must be started on login (on a local machine) or otherwise available on your LAN. 

##### Caveats:

1. System SUSPEND while server is running. 
   - If the server is running for a long time and the system enters in SUSPEND mode (if enabled), it seems, the CUDA kernel memory is freed. Then on API call (after RESUME), the server exits abnormally and has to be restarted (see this [issue](https://github.com/ggerganov/whisper.cpp/issues/1991#issue-2204120607) for description).  
   - After return from SUSPEND, running the server and other generative AI models (e.g. Stable Diffusion) may result in a run without CUDA support (as the GPU is reported to be busy and unavailable). This could be a serious trade-off. There is a solution as described [here](https://askubuntu.com/questions/1228423/how-do-i-fix-cuda-breaking-after-suspend) for example. 
---
⚠️Warning: 
Calling the whisper.cpp server over the open internet may not be a good idea, since, not only the latency will increase but, among other security factors, there is no encryption of the speech data and the server implementation does not sanitize the calls in any way.

An example for setting up the server with the desired model and other runtime parameters is available [here](https://github.com/ggerganov/whisper.cpp/tree/master/examples/server)
