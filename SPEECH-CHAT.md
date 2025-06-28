# Multilingual Interactive Speech Chat with **blahstbot**

## Overview
To expand the lean and performant [**BlahST**](https://github.com/QuantiusBenignus/BlahST) into a snappy, UI-less platform for natural, spoken interaction with LLMs, the tool **blahstbot** has been added.
This tool leverages whisper.cpp for Automatic Speech Recognition (ASR), LLM text interaction using llama.cpp and Piper Text-to-Speech (TTS) to create a seamless interactive speech chat experience across multiple languages.
The text of the conversation can be pasted optionally and selectively, or automatically in any editable text field in the desktop. 
Would you like to hear Gemma3 speaking like multiple polyglots in the same conversation? Here is an example (unmute audio please):



https://github.com/user-attachments/assets/b9f1aec4-e293-46a3-9c9b-45d5e05c66f4
_A conversation (speech to speech chat) where the answers and statements of the same LLM are spoken in various languages, by different TTS models and voices, selected automatically._ 

## Features

* **Real-time speech intertaction**
* **Multilingual support**
* **LLM-powered conversation**
* **Fast, yet natural-sounding speech synthesis**
* **NEW: Append context to questions spoken in turn by simply selecting any text in any window with the mouse. Even speeking is optional.**

## Setup
Aside from configuring **Blahst** as described in the main [README.md](README.md), one needs to download the .onnx and .json files for each desired TTS language from the [Piper](https://github.com/rhasspy/piper) GitHub repo and place the in `$AI/piper` subfolder (see `blahst.cfg`)
Several languages are preconfigured in blahst.cfg and the availability of at least some of those files in `$AI/piper` will be required.
Adding new model files should be done in `blahst.cfg` in similar fashion.

## Languages Supported
- All languages available in the [Piper repository](https://github.com/rhasspy/piper/blob/master/VOICES.md)
- English default.
- Languages are added/configured in `blahst.cfg` as elements of an associative array, with keys that must conform to the ISO 639-1 standard, e.g. 'FR', 'DE', 'PT', etc.

## Usage
Set a new hotkey to start `blahstbot -n` (for llama-server use) and reuse the main "STOP-RECORDING" hotkey of BlahST at the end of your speech. 
The bot will answer promptly and provide the question and answer as text to be pasted or autopasted (if configured). 

## Technologies Used
- Automatic Speech Recognition (ASR) - [whisper.cpp](https://github.com/ggml-org/whisper.cpp)
- Large Language Model (LLM) - [Gemma3-12B preset](https://huggingface.co/google/gemma-3-12b-it-qat-q4_0-gguf), can be replaced with others depending on system hardware and user needs.
- Text-to-Speech (TTS) - [Piper](https://github.com/rhasspy/piper)
- Text parser and low-overhead workflow orchestrator - [zsh](https://www.zsh.org/) Outperforms languages like Python by a lot with its direct execution of pipelined command-line tools. 
