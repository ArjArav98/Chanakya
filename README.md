# Contents
* [What is Chanakya?](#what-is-chanakya)
* [Where can it be used?](#where-can-it-be-used)
* [Quickstart](#quickstart)
* [Any planned features?](#planned-features)
* [Wait, what does 'Chanakya' mean?](#etymology)
* [Tools](#tools)

## What is Chanakya?
**Chanakya is a simple yet completely customisable, scalable and lightweight chatbot.** It is written wholly in C++ and is inspired by the AI concept of 'Expert Systems'. Chanakya has a simple mechanism:- It takes questions from the user, consults a local knowledge base and returns a result. I've listed down some of Chanakya's major features and differences from other chatbots.

* Chanakya's field of expertise can be ***completely customised*** by you, the user! Using a simple syntax that I created for this purpose, you can create knowledge bases for Chanakya on any topic.
* It is ***extremely scalable***. The knowledge base can be increased or decreased with very little impact on performance.
* Chanakya is a ***lightweight*** application and consumes very little memory and CPU time!
* It returns fast and accurate results even if the grammar and semantics of the question aren't exactly correct.

    ```
    Chanakya: Hey there! I'm Chanakya!
    Ask me anything about 'Star Wars - The Force Awakens'!
  
    You: who is the director?
    Chanakya: JJ Abrams.
  
    You: when did the movie release?
    Chanakya: The worldwide release was 25th December, 2015.
  
    You: name of daisy ridley character?
    Chanakya: Rey.
  
    You: han solo actor name
    Chanakya: Harrison Ford.
  
    You: bye
    Chanakya: Bye!
    ```
A sample exchange between the user and Chanakya with a **'Star Wars'** knowledge base. We can see that Chanakya **doesn't need perfect grammar** to understand what the user is asking.

## Where can it be used?
Right now, Chanakya isn't really a production-grade application. However, I am planning to develop a web API which will be able to take questions from a webpage and then return a result. In any case, Chanakya has a wide variety of use-cases in day-to-day life.

* An **educational** and interactive bot for children to learn about various topics and subjects. For example, the 'Bengal Tiger' knowledge base which I've created could be used to let children learn more about the animal and its eating and living habits.
* An **interactive tour guide**. Chanakya could be installed at any monument or heritage site and be used to educate visitors about the place.
* An **e-commerce shopkeeper** which could potentially help customers locate or find a product of their choice amongst the items in a shop.

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

## Any planned features?
Here's a list of some of the features I'd like to implement in the future in no particular order.

* **Word Stemming** - This might help conserve space when adding keywords for a particular branch in the knowledge base.
* **Web API** - An API which can help webpages utilise Chanakya with a simple function call.
* **Approximate Spellings** - In case the spelling of a word is wrong, then an approximation of what the correct word might be can be done.
* **Documentation** - A proper documentation for Chanakya's logic, code and usage.
* **Context** - Adding 'context' to conversations with Chanakya.

## Etymology
It's named after **Chanakya** (371 BC - 283 BC), an ancient Indian teacher and royal advisor. Known for being a person who could *answer* the most ardous of questions, he is credited with playing an important role in the establishment of the Mauryan Empire. 

## Tools
* Vim Editor
* Clang C++ Compiler
