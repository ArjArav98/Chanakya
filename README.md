# Chanakya
**Chanakya is a simple yet completely customisable and scalable chatbot.** Based on the AI concept of 'Expert Systems', Chanakya is written wholly from scratch in C++. 

  * When answering questions read from the user, the chatbot accesses a **large knowledge base**, present in its memory, to find the required information. 
  * The chatbot's field of expertise can be decided by ***you***, the developer!
  * By being written in C++ and accessing a local knowledge base, the chatbot is **extremely fast** and versatile.

### The Knowledge Base
Chanakya's knowledge base should be present as a text file with the extension ```.chat```. The knowledge base can be built using a **unique syntax** created for this very purpose (more on that below). 

  * The knowledge base can be built on any single domain of expertise such as **Star Wars** or **Indian history** or even, say, the **2016 US Presidential elections**.
  * The file must always be present in the ```/data``` folder.
  * A sample knowledge base file is present in the above directory in this git. The subject of the file is **'Chennai Super King's 2019 IPL campaign'**.

  ![csk-screenshot](https://github.com/ArjArav98/Chanakya/blob/master/img/chanakya-screen.png)

## Quickstart
* Clone or download the repository to your machine.
* Navigate to the ```/src``` folder and run the following commands.

  ```c++ chanakya.cpp -std=c++0x``` for Linux or Mac or ```cl chanakya.cpp``` for Windows.
* Once compiled, run these next commands to execute the programs.

  ```./a.out``` for Linux or Mac or ```chanakya``` for Windows.

* **You now have a fully-functioning chatbot!** Since the sample domain is **'Chennai Super Kings' 2019 Season'**, you can ask questions like *'Who was the man of the match in the rcb v csk match?'* or *'Who is csk's batting coach?'*. Try different word combinations of the same question too.
* Feel free to point out mistakes or give any criticisms!

## Etymology
It's named after **Chanakya** (371 BC - 283 BC), an ancient Indian teacher and royal advisor. Known with being a person who could *answer* the most ardous of questions, he is credited with playing an important role in the establishment of the Mauryan Empire. 

## Tools
* Vim Editor
* Clang C++ Compiler

## Work In Progress
Chanakya is still a work in progress.
* It is always being refined to make it more efficient and fast.
* I'm also thinking about creating a web API so that it can be used in websites. 
