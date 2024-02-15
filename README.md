# cliblurt
Input text from speech anywhere with GNOME keyboard shortcuts and whisper.cpp

The inspiration for this little tool came from [Blurt](https://github.com/QuantiusBenignus/blurt/). 
A simple GNOME extension that can input text from speech into any window with an editable text field.
If you liked Blurt for its power vs simplicity ratio, you will love this.
The work is, again, done by the *wsi* script, which is a toned-down version of [NoteWhispers](https://github.com/QuantiusBenignus/notewhispers/).
The actuall heavy lifting is performed by whisper.cpp which must be precompiled on your Linux system as described in [Blurt](https://github.com/QuantiusBenignus/blurt/).
The idea here is to not even write an extension like blurt. Just use a pair of hotkeys to start and stop recording from the microphone and send the recorded speech to whisper.cpp

When speech input is initiated, a microphone indicator icon appears in the top bar and is shown for the duration of the recording.
The disappearance of the microphone icon from the top bar indicates that the process is completed and **wsi** has "blurted" a snippet of text that can be pasted with the middle mouse button. (Note that on slower systems there may be a slight delay after the microphone icon disappears and before the text reaches the clipboard due to the time needed for transcription. On my computer it is less than 300 ms for an average paragraph of spoken text).

### SYSTEM SETUP

#### PREREQUISITES:
- zsh or bash command line shell installation on a Linux system running GNOME.   
- working whisper.cpp installation (see https://github.com/ggerganov/whisper.cpp
- The orchestrator tool **wsi** from this repository **must be placed in your $HOME/.local/bin/ folder**.  
- recent versions of 'sox', 'xsel' or 'wl-copy'  command-line tools from your system's repositories.
-  A working microphone 
> *DISCLAIMER: Some of the proposed actions, if implemented, will alter how your system works internally (e.g. systemwide temporary file storage and memory management). The author neither takes credit nor assumes any responsibility for any outcome that may or may not result from interacting with the contents of this document. Suggestions in this section are based on the author's choice and opinion and may not fit the taste or the particular situation of everyone; please, adjust as you like.*

#### "INSTALLATION"
*(Assuming whisper.cpp is installed and the "main" executable compiled with 'make' in the cloned whisper.cpp repo. See Prerequisites section)*
* Place the script **wsi** in $HOME/.local/bin/  ( **It is advisable to run this script once from the command line to let it check for its dependencies** )
* Create a symbolic link (the code expects 'transcribe' in your $PATH) to the compiled "main" executable in the whisper.cpp directory. For example, create it in your `$HOME/.local/bin/` (part of your $PATH) with 
```
ln -s /full/path/to/whisper.cpp/main $HOME/.local/bin/transcribe
```
If transcribe is not in your $PATH, either edit the call to it in **wsi** to include the absolute path, or add its location to the $PATH variable. Otherwise the script will fail.
 
#### CONFIGURATION
Inside the **wsi** script, near the begining, there is a clearly marked section, named **"USER CONFIGURATION BLOCK"**, where all the user-configurable variables (described in the following section) have been collected. 
Most can be left as is but the important one is the location of the whisper.cpp model file that you would like to use during transcription.

###### Hotkey to start recording of speech
* Open your GNOME system settings and find "Keyboard".
* Under "Keyboard shortcuts", "View and customize shortcuts"
* In the new window, scroll down to "Custom Shortcuts" and press it.
* Press "+" to add a new shortcut and give it a name: "Start recording speech"
* In the "Command" field type `/home/yourusername/.local/wsi`
* Then press "Set Shortcut" and select a (unused) key combination. For example CTRL+ALT+a
* Click Add and you are done. 

The **wsi** script has a silence detection filter in the call to sox (rec) and would stop recording (in the best case) on 2 seconds of silence.

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

The `wsi` script will take care of sending the transcribed text to the PRIMARY selection / clipboard under, either X11 or Wayland.
Then all one has to do is paste it with the middle mouse button anywhere they want. 
