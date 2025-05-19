# Multilingual Interactive Speech Chat with **blahstbot**

## Overview
To expand the lean and performant [**BlahST**](https://github.com/QuantiusBenignus/BlahST) into a snappy, UI-less platform for natural, spoken interaction with LLMs, the tool **blahstbot** has been added.
This tool leverages whisper.cpp for Automatic Speech Recognition (ASR), LLM text interaction using llama.cpp and Piper Text-to-Speech (TTS) to create a seamless interactive speech chat experience across multiple languages.

Would you like to hear Gemma3 speaking like multiple polyglots in the same conversation? Here is an example (unmute audio please):

## Languages Supported
- All languages available in the [Piper repository](https://github.com/rhasspy/piper/blob/master/VOICES.md)
- English default.
- Languages are added/configured in `blahst.cfg` as elements of an associative array, with keys that must conform to the ISO 639-1 standard, e.g. 'FR', 'DE', 'PT', etc.

## Features

* **Real-time speech intertaction**
* **Multilingual support**
* **LLM-powered conversation**
* **Fast, yet natural-sounding speech synthesis**

## Usage

Set a new hotkey to start `blahstbot -n` (for llama-server use) and reuse the main "STOP-RECORDING" hotkey of BlahST at the end of your speech. 
The bot will answer promptly and provide the question and answer as text to be pasted or autopasted (if configured). 

## Technologies Used
- Automatic Speech Recognition (ASR) - [whisper.cpp](https://github.com/ggml-org/whisper.cpp)
- Large Language Model (LLM) - [Gemma3-12B preset](https://huggingface.co/google/gemma-3-12b-it-qat-q4_0-gguf), can be replaced with others depending on system hardware and user needs.
- Text-to-Speech (TTS) - [Piper](https://github.com/rhasspy/piper)
- Text parser and low-overhead workflow orchestrator - [zsh](https://www.zsh.org/)
