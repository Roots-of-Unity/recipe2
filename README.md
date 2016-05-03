
## recipe2 ##
a command line tool for recipes and shopping lists

#### Table of Contents ####
<!-- MarkdownTOC autolink=true depth=3 bracket=round -->

- [Overview](#overview)
- [Description of Problem](#description-of-problem)
- [Proposed Solution](#proposed-solution)
- [Shopping List Ordering Algorithm](#shopping-list-ordering-algorithm)
- [Example Toolchain Scenario](#example-toolchain-scenario)
- [Next Steps](#next-steps)
- [License](#license)
- [Credits and Thanks](#credits-and-thanks)
- [Contact](#contact)

<!-- /MarkdownTOC -->

#### Overview ####
why I switched to the store schema idea
Also, why GRM won't work for every shopping scenario and why more utilities must exist. (think sublists, multiple stores, and mucinex)
#### Description of Problem ####
write me.
#### Proposed Solution ####
write me.
#### Shopping List Ordering Algorithm ####
description.
#### Example Toolchain Scenario ####
Example: I want to prepare a weeks worth of freezer meals for my family. So I begin by generating a shopping list using [Gourmet Recipe Manager](https://github.com/thinkle/gourmet). I want to make one of every dish in my database and 2 slow cooker green bean sides:

![](http://i.imgur.com/vnxz9eB.png)

So I generate a shopping list:

![](http://i.imgur.com/H1CchIB.png)

and format it slightly and print it: (future developments might include using Gourmet Recipe Manager's sqlite database directly)

![](http://i.imgur.com/cy8Tnv1.jpg)

Now that the list is printed firmly onto the original computational device: paper; I can proceed and order it according to the Shopping List Ordering Algorithm described in detail on the wiki. **PUT A LINK HERE**.

![](http://i.imgur.com/t9PFZVz.jpg)

Now, while that list is now "ordered" (future developments include a mobile app to perform this ordering. It's easier graphically and with touch.) in the sense that I've extracted the information that my head knows about 86th Street Costco inventory sequence, it won't be helping anyone in its present form. The list needs to be organized from least to greatest according to the penciled in sequence numbers.

To do that, (and this is why a graphically and touch based app would be the best interface here) I'm going to turn that boring task over to my program. But first, I need to prepare a file that can be read by my project.

I quickly copy and paste the list I printed out into a column in a spreadsheet.

![](http://i.imgur.com/Lv02fYZ.png)

Then I visually parse the hand-sequenced shopping list into the spreadsheet. This is easy because the items are in the same order in both paper and spreadsheet.

![](http://i.imgur.com/c65fG5j.png)

Now, the magic can happen! Observers may note that You can sort the spreadsheet and generate an ordered list, however, it would be challenging to store an overall "schema" about a particular shopping-store using this method. My project takes the first steps into fully implementing store  sequence schemas.

Next, export the spreadsheet as a a UTF-8 encoded, comma separated values file (*.csv):

![](http://i.imgur.com/joN7CSD.png)

For added compatibility (un-necessary on the system I tested with): Use a full-featured text editor (like Notepad++ on Windows) to make sure that the file is UTF-8 without BOM (That's byte order mark. It denotes which UTF encoding the file is in. There are several UTF encodings. The BOM could potentially cause issues.) And make sure that the line ending EOL character matches the target system. I tested with both and the project ran fine.

Next, put your single or multiple shopping list files... (that are ordered as a single sequence. For example: multiple sequences through a store would be lists you made for different trips to the store on different days. Taken together, these lists would not be a single sequence. Ordering these into one schema about a store: say 86th Street Costco is where I have an algorithm developed **SEE WIKI LINK HERE**, and will be implemented in later sessions. The part I coded for this session will be necessary to implement this further down the road.) 

An example of multiple lists that are put in the same sequence using the power of decimal numbers. This grocery list is an old relic that was ran with a typical color coding method: 

![](http://i.imgur.com/k45U5ei.jpg)

The above lists have been included as test *.csv files in the /tests/data directory of this project.

Next...put your single or multiple shopping list files that are in a single sequence into the **same directory** (filesystems are OS specific... therefore I glanced over this feature) as the recipe2 executable, and run the program as follows (assuming Windows in example):

![](http://i.imgur.com/MLwD5QL.png)

And the organized result should be:

![](http://i.imgur.com/gtTTyK6.png)

You can save this output by using your OS's redirection operators (Windows docs found [here](https://technet.microsoft.com/en-us/library/bb490982.aspx).) And copy and paste this into a word processor for a nice organized, and printable list.

![](http://i.imgur.com/pwSUSwM.png)

And then you can get really meta by running that output.txt through the program again. (Only joking, eventually it will be possible, and useful to do that.)

#### Next Steps ####
- GUI Auto Shopper App: It collaboratively maintains a giant database of store item schemas. This is how I'd start monetizing. When I actually became a company, I'd use my purchasing power to snuggle up with retailers for their actual parsable catalog, and make more money datamining.
  - For now, the grocery shopping app is a PnP (pen and paper... the original computation device) application
- CLI "Store the Store" Schema Component: Assumes correct ordering of a store. The correctness will be determined by users via some algorithm. This is what I have partially implemented. This will go onto be a backend to the different facets of the project.
- A smartphone/GUI/custom hardware component that uses OCR to read receipts after a shopping run to see what you actually acquired and from what store. This is one way to weed out inaccurate data and unknown items in stores.
- Patent on an "ordering system that allows for an arbitrary number of unknown items to be ordered at a later time." Woops. There goes that one.
- Add a sharing component of lists for recipes and life in general.
- A GUI/smartphone/touch "editor" for managing stores and their items. Example drawing:  
**DRAW ME**
- Alternate Names:
  - Shopping Tool
  - List Tool
  - Catalog Tool
  - Personal Purchasing Tool: The Future is Promising (R)
  - Buy Me This
  - AutoShopper
  - Jeeves
  - ListManager Pro - Ha! the name of this one makes me think of TradeSkillMaster on World of Warcraft or the spreadsheets of Eve: Online.
  - Never Forget Another Item on a List!

## License ##

<a href="http://www.opensource.org/"><img height="100" align="right" src="http://wiki.opensource.org/bin/download/OSI+Operations/Marketing+%26+Promotional+Collateral/OSI_certified_logo_vector.svg"></a>

recipe2 is certified [Open Source](http://www.opensource.org/docs/definition.html) software. It may be used for any purpose, including commercial purposes, at absolutely no cost. It is distributed under the terms of the [MIT license](http://www.opensource.org/licenses/mit-license.html) reproduced here.

> Copyright (c) 2016 Jace Thompson
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This site and software is not affiliated with or endorsed by the Open Source Initiative. For questions and suggestions about the recipe2 please contact the author at [jthompson161@ivytech.edu](mailto:jthompson161@ivytech.edu)

## Credits and Thanks ##
Dr. Diana Nixon - my CSCI 102 professor at Ivy Tech Community College - for the awesome semester, and for teaching us C++11 so well.  

My classmates this semester:

- Yoosuk
- Ben
- Xuyang
- Kevin
- Jay
- Bard
- Janna

Sample Recipes in *.txt form found [here](https://gist.github.com/Roots-of-Unity/5fbed865347c9366f61433f9fbdad6c0). As Gourmet XML file [here](https://gist.github.com/Roots-of-Unity/0c429ae012ace8e527112c9b7e2f3d9a). I give them my seal of approval. 

Playlists:  

- Battlestar Galactica Season 4 Soundtrack: [link](https://youtu.be/NY3gY48pxjA?list=PL95092E55EDA7E10D)  
  - Lots of coding was done to track 1 performed by Alessandro Juliani.
    - Composed by Bear McCreary
- The Martian OST: [link](https://youtu.be/W4u8-dS7Etg?list=PLFyzg2g9ronE9z6WTG-vq3sYXFeJzSz3_) 
  - by Harry Gregson-Williams
 

Library Credits:  
*Licenses are located in libraries directory of this project.*
 
I made use of:  

- [cxxopts](https://github.com/jarro2783/cxxopts) by Jarryd Beck for parsing command line arguments.
- [UTF8-CPP](https://github.com/nemtrif/utfcpp) by Nemanja Trifunovic for validating UTF-8.

Inspiration on how to layout a README.md from these immaculate projects:  
- [https://github.com/homebysix/recipe-robot](https://github.com/homebysix/recipe-robot)  
- [https://github.com/ColinH/PEGTL](https://github.com/ColinH/PEGTL)

## Contact ##
Jace Thompson  
[jthompson161@ivytech.edu](mailto:jthompson161@ivytech.edu)
