# BlahST
**Blah** **S**peech-to-**T**ext lets you have a bla(h)st inputing text from speech on Linux, with keyboard shortcuts and whisper.cpp. Fire up your microphone and perform high-quality, multilingual speech recognition offline.

**BlahST is probably the leanest Whisper-based speech-to-text input tool for Linux, sitting on top of whisper.cpp.** 

- **Now with the option to send audio to a whisper.cpp server for even faster [network transcription.](./API_TRANSCRIBE.md)**
- **Now able to select language and translate from the command line with the dedicated `wsiml` script**

Using low-resource, optimized command-line tools, spoken text input happens very fast. Here is a demostration video:

https://github.com/QuantiusBenignus/cliblurt/assets/120202899/e4cd3e39-6dd3-421b-9550-4c428a5a8f0a

### Principle of operation
The work is done by the *wsi* (*wsiml* for multilingual users) script, similar to the one in [Blurt](https://github.com/QuantiusBenignus/blurt/) - a simple GNOME extension for speech-to-text input.
Speech recognition is performed by whisper.cpp which must be precompiled on your Linux system or available as a [server](https://github.com/ggerganov/whisper.cpp/tree/master/examples/server) instance on your LAN or localhost.
The idea here is to not even write an extension like Blurt. Just use a pair of hotkeys to start and stop recording from the microphone and send the recorded speech to whisper.cpp which dumps transcribed text into the clipboard. An universal approach that should work in most Linux desktop environments and distributions.

When speech input is initiated with a hotkey, a microphone indicator appears in the top bar (at least in GNOME) and is shown for the duration of the recording (can be interupted with another hotkey).
The disappearance of the microphone icon from the top bar indicates completion and the transcribed text can be pasted from the clipboard. On slower systems there may be a slight delay after the microphone icon disappears and before the text reaches the clipboard due to longer transcription time. On my computer, via the whisper.cpp server API, it is less than 150 ms (300 ms with local whisper.cpp) for an average paragraph of spoken text.

For keyboard-only operation, with the standard `CTRL+V` for example, the standard clipboard will be used under X11 and Wayland (`wsi -c` or `wsiml -c`), while `wsi` (or `wsiml`) uses the PRIMARY sellection and text is pasted with the middle mouse button). For left-hand paste, speech recording can be relegated to hotkeys triggered with the right hand. For example I have setup the unused "+" and "Insert" keys on the numeric keypad. 

---

### SYSTEM SETUP

#### PREREQUISITES:
- zsh or bash command line shell installation on a Linux system running any modern desktop environment.   
- working [whisper.cpp installation](https://github.com/ggerganov/whisper.cpp) or a listening whisper.cpp server on your LAN/localhost (see network-transcription [section](./API_TRANSCRIBE.md))
- The orchestrator tool **wsi** or **wsiml** from this repository **must be placed in your $HOME/.local/bin/ folder or elsewhere in your $PATH** (The installation script `install-wsi` handles most of these).  
- recent versions of 'sox', 'xsel' (or 'wl-copy' on Wayland) command-line tools from your system's repositories.
-  A working microphone 
> *DISCLAIMER: The author neither takes credit nor assumes any responsibility for any outcome that may or may not result from interacting with the contents of this document. The proposed actions and automations (e.g. installation locations etc.) are merely suggestions and are based on the author's choice and opinion. As they may not fit the taste or the particular situation of everyone, please, adjust as needed.*

#### INSTALLATION
<details>
<summary>USING THE INSTALLATION SCRIPT</summary>
Run the script `install-wsi` from the folder of the cloned repository and follow the prompts. It will move the script and make it executable, create a link to whisper.cpp `main` executable, set the environment, set a default whisper.cpp model, check for dependencies and request their installation if missing, etc.
The installation script also handles setup for network transcription, but the IP and port for the whisper.cpp server must be set manually in `wsi` or `wsiml`
Run the script `wsi` or `wsiml` directly from the command line first to verify its proper operation. Later it will be invoked only with [hotkeys](https://github.com/QuantiusBenignus/BlahST/#gui-setup-of-hotkeys) for speed and convenience.
</details>
<details>
<summary>MANUAL INSTALLATION</summary>

*(Assuming whisper.cpp is installed and the "main" executable compiled with 'make' in the cloned whisper.cpp repo. See Prerequisites section)*
* Place the script **wsi** and/or **wsiml** in $HOME/.local/bin/
* Make it executable
  ```
  cd $HOME/.local/bin; chmod +x wsi
  ```
* Run once from the command line to let the script check for required dependencies
* If using local whisper.cpp, create a symbolic link (the code expects 'transcribe' in your $PATH) to the compiled "main" executable in the whisper.cpp directory.
  For example, create it in your `$HOME/.local/bin/` (part of your $PATH) with 
```
ln -s /full/path/to/whisper.cpp/main $HOME/.local/bin/transcribe
```
If transcribe is not in your $PATH, either edit the call to it in **wsi** to include the absolute path, or add its location to the $PATH variable. Otherwise the script will fail.
</details>
 
#### CONFIGURATION
##### For manual installation only:
Inside the `wsi` or `wsiml` script, near the begining, there is a clearly marked section, named **"USER CONFIGURATION BLOCK"**, where all the user-configurable variables (described in the following section) have been collected. 
Most can be left as is but the important one is the location of the whisper.cpp model file that you would like to use during transcription (or the IP and port number for the whisper.cpp server)

##### GUI SETUP OF HOTKEYS
To start and stop speech input, for both manual and automatic installation
<details>
<summary> CASE 1: GNOME</summary>

##### Hotkey to start recording of speech
* Open your GNOME system settings and find "Keyboard".
* Under "Keyboard shortcuts", "View and customize shortcuts"
* In the new window, scroll down to "Custom Shortcuts" and press it.
* Press "+" to add a new shortcut and give it a name: "Start Recording Speech"
* In the "Command" field type `/home/yourusername/.local/bin/wsi` for using the middle mouse button or change it to `.../wsi -c` for using the clipboard.
* (For users of the multi-lingual models, replace `wsi` above with `wsiml`)
* Then press "Set Shortcut" and select a (unused) key combination. For example CTRL+ALT+a
* Click Add and you are done. 

The orchestrator script has a silence detection filter in the call to sox (rec) and would stop recording (in the best case) on 2 seconds of silence.
In addition, if one does not want wait or has issues with the silence detection threshold:

##### Manual speech recording interuption
For those who want to be able to interupt the recording manually with a key combination, in the spirit of great hacks, we are going to use the system built-in features:
* Open your GNOME system settings and again, find "Keyboard".
* Under "Keyboard shortcuts", "View and customize shortcuts"
* In the new window, scroll down to "Custom Shortcuts" and press it.
* Press "+" to add a new shortcut and give it a name: "Interupt Speech Input!"
* In the "Command" field type `pkill --signal 2 rec`
* Then press "Set Shortcut" and select a (unused) key combination. For example CTRL+ALT+x
* Click Add and you are done.
  
That Simple.  Just make sure that the new key binding has not been set-up already for something else.
Now when the script is recording speech, it can be stopped with the new key combo and transcription will start immediatelly.
</details>

<details>
<summary> CASE 2: XFCE4</summary>
This is simalr to the GNOME setup above (for reference, see its more detailed instructions) 
  
* Open the Xfce4 Settings Manager.
* Navigate to Keyboard → Application Shortcuts.
* Click on the Add button to create a new shortcut.
* Enter the name of the shortcut and the command e.g. `/home/yourusername/.local/bin/wsi`  or `.../wsi -c` for using the clipboard.
* (For users of the multi-lingual models, replace `wsi` above with `wsiml`)
* Press the keys you wish to assign to the shortcut.
* Click OK to save the shortcut.
 The hotkey to stop speech recording should be done similarly with `pkill --signal 2 rec`.
</details>

<details>
<summary> 
CASE 3: KDE (Plasma)
</summary>
This is similar to the GNOME setup above (for reference, see its more detailed instructions)
  
* Open the System Settings application.
* Navigate to Shortcuts and then Custom Shortcuts.
* Click on Edit and then New to create a new group for your shortcuts if needed.
* Under the newly created group, click on New again and select Global Shortcut -> Command/URL.
* Give your new shortcut a name.
* Choose the desired shortcut key combination by clicking on the button next to "None" and pressing the keys you want to assign to the shortcut.
* In the Trigger tab, specify the command to be executed when the shortcut is triggered. e.g. `/home/yourusername/.local/bin/wsi` or `.../wsi -c`
* (For users of the multi-lingual models, replace `wsi` above with `wsiml`)
* Ensure that the Enabled checkbox is checked to activate the shortcut.
* Apply the changes by clicking Apply or OK.
The hotkey to stop speech recording should be done similarly with `pkill --signal 2 rec`. 
</details>

Please, note that there may be slight variations in the above steps depending on the version installed on your system.
For many other environements, such as **Mate, Cinnamon, LXQt, Deepin**, etc. the steps should be somewhat similar to the examples above.
Please, consult the documentation for your systems desktop environment.
#### TO DO
- [x] POSIX compliant installation script
- [ ] POSIX compliant orchestration scripts

#### SUMMARY
* On the press of a hotkey combo, the `wsi` script will record speech (stopped with a hotkey or by silence detection), use a local copy of whisper.cpp and send the transcribed text to the PRIMARY selection under, either X11 or Wayland.
Then all one has to do is paste it with the middle mouse button anywhere they want. (For people holding the mouse with their right hand, speech recording hotkeys for the left hand would make sense.) 

* If using `wsi -c` (the approaches can coexist, just set up different set of hotkeys), the transcribed text is sent to the clipboard (not PRIMARY selection) under, either X11 or Wayland.
Then pasting happens with the `CTRL+V` (`CTRL+SHIFT+V` for GNOME terminal) or `SHIFT+INSert` keys as usual. (For most people, right-hand hotkeys would work well.)

* If transcribing over the network with `wsi -n -c` (selected with a hotkey of its own), the script will attempt to send the recorded audio to a running, properly set whisper.cpp server (on the LAN or `localhost`).
  It will then collect the textual response and format it for pasting with the `CTRL+V` (`CTRL+SHIFT+V` for GNOME terminal) or `SHIFT+INSert` keys (to paste with the middle mouse button use `wsi -n` instead).
  
* For multilinuag users, in addition to the features of wsi, `wsiml` provides the ability to specify a language, e.g. `-l fr` and the option to translate to english with `-t`.  
---

<details>
  <summary>TIPS AND TRICKS</summary>
Sox is recording in wav format at 16k rate, the only currently accepted by whisper.cpp. This is done in **wsi** with this command:
`rec -t wav $ramf rate 16k silence 1 0.1 3% 1 2.0 6% `
It will attempt to stop on silence of 2s with signal level threshold of 6%. A very noisy environment will prevent the detection of silence and the recording (of noise) will continue. This is a problem and a remedy that may not work in all cases is to adjust the duration and silence threshold in the sox filter in the `wsi` script. Of course, one can use the manual interuption method if preferred.

We can't raise the threshold arbitrarily because, if one consistently lowers their voice (fadeout) at the end of speech, it may get cut off if the threshold is high. Lower it in that case to a few %.    
It is best to try to make the speech distinguishable from noise by amplitude (speak clearly, close to the microphone), while minimizing external noise (sheltered location of the microphone, noise canceling hardware etc.)
With good speech signal level, the threshold can then be more effective, since SNR (speech-to-noise ratio:-) is effectively increased. 

After the speech is captured, it will be passed to `transcribe` (whisper.cpp) for speech recognition. This will happen faster than real time (especially with a fast CPU or if your whisper.cpp installation uses CUDA). One can adjust the number of processing threads used by adding  `-t n` to the command line parameters of transcribe (please, see whisper.cpp documentation). 
The script will then parse the text to remove non-speech artifacts, format it and send it to the PRIMARY selection (clipboard) using either X11 or Wayland tools. 

In principle, whisper (whisper.cpp) **is multilingual** and with the correct model file, this extension will "blurt" out UTF-8 text transcribed in the correct language. In the wsi script, the language choice can be made permanent by using `-l LC` in the `transcribe` call, where LC stands for the language code of choice, for example `-l fr` for french. 

##### Temporary directory and files
Speech-to-text transcription is memory- and CPU-intensive task and fast storage for read and write access can only help. That is why **wsi** stores temporary and resource files in memory, for speed and to reduce SSD/HDD "grinding": `TEMPD='/dev/shm'`. 
This mount point of type "tmpfs" is created in RAM (let's assume that you have enough, say, at least 8GB) and is made available by the kernel for user-space applications. When the computer is shut down it is automatically wiped out, which is fine since we do not need the intermediate files.
In fact, for some types of applications (looking at you Electron), it would be beneficial (IMHO) to have the systemwide /tmp mount point also kept in RAM. Moving /tmp to RAM may speed up application startup a bit. A welcome speedup for any Electron app. In its simplest form, this transition is easy, just run:

`echo "tmpfs /tmp tmpfs rw,nosuid,nodev" | sudo tee -a /etc/fstab`
and then restart your Linux computer.
For the aforementioned reasons, especially if HDD is the main storage media, one can also move the ASR model files needed by whisper.cpp in the same location (/dev/shm). These are large files, that can be transferred to this location at the start of a terminal session (or at system startup). This can be done using your `.profile` file by placing something like this in it: 
```
([ -f /dev/shm/ggml-base.en.bin ] || cp /path/to/your/local/whisper.cpp/models/ggml* /dev/shm/)
```
</details>

---

#### Credits
* Open AI (for [Whisper](https://github.com/openai/whisper))
* Georgi Gerganov and community ( for Whisper's C/C++ port [whisper.cpp](https://github.com/ggerganov/whisper.cpp))
* The **sox** developers (for the venerable "Swiss Army knife of sound processing tools")
* The creators and maintainers of CLI utilities such as **xsel, wl-copy, curl, jq** and others that make the Linux environment (CLI and GUI) such a powerful paradigm.
