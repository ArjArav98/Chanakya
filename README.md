# Contents
* [What is Chanakya?](#what-is-chanakya)
* [Quickstart](#quickstart)
* [Wait, what does 'Chanakya' mean?](#etymology)
* [Tools](#tools)

## What is Chanakya?
**Chanakya is a simple yet completely customisable, scalable and lightweight chatbot.** Based on the AI concept of 'Expert Systems', Chanakya is written wholly from scratch in C++. 

  * When answering questions read from the user, the chatbot accesses a **large knowledge base**, present in its memory, to find the required information. 
  * The chatbot's field of expertise can be decided by ***you***, the developer!
  * By being written in C++ and accessing a local knowledge base, the chatbot is **extremely fast** and versatile.
  * Ideal for implementing in situations where chatbots specialised in a single-domain are required such as information guides, shop assistants, educational bots, etc.

    ```
    Chanakya: Hey there! I'm Chanakya!
    Ask me anything about 'Star Wars - The Force Awakens'!
  
    You: who is the director?
    Chanakya: JJ Abrams.
  
    You: when did the movie release?
    Chanakya: The worldwide release was 25th December, 2015.
  
    You: name of daisy ridley's character?
    Chanakya: Rey.
  
    You: han solo actor name
    Chanakya: Harrison Ford.
  
    You: bye
    Chanakya: Bye!
    ```
A sample exchange between the user and Chanakya with a **'Star Wars'** knowledge base. We can see that Chanakya **doesn't need perfect grammar** to understand what the user is asking.

## Quickstart
* Clone or download the repository to your machine.
* Navigate to the ```/src``` folder and run the following commands.
  
  For Linux and Mac (in Terminal)
  ```
  $ c++ chanakya.cpp -std=c++0x
  ```
  For Windows (in Command Prompt)
  ```
  cl chanakya.cpp
  ```
* You can now choose the domain or topic that Chanakya will converse about. Navigate to the ```/data``` folder and take a look at the different topics present. Once you have decided the topic, navigate to the ```/config``` folder and edit ```prog.config``` accordingly.

  ```
  name = Chanakya .
  field = <field name here> .
  knowledge_file = ../data/<chat file name here> .
  ```
  
  For example, amongst the topics in the ```/data``` directory, if you'd like to choose Taj Mahal, then your ```prog.config``` file would look something like this.

  ```
  name = Chanakya .
  field = Taj Mahal .
  knowledge_file = ../data/tajmahal.chat .
  ```
  
* Now, execute the following commands, and voila! **You should now have a fully-functioning chatbot!**
  
  For Linux and Mac (in Terminal)
  ```
  $ ./a.out
  ```
  For Windows (in Command Prompt)
  ```
  chanakya
  ```
* Feel free to point out mistakes or give any criticisms!

## Etymology
It's named after **Chanakya** (371 BC - 283 BC), an ancient Indian teacher and royal advisor. Known for being a person who could *answer* the most ardous of questions, he is credited with playing an important role in the establishment of the Mauryan Empire. 

## Tools
* Vim Editor
* Clang C++ Compiler

## Work In Progress
Chanakya is still a work in progress.
* It is always being refined to make it more efficient and fast.
* I'm also thinking about creating a web API so that it can be used in websites. 
