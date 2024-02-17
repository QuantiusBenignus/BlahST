# BlahST
**Blah** **S**peech-to-**T**ext will let you have a blahst pasting text from speech on Linux, with keyboard shortcuts and whisper.cpp

The inspiration for this little tool came from [Blurt](https://github.com/QuantiusBenignus/blurt/). 
A simple GNOME extension that can input text from speech into any window with an editable text field.
If you liked Blurt for its power vs simplicity ratio, you will love this. 

**This is probably the leanest Whisper-based speech-to-text input tool for Linux, sitting on top of the lean and mean whisper.cpp**

The work is, again, done by the *wsi* script, which is a toned-down version of [NoteWhispers](https://github.com/QuantiusBenignus/notewhispers/).
The actuall heavy lifting is performed by whisper.cpp which must be precompiled on your Linux system as described in [Blurt](https://github.com/QuantiusBenignus/blurt/).
The idea here is to not even write an extension like blurt. Just use a pair of hotkeys to start and stop recording from the microphone and send the recorded speech to whisper.cpp

When speech input is initiated, a microphone indicator icon appears in the top bar and is shown for the duration of the recording.
The disappearance of the microphone icon from the top bar indicates that the process is completed and **wsi** has "blurted" a snippet of text that can be pasted with the middle mouse button. (Note that on slower systems there may be a slight delay after the microphone icon disappears and before the text reaches the clipboard due to the time needed for transcription. On my computer it is less than 300 ms for an average paragraph of spoken text).

If one fancies keyboard-only operation and wants to paste with the standard `CTRL+V` for example, then they can use the `wrsi` script (instead of **wsi**), which uses the standard clipboard under X11 and Wayland (not the PRIMARY sellection).
In this case, it is advisable to relegate the speech recording to hotkeys triggered with the right hand. For example I have setup the "+" and "Insert" keys on the numeric keypad since I do not use it.
Then pasting happens very fast with the left hand. Here is a demostration video:


https://github.com/QuantiusBenignus/cliblurt/assets/120202899/e4cd3e39-6dd3-421b-9550-4c428a5a8f0a


### SYSTEM SETUP

#### PREREQUISITES:
- zsh or bash command line shell installation on a Linux system running GNOME.   
- working [whisper.cpp installation](https://github.com/ggerganov/whisper.cpp)
- The orchestrator tool **wsi** or **wrsi** from this repository **must be placed in your $HOME/.local/bin/ folder or elsewhere in your $PATH**.  
- recent versions of 'sox', 'xsel' or 'wl-copy'  command-line tools from your system's repositories.
-  A working microphone 
> *DISCLAIMER: Some of the proposed actions, if implemented, will alter how your system works internally (e.g. systemwide temporary file storage and memory management). The author neither takes credit nor assumes any responsibility for any outcome that may or may not result from interacting with the contents of this document. Suggestions in this section are based on the author's choice and opinion and may not fit the taste or the particular situation of everyone; please, adjust as you like.*

#### "INSTALLATION"
*(Assuming whisper.cpp is installed and the "main" executable compiled with 'make' in the cloned whisper.cpp repo. See Prerequisites section)*
* Place the scripts **wsi** and **wrsi** in $HOME/.local/bin/ and make them executable `chmod +x` ( **It is advisable to run once from the command line to let it check for its dependencies** )
* Create a symbolic link (the code expects 'transcribe' in your $PATH) to the compiled "main" executable in the whisper.cpp directory. For example, create it in your `$HOME/.local/bin/` (part of your $PATH) with 
```
ln -s /full/path/to/whisper.cpp/main $HOME/.local/bin/transcribe
```
If transcribe is not in your $PATH, either edit the call to it in **wsi** to include the absolute path, or add its location to the $PATH variable. Otherwise the script will fail.
 
#### CONFIGURATION
Inside the **wsi** (or **wrsi**) script, near the begining, there is a clearly marked section, named **"USER CONFIGURATION BLOCK"**, where all the user-configurable variables (described in the following section) have been collected. 
Most can be left as is but the important one is the location of the whisper.cpp model file that you would like to use during transcription.

##### GUI configuration of the hotkeys to start and stop speech input
##### GNOME:
###### Hotkey to start recording of speech
* Open your GNOME system settings and find "Keyboard".
* Under "Keyboard shortcuts", "View and customize shortcuts"
* In the new window, scroll down to "Custom Shortcuts" and press it.
* Press "+" to add a new shortcut and give it a name: "Start recording speech"
* In the "Command" field type `/home/yourusername/.local/bin/wsi`
* Then press "Set Shortcut" and select a (unused) key combination. For example CTRL+ALT+a
* Click Add and you are done. 

The **wsi** (**wrsi**) script has a silence detection filter in the call to sox (rec) and would stop recording (in the best case) on 2 seconds of silence.

In addition, if one does not want wait or has issues with the silence detection threshold:

###### Manual speech recording interuption
For those who want to be able to interupt the recording manually with a key combination, in the spirit of great hacks, we are going to use the system built-in features:
* Open your GNOME system settings and find "Keyboard".
* Under "Keyboard shortcuts", "View and customize shortcuts"
* In the new window, scroll down to "Custom Shortcuts" and press it.
* Press "+" to add a new shortcut and give it a name: "Blurt it already!"
* In the "Command" field type `pkill --signal 2 rec`
* Then press "Set Shortcut" and select a (unused) key combination. For example CTRL+ALT+x
* Click Add and you are done.
  
That Simple.  Just make sure that the new key binding has not been set-up already for something else.
Now when the extension is recording speech, it can be stopped with the new key combo and transcription will start immediatelly.

##### XFCE4:
* Open the Xfce4 Settings Manager.
* Navigate to Keyboard → Application Shortcuts.
* Click on the Add button to create a new shortcut.
* Enter the name of the shortcut and the command e.g. `pkill --signal 2 rec`.
* Press the keys you wish to assign to the shortcut.
* Click OK to save the shortcut.
  
##### KDE (Plasma):
* Open the System Settings application.
* Navigate to Shortcuts and then Custom Shortcuts.
* Click on Edit and then New to create a new group for your shortcuts if needed.
* Under the newly created group, click on New again and select Global Shortcut -> Command/URL.
* Give your new shortcut a name.
* Choose the desired shortcut key combination by clicking on the button next to "None" and pressing the keys you want to assign to the shortcut.
* In the Trigger tab, specify the command or URL that should be executed when the shortcut is triggered.
* Ensure that the Enabled checkbox is checked to activate the shortcut.
* Apply the changes by clicking Apply or OK.

Please, note that there may be slight variations in these steps depending on the version installed on your system.
For many other environements, such as Mate, Cinnamon, LXQt, Deepin, etc. the steps should be somewhat simmilar to the examples above.
Please, consult the documentation for your systems desktop environment.

---
The `wsi` script will take care of sending the transcribed text to the PRIMARY selection under, either X11 or Wayland.
Then all one has to do is paste it with the middle mouse button anywhere they want. 

if using **wrsi** (the two approaches can coexist), the transcribed text is sent to the clipboard under, either X11 or Wayland.
Then pasting it happens with the `CTRL+V` (`CTRL+SHIFT+V` for GNOME terminal) or `SHIFT+INSert` keys as usual.
