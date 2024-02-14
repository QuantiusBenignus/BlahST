# cliblurt
Input text from speech anywhere with GNOME keyboard shortcuts

The inspiration for this little tool came from [Blurt](https://github.com/QuantiusBenignus/blurt/). 
A simple GNOME extension that can input text from speech into any window with an ediatble text field.
If you liked Blurt for its power vs simplicity ratio, you will love this.
The work is, again, done by the *wsi* script, which is a toned-down version of [NoteWhispers](https://github.com/QuantiusBenignus/notewhispers/).
The actuall heavy lifting is performed by whisper.cpp which must be precompiled on your Linux system as described in [Blurt](https://github.com/QuantiusBenignus/blurt/).

The idea here is to not even write an extension like blurt. Just use a pair of hotkeys to start and stop recording from the microphone and send the recorded speech to whisper.cpp

### Setup
Please, read the setup for [Blurt](https://github.com/QuantiusBenignus/blurt/) up to the point of downloading the GNOME extension (which we do not need here).

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
